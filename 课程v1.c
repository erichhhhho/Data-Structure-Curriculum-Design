#include<stdio.h>		//��׼���롢���ͷ�ļ�
#include<stdlib.h>      //exit����
#include<string.h>		//�����ַ�����������ͷ�ļ�
#include<process.h>		//����access������ͷ�ļ�
#include<time.h>        //�������

#define MAXFLIGHT  1000			//�������ĺ�����
#define E  1000
#define PRINT "%-8d %-8s %-8s %-20s %-20s %-5d %-8d\n",p[i].num,p[i].start,p[i].destination,p[i].TakeOffTime,p[i].ArriveTime,p[i].count,p[i].price //�궨�������ʽ
#define FLIGHT "�����   ��ʼվ   �յ�վ    ���ʱ��           ����ʱ��         ��Ʊ�� ��Ʊ�۸�\n"
#define PRINTORDER  "%-9d %-20lld  %-8s   %-8d   %-5d  $%-8d\n",OrderList[CurrentOrder].OrderNum,OrderList[CurrentOrder].ClientID,OrderList[CurrentOrder].ClientName,OrderList[CurrentOrder].FlightNum,OrderList[CurrentOrder].TicketNum,OrderList[CurrentOrder].cost
#define ORDER   "������    �ͻ����ID           �ͻ�����   �����    ����Ʊ��  ������Ǯ\n"

struct plane         	//����ṹ������
{
    int num;			        	//���庽���
    char start[30];		            //������ʼվ
    char destination[30];			//�յ�վ
    char TakeOffTime[30];			//���ʱ��
    char ArriveTime[30];            //����ʱ��
    int count;	                    //ʣ���Ʊ����
    int price;                       //��Ʊ�۸�

} p[MAXFLIGHT];


struct OrderNode
{
    int OrderNum;                       //������
    long  long ClientID;                //��Ʊ�û����֤
    char ClientName[20];                //��Ʊ�ͻ�����
    int  FlightNum;                     //�����
    int  TicketNum;                     //����Ʊ��
    int  cost;
} OrderList[E];

int i,m=0,e=0;				//����ȫ�ֱ���iΪ�Ѷ�ȡԪ�ظ���
int CurrentOrder,TotalOrder=0;
char again[10];
int result[E];
int IniResult;

int CorrectInput;

void add();		//�����������Ӻ�����Ϣ����
void print(); 		//��ʾ������Ϣ
int* flightSearch();		//���Һ�����Ϣ
void book();	//��Ʊҵ��
void refund();		//��Ʊ
void read();		//��ȡ�ļ�
void save();		//�����ļ�
void output();		//�����ʽ
void initiate();	//ϵͳ��ʼ��
void build();		//���������ļ�
void del(int );         //ɾ������
void modify();        //���ĺ�����Ϣ
void cancel();      //ɾ������

void main()
{
    int select;
    initiate();		//ϵͳ��ʼ���ж��Ƿ����ԭʼ�����ļ�
    srand((int)time(0));
    printf("             ��---���ã���ӭ����ɻ���Ʊϵͳ��---��\n");
    printf("===============================================================================\n");
   /* printf("m=%d\n",m);
    printf("i=%d\n",i);
    printf("TotalOrder=%d\n",TotalOrder);
    printf("CurrentOrder=%d\n",CurrentOrder);*/

    do
    {
        printf("\n --------��         1.���Ӻ�����Ϣ           ��-------- \n\n"
               " --------��         2.��������Լ���Ʊ��Ϣ    ��-------- \n\n"
               " --------��         3.���Һ�����Ϣ           ��-------- \n\n"
               " --------��         4.��Ʊҵ��               ��-------- \n\n"
               " --------��         5.��Ʊҵ��               ��-------- \n\n"
               " --------��         6.�޸ĺ�����Ϣ           ��-------- \n\n"
               " --------��         7.����ȡ������           ��-------- \n\n"
               " --------��         0.�˳�                   ��-------- \n\n");
        printf("================================================================================\n");
        printf("����0-6��ѡ���Իس���������\n\n");
        scanf("%d",&select);
        switch(select)
        {
        case 1:
            add();		//�������Ӻ��ຯ��
            save();
            break;
        case 2:
            print();		//������ʾģ��
            break;
        case 3:
            flightSearch();	//���ò���ģ��
            break;
        case 4:
            book();	//���ö�Ʊģ��
            save();
            break;
        case 5:
            refund();	//������Ʊģ��
            save();
            break;
        case 6:
            modify();   //�����޸ĺ�����Ϣģ��
            break;
        case 7:
            cancel();       //����ȡ��������Ϣģ��
            save();
            break;
        case 0:				//�˳�ϵͳ
            save();
            printf("ллʹ�ã��ټ��� ");
            break;
        }
    }
    while(select!=0);		//�ж��Ƿ������������
}

