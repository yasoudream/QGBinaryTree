#pragma once
#pragma once
template <typename T>
class LinkQueue
{
private:
	struct Node
	{
		T data;
		Node* next;
	};

public:
	LinkQueue();
	~LinkQueue();

	//清空
	void clear(void);
	//是否空
	bool isEmply();
	//获得栈顶元素引用,空栈返回false，getter不变
	bool getfront(T& getter);
	//出栈，空栈返回false
	bool pop();
	//出栈，空栈返回false，getter不变
	bool pop(T& getter);
	//入栈
	void push(T data);
	//栈元素数量
	int size();

private:
	int queueSize;			//当前元素数量
	Node* queueData;			//数据
};

template<typename T>
inline LinkQueue<T>::LinkQueue()
{
	queueSize = 0;
	queueData = nullptr;
}

template<typename T>
inline LinkQueue<T>::~LinkQueue()
{
	clear();
}

template<typename T>
inline void LinkQueue<T>::clear(void)
{
	queueSize = 0;
	Node* pt = queueData;
	while (pt != nullptr)
	{
		pt = pt->next;
		delete queueData;
		queueData = pt;
	}
}

template<typename T>
inline bool LinkQueue<T>::isEmply()
{
	if (queueSize)
		return true;
	return false;
}

template<typename T>
inline bool LinkQueue<T>::getfront(T & getter)
{
	if (!queueSize)
		return false;
	getter = queueData->data;
	return true;
}

template<typename T>
inline bool LinkQueue<T>::pop()
{
	if (!queueSize)
		return false;
	Node* pt = queueData;
	queueData = queueData->next;
	delete pt;
	queueSize--;
	return true;
}

template<typename T>
inline bool LinkQueue<T>::pop(T & getter)
{
	if (!queueSize)
		return false;
	Node* pt = queueData;
	queueData = queueData->next;
	getter = pt->data;
	delete pt;
	queueSize--;
	return true;
}

template<typename T>
inline void LinkQueue<T>::push(T data)
{
	Node* pt = new Node;
	Node** pt2 = &queueData;
	pt->data = data;
	pt->next = nullptr;
	while (*pt2)
	{
		pt2 = &(*pt2)->next;
	}
	*pt2 = pt;
	queueSize++;
}

template<typename T>
inline int LinkQueue<T>::size()
{
	return queueSize;
}

