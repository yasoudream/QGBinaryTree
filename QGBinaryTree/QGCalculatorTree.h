#ifndef __QG_CALCULATOR_TREE_H__
#define __QG_CALCULATOR_TREE_H__
#include "QGBinaryTree.h"
#include <iostream>
#include <cmath>

#define ERROR_PRINT(data) std::cout << std::endl << "这是一个"<< data <<"触发的错误提示" << std::endl

enum class DataType { FLOAT, INT, OPERATOR };

struct CalculateData
{
	int i;
	float f;
	char oprt;
	DataType type;
	CalculateData() {};
	CalculateData(int data)
	{
		i = data;
		f = 0.0f;
		oprt = 0;
		type = DataType::INT;
	}
	CalculateData(float data)
	{
		i = 0;
		f = data;
		oprt = 0;
		type = DataType::FLOAT;
	}
	CalculateData(char data)
	{
		i = 0;
		f = 0.0f;
		oprt = data;
		type = DataType::OPERATOR;
	}
	CalculateData(int id, float fd, char cd, DataType td)
	{
		i = id;
		f = fd;
		oprt = cd;
		type = td;
	}
	void clear()
	{
		i = 0;
		f = 0;
		oprt = 0;
		type = DataType::INT;
	}
	static CalculateData zero()
	{
		return { 0, 0, 0, DataType::INT };
	}
	//int打包
	static CalculateData pack(int x)
	{
		return { x, 0, 0, DataType::INT };
	}
	//char打包
	static CalculateData pack(char c)
	{
		return { 0, 0, c, DataType::OPERATOR };
	}
	//float打包
	static CalculateData pack(float f)
	{
		return { 0, f, 0, DataType::FLOAT };
	}
	float getvalue()
	{
		switch (type)
		{
		case DataType::OPERATOR:
			return (float)oprt;
		case DataType::FLOAT:
			return f;
		case DataType::INT:
			return (float)i;
		}
	}
	CalculateData operator= (CalculateData data)
	{
		i = data.i;
		f = data.f;
		oprt = data.oprt;
		type = data.type;
		return *this;
	}
};

class QGCalculatorTree : public QGBinaryTree<CalculateData>
{

public:
	QGCalculatorTree() : QGBinaryTree<CalculateData>() {};
	~QGCalculatorTree() { releaseAll(m_root); };

	bool push(CalculateData data);
	//这树没有弹出功能，为了完成接口意思意思
	bool pop(CalculateData data) { return false; };

	bool makeout(float& getter);

	void clear();


private:
	bool makeout_main(CalculateData& getter, Node* node);
	bool push_main(Node* p, Node*& father);
	
};
































#endif // !__QG_CALCULATOR_TREE_H__


