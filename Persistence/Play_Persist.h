/*Description : ������Ŀ���߼���ͷ�ļ�*/

#ifndef PLAY_PERSIST_H_
#define PLAY_PERSIST_H_

#include "../Service/Play.h"


//���ܣ����ļ�play.dat���������о�Ŀ��Ϣ
int Play_Perst_SelectAll(play_list_t list);

//���ܣ����Ŀ�����ļ�play.dat�е�ĩβ����һ���µľ�Ŀ��Ϣ
int Play_Perst_Insert(play_t *date);


//���ܣ������ļ�play.dat�е�һ����Ŀ��Ϣ
int	Play_Perst_Update(const play_t *date);


//���ܣ���ȥ�ļ�play.dat��ָ��ID�ľ�Ŀ��Ϣ
int Play_Perst_RemByID(int id);


//���ܣ����ļ�play.dat������ָ��ID�ľ�Ŀ��Ϣ��buf��
int Play_Perst_SelectByID(int id,play_t *buf);


#endif	/* PLAY_PERSIST_H_ */
