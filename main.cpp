// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Course : Computational Problem Solving II (CPET-321)
// Developer : Naman Nanda
// Date : Fall 2018
// File : Playlist
//======================================================================
#include <iostream>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <string>
#include <cstdlib>
#include "bfunctions.hpp"
using namespace std;
//----------------------------------------------------------------------------------------------------------------//
// reads the contents from the text file (used only once)
void readme(lasstplaylist *current_song)
{
	string rankme, yearme, decademe, performerme, genreme;
	ifstream inFile;
	inFile.open("billboard.txt"); //opens the billboard
	if (inFile.fail())
	{
		cout << "Cant open! Bye" << endl;
		exit (1);
	}
	do
	{
		getline(inFile, current_song->title); //gets all the lines from the billboard file line by line
		getline(inFile, current_song->artist);
		getline(inFile, rankme);
		current_song -> rank = atoi(rankme.c_str());
		getline(inFile, yearme);
		current_song -> year = atoi(yearme.c_str());
		getline(inFile, decademe);
		current_song -> decade = atoi(decademe.c_str());
		getline(inFile, performerme);
		current_song -> performer = performerme[0];
		getline(inFile, genreme);
		current_song -> genre = atoi(genreme.c_str());
		if (inFile.eof())
		{
			current_song->nextsong = NULL;
			break;
		}
		else
		{
			current_song->nextsong = new lasstplaylist;
			current_song = current_song->nextsong; //next song
		}
	}
	while (true);
	return;
}
//----------------------------------------------------------------------------------------------------------------//
void displaytextfile(lasstplaylist *current_song)
{
	int cnt = 1; // this is the display function to display the original billboard text file
	cout << "The Original list of 100 songs is as follows:" << endl;
	cout<< setw(10) << left << "#" << setw(60) << left << "Title" <<setw(60) << left << "Artist"<<setw(60) << left << "Rank"<<setw(20) << left << "Year"<<setw(20) << left << "Decade"<<setw(20) << left << "Performer"<<setw(20) << left << "genre" <<endl;
	while (current_song != NULL)
	{
	cout << setw(10) << left << cnt <<setw(60) << left << current_song->title<< setw(60) << left <<current_song->artist << setw(60) << left << current_song->rank<< setw(20) << left << current_song->year<< setw(20) << left << current_song->decade<< setw(20) << left <<current_song->performer<< setw(20) << left <<current_song->genre<< endl;
    cnt++;
	current_song = current_song->nextsong;
	}
	return;
}
//----------------------------------------------------------------------------------------------------------------//
void displayme(lasstplaylist *namanslist)
{
	string userPlaylistName; // this is used to display the playlist file that was created by the user and printed and saved
	int cnt = 1;
	cout << "Enter the playlist name: ";
		cin >> userPlaylistName;
		std::ifstream inFile ((userPlaylistName += ".txt").c_str()); // tries to find the file
		if (inFile.fail())
		{
			cout << "No such playlist exist" << endl;
			exit (1);
		}
		cout << "Your Playlist contains these songs:" << endl; // displays the songs in that playlist

		cout<< setw(10) << left << "#" << setw(60) << left << "Title" <<setw(60) << left << "Artist"<<setw(60) << left << "Rank"<<setw(20) << left << "Year"<<setw(20) << left << "Decade"<<setw(20) << left << "Performer"<<setw(20) << left << "genre" <<endl;
				while (namanslist != NULL)
		{
			cout << setw(10) << left << cnt <<setw(60) << left << namanslist->title<< setw(60) << left <<namanslist->artist << setw(60) << left << namanslist->rank<< setw(20) << left << namanslist->year<< setw(20) << left << namanslist->decade<< setw(20) << left <<namanslist->performer<< setw(20) << left <<namanslist->genre<< endl;
		    cnt++;
			namanslist = namanslist->nextsong;
		}
		cout << endl;
}
//----------------------------------------------------------------------------------------------------------------//
//user can remove any song from the playlist that has been created
void removeme (lasstplaylist *namanslist)
{
	string usergvnname;
	cout << "Enter the playlist name: ";
	cin >> usergvnname;
	ifstream inFile;
	inFile.open((usergvnname+ ".txt").c_str()); //tried to find the file
	if (inFile.fail())
	{
			cout << "Cant open! Bye" << endl;
			exit (1);
	}
	int position, cnt = 2;
	lasstplaylist *tmp1, *tmp2;
	tmp1 = namanslist;
	tmp2 = tmp1 -> nextsong;
	cout << "Remove which song? "; //asks the suer teh position of the song
	cin >> position;
	while(cnt++ < position)
		{
			tmp1 = tmp2;
			tmp2 = tmp1 -> nextsong;
		}
	tmp1 -> nextsong = tmp2 -> nextsong; //deletes the pointer that points to the position selected by the user
	// same as in contact info excersice thatw e did in class
	delete(tmp2);
	cout << "The song was removed" <<endl;
}

