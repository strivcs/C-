class bbNode
{
public:
	bbNode* parent;      //父母
	bool leftChild;      //是否为左孩子

	//构造函数
	bbNode(bbNode* theParent, bool theLeftChild)
	{
		parent = theParent;
		leftChild = theLeftChild;
	};
};


