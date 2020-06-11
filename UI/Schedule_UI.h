#ifndef SCHEDULE_UI_H_

#define SCHEDULE_UI_H_

#include "Schedule.h"
/*
Schedule_UI_MgtEntry	 
演出计划管理界面，演出计划按照剧目进行管理，以剧目id为输入，输出演出计划信息
	 */
void Schedule_UI_MgtEntry();

/*
 Schedule_UI_Add
	输入相关剧目的ID号,添加一条演出计划信息
	 */
void Schedule_UI_Add();

/*
Schedule_UI_Delete
输入待删除的剧目ID号，按照ID号删除演出计划信息
	 */
void Schedule_UI_Delete();

/*
Schedule_UI_Modify
按照ID号更新演出计划信息
	 */
void Schedule_UI_Modify();


int Schedule_UI_SelectByPlayPlayName(schedule_node_t* h);

#endif
