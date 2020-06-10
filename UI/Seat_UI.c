/*
* Copyright(C), 2007-2008, XUPT Univ.	 
* 用例编号：TTMS_UC_02
* File name: Seat_UI.c			  
* Description : 设置座位用例界面层	
* Author:   XUPT  		 
* Version:  v.1 	 
* Date: 	2015年4月22日	
*/

#include "Seat_UI.h"
#include "../Service/Seat.h"

#include "../Service/Studio.h"
#include "../Common/List.h"
#include <stdio.h>

/*
表识符：TTMS_SCU_Seat_UI_S2C 
函数功能：根据座位状态获取界面显示符号。
参数说明：status为seat_status_t类型，表示座位状态。
返 回 值：字符型，表示座位的界面显示符号。
*/
inline char Seat_UI_Status2Char(seat_status_t status) {

	char statuschar;
	switch (status) {
	case SEAT_GOOD:
		statuschar = 'G';
		break;
	case SEAT_BROKEN:
		statuschar = 'B';
		break;
	case SEAT_NONE:
		statuschar = 'N';
		break;
	}
	return statuschar;
}

/*
标识符：TTMS_SCU_Seat_UI_C2S
函数功能：根据输入符号获取座位状态。
参数说明：statusChar为字符型，表示设置座位的输入符号。
返 回 值：seat_status_t类型，表示座位的状态。
*/
inline seat_status_t Seat_UI_Char2Status(char statusChar) {
	seat_status_t situation;
	switch (statusChar)
	{
	case'G':
			situation = SEAT_GOOD;
			break;
	case 'B':
		situation = SEAT_BROKEN;
		break;
	case 'N':
		situation = SEAT_NONE;
		break;
	}
	return situation;
}

/*
标识符：TTMS_SCU_Seat_UI_MgtEnt
函数功能：界面层管理座位的入口函数，显示当前的座位数据，并提供座位数据添加、修改、删除功能操作的入口。
参数说明：roomID为整型，是需要设置座位的演出厅ID。
返 回 值：无。
*/ 
void Seat_UI_MgtEntry(int roomID) {
	int i, j;
	char choice;
	int seatCount;
	int changedCount = 0;
	studio_t studioRec;

	if (!Studio_Srv_FetchByID(roomID, &studioRec)) {
		printf("\n\n\n			=================================================================");
		printf("\n	                 		      **演出厅不存在！**                             ");
		printf("\n			=================================================================");
		getchar();
		return;
	}

	seat_list_t list;
	seat_node_t* p;

	List_Init(list, seat_node_t);
	seatCount = Seat_Srv_FetchByRoomID(list, roomID);

	if (!seatCount) {
		seatCount = Seat_Srv_RoomInit(list, roomID, studioRec.rowsCount,
			studioRec.colsCount);
		studioRec.seatsCount = seatCount;
		Studio_Srv_Modify(&studioRec);
	}
	do {
		printf("\n\n\n			=================================================================");
		printf("\n			---------------------%d号演出厅座位表------------------------------", roomID);
		printf("\n			*****************************************************************");
		printf("\n	\t\t   列：%c", ' ');
		for (i = 1; i <= studioRec.colsCount; i++) {
			printf("%3d", i);
		}
		printf("\n	\t\t=================================================================");

		for (i = 1; i <= studioRec.rowsCount; i++) {
			j = 1;
			printf("\n	\t\t%3d行：%3c", i, ' ');

			List_ForEach(list, p)
			{
				if (p->data.row == i) 
				{
					while (p->data.column != j) {
						printf("%3c", ' ');
						j++;
					}
					Seat_UI_Status2Char(p->data.status);
					if (p->data.status == SEAT_NONE)
					{
						printf("N  ");
					}
					if (p->data.status == SEAT_GOOD)
					{
						printf("G  ");
					}
					if (p->data.status == SEAT_BROKEN)
					{
						printf("B  ");
					}
					j++;
				}
			}
		}
		printf("\n	\t\t|     [A]dd     |    [D]elete    |   [U]pdate   |     [R]eturn   |\n");
		printf("\n	\t\tYour choice:");
		scanf("%c", &choice);
		switch (choice) {
		case 'a':
		case 'A':
			changedCount = Seat_UI_Add(list, roomID, studioRec.rowsCount,
				studioRec.colsCount);
			if (changedCount > 0) 
			{
				seatCount += changedCount;
				studioRec.seatsCount = seatCount;
				Studio_Srv_Modify(&studioRec);
			}
			break;
		case 'd':
		case 'D':
			changedCount = Seat_UI_Delete(list, studioRec.rowsCount,
				studioRec.colsCount);
			if (changedCount > 0) 
			{
				seatCount -= changedCount;
				studioRec.seatsCount = seatCount;
				Studio_Srv_Modify(&studioRec);
			}
			break;
		case 'u':
		case 'U':
		{
			int row, column;
			char choice;
			printf("\n			=================================================================");
			printf("\n			                             更新座位                            ");
			printf("\n	\t\t|      [1]按行更新     |      [2]按列更新     |    [3]单座更新   |");
			printf("\n	\t\t|\tInput Your Choice:");
			choice = l_getc();
			switch (choice)
			{
			case '3':
				printf("\t\t\t|\t请输入座位行号:");
				while (1) 
				{
					if (scanf("%d", &(row)) == 1) { cl_stdin(); break; }
					else { cl_stdin(); printf("\n	                 		       INPUTERROR！需要重新输入    "); }
				}
				printf("\t\t\t|\t请输入座位列号:");
				while (1) 
				{
					if (scanf("%d", &(column)) == 1) { cl_stdin(); break; }
					else { cl_stdin(); printf("\n	                 		     **输入有误！清重新输入**  "); }
				}
				Seat_UI_Modify(list, row, column);
				break;
			case '2':
				printf("\t\t\t|\t请输入座位的列号:");
				while (1) {
					if (scanf("%d", &(column)) == 1) { cl_stdin(); break; }
					else { cl_stdin(); printf("\n	                 		     **输入有误！清重新输入**  "); }
				}
				Seat_UI_Modify(list, 0, column);
				break;
			case '1':
				printf("\t\t\t|\t请输入座位的行号:");
				while (1) {
					if (scanf("%d", &(row)) == 1) { cl_stdin(); break; }
					else { cl_stdin(); printf("\n	                 		     **输入有误！清重新输入**  "); }
				}
				Seat_UI_Modify(list, row, 0);
				break;
			}
			break;
		}
		}
	} while (choice != 'r' && choice != 'R');

	List_Destroy(list, seat_node_t);
}

