#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NODE_NUM 100 //定义最大输入人数限度（链表在内存中的最大长度），让其可灵活变化

int Key[MAX_NODE_NUM];  //定义全局变量，用于打印每个人的密码

//定义结点
typedef struct LinkList
{
	int data;  //定义结点数据域
	struct LinkList *next;   //定义结点指针域，结构类型为 LinkList
	int kill;   //引入标记变量（标志记为杀与被杀  1为活 0为被杀）
}node;


//初始化链表
void Initialise(node **pNode,int item)//**pNode 指向指针的指针   指向的对象pNode还是指针
{
	 node *tmp;  //新结点
	 node *target;  //尾结点
	 int i=1;
	 while(i <= item)
	 {
		 if(* pNode == NULL)  //如果输入的链表是空。则创建一个新的节点，使其next指针指向自己
		 {
			 *pNode = (node *)malloc(sizeof(struct LinkList));  //向操作系统申请一块内存,大小为LinkLis,类型为node *的空间给pNode指针变量
			 if(!(* pNode))
			 {
				 exit(0);  //程序执行到此处时跳出不再执行
			 }
			 (*pNode)->data = i;  //将pNode结点的数据域赋值给i；
			 (*pNode)->kill=0;  //进行标记变量初始化，标记结点
			 (*pNode)->next = *pNode ;  //结点的指针域指向的下一个是它本身
			 i++;
		 }
		 else
		 {  //相当于一个插入操作，输入的链表不是空的，寻找链表的尾节点，使尾节点的next=新节点。新节点的next指向头节点//
			 target = *pNode;
			 while(target->next != *pNode)
			 {
				 target = target->next;  //尾结点的指针指向下一个结点，即新的结点
			 }
			 tmp = (node*)malloc(sizeof(struct LinkList ));  //为新结点申请存储空间
			 if(! tmp)
			 {
				 exit(0);  //没有新结点，跳出循环
             }

			 tmp->data = i;
			 i++;
			 tmp->next  = *pNode ;  //新结点指针指向头结点，形成循环链表
			 target->next  = tmp;  //尾结点指向新结点，此时新的结点就变成了新的尾结点
			 tmp->kill=0;  //该结点标记为活
	     }
    }
}


/*全局变量函数定义*/
void assign(int y)
{
     int i;
	 for(i=1;i<=y;i++)
	 {
	    printf("\n请输入第%d个人的密码:",i);
		scanf("%d",&Key[i]);

	 }

}
/*遍历链表，并打印初始的链表*/
 void Traversal(node *pNode)
 {
	 node *tmp;
	 tmp = pNode;
	 printf("\n\t-----------------循环链表初始打印-----------------\n");
	 do
	 {
		 printf("\n第%d个人,密码为:%d",tmp->data,Key[tmp->data]);  // 打印链表 例如；第一个人，密码为1

		 tmp = tmp->next ;  //打印完成后继续遍历下一个结点
	 }while(tmp!= pNode);  //当前节点再次回到头节点则结束
	 printf("\n\n完成初始链表的创建\n");
 }


/*删除结点，进行杀人游戏*/
void DeleteNode(node **pNode,int x,int y)
 {
	 int people = 1;

	 printf("\t-----------------删除出列情况打印-----------------\n\n");
	 node *target;
	 target = *pNode ;
	 while(people <= y)
	 {
	     int i=1;
	     if(people==1)
		{
		  while(i<x)
		 {

		 	target=target->next;
			 if(target->kill==0)   //未被杀，则进行标记
		 	{
		 		i++;
            }
		 }
        }
		 else
		 {
		 	while(i<=x)
		 {
		 	target=target->next;
			 if(target->kill==0)
		 	 {
		 		i++;
			 }
         }
	}
		 printf("第%d个人被杀 密码是%d\n",target->data,Key[target->data]);   //打印出列情况，例如 第1个人被杀，密码为1；
		 x=Key[target->data];   //将被杀的人的密码作为下一个循环开始的初始条件
		 target->kill=1; //被杀之后标记为一
		 people++;
	 }

 }


int main()
{
	 int x,y;
	 printf("请输入参与游戏的人数，最多为%d个人:\t",MAX_NODE_NUM);
	 scanf("%d",&y);
	 printf("\n请输入初始密码:\t");
	 scanf("%d",&x);
	 node *head = NULL;
	 Initialise (&head,y);
	 assign(y);
	 Traversal (head);
	 DeleteNode (&head,x,y);
	 return 0;
}
