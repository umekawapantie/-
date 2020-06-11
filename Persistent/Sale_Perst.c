#include "Sale_Perst.h"
#include "../Common/List.h"
#include "../Service/Sale.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>
#include <string.h>
#include "EntityKey_Persist.h"



//将参数所指的订单信息写入售票文件中 
int Sale_Perst_Insert (sale_t *data)//书上和视频对与此流程图所对应函数有部分不同，我按书上的写了 
{
	data.id=EntKey_Perst_GetNewKeys("sale");//？？ 
	int rtn=0;
	FILE *fp;
	fp=fopen("Sale.dat","ab");
	if(fp==NULL)
	{
	   printf("fail to open file!");//打开文件失败
	   return 0;

	}
	
	rtn=fwrite(data,sizeof(sale_t),1,fp); 
		fclose(fp);
		return rtn;
}



//使用data中票的状态信息修改数据文件中票的状态 
int Ticket_Perst_Update (const ticket_t *data){

	assert(NULL!=data);
    FILE *fp = fopen("Ticket.dat","rb+");
	if (NULL == fp) {

		printf("fail to open file!");//打开文件失败
		return 0;

	}

	ticket_t rec;
	int rtn = 0;

	while (!feof(fp)) {
		
		if (fread(&rec, sizeof(ticket_t), 1, fp)) {

			if (rec.id == data->id) {
				fwrite(data, sizeof(ticket_t), 1, fp);
				rtn = 1;
				break;

			}
		}
	}

	fclose(fp);
	return rtn;
}


//根据演出计划ID载入演出票的数据 
int Ticket_Perst_SelBySchID(int id,ticket_list_t list)//list代表链表的头结点 
{  
   int count=0;
   ticket_node_t data;
   List_Init(list,ticket_node_t);
   FILE* fp=fopen("Ticket.dat","rb");
   if(fp==NULL)
   {
   	 printf("fail to open file!");
	 return 0;
   }
   while(fread(data,sizeof(ticket_node_t),1,fp))
   {
   	if(data->schedule_id==id)
   	{  count++;
	   List_AddTail(list,data);
	   }
	} 
	fclose(fp);
	return count;
 } 
 
 
 
 
