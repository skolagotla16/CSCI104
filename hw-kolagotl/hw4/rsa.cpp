#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

//Calculates the log part of x
long calculateX(long n){
 
    long a = log(n/27);
    long b = log(100);
    return ((long)(a/b) + 1);

}

//Converts n into a binary string
string binary(long n) {
  string after = "";
  while(n > 0) {
    long m = n%2;
    after += to_string(m); 
    n /= 2;
  }
  reverse(after.begin(), after.end());
  return after;
}

//Taken from class instructions to perform modular exponentiation
long modularExponentiation(long m, string e, long n){

    long power;
    string itter = e;
    power = m%n;
    long b = 1;
    int binary; 
    int size = itter.size();
    for (long i = 0; i < size; i++){
        binary = itter[i] - '0';
        if (binary == 1){
            b = (b*power) % n;
        }

        power = power * power % n;
    }
    return b;
}

//Prints out user instructions

void encrypt(string filename, long n, string message) {

  if(n < 27) {
    cout << "n is too small!" << endl;
    return;
  }

  long e;
  e = 65537;
  string binary_e = binary(e);
  long x = calculateX(n);

  ofstream file(filename); 
  bool check = true;
  int cnt = 0;

  while(check) {
    //String used to store value of m as it is built
    string M = "";

    //Encrypts x length times
    for(long i = 0; i < x; i++) {
      if (cnt*x + i == message.size() - 1){
        check = false; 
      }      
      //Fill end with 0's
      if(i > message.size() - 1) {
        M += "00";
      }
      else {
        //Change ascii value to 0-26
        int change = (int)message[cnt*x + i] - 96;

        //Set space to 00
        if(message[cnt*x + i] == ' ') {
          M  += "00";
        }
        //Fill single digit 10's place with 0's
        else if(change < 10) {
          M += "0" + to_string(change);
        }
        else {
          M += to_string(change);
        }
      }
    }
  
    long m = stol(M);
    long c = modularExponentiation(m, binary_e, n);
    //Write number to file
    file << c << " ";
    cnt++;
  }
}

long calculateD(long e, long L) {
  long t = 1;
  long old_t = 0;
  long r = e;
  long old_r = L;
  long quotient;
  long temp;

  while(r != 0){
    quotient = old_r/r;
    temp = r; 
    r = old_r - quotient * r;
    old_r = temp;
    temp = t;
    t = old_t - quotient * t;
    old_t = temp;

    if (old_t < 0){
      while (old_t < 0){
        old_t += (e-1)*(L-1);
      }
    }

  }

  return old_t;
}

long calculateL(long p, long q){
  long t = 1;
  long old_t = 0;
  long r = p;
  long old_r = q;
  long quotient;
  long temp;
  long L;

  while( r != 0){
    quotient = old_r/r;
    temp = r; 
    r = old_r - quotient * r;
    old_r = temp;
    temp = t;
    t = old_t - quotient * t;
    old_t = temp;
  }

  return old_r;
}

void decrypt(string input, string output, long d, long n) {
  

}

int main(int argc, char*argv[]) {
  
  long p = stol(argv[1]);
  long q = stol(argv[2]);
  long d = calculateD(p, q);
  while(true) {

    string choice;
    cout << "Enter EXIT, ENCRYPT, DECRYPT: " << endl;
    cin >> choice;

    if(choice != "DECRYPT" && choice != "ENCRYPT" && choice != "EXIT") {
      cout << "Command was not valid, the program is ending." << endl;
      break;
    }
  
    else if(choice == "ENCRYPT") {
      long n;
      string filename, message; 
      filename = "";
      message = "";
      
      cin >> filename >> n;
      getline(cin, message);

      //To get rid of spaces
      message = message.substr(1, message.size() - 1);
      encrypt(filename, n, message);
    }

    else if(choice == "EXIT") {
      break;
    }

    else if(choice == "DECRYPT") {
      string input, output;
      input = "";
      output = "";
      cin >> input >> output;
      long d;
      long n = p*q;
      long L = ((p-1) * (q-1))/calculateL(p-1, q-1);
      
      

      if (L <= 65537){
        cout << "Oof invalid numbers!" << endl;
        break;
      }

      d = calculateD(65537, L);
      decrypt(input, output, d, n);
    }
  }
  return 0;
}