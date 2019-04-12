// �շ�����.cpp: �������̨Ӧ�ó������ڵ㡣

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

//�շ������Լ��շ������Ĵ洢��ʾ��������ö�̬����
typedef struct huffNode
{
    float weight;   //Ȩ��
    int lchild, rchild, parent;  //�����ӽڵ�͸��ڵ�
}HTNode, *HuffTree;
typedef char **HuffCode;

//�ҳ��������޸��ڵ���Ȩֵ��С�������ڵ��±�,�ֱ���s1��s2����
void select(const HuffTree &HT, int n, int &s1, int &s2);

//HT:����������HC:���������룬w:������������ڵ��Ȩֵ��n:������������ڵ�ĸ���
void HuffmanCode(HuffTree &HT, HuffCode &HC, float *w, int n);

int main()
{
	int i;
	int n;
	char*leaf;  //��������Ԫ��
	float* weight;  //�����ӦȨֵ
	printf("������Ҫ�������������Ҷ�ӽڵ���Ŀ:");
	scanf("%d", &n);
	getchar();
	leaf = (char*)malloc((n+1) * sizeof(char));
	if (!leaf)
	{
		printf("�ڴ治��!");
		exit(0);
	}
	printf("�������Ӧ�ı���Ԫ�أ�ע�⣬��Ϊ����scanf���룬����������ĸʱ�����κοհ׼�����������5����ĸ,����ABCDE��:");
	for (i = 0; i < n; i++)
	{
		scanf("%c", &leaf[i + 1]);
	}//��0��Ԫ�ر�������
	weight=(float*)malloc((n+1)*sizeof(float)); //��0��Ԫ�ر�������
	if (!weight)
	{
		printf("�ڴ治��!");
		exit(0);
	}
	printf("�������Ӧ��Ȩֵ:");
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

//�ҳ�������Ȩֵ��С�������ڵ��±�,�ֱ���s1��s2����
void select(const HuffTree &HT, int n, int &s1, int &s2)
{
	int i;
	s1 = s2 = 0;
	float min1 = 1;//��Сֵ��INT_MAX��<limits.h>�ж����
	float min2 = 1;//��Сֵ

	for (i = 1; i <= n; ++i)
	{
		if (HT[i].parent == 0)
		{//ɸѡû�и��ڵ����С�ʹ�СȨֵ�±�
			if (HT[i].weight < min1)
			{//�������СֵС
				min2 = min1;
				s2 = s1;
				min1 = HT[i].weight;
				s1 = i;
			}
			else if ((HT[i].weight >= min1) && (HT[i].weight < min2))
			{//������ڵ�����Сֵ����С�ڴ�Сֵ
				min2 = HT[i].weight;
				s2 = i;
			}
			else
			{//������ڴ�Сֵ����ʲô������
				;
			}
		}
	}
}

//HT:����������HC:���������룬w:������������ڵ��Ȩֵ��n:������������ڵ�ĸ���
void HuffmanCode(HuffTree &HT, HuffCode &HC, float *w, int n)
{
	char temp; //��ʱ����
	int head,tail;   //����code
	int length; //ÿһ��code�ĳ���
	int s1=0;
	int s2=0;
	int m = 2 * n - 1;       //����֪��n���ڵ㹹��Ĺ���������2n-1���ڵ�
	int i, c, f, j;
	char *code;  //�ݴ�����
	HT = (HuffTree)malloc((m + 1) * sizeof(HTNode));  //0��Ԫδʹ��


	for (i = 1; i <= n; i++) //��ʼ��ǰn���ڵ�(�������������ԭʼ�ڵ�)
	{
	    HT[i].weight=w[i];
	    HT[i].lchild=0;
	    HT[i].rchild=0;
	    HT[i].parent=0;
	}

	for (i = n + 1; i <= m; i++) //��ʼ����n-1���ڵ�

    {
        HT[i].weight=0;
	    HT[i].lchild=0;
	    HT[i].rchild=0;
	    HT[i].parent=0;
    }
	for (i = n + 1; i <= m; i++) //������������
	{
		select(HT, i - 1, s1, s2);//�ҳ�ǰi-1���ڵ���Ȩֵ��С�Ľڵ��±�
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//����������
	HC = (char **)malloc((n) * sizeof(char *));
	//�ݴ����
	code = (char *)malloc(n * sizeof(char));//ʹ���˵�0��Ԫ
	for (i = 1; i <= n; i++)
	{
		for (c = i, f = HT[c].parent, j = 0; f != 0; c = HT[c].parent, f = HT[c].parent, j++)
		{//��Ҷ��ɨ�赽��
			if (HT[f].lchild == c)
			{
				code[j] = '0';
			}
			else if (HT[f].rchild == c)
			{
				code[j] = '1';
			}
			else
			{//����ʲôҲ����
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

