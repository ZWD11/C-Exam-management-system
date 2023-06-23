#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ERROR 0
#define OK 1

const char* MENU_FUNCTION[] =
{
	"(1)试题添加","(2)试题删除","(3)备份全部题目",
	"(4)删除全部题目","(5)试题修改","(6)试题查询:",
	"(7)统计题目","(8)查询题目","(9)自动生成试券"
	,"(10)退出程序"
};
  
typedef struct commodity {
	int num;//题目编号
	char topic[256];
	int type;//题目类型  1选择  2填空
	char choiceA[256];//选择题A 
	char choiceB[256];//选择题B
	char choiceC[256];//选择题C 
	char choiceD[256];//选择题D
	char answer[256];//答案 
} ElemType;

//单向链表//
typedef struct Node {
	ElemType data;//数据域 

	struct Node* next;//指针域 
} SNode;
typedef struct Linklist {

	int choiceNum;
	int TKNum;

	SNode * head;//指向第一个节点
	SNode * Tail;//链尾表部方便添加节点
} *SLinklist;
//单链表函数//
bool Init_SLinkList(SLinklist *L);
bool Creat_SLinkList_Tail(SLinklist L, ElemType e);
SNode* Find_SLinkNode_Val(SLinklist L, int num);
int Delete_DatainList(SLinklist L, int num);

int freeDatainList(SLinklist L);//销毁
void saveFile();//备份
bool loadFile();//加载备份

void mainMenu();//主菜单
void addTopic();//添加题目
void deleteTopic();//删除题目
void seek();//试题查询
void modify();//修改
void seetAsStr();//按用户输入查询题目并打印
void scsj();//生成试卷
void savesj(SLinklist xzList, SLinklist tkList);//保存试卷
void saveDa(SLinklist xzList, SLinklist tkList);//保存答案
void scst(SLinklist xzList, SLinklist tkList, int choiceNum, int TKNum);//生成试题
int run_flag;//运行标识
ElemType getCin;//保存输入

