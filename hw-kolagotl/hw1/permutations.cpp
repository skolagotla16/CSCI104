
#include <string> 
#include <iostream>
using namespace std;

void change(string in, int s_index, int e_index);
void change(string in, int s_index, int e_index){
    
    if (s_index == e_index - 1)
    {
        cout << in << endl;
        return;
    }
 
    for (int i = s_index; i < e_index; i++)
    { 
        swap(in[s_index], in[i]);       
        change(in, s_index + 1, e_index);
        swap(in[s_index], in[i]);
    }
}
 
void permutations(string in){

    change(in, 0, in.size());

}

