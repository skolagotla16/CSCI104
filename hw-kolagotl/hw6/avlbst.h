#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight () const; //getHeight, but int version
    void setHeight (int height); //setHeight

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialinodee the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), height_(1)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateLeft (AVLNode<Key, Value> *node);
    void rHelper (AVLNode<Key, Value> *node, AVLNode<Key, Value> *node1, AVLNode<Key, Value> *node2, int count);
    void rotateRight (AVLNode<Key, Value> *node);
    void rotateLeftRight (AVLNode<Key, Value> *node);
    void rotateRightLeft (AVLNode<Key, Value> *node);
    int heightHelper(AVLNode<Key, Value>* node) const;
    AVLNode<Key, Value>* bstRemove(const Key& key);
};


template<typename Key, typename Value>
int AVLTree<Key, Value>::heightHelper(AVLNode<Key, Value>* node) const {
	//returns the height
	if (node == NULL) {
		return 0;
	}
	return node->getHeight();
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
   //Do BST Insert
    Node<Key, Value>* repeat = BinarySearchTree<Key, Value>::internalFind(new_item.first);

    if (this->root_ == NULL){
        AVLNode<Key, Value> *tempNode = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        this -> root_ = tempNode;
        return;
    }

    // checks if the inserted value is a repeat
    else if (repeat != NULL){
        repeat -> setValue(new_item.second);
        return;
    }

    AVLNode<Key, Value>* curr = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
    AVLNode<Key, Value>* curr_parent = (AVLNode<Key, Value>*)this -> root_;

    while (curr != NULL){
        //if the value inserted is greater than the root go right
        if (curr -> getKey() > curr_parent -> getKey()){
            if(curr_parent->getRight() != NULL){
                curr_parent = curr_parent->getRight();
            }

            else{
                Node<Key, Value>* newRoot = new AVLNode<Key, Value>(new_item.first, new_item.second, curr_parent);
                newRoot->setValue(new_item.second);
                curr_parent->setRight(newRoot);
                curr = NULL;
            }   
        }

        // if the value being inserted is smaller go left
        else if(curr->getKey() < curr_parent->getKey()){
            if(curr_parent->getLeft() != NULL){
                  
                curr_parent = curr_parent->getLeft();
            }
            else{
                Node<Key, Value>* newRoot = new AVLNode<Key, Value>(new_item.first, new_item.second, curr_parent);
                newRoot->setValue(new_item.second);
                curr_parent->setLeft(newRoot);
                curr = NULL;
            }
        }
    }

    //now fix heights and balance the trees
    AVLNode<Key, Value>* node = (AVLNode<Key, Value>*) BinarySearchTree<Key, Value>::internalFind(new_item.first);
    //Keep going up tree rotating and updating heights
    while(node != NULL) {
      int temp_left = heightHelper(node->getLeft());
      int temp_right = heightHelper(node->getRight());

      //difference in the height of the two trees
      int d = temp_left - temp_right;
      node -> setHeight(1 + std::max(temp_left, temp_right));
      

      if(d > 1 || d < -1) {

        //If the right subtree is longer
        if(temp_left < temp_right) {
          if(new_item.first > node->getRight()->getKey()) {
            rotateLeft(node);
          }

          else if(new_item.first < node->getRight()->getKey()) {
            rotateRightLeft(node);
          }
        }
        //If the left sub tree is longer
        else if(temp_left > temp_right) {
          if(new_item.first < node->getLeft()->getKey()) {
            rotateRight(node);
          }
          else if(new_item.first > node->getLeft()->getKey()) {
            rotateLeftRight(node);
          }
        }
      }
      node = node -> getParent();
    }

}
//This function uses the BST remove and returns the parent node
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::bstRemove(const Key& key) {
    int cnt = 0;
    AVLNode<Key, Value> *curr = (AVLNode<Key, Value>*) BinarySearchTree<Key, Value>::internalFind(key);
    AVLNode<Key, Value> *child; 
    AVLNode<Key, Value> *grandR;                         
    AVLNode<Key, Value> *grandL;
    AVLNode<Key, Value> *tempLeft;
    AVLNode<Key, Value> *tempParent;
    AVLNode<Key, Value> *pred = (AVLNode<Key, Value>*) BinarySearchTree<Key, Value>::predecessor(curr);
    AVLNode<Key, Value> *par = curr->getParent();

    if(curr != this -> root_) {
        cnt = 0;
    }
    else {
        cnt = 1;
    }

    // node doesn't have children
    if(curr->getRight() == NULL && curr->getLeft() == NULL)       
    {
        // if node is the only node, it's a root
        if(curr->getParent() == NULL)
        {
            delete curr;
            this -> root_ = NULL;
            return NULL;
        }

        //right child
        if(curr == curr->getParent()->getRight()){    
            curr->getParent()->setRight(NULL);
        }
        //left child
        else if(curr == curr->getParent()->getLeft()){            
                curr->getParent()->setLeft(NULL);
        } 

    }

    // Node w/ one child
    //move child up
    else if(curr->getRight() == NULL || curr->getLeft() == NULL){
        //right child
        if(curr->getRight() != NULL)                     
        {
            child = curr->getRight();
            grandR = child->getRight();
            grandL = child->getLeft();
        }

        //left child
        else if(curr->getLeft() != NULL)                
        {
            child = curr->getLeft();
            grandR = child->getRight();
            grandL = child->getLeft();
        }

        nodeSwap(curr, child);

        if(curr->getParent() == NULL) {
            this -> root_ = child;
            child->setParent(NULL);
        }

        //fix grand children
        child->setRight(grandR);   
        if(grandR != NULL){
            grandR->setParent(child);
        } 

        child->setLeft(grandL);
        if(grandL != NULL){
            grandL->setParent(child);
        }
    }

    // node with 2 children
    else 
    {    
        nodeSwap(curr, pred);

        // root node
        if(cnt == 1)  {                                
            this -> root_ = pred;
        }
        
        // left child
        if(curr == curr->getParent()->getLeft()) {
            if (curr->getLeft() == NULL && curr->getRight() == NULL) {       
                curr->getParent()->setLeft(NULL);
            }
        }

        // right child
        else if(curr == curr->getParent()->getRight() ){
            if (curr->getLeft() == NULL && curr->getRight() == NULL){   
                curr->getParent()->setRight(NULL);
            }
        }

        //account for grand children
        tempLeft = curr -> getLeft();
        tempParent = curr -> getParent();
        if(curr->getLeft() != NULL)                        
        {
            //left child 
            if(tempParent == pred)             
            {
                pred->setLeft(tempLeft);
                tempLeft->setParent(pred);
            } 
            //right child
            else                             
            {
                tempParent->setRight(tempLeft);
                tempLeft->setParent(tempParent);
            }
        }        
    }

    delete curr;
    if(par == NULL && this->root_ != NULL) {
      return (AVLNode<Key, Value>*)this->root_;
    }
    
    if(this->root_ == NULL) {
      return NULL;
    }
    return par;
}

