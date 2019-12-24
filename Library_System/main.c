#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//����ѧ���û��ṹ��
struct Student
{
    char name[10];//�û���
    char id[10];//�˺�
    char password[8];//����
    char type[10];//����
    struct Student *next;//��һ�������ַ
};
//������������
typedef struct Student student, *student_pointer;

//����������Ϣ�ṹ��
struct Book
{
    int  id;//���
	char name[20];//����
	char author[20];//����
	char publisher[20];//������
	char type[20];//����
	int pubtime;//����ʱ��
	int price;//�۸�
	int Num;//�˳�״̬��
    struct Book *next;//��һ�������ַ
};
//������������
typedef struct Book book, *book_pointer;
//����ȫ��״̬��
int select, b=0;
//����ṹ��ָ��
book_pointer book_head;
student_pointer student_head;


//����ȫ�ֺ���
void load(book_pointer book_head,student_pointer student_head);//���ļ��е���Ϣ���ص�������
void login(student_pointer k,char str1[],char str2[]);//�����˺���Ϣ����
int compare(char k[],char m[], char n[], char str[], char password[]);//����У��
void librarian(book_pointer book_head, student_pointer student_head);//����Ա��ں���
void user_management_system(student_pointer student_head);//�û�������
void reader(book_pointer book_head, student_pointer student_head);//��ͨ���ߺ���
void change(student_pointer student_head);//�޸��û�����
void adduser(student_pointer student_head);//�����û�
void deleteuser(student_pointer student_head);//ɾ���û�
void print(student_pointer student_head);//��ʾ������Ϣ��ں���
void printuser(student_pointer student_head);//����û���Ϣ
void printadmin(student_pointer student_head);//�������Ա��Ϣ
void save(student_pointer student_head);//�����û���Ϣ
void password(student_pointer student_head);//���߸�������
void book_management_system(book_pointer book_head);//ͼ����Ϣ������
void newbook(book_pointer book_head);//���ͼ����Ϣ
void Save(book_pointer book_head);//��ͼ�����Ϣ�����ļ���
void Output(book_pointer book_head);//���ͼ����Ϣ
void oldbook(book_pointer book_head);//�����¼�
void titledelete(book_pointer book_head);//������ɾ���鼮
void iddelete(book_pointer book_head);//�����ɾ���鼮
void search(book_pointer book_head);//��ѯͼ����Ϣ
void titlesearch(book_pointer book_head);//��������
void authorsearch(book_pointer book_head);//����������
void modify(book_pointer book_head);//ͼ����Ϣ�޸�

int main()
{
    system("color 3a");//�����л�ɫ
    //��ֵ�û��ṹ��ͷָ��
    student_head=(student_pointer)malloc(sizeof(student));
    //�����鼮�ṹ��ͷָ��
    book_head=(book_pointer)malloc(sizeof(book));
    //��ʼ���ṹ����ָ����Ϣ
    student_head->next=NULL;
    book_head->next=NULL;
    load(book_head,student_head);
    //��ʼ����¼����
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
        printf("*               ��ӭ����ͼ�����ϵͳ              *\n");
        printf("***************************************************\n\n");
        printf("�������û�����������˺ź����룺\n");
        printf("�û������˺ţ�");
        scanf("%s",id);
        printf("���룺");
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
            b=0;//��λ�ʺŵ�¼״̬
            b=compare(k->name,k->id,k->password,id,password);
            if(b==1)
            {
               if(strcmp(k->type,"����Ա")==0)
               {
                   librarian(book_head, student_head);//ͼ�����Ա����
               }
               if(strcmp(k->type,"�û�")==0)
               {
                   reader(book_head, student_head);//��ͨ�û�����
               }
               break;//ֱ������ѭ����ʵ���ʺ�ע��
            }
            k=k->next;
        }
        int b1;//���ڼ�¼�Ƿ���������״̬��
        while(b!=1)//�Ƿ�ע���ʺ�״̬��
        {
            printf("������Ϣ�����˳��밴0���ٴ����밴1��\n");
            scanf("%d",&b1);
            if(b1==1)//��������
            {
                printf("������������Ϣ��\n");
                printf("�û������˺ţ�");
                scanf("%s",id);//id���ַ��������������ָ��
                printf("���룺");
                scanf("%s",password);
                k=student_head;//����ָ��
                while(k)
                {
                    b=0;
                    b=compare(k->name,k->id,k->password,id,password);
                    if(b==1)//��������
                    {
                        if(strcmp(k->type,"����Ա")==0)
                        {
                            librarian(book_head, student_head);//����Ա����
                        }
                        if(strcmp(k->type,"�û�")==0)
                        {
                            reader(book_head, student_head);//��ͨ���ߺ���
                        }
                        break;//ʵ���ʺ�ע��
                    }
                    k=k->next;
                }
            }
            else if (b1==0)//�˳�
            {
                exit(0);
            }
            else//�쳣����
            {
                printf("ѡ��ѡ�����\n\n"); 
            }       
        }
}

