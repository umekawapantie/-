#ifndef TICKET_PERSIST_H_
#define TICKET_PERSIST_H_

#include"../Service/Ticket_Ser.h"
#include"../Service/Schedule.h"
#include"../Service/Seat.h"
//int Schedule_Perst_SelectByID(int id,schedule_t *buf);   //  从文件中载入指定id的演出计划


int  Ticket_Perst_Insert(seat_list_t list, int schedule_id);      //从票的信息文件ticket.dat 中批量加入list链表上所有票的信息


int  Ticket_Perst_Rem(int schedule_id);    //批量删除演出计划的id号

//int Ticket_Perst_SelBySchID(int ID,ticket_list_t list);


int Ticket_Perst_SelBySchID(int ID, ticket_list_t list);

int Ticket_Perst_SelByticketID(id, buf);

#endif
