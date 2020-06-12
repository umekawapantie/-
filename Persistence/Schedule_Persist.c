#include "../Persistence/Schedule_Persist.h"
#include "EntityKey_Persist.h"
#include "../Service/Play.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Common/List.h"
#include <io.h>


//static const char SCHEDULE_DATA_FILE[] = "Schedule.dat";
static const char PLAY_DATA_FILE[] = "Play.dat";

//��ʶ�� ��TTMS_SCU_Schedule_Perst_SelByPlay
//�������� �����ݳ��ƻ������ļ���������ָ����Ŀ�������ݳ��ƻ���Ϣ����������list��
int Schedule_Perst_SelectByPlay(schedule_list_t list, int play_id){
    int reCount = 0;
    FILE * fp;
    schedule_list_t  newNode;
    schedule_t data;
    fp =fopen("Schedule.dat", "rb");
    if (fp == NULL) {
        printf("can not open %s file", "Schedule.dat");
        return reCount;
    } else {
        while(!feof(fp)) {
            fread(&data, sizeof(data), 1, fp);
            if (data.play_id == play_id) {
                newNode = (schedule_list_t)malloc(sizeof(schedule_node_t));
                newNode->data = data;
                List_AddTail(list, newNode);
                reCount++;
            }
        }
    }
    fclose(fp);
    return reCount;
}


//��ʶ�� ��TTMS_SCU_Schedule_Perst_Insert
//�������� �����ݳ��ƻ��ļ�Schedule.dat��ĩβ����һ���µ��ݳ��ƻ�
int Schedule_Perst_Insert(schedule_t * data) {
    FILE * fp;
    int rtn = 0;

    ////����������Ʒ����������ӵĴ���
	long key = EntKey_Perst_GetNewKeys("schedule", 1); //Ϊ���ݳ��������ȡ
	if(key<=0)			//��������ʧ�ܣ�ֱ�ӷ���
		return 0;
	data->id = key;		//�����¶�����ص�UI��
	////����������Ʒ����������ӵĴ���
	////����������Ʒ����������ӵĴ���

    fp = fopen("Schedule.dat", "ab");
    if (fp == NULL){
          printf("can not open %s file", "Schedule.dat");
          return 0;
    } else {
        rtn = fwrite(data, sizeof(schedule_t), 1, fp);
    }
    fclose(fp);
    return rtn;


}


//��ʶ�� ��TTMS_SCU_Schedule_Perst_Update
//�������� : �����ݳ��ƻ������ļ�Schedule.dat�е�һ���ݳ��ƻ���Ϣ��
int Schedule_Perst_Update(const schedule_t *data) {
    int found = 0;
    FILE * fp;
    schedule_t buf;
    fp = fopen("Schedule.dat", "rb+");
    if (fp == NULL) {
        printf("can not open %s file", "Schedule.dat");
        return found;
    }
    else {
        while(!feof(fp)) {
            fread(&buf, sizeof(schedule_t), 1, fp);
            if (buf.id == data->id) {
                fseek(fp, -((int)sizeof(schedule_t)), SEEK_CUR);
                fwrite(data, sizeof(schedule_t), 1, fp);
                found = 1;
                break;
            }
        }
    }
    fclose(fp);
    return found;
}


//��ʶ�� ��TTMS_SCU_Schedule_Perst_RemByID
//�������� ��ȥ���ݳ��ƻ������ļ�Schedule.dat��ָ��ID���ݳ��ƻ�
int Schedule_Perst_RemByID(int id) {
    int found = 0;
    FILE *fp, *ftp;
    schedule_t buf;
    //fp = fopen("ScheduleTmp.dat", "wb");
    if (rename("Schedule.dat", "ScheduleTmp.dat") < 0) {
        printf("Schedule.dat����ʧ��.");
        return found;
    } else {
        fp = fopen("ScheduleTmp.dat", "rb");
        ftp = fopen("Schedule.dat", "wb+");
        if (fp == NULL) {
            printf("ScheduleTmp.dat��ʧ��");
            return found;
        } else {
            while (!feof(fp)){
                fread(&buf, sizeof(schedule_t), 1, fp);
                if (buf.id == id) {
                    found = 1;
                } else {
                    fwrite(&buf, sizeof(schedule_t), 1, ftp);
                }
            }
        }
        fclose(fp);
        fclose(ftp);
        remove("ScheduleTmp.dat");
        return found;
    }
}


/*
��ʶ����TTMS_SCU_Schedule_Perst_SelectAll
�������ܣ����ݳ��ƻ������ļ�Schedule.dat�����������ݳ��ƻ������ص�����list��
����˵����listschedule_list_t����ָ�룬��ʾ��¼�����ݳ��ƻ�������ͷָ��
�� �� ֵ�����ͣ���ʾ������ݳ��ƻ�����
*/

int Schedule_Perst_SelectAll(schedule_list_t list)
{
    schedule_node_t *newNode;
	schedule_t data;
	int recCount = 0;

	assert(NULL!=list);
    //printf("11111\n");

	List_Free(list, schedule_node_t);

	FILE *fp = fopen("Schedule.dat", "rb");

	if (NULL == fp)
	{
		printf("�޷����ļ� %s!\n", "Schedule.dat");
		return 0;
	}

	while (!feof(fp))
	{

		if (fread(&data, sizeof(schedule_t), 1, fp))
		{
			newNode = (schedule_node_t*) malloc(sizeof(schedule_node_t));
			if (!newNode)
			{
				printf("���棬�ڴ����!!!\n���ܽ���������ݼ��ص��ڴ���!!!\n");
				break;
			}
			newNode->data = data;
			List_AddTail(list, newNode);
			recCount++;
		}
	}
	fclose(fp);
	return recCount;
}

/*
��ʶ����TTMS_SCU_Schedule_Perst_SelectAll
�������ܣ��Ӿ�Ŀ��ϢPlay.dat�������Ŀ���ư�ָ���ַ��ľ�Ŀ��Ϣ
����˵����listschedule_list_t����ָ�룬��ʾ��¼�����ݳ��ƻ�������ͷָ��
          condt�ַ������飬��ʾ���ҵĹؼ���
�� �� ֵ�����ͣ���ʾ���������ĵ��ݳ��ƻ�����
*/

int Play_Perst_SelectByName(play_list_t list,char condt[])
{
    int recCount = 0;
    play_t data;
    play_node_t *newNode;

    assert(NULL!=list);


    if (access(PLAY_DATA_FILE,0))
    {
        printf("�ļ�������");
        return 0;
    }
    /*��ʼ��list*/
    List_Free(list,play_node_t);

    FILE *fp = fopen(PLAY_DATA_FILE,"rb");
    /*�ж��ļ��Ƿ�Ϊ��*/
    if (fp == NULL)
    {
        printf("Play_Perst_SelectByName��ʧ��");
        return 0;
    }
    /*���������ļӵ�list��*/
    while(!feof(fp))
    {
        if (fread(&data, sizeof(play_t), 1, fp))
		{
			newNode = (play_node_t*) malloc(sizeof(play_node_t));
			if (!newNode)
			{
				printf("���棬�ڴ����!!!\n���ܽ���������ݼ��ص��ڴ���!!!\n");
				break;
			}
			newNode->data = data;
			if(strstr(newNode->data.name,condt)!=NULL)
			{
                List_AddTail(list, newNode);
                recCount++;
			}
		}
    }
    fclose(fp);
    return recCount;
}
