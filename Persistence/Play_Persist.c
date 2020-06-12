/*�������ܣ����ڴ��ļ����������о�Ŀ���ݡ�*/
//����˵����list��play_list_t����ָ�룬ָ���Ŀ������ͷָ�롣

#include "Play_persist.h"
#include "../Common/List.h"
#include "../Service/Play.h"
#include "EntityKey_Persist.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <assert.h>

int Play_Perst_SelectAll(play_list_t list) {
	play_node_t *newNode;
	play_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, play_node_t);

	FILE *fp = fopen("Play.dat", "r+");
	if (NULL == fp) { //�ļ�������
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(play_t), 1, fp)) {
			newNode = (play_node_t*) malloc(sizeof(play_node_t));
			if (!newNode) {
				printf("Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
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

//��ʶ����TTMS_SCU_Play_Perst_Insert
//���ܣ����Ŀ�����ļ�play.dat�е�ĩβ����һ���µľ�Ŀ��Ϣ
int Play_Perst_Insert(play_t *data){
	FILE *fp;

	assert(NULL!=data);
	////����������Ʒ����������ӵĴ���
	long key = EntKey_Perst_GetNewKeys("Play", 1);
	if(key<=0)			//��������ʧ�ܣ�ֱ�ӷ���
			return 0;
		data->id = key;		//�����¶�����ص�UI��
	////����������Ʒ����������ӵĴ���

	fp = fopen("Play.dat", "ab");
	int rtn = 0;
	if (fp == NULL) {
		printf("��ʧ��insert!");
		return 0;
	}

	rtn = fwrite(data, sizeof(play_t), 1, fp);

	fclose(fp);
	return rtn;
}


//��ʶ����TTMS_SCU_Play_Perst_Update
//���ܣ������ļ�play.dat�е�һ����Ŀ��Ϣ
int	Play_Perst_Update(const play_t *data) {
	int found = 0;
	FILE *fp;
	play_t buf;
	fp = fopen("Play.dat", "rb+");
	if (fp == NULL) {
			printf("��'Play.dat'ʧ��\n");
	}
	else {
		while(!feof(fp)) {
			if(fread(&buf, sizeof(buf), 1, fp)){
                if (buf.id == data->id) {
                    fseek(fp, -((int)sizeof(play_t)), SEEK_CUR);
                    fwrite(data, sizeof(play_t), 1, fp);
                    found = 1;
                    break;
                }
			}
		}
	}
	if (fp)
		fclose(fp);
	return found;
}


//��ʶ����TTMS_SCU_Play_Perst_RemByID
//���ܣ���ȥ�ļ�play.dat��ָ��ID�ľ�Ŀ��Ϣ
int Play_Perst_RemByID(int id) {
	int found = 0;
	FILE * fp, *ftp;
	play_t  buf;
	if(rename("Play.dat", "PlayTmp.dat")<0){
		printf("Cannot rename file %s!\n", "Play.dat");
		return 0;
	}
	//��ԭʼ�ļ���������Ȼ���ȡ��������д�뵽�����ļ��У�����Ҫɾ����ʵ����˵���
	//��ԭʼ�����ļ�������

	fp = fopen("PlayTmp.dat", "rb");
	if (NULL == fp ){
		printf("Cannot open file %s!\n", "PlayTmp.dat");
		return 0;
	}

	ftp = fopen("Play.dat", "wb");
	if ( NULL == ftp ) {
		printf("Cannot open file %s!\n", "Play.dat");
		return 0;
	}
	else {
		while(!feof(fp)) {
			fread(&buf, sizeof(buf), 1, fp);
			if (buf.id == id) {
				found = 1;
			}
			else {
				fwrite(&buf, sizeof(play_t), 1, ftp);
			}
		}
		fclose(fp);
		fclose(ftp);
		remove("PlayTmp.dat");
		return found;
	}
}


//��ʶ����TTMS_SCU_Play_Perst_SelByID
//���ܣ����ļ�play.dat������ָ��ID�ľ�Ŀ��Ϣ��buf��
int Play_Perst_SelectByID(int id, play_t *buf) {
	assert(NULL!=buf);

	FILE *fp = fopen("play.dat", "rb");
	if (NULL == fp) {
        printf("���ܴ�play.dat!\n");
		return 0;
	}

	play_t data;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&data, sizeof(play_t), 1, fp)) {
			if (id == data.id) {
				*buf = data;
				found = 1;
				break;
			}
		}
	}
	fclose(fp);
	return found;
}
//�� �� ֵ�����ͣ���ʾ�ɹ������˾�Ŀ�ĸ�����
