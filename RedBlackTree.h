#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template<typename T>
class NodeT
{
public:
	T data;
	NodeT *left;
	NodeT *right;
	NodeT *parent;
	bool isBlack; // true if black

	/*
	 * Constructor of the NodeT that takes a template type parameter
	 * Param: template type parameter
	 * Post: initiate left, right, parent pointers to nullptr,
	 * 		data will be set according to the given data parameter
	 *		isBlack will be false
	 */
	NodeT(T d)
	{
		data = d;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		isBlack = false;
	}

/*
 * Destructor of the NodeT
 * Param: none
 * Post: all NodeT will be deleted in order
 */
	~NodeT()
	{
		if (left != nullptr)
		{
			delete left;
		}
		if (right != nullptr)
		{
			delete right;
		}
	}

};


template<typename T>
class RedBlackTree
{
private:
	// NodeT<T> *root; // remember to change back to private
	int tree_size;

public:

	NodeT<T> *root; // remember this?



	RedBlackTree();

	RedBlackTree(const RedBlackTree<T> &src);

	RedBlackTree operator=(const RedBlackTree<T> &src);

	~RedBlackTree();

	bool insert(T data);

	bool remove(T data);

	bool search(T data);

	vector <T> search(T data1, T data2);

	T closestLess(T data);

	T closestGreater(T data);

	vector <T> values();

	int size();

	template<class Tjwme>
	friend NodeT<Tjwme> *JWMEgetRoot(const RedBlackTree<Tjwme> &rbt);

private:
	NodeT<T> *copyNodeT(const NodeT<T> *target);

	vector <T> inOrderTraversal(const NodeT<T> *root);

	NodeT<T> *bstInsert(NodeT<T> *root, NodeT<T> *in);

	NodeT<T> *bstReplace(NodeT<T> *target);

	NodeT<T> *bstFind(T target);

	void fixDoubleBlack(NodeT<T> *target);

	NodeT<T> *rightRotate(NodeT<T> *root);

	NodeT<T> *leftRotate(NodeT<T> *root);

	bool helperNoChildren(NodeT<T> *t, NodeT<T> *p);
	
	bool helperOneChild(NodeT<T> *t, NodeT<T> *r, NodeT<T> *p);
};

/*
 * Default constructor of the RedBlackTree
 * Param: None
 * Post: root pointer will be set to nullptr
 */
template<typename T>
RedBlackTree<T>::RedBlackTree()
{
	root = nullptr;
	tree_size = 0;
}

/*
 * Copy constructor of the RedBlackTree
 * Param: reference of a RedBlackTree<T> object
 * Post: all nodeT of the parameter will will be 
 * copied; root pointer will also be set accordingly
 */
template<typename T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T> &src)
{
	tree_size = src.tree_size;
	root = copyNodeT(src.root);
}

/*
 * Destructor of the RedBlackTree
 * Param: none
 * Post: all NodeT will be deleted in order
 */
template<typename T>
RedBlackTree<T> RedBlackTree<T>::operator=(const RedBlackTree<T> &src)
{
	if (&src != (const RedBlackTree<T> *) this)
	{
		if (root != nullptr)
		{
			delete root;
		}
		root = copyNodeT(src.root);
		tree_size = src.tree_size;
	}
	return *this;
}

/*
 * Overridden assignment operation of the RedBlackTree
 * Param: constant reference of a RedBlackTree<T> object
 * Post:(parameter != this) all NodeT in the tree will deleted;
 * 		all nodeT of the parameter will will be 
 * 		copied; root pointer will also be set accordingly
 */
template<typename T>
RedBlackTree<T>::~RedBlackTree()
{
	if (root != nullptr)
	{
		delete root;
	}
}

/* 
 * Pre: RedBlackTree obj need to be created
 * Param: template type parameter to add
 * Post: returns false if node containing data exists;
 * otherwise return true and add new NodeT to the tree
 * and update tree_size
 */
