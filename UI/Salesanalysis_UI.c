#include "Salesanalysis_UI.h"
#include "list.h"
#include "common.h"
#include "Salesanalysis.h"
#include <conio.h>
#include <stdio.h>
#include "unistd.h"
#include <assert.h>
#include <string.h>

extern account_t gl_CurUser;//外部变量gl_CurUser 用于存储登录用户信息

static const int SALESANALYSIS_PAGE_SIZE = 5;//分页为5

/*
剧院销售排行榜函数,降序显示截止目前剧院电影票房排行榜
*/
void SalesAnalysis_UI_BoxOffice() {
	int i;
	char choice;

	salesanalysis_list_t head;
	salesanalysis_node_t* pos;
	Pagination_t paging;

	List_Init(head, salesanalysis_node_t);
	paging.offset = 0;
	paging.pageSize = SALESANALYSIS_PAGE_SIZE;

	paging.totalRecords = Salesanalysis_Srv_StaticSale(head);//载入数据
	SalesAnalysis_Srv_SortBySale(head);   //根据票房排序

	Paging_Locate_FirstPage(head, paging);
	do {
		printf("\t\t\t=========================================================================\n");
		printf("\t\t\t%28s""票房图表\n");
		printf("\t\t\t-------------------------------------------------------------------------\n");
		printf("\t\t\t剧目名\t\t区域\t\t售票数\t票房\t上映时间\t\t下映时间\n");

		for (i = 0, pos = (salesanalysis_node_t*)(paging.curPos);
			pos != head && i < paging.pageSize; i++) {
			printf("\t\t\t%-10s\t%-10s\t%-5ld\t%-5ld\t%d-%d-%d\t%d-%d-%d\t\n",
				pos->data.name, pos->data.area, pos->data.totaltickets, pos->data.sales,
				pos->data.start_date.year, pos->data.start_date.month, pos->data.start_date.day,
				pos->data.end_date.year, pos->data.end_date.month, pos->data.end_date.day);
			pos = pos->next;
		}
		printf("\t\t\t---------- 共 %2d 项 --------------------------- 第 %2d/%2d 页 --------\n",
			paging.totalRecords, Pageing_CurPage(paging),
			Pageing_TotalPages(paging));
		printf("\t\t\t*************************************************************************\n");
		printf("\t\t\t[P]上一页	|	[N]下一页	|	[R]返回\n");
		printf("\n\t\t\t=========================================================================\n");
		fflush(stdin);
		printf("\t\t\t请选择功能：");
		scanf("%c", &choice);

		switch (choice)
		{
		case 'P':
		case 'p':
			if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, salesanalysis_node_t);
			}
			break;
		case 'N':
		case 'n':
			if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, salesanalysis_node_t);
			}
			break;
		}
	} while (choice != 'R' && choice != 'r');
	List_Destroy(head, salesanalysis_node_t);
}

/*
显示售票员在给定日期区间的售票情况
*/
void SalesAnalysis_UI_StatSale(int usrID, user_date_t stDate, user_date_t endDate) {
	account_t usr;
	int sale_count = 0;
	sale_count = Salesanalysis_Srv_CompSaleVal(usrID, stDate, endDate);    //获取销售员的销售额

	if (!Account_Srv_FetchByID(usrID, &usr)) {
		printf("\t\t\tID不存在!\n请按回车结束\n");
		getchar();
		return;
	}

	printf("\t\t\t================售票员%d的销售情况===================\n", usrID);
	printf("\t\t\t销售开始日期:     %d-%d-%d\n", stDate.year, stDate.month, stDate.day);
	printf("\t\t\t销售截至日期:     %d-%d-%d\n", endDate.year, endDate.month, endDate.day);
	printf("\t\t\t销售额：%d\n", sale_count);
	printf("\t\t\t======================================================\n");

}

/*
统计销售额，票房结合在了一起
*/
void SalesAanalysis_UI_MgtEntry() {

	user_date_t stDate, endDate;
	account_t user;
	char choice;
	do {
		//		printf("根据需求，请输入对应字符：\n\n");
		printf("\t\t\t===============================================\n");
		printf("      \t\t\t[A]剧目票房排行榜\n");
		printf("      \t\t\t[B]查询员工在给定日期区间销售额情况\n");
		printf("      \t\t\t[C]查询员工在给定日期区间售票情况\n");
		printf("\n\t\t\t***********************************************\n");
		printf("\t\t\t[R]返回\n");
		printf("\t\t\t===============================================\n");
		printf("\t\t\t请选择功能：");
		fflush(stdin);
		scanf("%c", &choice);
		switch (choice)
		{
		case 'A':
		case 'a':
			SalesAnalysis_UI_BoxOffice();
			break;
		case 'B':
		case 'b':
			if (gl_CurUser.type == USR_CLERK)
				SalesAnalysis_UI_StatSale(gl_CurUser.id, stDate, endDate);
			else
			{
				printf("\t\t\t请输入售票员姓名：\n");
				fflush(stdin);
				char UsrName[100];
				scanf("%s", UsrName);
				if (!Account_Srv_FetchByName(UsrName, &user))
					printf("\t\t\t不存在该售票员信息\n");
				else
					SalesAnalysis_UI_StatSale(user.id, stDate, endDate);
			}
			break;
		case 'C':
		case 'c':
			if (gl_CurUser.type == USR_MANG)
			{
				char UsrName[100];
				printf("\t\t\t请输入售票员姓名：\n");
				scanf("%s", UsrName);
				fflush(stdin);
				if (!Account_Srv_FetchByName(UsrName, &user))
					printf("不存在该售票员信息\n");
				else
				{
					printf("\t\t\t请输入剧目上映时间:\n");	fflush(stdin);
					scanf("%d-%d-%d", &stDate.year, &stDate.month, &stDate.day);
					printf("\t\t\t请输入剧目结映时间:\n");	fflush(stdin);
					scanf("%d-%d-%d", &endDate.year, &endDate.month, &endDate.day);
					SalesAnalysis_UI_StatSale(user.id, stDate, endDate);
				}
			}
			else
			{
				printf("\t\t\t没有权限操作\n");
				break;
			}
		}
	} while (choice != 'R' && choice != 'r');
}
