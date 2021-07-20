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

	if (tr.size() == 0)
		return ;
	q.push(tr.root);
	this_layer_cnt = 1;
	next_layer_cnt = 0;
	while (this_layer_cnt > 0)
	{
		NodeT<T> *cur = q.front();
		q.pop();

		if (cur != nullptr)
		{
			cout << to_string(cur->data);
			if (cur->isBlack == true)
			 cout << " ";
			else
			 cout << "R ";
		}
		else
			cout << "X ";
		this_layer_cnt--;
		if (cur != nullptr)
		{
			q.push(cur->left);
			q.push(cur->right);
			next_layer_cnt += 2;
		}
		if (this_layer_cnt == 0)
		{
			cout << endl;
			this_layer_cnt = next_layer_cnt;
			next_layer_cnt = 0;
		}
	}
}

void testInsertLeftScewed()
{
	RedBlackTree<int> rb1;
	RedBlackTree<int> &rb_ref = rb1;
	
	for (int i = 180; i >= 0; i -= 10)
	{
		rb1.insert(i);
		levelOrderPrint(rb_ref);
		cout << "\n\n";
	}	
}

void testInsertRightScewed()
{
	RedBlackTree<int> rb1;
	RedBlackTree<int> &rb_ref = rb1;
	
	for (int i = 180; i >= 0; i -= 10)
	{
		rb1.insert(i);
		levelOrderPrint(rb_ref);
		cout << "\n\n";
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
	// simpleTest();
    // statistics("test.txt");
    cout << "Left scewed 180 --> 0" << endl;
	testInsertLeftScewed();
	cout << "Right scewed 0 --> 180" << endl;
	testInsertRightScewed();

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

	
	// rb1.insert(80);
	// rb1.insert(10);
	// rb1.insert(35);
	// rb1.insert(45);
	// cout << "Tree size: " << to_string(rb1.size()) << endl;
	
	// RedBlackTree<int> &rb_ref = rb1;
	// cout << "Print tree: " << endl;
	// levelOrderPrint(rb_ref);
	return 0;
}