template<typename T>
bool RedBlackTree<T>::insert(T data)
{
	// Check if data is in tree
	if (search(data) == true)
	{
		return false;
	}
	// BST insertion
	NodeT<T> *in = new NodeT<T>(data);
	root = bstInsert(root, in);

	// Fix violation
	NodeT<T> *uncle = nullptr;
	NodeT<T> *parent = nullptr;
	NodeT<T> *grand_parent = nullptr;
	while (in->parent != nullptr && in->isBlack == false && in->parent->isBlack == false)
	{
		parent = in->parent;
		grand_parent = in->parent->parent;
		// Parent is left children
		if (parent == grand_parent->left)
		{
			uncle = grand_parent->right;
			// Red uncle: Recolor to fix violation
			if (uncle != nullptr && uncle->isBlack == false)
			{
				grand_parent->isBlack = false;
				parent->isBlack = true;
				uncle->isBlack = true;
				in = grand_parent;
			} else
			{
				/* 
				in is right child of its parent
				Left-rotation required */
				if (in == parent->right)
				{
					in = leftRotate(parent);
					parent = in->left;
				}
				/*
				in is left child of its parent
				Right-rotation required */
				in = rightRotate(grand_parent);
				parent->isBlack = true;
				grand_parent->isBlack = false;
			}
		}
			// Parent is right children
		else
		{
			uncle = grand_parent->left;

			// Red uncle: Recolor to fix violation
			if ((uncle != nullptr) && (uncle->isBlack == false))
			{
				grand_parent->isBlack = false;
				parent->isBlack = true;
				uncle->isBlack = true;
				in = grand_parent;
			} else
			{
				/*
				in is left child of its parent
				Right-rotation required */
				if (in == parent->left)
				{
					in = rightRotate(parent);
					parent = in->right;
				}

				/* 
				in is right child of its parent
				Left-rotation required */
				in = leftRotate(grand_parent);
				parent->isBlack = true;
				grand_parent->isBlack = false;
			}
		}
	}
	root->isBlack = true;
	tree_size++;
	return true;
}

/* 
 * Pre: RedBlackTree obj need to be created
 * Param: template type parameter to remove
 * Post: returns true and remove node it node containing 
 * data exists and update tree_size; 
 * otherwise return false
 */
template<typename T>
bool RedBlackTree<T>::remove(T data)
{
	// TODO: fill in function (see slide)
	// Check if data is in tree
	NodeT<T> *t = bstFind(data);
	if (t == nullptr)
	{
		return false;
	}
	// find node that will replace target
	NodeT<T> *r = bstReplace(t);
	NodeT<T> *p = t->parent;

	if (r == nullptr)
	{
		return helperNoChildren(t, p);
	}
	if (t->left == nullptr || t->right == nullptr)
	{
		return helperOneChild(t, r, p);
	}
	/* target has two children, swap values and recurse */
	T tmp = t->data;
	t->data = r->data;
	r->data = tmp;
	if (r->left == nullptr && r->right == nullptr)
	{
		return helperNoChildren(r, r->parent);
	}
	else
	{
		if (r->left != nullptr)
		{
			return helperOneChild(r, r->left, r->parent);
		}
		else
		{
			return helperOneChild(r, r->right, r->parent);
		}
	}
}


/* 
 * Pre: RedBlackTree obj need to be created
 * Param: template type parameter to search for
 * Post: returns true if node containing data exists;
 * otherwise return false
 */
template<typename T>
bool RedBlackTree<T>::search(T data)
{
	if (root == nullptr)
	{
		return false;
	}

	NodeT<T> *cur = root;

	while (cur != nullptr)
	{
		if (cur->data == data)
		{
			return true;
		} else if (cur->data < data)
		{
			cur = cur->right;
		} else
		{
			cur = cur->left;
		}
	}
	return false;
}

/* 
 * Pre: RedBlackTree obj need to be created
 * Param: template type parameters defining range to search
 * Post: returns vector of template type values in the
 * tree that falls in the data range
 */
