class bbNode
{
public:
	bbNode* parent;      //��ĸ
	bool leftChild;      //�Ƿ�Ϊ����

	//���캯��
	bbNode(bbNode* theParent, bool theLeftChild)
	{
		parent = theParent;
		leftChild = theLeftChild;
	};
};


