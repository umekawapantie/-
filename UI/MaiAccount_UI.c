#include<stdio.h>
#include"./Account_Srv.h"
#include"./List.h"
void MaiAccount_UI_MgtEntry()                          //修改个人信息
{
	account_list_t head;
	List_Init(head, account_node_t);
	Account_Srv_FetchAll(head);
	account_node_t* p=NULL;
	p = (account_node_t*)malloc(sizeof(account_node_t));
	printf("\t\t\t\t=====================Modify personal information=====================\n\n");
	printf("Please input your username:");
	scanf("%s", p->data.username);
	if (Account_Srv_Mod(head, p)) printf("\t\t\t\t^-^Successfully modify!\n");
	else   printf("\t\t\t\t>.<Fail to modify!\n");
}
