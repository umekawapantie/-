#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<io.h>
#include"./List.h"
#include"./Account_Srv.h"
int Account_Perst_CheckAccFile()//1.判断文件是否存在
{
	if (assess("Account.dat", 0))
		return 0;
	return 1;
}
int Account_Perst_VerifyLog(account_node_t* p)//验证登录
{
	int pd = 0;
	FILE* fp = fopen("Account.dat", "rb");
	if (fp == NULL)
	{
		printf("Error!\n");
		return 0;
	}
	account_node_t* temp;
	temp = NULL;
	temp = (account_node_t*)malloc(sizeof(account_node_t));
	while (fread(temp, sizeof(account_node_t), 1, fp))
	{
		if ((strcmp(temp->data.username, p->data.username) == 0) && (strcmp(temp->data.password, p->data.password) == 0))
			pd = 1;
	}
	free(p);
	free(temp);
	fclose(fp);
	return pd;
}
int Account_Perst_VerifyExit(account_node_t* p)//判断用户是否存在
{
	int pd = 0;
	account_node_t* temp;
	FILE* fp = fopen("Account.dat", "rb");
	if (fp == NULL)
	{
		printf("Error!\n");
		return 0;
	}
	while (fread(temp, sizeof(account_node_t), 1, fp) != 0)
	{
		if (strcmp(temp->data.username, p->data.username) == 0)
			pd = 1;
	}
	free(temp);
	fclose(fp);
	if (pd) return 1;
	return 0;
}
int Account_Perst_Add(account_node_t *p)//2.存储写入文件
{
	int rtn = 0;
	FILE* fp;
	account_node_t* temp = NULL;
	temp = (account_node_t*)malloc(sizeof(account_node_t));
	temp = p->next;
	p->data.id=EntKey_Perst_GetNewKeys(p->data.username,1);
	if (!Account_Perst_CheckAccFile())//文件不存在，则以写的形式打开
	{
		fp = fopen("Account.dat", "wb+");
	}
	else {
		fp = fopen("Account.dat", "ab");//文件存在，则以追加的形式打开
	}
	if (fp == NULL)
	{
		printf("Error!\n"); return rtn;
	}
	fwrite(temp, sizeof(account_node_t), 1, fp); rtn = 1;
	fclose(fp);
	free(temp);
	return rtn;
}
int Account_Perst_Update(account_node_t* p)//3.更新系统用户
{
	int found = 0;
	account_node_t* temp;
	temp = (account_node_t*)malloc(sizeof(account_node_t));
	if (!Account_Perst_CheckAccFile())return 0;
	FILE* fp = fopen("Account.dat", "rb+");
	if (fp == NULL) return found;
	while (fread(temp, sizeof(account_node_t), 1, fp))
	{
		if (temp->data.id== p->data.id)//回撤文件指针
		{
			fseek(fp, -sizeof(account_t), SEEK_CUR);
			fwrite(temp, sizeof(account_t), 1, fp);
			found = 1;
			break;
		}
	}
	free(temp);
	fclose(fp);
	return found;
}
int Account_Perst_RemByID(int id)//4.根据ID删除用户
{
	int found = 0;
	account_node_t* temp;
	FILE* fp, * fp1;
	temp = (account_node_t*)malloc(sizeof(account_node_t));
	if(rename("Account.dat","Accounttemp.dat")==0)return 0;
	if (!Account_Perst_CheckAccFile())return 0;
	fp = fopen("Account.dat", "wb");
	if (fp == NULL)
	{
		printf("\nError!\n"); return 0;
	}
	fp1 = fopen("Accounttemp.dat", "rb");
	while (1)
	{
		if (fread(temp, sizeof(account_node_t), 1, fp1) == 0)break;
		if (temp->data.id == id) found = 1;
		else
		{
			fwrite(temp, sizeof(account_node_t), 1, fp);
		}
	}
	free(temp);
	fclose(fp);
	fclose(fp1);
	remove("Accounttemp.dat");
	return found;
}
int Account_Perst_FetechByUsername(account_list_t head)//5.将所有的用户信息传入链表中
{
	account_node_t* temp;
	int usercount = 0;
	FILE* fp=fopen("Account.dat","rb");
	if (fp == NULL) return 0;
	temp = (account_node_t*)malloc(sizeof(account_node_t));
	while (fread(temp, sizeof(account_node_t), 1, fp))
	{
		temp = (account_node_t*)malloc(sizeof(account_node_t));
		usercount++;
		List_AddTail(head, temp);
	}
	free(temp);
	return usercount;
}

