// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Course : Computational Problem Solving II (CPET-321)
// Developer : Naman Nanda
// Date : Fall 2018
// File : Playlist
//======================================================================
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>      // std::stringstream
#include <assert.h>

using namespace std;

//----------------------------------------------------------------------------------------------------------------//
class PassengersDataProcessing
{
	//----------------------------------------------------------------------------------------------------------------//
private:
	unordered_map<string,int> passengersCredit;
	string passengersCreditFileName;
	//----------------------------------------------------------------------------------------------------------------//
public:
	//----------------------------------------------------------------------------------------------------------------//
	int getCredit(string name){//checks the credit that each name has in the text file
		if(passengersCredit.count(name))
			return passengersCredit[name];
		else return -1;	//error member not found
	}
	//----------------------------------------------------------------------------------------------------------------//
	bool setCredit(string name, int credit){
		if(passengersCredit.count(name)){
			passengersCredit[name] = credit;
			return true;
		}
		else{
			return false;	//error member not found
		} 
	}
	//----------------------------------------------------------------------------------------------------------------//
	void loadPassengersCredit(string filename){ //reads the credit and tells the program how many credits the person got
		this->passengersCreditFileName = filename;

		ifstream passengersCreditData(filename);
		assert(passengersCreditData.is_open());
		string line;
		while(getline(passengersCreditData, line)){
			stringstream ss(line);
			string fname, lname;
			int credit;

			ss >> lname >> fname >> credit;

			passengersCredit[lname + " " + fname] = credit;
		}
		passengersCreditData.close();
	}
	//----------------------------------------------------------------------------------------------------------------//
	void savePassengersCredit(){//saves the credit after any reservation is made
		ofstream passengersCreditData(passengersCreditFileName, ofstream::trunc);
		assert(passengersCreditData.is_open());
		for(auto data : passengersCredit){
			passengersCreditData << data.first + " " + to_string(data.second) + "\n";
		}
		passengersCreditData.close();
	}
	
};
//----------------------------------------------------------------------------------------------------------------//