//----------------------------------------------------------------------------------------------------------------//
// inserts a song in the playlist
void insertme (lasstplaylist *current_song, lasstplaylist *namanslist)
{

	string usergvnname;
	int cnt = 1, position, rnk;
	cout << "Enter the name of an existing playlist: ";
	cin >> usergvnname; //asks about the playlist they wanna edit

	if (usergvnname != namanslist -> title)
	{
		cout << "Playlist doesnt exist" << endl;
	}

	ifstream inFile;
	inFile.open((usergvnname + ".txt").c_str()); //tried to find it

	if (inFile.fail())
	{
		cout << "Cant open! Bye" << endl;
		exit (1);
	}

	cout << "What is the rank of the song that you want to add? ";
	cin >> rnk;
	if (rnk < 1 ||rnk > 100 ) //only allows the suer to choose the ranks available
	{
		cout << "Rank is not within limits" << endl;
	}
	lasstplaylist *trvsefirst;
	lasstplaylist *trvsesecond, *tmp; //declartion of pointers
	trvsefirst = current_song;
	trvsesecond = namanslist;
	while (cnt < rnk)
	{
		trvsefirst = trvsefirst -> nextsong;
		cnt++;
	}

	cout << "Where would you like to insert the song? ";
	cin >> position;

	if (position < 1 || position > 100)
	{
		cout << "Not within limits" << endl;
	}
	tmp = new(lasstplaylist);

		for (int i=1; i<position; i++) //tries to find the position the user selected
		{
			trvsesecond -> title = trvsefirst -> title;
	trvsesecond -> artist = trvsefirst -> artist; //linked list magic
	trvsesecond -> rank = trvsefirst -> rank;
	trvsesecond -> year = trvsefirst -> year;
	trvsesecond -> decade = trvsefirst -> decade;
	trvsesecond -> performer = trvsefirst -> performer;
	trvsesecond -> genre = trvsefirst -> genre;
	trvsesecond = trvsesecond -> nextsong;
	trvsesecond = trvsefirst;
	//trvsesecond = trvsesecond->nextsong;
		}
			tmp -> nextsong = trvsesecond->nextsong;
			trvsesecond->nextsong = tmp;
			return;
}
//----------------------------------------------------------------------------------------------------------------//
//function that controls the creation of playlist using the 4 categories
void createme(lasstplaylist *current_song, lasstplaylist *namanslist)
{
	string playlistName;
	string rankme, yearme, decademe, performerme, genreme;

	lasstplaylist *trvsefirst;
	trvsefirst = current_song;

	int optionscreate;
	cout << "What way do you want to sort them" << endl; //gives options to choose from
	cout << "1. Ranking"<< endl;
	cout << "2. Decade"<< endl;
	cout << "3. Performer Type"<< endl;
	cout << "4. Genres"<< endl;
	cin >> optionscreate;
cout << "What would you like to name your playlist? ";
cin >> playlistName;
	switch(optionscreate)
	{
		case 1:
		{		//ranking is shown as the first case
			char pool;

			namanslist -> title = playlistName;
			int rankoptions, cnt = 20;
			do{
				cout << "choose the ranks";
				       cin >> rankoptions;
				while(trvsefirst != NULL){
				       if (trvsefirst -> rank == rankoptions) //tried to find the ranked song choosen by the user
				       	  {
				    	   	   namanslist -> nextsong = new lasstplaylist;
				    	   	   namanslist = namanslist->nextsong;
				    	   	   namanslist -> title = trvsefirst -> title;
				    	   	   namanslist -> artist = trvsefirst -> artist;
				    	   	   namanslist -> rank = trvsefirst -> rank;
				    	   	   namanslist -> year = trvsefirst -> year;
				    	   	   namanslist -> decade = trvsefirst -> decade;
				    	   	   namanslist -> performer = trvsefirst -> performer;
				    	   	   namanslist -> genre = trvsefirst -> genre;
				    	   	   cnt--;
				       	  }
					   trvsefirst = trvsefirst -> nextsong;
					}
				   namanslist -> nextsong = NULL;

					cout << "Do you want to add another rank(y/n)?" << endl; //asks the user if they want to add another song or not
				    cin >> pool;
				    if (pool == 'n')
				    {
				    	break;
				    	cout << "Your playlist has been created!(please save it before doing anything else on it)" << endl;
				    }
				} while (cnt < 21); // as it reaches 21 songs it breaks
			cout << "Your playlist has been created!(please save it before doing anything else on it)" << endl;
					break;
				}
		case 2:
		{	//decade is sorted int his case
			int decadeoptions;
			cout << "Decade options" << endl;
			cout << "50 or 60 or 70 or 80 or 90 or 00 or 10"<< endl; //which decade the suer wants
			cin >> decadeoptions;
			namanslist -> title = playlistName;
			while(trvsefirst != NULL)
			{
				if (trvsefirst->decade == decadeoptions)
				{
					namanslist -> nextsong = new lasstplaylist;
					namanslist = namanslist->nextsong;
					namanslist -> title = trvsefirst -> title;
					namanslist -> artist = trvsefirst -> artist;
					namanslist -> rank = trvsefirst -> rank;
					namanslist -> year = trvsefirst -> year;
					namanslist -> decade = trvsefirst -> decade;
					namanslist -> performer = trvsefirst -> performer;
					namanslist -> genre = trvsefirst -> genre;
				}
			 trvsefirst = trvsefirst->nextsong;

			}
			namanslist -> nextsong = NULL;
			cout << "Your playlist has been created!(please save it before doing anything else on it)" << endl;
			break;
		}
		case 3:
		{	//performer type is sorted in this case

			namanslist -> title = playlistName;
			namanslist = namanslist -> nextsong;
			char performeroptions;
			cout << "Gender options:" << endl;
			cout << "F or M or B or G"<< endl; //asks the user whether they want to choose band male or female or duo
		    cin >> performeroptions;
		   namanslist -> title = playlistName;
			while(trvsefirst != NULL)
			{
				if (trvsefirst->performer == performeroptions)
				{
					namanslist -> nextsong = new lasstplaylist;
					namanslist = namanslist->nextsong;
					namanslist -> title = trvsefirst -> title;
					namanslist -> artist = trvsefirst -> artist;
					namanslist -> rank = trvsefirst -> rank;
					namanslist -> year = trvsefirst -> year;
					namanslist -> decade = trvsefirst -> decade;
					namanslist -> performer = trvsefirst -> performer;
					namanslist -> genre = trvsefirst -> genre;
				}
				trvsefirst = trvsefirst->nextsong;
			}
			namanslist -> nextsong = NULL;
			//cout << "Your playlist has been created!(please save it before doing anything else on it)" << endl;
			break;
		}
		case 4:
		{
//genre type is used in this case ----there are 8 genres
			int genreoptions;
			namanslist -> title = playlistName;
			namanslist = namanslist -> nextsong;
			cout << "Genre options:" << endl;
			cout << "1.Latin"<< endl;
			cout << "2.Country"<< endl;
			cout << "3.Hip-Hop/Rap"<< endl;
			cout << "4.Jazz"<< endl;
			cout << "5.Dance/Electronic"<< endl;
			cout << "6.R&B"<< endl;
			cout << "7.Pop"<< endl;
			cout << "8.Rock"<< endl;
			cin >> genreoptions;
			namanslist -> title = playlistName;
			while(trvsefirst != NULL)
			{
				if (trvsefirst->genre == genreoptions)
				{
					namanslist -> nextsong = new lasstplaylist;
					namanslist = namanslist->nextsong;
					namanslist -> title = trvsefirst -> title;
					namanslist -> artist = trvsefirst -> artist;
					namanslist -> rank = trvsefirst -> rank;
					namanslist -> year = trvsefirst -> year;
					namanslist -> decade = trvsefirst -> decade;
					namanslist -> performer = trvsefirst -> performer;
					namanslist -> genre = trvsefirst -> genre;
				}
				trvsefirst = trvsefirst->nextsong;
			}
				namanslist -> nextsong = NULL;
				//cout << "Your playlist has been created!(please save it before doing anything else on it)" << endl;
				break;
			}
		default:
		{
			cout << "invalid input" << endl;
			break;
		}
	}
}


