//------------------------------------------------------------------------------
// Projektuppgift
// DT018G_stni1401_Projekt
// Stefan Nikolic 2017-06-01
//------------------------------------------------------------------------------
#include "main.h"
//------------------------------------------------------------------------------
//               ********** Funktionsdefinitioner **********
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// MENU
//------------------------------------------------------------------------------

// Show menu 
int showMenu(vector<string> &texts, vector<Person> &persons) {
	int input;
	bool inputCheck;

	cout << endl << endl << " ***** MENY *****" << endl << endl;

	// Get menu alternatives 
	for (string text : texts) {
		cout << text << endl;
	}

	cout << endl << " Total number of persons in list " << persons.size() << endl;

	do {
		cout << endl << " Choose an option: ";

		// if input is invalid
		if (!(cin >> input) || input < 1 || input > 11)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			inputCheck = false;

		}

		else
		{
			inputCheck = true;
		}
	} while (!inputCheck);



	return input;
}

// Get text for the menu
void getMenuText(vector<string> &texts)
{

	texts.push_back(" 1. Add person");
	texts.push_back(" 2. Show all persons");
	texts.push_back(" 3. Search person in list");
	texts.push_back(" 4. Delete person from list");
	texts.push_back(" 5. Sort by name");
	texts.push_back(" 6. Sort by signature");
	texts.push_back(" 7. Sort by length");
	texts.push_back(" 8. Random order");
	texts.push_back(" 9. Save list to a textfile");
	texts.push_back(" 10. Load list to a textfile");
	texts.push_back(" 11. Close");
}


//------------------------------------------------------------------------------
// MANAGE PERSON
//------------------------------------------------------------------------------

// Add new person to the list
void addPerson(vector<Person> &persons) {

	bool again = true;

	do
	{

		Person person;
		int myInput;
		string firstname,
			lastname;
		float length;

		cout << endl << " ***Add a person***" << endl;

		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ensure that all 3 cin appears without over jumping  

		// Add firstname
		while (true) {

			cout << endl << " Enter firstname: ";
			getline(cin, firstname);

			// if input contains non alphanumeric characters bool is true
			bool firstname_contains_non_alpha
				= !regex_match(firstname, regex(R"(^[A-Za-z\s]+$)")); // /s is for matching whitespace

																	  // if input contains non alphanumeric
			if (firstname_contains_non_alpha)
				cout << " - Name must contain just alphabet letters a-z" << endl;

			// if input is less than 1 letter 
			else if (firstname.size() < 2)
				cout << " - It must be more than 1 letter in firstname." << endl;

			// if first character in input is whitespace
			else if (firstname[0] == ' ')
				cout << " - First letter can not be a empty space." << endl;

			else {
				break;
			}

		}

		// Add lastname
		while (true) {

			cout << " Enter lastname: ";
			getline(cin, lastname);


			// if input contains non alphanumeric characters bool is true
			bool lastname_contains_non_alpha
				= !regex_match(lastname, regex(R"(^[A-Za-z\s]+$)"));

			// if input contains non alphanumeric
			if (lastname_contains_non_alpha)
				cout << " - Name must contain just alphabet letters a-z" << endl;

			// if input is less than 1 letter 
			else if (lastname.size() < 2)
				cout << " - It must be more than 1 letter in firstname." << endl;

			// if first character in input is whitespace
			else if (lastname[0] == ' ')
				cout << " - First letter can not be a empty space." << endl;

			else {
				break;
			}

		}

		// Add length
		cout << " Enter length: ";
		cin >> length;

		while (cin.fail()) {
			cout << " Letters is not allowed. Enter en integer: ";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> length;
		}



		// if person is not unik
		if (unikPerson(firstname, lastname, length, persons)) {
			cout << endl << " It is duplicate!" << endl;
			cout << " 1. Change name" << endl;
			cout << " 2. Cancel adding" << endl;
			cout << endl << " Choose the one alternative: ";
			cin >> myInput;

			// error controll  
			while (cin.fail() || myInput != 1 && myInput != 2) {
				cout << " Choose the one alternative: ";
				cin.clear();
				cin.ignore(256, '\n');
				cin >> myInput;
			}

			if (myInput == 2)
				again = false;

		}

		// if new person is unik
		else
		{
			person.firstName = firstname;
			person.lastName = lastname;
			person.length = length;

			person.signature = createSignature(firstname, lastname, persons);

			persons.push_back(person); // add new person to the vector 

									   // show new person
			cout << endl << left << setw(20) << "Sign";
			cout << left << setw(30) << "Name";
			cout << setw(7) << "Length [m]" << endl;


			cout << fixed;                     // show with a fixed decimal point - not scientific notation
			cout << setprecision(2);          // show only 2 digits after the decimal point
			cout << left << setw(20) << person.signature;
			cout << left << setw(30) << person.firstName + " " + person.lastName;
			cout << right << setw(7) << person.length << endl;

			cout << endl << " New person added!" << endl;
			pressAnyKey();
			again = false;
		}
	} while (again);

}

