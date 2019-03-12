// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Course : Computational Problem Solving II (CPET-321)
// Developer : Naman Nanda
// Date : Fall 2018
// File : Airplane reservation system
//======================================================================
#include <iostream>
#include <set>
#include <conio.h>
#include <fstream>
#include <unordered_map>
#include <vector>
#include "Plane.cpp"
#include "PassengersDataProcessing.cpp"
using namespace std;
//----------------------------------------------------------------------------------------------------------------//
struct reservationData
{
	string name;
	string departingFlight;
	string departingFlightSeatNo;
	string returningFlight;
	string returningFlightSeatNo;
	string seatInitialsDepartingFlight;
	string seatInitialsReturningFlight;
	int planereturningindex;
	int planeongoingindex;
};
//----------------------------------------------------------------------------------------------------------------//
class AirShuttleReservationSystem
{
	unordered_map<string, reservationData> reservationsData;	
	PassengersDataProcessing passengersData;
	set<string> reservationsMade;
	Plane *planes[10];

	//----------------------------------------------------------------------------------------------------------------//
	bool __modifyReservation(bool fdel = false) // the delete and modify both run from this function
	{
		cout << "Enter the Reservation Code : "; //it asks for the reservation code
		string please; cin >> please;

		if(reservationsData.count(please))
		{
			reservationsMade.erase(please.substr(4, 2)); //erases the original reservation(if its delete it stops there but if its modify the function keeps going)
			reservationData dat = reservationsData[please];

			int a = planes[dat.planeongoingindex]->getCreditNeeded();
			int b = planes[dat.planereturningindex]->getCreditNeeded();
			string name = dat.name;
			int credit = passengersData.getCredit(name) + a + b;
			passengersData.setCredit(name, credit);

			planes[dat.planeongoingindex]->unreserveSeat(dat.departingFlightSeatNo[0] - '0', dat.departingFlightSeatNo[1] - '0');
			planes[dat.planereturningindex]->unreserveSeat(dat.returningFlightSeatNo[0] - '0', dat.returningFlightSeatNo[1] - '0');

			reservationsData.erase(please);
			cout << "Passenger Name : " << name << endl;
			if(fdel) return true;
			else return CreateReservation(name);
		}
		else
		{
			cout << "Error : Reservation not found. Please check the code." << endl;
			return false;
		}
	}
//----------------------------------------------------------------------------------------------------------------//
public:
	AirShuttleReservationSystem()
{
		planes[0] = new Bombardier("B1O"); //arrays for the 9 planes
		planes[1] = new Dehavilland("D1O");
		planes[2] = new Dehavilland("D2O");
		planes[3] = new Kingsair("K1O");
		planes[4] = new Kingsair("K2O");

		//return flights modelled as different planes itself
		planes[5] = new Bombardier("B1R");
		planes[6] = new Dehavilland("D1R");
		planes[7] = new Dehavilland("D2R");
		planes[8] = new Kingsair("K1R");
		planes[9] = new Kingsair("K2R");

		//load passenger Data
		passengersData.loadPassengersCredit("CGA_members.txt");
	}
	//----------------------------------------------------------------------------------------------------------------//
	~AirShuttleReservationSystem()
	{
		passengersData.savePassengersCredit();
		for(int i = 0; i < 10; i++)
			delete this->planes[i];
	}

