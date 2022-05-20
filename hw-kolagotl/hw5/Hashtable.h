#ifndef HASHTABLE_INCLUDED
#define HASHTABLE_INCLUDED
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

template <typename T>
class Hashtable {
  public:
    Hashtable(bool debug = false, unsigned int size = 11);
    ~Hashtable();
    int hash(string k) const;
    const T& lookup(string k);
    int add(string k, const T& val);
    void reportAll(ostream& outputStream) const;

private:
    //int hash(string k) const;  
    void resize();
    string k;
    unsigned int size;
    bool debug;
    int numItems;
    std::pair<string, T>** item; 
    int r[5];
    int primeNumberIndex; 

};

template <typename T>
Hashtable<T>::Hashtable(bool debug, unsigned int size) {
    this->k = k; 
    this->size = size; 
    this->debug = debug;
    this-> item = new std::pair<string, T>*[size](); 

    int primeNums[17] = {11, 23, 47, 97, 197, 397, 797, 1597, 
        3203, 6421, 12853, 25717, 51437, 102877, 
        205759, 411527, 823117};

    primeNumberIndex = 0;
    primeNumberIndex = primeNums[primeNumberIndex];

    //sets rand value for r1, r2, r3, r4, r5
    if(debug == false) {
        int m = size - 1;
        r[0] = rand() % m; r[1] = rand() % m; r[2] = rand() % m; r[3] = rand() % m; r[4] = rand() % m;
    }
    //sets values for r1, r2, r3, r4, r5
    else if (debug == true) {
        r[0] = 983132572; r[1] = 1468777056; r[2] = 552714139; r[3] = 984953261; r[4] = 261934300;
    }
}

template <typename T>
Hashtable<T>::~Hashtable() {
  for(int i = 0; i < size; i++) {
    if(item[i] != nullptr) {
      delete item[i];
    }
  }
  delete[] item;
}

template <typename T>
int Hashtable<T>::hash(std::string k) const{

    long long wordPieces[5] = {0}; // to hold the string fragments 
    
    long long initialNums = 0; // added up a1's
    long long temp;
    string cutString = "";
    int letterToNum = 0;
    int stringSize = k.size();
    int itCnt = (stringSize/6) + 1; // how many fragments there are going to be

    if (stringSize % 6 == 0){
      itCnt--;
    }

    if (stringSize == 1){
      itCnt = 1;
    }

    for (int j = 1; j <= itCnt; j++){
        string finalMessage = "";
        //cutting the original string into chunks of six

        //starting from the end for strings greater than size 6
        if (stringSize >= 6){
            cutString = k.substr((stringSize - 6)); 
            k = k.substr(0, stringSize - 6);
            stringSize = k.size();
        }

        // if the string smaller than 6
        else if(stringSize < 6){
            cutString = k;
        }

        string sixString = "";

        //iterating through each fragment
        for(int i = 0; i < 6; i++) {
            if(i > cutString.size() - 1) {
                break;
            }
            else{ 
                letterToNum = (int)cutString[i] - 96;
                if ( letterToNum >= 10){
                    sixString += to_string(letterToNum);
                }
                else if (letterToNum < 10){
                    sixString += "0" + to_string(letterToNum);
                }
                   
            }
        }

        finalMessage += sixString;
        //adding zeros to the front if some where missing
        if (finalMessage.size() < 12){
            int cnt = 12 - finalMessage.size();

            for (int i = 0; i < cnt; i++){
                 finalMessage = "0" + finalMessage;
            }
        }

        // calculates the 27^5 + 27^4 + 27^3 ect
        for (int k = 5; k >= 0; k--){
           temp = stol(finalMessage.substr(0, 2));
           initialNums += pow(27, k) * temp;
           finalMessage = finalMessage.substr(2);
        }

        // adds nums to the arr
        wordPieces[5-j] = initialNums;
        initialNums = 0;

        if (j == itCnt){
          break;
        }
    }

    long long numtemp = r[0]*wordPieces[0] + r[1]*wordPieces[1] + r[2]*wordPieces[2] + r[3]*wordPieces[3] + r[4]*wordPieces[4];
    numtemp = numtemp % size;
    return numtemp;
}

template <typename T>
int Hashtable<T>::add(string k, const T& val) {

    int probe = 0;
    int probeFinal = 0;
    double loadFactor = double(numItems)/(double)size;

    // resize if the load factor is > 0.5
    if (loadFactor > 0.5){
        resize();
    }

    int hashValue = 0;
    hashValue = hash(k);

    for (int i = 1; i <= size; i++){

        // if item does not exist add it and break;
        if(item[hashValue] == nullptr) {
        numItems++;
                item[hashValue] = new pair<string,T> (k,val);
                break;
        }

        // break if item exists
        else if(item[hashValue]->first == k){
                break;
        }

        // quadratic probing
        else {
        hashValue += (pow(i,2));
        hashValue = hashValue % size;
        }
        probe++;
    }

    probeFinal = probe - 1;

    return probeFinal; 

}

template <typename T>
void Hashtable<T>::resize(){

    int primeNums[17] = {11, 23, 47, 97, 197, 397, 797, 1597, 
      3203, 6421, 12853, 25717, 51437, 102877, 
      205759, 411527, 823117};

    vector<string> words; 
    vector<T> nums; 

    primeNumberIndex++; 
	 
	int storeSize = size; 
	size = primeNums[primeNumberIndex]; 
	
	numItems = 0; 
	item = new pair<string, T>*[primeNums[primeNumberIndex]]; 

	for (int i = 0; i < storeSize; i++) {
		if (item[i] != NULL) {
			words.push_back(item[i]->first); 
			nums.push_back(item[i]->second); 
			numItems++; 
    }
	}

	for (int i = 0; i < size; i++) {
		item[i] = NULL; 
	}

	for (unsigned int i = 0; i < words.size(); i++) {
		add(words[i], nums[i]);  
	}

}

template <typename T>
const T& Hashtable<T>::lookup(std::string k) {
    int i = 0;
    int hashValue = hash(k);
    // for loop bc while loop would never end
    for (int idx = 0; idx < size; idx++){
        if(item[hashValue] -> first == k){
            return item[hashValue]->second;
        }
        i++;
        hashValue = hashValue + (int)pow(i, 2) % size;
    }
}

template <typename T>
void Hashtable<T>::reportAll(ostream& outputStream) const {
    for (int i = 0; i < size; i++){
        if (item[i] != NULL){
        outputStream << item[i] -> first << " " << item[i]->second << endl;
        }
    }
}

#endif