// Create a signature for new person
string createSignature(string &firstname, string &lastname, vector<Person> &persons) {


	string signature,
		existingSignature;

	// signature firstname (create first 3 letters)
	for (int i = 0; i < signatureSize; i++) {
		if (firstname[i] == ' ')
			signature += 'x';

		else if (firstname[i] == NULL || firstname[i] == '\0') {
			for (int x = 0; x < (signatureSize - i); x++) {
				signature += 'x';
			}
			break;
		}

		else
			signature += tolower(firstname[i]);

	}

	// signature lastname (create second 3 letters)
	for (int i = 0; i < signatureSize; i++) {

		if (lastname[i] == ' ')
			signature += 'x';

		else if (lastname[i] == NULL || lastname[i] == '\0') {
			for (int x = 0; x < (signatureSize - i); x++) {
				signature += 'x';
			}
			break;
		}

		else
			signature += tolower(lastname[i]);
	}

	// check if there is peroson with same siganture (without last 2 numbers) in the list
	int counter = 1;
	int lastSignNum = 0,
		currentSignNum;

	// getting last number for person with same signature (without last number)
	for (auto e : persons)
	{
		existingSignature = e.signature.substr(0, (signatureSize * 2)); //first + lastname xxxyyy
		currentSignNum = stof(e.signature.substr((signatureSize * 2), signatureSize)); //number zz 

																					   //if new signature is same as signature from the list
		if (existingSignature == signature)
			lastSignNum = currentSignNum;
	}

	//create signature by lastnumber + 1 if lastnumber is 0-8
	if (lastSignNum < 9) {
		signature += "0" + to_string(lastSignNum + 1);
	}

	//create signature by lastnumber + 1 if lastnumber bigger than 8
	else
	{
		signature += to_string(lastSignNum + 1);
	}

	return signature;
}

// Check if new person is unik
bool unikPerson(string firstname, string lastname, float length, vector<Person> &persons) {

	string firstnameTemp = firstname,
		lastnameTemp = lastname;
	vector<Person> personsTemp = persons;
	bool unik = false;

	// transform new firstname and lastname to lower
	transform(firstnameTemp.begin(), firstnameTemp.end(), firstnameTemp.begin(), tolower);
	transform(lastnameTemp.begin(), lastnameTemp.end(), lastnameTemp.begin(), tolower);


	for (auto e : personsTemp)
	{
		// transform current firstname and lastname from the list to lower
		transform(e.firstName.begin(), e.firstName.end(), e.firstName.begin(), tolower);
		transform(e.lastName.begin(), e.lastName.end(), e.lastName.begin(), tolower);

		// if firstname and last name for current person from the list is same as firstname and lastname for new person
		if (e.firstName == firstnameTemp && e.lastName == lastnameTemp && e.length == length) {
			unik = true;
			break;

		}
	}
	return unik;
}

