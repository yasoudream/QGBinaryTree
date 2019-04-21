#include "QGCalculatorTree.h"

bool QGCalculatorTree::push(CalculateData data)
{
	Node* father = nullptr;
	if (m_root != nullptr)
	{
		if (push_main(m_root, father))
		{
			if (father->left == nullptr)
				father->left = new Node(data, nullptr, nullptr);
			else
				father->right = new Node(data, nullptr, nullptr);
			size++;
			return true;
		}
		else
		{
			ERROR_PRINT("输入异常");
			return false;
		}
	}
	m_root = new Node(data, nullptr, nullptr);
	return true;

}

bool QGCalculatorTree::makeout(float & getter)
{
	CalculateData Ngetter;
	Ngetter = CalculateData::zero();
	bool state = makeout_main(Ngetter, m_root);
	if (!state)
		return false;
	getter = Ngetter.getvalue();
	return true;
}

void QGCalculatorTree::clear()
{
	releaseAll(m_root);
	size = 0;
	m_root = nullptr;
}

bool QGCalculatorTree::makeout_main(CalculateData & getter, Node * node)
{
	if (node == nullptr)
	{
		ERROR_PRINT("很多错误");
		return false;
	}
	
	
	float f;	//容器

	switch (node->data.type)
	{
	case DataType::FLOAT :
	case DataType::INT:
		getter = node->data;
		return true;
	case DataType::OPERATOR:
		CalculateData l, r;
		bool lb = makeout_main(l, node->left);
		bool rb = makeout_main(r, node->right);
		if (!lb || !rb)
			return false;
		switch (node->data.oprt)
		{
		case '+':
			f = l.getvalue() + r.getvalue();
			break;
		case '-':
			f = l.getvalue() - r.getvalue();
			break;
		case '*':
			f = l.getvalue() * r.getvalue();
			break;
		case '/':
			if (r.getvalue() == 0)
			{
				ERROR_PRINT("除以零");
				return false;
			}
			f = l.getvalue() / r.getvalue();
			break;
		case '%':
			if (l.type == DataType::FLOAT || r.type == DataType::FLOAT)
			{
				ERROR_PRINT("浮点求余");
				return false;
			}
			f = l.i % r.i;
			break;
		case '^':
			if (l.getvalue() < 0)
			{
				ERROR_PRINT("负数幂运算");
				return false;
			}
			f = powf(l.getvalue(), r.getvalue());
			break;
		default:
			ERROR_PRINT("运算符异常");
			return false;
		}
	}
	int i = static_cast<int> (f);
	if (fabs(f - i) > 1e-6)
		getter = CalculateData::pack(f);
	else
		getter = CalculateData::pack(i);
	return true;
}

bool QGCalculatorTree::push_main(Node* nodep, Node*& father)
{
	
	if (nodep->data.type != DataType::OPERATOR)
		return false;


	if (nodep->left == nullptr)
	{
		father = nodep;
		return true;
	}
	if (push_main(nodep->left, father))
		return true;

	if (nodep->right == nullptr)
	{
		father = nodep;
		return true;
	}
	if (push_main(nodep->right, father))
		return true;
	return false;
}
