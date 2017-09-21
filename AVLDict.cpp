#ifndef _AVLDICT_CPP
#define _AVLDICT_CPP

//AVLDict.cpp
#include "AVLDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>


// An implementation of a dictionary ADT as an AVL tree
//
AVLDict::AVLDict() {
  root = NULL;
  


  // Initialize array of counters for depth statistics
  depth_stats = new int[MAX_STATS]();
}

void AVLDict::destructor_helper(node * x) {
  if (x == NULL) return; // Nothing to destroy.
  destructor_helper(x->left);
  destructor_helper(x->right);
  delete x->key;
  delete x;
}

AVLDict::~AVLDict() {
  // Clean up the tree.
  // This is most easily done recursively.
  destructor_helper(root);

  // It's not good style to put this into a destructor,
  // but it's convenient for this assignment...
  cout << "Depth Statistics for find():\n";
  for (int i=0; i<MAX_STATS-1; i++)
    cout << i << ": " << depth_stats[i] << endl;
  cout << "More: " << depth_stats[MAX_STATS-1] << endl;
  delete [] depth_stats;
}

// 221 Students:  DO NOT CHANGE THIS FUNCTION
// You need to call this function from your find (or from a helper function).
// Pass in the depth in the tree that the find stopped at.
// E.g., you'd call record_stats(0) if the entire dictionary were
// a NULL tree and you did a find on it.
// You'd call record_stats(1) if the entire dictionary were a single
// node, and you did a find on that dictionary, successful or not.
// (Another way to understand this is the number of nodes on the chain
// from the root to the node where the find succeeded,
// or to a leaf if the find didn't succeed.)
void AVLDict::record_stats(int depth) {
  if (depth > MAX_STATS-1) depth = MAX_STATS-1;
  depth_stats[depth]++;
}




bool AVLDict::find(MazeState *key, MazeState *&pred) {
  // TODO:  Write this function!
  int depth = 0;
  string k = key->getUniqId();
  node* temp = root;

  while (temp != NULL) {
    depth++;
    if (k == temp->key->getUniqId()) {
      pred = temp->data;
      record_stats(depth);
      return true;
    }
    else if (k < temp->key->getUniqId()) {
      temp = temp->left;
    }

    else {
      temp = temp->right;
    }
  }
  record_stats(depth);
  return false;
}


bool AVLDict::update_height( node* x ) {
  // TODO:  Write this function!
  if( x == NULL ) return false;
  int m = max(height(x->left), height(x->right)) + 1;
  if( x->height != m ) {
    x->height = m;
    return true;
  }
  return false;

}

void AVLDict::rotate_left( node *& a ) {
  // "rotates" the subtree rooted at a to the left (counter-clockwise)

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
std::cout << "Rotate Left: " << a->getUniqId() << std::endl;
#endif
// End of "DO NOT CHANGE" Block

  // TODO:  Write this function!
	
		node * temp = a->right;
  		a->right = temp->left;
  		temp->left = a;
  		update_height(a);
 		update_height(temp);
  		a = temp;
	

}

void AVLDict::rotate_right( node *& b ) {
  // "rotates" the subtree rooted at b to the right (clockwise)

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
cout << "Rotate Right: " << b->getUniqId() << endl;
#endif
// End of "DO NOT CHANGE" Block

  // TODO:  Write this function!
	
  		node * temp = b->left;
 		b->left = temp->right;
  		temp->right = b;
  		update_height(b);
  		update_height(temp);
  		b = temp;
	

}

// You may assume that no duplicate MazeState is ever added.
void AVLDict::add(MazeState *key, MazeState *pred) {

  // TODO:  Write this function!
  string k = key->getUniqId();
  // Base Case
  node* temp = new node();
  temp->key = key;
  temp->data = pred;
  temp->left = NULL;
  temp->right = NULL;
  temp->height = 0;
  addHelper(temp, root);
}

void AVLDict::addHelper(node*& n, node*& r){
	if (r == NULL){
    		r = n;
	}
  	if( n->key->getUniqId() < r->key->getUniqId() ) {
    		addHelper(n, r->left );
 	}
  	else if(n->key->getUniqId() > r->key->getUniqId() ) {                       
    		addHelper(n, r->right );
  	}
  	if(update_height(r)) balance(r);
}
 
  
  // either go to the left, or to the right, but ignore if already in tree
  // if key == root->key then ignore it (do not insert duplicate) 
  
  // We know: descendant had a child added (in recursive call, above).
  // Now we're "unwinding" the call-stack (returning from the recursive calls, 
  // one level at a time, until we get to the original call). 
  // Do we have to rebalance at this level?
 
 
 


    

void AVLDict::balance(node *& x){
	if(x == NULL) return;
	int b = height(x->left) - height(x->right);
	if( b >= -1 && b<= 1) return;
	if( b == 2){ 
		if(height(x->left->left) > height(x->left->right) ){
			rotate_right(x);
		}else {
			rotate_left(x->left);
			rotate_right(x);
		}
	} else {
		if(height(x->right->right) > height(x->right->left) ) {
			rotate_left(x);
		} else {
			rotate_right(x->right);
			rotate_left(x);
		}
	}
} 
	


#endif 
