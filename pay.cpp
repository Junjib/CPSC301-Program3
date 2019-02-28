#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include "person.h"
#include "person.cpp"

using namespace std;

// Reads the data from the text file and stores the data into the employees
// vector.
void readData(vector<Person> &employees);

// Retrieves the company names from the employees vector and stores it into the
// companyNames vector. Duplicates should not be included in the companyNames
// vector.
void getCompanies(vector<Person> &employees, vector<string> &compNames);

// Finds and outputs the information of the employee with the highest pay.
void printHighestPaid(vector<Person> &employees);

// Separates and writes the employees to a unique text file based on the
// company that they work at. For example all the employees that work at
// Boeing will be written to a text file called Boeing.txt.
void separateAndSave(vector<Person> &employees, vector<string> &compNames);

// Will display the contents in the vector. THIS IS ONLY FOR TESTING PURPOSES.
void displayVector(vector<Person> &employees);

int main()
{
  vector<Person> employees;
  vector<string> companyNames;

  readData(employees);
  //displayVector(employees);

  return 0;
}

void readData(vector<Person> &employees)
{
  ifstream readFile;
  string file = "input.txt", firstName, lastName, coName;
  int coID;
  float hours, rate;
  Person object;

  readFile.open(file);
  if(readFile.fail())
  {
    cout << "Error, file failed to open.\n";
  }

  while(readFile >> firstName)
  {
    readFile >> lastName;
    readFile >> coID;
    readFile >> coName;
    readFile >> hours;
    readFile >> rate;
    object.setFirstName(firstName);
    object.setLastName(lastName);
    object.setEmployeeId(coID);
    object.setCompanyName(coName);
    object.setHoursWorked(hours);
    object.setPayRate(rate);
    employees.push_back(object);
  }

  readFile.close();
}

// =======================================================================
// FOR TESTING PURPOSES. REMOVE WHEN PROGRAM IS READY TO TURN IN.
void displayVector(vector<Person> &employees)
{
  int size = employees.size(), coID;
  string firstName, lastName, coName;
  float hours, rate;

  for(int i = 0; i < size; i++)
  {
    firstName = employees.at(i).getFirstName();
    lastName = employees.at(i).getLastName();
    coID = employees.at(i).getEmployeeId();
    coName = employees.at(i).getCompanyName();
    hours = employees.at(i).getHoursWorked();
    rate = employees.at(i).getPayRate();
    cout << firstName << " " << lastName << " " << coID << " " << coName;
    cout << " " << hours << " " << rate << endl;
  }
}
// =======================================================================

void getCompanies(vector<Person> &employees, vector<string> &compNames)
{
  int counter = 0, size = employees.size();
  string name;

  do
  {
    name = employees.at(counter).getCompanyName();
    counter++;

    for(int i = 0; i < counter; i++)
    {
    }
  } while(counter <= size);
}