// Search person in the list 
void searchPerson(vector<Person> &persons) {
	string signature;
	bool hit = false;

	cout << endl << " ***SEARCH PERSON***" << endl << endl;
	cout << " Enter signature for person you want to search: ";
	cin >> signature;

	for (auto e : persons)
	{
		if (e.signature == signature) {
			cout << endl << " Person found!" << endl << endl;
			cout << left << setw(20) << "Sign";
			cout << left << setw(40) << "Name";
			cout << setw(7) << "Length [m]" << endl;

			cout << fixed;                     // show with a fixed decimal point - not scientific notation
			cout << setprecision(2);          // show only 2 digits after the decimal point
			cout << left << setw(20) << e.signature;
			cout << left << setw(40) << e.firstName + " " + e.lastName;
			cout << right << setw(7) << e.length << endl;
			hit = true;
			break;
		}
	}

	if (hit == false) {
		cout << endl << " Person not found" << endl;
	}

	pressAnyKey();
}

// Delete person from the list 
void deletePerson(vector<Person> &persons) {

	string signature;
	bool hit = false;

	cout << endl << " ***DELETE PERSON***" << endl << endl;
	cout << " Enter signature for person you want to delete: ";
	cin >> signature;

	for (int i = 0; i < persons.size(); i++)
	{
		if (persons[i].signature == signature) {
			cout << endl << "Person " << persons[i].firstName + " " + persons[i].lastName << " Signature: " << persons[i].signature << " is deleted!" << endl << endl;
			persons.erase(persons.begin() + i);
			hit = true;
			break;
		}
	}

	if (hit == false) {
		cout << endl << " Person not found" << endl;
	}

	pressAnyKey();
}

//------------------------------------------------------------------------------
// MANAGE LIST
//------------------------------------------------------------------------------

// Show list with 20 personer per side 
void showList(vector<Person> &persons) {

	int startIndex = 0;
	cout << endl << endl << " ***NAME LIST***" << endl;

	// if list is empty
	if (persons.size() == 0) {
		cout << " The list is empty" << endl;
		pressAnyKey();
	}

	else
	{
		while (startIndex < 100)
		{
			// show 20 persons per page
			if (startIndex < persons.size()) {
				getPersons(startIndex, numPersonsPerPage, persons); // get 20 persons
				startIndex += numPersonsPerPage;   // + startIndex with 20 
				pressAnyKey();
			}

			else
			{
				break;
			}
		}
	}

}

// Get persons 
void getPersons(int nStart, int nCount, vector<Person> &persons)
{

	cout << left << setw(4) << "Nr.";
	cout << left << setw(20) << "Sign";
	cout << left << setw(30) << "Name";
	cout << setw(7) << "Length [m]" << endl;

	for (int i = nStart; i < (nStart + nCount); i++)
	{
		if (i <= (persons.size() - 1)) {
			cout << fixed;                     // show with a fixed decimal point - not scientific notation
			cout << setprecision(2);          // show only 2 digits after the decimal point
			cout << left << setw(4) << i + 1;
			cout << left << setw(20) << persons[i].signature;
			cout << left << setw(30) << persons[i].firstName + " " + persons[i].lastName;
			cout << right << setw(7) << persons[i].length << endl;
		}

	}
}

//------------------------------------------------------------------------------
// SORTING LIST
//------------------------------------------------------------------------------

// Sorting list by lastname/signature/length
void sort(vector<Person> &persons, Sort type) {

	// if list is not empty
	if (persons.size() != 0)
	{
		switch (type)
		{
		case name:
			sort(persons.begin(), persons.end(), compare_by_name); // sorting by lastname
			cout << endl << " Sorting by lastname complate!" << endl;
			break;

		case signature:
			sort(persons.begin(), persons.end(), compare_by_signature); // sorting by signature
			cout << endl << " Sorting by signature complate!" << endl;
			break;

		case length:
			sort(persons.begin(), persons.end(), compare_by_length); // sorting by signature
			cout << endl << " Sorting by length complate!" << endl;
			break;
		}
	}

	else
		cout << endl << " The list is empty!" << endl;

	pressAnyKey();
}

