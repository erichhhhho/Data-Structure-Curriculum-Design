#include<stdio.h>		//标准输入、输出头文件
#include<stdlib.h>      //exit函数
#include<string.h>		//包含字符串函数处理头文件
#include<process.h>		//包含access函数的头文件
#include<time.h>        //随机种子

#define MAXFLIGHT  1000			//定义最多的航班数
#define E  1000
#define PRINT "%-8d %-8s %-8s %-20s %-20s %-5d %-8d\n",p[i].num,p[i].start,p[i].destination,p[i].TakeOffTime,p[i].ArriveTime,p[i].count,p[i].price //宏定义输出格式
#define FLIGHT "航班号   起始站   终点站    起飞时间           降落时间         机票数 机票价格\n"
#define PRINTORDER  "%-9d %-20lld  %-8s   %-8d   %-5d  $%-8d\n",OrderList[CurrentOrder].OrderNum,OrderList[CurrentOrder].ClientID,OrderList[CurrentOrder].ClientName,OrderList[CurrentOrder].FlightNum,OrderList[CurrentOrder].TicketNum,OrderList[CurrentOrder].cost
#define ORDER   "订单号    客户身份ID           客户名字   航班号    所定票数  订单价钱\n"

struct plane         	//定义结构体数组
{
    int num;			        	//定义航班号
    char start[30];		            //航班起始站
    char destination[30];			//终点站
    char TakeOffTime[30];			//起飞时间
    char ArriveTime[30];            //到达时间
    int count;	                    //剩余机票数量
    int price;                       //机票价格

} p[MAXFLIGHT];


struct OrderNode
{
    int OrderNum;                       //订单号
    long  long ClientID;                //订票用户身份证
    char ClientName[20];                //订票客户姓名
    int  FlightNum;                     //航班号
    int  TicketNum;                     //购买票数
    int  cost;
} OrderList[E];

int i,m=0,e=0;				//定义全局变量i为已读取元素个数
int CurrentOrder,TotalOrder=0;
char again[10];
int result[E];
int IniResult;

int CorrectInput;

void add();		//函数声明增加航班信息函数
void print(); 		//显示航班信息
int* flightSearch();		//查找航班信息
void book();	//订票业务
void refund();		//退票
void read();		//读取文件
void save();		//保存文件
void output();		//输出格式
void initiate();	//系统初始化
void build();		//建立数据文件
void del(int );         //删除订单
void modify();        //更改航班信息
void cancel();      //删除航班

void main()
{
    int select;
    initiate();		//系统初始化判断是否存在原始数据文件
    srand((int)time(0));
    printf("             ★---您好，欢迎进入飞机订票系统！---★\n");
    printf("===============================================================================\n");
   /* printf("m=%d\n",m);
    printf("i=%d\n",i);
    printf("TotalOrder=%d\n",TotalOrder);
    printf("CurrentOrder=%d\n",CurrentOrder);*/

    do
    {
        printf("\n --------☆         1.增加航班信息           ☆-------- \n\n"
               " --------☆         2.浏览航班以及订票信息    ☆-------- \n\n"
               " --------☆         3.查找航班信息           ☆-------- \n\n"
               " --------☆         4.订票业务               ☆-------- \n\n"
               " --------☆         5.退票业务               ☆-------- \n\n"
               " --------☆         6.修改航班信息           ☆-------- \n\n"
               " --------☆         7.航班取消更新           ☆-------- \n\n"
               " --------☆         0.退出                   ☆-------- \n\n");
        printf("================================================================================\n");
        printf("请在0-6中选择以回车键结束：\n\n");
        scanf("%d",&select);
        switch(select)
        {
        case 1:
            add();		//调用增加航班函数
            save();
            break;
        case 2:
            print();		//调用显示模块
            break;
        case 3:
            flightSearch();	//调用查找模块
            break;
        case 4:
            book();	//调用订票模块
            save();
            break;
        case 5:
            refund();	//调用退票模块
            save();
            break;
        case 6:
            modify();   //调用修改航班信息模块
            break;
        case 7:
            cancel();       //调用取消航班信息模块
            save();
            break;
        case 0:				//退出系统
            save();
            printf("谢谢使用，再见！ ");
            break;
        }
    }
    while(select!=0);		//判断是否调用其他函数
}

void initiate()		//定义系统初始化函数
{
    if(access("Flight.txt",0)==-1)//如果文件存在，返回0，不存在，返回-1。
        build();
    else
        read();
}