void initiate()		//����ϵͳ��ʼ������
{
    if(access("Flight.txt",0)==-1)//����ļ����ڣ�����0�������ڣ�����-1��
        build();
    else
        read();
}

void build()		//���彨�������ļ�����
{
//    printf("Build������������");
    FILE *fp,*fp2;		//�����ļ�ָ��


    if((fp2=fopen("ClientOrder.txt","wb"))==NULL)		//���ļ����ж��Ƿ����
    {
        printf("������Ʊ��Ϣ�ļ�ʧ��! ");		//��ӡ������ʾ
        getchar();
        return;
    }
    fclose(fp2);

    if((fp=fopen("Flight.txt","wb"))==NULL)		//���ļ����ж��Ƿ����
    {
        printf("����������Ϣ�ļ�ʧ��! ");		//��ӡ������ʾ
        getchar();
        return;
    }

    printf("���������뺽����Ϣ(�Իس�������):\n");      //��ӡ��ʾ��Ϣ
    printf("-------------------------------------------------------------------------- \n");

    for(i=0; i<MAXFLIGHT; i++)
    {
        printf("�����뺽���: ");
        CorrectInput=scanf("%d",&p[i].num);		         //���뺽���
        while(CorrectInput==0)
            {
                printf("�������!��������ȷ��ʽ���ݣ�\n");
                getchar();
                CorrectInput=scanf("%d",&p[i].num);
                }

        printf("��������ʼվ: ");
        scanf("%s",p[i].start);		        //������ʼվ
        printf("�������յ�վ: ");
        scanf("%s",p[i].destination);		//�����յ�վ
        printf("���������ʱ��: ");
        scanf("%s",p[i].TakeOffTime);		//�������ʱ��
        printf("�����뽵��ʱ��: ");
        scanf("%s",p[i].ArriveTime);		//���뽵��ʱ��
        printf("�������Ʊ��: ");
        CorrectInput=scanf("%d",&p[i].count);	        //�����Ʊ��
         while(CorrectInput==0)
            {
                printf("�������!��������ȷ��ʽ���ݣ�\n");
                getchar();
                CorrectInput=scanf("%d",&p[i].count);
                }

        printf("������Ʊ�ۣ�");
        CorrectInput=scanf("%d",&p[i].price);
         while(CorrectInput==0)
            {
                printf("�������!��������ȷ��ʽ���ݣ�\n");
                getchar();
                CorrectInput=scanf("%d",&p[i].price);
                }

        fwrite(&p[i],sizeof(struct plane),1,fp);//ģ��д�������ļ�
        m++;                                //�ܺ�������1

        printf("������,�Ƿ�������?�����y��n�Իس�������:");
        scanf("%s",again);

        if(strcmp(again,"y")!=0)			//�ж��Ƿ������Ӻ�����Ϣ
        {
            fclose(fp);			//�ر��ļ�
            return;
        }
    }

}

