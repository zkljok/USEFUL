#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#define LEN sizeof(struct student)		//定义结构体的长度//

#define DATAOUT "%-10s%-20s%-20s%-15s%-25s%-20s%\n"		//这个宏规定了输出的格式//

#define DATA stu[i].name,stu[i].sex,stu[i].id,stu[i].tel,stu[i].email,stu[i].address		//代表结构体数组元素中的各个成员// 

//定义结构体成员//
struct student 
{
	char name[10];
	char id[20];
	char tel[15];
	char email[25];
	char address[30];
	char sex[35];
};

struct student stu[100];		//定义结构体数组//

//声明程序中要用到的函数//
void input  ();
void search ();
void search2 ();
void update ();
void deleted();
void display();
void sort   ();
void menu   ();

//菜单打印模块 // 
void menu()		
{
	system("cls");		//清屏//
	printf("\n\n");		//控制主功能菜单设计// 
	printf("\t\t\t\t\t============学生通讯录管理系统==============\n\n");
	printf("\t\t\t\t\t********************************************\n\n"); 
	printf("\t\t\t\t\t\t\t0. 退出系统\t\t\t\n\n");
	printf("\t\t\t\t\t\t\t1. 记录数据\t\t\t\n\n");
	printf("\t\t\t\t\t\t\t2. 查找数据（学号）\t\t\t\n\n");
	printf("\t\t\t\t\t\t\t3. 查找数据（姓名）\t\t\t\n\n");
	printf("\t\t\t\t\t\t\t4. 修改数据\t\t\t\n\n");
	printf("\t\t\t\t\t\t\t5. 删除数据\t\t\t\n\n");
	printf("\t\t\t\t\t\t\t6. 数据排序\t\t\t\n\n");
	printf("\t\t\t\t\t\t\t7. 查看数据\t\t\t\n\n");
	printf("\t\t\t\t\t********************************************\n\n");
	printf("\t\t\t\t\t============学生通讯录管理系统==============\n\n");
	printf("\t\t\t\t\t请输入你的选择(0-7):");
}

//输入模块 // 
void input()
{
	int i,count=0;		//记录通讯录中联系人个数的变量//
	char ch[2];		//记录用户的输入//
	FILE *fp;		//定义指向文件的指针变量//
	if((fp=fopen("D:\\data.txt","a+"))==NULL)		//调用fopen函数创建一个新的文本来保存联系人信息//
	{
		printf("创建文件失败!\n");
		return;
	}
	while (!feof(fp))		//判断文件是否结束//
	{
		if (fread(&stu[count], LEN, 1, fp)==1)		//使用fread函数将文件中的记录逐条读取到结构体数组//
			count++;
	}
	fclose(fp);		//关闭文件//
	if (count==0)		//判断当前通讯录是否为空//
		printf("通讯录为空!\n");
	else
	{
		display();		//显示联系人的所有信息//
	}
	if ((fp=fopen("D:\\data.txt", "wb"))==NULL)		//如果打开文件失败//
	{
		printf("无法打开文件!\n");
		return;
	}
	//将数据重写入磁盘//
	for (i = 0; i < count; i++)
		fwrite(&stu[i], LEN, 1, fp);
	printf("是否继续输入(y/n)：");		//提示用户输入//
	scanf("%s",ch);
	while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)		//判断用户是否需要输入//
	{
		printf("学号:");
		scanf("%s", &stu[count].id);
		//判断用户输入学号在通讯录中是否存在//
		for(i=0;i<count;i++)
			if (strcmp(stu[i].id, stu[count].id) == 0)
			{
				printf("该用户已经存在！\n");
				fclose(fp);
				return;
			}
		printf("录入格式：姓名 性别 电话 邮箱 地址 （不同数据中间使用空格间隔）\n");
		scanf("%s%s%s%s%s", &stu[count].name, &stu[count].sex, &stu[count].tel, &stu[count].email, &stu[count].address);
		if (fwrite(&stu[count], LEN, 1, fp) != 1)		//将新建联系人信息保存到磁盘//
		{
			printf("无法保存数据!");
			getch();
		}
		else
		{
			printf("学号为%s的学生信息保存成功!\n", stu[count].id);
			count++;
		}
		printf("是否继续输入?(y/n):");
		loop1:scanf("%s",ch);
	}
	if(strcmp(ch,"N") != 0 && strcmp(ch,"n") != 0)
		{
			printf("输入错误，请重新输入(y/n):");
			goto loop1;	
		}
	else 
		{
			printf("录入联系人信息完成！！！\n");
			fclose(fp);
			return ; 
		}
	fclose(fp);
	printf("录入联系人信息完成！！！\n");
}