void build()		//定义建立数据文件函数
{
//    printf("Build函数！！！！");
    FILE *fp,*fp2;		//定义文件指针


    if((fp2=fopen("ClientOrder.txt","wb"))==NULL)		//打开文件并判定是否出错
    {
        printf("创建订票信息文件失败! ");		//打印出错提示
        getchar();
        return;
    }
    fclose(fp2);

    if((fp=fopen("Flight.txt","wb"))==NULL)		//打开文件并判定是否出错
    {
        printf("创建航班信息文件失败! ");		//打印出错提示
        getchar();
        return;
    }

    printf("请依次输入航班信息(以回车键结束):\n");      //打印提示信息
    printf("-------------------------------------------------------------------------- \n");

    for(i=0; i<MAXFLIGHT; i++)
    {
        printf("请输入航班号: ");
        CorrectInput=scanf("%d",&p[i].num);		         //输入航班号
        while(CorrectInput==0)
            {
                printf("输入错误!请输入正确格式数据！\n");
                getchar();
                CorrectInput=scanf("%d",&p[i].num);
                }

        printf("请输入起始站: ");
        scanf("%s",p[i].start);		        //输入起始站
        printf("请输入终点站: ");
        scanf("%s",p[i].destination);		//输入终点站
        printf("请输入起飞时间: ");
        scanf("%s",p[i].TakeOffTime);		//输入起飞时间
        printf("请输入降落时间: ");
        scanf("%s",p[i].ArriveTime);		//输入降落时间
        printf("请输入机票数: ");
        CorrectInput=scanf("%d",&p[i].count);	        //输入机票数
         while(CorrectInput==0)
            {
                printf("输入错误!请输入正确格式数据！\n");
                getchar();
                CorrectInput=scanf("%d",&p[i].count);
                }

        printf("请输入票价：");
        CorrectInput=scanf("%d",&p[i].price);
         while(CorrectInput==0)
            {
                printf("输入错误!请输入正确格式数据！\n");
                getchar();
                CorrectInput=scanf("%d",&p[i].price);
                }

        fwrite(&p[i],sizeof(struct plane),1,fp);//模块写入数据文件
        m++;                                //总航班数加1

        printf("添加完毕,是否继续添加?请键入y或n以回车键结束:");
        scanf("%s",again);

        if(strcmp(again,"y")!=0)			//判断是否继续添加航班信息
        {
            fclose(fp);			//关闭文件
            return;
        }
    }

}

void read()			//定义读取文件函数
{
    FILE *fp,*fp2;
    if((fp=fopen("Flight.txt","r"))==NULL)
    {
        printf("\n  Warning!!读取航班信息文件失败!!!!! \n");
        getchar();
        exit(1);
    }
    if((fp2=fopen("ClientOrder.txt","r"))==NULL)
    {
        printf("\n  Warning!!读取订票文件失败!!!!! \n");
        getchar();
        exit(1);
    }
    i=0;
    while(!feof(fp))
    {
        fread(&p[i],sizeof(struct plane),1,fp);		//逐块读取数据
        i++;
        m++;		//计算存在航班数
    }
    m--;
    fclose(fp);
    CurrentOrder=0;
    while(!feof(fp2))
    {
        fread(&OrderList[CurrentOrder],sizeof(struct OrderNode),1,fp2);		//逐块读取数据
        CurrentOrder++;
        TotalOrder++;		//计算存在航班数
    }
    TotalOrder--;
    fclose(fp2);

}

void save()		//定义保存函数
{
    printf("save!");
    FILE *fp,*fp2;
    if((fp=fopen("Flight.txt","w"))==NULL)
    {
        printf("写入航班信息文件失败! ");
        getchar();
        return;
        return;
    }
    for(i=0; i<m; i++)			//逐块保存数据
        fwrite(&p[i],sizeof(struct plane),1,fp);
    fclose(fp);

    if((fp2=fopen("ClientOrder.txt","w"))==NULL)
    {
        printf("写入订票信息文件失败! ");
        getchar();
        return;
        return;
    }

    for(CurrentOrder=0; CurrentOrder<TotalOrder; CurrentOrder++)			//逐块保存数据
        fwrite(&OrderList[CurrentOrder],sizeof(struct OrderNode),1,fp2);
    fclose(fp2);
}


