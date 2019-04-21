#include <iostream>
#include <conio.h>
#include "QGTreeCalculator.h"

using namespace std;
//����������bug�����ƴ�-.-

void outputdata(CalculateData data)
{
	switch (data.type)
	{
	case DataType::FLOAT:
		cout << static_cast<float> (data.getvalue()) << ' '; 
		break;
	case DataType::INT:
		cout << static_cast<int> (data.getvalue()) << ' ';
		break;
	case DataType::OPERATOR:
		cout << static_cast<char> (data.getvalue()) << ' ';
		break;
	}
}


int main()
{
	char c = 0;
	bool (QGTreeCalculator::*func)(void(*visit)(CalculateData));
	func = nullptr;
	QGTreeCalculator ctr;
	while (c > '8' || c < '1')
	{
		cout << "�������ģʽ 1~4 ǰ�����򡢺��򡢲�α���" << endl;
		cout << "             5~8 ����������ѭ����" << endl;
		c = _getch();
	}
	switch (c)
	{
	case '1':
		func = &QGTreeCalculator::pretr;
		break;
	case '2':
		func = &QGTreeCalculator::intr;
		break;
	case '3':
		func = &QGTreeCalculator::posttr;
		break;
	case '4':
		func = &QGTreeCalculator::leveltr;
		break;
	case '5':
		func = &QGTreeCalculator::pretrc;
		break;
	case '6':
		func = &QGTreeCalculator::intrc;
		break;
	case '7':
		func = &QGTreeCalculator::posttrc;
		break;
	case '8':
		func = &QGTreeCalculator::leveltrc;
		break;
	}


	system("cls");

	cout << "��������ʽ ������������\n�������ָ�ֹͣ" << endl;
	
	float num;
	char ch[MAX_LEN];
	cin >> ch;
	while (ctr.input(ch))
	{
		if (ctr.output(num))
		{
			cout << "�������" << endl;
			(ctr.*func)(outputdata);
			putchar('\n');
			cout << "�����" << num << endl;
		}
			
		else
			break;
		cin >> ch;
	}
	cout << "�������" << endl;
	

	return 0;
}