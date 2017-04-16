#include<iostream>
#include<cstdlib>
using namespace std;

//������������
#define N 20

//�����Զ�������
typedef int DataType;

//�����������Ҷ�ӽ��Ľṹ
typedef struct node {
	char ch;
	DataType weight;	//�ٶ�Ҷ�ӵ�ȨֵΪ����
	int lchild, rchild, parent;
}Htnode;

//������������Ĵ洢�ṹ
typedef struct {
	char *code;		//Ψһ����
	char leaf;		//Ҷ�ӵ�ַ
	int length;		//����ĳ���
}CodeType;			//Ҷ�ӱ�������

//��������
void Hufcoding(Htnode huftree[],CodeType cd[], int w[],int n);//�����������
int selectMin(Htnode *huftree, int i);/* ��1��i-1��ѡ����С����������˫��Ϊi */

int main()
{
	return 0;
}

//�����������
void Hufcoding(Htnode huftree[], CodeType cd[], int w[], int n)
{
	//�����������ھ�̬����huftree�У�w��Ž��Ȩ�أ�n��Ҷ�Ӹ��������ı������cd[]��
	int i, k, s1, s2, m, f, c, sum;
	char temp[N];	//�ݴ�Ҷ�ӵı����ַ����������Ҫת��
	m = 2 * n - 1;	//������������Ľ������
	for (i = 1; i <= n; i++)	//��ʼ����̬����ÿ������Գ�һ����
	{
		huftree[i].weight = w[i - 1];
		huftree[i].lchild = huftree[i].rchild = huftree[i].parent = -1;
		huftree[i].ch = getchar();
	}
	for (i = n + 1; i <= m; i++)	//��ʼ��
	{
		huftree[i].weight = -1;
		huftree[i].lchild = huftree[i].rchild = huftree[i].parent = -1;
	}

	s1 = s2 = 1;//���������е�Ҷ�ӹ��٣��˴�Ϊ������

	for (i = 1; i <= m; i++)	//����n-1����Ҷ�ӽ���ѭ��
	{
		s1 = selectMin(huftree, n + i - 1);
		s2 = selectMin(huftree, n + i - 1);
		sum = huftree[s1].weight + huftree[s2].weight;
		huftree[n + i].weight = sum;
		huftree[s1].parent = huftree[s2].parent = n + i;
		huftree[n + i].lchild = s1;
		huftree[n + i].rchild = s2;
	}

	for (i = 1;i <= n; i++)		//��ʼ��ÿ��Ҷ�ӽ��ı���
	{
		c = 0;
		for (k = i, f = huftree[i].parent; f != -1; k = f, f = huftree[f].parent)
		{
			if (huftree[f].lchild == k)
			{
				temp[c] = '0';
				c++;
			}
			else
			{
				temp[c] = '1';
				c++;
			}
		}
		cd[i].code = (char *) malloc (c + 1);
		cd[i].code[c] = '\0';
		c--;
		k = 0;
		while (c >= 0)
		{
			cd[i].code[k++] = temp[c--];//��tempת�õ�code��
		}
		cd[i].leaf = huftree[i].ch;
		cd[i].length = k;
	}//forѭ������
}

/* ��1��i-1��ѡ����С����������˫��Ϊi */
int selectMin(Htnode *huftree, int i)
{
	int k, s,Min;
	Min = 32767; s = 0;
	for (k = 1; k<i; k++) /* ѡ����С���� */
	{
		if (huftree[s].parent == -1 && huftree[k].weight<Min)
		{
			s = k;
			Min = huftree[k].weight;
		}
	}
	huftree[s].parent = i;
	return s;
}