template<typename T>
vector <T> RedBlackTree<T>::search(T data1, T data2)
{
	vector <T> allVal = inOrderTraversal(this->root);
	vector <T> out;

	int target = min(data1, data2);
	int i = 0;

	while (i < allVal.size() && allVal[i] < target)
	{
		++i;
	}
	target = max(data1, data2);
	while (i < allVal.size() && allVal[i] <= target)
	{
		out.push_back(allVal[i]);
		++i;
	}
	return out;
}

/* 
 * Pre: RedBlackTree obj need to be created
 * Param: target template type parameter
 * Post:  returns the largest value stored in the
 * tree that is less than the parameter
 */
template<typename T>
T RedBlackTree<T>::closestLess(T data)
{
	vector <T> allVal = inOrderTraversal(this->root);

	if (tree_size == 0 || allVal[0] >= data)
	{
		return data;
	}	
	for (int i = 0; i < allVal.size(); ++i)
	{
		if (i - 1 >= 0 && allVal[i] >= data)
		{
			return allVal[i - 1];
		}
	}
	return data;
}

/* 
 * Pre: RedBlackTree obj need to be created
 * Param: target template type parameter
 * Post:  returns the smallest value stored in the
 * tree that is greater than the parameter
 */
template<typename T>
T RedBlackTree<T>::closestGreater(T data)
{
	vector <T> allVal = inOrderTraversal(this->root);

	if (tree_size == 0 || allVal[tree_size - 1] <= data)
	{
		return data;
	}
	for (int i = allVal.size() - 1; i >= 0; --i)
	{
		if (i + 1 < allVal.size() && allVal[i] <= data)
		{
			return allVal[i + 1];
		}
	}
	return data;
}

/* 
 * Pre: RedBlackTree obj need to be created
 * Param: none
 * Post: returns vector containing all template type
 * values in the tree in ascending order
 */
template<typename T>
vector <T> RedBlackTree<T>::values()
{
	return inOrderTraversal(this->root);
}

/* 
 * Pre: RedBlackTree obj need to be created
 * Param: none
 * Post: returns the number of NodeT in the tree
 */
template<typename T>
int RedBlackTree<T>::size()
{
	return tree_size;
}

///// Helper Functions /////

/*
 * Param: pointer to NodeT to be copied
 * Post: all NodeT in target will be deep copied,
 * and the copied root will be returned 
 */
template<typename T>
NodeT<T> *RedBlackTree<T>::copyNodeT(const NodeT<T> *target)
{
	if (target == nullptr)
	{
		return nullptr;
	}
	NodeT<T> *out = new NodeT<T>(target->data);
	out->isBlack = target->isBlack;
	NodeT<T> *newLeft = nullptr;
	NodeT<T> *newRight = nullptr;
	if (target->left != nullptr)
	{
		newLeft = copyNodeT(target->left);
		newLeft->parent = out;
	}
	if (target->right != nullptr)
	{
		newRight = copyNodeT(target->right);
		newRight->parent = out;
	}
	out->left = newLeft;
	out->right = newRight;
	return out;
};

/* 
 * Inorder traversal of the node
 * Param: none
 * Post: returns vector containing all template type
 * values in the tree in ascending order
 */
template<typename T>
vector <T> RedBlackTree<T>::inOrderTraversal(const NodeT<T> *root)
{
	vector <T> out;
	vector <T> leftVec, rightVec;

	if (root == nullptr)
	{
		return out;
	}
	if (root->left != nullptr)
	{
		leftVec = inOrderTraversal(root->left);
	}
	if (root->right != nullptr)
	{
		rightVec = inOrderTraversal(root->right);
	}
	out.insert(out.end(), leftVec.begin(), leftVec.end());
	out.push_back(root->data);
	out.insert(out.end(), rightVec.begin(), rightVec.end());
	return out;
};

/*
 * Param: node in the tree to be right rotated
 * Post: tree will be right rotated at root and 
 * new root will be returned
 */
