#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//定义学生用户结构体
struct Student
{
    char name[10];//用户名
    char id[10];//账号
    char password[8];//密码
    char type[10];//类型
    struct Student *next;//下一个链表地址
};
//重命名类型名
typedef struct Student student, *student_pointer;

//定义数据信息结构体
struct Book
{
    int  id;//编号
	char name[20];//书名
	char author[20];//作者
	char publisher[20];//出版商
	char type[20];//类型
	int pubtime;//出版时间
	int price;//价格
	int Num;//退出状态码
    struct Book *next;//下一个链表地址
};
//重命名类型名
typedef struct Book book, *book_pointer;
//定义全局状态码
int select, b=0;
//定义结构体指针
book_pointer book_head;
student_pointer student_head;


//声明全局函数
void load(book_pointer book_head,student_pointer student_head);//将文件中的信息加载到链表中
void login(student_pointer k,char str1[],char str2[]);//检验账号信息函数
int compare(char k[],char m[], char n[], char str[], char password[]);//密码校验
void librarian(book_pointer book_head, student_pointer student_head);//管理员入口函数
void user_management_system(student_pointer student_head);//用户管理函数
void reader(book_pointer book_head, student_pointer student_head);//普通读者函数
void change(student_pointer student_head);//修改用户密码
void adduser(student_pointer student_head);//新增用户
void deleteuser(student_pointer student_head);//删除用户
void print(student_pointer student_head);//显示读者信息入口函数
void printuser(student_pointer student_head);//输出用户信息
void printadmin(student_pointer student_head);//输出管理员信息
void save(student_pointer student_head);//保存用户信息
void password(student_pointer student_head);//读者更改密码
void book_management_system(book_pointer book_head);//图书信息管理函数
void newbook(book_pointer book_head);//添加图书信息
void Save(book_pointer book_head);//将图书馆信息导入文件中
void Output(book_pointer book_head);//输出图书信息
void oldbook(book_pointer book_head);//旧书下架
void titledelete(book_pointer book_head);//按书名删除书籍
void iddelete(book_pointer book_head);//按编号删除书籍
void search(book_pointer book_head);//查询图书信息
void titlesearch(book_pointer book_head);//书名查找
void authorsearch(book_pointer book_head);//作者名查找
void modify(book_pointer book_head);//图书信息修改

int main()
{
    system("color 3a");//命令行换色
    //赋值用户结构体头指针
    student_head=(student_pointer)malloc(sizeof(student));
    //复制书籍结构体头指针
    book_head=(book_pointer)malloc(sizeof(book));
    //初始化结构体内指针信息
    student_head->next=NULL;
    book_head->next=NULL;
    load(book_head,student_head);
    //初始化登录资料
    char id[10],password[10];
    student_pointer k=student_head;
    while (1)
    {
        system("cls");
        printf("***************************************************\n");
        printf("*     ______   __    __  __      __  ________     *\n");
        printf("*    /      \\ /  |  /  |/  \\    /  |/        |    *\n");
        printf("*   /$$$$$$  |$$ | /$$/ $$  \\  /$$/ $$$$$$$$/     *\n");
        printf("*   $$ \\__$$/ $$ |/$$/   $$  \\/$$/  $$ |__        *\n");
        printf("*   $$      \\ $$  $$<     $$  $$/   $$    |       *\n");
        printf("*    $$$$$$  |$$$$$  \\     $$$$/    $$$$$/        *\n");
        printf("*   /  \\__$$ |$$ |$$  \\     $$ |    $$ |_____     *\n");
        printf("*   $$    $$/ $$ | $$  |    $$ |    $$       |    *\n");
        printf("*    $$$$$$/  $$/   $$/     $$/     $$$$$$$$/     *\n");
        printf("*                                                 *\n");
        printf("*               欢迎来到图书管理系统              *\n");
        printf("***************************************************\n\n");
        printf("请输入用户名和密码或账号和密码：\n");
        printf("用户名或账号：");
        scanf("%s",id);
        printf("密码：");
        scanf("%s",password);
        login(k,id,password);
    }       
    return 0;
}