int compare(char k[],char m[], char n[], char str[], char password[])
{
    if((strcmp(str,k)==0||strcmp(str,m)==0)&&(strcmp(password,n)==0))
    {
        printf("������Ϣ��ȷ,��������ϵͳ\n\n");
        return 1;
    }
    return 0;
}

void librarian(book_pointer book_head, student_pointer student_head)//ͼ�����Ա����
{
    do{
    printf("******************************************\n");
    printf("*             1:�û�����                 *\n");
    printf("*             2:ͼ����Ϣ����             *\n");
    printf("*             3:ע��                     *\n");
    printf("******************************************\n\n");
    printf("��������Ҫ���е���Ŀѡ��\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            user_management_system(student_head);//�û�������
            break;
        case 2:
            book_management_system(book_head);//ͼ����Ϣ������
            break;
        case 3:
            printf("\n\n");
            break;
        default:
            printf("����ѡ����ڣ�\n\n");
    }}while(select!=3);
}

void user_management_system(student_pointer student_head)//�û�������
{
    do{
    printf("************************************\n");
    printf("*        1:����˺�                *\n");
    printf("*        2:ɾ���˺�                *\n");
    printf("*        3:��������˺�            *\n");
    printf("*        4:�����û�����             *\n");
    printf("*        5:����                    *\n");
    printf("************************************\n\n");
    printf("��������Ҫ���е���Ŀѡ��\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            adduser(student_head);//����˺�
            break;
        case 2:
            deleteuser(student_head);//ɾ���˺�
            break;
        case 3:
            print(student_head);//��������˺�
            break;
        case 4:
            change(student_head);//�����û�����
            break;
        case 5:
            printf("\n\n");
            break;
        default:
            printf("����ѡ����ڣ�\n");
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
    //������load�û���Ϣ��ʽ�ҵ�����ĩβ
    //���ַ�ʽ�˷��ڴ�ռ�
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
            p2=p1;//�������ָ��ָ�����һ���ѿ�
        }
    printf("�����������û������˺š�������������#��ʾ�������\n");
    printf("����ʾ�������� 1 111111 �û�\n");
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
        printf("������ͨ�����û���Ϣ:\n");
        printuser(student_head);
        save(student_head);
}

void deleteuser(student_pointer student_head)//ɾ�������˺�
{
    printf("�������ɾ���Ķ����û������˺���Ϣ\n");
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
                    printf("��ɾ���Ķ�����ϢΪ��\n");
                    printf("%s %s %s %s\n",p1->name,p1->id,p1->password,p1->type);
                    p2->next=p1->next;
                    flag=1;
                    free(p1);
                    printf("������Ϣ��ɾ��\n");
                }
        }

    }
    if(flag==0)
    {

        printf("���޶�����Ϣ���޷�ɾ��\n");

    }
    save(student_head);
}