template<typename T>
NodeT<T> *RedBlackTree<T>::rightRotate(NodeT<T> *x)
{
	NodeT<T> *y = x->left;
	if (y == nullptr)
	{
		return root; // cannot right rotate
	}
	x->left = y->right;
	// See nodes' parent references
	// y's right children
	if (y->right != nullptr)
	{
		y->right->parent = x;
	}
	// y
	y->parent = x->parent;

	// Set child reference of x’s parent
	if (x->parent == nullptr) // x was root
	{
		root = y;
	} else if (x == x->parent->left)
	{
		x->parent->left = y; // x is left children
	} else
	{
		x->parent->right = y; // x is right children
	}
	// make x y's right children
	y->right = x;
	x->parent = y;
	return root;

}

/*
 * Param: node in the tree to be left rotated
 * Post: tree will be left rotated at x and 
 * new root will be returned
 */
template<typename T>
NodeT<T> *RedBlackTree<T>::leftRotate(NodeT<T> *x)
{
	NodeT<T> *y = x->right;
	if (y == nullptr)
	{
		return root; // cannot left rotate
	}
	x->right = y->left;
	// See nodes' parent references
	// y's left children
	if (y->left != nullptr)
	{
		y->left->parent = x;
	}
	// y
	y->parent = x->parent;

	// Set child reference of x’s parent
	if (x->parent == nullptr) // x was root
	{
		root = y;
	} else if (x == x->parent->left)
	{
		x->parent->left = y; // x is left children
	} else
	{
		x->parent->right = y; // x is right children
	}
	// make x y's left children
	y->left = x;
	x->parent = y;
	return root;
}

/*
 * Param: current root of the tree and node to be inserted
 * Post: param node will be inserted
 * without violating BST policies and return the new root
 */
template<typename T>
NodeT<T> *RedBlackTree<T>::bstInsert(NodeT<T> *root, NodeT<T> *in)
{
	/* If the tree is empty, return a new node */
	if (root == nullptr)
	{
		return in;
	}

	/* Otherwise, recur down the tree */
	if (in->data < root->data)
	{
		root->left = bstInsert(root->left, in);
		root->left->parent = root;
	} else if (in->data > root->data)
	{
		root->right = bstInsert(root->right, in);
		root->right->parent = root;
	}

	/* return the (unchanged) node pointer */
	return root;
}

/*
 * Param: node to be removed
 * Post: return the node that will replace target after remove
 */
template<typename T>
NodeT<T> *RedBlackTree<T>::bstReplace(NodeT<T> *target)
{
	if (target->left != nullptr && target->right != nullptr)
	{
		/* node has two children */
		NodeT<T> *tmp = target->left;
		while (tmp != nullptr && tmp->right != nullptr)
		{
			tmp = tmp->right;
		}
		return tmp;
	}

	if (target->left == nullptr && target->right == nullptr)
	{
		return nullptr;
	} 

	if (target->left != nullptr)
	{
		return target->left;
	} 
	else
	{
		return target->right;
	}
}

/*
 * Param: template type data we are finding in the tree
 * Post: return the node contains the target data
 * nullptr if not found
 */
template<typename T>
NodeT<T> *RedBlackTree<T>::bstFind(T target)
{
	NodeT<T> *cur = root;

	while (cur != nullptr)
	{
		if (cur->data > target)
		{
			cur = cur->left;
		} else if (cur->data < target)
		{
			cur = cur->right;
		} else
		{
			return cur;
		}
	}
	return nullptr;
}

/*
 * Param: node we are going to fix
 * Post: fix double black case at target node
 */
