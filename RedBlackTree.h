// Include

template<typename T>
class NodeT<T>
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
}

template<typename T>
class RedBlackTree<T>
{
private:
	NodeT	*root;

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

}