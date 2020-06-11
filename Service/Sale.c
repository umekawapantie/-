#include "../Persistence/Sale_Perst.h"
#include "../Persistence/Ticket_Perst.h"
#include "../Common/List.h"

//将新产生的售票订单信息添加到销售记录中 
int Sale_Srv_Add(sale_t *data)
{
   return Sale_Perst_Insert(data);
}


//使用data中票的状态信息修改数据文件中票的状态 
int Ticket_Srv_Modify (const ticket_t *data)
{
	return Ticket_Perst_Update(data);
}

//根据演出计划ID获取所有演出票的数据 
int Ticket_Srv_FetchBySchID(ticket_list_t list, int schedule_id)
{
	return Ticket_Perst_SelectBySchID(list,schedule_id);
}

//根据座位ID获取票的数据 
ticket_node_t * Ticket_Srv_FetchBySeatID (ticket_list_t list, int seat_id)
{
	ticket_node_t* p;

	List_ForEach(list,p)

	{

			if(p->data.seat_id == seat_id) return p;

	}

	return NULL;
}
