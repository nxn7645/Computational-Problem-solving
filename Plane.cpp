// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Course : Computational Problem Solving II (CPET-321)
// Developer : Naman Nanda
// Date : Fall 2018
// File : Playlist
//======================================================================
#include <vector>
#include <iostream>
using namespace std;
//----------------------------------------------------------------------------------------------------------------//
class Plane{ //the class for occupying the seats on the different planes available
protected:
	int row, col;
	vector<string> seats;
	string planeName;
	string seatInitials;
	int creditNeeded;
	void setSeats(const vector<string> &seats){ //setting the seats on the plane
		this->seats = seats;}
	void setSeatInitials(string seatInitials){ // set initials of the column
		this->seatInitials = seatInitials;}
public:
	Plane(string name, int creditNeeded){
		this->planeName = name;			
		this->creditNeeded = creditNeeded;
	}

	Plane(){
	}
	string getSeatInitials(){
		return this->seatInitials;
	}
	string getName(){
		return this->planeName;
	}
	int getCreditNeeded(){
		return this->creditNeeded;
	}
	vector<string> getSeats(){
		return this->seats;
	}
	bool isFull(){ //checks to see if the plane is full or not
		for(int r = 1; r < seats.size(); r++){
			for(int c = 0; c < seats[r].size(); c++){
				if(seats[r][c] == '0')
					return false;
			}
		}
		return true;
	}

	void printAvailableSeats(){//evaluates the seats available before it shows it to the user for selection
		cout << "Seating\n_ : Available\t * : Unavailable" << endl;
		cout << "      " + seatInitials << endl;
		for(int r = 1; r < seats.size(); r++){
			cout << "row " + to_string(r) + " ";
			for(int c = 0; c < seats[r].size(); c++){
				cout << ((seats[r][c] == '0') ? '_' : '*');
			}
			cout << endl;
		}
	}

	bool reserveSeat(int r, int c){ //after the user selects the seat it reserves the seat
		if(r < 0 || r >= seats.size() || c < 0)
			return false;
		else if(seats.size() && (c >= seats[0].size()))
			return false;
		else if(seats[r][c] == '1')
			return false;
		else{
			//reservation successful
			this->seats[r][c] = '1';
			return true;
		}
	}

	bool unreserveSeat(int r, int c){//after the user selects to delete or modify a seat it unreserves the seat
		if(r < 0 || r >= seats.size() || c < 0)
			return false;
		else if(seats.size() && (c >= seats[0].size()))
			return false;
		else if(seats[r][c] == '0')
			return false;
		else{
			//reservation successfully cancelled
			seats[r][c] = '0';
			return true;
		}
	}
};

class Bombardier : public Plane{ //2 planes for bombadier
public:
	Bombardier(string FlightName) : Plane(FlightName, 1) {
		vector<string> seats;

		//8 rows and 4 available columns
		for(int i = 0; i < 9; i++)
			seats.push_back("0000");

		this->setSeatInitials("ABDE");
		this->setSeats(seats);
	}
};


class Dehavilland : public Plane{//4 planes for dehavilland
public:	
	Dehavilland(string FlightName) : Plane(FlightName, 2) {
		vector<string> seats;

		//4 rows and available columns
		for(int i = 0; i < 4; i++)
			seats.push_back("00100");
		seats.push_back("00000");	//C-th column is also available


		this->setSeatInitials("ABCDE");
		this->setSeats(seats);
	}
};

class Kingsair : public Plane{//4 planes for kingsair
public:	
	Kingsair(string FlightName) : Plane(FlightName, 3) {
		vector<string> seats;

		//4 rows and available columns
		for(int i = 0; i < 5; i++)
			seats.push_back("00");
		seats.push_back("10");	//A-th column is unavailable in 5th row
		seats.push_back("00");


		this->setSeatInitials("AD");
		this->setSeats(seats);
	}
};
