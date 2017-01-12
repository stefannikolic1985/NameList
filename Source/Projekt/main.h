//------------------------------------------------------------------------------
// Projektuppgift
// DT018G_stni1401_Projekt
// Stefan Nikolic 2017-06-01
//------------------------------------------------------------------------------
#ifndef MAIN_H
#define MAIN_H

#include <regex>
#include "constants.h"
#include <conio.h>  // for using _getch() for press any key to continue 
#include <sstream> // read from files
#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <ctime> 
#include <vector> 
#include <limits>
#include <algorithm>
#include <cstdlib>      // std::rand, std::srand
#include <iterator>
#include <iostream> // writing on a text file
#include <fstream> // writing on a text file
using std::find;
using std::remove;

using namespace std;
//------------------------------------------------------------------------------
// Funktionsprototyper
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Menu
//------------------------------------------------------------------------------
void getMenuText(vector<string> &texts);
int showMenu(vector<string> &texts, vector<Person> &persons);

//------------------------------------------------------------------------------
// Add new person
//------------------------------------------------------------------------------
void addPerson(vector<Person> &persons);
string createSignature(string &firstname, string &lastname, vector<Person> &persons);
bool unikPerson(string firstname, string lastname, float length, vector<Person> &persons);
void searchPerson(vector<Person> &persons);
void deletePerson(vector<Person> &persons);

//------------------------------------------------------------------------------
// Manage list
//------------------------------------------------------------------------------
void showList(vector<Person> &persons);
void getPersons(int nStart, int nCount, vector<Person> &persons);

//------------------------------------------------------------------------------
// Sorting list
//------------------------------------------------------------------------------
void sort(vector<Person> &persons, Sort type);
bool compare_by_name(const Person& lhs, const Person& rhs);
bool compare_by_signature(const Person& lhs, const Person& rhs);
bool compare_by_length(const Person& lhs, const Person& rhs);
void sortRandom(vector<Person> &persons);



//------------------------------------------------------------------------------
// Save and read to/from file
//------------------------------------------------------------------------------
void saveFile(vector<Person> &persons);
void readFile(vector<Person> &persons);
string crypting(string tempString, int key, string type);

//------------------------------------------------------------------------------
// Other funktions
//------------------------------------------------------------------------------
void pressAnyKey();



#endif