// Compare names for sorting
bool compare_by_name(const Person& leftPerson, const Person& rightPerson) {

	string leftName = leftPerson.lastName + leftPerson.firstName,
		rightName = rightPerson.lastName + rightPerson.firstName;

	// covert both string to lower
	transform(leftName.begin(), leftName.end(), leftName.begin(), tolower);
	transform(rightName.begin(), rightName.end(), rightName.begin(), tolower);


	return leftName < rightName;
}

// Compare signature for sorting
bool compare_by_signature(const Person& leftPerson, const Person& rightPerson) {

	return leftPerson.signature < rightPerson.signature;
}

// Compare length for sorting
bool compare_by_length(const Person& leftPerson, const Person& rightPerson) {

	return leftPerson.length > rightPerson.length;
}

// Sorting list random 
void sortRandom(vector<Person> &persons) {
	if (persons.size() != 0) {
		auto engine = default_random_engine{};
		random_shuffle(begin(persons), end(persons)); // start random shuffle
		cout << " Random sorting complate!" << endl;
	}
	else
		cout << endl << " The list is empty!" << endl;

	pressAnyKey();
}


//------------------------------------------------------------------------------
// SAVE AND READ TO/FROM FILE
//------------------------------------------------------------------------------
// Save list to .txt file
void saveFile(vector<Person> &persons) {

	string fileName = "persons.txt",
		tempFirstname,
		tempLastname,
		tempSignature,
		tempLength,
		delimEncrypted,
		tempString,
		type = "encrypting",
		delimString(1, delim);
	int key;
	ofstream myfile(fileName);

	cout << endl << " Enter key for encryption: ";
	cin >> key;

	delimEncrypted = crypting(delimString, key, type); // encrypting delim

	if (myfile.is_open())
	{

		for (auto e : persons) {
			tempLength = to_string(e.length); // convert double to string
			tempString = e.firstName + delimString + e.lastName + delimString + e.signature + delimString + tempLength;	// create line per person
			myfile << crypting(tempString, key, type) << endl; // add encrypted string to myfile
		}
		cout << " All persons are successfully saved on the file!" << endl;
		myfile.close();
	}


	else {
		cout << " Unable to open file";
	}

	pressAnyKey();
}

// Read list from .txt file
void readFile(vector<Person> &persons) {
	string fileName = "persons.txt";
	string tempString,
		tempLength,
		decryptedTempString,
		type = "decrypting";
	int key;
	ifstream fin(fileName);
	Person person;
	vector<Person> tempPersons;

	if (fin.is_open())
	{
		cout << endl << " Enter key for encryption: ";
		cin >> key;

		while (getline(fin, tempString))
		{
			// decrypting tempString
			decryptedTempString = crypting(tempString, key, type);

			// splits string
			stringstream linestream(decryptedTempString);

			getline(linestream, person.firstName, delim);
			getline(linestream, person.lastName, delim);
			getline(linestream, person.signature, delim);
			linestream >> person.length;

			// add to temp vectore
			tempPersons.push_back(person);
		}

		persons = tempPersons; // update persons
		cout << " The file is loaded!" << endl;
		pressAnyKey();
	}

	else {
		cout << " Unable to open file" << endl;
		pressAnyKey();
	}


}

// Encryption and Decryption
string crypting(string tempString, int key, string type) {

	string encryptedString = tempString;

	for (int i = 0; i < tempString.size(); i++) {

		char c = tempString[i];

		// encrypting
		if (type == "encrypting")
			encryptedString[i] = c + key;

		// decrypting
		else if (type == "decrypting")
			encryptedString[i] = c - key;
	}

	return encryptedString;
}


//------------------------------------------------------------------------------
// OTHER FUNKTIONS
//------------------------------------------------------------------------------
// Press any key to continue dd
void pressAnyKey() {
	cout << endl << " Press any key to put continue..." << endl;
	_getch(); // wait until user enter any key
}