void read()			//�����ȡ�ļ�����
{
    FILE *fp,*fp2;
    if((fp=fopen("Flight.txt","r"))==NULL)
    {
        printf("\n  Warning!!��ȡ������Ϣ�ļ�ʧ��!!!!! \n");
        getchar();
        exit(1);
    }
    if((fp2=fopen("ClientOrder.txt","r"))==NULL)
    {
        printf("\n  Warning!!��ȡ��Ʊ�ļ�ʧ��!!!!! \n");
        getchar();
        exit(1);
    }
    i=0;
    while(!feof(fp))
    {
        fread(&p[i],sizeof(struct plane),1,fp);		//����ȡ����
        i++;
        m++;		//������ں�����
    }
    m--;
    fclose(fp);
    CurrentOrder=0;
    while(!feof(fp2))
    {
        fread(&OrderList[CurrentOrder],sizeof(struct OrderNode),1,fp2);		//����ȡ����
        CurrentOrder++;
        TotalOrder++;		//������ں�����
    }
    TotalOrder--;
    fclose(fp2);

}

void save()		//���屣�溯��
{
    printf("save!");
    FILE *fp,*fp2;
    if((fp=fopen("Flight.txt","w"))==NULL)
    {
        printf("д�뺽����Ϣ�ļ�ʧ��! ");
        getchar();
        return;
        return;
    }
    for(i=0; i<m; i++)			//��鱣������
        fwrite(&p[i],sizeof(struct plane),1,fp);
    fclose(fp);

    if((fp2=fopen("ClientOrder.txt","w"))==NULL)
    {
        printf("д�붩Ʊ��Ϣ�ļ�ʧ��! ");
        getchar();
        return;
        return;
    }

    for(CurrentOrder=0; CurrentOrder<TotalOrder; CurrentOrder++)			//��鱣������
        fwrite(&OrderList[CurrentOrder],sizeof(struct OrderNode),1,fp2);
    fclose(fp2);
}


void add()		//�������Ӻ�����Ϣ����
{
    int Tempnum,Tempcount,Tempprice;



    do
    {
        printf("������������Ҫ���ӵĺ�����Ϣ(�Իس�������):  \n");      //��ӡ��ʾ��Ϣ
        printf("-------------------------------------------------------------------------- \n");
        printf("�����뺽���: ");
            CorrectInput=scanf("%d",&Tempnum);
        while(CorrectInput==0)		//��ȡ�����
            {
                printf("�������!��������ȷ��ʽ���ݣ�\n");
                getchar();
                CorrectInput=scanf("%d",&Tempnum);
                }


        for(i=0; i<m; i++)
        {
            if(Tempnum==p[i].num)
            {
                printf("������󣡴����ظ�����ţ��ַ��ز˵�\n");
                return;
            }
        }

        p[m].num=Tempnum;

        printf("��������ʼվ: ");
        scanf("%s",p[m].start);		        //��ȡ��ʼվ


        printf("�������յ�վ: ");
        scanf("%s",p[m].destination);		//��ȡ�յ�վ
        printf("���������ʱ��: ");
        scanf("%s",p[m].TakeOffTime);		//��ȡ���ʱ��
        printf("�����뽵��ʱ��: ");
        scanf("%s",p[m].ArriveTime);		//��ȡ����ʱ��
        printf("�������Ʊ��: ");
        CorrectInput=scanf("%d",&p[m].count);	        //��ȡ��Ʊ��
        while(CorrectInput==0)		//��ȡ�����
            {
                printf("�������!��������ȷ��ʽ���ݣ�\n");
                getchar();
                CorrectInput=scanf("%d",&p[m].count);
                }

        printf("������۸�");
        CorrectInput=scanf("%d",&p[m].price);            //��ȡ��Ʊ�۸�
        while(CorrectInput==0)		//��ȡ�����
            {
                printf("�������!��������ȷ��ʽ���ݣ�\n");
                getchar();
                CorrectInput=scanf("%d",&p[m].price);
                }


        m++;                                //��ȡ�ܺ�����Ϣ
        printf("������,�Ƿ�������?�����y��n�Իس�������:");
        scanf("%s",again);
    }
    while(!strcmp(again,"y"));		//�ж��Ƿ�������


}

