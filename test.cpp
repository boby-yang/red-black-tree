# include "RedBlackTree.h"
# include <iostream>
using namespace std;

/* 
 * Constructors to test:
 * RedBlackTree Normal constructor
 * RedBlackTree(RedBlackTree<T> &src) Copy constructor
 * RedBlackTree operator=(RedBlackTree<T> &src) = Operator
	
 * Methods to test:
 * bool insert(T data);
 * bool remove(T data);
 * bool search(T data);
 * vector<T> search(T data1, T data2);
 * T closestLess(T data);
 * T closestGreater(T data);
 * vector<T> values();
 * int size();
 */




int main()
{
	RedBlackTree<int> rbt;
	cout << to_string(rbt.size()) << endl;
	return 0;
}