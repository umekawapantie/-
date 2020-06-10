#include "Schedule.h"

#include "Schedule_Perst.h"
#include "EntityKey_Perst.h"
#include "Play_Perst.h"

#include "List.h"

#include <stdio.h>



//函数功能：根据参数中的剧目ID号，查找与该剧目相关的演出计划。
int Schedule_Srv_FetchByPlay(schedule_list_t list, int play_id) {
    return Schedule_Perst_SelectByPlay(list, play_id);
}


//标识符 ：TTMS_SCU_Schedule_Srv_Add
//函数功能：将参数data作为实参调用持久化层存储新演出计划函数，并将持久化层函数的返回值传递给界面层函数
int Schedule_Srv_Add(schedule_t* data) {
    return Schedule_Perst_Insert(data);
}


//标识符 ：TTMS_SCU_Schedule_Srv_Mod
//函数功能：用参数data中的演出计划数据作为实参，通过调用持久化层函数来修改文件记录的旧的演出计划信息。
int Schedule_Srv_Modify(const schedule_t* data) {
    return Schedule_Perst_Update(data);
}


//标识符 ：TTMS_SCU_Schedule_Srv_DelByID
//函数功能 ：根据参数id记录的演出计划ID号，调用持久化层函数删除相应的演出计划。
int Schedule_Srv_DeleteByID(int id) {
    return Schedule_Perst_RemByID(id);
}

//标识符 ：TTMS_SCU_Schedule_Srv_FetchAll
//函数功能： 获取全部演出计划
int Schedule_Srv_FetchAll(schedule_list_t list)
{
    return Schedule_Perst_SelectAll(list);
}

//标识符 ：TTMS_SCU_Schedule_Srv_FetchByName
//函数功能： 根据名称获取剧目
int Play_Srv_FetchByName(play_list_t list, char condt[])
{
    return Play_Perst_SelectByName(list, condt);
}

int Schedule_Srv_StatRevByPlay(int play_id, int* soldCount)
{
    int value = 0;          //存储票房
    int sold = 0;
    schedule_list_t list;
    schedule_node_t* p;
    *soldCount = 0;

    int flag;

    List_Init(list, schedule_node_t);
    flag = Schedule_Perst_SelectByPlay(list, play_id);              //构建演出计划链表list
    //printf("%d\n\n\n",Schedule_Perst_SelectByPlay(list, play_id));
    List_ForEach(list, p) {
        if (flag == 1)
            break;
        printf("%d\n", p->data.id);
        value += Ticket_Srv_StatRevSchID(p->data.id, &sold);
        *soldCount = *soldCount + sold;
        flag--;
    }

    List_Destroy(list, schedule_node_t);

    return value;
}
