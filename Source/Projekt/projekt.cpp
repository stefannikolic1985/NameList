//------------------------------------------------------------------------------
// Projektuppgift
// DT018G_stni1401_Projekt
// Stefan Nikolic 2017-06-01
//------------------------------------------------------------------------------
#include "main.h"
//------------------------------------------------------------------------------
// Huvudprogram
//------------------------------------------------------------------------------
int main()
{
	bool again = true;
	vector<string> menuText;
	vector<Person> persons;

	getMenuText(menuText); // Show menu 
	
	do
	{
		int input = showMenu(menuText, persons);
	
		switch (input)
		{
		case 1: addPerson(persons); break;
		case 2: showList(persons); break;
		case 3: searchPerson(persons); break;
		case 4: deletePerson(persons); break;
		case 5: sort(persons, Sort::name); break;
		case 6: sort(persons, Sort::signature); break;
		case 7: sort(persons, Sort::length); break;
		case 8: sortRandom(persons); break;
		case 9: saveFile(persons); break;
		case 10: readFile(persons); break;
		case 11: again = false;
		}
	} while (again);
	return 0;
}