void add()		//定义增加航班信息函数
{
    int Tempnum,Tempcount,Tempprice;



    do
    {
        printf("请依次输入您要增加的航班信息(以回车键结束):  \n");      //打印提示信息
        printf("-------------------------------------------------------------------------- \n");
        printf("请输入航班号: ");
            CorrectInput=scanf("%d",&Tempnum);
        while(CorrectInput==0)		//读取航班号
            {
                printf("输入错误!请输入正确格式数据！\n");
                getchar();
                CorrectInput=scanf("%d",&Tempnum);
                }


        for(i=0; i<m; i++)
        {
            if(Tempnum==p[i].num)
            {
                printf("输入错误！存在重复航班号！现返回菜单\n");
                return;
            }
        }

        p[m].num=Tempnum;

        printf("请输入起始站: ");
        scanf("%s",p[m].start);		        //读取起始站


        printf("请输入终点站: ");
        scanf("%s",p[m].destination);		//读取终点站
        printf("请输入起飞时间: ");
        scanf("%s",p[m].TakeOffTime);		//读取起飞时间
        printf("请输入降落时间: ");
        scanf("%s",p[m].ArriveTime);		//读取降落时间
        printf("请输入机票数: ");
        CorrectInput=scanf("%d",&p[m].count);	        //读取机票数
        while(CorrectInput==0)		//读取航班号
            {
                printf("输入错误!请输入正确格式数据！\n");
                getchar();
                CorrectInput=scanf("%d",&p[m].count);
                }

        printf("请输入价格：");
        CorrectInput=scanf("%d",&p[m].price);            //读取机票价格
        while(CorrectInput==0)		//读取航班号
            {
                printf("输入错误!请输入正确格式数据！\n");
                getchar();
                CorrectInput=scanf("%d",&p[m].price);
                }


        m++;                                //读取总航班信息
        printf("添加完毕,是否继续添加?请键入y或n以回车键结束:");
        scanf("%s",again);
    }
    while(!strcmp(again,"y"));		//判断是否继续添加


}

void cancel()   //取消航班
{
    int* outcome;
    int select;
    outcome=flightSearch();	//调用查询模块
    if(outcome[0]==-1)
    {
        printf("对不起!没有找到您所需要的航班,所以不能订票。\n");	//未查找到所需航班
        printf("\n请按回车键返回上层菜单 ");
        getchar();
        getchar();
        return;
    }

    if(outcome[1]!=-1)//搜索结果大于1，需要选择一个
    {
        printf("请选择你需要订票的航班在查询结果中的序号：\n");
        scanf("%d",&select);
        i=outcome[select-1];
    }
    else
        i=outcome[0];
    printf("成功删除以下航班！\n");
    printf(FLIGHT);

    printf(PRINT);
    for(; i<m; i++)
    {
        p[i]=p[i+1];
    }
    m--;


}

void output()		//定义输出格式函数
{
    printf(FLIGHT);		//信息标题

    for(i=0; i<m; i++)
        printf(PRINT);//打印出信息
    printf("展示当前所有订单：\n");
    printf(ORDER);

    for(CurrentOrder=0; CurrentOrder<TotalOrder; CurrentOrder++)
        printf(PRINTORDER);

    printf("m=%d\n",m);
    printf("i=%d\n",i);
    printf("TotalOrder=%d\n",TotalOrder);
    printf("CurrentOrder=%d\n",CurrentOrder);
}

void print()		//定义显示航班信息函数
{
    printf("\n目前我们有如下航班：\n");
    output();			//调用输出格式函数
    printf("\n请按回车键返回上层菜单 ");
    getchar();
    getchar();
}

