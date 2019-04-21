#include "QGTreeCalculator.h"

QGTreeCalculator::QGTreeCalculator()
{
	mdataStack.clear();
	pdataStack.clear();
	tdataStack.clear();
	tree.clear();
}

QGTreeCalculator::~QGTreeCalculator()
{
	mdataStack.clear();
	pdataStack.clear();
	tdataStack.clear();
	tree.clear();
}

bool QGTreeCalculator::input(const char * equ)
{
	mdataStack.clear();
	pdataStack.clear();
	tdataStack.clear();
	tree.clear();
	if (strlen(equ) > MAX_LEN || strlen(equ) < 1)
	{
		ERROR_PRINT("��ʽ�����쳣");
		return false;
	}
	int index = 0;

	int idata = 0;			//int��ת
	float fdata = 0;		//float��ת

	float pointcount = 10;	//�����λ
	bool isInt = true;		//��int��

	if (equ[index] >= '0' && equ[index] <= '9')//���ִ���
	{
		if (isInt)
		{
			idata *= 10;
			idata += equ[index] - '0';
			//idata += (equ[index] - '0') * 10;
			//pointcount *= 10;
		}
		else
		{
			fdata += (equ[index] - '0') / pointcount;
		}

	}
	else
	{
		switch (equ[index])
		{
		case '(':
			mdataStack.push(CalculateData::pack('('));
			break;
		default:
			ERROR_PRINT("�ַ��쳣");
			return false;
			break;
		}
	}



	index++;

	while (equ[index] != '\0')
	{
		if (equ[index] >= '0' && equ[index] <= '9')//���ִ���
		{
			if (isInt)
			{
				idata *= 10;
				idata += equ[index] - '0';
				
			}
			else
			{
				fdata += (equ[index] - '0') / pointcount;
				pointcount /= 10;
			}

		}
		//����
		else if (equ[index] == '+' || equ[index] == '-' ||
			equ[index] == '*' || equ[index] == '/' ||
			equ[index] == '(' || equ[index] == ')' ||
			equ[index] == '%' || equ[index] == '^')
		{
			//������ź����Ǹ����֣������ִ������
			if (equ[index - 1] >= '0' && equ[index -+- 1] <= '9')
			{
				if (isInt)//�������
				{
					mdataStack.push(CalculateData::pack(idata));
				}
				else//���������
				{
					mdataStack.push(CalculateData::pack(fdata));
				}
				//����
				isInt = true;
				fdata = 0;
				idata = 0;
				pointcount = 10;
			}
			//���������������
			switch (equ[index])
			{
			case '+':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//Ӧ���Ǹ������Ӻ�
				{
					mdataStack.push(CalculateData::pack('+'));
				}
				else//��Ӻ��е�ë��
				{
					ERROR_PRINT("�Ӻ��쳣");
					return false;
				}
				break;

			case '-':
				if (equ[index - 1] == '(')//����ʯ����
				{
					mdataStack.push(CalculateData::zero());//����0��ǰ��
					mdataStack.push(CalculateData::pack('-'));
				}
				else if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//Ӧ���Ǹ���������
				{
					mdataStack.push(CalculateData::pack('-'));
				}
				else//������е�ë��
				{
					ERROR_PRINT("�����쳣");
					return false;
				}
				break;

			case '*':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//Ӧ���Ǹ������˺�
				{
					mdataStack.push(CalculateData::pack('*'));
				}
				else//��˺��е�ë��
				{
					ERROR_PRINT("�˺��쳣");
					return false;
				}
				break;
			case '/':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//Ӧ���Ǹ���������
				{
					mdataStack.push(CalculateData::pack('/'));
				}
				else//������е�ë��
				{
					ERROR_PRINT("�����쳣");
					return false;
				}
				break;
				//����һ��û���������м����
			case '(':
				mdataStack.push(CalculateData::pack('('));
				break;
			case ')':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//Ӧ���Ǹ���������
				{
					mdataStack.push(CalculateData::pack(')'));
				}
				else//�������е�ë��
				{
					ERROR_PRINT("�����쳣");
					return false;
				}
				break;

			case '%':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//Ӧ���Ǹ�������ģ
				{
					mdataStack.push(CalculateData::pack('%'));
				}
				else//����ģ�е�ë��
				{
					ERROR_PRINT("�����쳣");
					return false;
				}
				break;

				break;
			case '^':

				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//Ӧ���Ǹ�����������
				{
					mdataStack.push(CalculateData::pack('^'));
				}
				else//���������е�ë��
				{
					ERROR_PRINT("�������쳣");
					return false;
				}
				break;

			default:
				break;
			}
		}
		else if (equ[index] == '.')//С����
		{
			if (equ[index - 1] >= '0' && equ[index - 1] <= '9' && equ[index + 1] >= '0' && equ[index + 1] <= '9')
			{
				isInt = false;
				fdata = idata;
				idata = 0;
				pointcount = 10;
			}
			else
			{
				ERROR_PRINT("С�����쳣");
				return false;
			}
		}
		else
		{
			ERROR_PRINT("�ַ��쳣");
			return false;
		}
		index++;
	}


	if (equ[index - 1] >= '0' && equ[index - 1] <= '9')
	{
		//���Ĵ��
		if (isInt)//�������
		{
			mdataStack.push(CalculateData::pack(idata));
		}
		else//���������
		{
			mdataStack.push(CalculateData::pack(fdata));
		}
		//����
		isInt = true;
		fdata = 0;
		idata = 0;
		pointcount = 10;
	}
	return true;
}




