#ifndef SALESANALYSISPERSIST_H_
#define SALESANALYSISPERSIST_H_
#include "SalesAnalysis.h"
#include "Play.h"
#include "Sale.h"

int Salesanalysis_Perst_Insert(const salesanalysis_t* data);
int SalesAnalysis_Perst_SelectAll(salesanalysis_list_t list);
int Sale_Perst_SelectALL(sale_list_t list);

#endif 
