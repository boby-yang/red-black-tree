# include "RedBlackTree.h"
# include <iostream>
using namespace std;

int main()
{
	RedBlackTree<int> rbt;
	cout << to_string(rbt.size()) << endl;
	return 0;
}