template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    AVLNode<Key, Value>* y;
    AVLNode<Key, Value>* x;
    if(BinarySearchTree<Key, Value>::internalFind(key) == NULL) {
      return;
    }
    //get parent using bst remove
    AVLNode<Key, Value> *node = bstRemove(key);
    //Removed last element 
    if(node == NULL) {
      return;
    }
    

    while(node != nullptr){
        int t_l = heightHelper(node->getLeft());
        int t_r = heightHelper(node->getRight());
        int dif = t_l - t_r;

        //to find child trees with the largest height
        if(dif > 1 || dif < -1){
            if (t_l > t_r){
                y = node->getLeft();
                if(heightHelper(y->getRight()) > heightHelper(y->getLeft())){
                    x = y->getRight();
                } else { 
                    x = y->getLeft();
                }
            }
            else if(t_r > t_l){
                y = node->getRight();
                if(heightHelper(y->getLeft()) > heightHelper(y->getRight())){
                    x = y->getLeft();
                } else { 
                    x = y->getRight();
                }
            } 

            //rotate once you have the x and y values
            //if the right subtree is longer
            if(heightHelper(node->getLeft()) < heightHelper(node->getRight())){ 
                if(x == y->getRight()){
                    rotateLeft(node);
                }
                else {
                    rotateRight(y);
                    rotateLeft(node);
                }
            } 
            //if the left subtree is longer
            else if (heightHelper(node->getLeft()) > heightHelper(node->getRight())){
                if(x == y->getLeft()){
                    rotateRight(node);
                }
                else{
                    rotateLeft(y);
                    rotateRight(node);
                }
            }
        }
        //keep traversing the tree
        node = node->getParent();
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeftRight(AVLNode<Key, Value> *node){
    //un zig-zag and make zig zig
    rotateLeft(node->getLeft());
    //rotate 
    rotateRight(node);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRightLeft(AVLNode<Key, Value> *node){
    //un zig-zag and make zig zig
    rotateRight(node->getRight());
    //rotate 
    rotateLeft(node);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateLeft (AVLNode<Key, Value> *node)
{

  AVLNode<Key, Value>* erase = node->getRight()->getLeft();
  AVLNode<Key, Value>* par = node->getParent();
  AVLNode<Key, Value>* kid = node->getRight();
  int cnt = 0;

  //acounts for if the node is a root
  if(node == this->root_) {
    this->root_ = kid;
    cnt = 1;
  }

  //begin rotate
  node->setRight(erase);

  if(kid->getLeft() != NULL) {
    erase->setParent(node);
  }

  node->setParent(kid);
  kid->setParent(par);
  kid->setLeft(node);

  if (par != NULL){
    if (par -> getRight() == node){
      par->setRight(kid);
    }
    else if (par->getLeft() == node){
      par->setLeft(kid);
    }
  }

  // fix the heights of all the nodes after the rotate
  rHelper(node, kid, par, cnt);

}

template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateRight (AVLNode<Key, Value> *node)
{
  // same as rotate left but right
  AVLNode<Key, Value>* par = node->getParent(); 
  AVLNode<Key, Value>* kid = node->getLeft();
  AVLNode<Key, Value>* erase = node->getLeft()->getRight();
  int cnt = 0;

  if(node == this->root_) {
    this->root_ = kid;
    cnt = 1;
  }

  node->setLeft(erase);

  if(kid->getRight() != NULL) {
    erase->setParent(node);
  }

  node->setParent(kid);
  kid->setRight(node);
  kid->setParent(par);

  if (par != NULL){
    if (par -> getRight() == node){
      par->setRight(kid);
    }
    else if (par->getLeft() == node){
      par->setLeft(kid);
    }
  }
  // fixes the height after rotate
  rHelper(node, kid, par, cnt);
}

//this helper function fixes the heights after everything is rotated 
template<typename Key, typename Value>
void AVLTree<Key,Value>::rHelper (AVLNode<Key, Value> *node, AVLNode<Key, Value> *kid, AVLNode<Key, Value> *par, int cnt){
  int t_l = heightHelper(node->getLeft());
  int t_r = heightHelper(node->getRight());

  if (t_l > t_r){
    node-> setHeight(1 + t_l);
  }
  else {
    node -> setHeight(1 + t_r);
  }

  int kL = heightHelper(kid->getLeft());
  int kR = heightHelper(kid->getRight());

  if (kL < kR){
    kid->setHeight(1 + kR);
  }
  else{
    kid->setHeight(1 + kL);
  }
  
  //to do if node is the root
  if(cnt == 0) {
    int pL = heightHelper(par->getLeft());
    int pR = heightHelper(par->getRight());
    if (pL > pR){
      par->setHeight(1 + pL);
    }
    else{
      par->setHeight(1 + pR);
    }
  }
  else {
    return;
  }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}


#endif
