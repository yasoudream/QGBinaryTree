#include <iostream>
#include "QGTreeCalculator.h"

using namespace std;
//可能有隐藏bug，求善待-.-

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
	cout << "请输入表达式 负数请用括号\n输入错误指令即停止" << endl;
	QGTreeCalculator ctr;
	float num;
	char ch[MAX_LEN];
	cin >> ch;
	while (ctr.input(ch))
	{
		if (ctr.output(num))
		{
			ctr.tr(outputdata);
			cout << "结果：" << num << endl;
		}
			
		else
			break;
		cin >> ch;
	}
	cout << "计算结束" << endl;
	

	return 0;
}