SLinklist list;//题目链表
int main()
{
	int item;
	Init_SLinkList(&list);
	run_flag = 1;
	printf("是否读取现有题库？\n1.读入2.不读入");
		scanf("%d", &item);
	if (item == 1)
	{
		while (!loadFile())
		{
			printf("\n是否读取现有题库？\n1.读入2.不读入");
			scanf("%d", &item);
			if (item != 1)
				break;
		}

	}
	while (run_flag)
	{
		mainMenu();
	}
	return 0;
}
void  mainMenu()
{

	int num;
	system("cls"); //清屏
	printf(" \n\n                    \n\n");
	printf("  ******************************************************\n\n");
	printf("  *                  题目生成系统                    *\n \n");
	printf("  ******************************************************\n\n");
	printf("*********************系统功能菜单*************************\n");
	printf("     *********************************************     \n");
	for (int i = 0; i < 10; i++)
	{
		printf("     %s\n", MENU_FUNCTION[i]);
		printf("               ******************                            \n");
	}
	printf("                  --------------------                    \n");
	printf("     请选择菜单编号:");
	scanf("%d", &num);
	getchar();
	switch (num)
	{
	case 1:
		addTopic();//添加题目
		break;
	case 2:
		deleteTopic();//删除题目
		break;

	case 3:
		saveFile();
		break;
	case 4:
		freeDatainList(list);//销毁
		Init_SLinkList(&list);//要在初始化一下
		printf("删除完成!\n");
		system("pause");
		break;
	case 5:
		modify();//修改
		break;
	case 6:
		seek();//试题查询
		break;
	case 7:
		printf("\n共有选择%d", list->choiceNum);
		printf("\n共有填空%d", list->TKNum);
		system("pause");
		break;
	case 8:
		seetAsStr();
		break;
	case 9:
		scsj();//生成试卷
		break;
	case 10:
		printf("即将退出程序!\n");
		run_flag = 0;
		break;
	default:
		printf("请在1-8之间选择\n");
	}
};
void savesj(SLinklist xzList, SLinklist tkList)//保存试卷
{

	int i=1;
	FILE *fp;
	char path[100];
	printf("请输入试卷保存位置\n");
	scanf("%s", path);
	fp = fopen(path, "w");
	if (!fp)
	{
		printf("\n文件保存失败！\n");
		return;
	}
	fprintf(fp, "姓名：_______ 班级：______ 分数:_____\n");
	fprintf(fp, "\n一、选择：\n");
	SNode * Node_L;
	Node_L = xzList->head;
	while (Node_L)
	{
		fprintf(fp, "(%d):%s\n", i++, Node_L->data.topic);
		fprintf(fp, "A:%s\n", Node_L->data.choiceA);
		fprintf(fp, "B:%s\n", Node_L->data.choiceB);
		fprintf(fp, "C:%s\n",  Node_L->data.choiceC);
		fprintf(fp, "D:%s\n", Node_L->data.choiceD);
		Node_L = Node_L->next;
	}

	fprintf(fp, "\n二、填空：\n");
	i = 1;
	Node_L = tkList->head;
	while (Node_L)
	{
		fprintf(fp, "(%d):%s\n", i++, Node_L->data.topic);
		Node_L = Node_L->next;
	}
	fclose(fp);
	printf("\n试卷保存完成");
}
void saveDa(SLinklist xzList, SLinklist tkList)//保存答案
{
	int i = 1;
	FILE *fp;
	char path[100];
	printf("请输入答案保存位置\n");
	scanf("%s", path);
	fp = fopen(path, "w");
	if (!fp)
	{
		printf("\n文件保存失败！\n");
		return;
	}
	fprintf(fp, "答案\n");
	fprintf(fp, "\n一、选择：\n");
	SNode * Node_L;
	Node_L = xzList->head;
	while (Node_L)
	{
		fprintf(fp, "(%d):%s\n", i++, Node_L->data.answer);
	
		Node_L = Node_L->next;
	}

	fprintf(fp, "\n二、填空：\n");
	i = 1;
	Node_L = tkList->head;
	while (Node_L)
	{
		fprintf(fp, "(%d):%s\n", i++, Node_L->data.answer);
		Node_L = Node_L->next;
	}
	fclose(fp);
	printf("\n答案保存完成");

}
void scst(SLinklist xzList, SLinklist tkList, int choiceNum,int TKNum)
{
	srand((unsigned)time(NULL)); // 初始化随机数 以时间为种，以达到随机的目的 
		SNode * Node_find;
	Node_find = list->head;//从头开始查找
	while (Node_find != NULL)
	{
		int scTKdlag = rand() % (list->TKNum +5)- TKNum;//加五为提高生成的速率用随机函数出题，大于0则加入 tkList 完成随机生产
	    int scXZdlag = rand() % (list->choiceNum + 5) - choiceNum;// 用随机函数出题，大于0则加入 大于0则加入 xzList 完成随机生产

		if (Node_find->data.type==1)
		{
			if (scXZdlag > 0)
			{
				if (xzList->choiceNum >= choiceNum)
				{
					continue;//达到要求
				}
				if (!Find_SLinkNode_Val(xzList, Node_find->data.num))//保证题目编号不重复
				{
					Creat_SLinkList_Tail(xzList, Node_find->data);
				}
				
	       
			}
		}
		else
		{
			if (scTKdlag > 0)
			{
				if (tkList->TKNum>= TKNum)
				{
					continue;//达到要求
				}
				if (!Find_SLinkNode_Val(tkList, Node_find->data.num))//保证不重复
				{
					Creat_SLinkList_Tail(tkList, Node_find->data);//创建一个链表尾接在填空题链表上 
				}
			
			}
		}
				
		Node_find = Node_find->next;
	}
}
void scsj()//生成试卷
{
	int item;
	int choiceNum;//选择数量
	int TKNum;//填空数量
	char sjFileName[253];//试卷文件名 
	char daFileName[256];//答案文件名
	SLinklist xzList;//选择题链表
	SLinklist tkList;//填空题链表
	Init_SLinkList(&xzList);//清空地址 
	Init_SLinkList(&tkList);//清空地址 
	while (1)
	{


		memset(&getCin, 0, sizeof(ElemType));//输入置0
		system("cls"); //清屏
		printf("  ******************************************************\n\n");
		printf("  *                    生成试卷                          *\n \n");
		printf("  ******************************************************\n\n");
		printf("  ---------------------------");

		printf("\n请输入要生成的选择题数量：" );

		scanf("%d", &choiceNum);
		while (list->choiceNum < choiceNum)//直到题目编号不重复或手动返回
		{
			printf("\n题库数量小于输入的数量：1重新输入，2返回");
			scanf("%d", &item);
			if (item != 1)
			{
				freeDatainList(xzList);//防止内存泄露       
				freeDatainList(tkList);//防止内存泄露
				return;
			}

			printf("\n  ******************\n");
			printf("  请输入要生成的选择题数量:");
			scanf("%d", &choiceNum);
		}
		printf("\n请输入要生成的填空题数量：");
		scanf("%d", &TKNum);
		while (list->TKNum < TKNum)//直到题目编号不重复或手动返回
		{
			printf("\n题库数量小于输入的数量：1重新输入，2返回");
			scanf("%d", &item);
			if (item != 1)
			{
				freeDatainList(xzList);//防止内存泄露       
				freeDatainList(tkList);//防止内存泄露

				return;
			}
			printf("\n  ******************\n");
			printf("  请输入要生成的填空题数量:");
			scanf("%d", &TKNum);
		} 
		while (1)
		{
			scst(xzList, tkList, choiceNum, TKNum);
			if (xzList->choiceNum>=choiceNum&&tkList->TKNum>=TKNum)//知道满足要求退出
			{
				break;
			}
		}

		savesj(xzList, tkList);
		saveDa(xzList, tkList);
		system("pause");
		break;//返回主菜单

	}

	freeDatainList(xzList);//防止内存泄露       
	freeDatainList(tkList);//防止内存泄露

}
void seetAsStr()
{
	int item;
	while (1)
	{


		memset(&getCin, 0, sizeof(ElemType));//输入置0
		system("cls"); //清屏
		printf("  ******************************************************\n\n");
		printf("  *                    试题查询(内容)                          *\n \n");
		printf("  ******************************************************\n\n");
		printf("  ---------------------------");
		printf("  请输入要查询题目内容:");
		scanf("%s", &getCin.topic);
		SNode * Node_find;
		Node_find = list->head;//从头开始查找
		while (Node_find != NULL)
		{
			char * i = strstr(Node_find->data.topic, getCin.topic);/*判断是否包含，包含i指向该字符串第一次出现的地址*/
			SNode *    nodet = Node_find;
			if (i)
			{
				printf("\n-------------------------------\n");
				printf("题目:%s\n", nodet->data.topic);
				if (nodet->data.type == 1)
				{

					printf("A:%s\n", nodet->data.choiceA);
					printf("B:%s\n", nodet->data.choiceB);
					printf("C:%s\n", nodet->data.choiceC);
					printf("D:%s\n", nodet->data.choiceD);

				}
				printf("答案:%s\n", nodet->data.answer);

			}
			Node_find = Node_find->next;
		}

		printf("\n\t\n1继续查询，2返回");
		scanf("%d", &item);
		if (item != 1)
			return;

	}

}
void saveFile()//备份
{
	FILE *fp;
	char path[100];
	printf("请输入备份路径\n");
	scanf("%s", path);
	fp = fopen(path, "w");
	if (!fp)
	{
		printf("\n文件保存失败！\n");
		return;
	}
	SNode * Node_L;
	Node_L = list->head;
	while (Node_L)
	{
		fwrite(&Node_L->data, sizeof(ElemType), 1, fp);
		Node_L = Node_L->next;
	}
	fclose(fp);
}
bool loadFile()//加载备份
{
	FILE* fp; char path[100];
	printf("请输入要载入的备份文件\n");
	scanf("%s", path);
	fp = fopen(path, "r");
	if (!fp)
	{
		printf("\n文件加载失败！\n");
		return false;
	}

	while (fread(&getCin, sizeof(ElemType), 1, fp))
	{
		Creat_SLinkList_Tail(list, getCin);
	}
	fclose(fp);
	return true;
}
void seek()//试题查询
{

	int item;
	while (1)
	{


		memset(&getCin, 0, sizeof(ElemType));//输入置0
		system("cls"); //清屏
		printf("  ******************************************************\n\n");
		printf("  *                    试题查询(编号)                          *\n \n");
		printf("  ******************************************************\n\n");
		printf("  ---------------------------");
		printf("  请输入要查询题目编号:");
		scanf("%d", &getCin.num);
		while (!Find_SLinkNode_Val(list, getCin.num))//直到题目编号不重复或手动返回
		{
			printf("\n该题目编号不存在：1重新输入，2返回");
			scanf("%d", &item);
			if (item != 1)
				return;
			printf("\n  ******************\n");
			printf("  请输入要查询题目编号:");
			scanf("%d", &getCin.num);
		}
		SNode* nodet = Find_SLinkNode_Val(list, getCin.num);
		printf("\n-------------------------------\n");
		printf("题目:%s\n", nodet->data.topic);
		if (nodet->data.type == 1)
		{

			printf("A:%s\n", nodet->data.choiceA);
			printf("B:%s\n", nodet->data.choiceB);
			printf("C:%s\n", nodet->data.choiceC);
			printf("D:%s\n", nodet->data.choiceD);

		}
		printf("答案:%s\n", nodet->data.answer);
		printf("\n\t\n1继续查询，2返回");
		scanf("%d", &item);
		if (item != 1)
			return;
	}
}
void modify()//修改
{
	int item;
	while (1)
	{
		printf("请输入");

		memset(&getCin, 0, sizeof(ElemType));//输入置0
		system("cls"); //清屏
		printf("  ******************************************************\n\n");
		printf("  *                    修改题目                          *\n \n");
		printf("  ******************************************************\n\n");
		printf("  ---------------------------");
		printf("  请输入要修改题目编号:");
		scanf("%d", &getCin.num);
		while (!Find_SLinkNode_Val(list, getCin.num))//直到题目编号不重复或手动返回
		{
			printf("\n该题目编号不存在：1重新输入，2返回");
			scanf("%d", &item);
			if (item != 1)
				return;
			printf("\n  ******************\n");
			printf("  请输入要修改题目编号:");
			scanf("%d", &getCin.num);
		}
		SNode* nodet = Find_SLinkNode_Val(list, getCin.num);

		printf("  请输入新的题目类型(1选择,2填空):");
		scanf("%d", &nodet->data.type);
		while (nodet->data.type < 1 || nodet->data.type>2)//题目编号必须为1或2
		{
			printf("\n请在1-2中间选择");
			printf("\n  ******************\n");
			printf("  请输入题目型(1选择,2填空):");
			scanf("%d", &nodet->data.num);
		}
		printf("\n  ******************\n");

		printf("\n请输入新的题目：");
		scanf("%s", nodet->data.topic);
		if (nodet->data.type == 1)
		{
			printf("\n  ******************\n");
			printf("\n请输入选项A:");
			scanf("%s", nodet->data.choiceA);
			printf("\n请输入选项B:");
			scanf("%s", nodet->data.choiceB);
			printf("\n请输入选项C:");
			scanf("%s", nodet->data.choiceC);
			printf("\n请输入选项D:");
			scanf("%s", nodet->data.choiceD);

		}
		printf("\n请输入答案:");
		scanf("%s", nodet->data.answer);

		while (nodet->data.type == 1 &&
			nodet->data.answer[0] != 'A'&&
			nodet->data.answer[0] != 'B'&&
			nodet->data.answer[0] != 'C'&&
			nodet->data.answer[0] != 'D')//题目编号必须为1或2
		{
			printf("\n选择答案请在 A B C D中间选择");
			printf("\n  ******************\n");
			printf("  请输入答案:");
			scanf("%s", nodet->data.answer);
		}

		printf("\n\t\t修改成功！1继续修改，2返回");
		scanf("%d", &item);
		if (item != 1)
			return;
	}
}
void deleteTopic()//删除题目
{
	int item;
	while (1)
	{
		printf("请输入");

		memset(&getCin,0, sizeof(ElemType));//输入置0
		system("cls"); //清屏
		printf("  ******************************************************\n\n");
		printf("  *                    删除题目                          *\n \n");
		printf("  ******************************************************\n\n");
		printf("  ---------------------------");
		printf(" 请输入要删除题目编号:");
		scanf("%d", &getCin.num);
		while (!Find_SLinkNode_Val(list, getCin.num))//直到题目编号不重复或手动返回
		{
			printf("\n该题目编号不存在：1重新输入，2返回");
			scanf("%d", &item);
			if (item != 1)
				return;
			printf("\n  ******************\n");
			printf("  请输入要删除题目编号:");
			scanf("%d", &getCin.num);
		}

		Delete_DatainList(list, getCin.num);
		printf("\n\t\t删除成功！1继续删除，2返回");
		scanf("%d", &item);
		if (item != 1)
 			return;
	}

}
void addTopic()//添加题目
{
	int item;
	while (1)
	{
		printf("请输入");
		memset(&getCin, 0, sizeof(ElemType));//输入置0
		system("cls"); //清屏
		printf("  ******************************************************\n\n");
		printf("  *                    添加题目                          *\n \n");
		printf("  ******************************************************\n\n");
		printf("  ---------------------------");
		printf("  请输入题目编号:");
		scanf("%d", &getCin.num);
		while (Find_SLinkNode_Val(list, getCin.num))//直到题目编号不重复或手动返回
		{
			printf("\n该题目编号已存在：1重新输入，2返回");
			scanf("%d", &item);
			if (item != 1)
				return;
			printf("\n  ******************\n");
			printf("  请输入题目编号:");
			scanf("%d", &getCin.num);
		}
		printf("\n  ******************\n");
		printf("  请输入题目类型(1选择,2填空):");
		scanf("%d", &getCin.type);
		while (getCin.type < 1 || getCin.type>2)//题目编号必须为1或2
		{
			printf("\n请在1-2中间选择");
			printf("\n  ******************\n");
			printf("  请输入题目型(1选择,2填空):");
			scanf("%d", &getCin.num);
		}
		printf("\n  ******************\n");

		printf("\n请输入题目：");
		scanf("%s", getCin.topic);
		if (getCin.type == 1)
		{
			printf("\n  ******************\n");
			printf("\n请输入选项A:");
			scanf("%s", getCin.choiceA);
			printf("\n请输入选项B:");
			scanf("%s", getCin.choiceB);
			printf("\n请输入选项C:");
			scanf("%s", getCin.choiceC);
			printf("\n请输入选项D:");
			scanf("%s", getCin.choiceD);

		}
		printf("\n请输入答案:");
		scanf("%s", getCin.answer);
		while (getCin.type == 1 &&
			getCin.answer[0] != 'A'&&
			getCin.answer[0] != 'B'&&
			getCin.answer[0] != 'C'&&
			getCin.answer[0] != 'D')//题目编号必须为1或2
		{
			printf("\n选择答案请在 A B C D中间选择");
			printf("\n  ******************\n");
			printf("  请输入答案:");
			scanf("%s", getCin.answer);
		}

		Creat_SLinkList_Tail(list, getCin);//加入链表

		printf("\n\t\t添加成功！1继续输入，2返回");
		scanf("%d", &item);
		if (item != 1)
			return;
	}



}

