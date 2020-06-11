#include<stdio.h>
#include<stdlib.h>
#include"./Account_UI.h"
#include"./Account_Srv.h"
#include"./List.h"
void Main_Menu(void) {
	char choice;
	int ch, m, pass = 0;//登录
	printf("\t\t\t\t======================welcome to LLMZ ciname==================\n\n");
	printf("\t\t\t\tDo you have account?                    Yes[1] / No[0]\n\n");
	printf("\t\t\t\t==============================================================\n");
	printf("\t\t\t\t");
	printf("\t\t\t\tPlease input your choice:");
	scanf("%d", &ch);
	account_list_t head;
	account_node_t* temp;
	List_Init(head, account_node_t);
	if (!ch)
	{		
		Account_UI_Add(head);
	}
	if (Login()) pass = 1;
	if (pass)//登陆通过执行功能
	{
		printf("Please input your username again:");
		scanf("%s",temp->data.username);
		temp=Account_FindByUserName(head,temp->data.username);
		do {
			printf("\t\t\t\t=======================welcome to LLMZ ciname=====================\n\n");
			printf("\t\t\t\t [S]Studio Management.\t\t\t");
			printf("[P]Play Management.\n\n");
			printf("\t\t\t\t [T]Ticket Sale.\t\t\t");
			printf("[R]Return Ticket.\n\n");
			printf("\t\t\t\t [Q]Queries\t\t\t\t");
			printf("[N]Ranking and Statistics.\n\n");
			printf("\t\t\t\t [A]Account Management.\t\t\t");
			printf("[I] Personal information.\n\n");
			printf("\t\t\t\t [E]Exist.\n\n");
			printf("\t\t\t\t===================================================================\n");
			printf("Please input your choice:");
			fflush(stdin);
			choice = getchar();
			switch (choice)
			{
			case 'S':
			case 's':
				if (temp->data.type == 9)
					Studio_UI_MgtEntry();//影院管理
				else printf("Sorry!You don't have access!");
				break;
			case 'P':
			case 'p':
				if(temp->data.type==2)
				    Play_UI_MgtEntry();//演出安排
				else printf("Sorry!You don't have access!");
				break;
			case 'Q':
			case 'q':
				if (temp->data.type == 1||temp->data.type==2)
				   Queries_Menu();//查询票务信息
				break;
			case 'T':
			case 't':
				if(temp->data.type==1)
				    Sale_UI_MgtEntry();//售票管理
				else printf("Sorry!You don't have access!");
				break;
			case 'R':
			case 'r':
				if (temp->data.type == 1)
				    Sale_UI_ReturnTicket();//退票管理
				else printf("Sorry!You don't have access!");
				break;
			case 'N':
			case 'n':
				if (temp->data.type == 1||temp->data.type==2)
				   SalesAanalysis_UI_MgtEntry();//统计销售额
				else printf("Sorry!You don't have access!");
				break;
			case 'A':
			case 'a':
				if(temp->data.type==9)
				    Account_UI_MgtEntry();//系统用户管理
				else printf("Sorry!You don't have access!");
				break;
			case 'I':
			case 'i':
				MaiAccount_UI_MgtEntry();//维护个人信息
			}
		} while ('E' != choice && 'e' != choice);
	}
	else
	{
		printf("Sorry!You don't have access!");
	}
}