int* flightSearch()		//定义查询函数
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
        printf("\n请输入航班起点站:");
        scanf("%s",a);		//输入查询的航班起点
        printf("请输入航班终点站:");
        scanf("%s",b);
        printf("\n输入完毕！查询的结果如下:\n\n");
        printf(FLIGHT);
        for(i=0; i<m; i++)
        {

            if(strcmp(p[i].start,a)==0&&strcmp(p[i].destination,b)==0)	//按航班起点和终点站判定输出条件
            {
                count++;
                printf("查到的第%d个航班:\n",count);
                printf(PRINT);		//显示信息
                flag=1;
                result[j++]=i;
            }
        }
        if(flag!=0)
        {
            printf("\n--------☆         查询完毕，共%d个符合条件航班，按回车键继续        ☆--------",count);
//	int k=0;
//	printf("result数组：\n");
//	for(;k<j;k++)
//        printf("%d  %d  %s  %s  星期%s   %d   %d\n",result[k],p[result[k]].num,p[result[k]].start,
            //               p[result[k]].destination,p[result[k]].time,p[result[k]].count ,p[result[k]].price);
            getchar();
            getchar();
            return result;
        }
        else
        {
            printf("\n--------☆         对不起，没有您需要的信息！           ☆--------\n");
            printf("--------☆         是否重新查找?请键入y或n以回车键结束");
            scanf("%s",again);
        }
    }
    while(!strcmp(again,"y")); //判定是否重新查找
    return result;//返回result数组（保存找到的航班对应数组下标）

}

void book()		//定义订票业务函数
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
        outcome=flightSearch();	//调用查询模块
        if(outcome[0]==-1)
        {
            printf("对不起!没有找到您所需要的航班,所以不能订票。\n");	//未查找到所需航班
            printf("\n请按回车键返回上层菜单 ");
            getchar();
            getchar();
            break;
        }
        do
        {
            if(outcome[1]!=-1)//搜索结果大于1，需要选择一个
            {
                printf("请选择你需要订票的航班在查询结果中的序号：\n");
                scanf("%d",&select);
                i=outcome[select-1];
            }
            else
                i=outcome[0];

            printf("请输入您要订的机票数（以回车键结束）： ");
            CorrectInput=scanf("%d",&WantToBookNum);		//输入所订机票数
            while(CorrectInput==0)
            {
                printf("输入错误!请输入正确格式数据！\n");
                getchar();
                CorrectInput=scanf("%d",&WantToBookNum);
                }

            if(WantToBookNum<=0)			//判定机票数是否出错
            {
                printf("输入错误！至少需订1张机票。\n");
            }
            else if(p[i].count==0)//判定机票是否售完
            {
                printf("对不起，你所选择的航班的机票已售完!\n");
                    if(outcome[1]!=-1)//搜索结果大于1，需要选择一个
                      {

                        printf("现为你推荐以下航班：\n");
                        for(IniResult=0;IniResult<E;IniResult++)
                            if(outcome[IniResult]!=-1&&p[outcome[IniResult]].count!=0)
                            {
                              i=outcome[IniResult];
                                printf(PRINT);
                            }

                      }
                break;
            }
            else if(p[i].count!=0&&p[i].count>=WantToBookNum)	//判定机票数是否大于等于订票数
            {

                printf("请输入您的姓名：");
                scanf("%s",OrderList[TotalOrder].ClientName);

                printf("请输入您的身份证：");
                scanf("%lld",&(OrderList[TotalOrder].ClientID));

                OrderList[TotalOrder].FlightNum=p[i].num;
                OrderList[TotalOrder].TicketNum=WantToBookNum;
                OrderList[TotalOrder].OrderNum=rand();
                OrderList[TotalOrder].cost=p[i].price*WantToBookNum;

                TotalOrder++;
                p[i].count=p[i].count-WantToBookNum;
                printf("订票成功!\n");
                printf("请支付$%d元，谢谢！\n",p[i].price*WantToBookNum);
                break;
            }
            else if(p[i].count<WantToBookNum)//判定机票数是否小于订票数
            {
                printf("对不起，你所选择的航班只剩%d张机票\n", p[i].count);
                printf("要重新输入要预定的机票数吗?请输入y或n以回车键结束: ");//判定是否重新输入订票数
                scanf("%s",again);
            }
        }
        while(!strcmp(again,"y"));
        printf("\n是否需要订其他航班的机票?请输入y或n以回车键结束: ");
        scanf("%s",again);
    }
    while(!strcmp(again,"y"));		//判定是否继续订票


}