bool QGTreeCalculator::output(float& Rgetter)
{
	CalculateData getter, topgetter;//��ȡ���ݵ�����
	getter.clear();//��ʼ��
	topgetter.clear();

	while (mdataStack.pop(getter))
	{
		switch (getter.type)
		{
			//������ֱ�����
		case DataType::FLOAT:
		case DataType::INT:
			pdataStack.push(getter);
			break;
			//����������
		case DataType::OPERATOR:
			switch (getter.oprt)
			{
			case ')':
				tdataStack.push(getter);
				break;

			case '(':
				while (true)
				{
					if (!tdataStack.pop(topgetter))
					{
						ERROR_PRINT("�������쳣");
						return false;
					}
					if (topgetter.oprt == ')')
						break;
					pdataStack.push(topgetter);
				}
				break;

			case '^':
				while (tdataStack.getTop(topgetter))
				{
					if (topgetter.oprt != '^')
						break;
					tdataStack.pop(topgetter);
					pdataStack.push(topgetter);
				}
				tdataStack.push(getter);
				break;

			case '/':
			case '*':
			case '%':
				while (tdataStack.getTop(topgetter))
				{
					if (topgetter.oprt == '+' || topgetter.oprt == '-' || topgetter.oprt == ')')
						break;
					tdataStack.pop(topgetter);
					pdataStack.push(topgetter);
				}
				tdataStack.push(getter);
				break;

			case '+':
			case '-':
				while (tdataStack.getTop(topgetter))
				{
					if (topgetter.oprt == ')')
						break;
					tdataStack.pop(topgetter);
					pdataStack.push(topgetter);
				}
				tdataStack.push(getter);
				break;

			default:
				break;
			}

		default:
			break;
		}
	}

	while (tdataStack.pop(getter))
	{
		if (getter.oprt == ')')
		{
			ERROR_PRINT("�������쳣");
			return false;
		}
		pdataStack.push(getter);
	}

	while (pdataStack.pop(getter))
	{
		if (!tree.push(getter))
		{
			ERROR_PRINT("¼���쳣");
			return false;
		}
	}
	float fget;
	if (!tree.makeout(fget))
	{
		ERROR_PRINT("�����쳣");
		return false;
	}
	Rgetter = fget;
	return true;
}