void print(student_pointer student_head)//��ʾ���ж�����Ϣ
{
    do{
    printf("************************************\n");
    printf("*        1:�������Ա�˺�            *\n");
    printf("*        2:����û��˺�              *\n");
    printf("*        3:����                    *\n");
    printf("************************************\n\n");
    printf("��������Ҫ���е���Ŀѡ��\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            printadmin(student_head);//�������Ա��Ϣ
            break;
        case 2:
            printuser(student_head);//����û���Ϣ
            break;
        case 3:
            printf("\n\n");
            break;
        default:
            printf("����ѡ����ڣ�\n");
            break;
    }}while(select!=3);
}

void printadmin(student_pointer student_head)//�������Ա��Ϣ
{
    student_pointer p=student_head->next;
    int i=0;
    while(p)
    {
        if(strcmp(p->type,"����Ա")==0)
        {
            printf("%s %s %s\n",p->name,p->id,p->password);
            i++;
        }
        p=p->next;
    }
    if(i==0)
        printf("û�й���Ա��Ϣ��");
}
void printuser(student_pointer student_head)//����û���Ϣ
{
    student_pointer p=student_head->next;
    int i=0;
    while(p)
    {
        if(strcmp(p->type,"�û�")==0)
        {
            printf("%s %s %s\n",p->name,p->id,p->password);
            i++;
        }
        p=p->next;
    }
    if(i==0)
    {
        printf("û���û���Ϣ��");
    }
}

void change(student_pointer student_head)
{
    student_pointer p=student_head->next;
    char name[10];
    int flag=0;//�޸�״̬��ʶ��
    printf("������Ҫ����������û������˺ţ�\n");
    scanf("%s",&name);
    while(p)
    {
        if(strcmp(p->type,"�û�")==0)//����ֻ���޸��û�����
        {
            if(strcmp(p->name,name)==0||strcmp(p->id,name)==0)
            {
                printf("�������������룺\n");
                scanf("%s",p->password);
                printf("�������û����룡\n");
                flag=1;
            }
        }
       p=p->next;
    }
    if(flag==0)
    {
        printf("δ�ҵ���Ӧ���û������˺ţ�\n");
    }
    printf("��ǰ������ϢΪ��\n");
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

void book_management_system(book_pointer book_head)//ͼ����Ϣ������
{
      do{
      printf("**********************************************\n");
	  printf("*         ��ӭ����ͼ�����Ա����             *\n");
	  printf("*         1�������ϼ�                        *\n");
	  printf("*         2�����ͼ����Ϣ                    *\n");
	  printf("*         3����ѯ                            *\n");
	  printf("*         4�������¼�                        *\n");
	  printf("*         5���޸�ͼ����Ϣ                    *\n");
	  printf("*         6���˳�                            *\n");
	  printf("**********************************************\n");

	  printf("     ���������ѡ��\n");
      scanf("%d",&select);

    switch(select)
    {
        case 1:newbook(book_head);//�����ϼ�
		       break;
	    case 2:Output(book_head);//ͼ�����
		       break;
	    case 3:search(book_head);//ͼ�����
		       break;
	    case 4:oldbook(book_head);//�����¼�
		       break;
	    case 5:modify(book_head);//�޸�ͼ����Ϣ
		       break;
        case 6:printf("\n\n");
                break;
        default:
            printf("ѡ�����!\n");
    }}while(select!=6);
}

void newbook(book_pointer book_head)//���ͼ����Ϣ
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

	printf("����������ͼ���š����������ߡ������硢��𡢳��������ա��۸񡢿��,����-1��ʾ�������\n");
    printf("����ʾ����201501 ���μ� ��ж� �л�  ���� 19580624 56 59\n");
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
   printf("���ڵ�ͼ����ϢΪ��\n");
   Output(book_head);
}

void Save(book_pointer book_head)//��ͼ�����Ϣ�����ļ���
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

