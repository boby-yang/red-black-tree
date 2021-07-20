# include "RedBlackTree.h"
# include <iostream>
# include <queue>
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
template<typename T>
void levelOrderPrint(RedBlackTree<T> &tr)
{
	queue<NodeT<T>*> q;
	int next_layer_cnt, this_layer_cnt;

	// if (tr.size() == 0)
	// 	return ;
	q.push(tr.root);
	this_layer_cnt = 1;
	next_layer_cnt = 0;
	while (!q.empty())
	{
		NodeT<T> *cur = q.front();
		q.pop();
		cout << to_string(cur->data);
		if (cur->isBlack == true)
			 cout << " ";
		else
			 cout << "R ";
		this_layer_cnt--;
		if (cur->left != nullptr)
		{
			q.push(cur->left);
			next_layer_cnt++;
		}
		if (cur->right != nullptr)
		{
			q.push(cur->right);
			next_layer_cnt++;
		}
		if (this_layer_cnt == 0)
		{
			cout << endl;
			this_layer_cnt = next_layer_cnt;
			next_layer_cnt = 0;
		}
	}
}

void simpleTest()
{
	// Int Tree Tests   
	RedBlackTree<int> rb1;
	if (rb1.insert(42)) cout << "inserted 42" << endl;
	rb1.insert(71);
	rb1.insert(13);
	RedBlackTree<int> rb2(rb1);
	cout << "Copy Tree size: " << to_string(rb2.size()) << endl;
	
	RedBlackTree<int> &rb_ref = rb2;
	cout << "Print copied tree: " << endl;
	levelOrderPrint(rb_ref);

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
	simpleTest();
	// NodeT<int> *fakeRoot = new NodeT<int>(5);
	// NodeT<int> *fakeLeft = new NodeT<int>(3);
	// NodeT<int> *fakeRight = new NodeT<int>(7);
	// fakeRoot->left = fakeLeft;
	// fakeRoot->right = fakeRight;
	// RedBlackTree<int> rb1;
	// RedBlackTree<int> &rb_ref = rb1;
	// rb1.root = fakeRoot;
	// cout << "Print tree: " << endl;
	// levelOrderPrint(rb_ref);

	RedBlackTree<int> rb1;
	rb1.insert(180);
	rb1.insert(170);
	rb1.insert(160);
	rb1.insert(150);
	rb1.insert(140);
	rb1.insert(130);
	rb1.insert(120);
	rb1.insert(110);
	rb1.insert(100);
	rb1.insert(90);
	rb1.insert(80);
	rb1.insert(70);
	rb1.insert(60);
	rb1.insert(50);
	rb1.insert(40);
	rb1.insert(30);
	rb1.insert(20);
	rb1.insert(10);
	// rb1.insert(80);
	// rb1.insert(10);
	// rb1.insert(35);
	// rb1.insert(45);
	cout << "Tree size: " << to_string(rb1.size()) << endl;
	
	RedBlackTree<int> &rb_ref = rb1;
	cout << "Print tree: " << endl;
	levelOrderPrint(rb_ref);
    statistics("test.txt");
	return 0;
}