//查找模块（学号）// 
void search()
{
	FILE *fp;
	int i, count = 0;
	char ch[2], id[20];		//定义数组接收用户的输入信息//
	//打开磁盘，并将磁盘中的通讯录逐条读取到内存结构体数组//
	if ((fp = fopen("D:\\data.txt","rb")) == NULL)
	{
		printf("无法打开文件！\n");
		return;
	}
	while (!feof(fp))		//判断是否到达文件的尾部//
		if (fread(&stu[count], LEN, 1, fp) == 1)
			count++;		//count终值为通讯录条目//
	fclose(fp);
	if (count == 0)
	{
		printf("通讯录为空!\n");
		return;
	}
	printf("请输入学生学号:");
	scanf("%s",id);
	//查找通讯录指定信息，运用字符比较函数//
	for(i=0;i<count;i++)
		if (strcmp(id, stu[i].id) == 0)
		{
			printf("此人信息存在,是否显示?(y/n):");
			scanf("%s", ch);
			if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
			{
				printf("姓名\t  性别\t\t      学号\t          电话\t\t 邮箱\t                  地址\t\t\n");
				printf(DATAOUT,DATA);
			}
			break;
		}
	//判断循环结束是因为没有找到联系人还是因为找到了但是没有显示联系人信息//
	if (i == count)
		printf("查询不到该联系人!\n"); 
}



//查找模块（姓名）//
void search2()
{
	FILE *fp;
	int i, count = 0;
	char ch[2], name[10];		//定义数组接收用户的输入信息//
	//打开磁盘，并将磁盘中的通讯录逐条读取到内存结构体数组//
	if ((fp = fopen("D:\\data.txt","rb")) == NULL)
	{
		printf("无法打开文件！\n");
		return;
	}
	while (!feof(fp))		//判断是否到达文件的尾部//
		if (fread(&stu[count], LEN, 1, fp) == 1)
			count++;		//count终值为通讯录条目//
	fclose(fp);
	if (count == 0)
	{
		printf("通讯录为空!\n");
		return;
	}
	printf("请输入学生姓名:");
	scanf("%s",name);
	//查找通讯录指定信息，运用字符比较函数//
	for(i=0;i<count;i++)
		if (strcmp(name, stu[i].name) == 0)
		{
			printf("此人信息存在,是否显示?(y/n):");
			scanf("%s", ch);
			if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
			{
				printf("姓名\t  性别\t\t      学号\t          电话\t\t 邮箱\t                  地址\t\t\n");
				printf(DATAOUT,DATA);
			}
			break;
		}
	//判断循环结束是因为没有找到联系人还是因为找到了但是没有显示联系人信息//
	if (i == count)
		printf("查询不到该联系人!\n"); 
}

//修改模块 
void update()
{
	FILE* fp;
	int i, j, count = 0;
	char id[20];
	if ((fp = fopen("D:\\data.txt", "r+")) == NULL)
	{
		printf("无法打开!\n");
		return;
	}
	while (!feof(fp))
		if (fread(&stu[count], LEN, 1, fp) == 1)
			count++;
	if (count == 0)
	{
		printf("通讯录为空!\n");
		fclose(fp);
		return;
	}
	display();
	//修改联系人信息//
	printf("请输入要修改联系人的学号!\n");
	printf("学号:");
	scanf("%s", &id);
	for (i = 0; i < count; i++)
	{
		if (strcmp(id, stu[i].id) == 0)
		{
                printf("录入格式：姓名 性别 电话 邮箱 地址 （不同数据中间使用空格间隔）\n");
		     scanf("%s%s%s%s%s", &stu[count].name, &stu[count].name, &stu[count].tel, &stu[count].email, &stu[count].address);
			printf("修改成功!");
			//打开磁盘，将修改后的联系人信息写入磁盘//
			if ((fp = fopen("D:\\data.txt", "wb")) == NULL)
			{
				printf("无法打开文件!\n");
				return;
			}
			for (j = 0; j < count; j++)
				if (fwrite(&stu[j], LEN, 1, fp) != 1)
				{
					printf("保存失败!");
					getch();
				}
			fclose(fp);
			return;
		}
	}
	printf("该联系人不存在!\n");		//没有找到该条联系人信息//
}

