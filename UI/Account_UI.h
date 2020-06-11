#ifndef ACCOUNT_UI_H_
#define ACCOUNT_UI_H_
int Login();                                       //系统用户登录
void Account_UI_MgtEntry();                        //系统用户管理
void MaiAccount_UI_MgtEntry();                     //维护个人信息
void Account_UI_Add(account_list_t head);          //注册
void Account_UI_Mod(account_list_t head);          //修改密码
void Account_UI_Del(account_list_t head);          //删除
void Account_UI_Que(account_list_t head);          //查询
void Account_UI_Change(account_list_t head);       //修改个人密码
#endif
