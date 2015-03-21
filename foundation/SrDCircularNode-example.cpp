#define CRTDBG_MAP_ALLOC
#include "SrDCircularNode.h"
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h>


//ǿ�ҽ��鲻Ҫʹ��new����malloc�����ڴ棬��delete����free�ͷ��ڴ棬����
//createObject()��destroy()�����������������������ڴ�Ĵ洢���ͷ����
//ǿ�ҽ��鲻Ҫʹ�ø��ƹ��캯�����ر��ǳ�Ա��������ָ�����������������쳣��

class SrMyListNode:public SrDCircularNode
{
public:
	//����createObject()���������ݾ������Ҫ������Ӧ�Ķ���
	static SrMyListNode* createObject()
	{ 
		SrMyListNode* node = new SrMyListNode();
		node->id = count++;
		node->name = new char[30];
		strcpy(node->name,"SrMyListNode");
		return node;
	}

	//����destroy()�������ͷ��ڴ�
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

	//��ʼ��һ��˫��ѭ������
	SrMyListNode::initialize(myNode);
	int nodeNum = 0;
	SrMyListNode* tmpNode;
	for( nodeNum = 0 ; nodeNum<10 ; nodeNum++ )
	{
		//����һ��SrMyListNode����
		tmpNode = SrMyListNode::createObject();
		//�����ż��������ͷ���󲿣����������������ͷ���ǰ��
		if( nodeNum%2 )
			myNode->insertAfter(tmpNode);
		else
			myNode->insertBefore(tmpNode);
	}
	//����˫��ѭ������������
	printf("Print List:%d ",myNode->id);
	tmpNode = (SrMyListNode*)myNode->getNextNode();
	while(tmpNode!=myNode)
	{
		printf("%d ",tmpNode->id);
		tmpNode = (SrMyListNode*)tmpNode->getNextNode();
	}
	printf("\n");

	//�ͷ��ڴ�

	tmpNode = (SrMyListNode*)myNode->getNextNode();
	//���SrMyListNode::erase����false��˵��myNode����Ǹ�˫��ѭ�������е����һ����㡣
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