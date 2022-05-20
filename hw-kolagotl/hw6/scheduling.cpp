#include "avlbst.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

// Backtracking and Recursion Method
bool scheduling(AVLTree<int, int>& organizer, int exams, int students, int time, int cur, vector<int> options, vector<vector<int>> classes){
    int issues_arr[time];
    bool issue;
    int temp; 

    // Base Case
    if(cur == exams){
        for(AVLTree<int, int>::iterator it = organizer.begin(); it != organizer.end(); ++it){
            cout << it->first << " " << it->second + 1 << endl;
        }
        return true;
    }
    
    int i = 0;
    while(i < time){
    issue = false;

        //Insert it into the AVL tree
        organizer.insert(make_pair(options[cur], i));
        //Look through each student
        int j = 0;
        while(j < students){
            int k = 0;
            while (k < students){
            //set arr to zero
            for (int z = 0; z < time; z++){
                issues_arr[z] = 0;
            }
            //Go through student classes
                int m = 0;
                while(m < classes[k].size()){
                    temp = classes[k][m];
                    if(organizer.find(temp) == organizer.end()) {
                        break;
                    }
                    //checks for scheduling conflict
                    else if (organizer.find(temp) != organizer.end()){
                        if(issues_arr[organizer.find(temp)->second] == false) {
                            issues_arr[organizer.find(temp)->second]++;
                        }
                        
                        else {
                            issue = true;
                            break;
                        }
                    }
                    m++;
                }
                k++;
            }
            j++;   
            //checks if there is an issue 
            if(issue == false){
                cur = cur + 1;
                bool check = scheduling(organizer, exams, students, time, cur, options, classes);
                if(check){
                    return true;
                }
            }
            organizer.remove(options[cur]);
        }
        i++;
    }
    return false;
}

int main(int argc, char *argv[]){

    AVLTree<int, int> organizer;
    vector<int> options;
    vector<vector<int>> stu_classes;
    int exams = 0;
    int students = 0;
    int times = 0;
    int i = 0;

    //To ensure that the correct number of arguments were passed
    if(argc < 2) {
        return -1;
    }

    string filename = argv[1];
    ifstream ifile(filename);

    //Makes sure that the file is valid
    if(ifile.fail()) {
        return -1;
    }

    //take in file inputs
    ifile >> exams >> students >> times;

    //now get rid of the first line
    string first_line;
    getline(ifile, first_line);

        while (i < students){
        //store classes
        vector<int> personal;
        string rid;
        getline(ifile, rid);
        istringstream ss(rid);

        //disgard the names
        string name;
        ss >> name;
        int curClass;

        while(ss >> curClass){
            personal.push_back(curClass);

            //add the class
            vector<int>::iterator it = find(options.begin(), options.end(), curClass);
            if(it != options.end()){}
            else {
                options.push_back(curClass);
            }
        }
        stu_classes.push_back(personal);
        i++;
    }

    bool answer = scheduling(organizer, exams, students, times, 0, options, stu_classes);
    if(answer){
        return 0;
    }
    else {
        cout << "No valid solution" << endl;
    }
    return 0;
}