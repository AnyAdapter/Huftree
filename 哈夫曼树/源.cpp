#include<iostream>
#include<cstdlib>
using namespace std;

//定义结点最大个数
#define N 20

//定义自定义类型
typedef int DataType;

//定义哈夫曼树叶子结点的结构
typedef struct node {
	char ch;
	DataType weight;	//假定叶子的权值为整型
	int lchild, rchild, parent;
}Htnode;

//定义哈夫曼树的存储结构
typedef struct {
	char *code;		//唯一编码
	char leaf;		//叶子地址
	int length;		//编码的长度
}CodeType;			//叶子编码类型

//声明函数
void Hufcoding(Htnode huftree[],CodeType cd[], int w[],int n);//构造哈夫曼树
int selectMin(Htnode *huftree, int i);/* 在1～i-1中选择最小的树且设其双亲为i */

int main()
{
	return 0;
}

//构造哈弗曼树
void Hufcoding(Htnode huftree[], CodeType cd[], int w[], int n)
{
	//哈弗曼树放在静态链表huftree中，w存放结点权重，n是叶子个数，最后的编码放在cd[]中
	int i, k, s1, s2, m, f, c, sum;
	char temp[N];	//暂存叶子的编码字符串，最后需要转置
	m = 2 * n - 1;	//计算哈夫曼树的结点总数
	for (i = 1; i <= n; i++)	//初始化静态链表，每个结点自成一课树
	{
		huftree[i].weight = w[i - 1];
		huftree[i].lchild = huftree[i].rchild = huftree[i].parent = -1;
		huftree[i].ch = getchar();
	}
	for (i = n + 1; i <= m; i++)	//初始化
	{
		huftree[i].weight = -1;
		huftree[i].lchild = huftree[i].rchild = huftree[i].parent = -1;
	}

	s1 = s2 = 1;//若哈夫曼中的叶子过少，此处为错误处理

	for (i = 1; i <= m; i++)	//生成n-1个非叶子结点的循环
	{
		s1 = selectMin(huftree, n + i - 1);
		s2 = selectMin(huftree, n + i - 1);
		sum = huftree[s1].weight + huftree[s2].weight;
		huftree[n + i].weight = sum;
		huftree[s1].parent = huftree[s2].parent = n + i;
		huftree[n + i].lchild = s1;
		huftree[n + i].rchild = s2;
	}

	for (i = 1;i <= n; i++)		//开始求每个叶子结点的编码
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
			cd[i].code[k++] = temp[c--];//将temp转置到code中
		}
		cd[i].leaf = huftree[i].ch;
		cd[i].length = k;
	}//for循环结束
}

/* 在1～i-1中选择最小的树且设其双亲为i */
int selectMin(Htnode *huftree, int i)
{
	int k, s,Min;
	Min = 32767; s = 0;
	for (k = 1; k<i; k++) /* 选择最小的树 */
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
