#pragma once
template <typename T>
class LinkStack
{
private:
	struct Node
	{
		T data;
		Node* next;
	};

public:
	LinkStack();
	~LinkStack();

	//清空
	void clear(void);
	//是否空
	bool isEmply();
	//获得栈顶元素引用,空栈返回false，getter不变
	bool getTop(T& getter);
	//出栈，空栈返回false
	bool pop();
	//出栈，空栈返回false，getter不变
	bool pop(T& getter);
	//入栈
	void push(T data);
	//栈元素数量
	int size();

private:
	int stackSize;			//当前元素数量
	Node* stackData;			//数据
};

template<typename T>
inline LinkStack<T>::LinkStack()
{
	stackSize = 0;
	stackData = nullptr;
}

template<typename T>
inline LinkStack<T>::~LinkStack()
{
	clear();
}

template<typename T>
inline void LinkStack<T>::clear(void)
{
	stackSize = 0;
	Node* pt = stackData;
	while (pt != nullptr)
	{
		pt = pt->next;
		delete stackData;
		stackData = pt;
	}
}

template<typename T>
inline bool LinkStack<T>::isEmply()
{
	if (stackSize)
		return true;
	return false;
}

template<typename T>
inline bool LinkStack<T>::getTop(T & getter)
{
	if (!stackSize)
		return false;
	getter = stackData->data;
	return true;
}

template<typename T>
inline bool LinkStack<T>::pop()
{
	if (!stackSize)
		return false;
	Node* pt = stackData;
	stackData = stackData->next;
	delete pt;
	stackSize--;
	return true;
}

template<typename T>
inline bool LinkStack<T>::pop(T & getter)
{
	if (!stackSize)
		return false;
	Node* pt = stackData;
	stackData = stackData->next;
	getter = pt->data;
	delete pt;
	stackSize--;
	return true;
}

template<typename T>
inline void LinkStack<T>::push(T data)
{
	Node* pt = new Node;
	pt->data = data;
	pt->next = stackData;
	stackData = pt;
	stackSize++;
}

template<typename T>
inline int LinkStack<T>::size()
{
	return stackSize;
}