void Output(book_pointer book_head)//���ͼ����Ϣ
{
   book_pointer p=book_head->next;

   if(p==NULL)
   {
	   printf("û��ͼ����Ϣ\n");
   }
   else
   {
       printf("���      ����    ����     ������   ��� ���������� �۸�   ���\n");
	   while(p)
	   {
         printf("%d%8s%10s%8s%8s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
         p=p->next;
	   }
   }
}

void search(book_pointer book_head)//��ѯͼ����Ϣ
{
    do{
    printf("***********************************\n");
    printf("*         1:����������            *\n");
    printf("*         2:����������            *\n");
    printf("*         3:����                  *\n");
    printf("***********************************\n\n");
    printf("     ��������Ҫ���е���Ŀѡ��\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            titlesearch(book_head);//��������
            break;
        case 2:
            authorsearch(book_head);//����������
            break;
        case 3:
            printf("\n\n");
            break;
        default:printf("ѡ�����\n");
    }}while(select!=3);
}

void titlesearch(book_pointer book_head)//��������
{
    book_pointer p=book_head->next;
	char name[20];
	int flag=0;//��ѯ״̬��

    printf("������Ҫ��ѯ��������\n");
	scanf("%s",name);
    while(p)
	{
		if(strstr(p->name,name)!=NULL||strstr(name,p->name)!=NULL)//ģ��ƥ��
		{
			printf("%d%8s%10s%8s%10s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
		    flag=1;
		}
		  p=p->next;
	}
	if(flag==0)
	 printf("������Ϣ������\n");
}

void authorsearch(book_pointer book_head)//����������
{
	book_pointer p=book_head->next;
	char author[20];
	int flag=0;

    printf("������Ҫ��ѯ���������֣�\n");
	scanf("%s",author);
    while(p)
	{
		if(strstr(p->author,author)!=NULL||strstr(author,p->author)!=NULL)//ģ��ƥ��
		{
			printf("%d%8s%10s%8s%10s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
		    flag=1;
		}
		  p=p->next;
	}
	if(flag==0)
	printf("������Ϣ������\n");
}

void oldbook(book_pointer book_head)//�����¼�
{
    do{
    printf("************************************\n");
    printf("*         1:������ɾ��             *\n");
    printf("*         2:�����ɾ��             *\n");
    printf("*         3���˳�                  *\n");
    printf("************************************\n\n");
    printf("      ��������Ҫ���е���Ŀѡ��\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            titledelete(book_head);//������ɾ��
            break;
        case 2:
            iddelete(book_head);//�����ɾ��
            break;
        case 3:
            printf("\n\n");
            break;
        default:
            printf("ѡ�����!\n");
    }}while(select!=3);
}

void titledelete(book_pointer book_head)//������ɾ��
{
    book_pointer p1=book_head,p2;
    char name[10];
	int  flag=0;//ɾ��״̬��

	printf("������Ҫɾ��ͼ���������\n");
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
                printf("�鼮��Ϣ��ɾ��\n");
            }
        }
	}
	if(flag==0)
	{
		printf("��ͼ����Ϣ������\n");
	}
	if(flag==1)
	{
	  printf("ɾ�����ͼ����ϢΪ:\n");
	  Output(book_head);
	  Save(book_head);
	}
}

void iddelete(book_pointer book_head)//�����ɾ���鼮
{
    book_pointer p1=book_head,p2=book_head->next;
    int id,flag=0;

	printf("������Ҫɾ��ͼ��ı�ţ�\n");
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
                printf("�鼮��Ϣ��ɾ��\n");
            }            
        }
	}
	if(flag==0)
	{
		printf("����������ͼ����Ϣ������\n");
	}
	if(flag==1)
	{
		printf("ɾ�����ͼ����ϢΪ:\n");
	    Output(book_head);
		Save(book_head);
	}
}

