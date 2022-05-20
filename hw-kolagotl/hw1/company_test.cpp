#include "company.hpp"
#include "company.cpp"
#include <cassert>

int main (){
CompanyTracker testCo(6);

//testing to make sure companies are split in the beginning
assert(testCo.inSameCompany(1, 2) == false);
assert(testCo.inSameCompany(4, 5) == false);

//testing the merge function

//test for -1 data
testCo.merge(-1, 5);
assert(testCo.inSameCompany(-1, 5) == false);

// tests for out of bounds data
testCo.merge(3, 9);
assert(testCo.inSameCompany(3, 9) == false);

//test for same data
testCo.merge(5, 5);
assert(testCo.inSameCompany(5, 5) == true);

//test for different data
testCo.merge(4, 5); 
assert(testCo.inSameCompany(4, 5) == true);

//test for different data
testCo.merge(3, 1);
assert(testCo.inSameCompany(3, 1) == true);

//testing inSameCompany
assert(testCo.inSameCompany(-1, 5) == false);
assert(testCo.inSameCompany(-1, 8) == false);

//testing the split function
testCo.split(-1);
testCo.split(3);
assert(testCo.inSameCompany(3, 1) == false);
assert(testCo.inSameCompany(3, 5) == true);


}