
#ifndef __GLOBALDATA__
#define __GLOBALDATA__


typedef struct Node
{
	//����ɫ
	int color;
	//��������
	int num;
	//�������
	int sortVal;
	//�������ɫ
	int colorPosition;
	//�Ƿ�ѡ��
	bool isSelect;

	//�ƾ���Ĵ�С
	float x,y,width,height;
	//��Ҫɾ��
	bool needDelete;

	//�������
	bool operator <(const Node &tempCard) const
	{
		if(sortVal==tempCard.sortVal)
		{
			return color<tempCard.color;
		}
		else
		{
			return sortVal>tempCard.sortVal;
		}
	}
}Card;


#endif
