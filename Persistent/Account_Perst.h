#ifndef ACCOUNT_PERST_H_
#define ACCOUNT_PERST_H_
#include<stdio.h>
int Account_Perst_CheckAccFile();
int Account_Perst_VerifyLog(account_node_t* p);
int Account_Perst_VerifyExit(account_node_t* p);
int Account_Perst_Add(account_node_t* h);
int Account_Perst_Update(account_node_t* p);
int Account_Perst_RemByID(int id);
int Account_Perst_FetechByUsername(account_list_t head);
#endif