	//----------------------------------------------------------------------------------------------------------------//
	string getReservationNo()
	{
		int maxx = 1;
		string ret = (maxx < 10) ? "0" + to_string(maxx) : to_string(maxx);
		while(reservationsMade.find(ret) != reservationsMade.end())
		{
			maxx++;
			ret = (maxx < 10) ? "0" + to_string(maxx) : to_string(maxx);
		}

		ret = (maxx < 10) ? "0" + to_string(maxx) : to_string(maxx);
		reservationsMade.insert(ret);
		return ret;
	}
	//----------------------------------------------------------------------------------------------------------------//
	bool CreateReservation()
	{

		string lname, fname;
		cout << "Enter the last name : " ; //this is the create function loop
		cin >> lname;
		cout << "Enter the first name : " ; //the user enters users first and last name
		cin >> fname;

		string name = lname + " " + fname;
		return CreateReservation(name);
	}
	//----------------------------------------------------------------------------------------------------------------//
	bool CreateReservation(string name)
	{
		int credit = passengersData.getCredit(name); //after the name has been inputed it checks if thats is in the text file or mot
		if(credit == -1){
			cout << "Error : Member not found" << endl;
			return false;
		}

		cout << "Flight Credits : " << credit << endl; //compares the number of credits assigned to them because if its less than 2 they cant make a booking
		if(credit < 2)
		{
			cout << "Error : not enough credits to complete round trip" << endl;
			return false;	
		}

		vector<int> indexMapping;
		cout << "Select a plane for LA->LV (Ongoing) journey" << endl; //if the name has been found and the credits are enough then it allows the user
		int c = 0;                                                   // to select a plane for outgoing journey
		for(int i = 0; i < 5; i++)
		{
			if((!planes[i]->isFull()) && planes[i]->getCreditNeeded() < credit){
				cout << ++c << ". " << planes[i]->getName() << endl;
				indexMapping.push_back(i);

				if(i == 1 || i == 3) i++;
			}
		}
		if(c == 0){
			cout << "Error : No planes available or low credit" << endl; //it compares the number of credits to the number of credits required for the particular plane choosen
			return false;
		}
		int a;
		cin >> a;
		if(a > c || a <= 0){
			cout << "Error : invalid choice" << endl;
			return false;	
		}
		a--;
		a = indexMapping[a];
		planes[a]->printAvailableSeats(); //this function displays the seats available int he plane that was choosen
		int r; char ch;
		seatsel:;
		cout << "Enter row : "; cin >> r; //the row and the column selection is entered
		cout << "Enter col : "; cin >> ch;
		c = planes[a]->getSeatInitials().find(ch);
		if(c == string::npos)
		{
			cout << "Error : Seat Column Invalid" << endl; //if the colums selected doesnt exist then it displays that
			return false;		
		}
		if(planes[a]->reserveSeat(r, c))
		{
			cout << "Ongoing Reservation Successful\n"; //if one of the flights is succesful it shows that
			passengersData.setCredit(name, credit - planes[a]->getCreditNeeded());
		}
		else
		{
			cout << "Error : Seat Unavailable. Try Again.\n"; //if the seat is occupied than it shows that
			goto seatsel;
		}
		int b = a;
		int r1 = r, c1 = c;

		returnjourney:;
		cout << "Select a plane for LV->LA (Return) journey" << endl; //now it allows the user to select the return flight
		indexMapping.clear();
		credit = passengersData.getCredit(name);
		c = 0;
		for(int i = 5; i < 10; i++)
		{
			if(!planes[i]->isFull() && planes[i]->getCreditNeeded() <= credit) //comapres the number of credits the person got
			{
				cout << ++c << ". " << planes[i]->getName() << endl;
				indexMapping.push_back(i);

				if(i == 6 || i == 8) i++;
			}
		}

		if(c == 0){
			cout << "Error : No Planes Available or low credit" << endl; //if the credits are not enough it displays this
			return false;
		}

		cin >> a;
		if(a > c || a <= 0)
		{
			cout << "Error : invalid choice. Please try again." << endl;
			goto returnjourney;	
		}
		a--; a = indexMapping[a];

		planes[a]->printAvailableSeats();
		seatsel1:;
		cout << "Enter row : "; cin >> r; //does the same thing that we did for the outgoing flight
		cout << "Enter col : "; cin >> ch;
		c = planes[a]->getSeatInitials().find(ch);
		if(c == string::npos)
		{
			cout << "Error : Seat Column Invalid. Try Again.\n";
			goto seatsel1;
		}

		if(planes[a]->reserveSeat(r, c))
		{
			cout << "Return Reservation Successful\n";
			passengersData.setCredit(name, credit - planes[a]->getCreditNeeded());
		}

		else
		{
			cout << "Error : Seat Unavailable. Try Again.\n";
			goto seatsel1;
		}

		string pname = planes[b]->getName().substr(0, 2);
		string qname = planes[a]->getName().substr(0, 2);
		string please = pname + qname + getReservationNo();

		reservationData dat;
		dat.name = name;
		dat.departingFlight = pname;
		dat.returningFlight = qname;
		dat.departingFlightSeatNo = to_string(r1) + to_string(c1);
		dat.returningFlightSeatNo = to_string(r) + to_string(c);

		dat.planeongoingindex = b;
		dat.planereturningindex = a;

		dat.seatInitialsReturningFlight = planes[a]->getSeatInitials(); //combines everything to make a reservation code
		dat.seatInitialsDepartingFlight = planes[b]->getSeatInitials();

		reservationsData[please] = dat;
		cout << "The reservation code is " + please << endl; //displays the code
		return true;
	}
	//----------------------------------------------------------------------------------------------------------------//
	bool ModifyReservation(){
		bool ret = __modifyReservation();
		if(ret) cout << "Reservation Updated Successfully." << endl; //when modify is selected in the menu it loops here
		return ret;
	}	
	//----------------------------------------------------------------------------------------------------------------//
	bool DeleteReservation(){
		bool ret = __modifyReservation(true);
		if(ret) cout << "Reservation Cancelled Successfully." << endl;//when delete is selected in the menu it loops here
		return ret;
	}
	//----------------------------------------------------------------------------------------------------------------//
	void PrintManifest(){ //this option is a secret option for the empolyee who works for the airlines
		string filename;
		for(int i = 0; i < 5; i++){
			filename = planes[i]->getName() + ".txt"; //after the password is put this function is called up
			ofstream file(filename, ofstream::trunc); // there are 10 files that printed with 4 files for kings and dalveride planes for outgoing and incoming and 2 files for bambaried

			file << "Plane Name : " << planes[i]->getName() << endl;
			file << "Flight Path : LALV" << endl;
			for(auto dat : reservationsData){
				if(dat.first.substr(0, 2) == planes[i]->getName().substr(0,2)){ //it prints all the seats occupied in that plane only
					char col = dat.second.departingFlightSeatNo[1];
					col = dat.second.seatInitialsDepartingFlight[col - '0'];
					file << dat.second.departingFlightSeatNo[0] << col << " " << dat.second.name << endl;
				}
			}
		}

		for(int i = 5; i < 10; i++){
			filename = planes[i]->getName() + ".txt";
			ofstream file(filename, ofstream::trunc);

			file << "Plane Name : " << planes[i]->getName() << endl;//it prints all the seats occupied in that plane only
			file << "Flight Path : LVLA" << endl;
			for(auto dat : reservationsData){
				if(dat.first.substr(2, 2) == planes[i]->getName().substr(0,2)){
					char col = dat.second.returningFlightSeatNo[1];
					col = dat.second.seatInitialsReturningFlight[col - '0'];
					file << dat.second.returningFlightSeatNo[0] << col << " " << dat.second.name << endl;
				}
			}
		}
	}
	//----------------------------------------------------------------------------------------------------------------//
	bool PrintReservation(){ //prints the reservation for the user
		cout << "Enter the Reservation Code : ";
		string please;
		cin >> please; //the user enters there reservation code

		if(reservationsData.count(please)){
			ofstream myfile("LAST_F_" + please + ".txt"); //it prints the text file in the format LAST_F_ticketno.txt file
			if(myfile.is_open()){
				reservationData dat = reservationsData[please];
				myfile << "Name : " << dat.name << endl //this is all the information that goes into the the text file (of the ticket0
					<< "Departing Flight Code : " << dat.departingFlight << endl
					<< "Departing Flight Seat : " << dat.departingFlightSeatNo << endl
					<< "Returning Flight Code : " << dat.returningFlight << endl
					<< "Returning Flight Seat : " << dat.returningFlightSeatNo << endl;
				myfile.close();
			}else{
				cout << "Error : Couldn't save the file" << endl; //if the file was not able to be saved
				return false;
			}	
			myfile.close();
			cout << "Your ticket has been Saved. Please check the text file!" <<endl;
		}		
		else{
			cout << "Error : Reservation not found. Please check the code." << endl;
			return false;
		}

		return true;
	}
};
//----------------------------------------------------------------------------------------------------------------//
 //where the magic happens
