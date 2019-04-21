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

	bool pretr(void(*visit)(CalculateData)) { return tree.PreOrderTraverse(visit); }
	bool intr(void(*visit)(CalculateData)) { return tree.InOrderTraverse(visit); }
	bool posttr(void(*visit)(CalculateData)) { return tree.PostOrderTraverse(visit); }
	bool leveltr(void(*visit)(CalculateData)) { return tree.LevelOrderTraverse(visit); }
	bool pretrc(void(*visit)(CalculateData)) { return tree.PreOrderTraverse_cycle(visit); }
	bool intrc(void(*visit)(CalculateData)) { return tree.InOrderTraverse_cycle(visit); }
	bool posttrc(void(*visit)(CalculateData)) { return tree.PostOrderTraverse_cycle(visit); }
	bool leveltrc(void(*visit)(CalculateData)) { return tree.LevelOrderTraverse_cycle(visit); }


};









































#endif // !__QG_TREE_CALCULATOR_H__



