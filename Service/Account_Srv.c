#include<stdio.h>
#include<string.h>
#include"./List.h"
#include"./Account_Srv.h"
#include"./Account_Perst.h"
#include"./Account_UI.h"
//2.用户登录验证
int Account_Srv_VerifyLog()
{
	int pd;
	account_node_t* p = NULL;
	for (int i = 1; i <= 3; i++)
	{
		printf("\t\t\t\tusername:"); scanf("%s", p->data.username);
		printf("\t\t\t\tpassword:"); scanf("%s", p->data.password);
		pd = Account_perst_VerifyLog(p);
		if (pd) break;
		else printf("\t\t\t\t>.<Login failure,and you have %d times to login!\n", 3 - i);
	}
	if (pd) return 1;
	return 	0;
}
account_node_t* Account_FindByUserName(account_list_t head,char usrName[])//7.根据用户名获取用户指针
{
	account_node_t *pos;
    List_ForEach(head, pos)
    {
		if (pos->data.username == usrName)
			return pos;
	}
	return NULL;
}
//3.注册,添加新用户
int Account_Srv_Add(account_list_t head)
{
	int pass = 0; char choice;
	account_node_t *p;
	while (pass == 0)
	{
	    pass = 1;
		p = (account_node_t*)malloc(sizeof(account_node_t));
	    printf("|UserName| : ");
    	scanf("%s", p->data.username);
	    if (strlen(p->data.username) <= 1)
	    {
	        pass = 0; printf("\n>.<Your username is too short!\n");
	    }
	    if (Account_Perst_VerifyExit(p))
	    {
	    	pass = 0;
	    	printf("\n>.<This username has exited!\n");
		}
	 }
	pass = 0;
	while(pass==0)
	{
		pass = 1;
		printf("UserType----- Anonymity [0]-----Salesman [1]-----Manager[2]-----Administrater [3]\n");
		printf("|UserType| : ");
		scanf("%c",&choice);
		switch (choice)
		{
		case(0): {p->data.type = USR_ANOMY; break; }
		case(1): {p->data.type = USR_CLEAK; break; }
		case(2): {p->data.type = USR_MANG; break; }
		case(3): {p->data.type = USR_ADMIN; break; }
		default: {printf("\n>.<Invalid selection!\n"); pass = 0; }
		}
	}
	pass = 0;
	while (pass== 0)
	{
		pass = 1;
		printf("|Password| : ");
		scanf("%s", p->data.password);
		if (strlen(p->data.password) < 8)
		{
			pass = 0; printf("\n>.<Your password is too short!\n");
		}
	}
	pass = 0;
	while (pass == 0)
	{
		pass = 1;
		printf("|TelNumber| : ");
		scanf("%s", p->data.telnumber);
		if (strlen(p->data.telnumber) < 8)
		{
			pass = 0; printf("\n>.<Your telnumber is too short!\n");
		}
	}
	List_AddTail(head, p);
	if (Account_Perst_Add(p))
		return 1;//存储新系统用户
	return 0;
}
//4.修改密码
int Account_Srv_Mod(account_list_t head,account_node_t* p)
{
	char Npassword[30],password[30];
	account_node_t* temp,*q;
	temp = (account_node_t*)malloc(sizeof(account_node_t));
	List_ForEach(head, temp)
	{
		if (strlen(temp->data.username,p->data.username)==0)
			break;
	}
	printf("\t\t\t\tPlease input the old password:"); scanf("%s", p->data.password);
	for (int i = 1; i <= 3; i++)
	{
		if (temp->data.password == p->data.password)
		{
			printf("Successful verity!Please input the new password:");
			scanf("%s",Npassword);
			
			break;
		}
		else
		{
			if (i != 3)
				printf("Sorry,the password is wrong!You have %d times to input.", 3 - i);
			else return 0;
		}
	}
	for (int i = 1; i <= 2;i++)
	{
		printf("Please input your new password again:");
		scanf("%s", password);
		if (Npassword == password)
		{
			printf("OK,new password is successfully set.Please input your new password again:");
			scanf("%s", temp->data.password);
		    break;
		}
		else
		{
			if (i != 2)
				printf("Sorry,the password is wrong!You have %d times to input.", 2 - i);
			else return 0;
		}
	}
	return Account_Perst_Update(temp);//更新系统用户
}
//5.删除用户
int Account_Srv_DelByID(account_list_t head)
{
	int userID;
	account_node_t* temp;
	temp = (account_node_t*)malloc(sizeof(account_node_t));
	printf("Please input the the username ID: ");
	scanf("%d", &userID);
	List_ForEach(head, temp)
	{
		if (temp->data.id == userID)
			break;
	}
	List_FreeNode(temp);
	return Account_Perst_RemByID(userID);
}

//6.将用户信息导入链表
int  Account_Srv_FetchAll(account_list_t head)
{
	return Account_Perst_FetechByUsername(head);
}
//7.修改信息
int Account_Srv_Change(account_list_t head, account_node_t* p)
{
	char choice;
	int ch;
	account_node_t* temp;
	temp = (account_node_t*)malloc(sizeof(account_node_t));
	List_ForEach(head, temp)
	{
		if (temp->data.username == p->data.username)
			break;
	}
	printf("What do you want to modify?\n");
	printf("username[U] type[T] telnumber[N]");
	fflush(stdin);
	scanf("%c", &choice);
	switch (choice)
	{
	case'U':case'u':
	{
		scanf("%s", temp->data.username);
	}
	case'T':case't':
	{
		printf("UserType----- Anonymity [0]-----Salesman [1]-----Manager[2]-----Administrater [3]\n");
		scanf("%d", &ch);
		switch (ch)
		{
		case(0): {temp->data.type = USR_ANOMY; break; }
		case(1): {temp->data.type = USR_CLEAK; break; }
		case(2): {temp->data.type = USR_MANG; break; }
		case(3): {temp->data.type = USR_ADMIN; break; }
		default: {printf("\n>.<Invalid selection!\n"); return 0; }
		}
	}
	case'N':case'n':
	{
		scanf("%s", temp->data.telnumber);
	}
	default:
		printf(">.<Sorry,your input is wrong!");
	}
	free(p);
	return Account_Perst_Update(temp);//更新系统用户
}
