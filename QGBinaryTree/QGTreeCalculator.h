#ifndef __QG_TREE_CALCULATOR_H__
#define __QG_TREE_CALCULATOR_H__
#include "QGCalculatorTree.h"
#include "LinkStack.h"
#include "LinkQueue.h"

#include <cstring>

constexpr auto MAX_LEN = 1000;

class QGTreeCalculator
{
private:
	//计算树
	QGCalculatorTree tree;

	//算式储存
	LinkStack<CalculateData> mdataStack;//中缀表达式队列，输出正好从后开始
	LinkStack<CalculateData> pdataStack;//前缀缀表达式栈，输出正好按顺序
	LinkStack<CalculateData> tdataStack;//中间转换栈


public:
	QGTreeCalculator();
	~QGTreeCalculator();

	bool input(const char* equ);
	bool output(float& Rgetter);

	bool tr(void(*visit)(CalculateData))
	{
		return tree.InOrderTraverse_cycle(visit);
	}
};









































#endif // !__QG_TREE_CALCULATOR_H__



