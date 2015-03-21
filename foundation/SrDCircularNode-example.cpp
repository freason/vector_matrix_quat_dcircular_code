#define CRTDBG_MAP_ALLOC
#include "SrDCircularNode.h"
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h>


//强烈建议不要使用new或者malloc分配内存，用delete或者free释放内存，重载
//createObject()和destroy()方法，可以清晰更加清晰内存的存储和释放情况
//强烈建议不要使用复制构造函数，特别是成员变量存在指针的情况，容易引起异常。

class SrMyListNode:public SrDCircularNode
{
public:
	//重载createObject()方法，根据具体的需要创建相应的对象
	static SrMyListNode* createObject()
	{ 
		SrMyListNode* node = new SrMyListNode();
		node->id = count++;
		node->name = new char[30];
		strcpy(node->name,"SrMyListNode");
		return node;
	}

	//重载destroy()方法，释放内存
	virtual void destroy()
	{ 
		delete[] name;
		SrDCircularNode::destroy();
	}
	int id;
	char* name;

	static int count;
protected:
	SrMyListNode():SrDCircularNode()
	{

	}
	SrMyListNode(SrMyListNode&);
	
};

int SrMyListNode::count = 0;


int main()
{

	SrMyListNode* myNode = SrMyListNode::createObject();

	//初始化一个双向循环链表
	SrMyListNode::initialize(myNode);
	int nodeNum = 0;
	SrMyListNode* tmpNode;
	for( nodeNum = 0 ; nodeNum<10 ; nodeNum++ )
	{
		//创建一个SrMyListNode对象
		tmpNode = SrMyListNode::createObject();
		//如果是偶数，插入头结点后部；如果是奇数，插入头结点前部
		if( nodeNum%2 )
			myNode->insertAfter(tmpNode);
		else
			myNode->insertBefore(tmpNode);
	}
	//遍历双向循环链表，输出结果
	printf("Print List:%d ",myNode->id);
	tmpNode = (SrMyListNode*)myNode->getNextNode();
	while(tmpNode!=myNode)
	{
		printf("%d ",tmpNode->id);
		tmpNode = (SrMyListNode*)tmpNode->getNextNode();
	}
	printf("\n");

	//释放内存

	tmpNode = (SrMyListNode*)myNode->getNextNode();
	//如果SrMyListNode::erase返回false，说是myNode结点是该双向循环链表中的最后一个结点。
	while(SrMyListNode::erase(myNode))
	{
		myNode->destroy();
		myNode = tmpNode;
		tmpNode = (SrMyListNode*)myNode->getNextNode();
	}
	myNode->destroy();

	_CrtDumpMemoryLeaks();
	return 0;
}