#ifndef SCHEDULE_PERST_H
#define SCHEDULE_PERST_H
#include "Schedule_Srv.h"

//函数功能 ：从演出计划数据文件中载入与指定剧目关联的演出计划信息，构成链表list。
int Schedule_Perst_SelectByPlay(schedule_list_t list, int play_id);


//函数功能 ：向演出计划文件Schedule.dat的末尾添加一条新的演出计划
int Schedule_Perst_Insert(schedule_t* data);


//函数功能 : 更新演出计划数据文件Schedule.dat中的一条演出计划信息。
int Schedule_Perst_Update(const schedule_t* data);


//函数功能 ：去除演出计划数据文件Schedule.dat中指定ID的演出计划
int Schedule_Perst_RemByID(int id);


//将所有演出计划信息串成链表
int Schedule_Perst_SelectAll(schedule_list_t list);


//通过名称将符合条件的剧目信息建立成一条链表
int Play_Perst_SelectByName(play_list_t list, char condt[]);

#endif // SCHEDULE_PERSIST_H