void cancel()   //ȡ������
{
    int* outcome;
    int select;
    outcome=flightSearch();	//���ò�ѯģ��
    if(outcome[0]==-1)
    {
        printf("�Բ���!û���ҵ�������Ҫ�ĺ���,���Բ��ܶ�Ʊ��\n");	//δ���ҵ����躽��
        printf("\n�밴�س��������ϲ�˵� ");
        getchar();
        getchar();
        return;
    }

    if(outcome[1]!=-1)//�����������1����Ҫѡ��һ��
    {
        printf("��ѡ������Ҫ��Ʊ�ĺ����ڲ�ѯ����е���ţ�\n");
        scanf("%d",&select);
        i=outcome[select-1];
    }
    else
        i=outcome[0];
    printf("�ɹ�ɾ�����º��࣡\n");
    printf(FLIGHT);

    printf(PRINT);
    for(; i<m; i++)
    {
        p[i]=p[i+1];
    }
    m--;


}

void output()		//���������ʽ����
{
    printf(FLIGHT);		//��Ϣ����

    for(i=0; i<m; i++)
        printf(PRINT);//��ӡ����Ϣ
    printf("չʾ��ǰ���ж�����\n");
    printf(ORDER);

    for(CurrentOrder=0; CurrentOrder<TotalOrder; CurrentOrder++)
        printf(PRINTORDER);

    printf("m=%d\n",m);
    printf("i=%d\n",i);
    printf("TotalOrder=%d\n",TotalOrder);
    printf("CurrentOrder=%d\n",CurrentOrder);
}

void print()		//������ʾ������Ϣ����
{
    printf("\nĿǰ���������º��ࣺ\n");
    output();			//���������ʽ����
    printf("\n�밴�س��������ϲ�˵� ");
    getchar();
    getchar();
}

int* flightSearch()		//�����ѯ����
{
    int flag=0;
    int count=0;
    int j=0;
    char a[30];
    char b[30];

for(IniResult=0;IniResult<E;IniResult++)
    result[IniResult]=-1;

    do
    {
        printf("\n�����뺽�����վ:");
        scanf("%s",a);		//�����ѯ�ĺ������
        printf("�����뺽���յ�վ:");
        scanf("%s",b);
        printf("\n������ϣ���ѯ�Ľ������:\n\n");
        printf(FLIGHT);
        for(i=0; i<m; i++)
        {

            if(strcmp(p[i].start,a)==0&&strcmp(p[i].destination,b)==0)	//�����������յ�վ�ж��������
            {
                count++;
                printf("�鵽�ĵ�%d������:\n",count);
                printf(PRINT);		//��ʾ��Ϣ
                flag=1;
                result[j++]=i;
            }
        }
        if(flag!=0)
        {
            printf("\n--------��         ��ѯ��ϣ���%d�������������࣬���س�������        ��--------",count);
//	int k=0;
//	printf("result���飺\n");
//	for(;k<j;k++)
//        printf("%d  %d  %s  %s  ����%s   %d   %d\n",result[k],p[result[k]].num,p[result[k]].start,
            //               p[result[k]].destination,p[result[k]].time,p[result[k]].count ,p[result[k]].price);
            getchar();
            getchar();
            return result;
        }
        else
        {
            printf("\n--------��         �Բ���û������Ҫ����Ϣ��           ��--------\n");
            printf("--------��         �Ƿ����²���?�����y��n�Իس�������");
            scanf("%s",again);
        }
    }
    while(!strcmp(again,"y")); //�ж��Ƿ����²���
    return result;//����result���飨�����ҵ��ĺ����Ӧ�����±꣩

}

