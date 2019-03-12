// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Course : Computational Problem Solving II (CPET-321)
// Developer : Naman Nanda
// Date : Fall 2018
// File :playlist header file
//======================================================================

#include <iostream>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <fstream>// needed for file I/O
#include <string>
#include <cstdlib>// needed for exit()

using namespace std;

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

struct lasstplaylist
{ // title->artist->rank->rank->year->decade->performer->genre->nextsong this is the way the linked list data is arranged in correlation with the billboard text file
  string title;
  string artist;
  int rank;
  int year;
  int decade;
  char performer;
  int genre;
  lasstplaylist *nextsong;
};

void readme(lasstplaylist *current_song);
void displaytextfile(lasstplaylist *current_song);
void displayme(lasstplaylist *namanslist);
void removeme (lasstplaylist *namanslist);
void insertme (lasstplaylist *current_song, lasstplaylist *namanslist);
void createme (lasstplaylist *current_song, lasstplaylist *namanslist);
void saveme (lasstplaylist *namanslist);
void deleteme();

#endif
