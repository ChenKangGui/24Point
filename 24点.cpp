#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#define maxn 15

int Start,End,Clock=0;

typedef struct{
	int X;
	int Y; 
}Pos;

//int color(int num)  //num为每一种颜色所代表的数字，范围时0~15
//{
//    SetConsoleTextAttribute(GetStdhandle(STD_OUTPUT_HANDLE),num);
//    return 0;
//}
//void gotoxy(int x,int y)
//{
//
//    COORDpos;
//    Pos.X=x;   //横坐标
//    Pos.Y=y;   //纵坐标
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
//}

int arr[52];
char op[5] = {'#','+','-','*','/',};

int i = 0;
int check(int arg)
{        
	//判断arr数组里有没有重复的 
	int i;
	for ( i = 0; i < 52; i++)
	{
		if (arr[i] == arg)
			return 1;
		if (arr[i] == 0)
			return 0;
	}
	return 0;
}

typedef struct{
  int l;
  int card[26];
}*PTR,CARD;
PTR Person, Computer;   //定义人机

int Selection()
{		
	// 选择端 
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("~~~~~~~~~~~~~~ 24点小游戏·~~~~~~~~~~~~~~~\n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("0、Start A Game\n");
	printf("1、Ranking List\n");
	printf("2、exit\n");
	printf("Please choose a number(0 or 1 or 2 )：");
	int selection;
	scanf("%d", &selection);
	while (selection != 0 && selection != 1 && selection != 2)
	{
		printf("ERROR, Please reinput a choice！\n");
		scanf("%d", &selection);
	}
	system("cls"); //清空屏幕，清空缓存区
	fflush(stdin);
	return selection;
}

void Wash()
{
	int tmp = 0;
	memset(arr, 0, sizeof(arr));
	srand(time(NULL));
	while (i < 52)
	{
		tmp = rand() % 52 + 1;
		if (check(tmp) == 1)              //将1-52打乱存入数组arr 
			continue;
		arr[i] = tmp;
		i++;
	}
}

void Send()
{                          
	//将52等分后发送给人与机器
	Computer = (PTR)malloc(sizeof(CARD));
	Person = (PTR)malloc(sizeof(CARD));
	Computer->l = 26;
	Person->l = 26;
	memset(Computer->card, 0, sizeof(Computer->card));
	memset(Person->card, 0, sizeof(Person->card));
	for (i = 0; i < 26; i++)
	{
		Person->card[i] = arr[i] % 13 + 1;
		Computer->card[i] = arr[i + 26] % 13 + 1;
	}
}

int Show_up()
{                        
	//将牌打出来
	printf("Your Cards are:");
	for (i = 0; i < Person->l; i++)
	{
		if(Person->card[i]==1)
		{
			printf("{%d} |A|  ", i + 1);
		}
		else if(Person->card[i]==11)
		{
			printf("{%d} |J|   ", i + 1);
		}
		else if(Person->card[i]==12)
		{
			printf("{%d} |Q|   ", i + 1);
		}
		else if(Person->card[i]==13)
		{
			printf("{%d} |K|   ", i + 1);
		}
		else
		{
			printf("{%d} |%d|   ", i + 1, Person->card[i]);
		}
		printf("\n");
	}
	printf("\n");
	printf("Computer's Cards are：");
	for (i = 0; i < Computer->l; i++)
	{
		if(Person->card[i]==1)
		{
			printf("{%d} |A|  ", i + 1);
		}
		else if(Person->card[i]==11)
		{
			printf("{%d} |J|   ", i + 1);
		}
		else if(Person->card[i]==12)
		{
			printf("{%d} |Q|   ", i + 1);
		}
		else if(Person->card[i]==13)
		{
			printf("{%d} |K|   ", i + 1);
		}
		else
		{
			printf("{%d} |%d|   ", i + 1, Computer->card[i]);
		}
		printf("\n");
	}
	return 0;
}

void DeleteCard(int m1, int m2, PTR a){
  a->card[m1] = a->card[--a->l];
  a->card[m2] = a->card[--a->l];
}// 

void AddCard(int f[], int sign, PTR a){
  if (sign == 1){                     //0是Person，1是computer
    sign = 2;
  }
  a->card[a->l++] = f[sign++];
  a->card[a->l++] = f[sign];
}

//计算24点 
double fun(double a1,double a2,int b)//加减乘除的函数
{switch(b)
{case 0:return (a1+a2); 
case 1:return (a1-a2);
case 2:return (a1*a2);
case 3:if(a2!=0) return (a1/a2);
}
}
int get24(int save[4]){
	int i,j,k,l,n,m,r,flg=1;
	double num[4]={1,1,1,1},tem1,tem2,tem3,abc=1111;
	char sign[5]="+-*/";
	//printf("输入四个数:");
	printf("这四个数为：%d %d %d %d\n", save[0], save[1], save[2], save[3]);
	for(i=0;i<4;i++){
		num[i]=save[i];
	}
if(flg){
	flg=0;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			if(j!=i)
			{
				for(k=0;k<4;k++)
					if(k!=i&&k!=j)
					{
						for(l=0;l<4;l++)
							if(l!=i&&l!=j&&l!=k)
								{
									for(n=0;n<4;n++)
										for(m=0;m<4;m++)
											for(r=0;r<4;r++)
											{
												tem1=fun(num[i],num[j],n);
												tem2=fun(tem1,num[k],m);
												tem3=fun(tem2,num[l],r);
												if(tem3==24.0){
  												//printf("{(%d%c%d)%c%d}%c%d=24\n",save[i],sign[n],save[j],sign[m],save[k],sign[r],save[l]);
  												return 1;
											}
											else if(tem3==-24.0){
											    //printf("{%d%c(%d%c%d)}%c%d=24\n",save[k],sign[m],save[i],sign[n],save[j],sign[r],save[l]);
										    	return 1;
											}
											else if(tem3==1.0/24.0){
											  //printf("%d%c{(%d%c%d)%c%d}=24\n",save[l],sign[r],save[i],sign[n],save[j],sign[m],save[k]);
											  return 1;
											}
											else if(tem3==-1.0/24.0){
											  //printf("%d%c{%d%c(%d%c%d)}=24\n",save[l],sign[r],save[k],sign[n],save[i],sign[m],save[j]);
									  			return 1;
											}
											else
											{
												tem1=fun(num[i],num[j],n);
												tem2=fun(num[k],num[l],r);
												tem3=fun(tem1,tem2,m);
												if(tem3==24.0){
  												//printf("(%d%c%d)%c(%d%c%d)=24\n",save[i],sign[n],save[j],sign[m],save[k],sign[r],save[l]);
  													return 1;
												}
											}
									}
							}
					}
			}
	}
	if(!flg) return 0;
	return 1;
}

char s[maxn], infixList[maxn][10];
char suffix[maxn][10];
int p = 0;
char tmp[maxn];
int p1 = 0;

//把字符串根据操作数、运算符、括号拆开，存储到infixList数组中
//转换成后缀表达式
int toInfixExpression(char *s){
  int i, tot = 0, n = strlen(s);
  for ( i = 0; i < n; i++){
    if (s[i] >= '0' && s[i] <= '9'){ //储存数字
      int p = 0;
      infixList[tot][p++] = s[i];
      while (i + 1 < n && s[i + 1] >= '0' && s[i + 1] <= '9'){
        infixList[tot][p++] = s[++i];
      }
      tot++;
    }
    else //储存运算符及括号
      infixList[tot++][0] = s[i];
  }
  return tot;
}

//获得优先级
int getPriority(char c){
  if (c == '+' || c == '-')
    return 1;
  else if (c == '*' || c == '/')
    return 2;
  else
    return 0; //处理'('的情况
}

//转换成后缀表达式
void parseSuffixExpression(char s[][10], int n){
  for (i = 0; i < n; i++){
    if (s[i][0] >= '0' && s[i][0] <= '9'){
      strcpy(suffix[p], s[i]);
      p++;
    }
    else if (s[i][0] == '('){
      tmp[p1] = s[i][0];
      p1++;
    }
    else if (s[i][0] == ')'){
      while (tmp[p1 - 1] != '('){
        suffix[p++][0] = tmp[--p1];
      }
      p1--;
    }
    else{
      while (p1 != 0 && getPriority(tmp[p1 - 1]) >= getPriority(s[i][0])){
        suffix[p++][0] = tmp[--p1];
      }
      tmp[p1++] = s[i][0];
    }
  }
  while (p1 != 0){ //将剩余的符号加入
    suffix[p++][0] = tmp[--p1];
  }
}

//计算一个以字符串形式存储的数的值
int parseInt(char *s){
  int k = strlen(s);
  int ans = 0;
  for (i = 0; i < k; i++){
    ans = ans * 10 + (s[i] - '0');
  }
  return ans;
}

//将数k转化成字符串形式存储到指针s开始的地方
void parseString(char *s, int k){
  char b[5];
  int PTR = 0,j;
  do{
    b[PTR++] = (char)('0' + k % 10);
    k /= 10;
  } while (k != 0);
  for (i = PTR - 1,j = 0; i >= 0; i--, j++){
    *(s + j) = b[i];
  }
  *(s + PTR) = '\0';
}

//计算后缀表达式的值
int calculate(){
  int PTR = 0;
  char t[maxn][10];
  int i, m = 1;
  for ( i = 0; i < p; i++){
    int k = strlen(suffix[i]);
    if (suffix[i][0] >= '0' && suffix[i][0] <= '9'){
      strcpy(t[PTR++], suffix[i]);
      t[PTR - 1][k] = '\0';
    }
    else{
      int b = parseInt(t[--PTR]);
      int a = parseInt(t[--PTR]);
      int res = 0;
      if (suffix[i][0] == '+'){
        res = a + b;
        printf("(%d) %d + %d = %d\n", m++, a, b, res);
      }
      else if (suffix[i][0] == '-'){
        res = a - b;
        printf("(%d) %d - %d = %d\n", m++, a, b, res);
      }
      else if (suffix[i][0] == '*'){
        res = a * b;
        printf("(%d) %d * %d = %d\n", m++, a, b, res);
      }
      else if (suffix[i][0] == '/'){
        if (b == 0){
          printf("除数为零出错！！！\n");
          return -1;
        }
        res = a / b;
        printf("(%d) %d / %d = %d\n", m++, a, b, res);
      }
      parseString(t[PTR], res);
      PTR++;
    }
  }
  return parseInt(t[0]);
}

int js(){ //计算
  //输入字符串
  p = p1 = 0;
  printf("------------------------------\n");
  printf("请输入待计算的表达式:");
  scanf("%s", s);
  End=time(NULL);
  Clock=End-Start+Clock;
  printf("累计用时：%d\n",Clock);
  int infixNum = toInfixExpression(s);
  parseSuffixExpression(infixList, infixNum);
  printf("运算过程如下所示：\n");
  if (abs(calculate()-24)<=0.00000000001)	//测试精度 
    return 1;
  else
    return 0;
}

int debug(){
  int m1, m2, n1, n2;
  int f[4], sign = -1;
  printf("please input two cards that you wanna to send out for calculating(输入牌的序号)：\n");
  while (1){
    scanf("%d %d", &m1, &m2);
    if (m1 < 1 || m2 < 1 || m1 > Person->l || m2 > Person->l)
      printf("ERROR, please reinput！\n");
    else
      break;
  }
  srand(time(NULL));
  n1 = rand() % Computer->l;
  do{
    n2 = rand() % Computer->l;
  } while (n1 == n2);
  f[0] = Person->card[m1 - 1];
  f[1] = Person->card[m2 - 1];
  f[2] = Computer->card[n1];
  f[3] = Computer->card[n2];
  //检查四个数能否组成24.
  if (get24(f)){
    printf("请输入你的计算：(形如【(Ao(BoC))oD、((AoB)oC)oD、Ao(Bo(CoD))、(AoB)o(CoD) 】\n");
    Start=time(NULL);//开始计时

	if (js()){
      printf("恭喜你，输入正确！\n");
      DeleteCard(m1 - 1, m2 - 1, Person);
      AddCard(f, sign = 0, Computer);
    }
    else{
      printf("错误\n"); 
      DeleteCard(n1, n2, Computer);
      AddCard(f, sign = 1, Person);
      return 0;
    }
  }
  else{
    printf("不能凑成24点！\n");
    return 0;
  }
}

int main(){
  HERE:
  switch (Selection())
  {
    case 0:
        Wash();
        Send();
        while (Person->l)
		{
          Show_up();
          debug();
          fflush(stdin);
        }
  		system("cls");
  		printf("!!!BINGO!!!\n");
  		printf("TOTAL TIME ：%d\n",Clock);
  		system("pause");
        goto HERE;
        break;
    case 1:
        break;
    case 2:
        return 0;
  }
}