void book()		//���嶩Ʊҵ����
{
    int* outcome;
    int WantToBookNum;
    int TempID;
    int select;
    int CountClient;
    int flag=0;

    printf("CurrentOrder:%d",CurrentOrder);

    do
    {
        outcome=flightSearch();	//���ò�ѯģ��
        if(outcome[0]==-1)
        {
            printf("�Բ���!û���ҵ�������Ҫ�ĺ���,���Բ��ܶ�Ʊ��\n");	//δ���ҵ����躽��
            printf("\n�밴�س��������ϲ�˵� ");
            getchar();
            getchar();
            break;
        }
        do
        {
            if(outcome[1]!=-1)//�����������1����Ҫѡ��һ��
            {
                printf("��ѡ������Ҫ��Ʊ�ĺ����ڲ�ѯ����е���ţ�\n");
                scanf("%d",&select);
                i=outcome[select-1];
            }
            else
                i=outcome[0];

            printf("��������Ҫ���Ļ�Ʊ�����Իس����������� ");
            CorrectInput=scanf("%d",&WantToBookNum);		//����������Ʊ��
            while(CorrectInput==0)
            {
                printf("�������!��������ȷ��ʽ���ݣ�\n");
                getchar();
                CorrectInput=scanf("%d",&WantToBookNum);
                }

            if(WantToBookNum<=0)			//�ж���Ʊ���Ƿ����
            {
                printf("������������趩1�Ż�Ʊ��\n");
            }
            else if(p[i].count==0)//�ж���Ʊ�Ƿ�����
            {
                printf("�Բ�������ѡ��ĺ���Ļ�Ʊ������!\n");
                    if(outcome[1]!=-1)//�����������1����Ҫѡ��һ��
                      {

                        printf("��Ϊ���Ƽ����º��ࣺ\n");
                        for(IniResult=0;IniResult<E;IniResult++)
                            if(outcome[IniResult]!=-1&&p[outcome[IniResult]].count!=0)
                            {
                              i=outcome[IniResult];
                                printf(PRINT);
                            }

                      }
                break;
            }
            else if(p[i].count!=0&&p[i].count>=WantToBookNum)	//�ж���Ʊ���Ƿ���ڵ��ڶ�Ʊ��
            {

                printf("����������������");
                scanf("%s",OrderList[TotalOrder].ClientName);

                printf("�������������֤��");
                scanf("%lld",&(OrderList[TotalOrder].ClientID));

                OrderList[TotalOrder].FlightNum=p[i].num;
                OrderList[TotalOrder].TicketNum=WantToBookNum;
                OrderList[TotalOrder].OrderNum=rand();
                OrderList[TotalOrder].cost=p[i].price*WantToBookNum;

                TotalOrder++;
                p[i].count=p[i].count-WantToBookNum;
                printf("��Ʊ�ɹ�!\n");
                printf("��֧��$%dԪ��лл��\n",p[i].price*WantToBookNum);
                break;
            }
            else if(p[i].count<WantToBookNum)//�ж���Ʊ���Ƿ�С�ڶ�Ʊ��
            {
                printf("�Բ�������ѡ��ĺ���ֻʣ%d�Ż�Ʊ\n", p[i].count);
                printf("Ҫ��������ҪԤ���Ļ�Ʊ����?������y��n�Իس�������: ");//�ж��Ƿ��������붩Ʊ��
                scanf("%s",again);
            }
        }
        while(!strcmp(again,"y"));
        printf("\n�Ƿ���Ҫ����������Ļ�Ʊ?������y��n�Իس�������: ");
        scanf("%s",again);
    }
    while(!strcmp(again,"y"));		//�ж��Ƿ������Ʊ


}

void refund()		//������Ʊ����
{
    int* h;
    int n;
    int flag=0;
    int num;
    int temp;

    do
    {
        // printf("��������Ʊ�Ķ����Ż���");
        printf("��������Ʊ�Ķ����ţ�\n");
        scanf("%d",&num);

        for(CurrentOrder=0; CurrentOrder<TotalOrder; CurrentOrder++)
        {
            if(OrderList[CurrentOrder].OrderNum==num)
            {
                flag=1;
                printf("���ҵ��ö���,��ѡ��\n");
                printf("y:����ȡ��;n:�˵�����Ʊ��y/n��\n");
                scanf("%s",again);
                if(strcmp(again,"y"))
                {
                    printf("����Ҫ�˶�����Ʊ��:\n");
                    scanf("%d",&n);
                    if(n<=0)
                    {
                        printf("������������˵�һ��Ʊ!\n");
                        return;
                    }
                    else if(n>OrderList[CurrentOrder].TicketNum)
                        printf("���������Ʊ�����Ѷ���Ʊ��\n");
                    else if(n==OrderList[CurrentOrder].TicketNum)
                    {
                        printf("ɾ��������\n");
                        del(CurrentOrder);
                    }
                    else
                        {
                            temp=(OrderList[CurrentOrder].cost/OrderList[CurrentOrder].TicketNum)*n;

                            printf("�ɹ�����%d��Ʊ,���˻�%dԪ��лл\n",n,temp);
                            OrderList[CurrentOrder].TicketNum-=n;
                            OrderList[CurrentOrder].cost-=temp;
                        }
                }
                else
                {

                    printf("ɾ��������\n");
                    del(CurrentOrder);
                }

            }

        }
        if(flag==0)
        {
            printf("�Բ���!û���ҵ�������Ҫ�ĺ���,���Բ�����Ʊ��\n");
            printf("\n�밴�س��������ϲ�˵� ");
            getchar();
            getchar();
            break;
        }



        printf("�Ƿ����������Ʊ�� �����y��n�Իس�������: ");		//�ж��Ƿ������Ʊ
        scanf("%s",again);
    }
    while(!strcmp(again,"y"));		//�ж�������ѭ��

}

