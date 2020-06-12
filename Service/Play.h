/*Description : ��Ŀҵ���߼���ͷ�ļ�*/

#ifndef PLAY_H_
#define PLAY_H_


//��Ŀ����;
typedef enum{
	PLAY_TYPE_FILE=1,	//	��Ӱ
	PLAY_TYPE_OPERA=2,	//���
	PLAY_TYPE_CONCERT=3	//���ֻ�
}play_type_t;

//��Ŀ�ּ�
typedef enum{
	PLAY_RATE_CHILD=1,	    //��ͯ
	PLAY_RATE_TEENAGE=2,	//������
	PLAY_RATE_ADULT=3	    //����
}play_rating_t;


//��������
typedef struct{
	int year;
	int month;
	int day;
}ttms_date_t;

//��Ŀ���ݽṹ
typedef struct {
	int 			id;
	char			name[31];			//	��Ŀ����
	play_type_t 	type;				// ��Ŀ����
	char 			area[8];			// ��Ʒ����
	play_rating_t 	rating;				// ��Ŀ�ּ�
	int 			duration;			// ��Ŀʱ��
	ttms_date_t 	start_date;			// ��ӳ����
	ttms_date_t 	offline_date;		// ��������
	int				price;				//	Ʊ��
} play_t;

//˫������
typedef struct play_node {
	play_t data;				//ʵ������
	struct play_node *next;	    //����ָ��
	struct play_node *prev;	    //ǰ��ָ��
} play_node_t, *play_list_t;

//��ʶ����TTMS_SCU_Play_Srv_FetchAll
//����: ��ȡȫ����Ŀ
int Play_Srv_FetchAll(play_list_t list);

//��ʶ����TTMS_SCU_Play_Srv_Add
//����: �����¾�Ŀ
int Play_Srv_Add(play_t *date);

//��ʶ����TTMS_SCU_Play_Srv_Mod
//����: �޸ľ�Ŀ
int Play_Srv_Modify(const play_t *date);

//��ʶ����TTMS_SCU_Play_Srv_DelByID
//����: 	ɾ����Ŀ
int Play_Srv_DeletByID(int id);

//��ʶ����TTMS_SCU_Play_Srv_FetchByID
//����:  ����ID��ȡ�¾�Ŀ
int Play_Srv_FetchByID(int id,play_t *buf);

#endif