//----------------------------------------------------------------------------------------------------------------//
//user has to save the playlist before he can display or do anythign to it
void saveme(lasstplaylist *namanslist)
{
	string usergvnname, inputme;
	cout << "Type the name of your playlist:";
	cin >> usergvnname; //ask the user the name of the playlist
	inputme = usergvnname;
	ofstream file;
	file.open ((usergvnname+".txt").c_str()); //prints it on a text file
	if (inputme != namanslist -> title)
	{
		cout << "Playlist name is not right" << endl;
	}
	while (namanslist != NULL)
	{
		file << namanslist->title<< endl;
		file << namanslist->artist<< endl;
		file << namanslist->rank<< endl;
		file << namanslist->year<< endl;
		file << namanslist->decade<< endl;
		file << namanslist->performer<< endl;
		file << namanslist->genre<< endl;
		namanslist = namanslist->nextsong;
	}
	cout << endl;
	file.close(); //after adding all the songs it closes the file
	cout<< "The playlist has been printed in a text file and saved" << endl;
	return;


}
//----------------------------------------------------------------------------------------------------------------//
//deleting the whole playlist as chosen by the user
void deleteme(){
	string DeleteMe; // deletes the whole text file
		cout << "Write the name of the playlist you would like to delete?"<<endl;
		cin >> DeleteMe;
		if(remove((DeleteMe+".txt").c_str())!= 0){
			perror ("Can not delete");
		}
		else
		{
				cout << "Done deleting";
		}
		cout << "Your playlist has been deleted!" << endl;
}

