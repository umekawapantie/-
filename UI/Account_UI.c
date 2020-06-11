#include<stdio.h>
#include"./List.h"
#include"./Account_UI.h"
#include"./Account_Srv.h"
#include"./Account_Perst.h"
void Account_UI_MgtEntry()//系统用户管理界面
{	
	char choice;
	do {
		
		int i;
		account_list_t head;
		account_node_t* pos;
		List_Init(head, account_node_t);
		Pagination_t paging;
		paging.offset = 0; paging.pageSize = 10;
		paging.totalRecords = Account_Srv_FetchAll(head);
		Paging_Locate_FirstPage(head, paging);
		printf("\t\t\t\t--------------------------------------------------------------\n\n");
		Paging_ViewPage_ForEach(head, paging, account_node_t, pos, i)
		{
             printf("\t\t\t\t       ID  :  %d        Name  :  %s        Type  :  %s", pos->data.id,pos->data.username,pos->data.type);
		}
		
		printf("\t\t\t\t---------------------------------------------------------%d/%d\n\n",Pageing_CurPage(paging), Pageing_TotalPages(paging));
		printf("\t\t\t\t========================Manage users==========================\n\n\n");
		printf("\t\t\t\t\t  Add user     [A]   Modify password  [M]\n\n");
		printf("\t\t\t\t\t  Delete user  [D]   Quest information   [Q]\n\n\n");
		printf("\t\t\t\t\t  Change other information[C]");
		printf("\t\t\t\tPre_Page[P]-----------------Exit[R]---------------Next_Page[N]\n");
		printf("\t\t\t\t==============================================================\n");
		printf("\t\t\t\tPlease input your choice:");
		fflush(stdin);
		scanf("%c", &choice);
		switch (choice)
		{
			case 'A':case'a': Account_UI_Add(head); break; 
			case 'M':case'm': Account_UI_Mod(head); break; 
			case 'D':case'd': Account_UI_Del(head); break; 
			case 'Q':case'q': Account_UI_Que(head); break;
			case'C':case'c':Account_UI_Change(head); break;
			case 'P':case'p':
				if (!(Pageing_IsLastPage(paging)))
				    Paging_Locate_OffsetPage(head, paging, -1, account_node_t);//?
				break;
			case 'N':case'n':
				if (!(Pageing_IsFirstPage(paging)))
				    Paging_Locate_OffsetPage(head, paging, 1, account_node_t);//?
				break;
			case 'R':case'r':List_Destroy(head,account_node_t); break;
		    default:
			    printf(">.<Sorry,your input is wrong!");
		}
	} while (choice != 'R'&&choice!='r');
}
int Login()//系统用户登录
{
	printf("\t\t\t\t============================Login=============================\n\n");
	if (Account_Srv_VerifyLog())
	{
		printf("\t\t\t\t^-^Successfully Login!\n");
		return 1;
	}
	printf("\t\t\t\t>.<Fail to Login!\n");
	return 0;
}
void Account_UI_Add(account_list_t head)//注册账号
{
	printf("\t\t\t\t=============================Add user=============================\n\n");
	if (Account_Srv_Add(head)) printf("\t\t\t\t^-^Successfully add!\n");
	else   printf("\t\t\t\t>.<Fail to add!\n");
}
void Account_UI_Mod(account_list_t head)//修改密码
{
	account_node_t* p = NULL;
	p = (account_node_t*)malloc(sizeof(account_node_t));
	printf("\t\t\t\t=========================Modify password======================\n\n");
	printf("Please input the username:");
	scanf("%s", p->data.username);
	if (!Account_Perst_VerifyExit(p))
	{
		printf(">.<The user isn't exist!");
	}
	else
	{
		if (Account_Srv_Mod(head,p)) printf("\t\t\t\t^-^Successfully modify!\n");
		else   printf("\t\t\t\t>.<Fail to modify!\n");
	}
}
void Account_UI_Del(account_list_t head)//注销账号
{
	printf("\t\t\t\t============================Delete user===========================\n\n");
	if (Account_Srv_DelByID(head)) printf("\t\t\t\t^-^Successfully delete!\n");
	else   printf("\t\t\t\t>.<Fail to delete!\n");
}

void Account_UI_Que(account_list_t head)//查询信息
{
	account_node_t* p;
	printf("\t\t\t\t==========================Quest information========================\n\n");
	printf("Please input the username:");
	scanf("%s", p->data.username);
	p = Account_FindByUserName(head, p->data.username);
	if ( p== NULL)
		printf("\t\t\t\t>.<Fail to quest!\n");
	else
	{
		printf("ID: %dt UserName:%s Password:%s Telephone:%s",p->data.id, p->data.username, p->data.password, p->data.telnumber);
	}
}
void Account_UI_Change(account_list_t head)//修改其他信息
{
	account_node_t* p = NULL;
	p = (account_node_t*)malloc(sizeof(account_node_t));
	printf("\t\t\t\t==========================Change information========================\n\n");
	printf("Please input the username:");
	scanf("%s", p->data.username);
	if (!Account_Perst_VerifyExit(p))
	{
		printf(">.<The user isn't exist!");
	}
	else
	{
		if (Account_Srv_Change(head,p)) printf("\t\t\t\t^-^Successfully modify!\n");
		else   printf("\t\t\t\t>.<Fail to modify!\n");
	}

}
