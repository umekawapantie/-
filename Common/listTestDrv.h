/*File name: listTestDrv.h*/

#ifndef COMMON_LISTTESTDRV_H_
#define COMMON_LISTTESTDRV_H_

//����������ݶ��� ��������
typedef struct TestListRec
{
    int value;
}TestListRec_t;

//������㶨�� ��������
typedef struct TestListNode
{
    TestListRec_t data;
    struct TestListNode *next, *prev;
}TestList_Node_t, *TestList_t;

//����Ϊ�գ�������
static void ListTest_Empty();

//��ʼ��������������
static void ListTest_Init();

//����β�巨������,������
static void ListTest_AddTail();

//����ͷ�巨������,������
static void ListTest_AddHead();

//�ͷ�����,������
static void ListTest_Free();

//����������������
static void ListTest_Destroy();

//������������
void List_TestDriver_Entry();


#endif /* COMMON_LISTTESTDRV_H_ */