/*
识符：TTMS_SCU_Seat_UI_Add
函数功能：用于添加一个新的座位数据。
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，
         第二个参数rowsCount为整型，表示座位所在行号，第三个参数colsCount为整型，表示座位所在列号。
返 回 值：整型，表示是否成功添加了座位的标志。
*/
int Seat_UI_Add(seat_list_t list, int roomID, int row, int column)
{  //输入一个座位
	seat_list_t tmp = Seat_Srv_FindByRowCol(list, row, column);
	if (tmp == NULL) {
		seat_t temp;

		temp.column = column;
		temp.row = row;
		temp.status = SEAT_GOOD;
		temp.roomID = roomID;

		if (Seat_Srv_Add(&temp)) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

/*
标识符：TTMS_SCU_Seat_UI_Mod 
函数功能：用于修改一个座位数据。
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，第二个参数rowsCount为整型，表示座位所在行号，第三个参数colsCount为整型，表示座位所在列号。
返 回 值：整型，表示是否成功修改了座位的标志。
*/
int Seat_UI_Modify(seat_list_t list, int row, int column) {
	seat_list_t tmp = Seat_Srv_FindByRowCol(list, row, column);

	if (tmp != NULL) {
		seat_t temp;
		Seat_Perst_SelectByID(tmp->data.id, &temp);
		char choice;
		printf(
			"*******************************************************************\n");
		printf(
			"[G]ood | [B]reak |  [N]one | \nthe seat's situation is %c", Seat_UI_Status2Char(temp.status));
		printf(
			"\n==================================================================\n");
		printf("Your Choice:");
		scanf("%c", &choice);
		getchar();
		tmp->data.status = Seat_UI_Char2Status(choice);

		if (Seat_Srv_Modify(&tmp->data)) {

			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

/*
标识符：TTMS_SCU_Seat_UI_Del
函数功能：用于删除一个座位的数据。
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，第二个参数rowsCount为整型，表示座位所在行号，第三个参数colsCount为整型，表示座位所在列号。
返 回 值：整型，表示是否成功删除了座位的标志。
*/
int Seat_UI_Delete(seat_list_t list, int row, int column) {
	seat_list_t tmp = Seat_Srv_FindByRowCol(list, row, column);

	if (tmp != NULL) {
		if (Seat_Srv_DeleteByID(tmp->data.id)) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}
