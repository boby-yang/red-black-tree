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


void simpleTest()
{
    // Int Tree Tests   
    RedBlackTree<int> rb1;
    if (rb1.insert(42)) cout << "inserted 42" << endl;
    rb1.insert(71);
    rb1.insert(13);
    RedBlackTree<int> rb2(rb1);
 
    if (rb1.remove(13)) cout << "removed 13" << endl;
    if (rb1.search(42)) cout << "found 42" << endl;
 
    vector<int> v1 = rb1.search(50, 100); //should contain 71
    vector<int> v2 = rb1.values(); //should contain {42,71}
 
    cout << "closestLess(12) = " << rb1.closestLess(12) << endl;
    cout << "closestGreater(91) = " << rb1.closestGreater(91) << endl;
 
    cout << "size = " << rb1.size() << endl; //should be 2
}

int main()
{
	RedBlackTree<int> rbt;
	cout << to_string(rbt.size()) << endl;
	return 0;
}