void modify(book_pointer book_head)//ͼ����Ϣ�޸�
{    
    char name[20],author[20],publisher[20],type[20];
    int  id,pubtime,price,Num;
    char sel;//�޸Ĳ���ѡ���
	int  flag=0;//�޸�״̬��
	book_pointer p;

	printf("������Ҫ�޸�ͼ��ı�ţ�\n");
	scanf("%d",&id);

	if(book_head==NULL)
	{
		printf("û��ͼ����Ϣ\n");
	}
	for(p=book_head;p!=NULL;p=p->next)//������ѯ���޸ĵ��鼮�Ķѿ�λ��
	{
		if(p->id==id)
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
		printf("ͼ����Ϣ������\n");
	if(flag==1)
	{
		printf("��ͼ�����Ϣ�Ѳ�ѯ������Ϣ���£�\n");
		printf("���      ����    ����     ������    ���    ����������   �۸�   ���\n");
	    printf("%d%8s%10s%8s%10s%10d%8d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
        getchar();
        //�޸�����
		printf("�Ƿ��޸������������� y or n:\n");
		scanf("%c",&sel);
		if(sel=='y')
		{
			printf("������������\n");
			scanf("%s",name);
			strcpy(p->name,name);;
		}
		//�޸�������
		printf("�Ƿ��޸��������������� y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("��������������\n");
			scanf("%s",author);
			strcpy(p->author,author);
		}
		//�޸ĳ�����
	    printf("�Ƿ��޸ĳ����磬������ y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("����������磺\n");
			scanf("%s",publisher);
			strcpy(p->publisher,publisher);
		}
		//�޸�ͼ������
	    printf("�Ƿ��޸�ͼ�����ͣ������� y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("������ͼ�����ͣ�\n");
			scanf("%s",type);
			strcpy(p->type,type);
		}
		//�޸ĳ���ʱ��
        printf("�Ƿ��޸ĳ���ʱ�䣬������ y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("���������ʱ�䣺\n");
			scanf("%d",&pubtime);
			p->pubtime=pubtime;
		}
		//�Ƿ��޸ļ۸�
		printf("�Ƿ��޸ļ۸������� y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("������۸�\n");
			scanf("%d",&price);
			p->price=price;
		}
		printf("�Ƿ��޸Ŀ�棬������ y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("�������棺\n");
			scanf("%d",&Num);
			p->Num=Num;
		}
		printf("�޸ĺ��ͼ����ϢΪ��\n");
        printf("���      ����    ����     ������    ���    ����������   �۸�   ���\n");
	    printf("%d%8s%10s%8s%10s%10d%8d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);

		Save(book_head);
	}
}

void reader(book_pointer book_head, student_pointer student_head)//��ͨ���ߺ���
{
    do{
    printf("************************************\n");
    printf("*          1:��������              *\n");
    printf("*          2:��ѯͼ����Ϣ          *\n");
    printf("*          3:�˳�                  *\n");
    printf("************************************\n\n");
    printf("   ��������Ҫ���е���Ŀѡ��\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            password(student_head);//���߸�������
            break;
        case 2:
            search(book_head);//��ѯͼ����Ϣ
            break;
        case 3:
            printf("\n\n");
            break;
        default:
            printf("ѡ�����\n");
    }}while(select!=3);
}

void password(student_pointer student_head)//���߸�������
{
    student_pointer p=student_head->next;
    int flag=0;//�����޸�״̬��
    char name[10], password[10];
    printf("�����������û������˺�\n");
    scanf("%s",name);
    int m=1;//����У��״̬��
    while(p)
	{
		if(strcmp(p->name,name)==0||strcmp(p->id,name)==0)//ģ��ƥ��
		{
		    while(m==1)//У��ԭ����
            {
                printf("��������ԭ��������\n");
                scanf("%s", password);
                if(strcmp(p->password, password)!=0)
                {
                    printf("����������������밴1�� �˳��밴2\n");
                    scanf("%d", &m);
                    continue;
                }
                if(strcmp(p->password, password)==0)//������ȷ���У��
                    break;
		    }
		    if(m==2)
                break;
			printf("����������������\n");
	        scanf("%s", password);
	        strcpy(p->password,password);
            printf("�����޸ĳɹ�\n");
	        save(student_head);
	        flag=1;
	        break;
		}
		p=p->next;
	}
	if(flag==0)
		printf("�˺���Ϣ������\n");
}
