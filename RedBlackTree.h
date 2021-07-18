#include <vector>
using namespace std;

/////// Part 1: NodeT Class ///////
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

/////// Part 2: Helper Methods ///////
/*
 * Param: pointer to NodeT to be copied
 * Post: all NodeT in target will be deep copied,
 * and the copied root will be returned 
 */
template<typename T>
NodeT<T> *copyNodeT(NodeT<T> *target)
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
		newLeft = copyNode(target->left);
		newLeft->parent = out;
	}
	if (target->right != nullptr)
	{
		newRight = copyNode(target->right);
		newRight->parent = out;
	}
	return out;
};

/* 
 * Inorder traversal of the node
 * Param: none
 * Post: returns vector containing all template type
 * values in the tree in ascending order
 */
template<typename T>
vector<T> inOrderTraversal(NodeT<T>  *root)
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

/////// Part 3: RedBlackTree Class ///////
template<typename T>
class RedBlackTree
{
private:
	NodeT<T>	*root;

public:
	RedBlackTree();

	RedBlackTree(RedBlackTree<T> &src);

	RedBlackTree operator=(RedBlackTree<T> &src);

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
}


/*
 * Copy constructor of the RedBlackTree
 * Param: reference of a RedBlackTree<T> object
 * Post: all nodeT of the parameter will will be 
 * copied; root pointer will also be set accordingly
 */
template<typename T>
RedBlackTree<T>::RedBlackTree(RedBlackTree<T> &src)
{
	root = copyNode(src->root);
}


/*
 * Destructor of the RedBlackTree
 * Param: none
 * Post: all NodeT will be deleted in order
 */
template<typename T>
RedBlackTree<T> RedBlackTree<T>::operator=(RedBlackTree<T> &src)
{
	if (&src != this)
	{
		if (root != nullptr)
		{
			delete *root;
		}
		root = copyNode(src->root);
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
 */
template<typename T>
bool RedBlackTree<T>::insert(T data)
{
	return false;
}


/* 
 * Pre: RedBlackTree obj need to be created
 * Param: template type parameter to remove
 * Post: returns true and remove node it node containing 
 * data exists; otherwise return false
 */
template<typename T>
bool RedBlackTree<T>::remove(T data)
{
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
		if (i - 1 >= 0 && allVal[i]->data > data)
		{
			return allVal[i - 1]->data;
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
		if (i + 1 < allVal.size() && allVal[i]->data < data)
		{
			return allVal[i + 1]->data;
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
	return inOrderTraversal(this->root).size();
}

