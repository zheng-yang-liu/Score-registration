#include<stdio.h>
#include<stdlib.h>
#include<string.h>//strcpy(,)...���������ļ� 
#define N 3961//���궨�壩N������ܴ����ѧ���� ����������N=3961Ϊ�˳���ļ��޳�������� 
#define M 20//���γ��� 
//����ṹ���� 
typedef struct student
{
	int registrati;//registrati���Ǽ� 
	char name[20];//����
	char course[20];//�γ� 
	int score[M];//�ɼ�  ��������ܴ���13�ƵĿγ̳ɼ� 
	float aver;//ƽ��ֵ 
}STUDENT;
//����ṹ�������ڲ�ѯ��ԭ�ļ���ȡ���Ŀγ�������Ҫ����Ŀγ������жԱ��Ƿ���ͬ 
typedef struct inquire1//inqiure:��ѯ 
{
	char course1[20];//�γ�
}INQUIRE1;
//����ṹ�����������������е�( �ݴ� ��ת�� )���� 
typedef struct transform//transform:ת�� 
{  
	int registrati;//ѧ�� 
	char name[20];//����
	char course[15];//�γ�
	int score1,score2;//�ɼ� 
	float aver;//ƽ��ֵ 
}TRANSFROM;
//����ȫ�ֱ���������Ͷ�ȡ���ݺ���ʹ�� 
FILE *fp;
char fname2[32];
//�Զ��庯�� 
void menu();//����һ��ģ�庯�� 
void inputscore(STUDENT s[],int n,int m,int n2,int choose,int mark1);//����һ��¼��ɼ��ĺ��� 
void inputOperate(STUDENT s[],int n,int m,int n2,int choose);//¼��������� 
void displayscore(STUDENT s[],int n,int m);//��ʾ���Ƴɼ��ĺ��� 
void displayaverage(STUDENT s[],int n,int m);//��ʾ�����γ̵�ƽ���ɼ��ĺ���
void ranking(STUDENT s[],int n,int m);//���������ĺ��� ������ѧ��ƽ��ֵ���������� 
void rankingOperate(STUDENT s[],int n,int m);//�������������ĺ��� ������ѧ��ƽ��ֵ���������� 
void displayranking(STUDENT s[],int n,int m);//��ʾ�γ���߷ֵĺ��� 
void displayfirst(STUDENT s[],int n,int m);//Ѱ�Ҳ���ʾ��һ������Ϣ
void averagescore(STUDENT s[],int n,int m);//����ƽ���ɼ��ĺ��� 
void inquire(STUDENT s[],int n,int m);//����һ����ѯĳλѧ���ɼ��ĺ��� 
void revise(STUDENT s[],int n,int m);//�޸�ѧ����Ϣ�ĺ��� 
void savef(STUDENT s[],int n,int m,int n2,int choose3,int mark2);//����һ�����溯�ļ����� 
void savefOperate(STUDENT s[],int n,int m,char *fname1);//����һ������������ļ����� 
int readf(STUDENT s[],int m);//����һ����ȡ�ļ����� 
int readfOperate(STUDENT s[],int m,char *fname1);//����һ����ȡ�ļ��������� 
int deletedata(STUDENT s[],int n,int m);//ɾ��ĳλѧ������Ϣ�ĺ��� 
int askrevise();//ѯ���Ƿ���������޸ĵĺ��� 
int checkregistrati(STUDENT s[],int n,int inid2,char inname2[]);//�˶�ѧ����Ϣ 
void operationmark();//�������б�־
int main()
{
	STUDENT stu[N];
	int choose2;
	int mark1=1;// ��mark1=1��û���й� ( 11����ȡ���� ������ʱ�ı��ֵ  
	int mark2=1;//"mark2=1"δ���й���3����������������ʱ�ı��ֵ 
	int choose3=2;//Ĭ�ϣ� 10���������� �������е�" choose3=2 "
	int choose;
	int n=0,m=0,n2=0;
	while(1)
	{	menu();
		printf("��ѡ��");
		scanf("%d",&choose2);
		switch(choose2)
		{
			case 1: printf("\n\n--������¼��ɼ�����--\n\n");
					printf("--¼�뷽ʽ�У�--");
					printf("\n\n--1��¼    �룺  --\n");
					printf("--2��׷��¼�룺--\n\n");
					printf("\n\n--��ѡ��");
					scanf("%d",&choose);
					if(choose==1)
					{
						printf("\n����ܴ���ѧ��%d��\n",N);
						printf("������Ҫ�����ѧ����:");
						scanf("%d",&n);
						if(n>=N)
						{
							printf("����ѧ����������%d��\n",N);
							printf("����������Ҫ�����ѧ����");
							scanf("%d",&n);
						}
						if(n<N)
						{
							printf("\t###�������%d�ſγ�\n������Ƴ���:",M);
							scanf("%d",&m);
							inputscore(stu,n,m,0,choose,mark1);
							printf("\n");
							system("pause");
						}
						break;
					}
					if(choose=2)
					{
						printf("\n����ܴ���ѧ��%d��\n",N);
						printf("������Ҫ�����ѧ����");
						scanf("%d",&n2);
						if(n2>=N)
						{
							printf("����ѧ����������%d��\n",N);
							printf("����������Ҫ�����ѧ����");
							scanf("%d",&n2);
						}
						if(n2<N)
						{
							if(m==0)
							{
								printf("\t###�������%d�ſγ�\n������ԭ�ļ��еĿγ���",M);
								scanf("%d",&m);
							}
							inputscore(stu,n,m,n2,choose,mark1);
							printf("\n");
							system("pause");
						}
						n=n+n2;//����ѧ������ 
						printf("׷��¼�����ѧ����%d ��",n);
						printf("\n");
						system("pause");
						break;
					}
			case 2: averagescore(stu,n,m);//��ƽ��ֵ 
					printf("\n");
					system("pause");
					break; 
			case 3: ranking(stu,n,m); //���� 
					mark2=0;
					system("pause"); 
					break; 
			case 4: displayscore(stu,n,m);//��ʾ���пγ̵ĳɼ� 
					printf("\n");
					system("pause");
					break; 		
			case 5: displayaverage(stu,n,m);//��ʾ�����γ̵�ƽ���ɼ� 
					printf("\n");
					system("pause");
					break;
			case 6: displayranking(stu,n,m); //������ĵĳɼ� 
					printf("\n");
					system("pause");
					break; 
			case 7: inquire(stu,n,m);//��ѯĳλѧ���ĳɼ� 
					printf("\n");
					system("pause");
					break; 
			case 8: revise(stu,n,m);//�޸�ѧ������ 
					printf("\n");
					system("pause");
					break; 
			case 9: n=deletedata(stu,n,m);//ɾ��ѧ����Ϣ 
					printf("\n");
					system("pause");
					break; 
			case 10: savef(stu,n,m,n2,choose3,mark2);//�������� 
					printf("\n");
					system("pause");
					break; 
			case 11: printf("������γ�����");//��ȡ���� 
					scanf("%d",&m); 
					n=readf(stu,m);//n�����ȡ����ѧ���� 
					mark1=0;//���й� ( 11����ȡ���� ������ʱ�ı��ֵ  
					printf("\n");
					system("pause");
					break; 
			case 0: exit(0);
					printf("\n");
					system("pause");
					break;
		}
		if(mark1==0)//ֻҪ�����˶�ȡ�������д˲��� 
			choose3=1;
		system("cls");
	}
	return 0; 
}
//�˵� 
void menu()
{
	printf("**********************************\n\n"); 
	printf("     **ѧ���ɼ��Ǽ�ϵͳ**\n\n");
	printf("**********************************\n");
	printf("\t 1��¼��ɼ�\n");
	printf("\t 2����ƽ���ɼ�\n");
	printf("\t 3����������\n");
	printf("\t 4����ʾ���Ƴɼ�\n");
	printf("\t 5����ʾ�����γ̵�ƽ���ɼ�\n");
	printf("\t 6����ʾ���Ƶ���߷�\n");
	printf("\t 7����ѯĳλѧ���ĳɼ�\n");
	printf("\t 8���޸�ĳλѧ������Ϣ\n");
	printf("\t 9��ɾ��ĳλѧ������Ϣ\n");
	printf("\t10����������\n");
	printf("\t11����ȡ����\n");
	printf("\t 0���˳�\n");
	printf("**********************************\n");
}
//¼��ѧ���ɼ� 
void inputscore(STUDENT s[],int n,int m,int n2,int choose,int mark1)
{
	INQUIRE1 inq[n];//�ݴ��ԭ�ļ��ж�ȡ���Ŀγ��Լ��γ�˳�� 
	int i,j,k; 
	FILE *fp;
	char *fname1;
	int mark=1;//mark����� ��mark=1���ޣ�11����ȡ���ݣ�����ʱ�ı�־ֵ 
	int mark2=1;//��mark2=1���ļ�����ȷ�ǵı��ֵ 
	if(choose==1)//��¼�������
	{
		for(k=0;k<m;k++)
		{
			printf("\n�������%d�ſγ�����",k+1);	
			scanf("%s",&s[k].course);
		}
		inputOperate(s,n,m,0,1);
	}
	if(choose==2)//��׷��¼�롷
	{
		if(mark1==1)//�ޣ�11����ȡ���ݣ�����ʱ���� 
		{
			printf("\n��������׷��¼������ݵı����ļ�����"); 
			scanf("%s",&fname2);
			fname1=fname2;
			if((fp=fopen(fname1,"r"))==NULL)//�˲�����С������
				mark2=0;
			if(mark2==1)
			{
				for(k=0;k<m;k++)//��ȡԭ�ļ��еĿγ�˳�� 
					fscanf(fp," %s",&s[k].course);
				fprintf(fp,"\n");
				fclose(fp);
				printf("\t##�γ�˳��Ϊ��");
		 		for(j=0;j<m;j++)
					printf("%s ��",s[j].course);
				inputOperate(s,n,m,n2,2);
			}
			if(mark2==0)
				printf("\n�ļ��򿪴�����������²�����\n");
		}
		if(mark1==0)//�����˶�ȡ���� 
		{
			printf("\t##�γ�˳��Ϊ��");
		 	for(j=0;j<m;j++)
				printf("%s ��",s[j].course);
			for(i=n;i<n+n2;i++)//ѧ�����νӴ�ԭ�ļ���ȡ����ѧ���� 
			{
				printf("\n\n ##student.NO%d:\n\n",i+1);
				printf("������ѧ�ţ�");
				scanf("%d",&s[i].registrati);
				printf("\n\t##��ע������֮�䲻Ҫ�пո񣡣�\n������������");
				scanf("%s",&s[i].name);
				for(j=0;j<m;j++)
				{
					printf("\n������%s�ɼ���",s[j].course);
					scanf("%d",&s[i].score[j]);
				}
			}
		}
	
	}
	operationmark();
	printf("--¼��ɼ�����--\n");
}
//¼����� 
void inputOperate(STUDENT s[],int n,int m,int n2,int choose)
{
	int i,j;
	if(choose==1)
	{
		for(i=0;i<n;i++)//��¼������� 
		{
			printf("\n\n ##student.NO%d:\n\n",i+1);
			printf("������ѧ�ţ�");
			scanf("%d",&s[i].registrati);
			printf("\n\t##��ע������֮�䲻Ҫ�пո񣡣�\n������������");
			scanf("%s",&s[i].name);
			for(j=0;j<m;j++)
			{
				printf("\n������%s�ɼ���",s[j].course);
				scanf("%d",&s[i].score[j]);
			}
		}
	}
	if(choose==2)//��׷��¼������� 
	{
		for(i=n;i<n+n2;i++)
		{
			printf("\n\n ##student.NO%d:\n\n",i+1);
			printf("������ѧ�ţ�");
			scanf("%d",&s[i].registrati);
			printf("\n\t##��ע������֮�䲻Ҫ�пո񣡣�\n������������");
			scanf("%s",&s[i].name);
			for(j=0;j<m;j++)
			{
				printf("\n������%s�ɼ���",s[j].course);
				scanf("%d",&s[i].score[j]);
			}
		}
	}
} 
//����ѧ��ƽ���ɼ� 
void averagescore(STUDENT s[],int n,int m)
{
	printf("\n\n--��������ƽ���ɼ�����--\n\n");
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
	printf("-��ƽ���ɼ�����--\n\n");
}
//��������
void ranking(STUDENT s[],int n,int m)
{
	printf("\n\n--�����ڳɼ���������--\n\n");
	rankingOperate(s,n,m);
	operationmark();
	printf("--�ɼ���������--\n"); 
} 
//������������ 
void rankingOperate(STUDENT s[],int n,int m)
{
	TRANSFROM tra;
	int i,j,g;
	for(i=1;i<n;i++)//����ð������ʹ�����ɴ�С���� 
		for(j=0;j<n-i;j++)
		{
			if(s[j].aver<s[j+1].aver)
			{
				//��ƽ��ֵ�������� 
				tra.aver=s[j].aver;
				s[j].aver=s[j+1].aver;
				s[j+1].aver=tra.aver;
				//��ѧ�Ž�������
				tra.registrati=s[j].registrati;
				s[j].registrati=s[j+1].registrati;
				s[j+1].registrati=tra.registrati;
				//��������������
				strcpy(tra.name,s[j].name);//�ַ������ַ���֮�䲻��ֱ�Ӹ�ֵ��ѡ��strcpy��,����������ת�� 
				strcpy(s[j].name,s[j+1].name);
				strcpy(s[j+1].name,tra.name);
				//�Կγ̳ɼ���������
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
//��ʾÿλѧ���ĳɼ���������ĳɼ� 
void displayscore(STUDENT s[],int n,int m)
{

	int i,j; 
	printf("\n\n--��������ʾ���Ƴɼ�����--\n\n");
	printf("\t###�γ�˳��Ϊ��");
	for(j=0;j<m;j++)
		printf("%s ��",s[j].course);
	printf("\n######���һ���ɼ�Ϊƽ���ɼ�######"); 
	printf("\n\nѧ���ĳɼ�Ϊ��");
	printf("\n\n");
	for(i=0;i<n;i++)
	{
		printf("%5d%10s",s[i].registrati,s[i].name);//ѧ�� ���� 
		for(j=0;j<m;j++)
			printf("%5d ",s[i].score[j]);//���Ƴɼ�
		printf("%9.1f",s[i].aver);// ƽ���ɼ� 
		printf("\n");
	}
	operationmark();
	printf("--��ʾ���Ƴɼ�����--\n");
}
//��ʾ�����γ̵�ƽ���ɼ� 
void displayaverage(STUDENT s[],int n,int m)
{
	int i,j;
	int i2,j2;//��'i','j'���ֿ� ������� 
	int i3,j3;//��'i','j'���ֿ� ������� 
	int choose; 
	float sum;//��sum����������γ̵ķ�����
	float average;//��average������γ�ƽ��ֵ 
	int mark1;//��mark1����Ƿ���������ѧ�������飩�±� 
	int mark2=0;//��mark2=0 �� δ�ҵ������������±� 
	printf("\n\n--��������ʾ�����γ̵�ƽ���ɼ�����--\n\n");
	for(j=0;j<m;j++)
	{
		average=0;
		sum=0;
		for(i=0;i<n;i++)//ÿ��ѭ���γ̱�־��j������ ѧ�� ��־"i" ��1 
			sum=sum+s[i].score[j];
		average=sum/n;
		printf("\n\t\t%s�γ̵�ƽ����Ϊ��%.2f \n",s[j].course,average);
	} 
	printf("\n�����Ƿ���ʾ���ڻ���ڸ��γ�ƽ���ֵ�ѧ�������\n"); 
	printf("1����ʾ\n"); 
	printf("2������ʾ\n");
	printf("��ѡ��");
	scanf("%d",&choose); 
	if(choose==1)
	{
		for(j=0;j<m;j++)
		{
			average=0;
			sum=0;
			for(i=0;i<n;i++)//ÿ��ѭ���γ̱�־��j������ ѧ�� ��־"i" ��1 
				sum=sum+s[i].score[j];
			average=sum/n;
			printf("\n\t\t%s�γ̵�ƽ����Ϊ��%.2f \n",s[j].course,average);
			printf("\n���ڵ���%s ƽ���ֵ�ѧ���У�\n",s[j].course);
			for(i2=0;i2<n;i2++)
			{
				mark2=0;
				if((float)s[i2].score[j]>=average)
					{
						mark1=i2;
						mark2=1;
					}
				if(mark2==1)//ֻ�������������ѧ�� ���� �ɼ� 
					printf("%5d%10s %d\n",s[mark1].registrati,s[mark1].name,s[mark1].score[j]);
			} 
			printf("С��%s ƽ���ֵ�ѧ���У�\n",s[j].course);
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
	printf("--��ʾ�����γ̵�ƽ���ɼ�����--\n");
}
//��γ���߷�
void displayranking(STUDENT s[],int n,int m)
{
	int mark;// ��mark ����Ƿ���������ѧ�������飩�±� 
	int i,j;
	int max;
	printf("\n\n--��γ���߷ֽ���--\n");
	printf("###ע��:�����ѧ���ĳɼ���ֻͬ��ʾ������ǰ��ѧ����Ϣ\n");
	for(j=0;j<m;j++)
	{
		max=s[0].score[j];
		mark=0;
		for(i=0;i<n;i++)//ÿ��ѭ��( "�γ�"��־" j "����   "ѧ��" ��־" i " ��1 )
		{
			if(s[i].score[j]>max)//��һ��ͬһ��Ŀ���бȽ������ֵ 
			{
				max=s[i].score[j];
				mark=i;
			}
		}
		printf("\n%s�γ̵���߷�Ϊ��%d ��ѧ��Ϊ��%d  %s\n",s[j].course,max,s[mark].registrati,s[mark].name);
	}
	operationmark();
	printf("--��γ���߷ֽ���--\n"); 
}
//��ѯĳλѧ���ĳɼ� 
void inquire(STUDENT s[],int n,int m)
{
	int i,j;
	int inid;//inid==inquire+registrati
	char inname[50];
	int mark;//��Ƿ���������ѧ�������飩�±� 
	int mark2=0;// " mark2=0 "δ�ҵ���ѧ�� 
	printf("\n\n--��ѯĳλѧ���ĳɼ�����--\n");
	printf("����������Ҫ��ѯѧ����ѧ�ţ�");
	scanf("%d",&inid);
	printf("\n\t##��ע������֮�䲻Ҫ�пո񣡣�\n����������Ҫ��ѯѧ����������");
	scanf("%s",&inname);
	mark2=checkregistrati(s,n,inid,inname);//���˶�ѧ����Ϣ������ 
	if(mark2==1)
	{
		for(i=0;i<n;i++)//�������в����������ѧ�� ������ͬ��ѧ����λ�� 
			if(inid==s[i].registrati&&strcmp(inname,s[i].name)==0)
				mark=i;
		printf("\n��Ҫ��ѯ��ѧ����%d  %s",s[mark].registrati,s[mark].name);
		printf("\n\n######�γ�˳��Ϊ��");
		for(j=0;j<m;j++)
			printf("%s ��",s[j].course);
		printf("\n######���һ���ɼ�Ϊƽ���ɼ�######"); 
		printf("\n\n%5d%10s",s[mark].registrati,s[mark].name);
		for(j=0;j<m;j++)
			printf("%5d ",s[mark].score[j]);
		printf("%9.1f",s[mark].aver);
	}
	if(mark2==0)
		printf("��Ǹδ��ѯ��ѧ��%d %s����Ϣ,��˶���Ϣ�����²�ѯ",inid,inname);
	operationmark();
	printf("--ѧ����Ϣ��ʾ����--\n"); 
}
//�˶�ѧ����Ϣ 
int checkregistrati(STUDENT s[],int n,int inid2,char inname2[])
{
	int i;
	int mark=0;
	for(i=0;i<n;i++)//�ҵ�ѧ��֮�󷵻ء�1 �� 
	{
		if(inid2==s[i].registrati&&strcmp(inname2,s[i].name)==0)
		{
			mark=1;
			break;
		}
	}
	return mark;
}
//�޸�ѧ����Ϣ 
void revise(STUDENT s[],int n,int m)
{
	int i,j; 
	int judge=1;//judge:�ж� ������whileѭ�� 
	int choose;//" choose "���桶 ��Ҫ�޸�ѧ��ʲô��Ϣ ������ 
	int inid;
	char inname[50];
	int mark1=0;//" mark1=0 " δ�ҵ�Ŀ���Ŀ 
	int mark2=0;// " mark2=0 "δ�ҵ���ѧ�� 
	int mark3;//��mark3 ����Ƿ���������ѧ�������飩�±� 
	int mark;//mark :��� 
	char replaceCOU[20]; 
	printf("\n\n--�������޸�ѧ����Ϣ����--\n\n");
	printf("����������Ҫ�޸�ѧ����ѧ�ţ�");
	scanf("%d",&inid);
	printf("\n\t##��ע������֮�䲻Ҫ�пո񣡣�\n����������Ҫ�޸�ѧ����������");
	scanf("%s",&inname);           
	mark2=checkregistrati(s,n,inid,inname);
	if(mark2==1)//�����д��ڸ�ѧ������ 
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
			printf("\n��Ҫ�޸ĵ�ѧ����%d  %s",s[mark].registrati,s[mark].name);
			printf("\n\n��Ҫ�޸�ѧ��ʲô��Ϣ\n");
			printf("1���޸�ѧ��\n");
			printf("2���޸�����\n");
			printf("3���޸ĳɼ�\n");
			printf("0���˳�\n");
			printf("��ѡ��");
			scanf("%d",&choose);
			switch(choose)
			{
				case 1: printf("��Ҫ�޸ĵ�ѧ��Ϊ:%d",s[mark].registrati);
						printf("��Ҫ�޸�Ϊ��");
						scanf("%d",&s[mark].registrati); 
						judge=askrevise();//ѯ���Ƿ�����Ը���ѧ�������޸� 
						printf("\n�޸�ѧ�Ų������\n");
						system("pause");
						break;
				case 2: printf("\n\t##��ע������֮�䲻Ҫ�пո񣡣�\n��Ҫ�޸ĵ�������%s ",s[mark].name);
						printf("\n��Ҫ�޸�Ϊ��");
						scanf("%s",&s[mark].name);
						judge=askrevise();
						printf("\n�޸������������\n");
						system("pause");
						break;
				case 3: printf("\n��Ҫ�޸ĳɼ��Ŀ�Ŀ��: ");
						scanf("%s",&replaceCOU);
						for(j=0;j<m;j++)//�˶Կ�Ŀ����¼�γ�λ�� 
						{
							mark1=0;//ÿ�����¸�ֵ��֤׼ȷ�� 
							if(strcmp(replaceCOU,s[j].course)==0)
							{
								mark1=1;
								mark3=j; 
								break;
							}
						}
						if(mark1==1)
						{
							printf("\n��Ҫ�޸�%s�ɼ���%d ",s[mark3].course,s[mark].score[mark3]);
							printf("\n��Ҫ�޸�Ϊ��");
							scanf("%d",&s[mark].score[mark3]);
							judge=askrevise();
							printf("\n�޸ĳɼ��������\n");
							system("pause");
						}
						if(mark1==0)
						{
							printf("δ��ѯ�� %s �γ���˶���Ϣ���ٽ����޸�\n",replaceCOU);
							judge=0;
						}
						break;
				case 0: printf("\n\n���˳���\n\n"); 
						judge=0; 
						break; 
			}
		}	
	}
	if(mark2==0)
		printf("��Ǹδ��ѯ��ѧ��%d %s����Ϣ,��˶���Ϣ�����²�ѯ",inid,inname);
	operationmark();
	printf("--�޸�ѧ����Ϣ����--\n"); 
}
//ѯ���Ƿ���������޸� 
int askrevise()
{
	int judge=0; 
	printf("\n��Ҫ�����Ը�ѧ�������޸���\n");
	printf("\t1�������޸�\n");
	printf("\t2����ͣ�޸�\n");
	printf("��ѡ��");
	scanf("%d",&judge);
	return judge;
}
//ɾ��ĳλѧ������Ϣ
int deletedata(STUDENT s[],int n,int m)
{
	int i,j;
	int mark2;//" mark2=0 "δ�ҵ���ѧ�� 
	int mark;//"mark"//��Ƿ���������ѧ�������飩�±� 
	int inid;
	int choose;//��choose�����м�¼�� ��ȷ��Ҫɾ��ѧ�� %d  %s ����Ϣ�𣿡�ѡ�� 
	char inname[50];
	printf("\n\n--������ɾ��ѧ����Ϣ����--\n\n");
	printf("����������Ҫɾ��ѧ����ѧ�ţ�");
	scanf("%d",&inid);
	printf("\n\t##��ע������֮�䲻Ҫ�пո񣡣�\n����������Ҫɾ��ѧ����������");
	scanf("%s",&inname);           
	mark2=checkregistrati(s,n,inid,inname);
	if(mark2==1) 
	{
		for(i=0;i<n;i++)
		{
			if(inid==s[i].registrati&&strcmp(inname,s[i].name)==0)	
				mark=i;
		}
		printf("\n��Ҫɾ����ѧ����%d  %s",s[mark].registrati,s[mark].name);
		printf("\n"); 
		printf("\n��ȷ��Ҫɾ��ѧ�� %d  %s ����Ϣ��\n",s[mark].registrati,s[mark].name);
		printf("1��ȷ��\n"); 
		printf("2���˳�\n"); 
		printf("��ѡ��");
		scanf("%d",&choose);
		if(choose==1)
		{					//���ҵ�Ҫɾ����ѧ���������ĺ�һλ��������ֵ�Դ����Ʋ��ϸ����������������һ 
			for(i=mark;i<n;i++)//ɾ��ѧ��,�������ɼ���ƽ���ɼ�
			{
					s[i].registrati=s[i+1].registrati;
					strcpy(s[i].name,s[i+1].name);
					s[i].aver=s[i+1].aver;
					for(j=0;j<m;j++)
						s[i].score[j]=s[i+1].score[j];
			}
			n=n-1;//ɾ������Ϊѧ��(ѧ��������һ) 
		 printf("ɾ������Ϣ����%d��ѧ��",n);
		}
		if(choose==2)
			printf("\n���˳�\n");
	}
	if(mark2==0)
		printf("��Ǹδ��ѯ��ѧ��%d %s����Ϣ,��˶���Ϣ�����²�ѯ",inid,inname);
	operationmark();
	return n;
} 
//����ѧ������ 
void savef(STUDENT s[],int n,int m,int n2,int choose3,int mark4)
{
	INQUIRE1 inq2[N];//�ݴ��ԭ�ļ���ȡ���Ŀγ�������Ҫ����Ŀγ������жԱ��Ƿ���ͬ 
	char *fname1; 
	int inq1=0;//" inq1 "��¼����Ŀγ���ԭ�ļ��еĿγ��ж�����һ�µ� 
	int  i,j;
	int k;
	int mark1=1;//"mark1=1"�ļ�����ȷ 
	int mark2=1;//"mark2=1"�ļ�����ȷ 
	int choose; //��choose����¼ ѡ�񡶱�����ļ���ʽ:�� 
	printf("\n\n--�����ڱ������ݽ���--\n\n");
	printf("������ļ���ʽ:\n");
	printf("\n1���½�һ���ļ����б��档\n");
	printf("2����ԭ�ļ��Ļ����Ͻ��б��档��ע�⣺�γ�˳������ԭ�ļ��γ�˳��һ�£���\n");
	printf("\n��ѡ���������ļ�����ʽ:");
	scanf("%d",&choose);
	if(choose==1)
	{
		 
		printf("��������Ҫ������ļ�����ע���ļ���׺��Ϊ .txt��ʽ��\n");
		scanf("%s",&fname2);
		if(mark4==0)//���й���������ʱ���� 
			savefOperate(s,n,m,fname2);//����
		if(mark4==1)//δ���й���������ʱ���� 
		{	
			rankingOperate(s,n,m);//����
			savefOperate(s,n,m,fname2);//����
		}
	} 
	if(choose==2)
	{
		printf("��������Ҫ������ļ�����ע���ļ���׺��Ϊ .txt��ʽ��\n");
		scanf("%s",&fname2);
		fname1=fname2;
		if((fp=fopen(fname1,"r"))==NULL)//(�ж϶�ȡ���ļ��Ƿ���� )�������д˲���������С 
			mark2=0;
		if(mark2==1)//�ļ�����ȷ�Ž��� 
		{	
			if(choose3==1)//ֻҪ��ȡ���ļ��ͽ��дβ��� 
			{
				savefOperate(s,n,m,fname2);//���� 
				n=readfOperate(s,m,fname2);//��ȡ 
				rankingOperate(s,n,m);//����
				savefOperate(s,n,m,fname2);//����
			}
			
			if(choose3==2)//ֻ����û�ж�ȡ�ļ�������²Ž��� 
			{
				for(k=0;k<m;k++)//����ԭ�ļ��еĿγ�˳�� 
					fscanf(fp," %s",&inq2[k].course1);
				fprintf(fp,"\n");
				fclose(fp); 
				for(k=0;k<m;k++)//�Ա����뵽�Ŀγ�˳���뱣��Ŀγ�˳�� 
				{
					if(strcmp(inq2[k].course1,s[k].course)==0)
						inq1++;
				}
				if(inq1==m)//����Ŀγ�˳����ԭ�ļ��Ŀγ�˳����ͬʱ���� 
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
						n=readfOperate(s,m,fname2);//��ȡ
						rankingOperate(s,n,m);//���� 
						savefOperate(s,n,m,fname2);//���� 
					}
					if(mark1==0)
						printf("\n\n�ļ��򿪴�����˶Ժ����½��в�����\n\n"); 
				}
				else//��inq1������m�ǽ���˻��� 
					printf("\n\n##����γ�˳���Ƿ���ԭ�ļ��γ�˳����ͬ��\n");		
			}		
		}
		if(mark2==0)
			printf("\n\n�ļ��򿪴�����˶Ժ����½��в�����\n\n");
	}
	operationmark();
	printf("--���ݱ������--\n");
}
//���б����ļ�����
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
//��ȡѧ������ 
int readf(STUDENT s[],int m)
{
	int i;
	printf("\n\n--�����ڶ�ȡ���ݽ���--\n\n");
	printf("��������Ҫ��ȡ���ļ�����ע���ļ���׺��Ϊ .txt��ʽ��\n");
	scanf("%s",&fname2);
	i=readfOperate(s,m,fname2);
	operationmark();
	printf("\n--Ϊ����ȡ��ѧ�� %d ��--",i);
	printf("\n\n--���ݶ�ȡ����--\n");
	return i;//����ڱ����ļ�ʱ����ˡ�\n�����������һ�η��ص�ѧ��������ҪҪ��һ 
}
//���ж�ȡ�ļ�����
int readfOperate(STUDENT s[],int m,char *fname1)
{
	int k;
	int i,j;
	int mark1=1;//"mark1=1"�ļ�����ȷ
	if((fp=fopen(fname1,"r"))==NULL)
		mark1=0;
	if(mark1==1)
	{
		for(k=0;k<m;k++)
 			fscanf(fp," %s",&s[k].course);
		fprintf(fp,"\n");
		for(i=0;!feof(fp);i++) //feof()������������Ƿ���ȡ�ļ��������������β�������1��û�о������0��
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
		printf("�ļ��򿪴���!��˶Ժ����¶�ȡ\n");
	return i;
}
//�������б�־
void operationmark()
{
	printf("\n\n\n\n\t->>\n");
	printf("\t->>\n");
	printf("\t->>\n");
}

