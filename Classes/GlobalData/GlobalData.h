
#ifndef __GLOBALDATA__
#define __GLOBALDATA__


typedef struct Node
{
	//牌颜色
	int color;
	//牌上数字
	int num;
	//排序规则
	int sortVal;
	//输出的颜色
	int colorPosition;
	//是否被选择
	bool isSelect;

	//牌矩阵的大小
	float x,y,width,height;
	//需要删除
	bool needDelete;

	//排序规则
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
