#include"bbNode.h"
class heapNode
{
public:
	//�����Ĭ�Ϲ��캯��
	heapNode() {};
	heapNode(unsigned short int a1, unsigned short int a2, unsigned short int a3,
		unsigned short int a4, unsigned short int a5, unsigned short int a6, unsigned short int a7
		, unsigned char b1, bbNode* b2);
	unsigned short int w1;//��ǰ���·����������1
	unsigned short int w2;//��ǰ���·����������2
	unsigned short int w3;//��ǰ���·����������3
	unsigned short int w4;//��ǰ���·����������4
	unsigned short int w5;//��ǰ���·����������5
	unsigned char  level;//��ǰ���Ĳ���
	unsigned short int upperprofit;//��ǰ������������(�ɱ����綨����(profitBound)����õ�)
	unsigned short int _profit;//��ǰ���·����������
	bbNode* liveNode;//��ǰ����Ӧ�ļ�¼���
	//���ز����������ȶ��е������㷨Ҫ��
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

//����ѹ��캯����ʵ��
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