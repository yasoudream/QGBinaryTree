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
		ERROR_PRINT("算式长度异常");
		return false;
	}
	int index = 0;

	int idata = 0;			//int中转
	float fdata = 0;		//float中转

	float pointcount = 10;	//浮点记位
	bool isInt = true;		//是int？

	if (equ[index] >= '0' && equ[index] <= '9')//数字处理
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
			ERROR_PRINT("字符异常");
			return false;
			break;
		}
	}



	index++;

	while (equ[index] != '\0')
	{
		if (equ[index] >= '0' && equ[index] <= '9')//数字处理
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
		//运算
		else if (equ[index] == '+' || equ[index] == '-' ||
			equ[index] == '*' || equ[index] == '/' ||
			equ[index] == '(' || equ[index] == ')' ||
			equ[index] == '%' || equ[index] == '^')
		{
			//如果符号后面是个数字，将数字打包放入
			if (equ[index - 1] >= '0' && equ[index -+- 1] <= '9')
			{
				if (isInt)//整数打包
				{
					mdataStack.push(CalculateData::pack(idata));
				}
				else//浮点数打包
				{
					mdataStack.push(CalculateData::pack(fdata));
				}
				//重置
				isInt = true;
				fdata = 0;
				idata = 0;
				pointcount = 10;
			}
			//对运算符单个处理
			switch (equ[index])
			{
			case '+':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//应该是个正常加号
				{
					mdataStack.push(CalculateData::pack('+'));
				}
				else//这加号有点毛病
				{
					ERROR_PRINT("加号异常");
					return false;
				}
				break;

			case '-':
				if (equ[index - 1] == '(')//负号石锤了
				{
					mdataStack.push(CalculateData::zero());//丢个0到前面
					mdataStack.push(CalculateData::pack('-'));
				}
				else if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//应该是个正常减号
				{
					mdataStack.push(CalculateData::pack('-'));
				}
				else//这减号有点毛病
				{
					ERROR_PRINT("减号异常");
					return false;
				}
				break;

			case '*':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//应该是个正常乘号
				{
					mdataStack.push(CalculateData::pack('*'));
				}
				else//这乘号有点毛病
				{
					ERROR_PRINT("乘号异常");
					return false;
				}
				break;
			case '/':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//应该是个正常除号
				{
					mdataStack.push(CalculateData::pack('/'));
				}
				else//这除号有点毛病
				{
					ERROR_PRINT("除号异常");
					return false;
				}
				break;
				//这是一堆没有做错误的屑代码
			case '(':
				mdataStack.push(CalculateData::pack('('));
				break;
			case ')':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//应该是个正常括号
				{
					mdataStack.push(CalculateData::pack(')'));
				}
				else//这括号有点毛病
				{
					ERROR_PRINT("括号异常");
					return false;
				}
				break;

			case '%':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//应该是个正常求模
				{
					mdataStack.push(CalculateData::pack('%'));
				}
				else//这求模有点毛病
				{
					ERROR_PRINT("求余异常");
					return false;
				}
				break;

				break;
			case '^':

				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//应该是个正常幂运算
				{
					mdataStack.push(CalculateData::pack('^'));
				}
				else//这幂运算有点毛病
				{
					ERROR_PRINT("幂运算异常");
					return false;
				}
				break;

			default:
				break;
			}
		}
		else if (equ[index] == '.')//小数点
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
				ERROR_PRINT("小数点异常");
				return false;
			}
		}
		else
		{
			ERROR_PRINT("字符异常");
			return false;
		}
		index++;
	}


	if (equ[index - 1] >= '0' && equ[index - 1] <= '9')
	{
		//最后的打包
		if (isInt)//整数打包
		{
			mdataStack.push(CalculateData::pack(idata));
		}
		else//浮点数打包
		{
			mdataStack.push(CalculateData::pack(fdata));
		}
		//重置
		isInt = true;
		fdata = 0;
		idata = 0;
		pointcount = 10;
	}
	return true;
}




bool QGTreeCalculator::output(float& Rgetter)
{
	CalculateData getter, topgetter;//提取数据的容器
	getter.clear();//初始化
	topgetter.clear();

	while (mdataStack.pop(getter))
	{
		switch (getter.type)
		{
			//运算数直接输出
		case DataType::FLOAT:
		case DataType::INT:
			pdataStack.push(getter);
			break;
			//运算符分情况
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
						ERROR_PRINT("左括号异常");
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
			ERROR_PRINT("左括号异常");
			return false;
		}
		pdataStack.push(getter);
	}

	while (pdataStack.pop(getter))
	{
		if (!tree.push(getter))
		{
			ERROR_PRINT("录入异常");
			return false;
		}
	}
	float fget;
	if (!tree.makeout(fget))
	{
		ERROR_PRINT("计算异常");
		return false;
	}
	Rgetter = fget;
	return true;
}