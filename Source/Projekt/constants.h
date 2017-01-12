//------------------------------------------------------------------------------
// Projektuppgift
// DT018G_stni1401_Projekt
// Stefan Nikolic 2017-06-01
//------------------------------------------------------------------------------
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
using std::string;
//------------------------------------------------------------------------------
// Definiera en struktur
//------------------------------------------------------------------------------
struct Person
{
	string firstName;
	string lastName;
	string signature;
	float length;
};

enum Sort { 
	name, 
	signature, 
	length };

//------------------------------------------------------------------------------
// Constant
//------------------------------------------------------------------------------
static const char delim = '|';
static const int numPersonsPerPage = 20; // how many persons will shows per "page"
static const int signatureSize = 3;  // how many characters from firstname/lastname will create signature (without number)

#endif