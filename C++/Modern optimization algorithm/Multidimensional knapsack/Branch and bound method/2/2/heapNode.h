#include"bbNode.h"
class heapNode
{
public:
	//大根堆默认构造函数
	heapNode() {};
	heapNode(unsigned short int a1, unsigned short int a2, unsigned short int a3,
		unsigned short int a4, unsigned short int a5, unsigned short int a6, unsigned short int a7
		, unsigned char b1, bbNode* b2);
	unsigned short int w1;//当前结点路径的总重量1
	unsigned short int w2;//当前结点路径的总重量2
	unsigned short int w3;//当前结点路径的总重量3
	unsigned short int w4;//当前结点路径的总重量4
	unsigned short int w5;//当前结点路径的总重量5
	unsigned char  level;//当前结点的层数
	unsigned short int upperprofit;//当前结点的利润上限(由背包界定函数(profitBound)计算得到)
	unsigned short int _profit;//当前结点路径的总利润
	bbNode* liveNode;//当前结点对应的记录结点
	//重载操作符，优先队列的排序算法要求
	bool operator<(const heapNode &right) const;
	bool operator>=(const heapNode &right) const;
};

bool heapNode::operator<(const heapNode &right) const
{
	return upperprofit < right.upperprofit;
}

bool heapNode::operator>=(const heapNode &right) const
{
	return upperprofit >= right.upperprofit;
}

//大根堆构造函数的实现
heapNode::heapNode(unsigned short int a1, unsigned short int a2, unsigned short int a3,
	unsigned short int a4, unsigned short int a5, unsigned short int a6, unsigned short int a7
	, unsigned char b1, bbNode* b2)
{
	upperprofit = a1;
	_profit = a2;
	w1 = a3;
	w2 = a4;
	w3 = a5;
	w4 = a6;
	w5 = a7;
	level = b1;
	liveNode = b2;
	//delete[]b2;
};