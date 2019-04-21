#ifndef __QG_BINARY_TREE_H__
#define __QG_BINARY_TREE_H__
#include <queue>
#include <stack>
#include <list>

template <typename T>
class QGBinaryTree
{
public:
	QGBinaryTree();
	virtual  ~QGBinaryTree();


protected:
	struct Node
	{
		T data;				//数据
		//Node* father;		//父节点
		Node* left;			//左节点
		Node* right;		//右节点

		Node() {};
		//带参构造
		Node(T indata, /*Node* infather, */Node* inleft = nullptr, Node* inright = nullptr)
		{
			data = indata;
			//father = infather;
			left = inleft;
			right = inright;
		}
		

		Node operator= (Node n)
		{
			data = n.data;
			//father = n.father;
			left = n.left;
			right = n.right;
			return *this;
		}
	};

protected:
	Node* m_root;		//树根
	int size;			//大小


public:
	//前序遍历
	bool PreOrderTraverse(void(*visit)(T));
	bool PreOrderTraverse_cycle(void(*visit)(T));

	//中序遍历
	bool InOrderTraverse(void (*visit)(T));
	bool InOrderTraverse_cycle(void(*visit)(T));

	//后序遍历
	bool PostOrderTraverse(void (*visit)(T));
	bool PostOrderTraverse_cycle(void(*visit)(T));

	//层次遍历
	bool LevelOrderTraverse(void (*visit)(T));
	bool LevelOrderTraverse_cycle(void(*visit)(T));

	//插入
	virtual bool push(T data) = 0;
	//按引索删除
	virtual bool pop(T data) = 0;

	int getSize() { return size; };

protected:
	//析构辅助函数
	void releaseAll(Node* node);

	/*递归三遍历辅助函数*/
	void pre_main(Node* node, void(*visit)(T));
	void in_main(Node* node, void(*visit)(T));
	void post_main(Node* node, void(*visit)(T));
	void level_main(std::queue<Node*>& nodepQueue, void(*visit)(T));
	
};
template<typename T>
inline QGBinaryTree<T>::QGBinaryTree()
{
	m_root = nullptr;
	size = 0;
}
template<typename T>
inline QGBinaryTree<T>::~QGBinaryTree()
{
	releaseAll(m_root);
}

template<typename T>
bool QGBinaryTree<T>::PreOrderTraverse(void(*visit)(T))
{
	if (m_root == nullptr)
		return false;
	pre_main(m_root, visit);
	return true;
	return false;
}

template<typename T>
inline bool QGBinaryTree<T>::PreOrderTraverse_cycle(void(*visit)(T))
{
	if (m_root == nullptr)
		return false;
	std::stack<Node*> nodepStack;
	nodepStack.push(m_root);
	while (nodepStack.size() > 0)
	{
		Node* node = nodepStack.top();
		nodepStack.pop();
		if (node->right != nullptr)
			nodepStack.push(node->right);
		if (node->left != nullptr)
			nodepStack.push(node->left);
		
		visit(node->data);
	}
	return true;
}

template<typename T>
bool QGBinaryTree<T>::InOrderTraverse(void(*visit)(T))
{
	if (m_root == nullptr)
		return false;
	in_main(m_root, visit);
	return true;
}

template<typename T>
bool QGBinaryTree<T>::InOrderTraverse_cycle(void(*visit)(T))
{
	std::stack<Node*> nodepStack;
	Node* nodep = m_root;

	while (nodep != nullptr || !nodepStack.empty())
	{
		if (nodep->left != nullptr)
		{
			nodepStack.push(nodep);
			nodep = nodep->left;
			continue;
		}
		visit(nodep->data);
		nodep = nodep->right;
		while (nodep == nullptr && !nodepStack.empty())
		{
			nodep = nodepStack.top();
			visit(nodep->data);
			nodepStack.pop();
			nodep = nodep->right;
		}
	}
	return true;

}

template<typename T>
bool QGBinaryTree<T>::PostOrderTraverse(void(*visit)(T))
{
	if (m_root == nullptr)
		return false;
	post_main(m_root, visit);
	return true;
}

template<typename T>
bool QGBinaryTree<T>::PostOrderTraverse_cycle(void(*visit)(T))
{
	if (m_root == nullptr)
		return false;
	std::stack<Node*> nodepStack;
	Node* nodep;
	Node* prep = nullptr;

	nodepStack.push(m_root);
	while (!nodepStack.empty())
	{
		nodep = nodepStack.top();
		if ((nodep->left == nullptr && nodep->right == nullptr) ||
			(prep != nullptr && (nodep->left == prep || nodep->right == prep)))
		{
			visit(nodep->data);
			nodepStack.pop();
			prep = nodep;
			continue;
		}
		if (nodep->right != nullptr)
			nodepStack.push(nodep->right);
		if (nodep->left != nullptr)
			nodepStack.push(nodep->left);
	}
	
}

template<typename T>
void QGBinaryTree<T>::releaseAll(Node * node)
{
	if (node == nullptr)
		return;
	releaseAll(node->left);
	releaseAll(node->right);
	delete node;
}

template<typename T>
void QGBinaryTree<T>::pre_main(Node * node, void(*visit)(T))
{
	if (node == nullptr)
		return;
	visit(node->data);
	pre_main(node->left, visit);
	pre_main(node->right, visit);
}

template<typename T>
void QGBinaryTree<T>::in_main(Node * node, void(*visit)(T))
{
	if (node == nullptr)
		return;
	in_main(node->left, visit);
	visit(node->data);
	in_main(node->right, visit);
}

template<typename T>
void QGBinaryTree<T>::post_main(Node * node, void(*visit)(T))
{
	if (node == nullptr)
		return;
	post_main(node->left, visit);
	post_main(node->right, visit);
	visit(node->data);
}

template<typename T>
void QGBinaryTree<T>::level_main(std::queue<Node*>& nodepQueue, void(*visit)(T))
{
	if (nodepQueue.size() <= 0)
		return;
	Node* node = nodepQueue.front();
	nodepQueue.pop();
	if (node->left != nullptr)
		nodepQueue.push(node->left);
	if (node->right != nullptr)
		nodepQueue.push(node->right);
	visit(node->data);
	level_main(nodepQueue, visit);
}

template<typename T>
bool QGBinaryTree<T>::LevelOrderTraverse(void(*visit)(T))
{
	if (m_root == nullptr)
		return false;

	std::queue<Node*> nodepQueue;
	nodepQueue.push(m_root);
	visit(m_root->data);
	level_main(nodepQueue, visit);
	return true;
}

template<typename T>
bool QGBinaryTree<T>::LevelOrderTraverse_cycle(void(*visit)(T))
{
	if (m_root == nullptr)
		return false;

	std::queue<Node*> nodepQueue;
	nodepQueue.push(m_root);

	while (nodepQueue.size() > 0)
	{
		Node* node = nodepQueue.front();
		nodepQueue.pop();
		if (node->left != nullptr)
			nodepQueue.push(node->left);
		if (node->right != nullptr)
			nodepQueue.push(node->right);
		visit(node->data);
	}
	return true;
}



































#endif


