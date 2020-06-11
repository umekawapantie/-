#ifndef SALE_H_
#define SALE_H_

#include "../Common/common.h"
#include "Account.h"
#include "Ticket.h"
#include "Schedule.h"

typedef enum{
	SALE_SELL=1,	//买票
	SALE_RETURN=-1	//退票
}sale_type_t;

typedef struct {
	long id;      		//销售记录ID
	int user_id;		//售票员ID
	int ticket_id;		//票ID
	ttms_date_t date ;	//处理日期
	ttms_time_t time;	//处理时间
	int value;			//票价
	sale_type_t type; //交易类型
}sale_t;

//双向链表
typedef struct sale_node {
	sale_t data;
	struct sale_node *next;//后向指针 
	struct sale_node *prev;//前向指针 
} sale_node_t, *sale_list_t;

int Sale_Srv_Add(sale_t *data);

int Ticket_Srv_Modify (const ticket_t *data);

int Ticket_Srv_FetchBySchID(ticket_list_t list, int schedule_id);

ticket_node_t * Ticket_Srv_FetchBySeatID (ticket_list_t list, int seat_id);

#endif