//删除模块 
void deleted()
{
	FILE* fp;
	int i, j, count = 0;
	char ch[2];
	char id[15];
	if ((fp = fopen("D:\\data.txt", "r+")) == NULL)
	{
		printf("无法打开文件!\n");
		return;
	}
	while (!feof(fp))
		if (fread(&stu[count], LEN, 1, fp) == 1)
			count++;
	fclose(fp);
	if (count == 0)
	{
		printf("通讯录为空!\n");
		return;
	}
	display();
	//删除联系人信息//
	printf("请输入要删除联系人的学号:");
	scanf("%s",id);
	for (i = 0; i < count; i++)
	{
		if (strcmp(id, stu[i].id) == 0)
		{
			printf("该联系人的身份信息如下：\n"); 
			printf("姓名\t  性别\t\t      学号\t          电话\t\t 邮箱\t                  地址\t\t\n");
			printf(DATAOUT, DATA);
			printf("确定要删除吗?(y/n)");
			loop2:scanf("%s", ch);
			if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
			{
				for (j = i; j < count; j++)
					stu[j] = stu[j + 1];
				count--;
				printf("删除成功!\n");
			}
			else 
				if(strcmp(ch,"N") != 0 && strcmp(ch,"n") != 0)
					{
						printf("输入错误，请重新输入(y/n):");
						goto loop2;	
					}
				else printf("取消删除！\n");
			//将删除后的通讯录写入对应的磁盘文件//
			if ((fp = fopen("D:\\data.txt", "wb")) == NULL)
			{
				printf("无法打开!\n");
				return;
			}
			for(j=0;j<count;j++)
				if (fwrite(&stu[j], LEN, 1, fp) != 1)
				{
					printf("保存失败!\n");
					getch();
				}
			fclose(fp);
			return;
		}
	}
	printf("查询不到该联系人!\n");
}

//排序模块 
void sort()
{
	FILE* fp;
	struct student p;
	int i = 0, j = 0, count = 0;
	if ((fp = fopen("D:\\data.txt", "r+")) == NULL)
	{
		printf("无法打开文件!\n");
		return;
	}
	while (!feof(fp))
		if (fread(&stu[count], LEN, 1, fp) == 1)
			count++;
	fclose(fp);
	if (count == 0)
	{
		printf("通讯录为空!\n");
		return;
	}
	for(i=0;i<count-1;i++)
		for(j=i+1;j<count;j++)
			if (strcmp(stu[i].id, stu[j].id) > 0)
			{
				p = stu[i];
				stu[i] = stu[j];
				stu[j] = p;
			}
	if ((fp = fopen("D:\\data.txt", "wb")) == NULL)
	{
		printf("无法打开文件!\n");
		return;
	}
	for(i=0;i<count;i++)
		if(fwrite(&stu[i],LEN,1,fp)!=1)
		{
			printf("保存失败!\n");
			getch();
		}
	fclose(fp);
	printf("排序成功!\n");
}

//显示模块 
void display()
{
	FILE* fp;
	int i, count = 0;
	fp = fopen("D:\\data.txt", "rb");		//以只读的方式打开文件//
	//读取文件通讯录//
	while (!feof(fp))
	{
		if (fread(&stu[count], LEN, 1, fp) == 1)
			count++;
	}
	fclose(fp);		//关闭文件//
	system("cls");
	printf("以下为全部联系人的信息：\n");
	printf("\n");
	printf("姓名\t  性别\t\t      学号\t          电话\t\t 邮箱\t                  地址\t\t\n");
	for (i = 0; i < count; i++)
		printf(DATAOUT, DATA);
}

//主函数//
int main()
{
	printf("\n\n\n\n\n\n\n"); 
	printf("\t\t\t\t==============================================\n\n");
	printf("\t\t\t\t**********************************************\n\n"); 
	printf("\t\t\t\t**********欢迎使用学生通讯录管理系统**********\n\n"); 
	printf("\t\t\t\t*************期待你有个好的体验 !!************\n\n"); 
	printf("\t\t\t\t**********************************************\n\n");
	printf("\t\t\t\t==============================================\n\n");
	printf("\t\t\t\t\t     按任意键进入主菜单\n"); 
	getch(); 
	int n;
	menu();		//调用主菜单//
	while (1)		//选择相应的功能//
	{
		loop:scanf("%d",&n);		//用户选择功能//
		switch (n)
		{
		case 0:
			printf("\n\t\t\t\t\t\t    ***欢迎下次使用***\t\t\t\n");
			printf("\t\t\t\t\t=============================================\n");
			exit(0); 
			break;
		case 1: input();		//输入模块// 
			break;		
		case 2: search();		//查找模块（学号）//
			break;
		case 3: search2();		//查找模块(姓名)//
			break;
		case 4: update();		//修改模块//
			break;
		case 5: deleted();		//删除模块//
			break;
		case 6: sort();			//排序模块//
			break;
		case 7: display();		//显示模块//
		default:printf("您的输入有误，请重新输入(0~7):\n");		//重新输入 
				goto loop; 
			break;
		}
		system("pause");				
		menu();		//再次调用主菜单//
	}
	
	return 0;
}