//----------------------------------------------------------------------------------------------------------------//
//where the magic happens

int main()
{
	lasstplaylist *head;
	lasstplaylist *namanslist; //pointers declared to be used
	head = new lasstplaylist;
	namanslist = new lasstplaylist;
	readme(head);
	int  options = 0;
	bool dothis = true;

	  while (dothis == true)
	  {
			cout<<"Welcome to Naman's Music Playlist creator!"<< endl; //awesome menu
			cout<<"What would you like to do?"<< endl;
			cout<<"1. Create your playlist" << endl;
			cout<<"2. Remove a song from your playlist"<< endl;
			cout<<"3. Insert your playlist"<< endl;
			cout<<"4. Delete your playlist"<< endl;
			cout<<"5. Display your playlist"<< endl;
			cout<<"6. Save the playlist"<< endl;
			cout<<"7. Display the original list of 100 songs"<< endl;
			cout<<"8. Quit"<< endl;

			cin >> options;

			switch(options) //switch allows us to choose different options
			{
			case 1: {
						createme(head, namanslist);  //calls the create function
						break;
					}
			case 2: {
						removeme(namanslist);//calls the remove function
						break;
					}
			case 3: {
						insertme(head, namanslist);//calls the insert function
						break;
					}
			case 4: {
						deleteme(); //calls the delete function
						break;
					}
			case 5: {
						displayme(namanslist);//calls the display function
						break;
					}
			case 6: {
						saveme(namanslist);//calls the save function
						break;
					}
			case 7: {
						displaytextfile(head);//calls the display text file function to display the origional list of 100 songs
						break;
					}
			case 8: {
						dothis = false;  // breaks if the user selects exit
						break;
					}
			default:
					{
						cout << "Please choose something else!" << endl;
						//menu = false;
						break;
					}
			   }
	       }
}
