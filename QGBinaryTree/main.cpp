#include <iostream>
#include "QGTreeCalculator.h"

using namespace std;
//����������bug�����ƴ�-.-

void outputdata(CalculateData data)
{
	switch (data.type)
	{
	case DataType::FLOAT:
		cout << static_cast<float> (data.getvalue()) << endl; 
		break;
	case DataType::INT:
		cout << static_cast<int> (data.getvalue()) << endl;
		break;
	case DataType::OPERATOR:
		cout << static_cast<char> (data.getvalue()) << endl;
		break;
	}
}


int main()
{
	cout << "��������ʽ ������������\n�������ָ�ֹͣ" << endl;
	QGTreeCalculator ctr;
	float num;
	char ch[MAX_LEN];
	cin >> ch;
	while (ctr.input(ch))
	{
		if (ctr.output(num))
		{
			ctr.tr(outputdata);
			cout << "�����" << num << endl;
		}
			
		else
			break;
		cin >> ch;
	}
	cout << "�������" << endl;
	

	return 0;
}