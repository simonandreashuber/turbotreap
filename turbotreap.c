/*
 *Author: Simon Huber
 *Mail: dev@simonhuber.org
 */

#include "turbotreap.h"


turbotreap* create_turbotreap(){
	turbotreap* tree;
	tree = (turbotreap*)malloc(sizeof(turbotreap));
	tree->mem = (node*)malloc(MAX_NODES * sizeof(node));
	tree->mem_unused = tree->mem;
	tree->root = NULL;
	tree->top = NULL;
	return tree;
}

void delete_turbotreap(turbotreap* tree){
	free(tree->mem);
	free(tree);
}

#define INSERT_NODE(child, parent_down_ptr, key_value) \
			parent_down_ptr = child; \
			child->up = cn; \
			child->key = key_value; \
			child->left = NULL; \
			child->right = NULL; \
			child->prio = (uint64_t)rand(); \
			child->prio <<= 32; \
			child->prio |=  (uint64_t)rand()

int insert_key(int64_t key, turbotreap* tree){
	node * cn = tree->root; //cn stands for current node
	if(!cn){ //if root is NULL create root node
		//maybe it would be good to check if MAX_NODES is not 0 but this case is nonsensical (might also be security problem)
		tree->top = NULL; //the tree is empty so we can just set all the memory stuff to the initial condition
		tree->mem_unused = tree->mem;
		INSERT_NODE(tree->mem_unused, tree->root, key);
		tree->mem_unused++;
		return 0; //key was not in tree
	} 
	//do binary tree insert
	while(1){ 
		if(key == cn->key){
			return 1;
		}
		if(key < cn->key){ // left or right case
			if(cn->left == NULL){ //insert or walk
				if(tree->top == NULL){ //insert at unused or used memory loc
					if(MAX_NODES + tree->mem <= tree->mem_unused){ //check if memory is left
						return -1;
					}
					INSERT_NODE(tree->mem_unused, cn->left, key); //do the insert with macro because speeeeed
					tree->mem_unused++; //advance unused space
				} else {
					node* new_top = tree->top->up; // not so happy with new variable one could use left ptr of child but then macro gets more complex and I want to refrain from overcomplicating
					INSERT_NODE(tree->top, cn->left, key);
					tree->top = new_top;
				}
				cn = cn->left;
				break; //here we need to break as there might be rotations needed
			} else {
				cn = cn->left;
			}		
		} else {
			if(cn->right == NULL){ //insert or walk
				if(tree->top == NULL){ //insert at unused or used memory loc
					if(MAX_NODES + tree->mem <= tree->mem_unused){//check if memory is left
						return -1;
					}
					INSERT_NODE(tree->mem_unused, cn->right, key); //do the insert with macro because speeeeed
					tree->mem_unused++; //advance unused space
				} else {
					node* new_top = tree->top->up; // not so happy with new variable one could use left ptr of child but then macro gets more complex and I want to refrain from overcomplicating
					INSERT_NODE(tree->top, cn->right, key);
					tree->top = new_top;
				}
				cn = cn->right;
				break; //here we need to break as there might be rotations needed
			} else {
				cn = cn->right;
			}
		}
	}
	//restore heap, note cn is the newly inserted node now
	while(cn->up != NULL && cn->up->prio < cn->prio){ // while cn not root nor heap property satisfied (left to right evaluation)
		if(cn == cn->up->left){ //cn is left child so: rotate right subtree at y
			if ((cn->up->left = cn->right)){ //set y left to B and check if not null
				cn->right->up = cn->up; //set B up to y
			}
			cn->right = cn->up; //set x right to y
			if((cn->up = cn->right->up)){ //set x up connection and check if it is null
				if(cn->up->left == cn->right){ //y was left child
					cn->up->left = cn; 
				} else { //y was right child
					cn->up->right = cn;
				}
			} else { // if the x up connection was NULL x is the root now
				tree->root = cn;
			}
			cn->right->up = cn; // set y up to x connection (can be done early since used)
		} else { //cn is right child so: rotate left subtree at x
			if((cn->up->right = cn->left)){ //set x right to B
				cn->left->up = cn->up; //set B up to x
			}
			cn->left = cn->up; //set y left to x
			if((cn->up = cn->left->up)){ //set y up connection and check if it is null
				if(cn->up->left == cn->left){ //x was left child
					cn->up->left = cn; 
				} else { //y was right child
					cn->up->right = cn;
				}
			} else { // if the x up connection was NULL x is the root now
				tree->root = cn;
			}
			cn->left->up = cn; // set x up to y connection (can be done early since used)
		}
	}
	return 0;
}



int find_key(int64_t key, turbotreap* tree){
	node * cn = tree->root; //cn stands for current node
	if(!cn){ //if root is NULL key not in tree 
		return 0; //key was not in tree
	} 
	while(key != cn->key){ 
		if(key < cn->key){ // left or right case
			if(cn->left == NULL){ //insert or walk
				return 0; // its not in tree
			} else {
				cn = cn->left;
			}		
		} else {
			if(cn->right == NULL){ //insert or walk
				return 0; //its not in tree
			} else {
				cn = cn->right;
			}
		}
	}
	return 1; //was in the tree
}



int delete_key(int64_t key, turbotreap* tree){
	//find node, if not in tree return 0, else continue with possible down rotations
	node * cn = tree->root; //cn stands for current node
	if(!cn){ //if root is NULL key not in tree 
		return 0; //key was not in tree
	} 
	while(key != cn->key){ 
		if(key < cn->key){ // left or right case
			if(cn->left == NULL){ //insert or walk
				return 0; // its not in tree
			} else {
				cn = cn->left;
			}		
		} else {
			if(cn->right == NULL){ //insert or walk
				return 0; //its not in tree
			} else {
				cn = cn->right;
			}
		}
	}

	//restore heap, note cn is the newly inserted node now
	while(cn->left || cn->right){ // while cn is not child
		if(!cn->right || ((cn->left && cn->right) && (cn->right->prio < cn->left->prio))){ // if right child NULL or both children exist and left prio is larger
			if ((cn->left->up = cn->up)){ //set x up to y up and check if it was NULL (0)
				if(cn->up->left == cn){ //y was left child (1)
					cn->up->left = cn->left; 
				} else { //y was right child
					cn->up->right = cn->left;
				}
			} else { //this is the case where y (cn) is the root
				tree->root = cn->left; // (1)
			}
			cn->up = cn->left; //(2)
			if((cn->left  = cn->up->right)){ //(3)
				cn->left->up = cn; //(4)
			}
			cn->up->right = cn; //(5)
		} else { //cn is right child so: rotate left subtree at x
			if ((cn->right->up = cn->up)){ //(0)
				if(cn->up->left == cn){ //(1)
					cn->up->left = cn->right; 
				} else { 
					cn->up->right = cn->right;
				}
			} else { //this is the case where y (cn) is the root
				tree->root = cn->right; // (1)
			}
			cn->up = cn->right; //(2)
			if((cn->right  = cn->up->left)){ //(3)
				cn->right->up = cn; //(4)
			}
			cn->up->left = cn; //(5)
		}
	}
	//cn is now a child so we can just delete
	if (!cn->up){ //check if root should be deleted
		tree->root = NULL;
	} else {
		if(cn->up->left == cn){ //change right child
			cn->up->left = NULL; 
		} else { 
			cn->up->right = NULL;
		}
	}
	cn->up = tree->top; //set connection to old top stack
	tree->top = cn; //cn is now top of stack
	return 1;
}