void load(book_pointer book_head,student_pointer student_head)
{
    book_pointer p1,p2=book_head;
	char name[20],author[20],publisher[20],type[20];
	int id, pubtime,price,Num;
    FILE *fp;
    if((fp=fopen("bookinfo.txt","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}
	while(fscanf(fp,"%d%s%s%s%s%d%d%d",&id,&name,&author,&publisher,&type,&pubtime,&price,&Num)!=EOF)
    {
      p1=(book_pointer)malloc(sizeof(book));
	  p1->id=id;
      p1->pubtime=pubtime;
	  p1->price=price;
      p1->Num=Num;
	  strcpy(p1->name,name);
	  strcpy(p1->author,author);
	  strcpy(p1->publisher,publisher);
	  strcpy(p1->type,type);
	  p2->next=p1;
	  p2=p1;
    }
    p2->next=NULL;


    student_pointer p3,p4=student_head;
	char name1[10],id1[10],password1[10],type1[10];
    if((fp=fopen("userinfo.txt","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}
	while(fscanf(fp,"%s %s %s %s",name1,id1, password1,type1)!=EOF)
    {
      p3=(student_pointer)malloc(sizeof(student));
      strcpy(p3->name,name1);
	  strcpy(p3->id,id1);
	  strcpy(p3->password,password1);
	  strcpy(p3->type,type1);
	  p4->next=p3;
	  p4=p3;
    }
    p4->next=NULL;
}

void login(student_pointer k,char id[],char password[])
{
    while(k)
        {
            b=0;//复位帐号登录状态
            b=compare(k->name,k->id,k->password,id,password);
            if(b==1)
            {
               if(strcmp(k->type,"管理员")==0)
               {
                   librarian(book_head, student_head);//图书管理员函数
               }
               if(strcmp(k->type,"用户")==0)
               {
                   reader(book_head, student_head);//普通用户函数
               }
               break;//直接跳出循环，实现帐号注销
            }
            k=k->next;
        }
        int b1;//用于记录是否重新输入状态码
        while(b!=1)//是否注销帐号状态码
        {
            printf("输入信息错误，退出请按0，再次输入按1：\n");
            scanf("%d",&b1);
            if(b1==1)//重新输入
            {
                printf("请重新输入信息：\n");
                printf("用户名或账号：");
                scanf("%s",id);//id是字符串，即本身就是指针
                printf("密码：");
                scanf("%s",password);
                k=student_head;//重置指针
                while(k)
                {
                    b=0;
                    b=compare(k->name,k->id,k->password,id,password);
                    if(b==1)//重新输入
                    {
                        if(strcmp(k->type,"管理员")==0)
                        {
                            librarian(book_head, student_head);//管理员函数
                        }
                        if(strcmp(k->type,"用户")==0)
                        {
                            reader(book_head, student_head);//普通读者函数
                        }
                        break;//实现帐号注销
                    }
                    k=k->next;
                }
            }
            else if (b1==0)//退出
            {
                exit(0);
            }
            else//异常处理
            {
                printf("选择选项不存在\n\n"); 
            }       
        }
}

int compare(char k[],char m[], char n[], char str[], char password[])
{
    if((strcmp(str,k)==0||strcmp(str,m)==0)&&(strcmp(password,n)==0))
    {
        printf("输入信息正确,即将进入系统\n\n");
        return 1;
    }
    return 0;
}

void librarian(book_pointer book_head, student_pointer student_head)//图书管理员函数
{
    do{
    printf("******************************************\n");
    printf("*             1:用户管理                 *\n");
    printf("*             2:图书信息管理             *\n");
    printf("*             3:注销                     *\n");
    printf("******************************************\n\n");
    printf("请输入你要进行的项目选项\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            user_management_system(student_head);//用户管理函数
            break;
        case 2:
            book_management_system(book_head);//图书信息管理函数
            break;
        case 3:
            printf("\n\n");
            break;
        default:
            printf("输入选项不存在！\n\n");
    }}while(select!=3);
}

void user_management_system(student_pointer student_head)//用户管理函数
{
    do{
    printf("************************************\n");
    printf("*        1:添加账号                *\n");
    printf("*        2:删除账号                *\n");
    printf("*        3:输出已有账号            *\n");
    printf("*        4:重置用户密码             *\n");
    printf("*        5:返回                    *\n");
    printf("************************************\n\n");
    printf("请输入你要进行的项目选项\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            adduser(student_head);//添加账号
            break;
        case 2:
            deleteuser(student_head);//删除账号
            break;
        case 3:
            print(student_head);//输出已有账号
            break;
        case 4:
            change(student_head);//重置用户密码
            break;
        case 5:
            printf("\n\n");
            break;
        default:
            printf("输入选项不存在！\n");
    }}while(select!=5);
}


void adduser(student_pointer student_head)
{
    student_pointer p1,p2=student_head;
    char name[10];
    char id[10];//char id[10];
    char password[8];//char password[8];
    char type[10];
    FILE *fp;
    //以重新load用户信息方式找到链表末尾
    //这种方式浪费内存空间
    if((fp=fopen("userinfo.txt","r+"))==NULL)
    {
        printf("File Open Error!\n");
        exit(0);
    }
    while(fscanf(fp,"%s %s %s %s",name,id,password,type)!=EOF)
        {
            p1=(student_pointer)malloc(sizeof(student));
            strcpy(p1->name,name);
            strcpy(p1->id,id);
            strcpy(p1->password,password);
            strcpy(p1->type,type);
            p2->next=p1;
            p2=p1;//最后两个指针指向最后一个堆块
        }
    printf("请依次输入用户名、账号、密码和类别，输入#表示输入结束\n");
    printf("输入示例：张三 1 111111 用户\n");
        while(scanf("%s",&name)!=EOF&&strcmp(name,"#")!=0)
        {
            p1=(student_pointer)malloc(sizeof(student));
            scanf("%s",&id);
            scanf("%s",&password);
            scanf("%s",&type);
            strcpy(p1->name,name);
            strcpy(p1->id,id);
            strcpy(p1->password,password);
            strcpy(p1->type,type);
            p2->next=p1;
            p2=p1;
        }
        p2->next=NULL;
        printf("已有普通读者用户信息:\n");
        printuser(student_head);
        save(student_head);
}

void deleteuser(student_pointer student_head)//删除读者账号
{
    printf("请输入待删除的读者用户名或账号信息\n");
    student_pointer p1=student_head,p2;
    char Delete[20];
    int flag=0;
    scanf("%s",Delete);
    while(p1)
    {
        p2=p1;
        p1=p1->next;
        if(p1)
        {
                if(strcmp(Delete,p1->name)==0||strcmp(Delete,p1->id)==0)
                {
                    printf("待删除的读者信息为：\n");
                    printf("%s %s %s %s\n",p1->name,p1->id,p1->password,p1->type);
                    p2->next=p1->next;
                    flag=1;
                    free(p1);
                    printf("读者信息已删除\n");
                }
        }

    }
    if(flag==0)
    {

        printf("查无读者信息，无法删除\n");

    }
    save(student_head);
}

void print(student_pointer student_head)//显示已有读者信息
{
    do{
    printf("************************************\n");
    printf("*        1:输出管理员账号            *\n");
    printf("*        2:输出用户账号              *\n");
    printf("*        3:返回                    *\n");
    printf("************************************\n\n");
    printf("请输入你要进行的项目选项\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            printadmin(student_head);//输出管理员信息
            break;
        case 2:
            printuser(student_head);//输出用户信息
            break;
        case 3:
            printf("\n\n");
            break;
        default:
            printf("输入选项不存在！\n");
            break;
    }}while(select!=3);
}

void printadmin(student_pointer student_head)//输出管理员信息
{
    student_pointer p=student_head->next;
    int i=0;
    while(p)
    {
        if(strcmp(p->type,"管理员")==0)
        {
            printf("%s %s %s\n",p->name,p->id,p->password);
            i++;
        }
        p=p->next;
    }
    if(i==0)
        printf("没有管理员信息！");
}
void printuser(student_pointer student_head)//输出用户信息
{
    student_pointer p=student_head->next;
    int i=0;
    while(p)
    {
        if(strcmp(p->type,"用户")==0)
        {
            printf("%s %s %s\n",p->name,p->id,p->password);
            i++;
        }
        p=p->next;
    }
    if(i==0)
    {
        printf("没有用户信息！");
    }
}

void change(student_pointer student_head)
{
    student_pointer p=student_head->next;
    char name[10];
    int flag=0;//修改状态标识符
    printf("请输入要重置密码的用户名或账号：\n");
    scanf("%s",&name);
    while(p)
    {
        if(strcmp(p->type,"用户")==0)//限制只能修改用户密码
        {
            if(strcmp(p->name,name)==0||strcmp(p->id,name)==0)
            {
                printf("请输入重置密码：\n");
                scanf("%s",p->password);
                printf("已重置用户密码！\n");
                flag=1;
            }
        }
       p=p->next;
    }
    if(flag==0)
    {
        printf("未找到对应的用户名或账号！\n");
    }
    printf("当前读者信息为：\n");
    printuser(student_head);
    save(student_head);
}

void save(student_pointer student_head)
{
    FILE *fp;
    student_pointer p;
    if((fp=fopen("userinfo.txt","w"))==NULL)
    {
        printf("File Open Error!\n");
        exit(0);
    }
    for(p=student_head->next;p;p=p->next)
        {
            fprintf(fp,"%s %s %s %s\n",p->name,p->id,p->password,p->type);
        }
        fclose(fp);
}

void book_management_system(book_pointer book_head)//图书信息管理函数
{
      do{
      printf("**********************************************\n");
	  printf("*         欢迎进入图书管理员界面             *\n");
	  printf("*         1：新书上架                        *\n");
	  printf("*         2：输出图书信息                    *\n");
	  printf("*         3：查询                            *\n");
	  printf("*         4：旧书下架                        *\n");
	  printf("*         5：修改图书信息                    *\n");
	  printf("*         6：退出                            *\n");
	  printf("**********************************************\n");

	  printf("     请输入你的选择：\n");
      scanf("%d",&select);

    switch(select)
    {
        case 1:newbook(book_head);//新书上架
		       break;
	    case 2:Output(book_head);//图书输出
		       break;
	    case 3:search(book_head);//图书查找
		       break;
	    case 4:oldbook(book_head);//旧书下架
		       break;
	    case 5:modify(book_head);//修改图书信息
		       break;
        case 6:printf("\n\n");
                break;
        default:
            printf("选项不存在!\n");
    }}while(select!=6);
}

void newbook(book_pointer book_head)//添加图书信息
{
	book_pointer p1,p2=book_head;
	char name[20],author[20],publisher[20],type[20];
	int id,pubtime,price,Num;
    FILE *fp;

    if((fp=fopen("bookinfo.txt","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}

	while(fscanf(fp,"%d%s%s%s%s%d%d%d",&id,name,author,publisher,type,&pubtime,&price,&Num)!=EOF)
    {
      p1=(book_pointer)malloc(sizeof(book));
	  p1->id=id;
	  strcpy(p1->name,name);
	  strcpy(p1->author,author);
	  strcpy(p1->publisher,publisher);
	  strcpy(p1->type,type);
	  p1->pubtime=pubtime;
	  p1->price=price;
	  p1->Num=Num;
	  p2->next=p1;
	  p2=p1;
    }

	printf("请依次输入图书编号、书名、作者、出版社、类别、出版年月日、价格、库存,输入-1表示输入结束\n");
    printf("输入示例：201501 西游记 吴承恩 中华  名著 19580624 56 59\n");
    while(scanf("%d",&id),id!=-1)
    {
      p1=(book_pointer)malloc(sizeof(book));
      scanf("%s%s%s%s%d%d%d",&name,&author,&publisher,&type,&pubtime,&price,&Num);
	  p1->id=id;
      p1->pubtime=pubtime;
	  p1->price=price;
	  p1->Num=Num;
	  strcpy(p1->name,name);
	  strcpy(p1->author,author);
	  strcpy(p1->publisher,publisher);
	  strcpy(p1->type,type);
	  p2->next=p1;
	  p2=p1;
	}

   p2->next=NULL;
   Save(book_head);
   printf("现在的图书信息为：\n");
   Output(book_head);
}

void Save(book_pointer book_head)//将图书馆信息导入文件中
{
	FILE *fp;
	book_pointer p;

	if((fp=fopen("bookinfo.txt","w"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}
    for(p=book_head->next;p;p=p->next)
	{
	   fprintf(fp,"%d%10s%10s%10s%10s%10d%8d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
	}
	fclose(fp);
}

void Output(book_pointer book_head)//输出图书信息
{
   book_pointer p=book_head->next;

   if(p==NULL)
   {
	   printf("没有图书信息\n");
   }
   else
   {
       printf("编号      书名    作者     出版社   类别 出版年月日 价格   库存\n");
	   while(p)
	   {
         printf("%d%8s%10s%8s%8s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
         p=p->next;
	   }
   }
}

void search(book_pointer book_head)//查询图书信息
{
    do{
    printf("***********************************\n");
    printf("*         1:按书名查找            *\n");
    printf("*         2:作者名查找            *\n");
    printf("*         3:返回                  *\n");
    printf("***********************************\n\n");
    printf("     请输入你要进行的项目选项\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            titlesearch(book_head);//书名查找
            break;
        case 2:
            authorsearch(book_head);//作者名查找
            break;
        case 3:
            printf("\n\n");
            break;
        default:printf("选项不存在\n");
    }}while(select!=3);
}

void titlesearch(book_pointer book_head)//书名查找
{
    book_pointer p=book_head->next;
	char name[20];
	int flag=0;//查询状态码

    printf("请输入要查询的书名：\n");
	scanf("%s",name);
    while(p)
	{
		if(strstr(p->name,name)!=NULL||strstr(name,p->name)!=NULL)//模糊匹配
		{
			printf("%d%8s%10s%8s%10s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
		    flag=1;
		}
		  p=p->next;
	}
	if(flag==0)
	 printf("该书信息不存在\n");
}

void authorsearch(book_pointer book_head)//作者名查找
{
	book_pointer p=book_head->next;
	char author[20];
	int flag=0;

    printf("请输入要查询的作者名字：\n");
	scanf("%s",author);
    while(p)
	{
		if(strstr(p->author,author)!=NULL||strstr(author,p->author)!=NULL)//模糊匹配
		{
			printf("%d%8s%10s%8s%10s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
		    flag=1;
		}
		  p=p->next;
	}
	if(flag==0)
	printf("该书信息不存在\n");
}

void oldbook(book_pointer book_head)//旧书下架
{
    do{
    printf("************************************\n");
    printf("*         1:按书名删除             *\n");
    printf("*         2:按编号删除             *\n");
    printf("*         3：退出                  *\n");
    printf("************************************\n\n");
    printf("      请输入你要进行的项目选项\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            titledelete(book_head);//按书名删除
            break;
        case 2:
            iddelete(book_head);//按编号删除
            break;
        case 3:
            printf("\n\n");
            break;
        default:
            printf("选项不存在!\n");
    }}while(select!=3);
}

void titledelete(book_pointer book_head)//按书名删除
{
    book_pointer p1=book_head,p2;
    char name[10];
	int  flag=0;//删除状态码

	printf("请输入要删除图书的书名：\n");
	scanf("%s",&name);
	while(p1)
	{
	    p2=p1;
        p1=p1->next;
        if(p1)
        {
            if(strcmp(name,p1->name)==0)
            {
                p2->next=p1->next;
                flag=1;
                free(p1);
                printf("书籍信息已删除\n");
            }
        }
	}
	if(flag==0)
	{
		printf("该图书信息不存在\n");
	}
	if(flag==1)
	{
	  printf("删除后的图书信息为:\n");
	  Output(book_head);
	  Save(book_head);
	}
}

void iddelete(book_pointer book_head)//按编号删除书籍
{
    book_pointer p1=book_head,p2=book_head->next;
    int id,flag=0;

	printf("请输入要删除图书的编号：\n");
	scanf("%d",&id);
	while(p1)
	{
	    p2=p1;
        p1=p1->next;
        if(p1)
        {
            if (p1->id==id)
            {
                p2->next=p1->next;
                flag=1;
                free(p1);
                printf("书籍信息已删除\n");
            }            
        }
	}
	if(flag==0)
	{
		printf("符合条件的图书信息不存在\n");
	}
	if(flag==1)
	{
		printf("删除后的图书信息为:\n");
	    Output(book_head);
		Save(book_head);
	}
}

void modify(book_pointer book_head)//图书信息修改
{    
    char name[20],author[20],publisher[20],type[20];
    int  id,pubtime,price,Num;
    char sel;//修改操作选择符
	int  flag=0;//修改状态码
	book_pointer p;

	printf("请输入要修改图书的编号：\n");
	scanf("%d",&id);

	if(book_head==NULL)
	{
		printf("没有图书信息\n");
	}
	for(p=book_head;p!=NULL;p=p->next)//遍历查询需修改的书籍的堆块位置
	{
		if(p->id==id)
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
		printf("图书信息不存在\n");
	if(flag==1)
	{
		printf("该图书的信息已查询到，信息如下：\n");
		printf("编号      书名    作者     出版社    类别    出版年月日   价格   库存\n");
	    printf("%d%8s%10s%8s%10s%10d%8d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
        getchar();
        //修改书名
		printf("是否修改书名，请输入 y or n:\n");
		scanf("%c",&sel);
		if(sel=='y')
		{
			printf("请输入书名：\n");
			scanf("%s",name);
			strcpy(p->name,name);;
		}
		//修改作者名
		printf("是否修改作者名，请输入 y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("请输入作者名：\n");
			scanf("%s",author);
			strcpy(p->author,author);
		}
		//修改出版社
	    printf("是否修改出版社，请输入 y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("请输入出版社：\n");
			scanf("%s",publisher);
			strcpy(p->publisher,publisher);
		}
		//修改图书类型
	    printf("是否修改图书类型，请输入 y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("请输入图书类型：\n");
			scanf("%s",type);
			strcpy(p->type,type);
		}
		//修改出版时间
        printf("是否修改出版时间，请输入 y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("请输入出版时间：\n");
			scanf("%d",&pubtime);
			p->pubtime=pubtime;
		}
		//是否修改价格
		printf("是否修改价格，请输入 y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("请输入价格：\n");
			scanf("%d",&price);
			p->price=price;
		}
		printf("是否修改库存，请输入 y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("请输入库存：\n");
			scanf("%d",&Num);
			p->Num=Num;
		}
		printf("修改后的图书信息为：\n");
        printf("编号      书名    作者     出版社    类别    出版年月日   价格   库存\n");
	    printf("%d%8s%10s%8s%10s%10d%8d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);

		Save(book_head);
	}
}

void reader(book_pointer book_head, student_pointer student_head)//普通读者函数
{
    do{
    printf("************************************\n");
    printf("*          1:更改密码              *\n");
    printf("*          2:查询图书信息          *\n");
    printf("*          3:退出                  *\n");
    printf("************************************\n\n");
    printf("   请输入你要进行的项目选项\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            password(student_head);//读者更改密码
            break;
        case 2:
            search(book_head);//查询图书信息
            break;
        case 3:
            printf("\n\n");
            break;
        default:
            printf("选项不存在\n");
    }}while(select!=3);
}

void password(student_pointer student_head)//读者更改密码
{
    student_pointer p=student_head->next;
    int flag=0;//密码修改状态码
    char name[10], password[10];
    printf("请输入您的用户名或账号\n");
    scanf("%s",name);
    int m=1;//密码校验状态码
    while(p)
	{
		if(strcmp(p->name,name)==0||strcmp(p->id,name)==0)//模糊匹配
		{
		    while(m==1)//校验原密码
            {
                printf("请输入您原来的密码\n");
                scanf("%s", password);
                if(strcmp(p->password, password)!=0)
                {
                    printf("密码错误，重新输入请按1， 退出请按2\n");
                    scanf("%d", &m);
                    continue;
                }
                if(strcmp(p->password, password)==0)//密码正确完成校验
                    break;
		    }
		    if(m==2)
                break;
			printf("请输入您的新密码\n");
	        scanf("%s", password);
	        strcpy(p->password,password);
            printf("密码修改成功\n");
	        save(student_head);
	        flag=1;
	        break;
		}
		p=p->next;
	}
	if(flag==0)
		printf("账号信息不存在\n");
}
