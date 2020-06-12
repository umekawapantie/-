//�������ܣ���ȡ���о�Ŀ�����ݣ��γ���listΪͷָ��ľ�Ŀ������
//����˵����list��play_list_t����ָ�룬ָ���Ŀ������ͷָ�롣

#include <stdio.h>
#include <stdlib.h>
#include "../Persistence/Play_Persist.h"
#include "../Common/List.h"

int Play_Srv_FetchAll(play_list_t list) {
	return Play_Perst_SelectAll(list);
}


//����: �����¾�Ŀ
int Play_Srv_Add(play_t *data) {
	return  Play_Perst_Insert(data);
}


//����: �޸ľ�Ŀ
int Play_Srv_Modify(const play_t *data) {
	return Play_Perst_Update(data);
}


//����: 	ɾ����Ŀ
int Play_Srv_DeletByID(int id) {
	return Play_Perst_RemByID(id);
}


//����:  ����ID��ȡ�¾�Ŀ
int Play_Srv_FetchByID(int id,play_t *buf) {
	return Play_Perst_SelectByID(id, buf);
}
//�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���ȡ�����о�Ŀ�ı�־��
