#ifndef SCHEDULE_PERSIST_H
#define SCHEDULE_PERSIST_H
#include "../Service/Schedule.h"

//��ʶ�� ��TTMS_SCU_Schedule_Perst_SelByPlay
//�������� �����ݳ��ƻ������ļ���������ָ����Ŀ�������ݳ��ƻ���Ϣ����������list��
int Schedule_Perst_SelectByPlay(schedule_list_t list, int play_id);


//��ʶ�� ��TTMS_SCU_Schedule_Perst_Insert
//�������� �����ݳ��ƻ��ļ�Schedule.dat��ĩβ����һ���µ��ݳ��ƻ�
int Schedule_Perst_Insert(schedule_t * data);


//��ʶ�� ��TTMS_SCU_Schedule_Perst_Update
//�������� : �����ݳ��ƻ������ļ�Schedule.dat�е�һ���ݳ��ƻ���Ϣ��
int Schedule_Perst_Update(const schedule_t *data);


//��ʶ�� ��TTMS_SCU_Schedule_Perst_RemByID
//�������� ��ȥ���ݳ��ƻ������ļ�Schedule.dat��ָ��ID���ݳ��ƻ�
int Schedule_Perst_RemByID(int id);


//�������ݳ��ƻ���Ϣ��������
int Schedule_Perst_SelectAll(schedule_list_t list);


//ͨ�����ƽ������������ݳ��ƻ���Ϣ������һ������
int Schedule_Perst_SelectByName(schedule_list_t list, char condt[]);

//ͨ�����ƽ����������ľ�Ŀ��Ϣ������һ������
int Play_Perst_SelectByName(play_list_t list,char condt[]);

#endif // SCHEDULE_PERSIST_H
