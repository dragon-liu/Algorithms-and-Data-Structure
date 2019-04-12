// 赫夫曼树.cpp: 定义控制台应用程序的入口点。

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

//赫夫曼树以及赫夫曼树的存储表示，这里采用动态数组
typedef struct huffNode
{
    float weight;   //权重
    int lchild, rchild, parent;  //左右子节点和父节点
}HTNode, *HuffTree;
typedef char **HuffCode;

//找出数组中无父节点且权值最小的两个节点下标,分别用s1和s2保存
void select(const HuffTree &HT, int n, int &s1, int &s2);

//HT:哈夫曼树，HC:哈夫曼编码，w:构造哈夫曼树节点的权值，n:构造哈夫曼树节点的个数
void HuffmanCode(HuffTree &HT, HuffCode &HC, float *w, int n);

int main()
{
	int i;
	int n;
	char*leaf;  //保存编码的元素
	float* weight;  //保存对应权值
	printf("请输入要构造哈夫曼树的叶子节点数目:");
	scanf("%d", &n);
	getchar();
	leaf = (char*)malloc((n+1) * sizeof(char));
	if (!leaf)
	{
		printf("内存不够!");
		exit(0);
	}
	printf("请输入对应的编码元素（注意，因为采用scanf输入，请在输入字母时不按任何空白键，连续输入5个字母,比如ABCDE）:");
	for (i = 0; i < n; i++)
	{
		scanf("%c", &leaf[i + 1]);
	}//第0个元素保留不用
	weight=(float*)malloc((n+1)*sizeof(float)); //第0个元素保留不用
	if (!weight)
	{
		printf("内存不够!");
		exit(0);
	}
	printf("请输入对应的权值:");
	for (i = 0; i < n; i++)
	{
		scanf("%f", &weight[i + 1]);
	}
	HuffTree HT;
	HuffCode HC;
	HuffmanCode(HT, HC, weight,n);
	for (i = 0; i < n; i++)
	{
		printf("%c:%s\n", leaf[i+1], HC[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}

//找出数组中权值最小的两个节点下标,分别用s1和s2保存
void select(const HuffTree &HT, int n, int &s1, int &s2)
{
	int i;
	s1 = s2 = 0;
	float min1 = 1;//最小值，INT_MAX在<limits.h>中定义的
	float min2 = 1;//次小值

	for (i = 1; i <= n; ++i)
	{
		if (HT[i].parent == 0)
		{//筛选没有父节点的最小和次小权值下标
			if (HT[i].weight < min1)
			{//如果比最小值小
				min2 = min1;
				s2 = s1;
				min1 = HT[i].weight;
				s1 = i;
			}
			else if ((HT[i].weight >= min1) && (HT[i].weight < min2))
			{//如果大于等于最小值，且小于次小值
				min2 = HT[i].weight;
				s2 = i;
			}
			else
			{//如果大于次小值，则什么都不做
				;
			}
		}
	}
}

//HT:哈夫曼树，HC:哈夫曼编码，w:构造哈夫曼树节点的权值，n:构造哈夫曼树节点的个数
void HuffmanCode(HuffTree &HT, HuffCode &HC, float *w, int n)
{
	char temp; //临时变量
	int head,tail;   //逆序code
	int length; //每一个code的长度
	int s1=0;
	int s2=0;
	int m = 2 * n - 1;       //容易知道n个节点构造的哈夫曼树是2n-1个节点
	int i, c, f, j;
	char *code;  //暂存编码的
	HT = (HuffTree)malloc((m + 1) * sizeof(HTNode));  //0单元未使用


	for (i = 1; i <= n; i++) //初始化前n个节点(构造哈夫曼树的原始节点)
	{
	    HT[i].weight=w[i];
	    HT[i].lchild=0;
	    HT[i].rchild=0;
	    HT[i].parent=0;
	}

	for (i = n + 1; i <= m; i++) //初始化后n-1个节点

    {
        HT[i].weight=0;
	    HT[i].lchild=0;
	    HT[i].rchild=0;
	    HT[i].parent=0;
    }
	for (i = n + 1; i <= m; i++) //构建哈夫曼树
	{
		select(HT, i - 1, s1, s2);//找出前i-1个节点中权值最小的节点下标
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//哈夫曼编码
	HC = (char **)malloc((n) * sizeof(char *));
	//暂存编码
	code = (char *)malloc(n * sizeof(char));//使用了第0单元
	for (i = 1; i <= n; i++)
	{
		for (c = i, f = HT[c].parent, j = 0; f != 0; c = HT[c].parent, f = HT[c].parent, j++)
		{//从叶子扫描到根
			if (HT[f].lchild == c)
			{
				code[j] = '0';
			}
			else if (HT[f].rchild == c)
			{
				code[j] = '1';
			}
			else
			{//否则什么也不做
				;
			}

		}
		code[j]='\0';
		HC[i-1] = (char *)malloc(strlen(code) * sizeof(char));
		length = strlen(code);
		for (head = 0, tail = length - 1; head < tail; head++, tail--)
		{
			temp = code[head];
			code[head] = code[tail];
			code[tail] = temp;
		}
		strcpy(HC[i-1], code);
	}

}