void refund()		//定义退票函数
{
    int* h;
    int n;
    int flag=0;
    int num;
    int temp;

    do
    {
        // printf("请输入退票的订单号或者");
        printf("请输入退票的订单号：\n");
        scanf("%d",&num);

        for(CurrentOrder=0; CurrentOrder<TotalOrder; CurrentOrder++)
        {
            if(OrderList[CurrentOrder].OrderNum==num)
            {
                flag=1;
                printf("已找到该订单,请选择：\n");
                printf("y:订单取消;n:退掉部分票（y/n）\n");
                scanf("%s",again);
                if(strcmp(again,"y"))
                {
                    printf("请问要退多少张票呢:\n");
                    scanf("%d",&n);
                    if(n<=0)
                    {
                        printf("输入错误，至少退掉一张票!\n");
                        return;
                    }
                    else if(n>OrderList[CurrentOrder].TicketNum)
                        printf("输入错误，退票多于已定的票！\n");
                    else if(n==OrderList[CurrentOrder].TicketNum)
                    {
                        printf("删除订单！\n");
                        del(CurrentOrder);
                    }
                    else
                        {
                            temp=(OrderList[CurrentOrder].cost/OrderList[CurrentOrder].TicketNum)*n;

                            printf("成功退了%d张票,共退回%d元！谢谢\n",n,temp);
                            OrderList[CurrentOrder].TicketNum-=n;
                            OrderList[CurrentOrder].cost-=temp;
                        }
                }
                else
                {

                    printf("删除订单！\n");
                    del(CurrentOrder);
                }

            }

        }
        if(flag==0)
        {
            printf("对不起!没有找到您所需要的航班,所以不能退票。\n");
            printf("\n请按回车键返回上层菜单 ");
            getchar();
            getchar();
            break;
        }



        printf("是否继续退其他票？ 请键入y或n以回车键结束: ");		//判定是否继续退票
        scanf("%s",again);
    }
    while(!strcmp(again,"y"));		//判定并跳出循环

}

void del(int delOrder)//删除订单
{
    int a,j,n;

    for(a=delOrder; a<TotalOrder; a++)
    {
        OrderList[a]=OrderList[a+1];
    }
    printf("删除成功！\n");
    TotalOrder--;
}


void modify()//改变航班信息
{
    int ModifyOption,CheckPnum,Startordestination,w,q;
    int TakeOffOrArrive;
    int remain;
    char h[30],g[30],again[20];
    int flag=0;

    printf("请输入要修改的航班的航班号\n");
    scanf("%d",&CheckPnum);

    for(i=0; i<MAXFLIGHT; i++)
    {
        if(p[i].num==CheckPnum)
        {
            printf("已找到此航班：\n");
            flag=1;
            printf(FLIGHT);
            printf(PRINT);

            do
            {
                printf("\n请选择:  1.修改起降点;2.修改时间;3.价格;4.航班号;5.所剩票数0.退出\n");
                scanf("%d",&ModifyOption);

                switch(ModifyOption)
                {
                case 1:
                    printf("请选择修改的是：1.起飞地点;2.降落地点\n");
                    scanf("%d",&Startordestination);
                    if(Startordestination==1)
                    {
                        printf("请输入修改后的起始站：\n");
                        scanf("%s",h);
                        strcpy(p[i].start,h);
                        printf("修改成功");

                    }
                    else  if(Startordestination==2)
                    {
                        printf("请输入修改后的终点站：\n");
                        scanf("%s",h);
                        strcpy(p[i].destination,h);
                        printf("修改成功");
                    }

                    break;
                case 2:
                    printf("请选择修改的是：1.起飞时间;2.到达时间\n");
                    scanf("%d",&TakeOffOrArrive);
                    if(TakeOffOrArrive==1)
                    {

                        printf("请输入修改后的时间\n");
                        scanf("%s",g);
                        strcpy(p[i].TakeOffTime,g);
                        printf("修改成功");

                    }
                    else  if(TakeOffOrArrive==2)
                    {

                        printf("请输入修改后的时间\n");
                        scanf("%s",g);
                        strcpy(p[i].ArriveTime,g);
                        printf("修改成功");
                    }


                    break;
                case 3:

                    printf("请输入修改后的价格\n");
                    scanf("%d",&w);
                    p[i].price=w;
                    printf("修改成功");

                    break;

                case 4:
                    printf("请输入修改后的航班号\n");
                    scanf("%d",&q);
                    p[i].num=q;

                    break;
                case 5:
                    printf("请输入修改后的所剩票数：\n");
                    scanf("%d",&remain);
                    p[i].count=remain;
                    break;

                case 0:				//退出系统

                    return;
                }
                printf("\n是否继续修改？（y/n）\n");
                scanf("%s",again);
            }
            while(!strcmp(again,"y"));
            save();
        }

    }
    if(flag==0)
        printf("航班号输入错误！！并没有这航班！现退出至菜单\n");
}