//初始化单链表
bool Init_SLinkList(SLinklist* L)
{
	//开辟头节点空间
	(*L) = (SLinklist)malloc(sizeof(SNode));
	if (!(*L))
	{
		printf("malloc error!");
		return false;
	}
	//开始没有节点头 和尾指向空

	(*L)->choiceNum = 0;//选择数量
	(*L)->TKNum = 0;//填空数量
	(*L)->head = NULL;
	(*L)->Tail = NULL;
	return true;
}

//尾插法建立单链表
bool Creat_SLinkList_Tail(SLinklist L, ElemType e)
{

	SNode *  Node_new;

	Node_new = (SNode *)malloc(sizeof(SNode));
	if (!Node_new)
	{
		printf("malloc error!");
		return false;
	}
	Node_new->data = e;//新节点数据赋值
	Node_new->next = NULL;//新节点下一个没有数据

	if (!L->head)//链表头没有数据  指向第一个
	{
		L->Tail = L->head = Node_new;

	}
	else
	{
		L->Tail->next = Node_new;//尾节点下一个节点指向新的节点
		L->Tail= Node_new;
	}
		
	if (e.type == 1) {
		(L)->choiceNum++;//选择数量


	}
	else
	{
		(L)->TKNum++;//填空数量

	}


	return true;
}