template<typename T>
void RedBlackTree<T>::fixDoubleBlack(NodeT<T> *t)
{
	if (t == root)
	{
		return;
	}
	NodeT<T> *p = t->parent;
	NodeT<T> *s;
	if (t == p->left)
	{
		s = p->right;
	} else
	{
		s = p->left;
	}
	/* no sibling, push up double black */
	if (s == nullptr)
	{
		fixDoubleBlack(p);
	} else
	{
		if (s->isBlack == false)
		{
			p->isBlack = false;
			s->isBlack = true;
			if (s == p->left)
			{
				rightRotate(p);
			} else
			{
				leftRotate(p);
			}
			fixDoubleBlack(t);
		} else
		{
			/* black sibling */
			if ((s->left != nullptr && s->left->isBlack == false) ||
				(s->right != nullptr && s->right->isBlack == false))
			{
				if (s->left != nullptr && s->left->isBlack == false)
				{
					if (s == p->left)
					{
						/* left left */
						s->left->isBlack = s->isBlack;
						s->isBlack = p->isBlack;
						rightRotate(p);
					} else
					{
						/* right right */
						s->left->isBlack = p->isBlack;
						rightRotate(s);
						leftRotate(p);
					}
				} else
				{
					if (s == p->left)
					{
						s->right->isBlack = p->isBlack;
						leftRotate(s);
						rightRotate(p);
					} else
					{
						s->right->isBlack = s->isBlack;
						s->isBlack = p->isBlack;
						leftRotate(p);
					}
				}
				p->isBlack = true;
			} else
			{
				/* 2 b children */
				s->isBlack = false;
				if (p->isBlack == true)
				{
					fixDoubleBlack(p);
				} else
				{
					p->isBlack = true;
				}
			}
		}
	}
}

/*
 * This is the helper function that deals with the target node 
 * being removed has no children.
 * Param: target node and parant node
 */
template<typename T>
bool RedBlackTree<T>::helperNoChildren(NodeT<T> *t, NodeT<T> *p)
{
	NodeT<T> *s = nullptr;

	/* set sibling */
	if (p != nullptr && t == p->left)
	{
		s = p->right;
	} else if (p != nullptr && t == p->right)
	{
		s = p->left;
	}

	/* Target is root */
	if (t == root)
	{
		root = nullptr;
	} 
	else
	{
		if (t->isBlack)
		{
			fixDoubleBlack(t);
		} 
		else
		{
			if (s != nullptr)
			{
				s->isBlack = false;
			}
		}
		if (t == p->left) //
		{
			p->left = nullptr;
		} 
		else
		{
			p->right = nullptr;
		}
	}
	free(t);
	tree_size--;
	return true;
}

/*
 * This is the helper function that deals with the target node 
 * being removed has 1 child.
 * Param: target node, parant node and the child of target node
 */
template<typename T>
bool RedBlackTree<T>::helperOneChild(NodeT<T> *t, NodeT<T> *r, NodeT<T> *p)
{	
	/* target has 1 child */
	if (t == root)
	{
		t->data = r->data;
		t->left = nullptr;
		t->right = nullptr;
		free(r);
	} else
	{
		/* detach target from tree and move r up */
		if (t == p->left)
		{
			p->left = r;
		} else
		{
			p->right = r;
		}
		free(t);
		r->parent = p;
		if (r->isBlack == true && t->isBlack == true)
		{
			fixDoubleBlack(r);
		} else
		{
			r->isBlack = true;
		}
	}
	tree_size--;
	return true;
}

/*
 * Pre: a file with filename
 * Param: a string contains the file name
 * Pose: outputs some statistics for the given filename 
 */
void statistics(string filename)
{
	RedBlackTree<double> rbt;
	double sum = 0.0;
	double median, big, small, avg;
	ifstream fin(filename, ifstream::in);
	if (fin.is_open())
	{
		double grade;
		while (fin >> grade)
		{
			if (true == rbt.insert(grade))
			{
				sum += grade;
			}
		}
	}
	vector<double> v = rbt.values();
	small = rbt.closestLess(42.0);
	big = rbt.closestGreater(42.0);
	if (rbt.size() == 0)
	{
		median = 0;
		avg = 0;
	}
	else
	{
		median = (v[rbt.size() / 2] + v[rbt.size() / 2 - 1]) / 2.0;
		median = (0 == (rbt.size() % 2) ? median : v[rbt.size() / 2]);
		avg = sum / rbt.size();
	}	
	cout << "# of values:  " << to_string(rbt.size()) << "\n";
	cout << "average:      " << to_string(avg) << "\n";
	cout << "median:       " << to_string(median) << "\n";
	cout << "closest < 42: " << (small == 42.0 ? "None" : to_string(small)) << "\n";
	cout << "closest > 42: " << (big == 42.0 ? "None" : to_string(big)) << "\n";
}