int main(){
	int cont = 1;
	int line;
	string password;
    AirShuttleReservationSystem ReservationSystem;
    while(cont)
    {
			cout<<"Welcome to Compulsive Gambler's Airline!"<<endl; //the user menu is printed here
			cout<<"1. Create a Reservation"<<endl;
			cout<<"2. Modify a Reservation"<<endl;
			cout<<"3. Delete a Reservation"<<endl;
			cout<<"4. Print a Reservation"<<endl;
			cout<<"5. Exit" <<endl;
			cin >> line;

			switch(line)
			{
					   case 1:
							  ReservationSystem.CreateReservation(); //calls the create function
							  break;
					   case 2:
							  ReservationSystem.ModifyReservation(); //calls the modify function
							  break;
					   case 3:
							  ReservationSystem.DeleteReservation();//allows to delete reservation
							  break;
					   case 4:
							  ReservationSystem.PrintReservation(); //helps to print the ticket for the user
							  break;
					   case 5:
							  cont = 0;
							  break;
					   case 6:
							  cout << "enter password?" << endl; //secret menu for the employee to access the manifest
							  cin >> password;
							  if(password == "mypassword")
							  {
								  ReservationSystem.PrintManifest();
							  }
							  else
							  {
								  cout << "Wrong Password." << endl;
							  }
							  break;
					   default:
							  cout<< "Invalid Choice" << endl;
							  break;
			}

    }
	return 0;
}
//----------------------------------------------------------------------------------------------------------------//
