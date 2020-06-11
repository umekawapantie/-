#include"../Common/List.h"
#include"Account_UI.h"
#include "Play_UI.h"
#include "Schedule_UI.h"
#include "Sale_UI.h"
#include "Ticket_UI.h"
#include "../Service/Ticket.h"
#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Service/Sale.h"
#include "../Service/Play.h"
#include "../Service/Schedule.h"
#include "./Seat_UI.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
static const int pagesize=5; 




/*TTMs_SCU_Sale_UI_MgtEnt
参数：无  返回值：无
功能：管理售票的主界面*/
void Sale_UI_MgtEntry()
{
	if(Account_Perst_SaleLogIn(p)==0){
		return ;
		}
	system("clear");
	int  i,id;
	char choice;
	
	play_list_t head;
	play_node_t *pos;
	Pagination_t paging;
	List_Init(pos,play_node_t);//初始化剧目链表
	Pagination_t paging;
	paging.offset=0;
	paging.pageSize=SALESANALYSIS_PAGE_SIZE;
	paging.totalRecords = Play_Srv_FetchAll(head);//通过Play_Srv_FetchAll()的返回值设置分页总记录数 
	Paging_Locate_FirstPage(head, paging); 
	
	do
	{
		system("clear");
		printf("\n\t\t=======================================================================\n");
		printf("\n============================Play information===============================\n");//剧目信息 
		printf("\t\t%5s %15s  %9s  %5s  %20s   %10s\n", "Movie ID", "name", "area",
				"time", "Start date->End date","price");
		//显示数据
		Paging_ViewPage_ForEach(head, paging, play_node_t, pos, i)
		{
			printf("\t\t%5d %8s  %9s  %5d  %d/%d/%d->%d/%d/%d  %5d\n", pos->data.id,pos->data.name,pos->data.area,pos->data.duration,
			pos->data.start_date.year,pos->data.start_date.month,pos->data.start_date.day,pos->data.end_date.year,
			pos->data.end_date.month,pos->data.end_date.day,pos->data.price);
	    }
			
            printf(	"------- %2d in total -------------------------------- page :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));

		printf("\n\n\n\n"); 

		printf("-------------Total:%2d -------------- Page %2d/%2d --------------------\n",

				paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
		printf("\n=================================================================");
		printf("*******************************************************************\n");
        printf("\t\t[C]Play Scheduler       [S]Search movie name  \n");
        printf("\t\t[F]Search movie ticket  [P]Previous page  \n ");
        printf("\t\t[N]Next page            [R]Exit   \n");
	
		printf("\n===================================================================\n");
		printf("\t\tPlease input you choice:");
		fflush(stdin);
		scanf("%c",&choice);
		//char name[64];
		switch(choice){
			    case 'C':
				case 'c':{
					printf("Please enter the play ID：");//请输入剧目id
			        scanf("%d",&id);
					Sale_UI_ShowScheduler(id);}
					break;
				
				case 'S':
				case 's':
					//暂时没找到这个函数，不知道参数情况 
					Play_UI_FetchByName();
					break;
					
				case 'F':
				case 'f':
					Play_Srv_FilterByName();
					break;
					
				case 'p':
				case 'P':	
					if(!Paging_IsFirstPage(paging))
					Paging_Locate_OffsetPage(h, paging, -1, play_node_t);
					break;

				case 'N':
				case 'n':
					if(!Paging_IsLastPage(paging))
					Paging_Locate_OffsetPage(h, paging, 1, play_node_t);
					break;
		}	

	}while(choice!='e'&&choice!='E'); 
	List_Destroy(head, play_node_t);	
 } 
 
 
 
 
 /*TTMs_SCU_Sale_UI_ShowSchedule
参数：playID为整型，表示要查询的剧目ID  返回值：无 
功能根据剧目ID显示演出计划*/
void Sale_UI_ShowScheduler(int playID)
{
	int i;
	play_t buf;
	i=Play_Srv_FetchByID(playID,&buf);
	if(i==0)
	{
		printf("The play ID does not exist");//此剧目id不存在
		return;
	}
	
	List_Init(flag, schedule_node_t);
	
	schedule_list_t flag;
	Schedule_Srv_FetchByPlay(flag,playID); //flag为剧目id所对应的所有演出计划链表
    Pagination_t paging;
	int len = 0;
	List_ForEach(flag,pos)
	{
		len++;
	}
	paging.offset = 0;
	paging.pageSize = SALESANALYSIS_PAGE_SIZE;
	paging.totalRecords = len;
	Paging_Locate_FirstPage(flag, paging);

    schedule_list_t pos;

	char choice;
	do{     
	system("clear");
	printf("\n=======================================================================\n");
	printf("\n========================Performance plan information==========================\n");//演出计划信息 
	printf("\t\t%8s %8s  %8s  %8s  %8s %8s\n", "Scheduler  ID", "Play ID", "Hall ID",
				"Date", "Time","Seat");// 演出计划ID，上映剧目ID ，演出厅ID ,放映日期, 放映时间,座位数
				
	Paging_ViewPage_ForEach(flag, paging, schedule_node_t, pos, i){
	    printf("\t\t%8d %8d  %8d  %d/%d/%d  %d/%d/%d %8d \n", pos->data.id,
					pos->data.play_id, pos->data.studio_id, pos->data.date.year,
					pos->data.date.month,pos->data.date.day,pos->data.time.hour,
					pos->data.time.minute,pos->data.time.second,pos->data.seat_count);	
       	}
	printf(	"------- %2d in total -------------------------------- page :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));

	
	printf("\n\n=================================================================");
	printf("*******************************************************************\n");
	printf("\t\t[P]Previous page  [T]Show tickets  [N]Next page  \n");
	printf("\n*******************************************************************\n\n");
	printf("\t\tPlease choice :\n");
	fflush(stdin);
	scanf("%c",&choice);
	int a;
	switch(choice)
	{
	   		case 't':
			case 'T':{
			system("clear");
				printf("请输入演出计划id：");
				scanf("%d",&a);
				Sale_UI_ShowTicket(a);}//传入演出计划id，获取票
				break;
				
			case 'p':
			case 'P':
				system("clear");
				if (!Pageing_IsFirstPage(paging)) {
					Paging_Locate_OffsetPage(flag, paging, -1, schedule_node_t);
				}
				break;

			case 'n':
			case 'N':
				system("clear");
				if (!Pageing_IsLastPage(paging)) {
					Paging_Locate_OffsetPage(flag, paging, 1, schedule_node_t);
				}
				break;
	}
	
   }while(choice!='r'&&choice!='R'); 
	List_Destroy(flag, schedule_node_t);	
}
 
 
 
 /*TTMS_SCU_Sale_UI_ShowTicket
显示演出票界面
参数：输入的演出计划id*/
void Sale_UI_ShowTicket(int schedule_id)
{
	schedule_t schedule_buf;
	Schedule_Srv_FetchByID(schedule_id,&schedule_buf);//根据演出计划id，找出演出计划的节点信息  演出计划理由剧目id


	ticket_list_t buf;//buf保存着某演出计划的所有票
	List_Init(buf,ticket_node_t);
	ticket_list_t pos;

	Pagination_t paging;
	paging.offset = 0;
	paging.pageSize =  SALESANALYSIS_PAGE_SIZE;

	int i;
	int choice;
	
	seat_list_t flag;//flag保存演出计划的所有座位      
	List_Init(flag,seat_node_t);
	Seat_Srv_FetchByRoomID(flag,schedule_buf.studio_id);//根据剧目id找到座位链表

	paging.totalRecords=Ticket_Srv_FetchBySchID(buf,schedule_id);
	Paging_Locate_FirstPage(buf,paging);



	do {
		system("clear");
	printf("\n=======================================================================\n");
	printf("\n========================Ticket information==========================\n");
    printf("\t\t%5s  %5s  %5s %5s %5s"," ticket id","schedulerid","seat","price","status of tickets");//票id,演出计划id,座位,价格,状态

	
	Paging_ViewPage_ForEach(buf, paging, ticket_node_t, pos, i){
		printf("\t\t%5d  %5d  %5d  %5d  %5d\n",pos->data.id,pos->data.schedule_id,pos->data.seat_id,
	        	pos->data.price,pos->data.status);		}

	
    printf(	"------- %2d in total -------------------------------- page :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));


    printf("\n\n\n\n"); 
    printf("\n\n=================================================================");
	printf("*******************************************************************\n");
	printf(" \t\t[1]sell tickets    [2]Previous page  [3]Next page  [0]return  \n");//视频里没有此条函数的要求和讲解，设数字方便些
	printf("\n*******************************************************************\n\n");
        
		printf("Please choice：");
		fflush(stdin);
		scanf("%d", &choice);
		
		switch(choice)
		{

			case 1:
			system("clear");
			Sale_UI_SellTicket(buf,flag);	
			break;

			case 2:
			system("clear");
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(buf, paging, -1, ticket_node_t);
			}
			break;

			case 3:
			system("clear");
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(buf, paging, 1, ticket_node_t);
			}
			break;
		}

	}while(choice!=0);

	List_Destroy(flag, seat_node_t);
	List_Destroy(buf, ticket_node_t);

} 




/*TTMs_SCU_Sale_UI_SellTicket
参数：tickList表示票列数，seatList表示所有座位列表
返回值：售出的票所对应的座位ID 
功能：售票*/

int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList)
{

	int x,y;
	printf("Please enter the row and column of the seat：");//输入座位的行列 
	scanf("%d %d",&x,&y);
	
	printf("\n");
	ticket_list_t q;

	int cnt2 = 1;

	seat_list_t b;
	b=Seat_Srv_FindByRC(seatList,x,y);//传入行列，找到座位信息，b储存座位信息链表节点
    if(b==NULL) 
	{
		printf("Wrong seat");
		return;
	}

	ticket_list_t flag;
	int i;
	flag=Ticket_Srv_FetchByID(b->data.id,tickList);//根据座位id，找到票的信息，，flag存储票信息链表节点
	if(flag == NULL){
		printf("Not found\n");//没有找到，票不存在 
		return;

	}
	else
	{
	printf("Ticket ID is %d\n",flag->data.id);
	}

	
	if(flag->data.status==0)//票的状态 

	{
		printf("The ticket can be purchased\n");//票未售，可买 
		flag->data.status=1;//未售->已售 
		Ticket_Srv_Modify(&(flag->data));
		
		sale_t buf;//保存这次售票的销售记录

		long key = EntKey_Perst_GetNewKeys(SALE_KEY_NAME, 1); //获取主键
		if(key<=0)			
			return 0;
		buf.id = key;	
		printf("\n");

		printf("输入你的id);//售票员的id 
		scanf("%d",&buf.user_id);
		buf.ticket_id=flag->data.id;
		buf.value==flag->data.price;

		struct tm *local;
		time_t t;
		t=time(&t);
		local=localtime(&t);  //当前日期
		printf("%d年%d月%d日\n",local->tm_year+1900,local->tm_mon+1,local->tm_mday);
		buf.date.year=local->tm_year+1900;
		buf.date.month=local->tm_mon+1;
		buf.date.day=local->tm_mday;
		printf("%d时%d分%d秒\n",local->tm_hour,local->tm_min,local->tm_sec);
		buf.time.hour=local->tm_hour;
		buf.time.minute=local->tm_min;
		buf.time.second=local->tm_sec;

		buf.type=1;//交易类型为买票（SALE_SELL=1 为买票） 
		Sale_Srv_Add(&buf);//存储销售记录 
        printf("The ID of the ticket you purchased is %d\n",buf.ticket_id);
		return 1;
	}

	else if(flag->data.status==1)
	{
		printf("The ticket has been sold");
		return 0;
	}
	else
	{
		printf("This ticket is reserved and cannot be purchased");//预留票，不能买 
		return 0;

	}
}



/*TTMs_SCU_Sale_UI_UI_ReturnTicket
参数：无  返回值：无
功能：退票*/
void Sale_UI_ReturnTicket()
{
	char choice;
	int id,t=0;
     while(1){
		system("clear");
       		printf("\n=======================================================================\n\n");
        	printf("\n========================Get a refund for the ticket==========================\n\n");
        	printf("\t\tPlease make sure that the ticket you want to return is not overdue!!!");//过期的票 
          	printf("\n	\t\tPlease enter the ID of the ticket:\n");
          	scanf("%d",&id);}
        

		ticket_t buf;
        ticket_list_t flag;
		if( Ticket_Srv_FetchByID(id,&buf) ==1)//若票存在 
		{

			if(buf.status==1)//票类型定义 1为已售，0为未售，9为预售 
			{
       			buf.status=0;
       			sale_t data;
				data.ticket_id=id;
				data.ticket_id=id;
	       		data.value=buf.price;
	       		data.type=-1;	//	SALE_RETURN=-1	退票
	       		Sale_Srv_Add(&data);
	       		Ticket_Srv_Modify(&buf);
	       		printf("\n\t\tRefund successful\n");
	       		
       		}
				   
			else{

       				printf("\nThe ticket is not sold or does not exist, cannot be refunded\n\n");
       				printf("Press any key to return");//按任意键返回
					getchar(); 
			        break;

       			}

       	}
	

}
 