//按题目编号查找单链表
SNode* Find_SLinkNode_Val(SLinklist L, int num)
{
	SNode * Node_find;
	Node_find = L->head;//从头开始查找
	while (Node_find != NULL)
	{

		if (Node_find->data.num == num)
		{
			return Node_find;
		}
		Node_find = Node_find->next;
	}
	return NULL;

}
//删除单链表指定题目编号的数据//
int Delete_DatainList(SLinklist L, int num)
{

	SNode * node_L, *node_delete;
	node_L = NULL;
	node_delete = L->head;

	while (node_delete != NULL)
	{
		if (node_delete->data.num == num)
		{
			break;//找到跳出循环
		}
		node_L = node_delete;//保存前一个节点
		node_delete = node_L->next;
	}
	if (!node_delete)
	{

		return false;
	}
	if (!node_L)//删除头节点
	{
		L->head = node_delete->next;
	}
	else {

		node_L->next = node_delete->next;

	}
	if (node_delete->data.type == 1) {
		(L)->choiceNum--;//选择数量

	}
	else
	{
		(L)->TKNum--;//填空数量

	}
	free(node_delete);

	return OK;//宏定义有 ok为 1 
}
int freeDatainList(SLinklist L)
{
	int len = 0;//链表长度初始化 
	SNode * Node_L;
	Node_L = L->head;
	while (Node_L != NULL)
	{
		SNode * de = Node_L;//临时保存删除节点指针
		len++;//链表长度相加 
		Node_L = Node_L->next;//指向下一节点
		free(de);//释放节点内存
	}
	free(L);//释放链表头
	return len;//返回销毁数量
}
