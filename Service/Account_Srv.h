#ifndef ACCOUNT_SER_H_
#define ACCOUNT_SER_H_
typedef enum
{
	USR_ANOMY=0, //匿名类型
	USR_CLEAK=1, //销售员类型
	USR_MANG=2,  //经理类型
	USR_ADMIN=9  //系统管理员类型
}account_type_t;
typedef struct
{
	int id;      //用户ID
	account_type_t type;//用户类型
	char username[30];//用户名
	char password[30];//用户密码
	char telnumber[30];//联系电话
}account_t;
typedef struct account_node
{
	account_t data;
	struct account_node* next;
	struct account_node* prev;
}account_node_t,*account_list_t;
int Account_Srv_VerifyLog();
account_node_t* Account_FindByUserName(account_list_t head, char usrName[]);
int Account_Srv_Add(account_list_t head);
int Account_Srv_Mod(account_list_t head, account_node_t* p);
int Account_Srv_DelByID(account_list_t head);
int  Account_Srv_FetchAll(account_list_t head);
int Account_Srv_Change(account_list_t head, account_node_t* p);
#endif
