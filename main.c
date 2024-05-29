/*
 *Author: Simon Huber
 *Mail: dev@simonhuber.org
 */

#include "turbotreap.h"
#include <time.h>

int main(){
	//set random set to current time
	srand(time(0)); 
	//test_0 is intended to verify basic functionality works
	printf("Starting: test_0 \n");
	turbotreap* T = create_turbotreap();
	for(int64_t i = 0; i<9;i=i+2){
		printf("insert_key: %ld, returns: %d\n", i, insert_key(i, T));
	}
	for(int64_t i = 0; i<11;i=i+1){
		printf("find_key: %ld, returns: %d\n",i, find_key(i, T));
	}
	for(int64_t i = 0; i<9;i=i+4){
		printf("delete_key: %ld, returns: %d\n", i, delete_key(i, T));
	}
	for(int64_t i = 0; i<11;i=i+1){
		printf("find_key: %ld, returns: %d\n",i, find_key(i, T));
	}
	delete_turbotreap(T);
	printf("Completed: test_0\n");

	//test_1 is intends to make use of the random structure find possible mistakes in the rotations 
	printf("Starting: test_1 \n");
	int64_t n = 10000000;
	turbotreap* T0 = create_turbotreap();
	turbotreap* T1 = create_turbotreap();
	int64_t r;
	int64_t D = 0;
	int64_t I = 0;
	clock_t s, e;
	s = clock();
	for(int64_t i = 0; i<n;i++){ //do some random insertions and deletions
		r = rand()%n;
		if(rand()%3){ //P(delete) = 1/3, P(insert) = 2/3
			D++;
			delete_key(r, T0);
			delete_key(r, T1);
		} else {
			I++;
			insert_key(r, T0);
			insert_key(r, T1);
		}
	}
	int64_t K = 0;
	for(int64_t i = 0; i<n;i++){ //find if trees agree
		if(find_key(i,T0) != find_key(i, T1)){
			printf("Warning: T0 and T1 dont agree something went wrong \n");
		} else {
			if (find_key(i,T0)){
				K++;
			}
		}
	}
	e = clock();
	delete_turbotreap(T0);
	delete_turbotreap(T1);
	printf("Completed: test_1 (if no Warnings were printed, test_1 was successful)\nStats: %ld insertions and %ld deletions were made, %ld nodes were in the trees, Completed in %f seconds \n", I, D, K, ((double)(e - s))/CLOCKS_PER_SEC);
	return 0;
}
