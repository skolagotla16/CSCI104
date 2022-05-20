#include "company.hpp"
#include <iostream>

// Initializes the tracker with n students and their 1-person companies.
CompanyTracker::CompanyTracker(int n)
{
  numCompanies = n;
  companies = new Company* [numCompanies];
  for (int i = 0; i < numCompanies; ++i)
      companies[i] = new Company ();
}

// Deallocates all dynamically allocated memory.
CompanyTracker::~CompanyTracker()
{
  for (int i = 0; i <= numCompanies; i++){
    while(companies[i] -> parent != nullptr){
      split(i);
    }
    delete companies[i];
  }
}

void CompanyTracker::merge(int i, int j)
{
  //checks if i and j are in bounds
  if (i == j ||i < 0 || j < 0
  || i >= numCompanies || j >= numCompanies 
  || inSameCompany(i, j) == true){
    return;
  }

  else{
    // merges the companies
    Company* newComp = new Company();
    largestCompany(i) -> parent = newComp;
    largestCompany(j) -> parent = newComp; 
    newComp -> merge1 = largestCompany(i);
    newComp -> merge2 = largestCompany(j);
    
  }
}

void CompanyTracker::split(int i)// how i am lost
{
  //checks if i and j are in bounds
  if (i < 0 || i >= numCompanies){ 
    return;
  }
  //checks if i is already merged
  if (companies[i] -> parent == nullptr){
    std::cout << "here" << std::endl;
    return;
  }

  else {
    //splits 
    Company* temp = largestCompany(i);
    temp -> merge1 -> parent = nullptr;
    temp -> merge2 -> parent = nullptr; 
    temp -> merge1 = nullptr;
    temp -> merge2 = nullptr;
    delete temp;
  }
}

bool CompanyTracker::inSameCompany(int i, int j)
{
  //checks if i and j are in bonuds
  if (i < 0 || i >= numCompanies || j < 0 || j >= numCompanies){
    return false;
  }
  //checks if i and j are in the same company
  if (largestCompany(i) == largestCompany(j)){
    return true;
  }

  return false;
}

Company* CompanyTracker::largestCompany(int i){ 
  Company* tempParent = companies[i];
  //keeps going until it finds the nullptr
  while(tempParent -> parent != nullptr){ 
    tempParent = tempParent -> parent;
  }
  return tempParent;
}
