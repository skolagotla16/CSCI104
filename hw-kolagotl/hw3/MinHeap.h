#ifndef MINHEAP_INCLUDED
#define MINHEAP_INCLUDED
#include <random>
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <algorithm>
using namespace std;
  template <class T>

  class MinHeap {
     public:
        MinHeap (int d);
        /* Constructor that builds a d-ary Min Heap
            This should work for any d >= 2,
            but doesn't have to do anything for smaller d.*/

       ~MinHeap ();

        void add (T item, int priority);
            /* adds the item to the heap, with the given priority. */

       const T & peek () const;
         /* returns the element with smallest priority.  
			Break ties however you wish.  
			Throws an exception if the heap is empty. */

        void remove ();
         /* removes the element with smallest priority.
			Break ties however you wish.
            Throws an exception if the heap is empty. */

        bool isEmpty ();
         /* returns true iff there are no elements on the heap. */

        void trickleDown(int pos);

        void bubbleUp(int pos);

    private:
        
        int d_temp = 0;
        int cnt_items = 0; 
        std::vector<std::pair<T,int>> cryVec; 
        // because this assignment made me want to cry
      // whatever you need to naturally store things.
      // You may also add helper functions here.
  };

template <class T>
MinHeap<T>::MinHeap(int d){
    cnt_items = 0;
    d_temp = d;
    
}

template <class T>
MinHeap<T>::~MinHeap(){}

template <class T>
void MinHeap<T>::add(T item, int priority){

    std::pair<T,int> newPair = std::make_pair( item, priority );
    cryVec.push_back(newPair);
    cnt_items++;
    int h_size = cryVec.size();
    bubbleUp(h_size - 1);
    
}

template <class T>
const T & MinHeap<T>::peek() const{
    if (cnt_items == 0){
        throw(std::logic_error("The heap is empty"));
    }

    return cryVec[0].first;
}

template <class T>
void MinHeap<T>::remove(){
     if (isEmpty()){
        throw(std::logic_error("Empty Heap"));
    }

    cnt_items = cnt_items - 1;
    cryVec[0] = cryVec.back();
    cryVec.pop_back();
    trickleDown(0);

}

template <class T>
bool MinHeap<T>::isEmpty(){
    if (cnt_items != 0){
        return false;
    }

    return true;
} 

template <class T>
void MinHeap<T>::bubbleUp(int pos){
    int child = (pos-1)/d_temp;
    if (pos > 0 && (cryVec[pos].second < cryVec[child].second)){
        std::swap(cryVec[pos], cryVec[child]);
        bubbleUp(child);
    }
    else if(pos > 0 && (cryVec[pos].second == cryVec[child].second)){
        if(cryVec[pos].first < cryVec[child].first){
            std::swap(cryVec[pos], cryVec[child]);
            bubbleUp(child);
        }
    }
}

template <class T>
void MinHeap<T>::trickleDown(int pos){
    int child = d_temp * pos + 1;

    if (child >= (int)(cryVec.size())){
        return;
    }

    int i = 1;
    int l_child = child;

    while (i < d_temp){
        if (child + i < (int)(cryVec.size())){
            int r_child;
            r_child = child + i;
            if (cryVec[r_child].second < cryVec[l_child].second){
                l_child = r_child;
            }
        }
        i++;
    }

    if (cryVec[pos].second == cryVec[l_child].second){
        std::swap(cryVec[pos], cryVec[l_child]);
        trickleDown(l_child);
    }

    else if (cryVec[pos].second > cryVec[l_child].second){
        std::swap(cryVec[pos], cryVec[l_child]);
        trickleDown(l_child);
    }

}

#endif