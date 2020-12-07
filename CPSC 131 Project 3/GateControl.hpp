#pragma once


#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

typedef size_t CardNumber;

typedef size_t GateNumber;



struct Authorization
{
	Authorization() { }

	Authorization(CardNumber number, const string& name, const string& startTime, const string& endTime)
	: number_(number), name_(name), startTime_(startTime), endTime_(endTime) { }

	CardNumber number_;

	string name_;

	string startTime_;

	string endTime_;
};

typedef map<CardNumber, Authorization> AuthorizationMap;
typedef	AuthorizationMap::iterator AuthorizationMapIterator;

typedef	vector<Authorization> AuthorizationVector;

struct Transaction
{
	Transaction() { }

	Transaction(CardNumber number, const string& name, const string& date, const string& time, bool accessAllowed)
	: number_(number), name_(name), date_(date), time_(time), accessAllowed_(accessAllowed) { }

	CardNumber number_;

	string name_;

	string date_;

	string time_;

	bool accessAllowed_;
};

typedef	vector<Transaction> TransactionVector;
typedef	TransactionVector::iterator TransactionVectorIterator;

class	GateControl
{
	public:
		bool accessAllowed(CardNumber number);

		bool addAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime);

		bool changeAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime);

		bool deleteAuthorization(CardNumber number);

		void getAllAuthorizations(AuthorizationVector& authorizationVector);

		void getAllTransactions(TransactionVector& transactionVector);

		bool getCardAuthorization(CardNumber number, Authorization& authorization);

		void getCardTransactions(CardNumber number, TransactionVector& transactionVector);

	private:
		AuthorizationMap authorizationMap_;

		TransactionVector transactionVector_;
};



extern string gCurrentDate;

extern string gCurrentTime;



//****************************************************************************************
//
//	TO DO
//
//****************************************************************************************


bool GateControl::accessAllowed(CardNumber number)
{
	//	TO DO
	AuthorizationMapIterator iterator = authorizationMap_.find(number);
	if (iterator != authorizationMap_.end()){
		transactionVector_.push_back(Transaction(number,iterator->second.name_,gCurrentDate, gCurrentTime, true));
		return true;
	}
	transactionVector_.push_back(Transaction(number,iterator->second.name_,gCurrentDate,gCurrentTime, false));
	return false;
}


bool GateControl::addAuthorization(CardNumber number, const string & name, const string & startTime, const string & endTime)
{
	//	TO DO
  return authorizationMap_.emplace(pair<CardNumber, Authorization>(number,
				 Authorization(number, name, startTime, endTime))).second;
}


bool GateControl::changeAuthorization(CardNumber number, const string & name, const string & startTime, const string & endTime)
{
	//	TO DO
  AuthorizationMapIterator iterator = authorizationMap_.find(number);
  if (iterator != authorizationMap_.end()){
    iterator->second.name_ = name;
    iterator->second.startTime_ = startTime;
    iterator->second.endTime_ = endTime;
    return true;
  }
  return false;
}


bool GateControl::deleteAuthorization(CardNumber number)
{
	//	TO DO
	AuthorizationMapIterator iterator = authorizationMap_.find(number);
	if (iterator != authorizationMap_.end()){
		authorizationMap_.erase(iterator);
		return true;
	}
	return false;
}


void GateControl::getAllAuthorizations(AuthorizationVector& authorizationVector)
{
	//	TO DO
	authorizationVector.clear();
	for(AuthorizationMapIterator iterator = authorizationMap_.begin(); iterator != authorizationMap_.end(); iterator++){
		authorizationVector.push_back(iterator->second);
	}
}


void GateControl::getAllTransactions(TransactionVector& transactionVector)
{
	//	TO DO
	if (!transactionVector_.empty()){
		transactionVector.assign(transactionVector_.begin(), transactionVector_.end());
	}
	else {
			transactionVector.clear();
	}
}


bool GateControl::getCardAuthorization(CardNumber number, Authorization& authorization)
{
	//	TO DO
	AuthorizationMapIterator iterator = authorizationMap_.find(number);
	if (iterator != authorizationMap_.end()){
		authorization.number_ = number;
		authorization.name_ = iterator->second.name_;
		authorization.startTime_ = iterator->second.startTime_;
		authorization.endTime_ = iterator->second.endTime_;
		return true;
	}
	return false;
}


void GateControl::getCardTransactions(CardNumber number, TransactionVector& transactionVector)
{
	//	TO DO
	for(TransactionVectorIterator iterator = transactionVector_.begin();iterator <= transactionVector_.end(); iterator++){
		if (iterator->number_ == number){
			transactionVector.push_back(*iterator);
		}
	}
}
