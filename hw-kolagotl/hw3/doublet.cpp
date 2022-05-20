#include "MinHeap.h"
#include <random>
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <algorithm>
using namespace std;

void Asearch(int& expansions, int& steps, set<string>& wordList, string start, string end){
    MinHeap<string> minheap(2);
    map<string, int> distance;
    int solution = 0; 
    gDist[start] = 0;
    minHeap.add(start, 0);
    int g = 0;
    bool loop = true;
    while(loop){
        string current = minheap.peek();
        minheap.remove();
        expansions++;
        g = distance[current];

        for(int i = 0; i < current.length(); i++){
            string temp = current; 
            for (int j = 97; j < 123){
                temp[i] = char(j);
                if (wordList.find(temp) != )
            }
        }
    }

}
int main(int argc, char* argv[]){
    int numWords = 0; 

    string firstWord = argv[1];
    string endWord = argv[2];
    string ifstream in_file(argv[3]);
    set<string> words
    in_file >> numWords;
    int i = 0;
    
    while (i < numWords){
        string word;
        in_file >> word;
        string lowerWord = toLower(word);
        words.insert(lowerWord);
    }

    first = toLower(firstWord);
    end = toLower(endWord);

    int steps = 0;
    int expansions = 0;

    Asearch(expansions, steps, words, first, end);
    cout << steps << endl;
    cout << expansions << endl;
    return 0;


    


}