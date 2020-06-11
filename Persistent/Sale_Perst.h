#ifndef SALE_PERST_H_

#define SALE_PERST_H_
#include "../Service/Sale.h"

#include "../Common/common.h"
#include"../Common/List.h"
int Sale_Perst_Insert (sale_t *data);

int Ticket_Perst_Update (const ticket_t *data);

int Ticket_Perst_SelBySchID(int id,ticket_list_t list);

#endif 
