/*
 *Author: Simon Huber
 *Mail: dev@simonhuber.org
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


#define MAX_NODES 10000000 //do not set this to 0 (will create a segfault)
typedef struct Node {
	struct Node* up; //some call it parents
	struct Node* left;
	struct Node* right;
	int64_t key;
	uint64_t prio; //used for heap structure part
} node;

typedef struct {
	node* root;
	/*
	 *mem is large array that holds the tree
	 *if delete_key is called and a node needs to be removed
	 *we change the ptrs and put it into a stack for 
	 *future reuse (stack not queue because of cache). top points to the top of this stack
	 *the up ptrs of the nodes in the stack point to the next element in the stack
	 *mem_unused points to the first addr in the memory alloced that has never been
	 *used and will be advanced if the queue is empty at insert time
	 */
	node* mem; 
	node* mem_unused;
	node* top; 
} turbotreap;

//create empty tree
turbotreap* create_turbotreap();

//dealloc tree
void delete_turbotreap(turbotreap* tree);

/*
 *if insert_key returns 0 the key was not in the tree 
 *if it returns 1 the key was in the tree
 */
int insert_key(int64_t key, turbotreap* tree);

/*
 *if delete_key returns 0 the key was in the tree
 *if it returns 1 the key was not in the tree
 */
int delete_key(int64_t key, turbotreap* tree);

/*
 *if find_key returns 0 the key is not in the tree
 *if it returns 1 the key is in the tree
 */
int find_key(int64_t key, turbotreap* tree);