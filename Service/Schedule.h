
#ifndef SCHEDULE_H_
#define SCHEDULE_H_
#include "Play_Srv.h"
#include"Schedule_Srv.c"

//日期类型
// 时间结构体定义如下：
// 类型标识：ttms_time_t
// 类型名称：ttms_time_t
// 类型定义：
typedef struct {
    int hour;
    int minute;
    int second;
}ttms_time_t;


//演出计划数据类型的定义如下：
//类型名称 ：schedule_t.
//类型定义：
typedef struct {
    int id;             //演出计划ID
    int play_id;        //上映剧目ID
    int studio_id;      //演出厅ID
    ttms_date_t date;   //放映日期
    ttms_time_t time;   //放映时间
    int seat_count;     //座位数
}schedule_t;


//演出计划链表节点的定义如下：
//类型标识 ：TTMS_SDS_Schedule_ListNode.
//类型名称: schedule_node_t、schedule_list_t
//类型定义：
typedef struct schedule_node {
    schedule_t data;
    struct schedule_node* next;
    struct schedule_node* prev;
}schedule_node_t, * schedule_list_t;


//函数功能：根据参数中的剧目ID号，查找与该剧目相关的演出计划。
int Schedule_Srv_FetchByPlay(schedule_list_t list, int play_id);


//函数功能：将参数data作为实参调用持久化层存储新演出计划函数，并将持久化层函数的返回值传递给界面层函数
int Schedule_Srv_Add(schedule_t* data);


//函数功能：用参数data中的演出计划数据作为实参，通过调用持久化层函数来修改文件记录的旧的演出计划信息。
int Schedule_Srv_Modify(const schedule_t* data);


//函数功能 ：根据参数id记录的演出计划ID号，调用持久化层函数删除相应的演出计划。
int Schedule_Srv_DeleteByID(int id);


//获取所有演出计划信息串成链表
int Schedule_Srv_FetchAll(schedule_list_t list);


//通过名称获取剧目信息
int Play_Srv_FetchByName(play_list_t list, char condt[]);

int Schedule_Srv_StatRevByPlay(int play_id, int* soldCount);

#endif // SCHEDULE_H_
#pragma once
