#ifndef 	SALE_UI_H_
#define 	SALE_UI_H_


#include "../Service/Play.h"
#include "../Service/Schedule.h"
#include "../Service/Seat.h"
#include "../Service/Account.h"
#include "../Service/Ticket.h"
void Sale_UI_MgtEntry();

void Sale_UI_ShowScheduler1(int playID);

int Sale_UI_SellTicket1(ticket_list_t tickList,seat_list_t seatList);

int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList); 

void Sale_UI_ReturnTicket();


#endif
 
