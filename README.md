# turbotreap

This is a small project of mine. I implemented a very basic version of a [Treap](https://en.wikipedia.org/wiki/Treap). The Priorities use the C rand() function but using a hash function instead could easily be implemented. The `main` function contains two tests. test_0 tests basic functionality and test_1 tries to the find problems with the rotations (make two trees with the same inserts and deletes but priorities will of course differ and hence the trees will look different). 

## How to
The `main` function illustrates how to use the Treap. Additionally you can have a look at the.h file. Be aware the there is a constant in `turbotreap.h` called `MAX_NODES`, it is set to 10000000 by default and well caps the number of nodes that can be in the Treap at any time.

## Other things
How "turbo" the Treap is left for you to decide but I tried to waste as little as possible.

Don't use this for anything critical because I have no idea if there are undiscovered mistakes or security vulnerability in the code (it's a side project)

## Console ouput

The concole output of the compiled `main.c` should look like this:

```
Starting: test_0 
insert_key: 0, returns: 0
insert_key: 2, returns: 0
insert_key: 4, returns: 0
insert_key: 6, returns: 0
insert_key: 8, returns: 0
find_key: 0, returns: 1
find_key: 1, returns: 0
find_key: 2, returns: 1
find_key: 3, returns: 0
find_key: 4, returns: 1
find_key: 5, returns: 0
find_key: 6, returns: 1
find_key: 7, returns: 0
find_key: 8, returns: 1
find_key: 9, returns: 0
find_key: 10, returns: 0
delete_key: 0, returns: 1
delete_key: 4, returns: 1
delete_key: 8, returns: 1
find_key: 0, returns: 0
find_key: 1, returns: 0
find_key: 2, returns: 1
find_key: 3, returns: 0
find_key: 4, returns: 0
find_key: 5, returns: 0
find_key: 6, returns: 1
find_key: 7, returns: 0
find_key: 8, returns: 0
find_key: 9, returns: 0
find_key: 10, returns: 0
Completed: test_0
Starting: test_1 
Completed: test_1 (if no Warnings were printed, test_1 was successful)
Stats: 3333530 insertions and 6666470 deletions were made, 2107999 nodes were in the trees, Completed in 38.775881 seconds 
```
