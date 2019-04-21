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
	//������
	QGCalculatorTree tree;

	//��ʽ����
	LinkStack<CalculateData> mdataStack;//��׺���ʽ���У�������ôӺ�ʼ
	LinkStack<CalculateData> pdataStack;//ǰ׺׺���ʽջ��������ð�˳��
	LinkStack<CalculateData> tdataStack;//�м�ת��ջ


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



