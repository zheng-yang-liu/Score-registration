#include<stdio.h>
#include<stdlib.h>
#include<string.h>//strcpy(,)...函数所在文件 
#define N 3961//（宏定义）N：最多能处理的学生数 （进过测试N=3961为此程序的极限超过会出错） 
#define M 20//最大课程数 
//定义结构变量 
typedef struct student
{
	int registrati;//registrati：登记 
	char name[20];//姓名
	char course[20];//课程 
	int score[M];//成绩  ——最多能储存13科的课程成绩 
	float aver;//平均值 
}STUDENT;
//定义结构变量用于查询从原文件读取到的课程名与想要保存的课程名进行对比是否相同 
typedef struct inquire1//inqiure:查询 
{
	char course1[20];//课程
}INQUIRE1;
//定义结构变量用于排名函数中的( 暂存 、转换 )操作 
typedef struct transform//transform:转化 
{  
	int registrati;//学号 
	char name[20];//姓名
	char course[15];//课程
	int score1,score2;//成绩 
	float aver;//平均值 
}TRANSFROM;
//定义全局变量供保存和读取数据函数使用 
FILE *fp;
char fname2[32];
//自定义函数 
void menu();//定义一个模板函数 
void inputscore(STUDENT s[],int n,int m,int n2,int choose,int mark1);//定义一个录入成绩的函数 
void inputOperate(STUDENT s[],int n,int m,int n2,int choose);//录入操作函数 
void displayscore(STUDENT s[],int n,int m);//显示各科成绩的函数 
void displayaverage(STUDENT s[],int n,int m);//显示各个课程的平均成绩的函数
void ranking(STUDENT s[],int n,int m);//进行排名的函数 （根据学生平均值进行排名） 
void rankingOperate(STUDENT s[],int n,int m);//进行排名操作的函数 （根据学生平均值进行排名） 
void displayranking(STUDENT s[],int n,int m);//显示课程最高分的函数 
void displayfirst(STUDENT s[],int n,int m);//寻找并显示第一名的信息
void averagescore(STUDENT s[],int n,int m);//计算平均成绩的函数 
void inquire(STUDENT s[],int n,int m);//定义一个查询某位学生成绩的函数 
void revise(STUDENT s[],int n,int m);//修改学生信息的函数 
void savef(STUDENT s[],int n,int m,int n2,int choose3,int mark2);//定义一个保存函文件函数 
void savefOperate(STUDENT s[],int n,int m,char *fname1);//定义一个保存操作函文件函数 
int readf(STUDENT s[],int m);//定义一个读取文件函数 
int readfOperate(STUDENT s[],int m,char *fname1);//定义一个读取文件操作函数 
int deletedata(STUDENT s[],int n,int m);//删除某位学生的信息的函数 
int askrevise();//询问是否继续进行修改的函数 
int checkregistrati(STUDENT s[],int n,int inid2,char inname2[]);//核对学生信息 
void operationmark();//操作进行标志
int main()
{
	STUDENT stu[N];
	int choose2;
	int mark1=1;// “mark1=1”没进行过 ( 11、读取数据 ）操作时的标记值  
	int mark2=1;//"mark2=1"未进行过（3、进行排名）操作时的标记值 
	int choose3=2;//默认（ 10、保存数据 ）操作中的" choose3=2 "
	int choose;
	int n=0,m=0,n2=0;
	while(1)
	{	menu();
		printf("请选择：");
		scanf("%d",&choose2);
		switch(choose2)
		{
			case 1: printf("\n\n--您处于录入成绩界面--\n\n");
					printf("--录入方式有：--");
					printf("\n\n--1、录    入：  --\n");
					printf("--2、追加录入：--\n\n");
					printf("\n\n--请选择：");
					scanf("%d",&choose);
					if(choose==1)
					{
						printf("\n最多能处理学生%d人\n",N);
						printf("请输入要处理的学生数:");
						scanf("%d",&n);
						if(n>=N)
						{
							printf("处理学生人数超过%d人\n",N);
							printf("请重新输入要处理的学生数");
							scanf("%d",&n);
						}
						if(n<N)
						{
							printf("\t###最多输入%d门课程\n请输入科程数:",M);
							scanf("%d",&m);
							inputscore(stu,n,m,0,choose,mark1);
							printf("\n");
							system("pause");
						}
						break;
					}
					if(choose=2)
					{
						printf("\n最多能处理学生%d人\n",N);
						printf("请输入要处理的学生数");
						scanf("%d",&n2);
						if(n2>=N)
						{
							printf("处理学生人数超过%d人\n",N);
							printf("请重新输入要处理的学生数");
							scanf("%d",&n2);
						}
						if(n2<N)
						{
							if(m==0)
							{
								printf("\t###最多输入%d门课程\n请输入原文件中的课程数",M);
								scanf("%d",&m);
							}
							inputscore(stu,n,m,n2,choose,mark1);
							printf("\n");
							system("pause");
						}
						n=n+n2;//更改学生人数 
						printf("追加录入后有学生：%d 人",n);
						printf("\n");
						system("pause");
						break;
					}
			case 2: averagescore(stu,n,m);//求平均值 
					printf("\n");
					system("pause");
					break; 
			case 3: ranking(stu,n,m); //排名 
					mark2=0;
					system("pause"); 
					break; 
			case 4: displayscore(stu,n,m);//显示所有课程的成绩 
					printf("\n");
					system("pause");
					break; 		
			case 5: displayaverage(stu,n,m);//显示各个课程的平均成绩 
					printf("\n");
					system("pause");
					break;
			case 6: displayranking(stu,n,m); //排名后的的成绩 
					printf("\n");
					system("pause");
					break; 
			case 7: inquire(stu,n,m);//查询某位学生的成绩 
					printf("\n");
					system("pause");
					break; 
			case 8: revise(stu,n,m);//修改学生数据 
					printf("\n");
					system("pause");
					break; 
			case 9: n=deletedata(stu,n,m);//删除学生信息 
					printf("\n");
					system("pause");
					break; 
			case 10: savef(stu,n,m,n2,choose3,mark2);//保存数据 
					printf("\n");
					system("pause");
					break; 
			case 11: printf("请输入课程数：");//读取数据 
					scanf("%d",&m); 
					n=readf(stu,m);//n代表读取到的学生数 
					mark1=0;//进行过 ( 11、读取数据 ）操作时的标记值  
					printf("\n");
					system("pause");
					break; 
			case 0: exit(0);
					printf("\n");
					system("pause");
					break;
		}
		if(mark1==0)//只要进行了读取操作进行此操作 
			choose3=1;
		system("cls");
	}
	return 0; 
}
//菜单 
void menu()
{
	printf("**********************************\n\n"); 
	printf("     **学生成绩登记系统**\n\n");
	printf("**********************************\n");
	printf("\t 1、录入成绩\n");
	printf("\t 2、求平均成绩\n");
	printf("\t 3、进行排名\n");
	printf("\t 4、显示各科成绩\n");
	printf("\t 5、显示各个课程的平均成绩\n");
	printf("\t 6、显示各科的最高分\n");
	printf("\t 7、查询某位学生的成绩\n");
	printf("\t 8、修改某位学生的信息\n");
	printf("\t 9、删除某位学生的信息\n");
	printf("\t10、保存数据\n");
	printf("\t11、读取数据\n");
	printf("\t 0、退出\n");
	printf("**********************************\n");
}
//录入学生成绩 
void inputscore(STUDENT s[],int n,int m,int n2,int choose,int mark1)
{
	INQUIRE1 inq[n];//暂存从原文件中读取到的课程以及课程顺序 
	int i,j,k; 
	FILE *fp;
	char *fname1;
	int mark=1;//mark：标记 “mark=1”无（11、读取数据）操作时的标志值 
	int mark2=1;//“mark2=1”文件打开正确是的标记值 
	if(choose==1)//《录入操作》
	{
		for(k=0;k<m;k++)
		{
			printf("\n请输入第%d门课程名：",k+1);	
			scanf("%s",&s[k].course);
		}
		inputOperate(s,n,m,0,1);
	}
	if(choose==2)//《追加录入》
	{
		if(mark1==1)//无（11、读取数据）操作时进行 
		{
			printf("\n请输入您追加录入后数据的保存文件名："); 
			scanf("%s",&fname2);
			fname1=fname2;
			if((fp=fopen(fname1,"r"))==NULL)//此操作减小犯错率
				mark2=0;
			if(mark2==1)
			{
				for(k=0;k<m;k++)//读取原文件中的课程顺序 
					fscanf(fp," %s",&s[k].course);
				fprintf(fp,"\n");
				fclose(fp);
				printf("\t##课程顺序为：");
		 		for(j=0;j<m;j++)
					printf("%s ，",s[j].course);
				inputOperate(s,n,m,n2,2);
			}
			if(mark2==0)
				printf("\n文件打开错误请检查后重新操作！\n");
		}
		if(mark1==0)//进行了读取操作 
		{
			printf("\t##课程顺序为：");
		 	for(j=0;j<m;j++)
				printf("%s ，",s[j].course);
			for(i=n;i<n+n2;i++)//学生数衔接从原文件读取到的学生数 
			{
				printf("\n\n ##student.NO%d:\n\n",i+1);
				printf("请输入学号：");
				scanf("%d",&s[i].registrati);
				printf("\n\t##（注意名字之间不要有空格！）\n请输入姓名：");
				scanf("%s",&s[i].name);
				for(j=0;j<m;j++)
				{
					printf("\n请输入%s成绩：",s[j].course);
					scanf("%d",&s[i].score[j]);
				}
			}
		}
	
	}
	operationmark();
	printf("--录入成绩结束--\n");
}
//录入操作 
void inputOperate(STUDENT s[],int n,int m,int n2,int choose)
{
	int i,j;
	if(choose==1)
	{
		for(i=0;i<n;i++)//《录入操作》 
		{
			printf("\n\n ##student.NO%d:\n\n",i+1);
			printf("请输入学号：");
			scanf("%d",&s[i].registrati);
			printf("\n\t##（注意名字之间不要有空格！）\n请输入姓名：");
			scanf("%s",&s[i].name);
			for(j=0;j<m;j++)
			{
				printf("\n请输入%s成绩：",s[j].course);
				scanf("%d",&s[i].score[j]);
			}
		}
	}
	if(choose==2)//《追加录入操作》 
	{
		for(i=n;i<n+n2;i++)
		{
			printf("\n\n ##student.NO%d:\n\n",i+1);
			printf("请输入学号：");
			scanf("%d",&s[i].registrati);
			printf("\n\t##（注意名字之间不要有空格！）\n请输入姓名：");
			scanf("%s",&s[i].name);
			for(j=0;j<m;j++)
			{
				printf("\n请输入%s成绩：",s[j].course);
				scanf("%d",&s[i].score[j]);
			}
		}
	}
} 
//计算学生平均成绩 
void averagescore(STUDENT s[],int n,int m)
{
	printf("\n\n--您处于求平均成绩界面--\n\n");
	int sum[N];
	int i,j;
	for(i=0;i<n;i++)
	{
		sum[i]=0;
		for(j=0;j<m;j++)
		{
			sum[i]+=s[i].score[j];
		}
		s[i].aver=(float)sum[i]/m;
	}
	operationmark();
	printf("-求平均成绩结束--\n\n");
}
//进行排名
void ranking(STUDENT s[],int n,int m)
{
	printf("\n\n--您处于成绩排名界面--\n\n");
	rankingOperate(s,n,m);
	operationmark();
	printf("--成绩排名结束--\n"); 
} 
//进行排名操作 
void rankingOperate(STUDENT s[],int n,int m)
{
	TRANSFROM tra;
	int i,j,g;
	for(i=1;i<n;i++)//利用冒泡排序使数据由大到小排列 
		for(j=0;j<n-i;j++)
		{
			if(s[j].aver<s[j+1].aver)
			{
				//对平均值进行排序 
				tra.aver=s[j].aver;
				s[j].aver=s[j+1].aver;
				s[j+1].aver=tra.aver;
				//对学号进行排序
				tra.registrati=s[j].registrati;
				s[j].registrati=s[j+1].registrati;
				s[j+1].registrati=tra.registrati;
				//对姓名进行排序
				strcpy(tra.name,s[j].name);//字符串与字符串之间不能直接赋值。选用strcpy（,）函数进行转换 
				strcpy(s[j].name,s[j+1].name);
				strcpy(s[j+1].name,tra.name);
				//对课程成绩进行排序
				for(g=0;g<m;g++)
				{
					tra.score1=s[j].score[g];
					tra.score2=s[j+1].score[g];
					s[j].score[g]=tra.score2;
					s[j+1].score[g]=tra.score1;
				}
			}
		}
} 
//显示每位学生的成绩或排名后的成绩 
void displayscore(STUDENT s[],int n,int m)
{

	int i,j; 
	printf("\n\n--您处于显示各科成绩界面--\n\n");
	printf("\t###课程顺序为：");
	for(j=0;j<m;j++)
		printf("%s ，",s[j].course);
	printf("\n######最后一个成绩为平均成绩######"); 
	printf("\n\n学生的成绩为：");
	printf("\n\n");
	for(i=0;i<n;i++)
	{
		printf("%5d%10s",s[i].registrati,s[i].name);//学号 姓名 
		for(j=0;j<m;j++)
			printf("%5d ",s[i].score[j]);//各科成绩
		printf("%9.1f",s[i].aver);// 平均成绩 
		printf("\n");
	}
	operationmark();
	printf("--显示各科成绩结束--\n");
}
//显示各个课程的平均成绩 
void displayaverage(STUDENT s[],int n,int m)
{
	int i,j;
	int i2,j2;//与'i','j'区分开 避免错误 
	int i3,j3;//与'i','j'区分开 避免错误 
	int choose; 
	float sum;//“sum”储存各个课程的分数和
	float average;//“average”储存课程平均值 
	int mark1;//“mark1”标记符合条件的学生（数组）下标 
	int mark2=0;//“mark2=0 ” 未找到符合条件的下标 
	printf("\n\n--您处于显示各个课程的平均成绩界面--\n\n");
	for(j=0;j<m;j++)
	{
		average=0;
		sum=0;
		for(i=0;i<n;i++)//每次循环课程标志“j”不变 学生 标志"i" 加1 
			sum=sum+s[i].score[j];
		average=sum/n;
		printf("\n\t\t%s课程的平均分为：%.2f \n",s[j].course,average);
	} 
	printf("\n请问是否显示高于或低于各课程平均分的学生情况？\n"); 
	printf("1、显示\n"); 
	printf("2、不显示\n");
	printf("请选择：");
	scanf("%d",&choose); 
	if(choose==1)
	{
		for(j=0;j<m;j++)
		{
			average=0;
			sum=0;
			for(i=0;i<n;i++)//每次循环课程标志“j”不变 学生 标志"i" 加1 
				sum=sum+s[i].score[j];
			average=sum/n;
			printf("\n\t\t%s课程的平均分为：%.2f \n",s[j].course,average);
			printf("\n大于等于%s 平均分的学生有：\n",s[j].course);
			for(i2=0;i2<n;i2++)
			{
				mark2=0;
				if((float)s[i2].score[j]>=average)
					{
						mark1=i2;
						mark2=1;
					}
				if(mark2==1)//只输出符合条件的学号 姓名 成绩 
					printf("%5d%10s %d\n",s[mark1].registrati,s[mark1].name,s[mark1].score[j]);
			} 
			printf("小于%s 平均分的学生有：\n",s[j].course);
			for(i2=0;i2<n;i2++)
			{
				mark2=0;
				if((float)s[i2].score[j]<average)
					{
						mark1=i2;
						mark2=1;
					}
				if(mark2==1)
					printf("%5d%10s %d\n",s[mark1].registrati,s[mark1].name,s[mark1].score[j]);
			} 
		} 
	}	
	operationmark();
	printf("--显示各个课程的平均成绩结束--\n");
}
//求课程最高分
void displayranking(STUDENT s[],int n,int m)
{
	int mark;// “mark ”标记符合条件的学生（数组）下标 
	int i,j;
	int max;
	printf("\n\n--求课程最高分界面--\n");
	printf("###注意:如果有学生的成绩相同只显示排名靠前的学生信息\n");
	for(j=0;j<m;j++)
	{
		max=s[0].score[j];
		mark=0;
		for(i=0;i<n;i++)//每次循环( "课程"标志" j "不变   "学生" 标志" i " 加1 )
		{
			if(s[i].score[j]>max)//逐一对同一科目进行比较求最大值 
			{
				max=s[i].score[j];
				mark=i;
			}
		}
		printf("\n%s课程的最高分为：%d 该学生为：%d  %s\n",s[j].course,max,s[mark].registrati,s[mark].name);
	}
	operationmark();
	printf("--求课程最高分结束--\n"); 
}
//查询某位学生的成绩 
void inquire(STUDENT s[],int n,int m)
{
	int i,j;
	int inid;//inid==inquire+registrati
	char inname[50];
	int mark;//标记符合条件的学生（数组）下标 
	int mark2=0;// " mark2=0 "未找到此学生 
	printf("\n\n--查询某位学生的成绩界面--\n");
	printf("请输入您想要查询学生的学号：");
	scanf("%d",&inid);
	printf("\n\t##（注意名字之间不要有空格！）\n请输入您想要查询学生的姓名：");
	scanf("%s",&inname);
	mark2=checkregistrati(s,n,inid,inname);//《核对学生信息操作》 
	if(mark2==1)
	{
		for(i=0;i<n;i++)//从数据中查找与输入的学号 名字相同的学生的位置 
			if(inid==s[i].registrati&&strcmp(inname,s[i].name)==0)
				mark=i;
		printf("\n您要查询的学生是%d  %s",s[mark].registrati,s[mark].name);
		printf("\n\n######课程顺序为：");
		for(j=0;j<m;j++)
			printf("%s ，",s[j].course);
		printf("\n######最后一个成绩为平均成绩######"); 
		printf("\n\n%5d%10s",s[mark].registrati,s[mark].name);
		for(j=0;j<m;j++)
			printf("%5d ",s[mark].score[j]);
		printf("%9.1f",s[mark].aver);
	}
	if(mark2==0)
		printf("抱歉未查询到学生%d %s的信息,请核对信息后重新查询",inid,inname);
	operationmark();
	printf("--学生信息显示结束--\n"); 
}
//核对学生信息 
int checkregistrati(STUDENT s[],int n,int inid2,char inname2[])
{
	int i;
	int mark=0;
	for(i=0;i<n;i++)//找到学生之后返回“1 ” 
	{
		if(inid2==s[i].registrati&&strcmp(inname2,s[i].name)==0)
		{
			mark=1;
			break;
		}
	}
	return mark;
}
//修改学生信息 
void revise(STUDENT s[],int n,int m)
{
	int i,j; 
	int judge=1;//judge:判断 《用于while循环 
	int choose;//" choose "储存《 您要修改学生什么信息 》操作 
	int inid;
	char inname[50];
	int mark1=0;//" mark1=0 " 未找到目标科目 
	int mark2=0;// " mark2=0 "未找到此学生 
	int mark3;//“mark3 ”标记符合条件的学生（数组）下标 
	int mark;//mark :标记 
	char replaceCOU[20]; 
	printf("\n\n--您处于修改学生信息界面--\n\n");
	printf("请输入您想要修改学生的学号：");
	scanf("%d",&inid);
	printf("\n\t##（注意名字之间不要有空格！）\n请输入您想要修改学生的姓名：");
	scanf("%s",&inname);           
	mark2=checkregistrati(s,n,inid,inname);
	if(mark2==1)//数据中存在该学生进入 
	{
		for(i=0;i<n;i++)
		{
			if(inid==s[i].registrati&&strcmp(inname,s[i].name)==0)
			{
				mark=i;
				break;
			}
		} 
		while(judge==1)
		{
			printf("\n您要修改的学生是%d  %s",s[mark].registrati,s[mark].name);
			printf("\n\n您要修改学生什么信息\n");
			printf("1、修改学号\n");
			printf("2、修改姓名\n");
			printf("3、修改成绩\n");
			printf("0、退出\n");
			printf("请选择：");
			scanf("%d",&choose);
			switch(choose)
			{
				case 1: printf("您要修改的学号为:%d",s[mark].registrati);
						printf("您要修改为：");
						scanf("%d",&s[mark].registrati); 
						judge=askrevise();//询问是否继续对该名学生进行修改 
						printf("\n修改学号操作完成\n");
						system("pause");
						break;
				case 2: printf("\n\t##（注意名字之间不要有空格！）\n您要修改的姓名是%s ",s[mark].name);
						printf("\n您要修改为：");
						scanf("%s",&s[mark].name);
						judge=askrevise();
						printf("\n修改姓名操作完成\n");
						system("pause");
						break;
				case 3: printf("\n您要修改成绩的科目是: ");
						scanf("%s",&replaceCOU);
						for(j=0;j<m;j++)//核对科目并记录课程位置 
						{
							mark1=0;//每次重新赋值保证准确度 
							if(strcmp(replaceCOU,s[j].course)==0)
							{
								mark1=1;
								mark3=j; 
								break;
							}
						}
						if(mark1==1)
						{
							printf("\n您要修改%s成绩是%d ",s[mark3].course,s[mark].score[mark3]);
							printf("\n您要修改为：");
							scanf("%d",&s[mark].score[mark3]);
							judge=askrevise();
							printf("\n修改成绩操作完成\n");
							system("pause");
						}
						if(mark1==0)
						{
							printf("未查询到 %s 课程请核对信息后再进行修改\n",replaceCOU);
							judge=0;
						}
						break;
				case 0: printf("\n\n已退出！\n\n"); 
						judge=0; 
						break; 
			}
		}	
	}
	if(mark2==0)
		printf("抱歉未查询到学生%d %s的信息,请核对信息后重新查询",inid,inname);
	operationmark();
	printf("--修改学生信息结束--\n"); 
}
//询问是否继续进行修改 
int askrevise()
{
	int judge=0; 
	printf("\n您要继续对该学生进行修改吗？\n");
	printf("\t1、继续修改\n");
	printf("\t2、暂停修改\n");
	printf("请选择：");
	scanf("%d",&judge);
	return judge;
}
//删除某位学生的信息
int deletedata(STUDENT s[],int n,int m)
{
	int i,j;
	int mark2;//" mark2=0 "未找到此学生 
	int mark;//"mark"//标记符合条件的学生（数组）下标 
	int inid;
	int choose;//“choose”进行记录《 您确定要删除学生 %d  %s 的信息吗？》选择 
	char inname[50];
	printf("\n\n--您处于删除学生信息界面--\n\n");
	printf("请输入您想要删除学生的学号：");
	scanf("%d",&inid);
	printf("\n\t##（注意名字之间不要有空格！）\n请输入您想要删除学生的姓名：");
	scanf("%s",&inname);           
	mark2=checkregistrati(s,n,inid,inname);
	if(mark2==1) 
	{
		for(i=0;i<n;i++)
		{
			if(inid==s[i].registrati&&strcmp(inname,s[i].name)==0)	
				mark=i;
		}
		printf("\n您要删除的学生是%d  %s",s[mark].registrati,s[mark].name);
		printf("\n"); 
		printf("\n您确定要删除学生 %d  %s 的信息吗\n",s[mark].registrati,s[mark].name);
		printf("1、确定\n"); 
		printf("2、退出\n"); 
		printf("请选择：");
		scanf("%d",&choose);
		if(choose==1)
		{					//先找到要删除的学生再用它的后一位覆盖它的值以此类推不断覆盖最后数组容量减一 
			for(i=mark;i<n;i++)//删除学号,姓名，成绩，平均成绩
			{
					s[i].registrati=s[i+1].registrati;
					strcpy(s[i].name,s[i+1].name);
					s[i].aver=s[i+1].aver;
					for(j=0;j<m;j++)
						s[i].score[j]=s[i+1].score[j];
			}
			n=n-1;//删除了以为学生(学生人数减一) 
		 printf("删除完信息后还有%d名学生",n);
		}
		if(choose==2)
			printf("\n已退出\n");
	}
	if(mark2==0)
		printf("抱歉未查询到学生%d %s的信息,请核对信息后重新查询",inid,inname);
	operationmark();
	return n;
} 
//保存学生数据 
void savef(STUDENT s[],int n,int m,int n2,int choose3,int mark4)
{
	INQUIRE1 inq2[N];//暂存从原文件读取到的课程名与想要保存的课程名进行对比是否相同 
	char *fname1; 
	int inq1=0;//" inq1 "记录输入的课程与原文件中的课程有多少是一致的 
	int  i,j;
	int k;
	int mark1=1;//"mark1=1"文件打开正确 
	int mark2=1;//"mark2=1"文件打开正确 
	int choose; //“choose”记录 选择《保存的文件形式:》 
	printf("\n\n--您处于保存数据界面--\n\n");
	printf("保存的文件形式:\n");
	printf("\n1、新建一个文件进行保存。\n");
	printf("2、在原文件的基础上进行保存。（注意：课程顺序需与原文件课程顺序一致！）\n");
	printf("\n请选择您保存文件的形式:");
	scanf("%d",&choose);
	if(choose==1)
	{
		 
		printf("请输入您要保存的文件名（注意文件后缀需为 .txt形式）\n");
		scanf("%s",&fname2);
		if(mark4==0)//进行过排名操作时进入 
			savefOperate(s,n,m,fname2);//保存
		if(mark4==1)//未进行过排名操作时进入 
		{	
			rankingOperate(s,n,m);//排名
			savefOperate(s,n,m,fname2);//保存
		}
	} 
	if(choose==2)
	{
		printf("请输入您要保存的文件名（注意文件后缀需为 .txt形式）\n");
		scanf("%s",&fname2);
		fname1=fname2;
		if((fp=fopen(fname1,"r"))==NULL)//(判断读取的文件是否存在 )读操作有此操作犯错率小 
			mark2=0;
		if(mark2==1)//文件打开正确才进入 
		{	
			if(choose3==1)//只要读取过文件就进行次操作 
			{
				savefOperate(s,n,m,fname2);//保存 
				n=readfOperate(s,m,fname2);//读取 
				rankingOperate(s,n,m);//排名
				savefOperate(s,n,m,fname2);//保存
			}
			
			if(choose3==2)//只有在没有读取文件的情况下才进入 
			{
				for(k=0;k<m;k++)//储存原文件中的课程顺序 
					fscanf(fp," %s",&inq2[k].course1);
				fprintf(fp,"\n");
				fclose(fp); 
				for(k=0;k<m;k++)//对比输入到的课程顺序与保存的课程顺序 
				{
					if(strcmp(inq2[k].course1,s[k].course)==0)
						inq1++;
				}
				if(inq1==m)//输入的课程顺序与原文件的课程顺序相同时进入 
				{
					if((fp=fopen(fname1,"a"))==NULL)
						mark1=0;
					if(mark1==1)
					{
						for(i=0;i<n;i++)
						{
							fprintf(fp,"\n"); 
							fprintf(fp,"%10d%8s",s[i].registrati,s[i].name);
							for(j=0;j<m;j++)
								fprintf(fp,"%5d",s[i].score[j]);
							fprintf(fp,"%8.1f",s[i].aver);
						}
						fclose(fp);
						n=readfOperate(s,m,fname2);//读取
						rankingOperate(s,n,m);//排名 
						savefOperate(s,n,m,fname2);//保存 
					}
					if(mark1==0)
						printf("\n\n文件打开错误请核对后重新进行操作！\n\n"); 
				}
				else//当inq1不等于m是进入此环节 
					printf("\n\n##请检查课程顺序是否与原文件课程顺序相同！\n");		
			}		
		}
		if(mark2==0)
			printf("\n\n文件打开错误请核对后重新进行操作！\n\n");
	}
	operationmark();
	printf("--数据保存结束--\n");
}
//进行保存文件操作
void savefOperate(STUDENT s[],int n,int m,char *fname1)
{
	int i,j,k;
	fp=fopen(fname1,"w");
	for(k=0;k<m;k++)
	fprintf(fp," %s",s[k].course);
	fprintf(fp,"\n");
	for(i=0;i<n;i++)
	{
		fprintf(fp,"%10d%8s",s[i].registrati,s[i].name);
		for(j=0;j<m;j++)
		fprintf(fp,"%5d",s[i].score[j]);
		fprintf(fp,"%8.1f",s[i].aver);
		if(i<n-1)
		fprintf(fp,"\n");
	}
	fclose(fp);
}
//读取学生数据 
int readf(STUDENT s[],int m)
{
	int i;
	printf("\n\n--您处于读取数据界面--\n\n");
	printf("请输入您要读取的文件名（注意文件后缀需为 .txt形式）\n");
	scanf("%s",&fname2);
	i=readfOperate(s,m,fname2);
	operationmark();
	printf("\n--为您读取到学生 %d 人--",i);
	printf("\n\n--数据读取结束--\n");
	return i;//如果在保存文件时输出了“\n”符程序会多读一次返回的学生人数就要要减一 
}
//进行读取文件操作
int readfOperate(STUDENT s[],int m,char *fname1)
{
	int k;
	int i,j;
	int mark1=1;//"mark1=1"文件打开正确
	if((fp=fopen(fname1,"r"))==NULL)
		mark1=0;
	if(mark1==1)
	{
		for(k=0;k<m;k++)
 			fscanf(fp," %s",&s[k].course);
		fprintf(fp,"\n");
		for(i=0;!feof(fp);i++) //feof()函数用来检测是否提取文件到结束如果到结尾就输出“1”没有就输出“0”
		{
			fscanf(fp,"%10d",&s[i].registrati);
			fscanf(fp,"%8s",&s[i].name);
			for(j=0;j<m;j++)
				fscanf(fp,"%5d",&s[i].score[j]);
			fscanf(fp,"%f",&s[i].aver);
		}
		fclose(fp);
	}
	if(mark1==0)
		printf("文件打开错误!请核对后重新读取\n");
	return i;
}
//操作进行标志
void operationmark()
{
	printf("\n\n\n\n\t->>\n");
	printf("\t->>\n");
	printf("\t->>\n");
}

