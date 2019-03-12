#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
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

int main()
{
  vector<Person> employees;
  vector<string> companyNames;

  readData(employees);
  getCompanies(employees, companyNames);
  printHighestPaid(employees);
  separateAndSave(employees, companyNames);

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

void getCompanies(vector<Person> &employees, vector<string> &compNames)
{
  int lCounter = 0, vCounter = 0, nCounter = 0, size = employees.size();
  string name;

  do
  {
    name = employees.at(vCounter).getCompanyName();
    lCounter++;

    // This block only executes if companyNames vector is empty.
    if(compNames.size() == 0)
    {
      compNames.push_back(name);
      vCounter++;
    }
    // ==========================================================
    else if(compNames.size() != 0)
    {
      for(int i = 0; i < compNames.size(); i++)
      {
        if(compNames.at(i) == name)
        {
          nCounter++;
        }
      }
      if(nCounter == 0)
      {
        compNames.push_back(name);
        vCounter++;
        nCounter = 0;
      }
      else
      {
        nCounter = 0;
        vCounter++;
      }
    }
  } while(lCounter < size);
}

void printHighestPaid(vector<Person> &employees)
{
  float highest, temp1, temp2;
  float tPay;
  string name;
  vector<float> pay;

  // Stores the total pay into the vector pay.
  for(int i = 0; i < employees.size(); i++)
  {
    tPay = employees.at(i).totalPay();
    pay.push_back(tPay);
  }

  // Finds the highest total pay.
  for(int i = 1; i < pay.size(); i++)
  {
    temp1 = pay.at(i);
    temp2 = pay.at(i - 1);

    if(temp1 > temp2)
    {
      if(highest > temp1)
      {
        highest = highest;
      }
      else
      {
        highest = temp1;
      }
    }
    if(temp2 > temp1)
    {
      if(highest > temp2)
      {
        highest = highest;
      }
      else
      {
        highest = temp2;
      }
    }
  }

  // Uses the value in the highest variable and compares to employees vector to
  // find the richest employee.
  for(int i = 0; i < employees.size(); i++)
  {
    if(highest == employees.at(i).totalPay())
    {
      name = employees.at(i).fullName();
      cout << "Highest paid: " << name << endl;
      cout << "Employee ID: " << employees.at(i).getEmployeeId() << endl;
      cout << "Employer: " << employees.at(i).getCompanyName() << endl;
      cout << "Total Pay: $" << fixed << setprecision(2) << highest << endl;
    }
  }
}

void separateAndSave(vector<Person> &employees, vector<string> &compNames)
{
  string name, coName, tempCoName;
  int coID, vCounter = 0, lCounter = 0;
  float pay, total = 0.0;
  ofstream writeData;

  for(int i = 0; i < compNames.size(); i++)
  {
    tempCoName = compNames.at(i);
    writeData.open(tempCoName + ".txt");

    for(int j = 0; j < employees.size(); j++)
    {
      name = employees.at(j).fullName();
      coID = employees.at(j).getEmployeeId();
      coName = employees.at(j).getCompanyName();
      pay = employees.at(j).totalPay();

      if(tempCoName == coName)
      {
        total += pay;
        writeData << left << setw(20) << name;
        writeData << right << setw(3) << coID;
        writeData << right << setw(12) << coName;
        writeData << right << setw(5) << "$" << fixed << setprecision(2) << pay;
        writeData << endl;
      }
    }
    writeData << "Total $" << fixed << setprecision(2) << total;
    total = 0.0;
    writeData.close();
  }
}
