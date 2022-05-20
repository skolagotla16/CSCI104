#include "Hashtable.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

double bdayParadox();
void probeRate();

int main(int argc, char const *argv[]) {
  /* code */
  srand(time(0));
  double totalPercent = 0;
  Hashtable<int> myHash(true);
  cout << myHash.hash("a") << endl;

  probeRate();
  for(int idx = 0; idx < 10; idx++) {
    double percent = bdayParadox();
    cout << "Trial " << idx << ": " << percent << endl;
    totalPercent += bdayParadox();
  }
  cout << "Average: " << totalPercent/10.0 << endl;
  return 0;
}

double bdayParadox() {
  string CHARACTERS = "abcdefghijklmnopqrstuvwxyz";
  double lower = 0;

  for(int idx = 0; idx < 10000; idx++) {
    set<string> availableWords;
    Hashtable<int> bday(false, 365);

    int probed = 0;
    int added = 0;

    while(!probed && added < 365/2) {
      string toAdd = "";
      for(int idx = 0; idx < 20; idx++) {
        toAdd += CHARACTERS[rand() % 25];
      }
      if(!availableWords.count(toAdd)) {
        probed = bday.add(toAdd, rand());
        added++;
        availableWords.insert(toAdd);
      }
    }
    if(added <= 23) {
      lower++;
    }
  }
  return lower/1000.0;
}

void probeRate() {
  string CHARACTERS = "abcdefghijklmnopqrstuvwxyz";
  double numElements[] = {400, 1000, 2349, 5000, 10000, 134532};
  for(int idx = 0; idx < 6; idx++) {
    Hashtable<int> elements(false);
    double totalProbes = 0;
    for(int i = 0; i < numElements[idx]; i++) {
      string toAdd = "";
      for(int j = 0; j < 20; j++) {
        toAdd += CHARACTERS[rand() % 25];
      }
      totalProbes += elements.add(toAdd, rand());
    }
    cout << "Probe rate for " << numElements[idx] << " elements: " << totalProbes/numElements[idx] << endl;
  }
}