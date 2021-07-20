#include <vector>
using namespace std;

template<typename T>
class NodeT
{
public:
	T		data;
	NodeT	*left;
	NodeT	*right;
	NodeT	*parent;
	bool	isBlack; // true if black

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




	NodeT<T> *root; // remember to change back to private




	RedBlackTree();
	RedBlackTree(const RedBlackTree<T> &src);
	RedBlackTree operator=(const RedBlackTree<T> &src);
	~RedBlackTree();
	bool insert(T data);
	bool remove(T data);
	bool search(T data);
	vector<T> search(T data1, T data2);
	T closestLess(T data);
	T closestGreater(T data);
	vector<T> values();
	int size();

	template <class Tjwme>
	friend NodeT<Tjwme>* JWMEgetRoot(const RedBlackTree<Tjwme> & rbt);

private:
	NodeT<T> *copyNodeT(const NodeT<T> *target);
	vector<T> inOrderTraversal(const NodeT<T> *root);
	NodeT<T>* bstInsert(NodeT<T> *root, NodeT<T> *in);
	// RbFix
	NodeT<T> *rightRotate(NodeT<T> *root);
	NodeT<T> *leftRotate(NodeT<T> *root);
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
	if (&src != (const RedBlackTree<T> *)this)
	{
		if (root != nullptr)
		{
			delete *root;
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
			}
			else
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
                in->isBlack = 1;
                grand_parent->isBlack = 0;
            }
		}
		// Parent is left children
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
            }
            else
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
                in->isBlack = 1;
                grand_parent->isBlack = 0;
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

	// Find node to delete
	// (need ptr to node to remove for next steps)
	// Remove node
	// Different cases
	return false;
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
		}
		else if (cur->data < data)
		{
			cur = cur->right;
		}
		else
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
vector<T> RedBlackTree<T>::search(T data1, T data2)
{
	vector<T> allVal = inOrderTraversal(this->root);
	vector<T> out;

	int target = min(data1, data2);
	int i = 0;

	while (i < allVal.size() && allVal[i] < target)
	{
		++i;
	}
	target = max(data1, data2);
	while (i < allVal.size() && allVal[i] <=target)
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
	vector<T> allVal = inOrderTraversal(this->root);

	for (int i = 0; i < allVal.size(); ++i)
	{
		if (i - 1 >= 0 && allVal[i] > data)
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
	vector<T> allVal = inOrderTraversal(this->root);

	for (int i = allVal.size() - 1; i >= 0; --i)
	{
		if (i + 1 < allVal.size() && allVal[i] < data)
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
vector<T> RedBlackTree<T>::values()
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
NodeT<T>* RedBlackTree<T>::copyNodeT(const NodeT<T> *target)
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
vector<T> RedBlackTree<T>::inOrderTraversal(const NodeT<T> *root)
{
	vector<T> out;
	vector<T> leftVec, rightVec;

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
NodeT<T>* RedBlackTree<T>::rightRotate(NodeT<T> *x)
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
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y; // x is left children
	}
	else
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
NodeT<T>* RedBlackTree<T>::leftRotate(NodeT<T> *x)
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
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y; // x is left children
	}
	else
	{
		x->parent->right = y; // x is right children
	}
	// make x y's left children
	y->left = x;
	x->parent = y;
	return root;
}

/*
 * Param: data to be inserted in the tree
 * Post: new red node containing data will be inserted
 * without violating BST policies and the inserted
 * node will be returned
 */
template<typename T>
NodeT<T>* RedBlackTree<T>::bstInsert(NodeT<T> *root, NodeT<T> *in)
{
	/* If the tree is empty, return a new node */
    if (root == nullptr)
       return in;
  
    /* Otherwise, recur down the tree */
    if (in->data < root->data)
    {
        root->left  = bstInsert(root->left, in);
        root->left->parent = root;
    }
    else if (in->data > root->data)
    {
        root->right = bstInsert(root->right, in);
        root->right->parent = root;
    }
  
    /* return the (unchanged) node pointer */
    return root;
}


