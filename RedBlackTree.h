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