void del(int delOrder)//ɾ������
{
    int a,j,n;

    for(a=delOrder; a<TotalOrder; a++)
    {
        OrderList[a]=OrderList[a+1];
    }
    printf("ɾ���ɹ���\n");
    TotalOrder--;
}


void modify()//�ı亽����Ϣ
{
    int ModifyOption,CheckPnum,Startordestination,w,q;
    int TakeOffOrArrive;
    int remain;
    char h[30],g[30],again[20];
    int flag=0;

    printf("������Ҫ�޸ĵĺ���ĺ����\n");
    scanf("%d",&CheckPnum);

    for(i=0; i<MAXFLIGHT; i++)
    {
        if(p[i].num==CheckPnum)
        {
            printf("���ҵ��˺��ࣺ\n");
            flag=1;
            printf(FLIGHT);
            printf(PRINT);

            do
            {
                printf("\n��ѡ��:  1.�޸��𽵵�;2.�޸�ʱ��;3.�۸�;4.�����;5.��ʣƱ��0.�˳�\n");
                scanf("%d",&ModifyOption);

                switch(ModifyOption)
                {
                case 1:
                    printf("��ѡ���޸ĵ��ǣ�1.��ɵص�;2.����ص�\n");
                    scanf("%d",&Startordestination);
                    if(Startordestination==1)
                    {
                        printf("�������޸ĺ����ʼվ��\n");
                        scanf("%s",h);
                        strcpy(p[i].start,h);
                        printf("�޸ĳɹ�");

                    }
                    else  if(Startordestination==2)
                    {
                        printf("�������޸ĺ���յ�վ��\n");
                        scanf("%s",h);
                        strcpy(p[i].destination,h);
                        printf("�޸ĳɹ�");
                    }

                    break;
                case 2:
                    printf("��ѡ���޸ĵ��ǣ�1.���ʱ��;2.����ʱ��\n");
                    scanf("%d",&TakeOffOrArrive);
                    if(TakeOffOrArrive==1)
                    {

                        printf("�������޸ĺ��ʱ��\n");
                        scanf("%s",g);
                        strcpy(p[i].TakeOffTime,g);
                        printf("�޸ĳɹ�");

                    }
                    else  if(TakeOffOrArrive==2)
                    {

                        printf("�������޸ĺ��ʱ��\n");
                        scanf("%s",g);
                        strcpy(p[i].ArriveTime,g);
                        printf("�޸ĳɹ�");
                    }


                    break;
                case 3:

                    printf("�������޸ĺ�ļ۸�\n");
                    scanf("%d",&w);
                    p[i].price=w;
                    printf("�޸ĳɹ�");

                    break;

                case 4:
                    printf("�������޸ĺ�ĺ����\n");
                    scanf("%d",&q);
                    p[i].num=q;

                    break;
                case 5:
                    printf("�������޸ĺ����ʣƱ����\n");
                    scanf("%d",&remain);
                    p[i].count=remain;
                    break;

                case 0:				//�˳�ϵͳ

                    return;
                }
                printf("\n�Ƿ�����޸ģ���y/n��\n");
                scanf("%s",again);
            }
            while(!strcmp(again,"y"));
            save();
        }

    }
    if(flag==0)
        printf("�����������󣡣���û���⺽�࣡���˳����˵�\n");
}


