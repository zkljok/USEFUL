#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#define LEN sizeof(struct student)		//����ṹ��ĳ���//

#define DATAOUT "%-10s%-20s%-20s%-15s%-25s%-20s%\n"		//�����涨������ĸ�ʽ//

#define DATA stu[i].name,stu[i].sex,stu[i].id,stu[i].tel,stu[i].email,stu[i].address		//����ṹ������Ԫ���еĸ�����Ա// 

//����ṹ���Ա//
struct student 
{
	char name[10];
	char id[20];
	char tel[15];
	char email[25];
	char address[30];
	char sex[35];
};

struct student stu[100];		//����ṹ������//

//����������Ҫ�õ��ĺ���//
void input  ();
void search ();
void search2 ();
void update ();
void deleted();
void display();
void sort   ();
void menu   ();

//�˵���ӡģ�� // 
void menu()		
{
	system("cls");		//����//
	printf("\n\n");		//���������ܲ˵����// 
	printf("\t\t\t\t\t============ѧ��ͨѶ¼����ϵͳ==============\n\n");
	printf("\t\t\t\t\t********************************************\n\n"); 
	printf("\t\t\t\t\t\t\t0. �˳�ϵͳ\t\t\t\n\n");
	printf("\t\t\t\t\t\t\t1. ��¼����\t\t\t\n\n");
	printf("\t\t\t\t\t\t\t2. �������ݣ�ѧ�ţ�\t\t\t\n\n");
	printf("\t\t\t\t\t\t\t3. �������ݣ�������\t\t\t\n\n");
	printf("\t\t\t\t\t\t\t4. �޸�����\t\t\t\n\n");
	printf("\t\t\t\t\t\t\t5. ɾ������\t\t\t\n\n");
	printf("\t\t\t\t\t\t\t6. ��������\t\t\t\n\n");
	printf("\t\t\t\t\t\t\t7. �鿴����\t\t\t\n\n");
	printf("\t\t\t\t\t********************************************\n\n");
	printf("\t\t\t\t\t============ѧ��ͨѶ¼����ϵͳ==============\n\n");
	printf("\t\t\t\t\t���������ѡ��(0-7):");
}

//����ģ�� // 
void input()
{
	int i,count=0;		//��¼ͨѶ¼����ϵ�˸����ı���//
	char ch[2];		//��¼�û�������//
	FILE *fp;		//����ָ���ļ���ָ�����//
	if((fp=fopen("D:\\data.txt","a+"))==NULL)		//����fopen��������һ���µ��ı���������ϵ����Ϣ//
	{
		printf("�����ļ�ʧ��!\n");
		return;
	}
	while (!feof(fp))		//�ж��ļ��Ƿ����//
	{
		if (fread(&stu[count], LEN, 1, fp)==1)		//ʹ��fread�������ļ��еļ�¼������ȡ���ṹ������//
			count++;
	}
	fclose(fp);		//�ر��ļ�//
	if (count==0)		//�жϵ�ǰͨѶ¼�Ƿ�Ϊ��//
		printf("ͨѶ¼Ϊ��!\n");
	else
	{
		display();		//��ʾ��ϵ�˵�������Ϣ//
	}
	if ((fp=fopen("D:\\data.txt", "wb"))==NULL)		//������ļ�ʧ��//
	{
		printf("�޷����ļ�!\n");
		return;
	}
	//��������д�����//
	for (i = 0; i < count; i++)
		fwrite(&stu[i], LEN, 1, fp);
	printf("�Ƿ��������(y/n)��");		//��ʾ�û�����//
	scanf("%s",ch);
	while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)		//�ж��û��Ƿ���Ҫ����//
	{
		printf("ѧ��:");
		scanf("%s", &stu[count].id);
		//�ж��û�����ѧ����ͨѶ¼���Ƿ����//
		for(i=0;i<count;i++)
			if (strcmp(stu[i].id, stu[count].id) == 0)
			{
				printf("���û��Ѿ����ڣ�\n");
				fclose(fp);
				return;
			}
		printf("¼���ʽ������ �Ա� �绰 ���� ��ַ ����ͬ�����м�ʹ�ÿո�����\n");
		scanf("%s%s%s%s%s", &stu[count].name, &stu[count].sex, &stu[count].tel, &stu[count].email, &stu[count].address);
		if (fwrite(&stu[count], LEN, 1, fp) != 1)		//���½���ϵ����Ϣ���浽����//
		{
			printf("�޷���������!");
			getch();
		}
		else
		{
			printf("ѧ��Ϊ%s��ѧ����Ϣ����ɹ�!\n", stu[count].id);
			count++;
		}
		printf("�Ƿ��������?(y/n):");
		loop1:scanf("%s",ch);
	}
	if(strcmp(ch,"N") != 0 && strcmp(ch,"n") != 0)
		{
			printf("�����������������(y/n):");
			goto loop1;	
		}
	else 
		{
			printf("¼����ϵ����Ϣ��ɣ�����\n");
			fclose(fp);
			return ; 
		}
	fclose(fp);
	printf("¼����ϵ����Ϣ��ɣ�����\n");
}

//����ģ�飨ѧ�ţ�// 
void search()
{
	FILE *fp;
	int i, count = 0;
	char ch[2], id[20];		//������������û���������Ϣ//
	//�򿪴��̣����������е�ͨѶ¼������ȡ���ڴ�ṹ������//
	if ((fp = fopen("D:\\data.txt","rb")) == NULL)
	{
		printf("�޷����ļ���\n");
		return;
	}
	while (!feof(fp))		//�ж��Ƿ񵽴��ļ���β��//
		if (fread(&stu[count], LEN, 1, fp) == 1)
			count++;		//count��ֵΪͨѶ¼��Ŀ//
	fclose(fp);
	if (count == 0)
	{
		printf("ͨѶ¼Ϊ��!\n");
		return;
	}
	printf("������ѧ��ѧ��:");
	scanf("%s",id);
	//����ͨѶ¼ָ����Ϣ�������ַ��ȽϺ���//
	for(i=0;i<count;i++)
		if (strcmp(id, stu[i].id) == 0)
		{
			printf("������Ϣ����,�Ƿ���ʾ?(y/n):");
			scanf("%s", ch);
			if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
			{
				printf("����\t  �Ա�\t\t      ѧ��\t          �绰\t\t ����\t                  ��ַ\t\t\n");
				printf(DATAOUT,DATA);
			}
			break;
		}
	//�ж�ѭ����������Ϊû���ҵ���ϵ�˻�����Ϊ�ҵ��˵���û����ʾ��ϵ����Ϣ//
	if (i == count)
		printf("��ѯ��������ϵ��!\n"); 
}



//����ģ�飨������//
void search2()
{
	FILE *fp;
	int i, count = 0;
	char ch[2], name[10];		//������������û���������Ϣ//
	//�򿪴��̣����������е�ͨѶ¼������ȡ���ڴ�ṹ������//
	if ((fp = fopen("D:\\data.txt","rb")) == NULL)
	{
		printf("�޷����ļ���\n");
		return;
	}
	while (!feof(fp))		//�ж��Ƿ񵽴��ļ���β��//
		if (fread(&stu[count], LEN, 1, fp) == 1)
			count++;		//count��ֵΪͨѶ¼��Ŀ//
	fclose(fp);
	if (count == 0)
	{
		printf("ͨѶ¼Ϊ��!\n");
		return;
	}
	printf("������ѧ������:");
	scanf("%s",name);
	//����ͨѶ¼ָ����Ϣ�������ַ��ȽϺ���//
	for(i=0;i<count;i++)
		if (strcmp(name, stu[i].name) == 0)
		{
			printf("������Ϣ����,�Ƿ���ʾ?(y/n):");
			scanf("%s", ch);
			if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
			{
				printf("����\t  �Ա�\t\t      ѧ��\t          �绰\t\t ����\t                  ��ַ\t\t\n");
				printf(DATAOUT,DATA);
			}
			break;
		}
	//�ж�ѭ����������Ϊû���ҵ���ϵ�˻�����Ϊ�ҵ��˵���û����ʾ��ϵ����Ϣ//
	if (i == count)
		printf("��ѯ��������ϵ��!\n"); 
}

//�޸�ģ�� 
void update()
{
	FILE* fp;
	int i, j, count = 0;
	char id[20];
	if ((fp = fopen("D:\\data.txt", "r+")) == NULL)
	{
		printf("�޷���!\n");
		return;
	}
	while (!feof(fp))
		if (fread(&stu[count], LEN, 1, fp) == 1)
			count++;
	if (count == 0)
	{
		printf("ͨѶ¼Ϊ��!\n");
		fclose(fp);
		return;
	}
	display();
	//�޸���ϵ����Ϣ//
	printf("������Ҫ�޸���ϵ�˵�ѧ��!\n");
	printf("ѧ��:");
	scanf("%s", &id);
	for (i = 0; i < count; i++)
	{
		if (strcmp(id, stu[i].id) == 0)
		{
                printf("¼���ʽ������ �Ա� �绰 ���� ��ַ ����ͬ�����м�ʹ�ÿո�����\n");
		     scanf("%s%s%s%s%s", &stu[count].name, &stu[count].name, &stu[count].tel, &stu[count].email, &stu[count].address);
			printf("�޸ĳɹ�!");
			//�򿪴��̣����޸ĺ����ϵ����Ϣд�����//
			if ((fp = fopen("D:\\data.txt", "wb")) == NULL)
			{
				printf("�޷����ļ�!\n");
				return;
			}
			for (j = 0; j < count; j++)
				if (fwrite(&stu[j], LEN, 1, fp) != 1)
				{
					printf("����ʧ��!");
					getch();
				}
			fclose(fp);
			return;
		}
	}
	printf("����ϵ�˲�����!\n");		//û���ҵ�������ϵ����Ϣ//
}

//ɾ��ģ�� 
void deleted()
{
	FILE* fp;
	int i, j, count = 0;
	char ch[2];
	char id[15];
	if ((fp = fopen("D:\\data.txt", "r+")) == NULL)
	{
		printf("�޷����ļ�!\n");
		return;
	}
	while (!feof(fp))
		if (fread(&stu[count], LEN, 1, fp) == 1)
			count++;
	fclose(fp);
	if (count == 0)
	{
		printf("ͨѶ¼Ϊ��!\n");
		return;
	}
	display();
	//ɾ����ϵ����Ϣ//
	printf("������Ҫɾ����ϵ�˵�ѧ��:");
	scanf("%s",id);
	for (i = 0; i < count; i++)
	{
		if (strcmp(id, stu[i].id) == 0)
		{
			printf("����ϵ�˵������Ϣ���£�\n"); 
			printf("����\t  �Ա�\t\t      ѧ��\t          �绰\t\t ����\t                  ��ַ\t\t\n");
			printf(DATAOUT, DATA);
			printf("ȷ��Ҫɾ����?(y/n)");
			loop2:scanf("%s", ch);
			if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
			{
				for (j = i; j < count; j++)
					stu[j] = stu[j + 1];
				count--;
				printf("ɾ���ɹ�!\n");
			}
			else 
				if(strcmp(ch,"N") != 0 && strcmp(ch,"n") != 0)
					{
						printf("�����������������(y/n):");
						goto loop2;	
					}
				else printf("ȡ��ɾ����\n");
			//��ɾ�����ͨѶ¼д���Ӧ�Ĵ����ļ�//
			if ((fp = fopen("D:\\data.txt", "wb")) == NULL)
			{
				printf("�޷���!\n");
				return;
			}
			for(j=0;j<count;j++)
				if (fwrite(&stu[j], LEN, 1, fp) != 1)
				{
					printf("����ʧ��!\n");
					getch();
				}
			fclose(fp);
			return;
		}
	}
	printf("��ѯ��������ϵ��!\n");
}

//����ģ�� 
void sort()
{
	FILE* fp;
	struct student p;
	int i = 0, j = 0, count = 0;
	if ((fp = fopen("D:\\data.txt", "r+")) == NULL)
	{
		printf("�޷����ļ�!\n");
		return;
	}
	while (!feof(fp))
		if (fread(&stu[count], LEN, 1, fp) == 1)
			count++;
	fclose(fp);
	if (count == 0)
	{
		printf("ͨѶ¼Ϊ��!\n");
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
		printf("�޷����ļ�!\n");
		return;
	}
	for(i=0;i<count;i++)
		if(fwrite(&stu[i],LEN,1,fp)!=1)
		{
			printf("����ʧ��!\n");
			getch();
		}
	fclose(fp);
	printf("����ɹ�!\n");
}

//��ʾģ�� 
void display()
{
	FILE* fp;
	int i, count = 0;
	fp = fopen("D:\\data.txt", "rb");		//��ֻ���ķ�ʽ���ļ�//
	//��ȡ�ļ�ͨѶ¼//
	while (!feof(fp))
	{
		if (fread(&stu[count], LEN, 1, fp) == 1)
			count++;
	}
	fclose(fp);		//�ر��ļ�//
	system("cls");
	printf("����Ϊȫ����ϵ�˵���Ϣ��\n");
	printf("\n");
	printf("����\t  �Ա�\t\t      ѧ��\t          �绰\t\t ����\t                  ��ַ\t\t\n");
	for (i = 0; i < count; i++)
		printf(DATAOUT, DATA);
}

//������//
int main()
{
	printf("\n\n\n\n\n\n\n"); 
	printf("\t\t\t\t==============================================\n\n");
	printf("\t\t\t\t**********************************************\n\n"); 
	printf("\t\t\t\t**********��ӭʹ��ѧ��ͨѶ¼����ϵͳ**********\n\n"); 
	printf("\t\t\t\t*************�ڴ����и��õ����� !!************\n\n"); 
	printf("\t\t\t\t**********************************************\n\n");
	printf("\t\t\t\t==============================================\n\n");
	printf("\t\t\t\t\t     ��������������˵�\n"); 
	getch(); 
	int n;
	menu();		//�������˵�//
	while (1)		//ѡ����Ӧ�Ĺ���//
	{
		loop:scanf("%d",&n);		//�û�ѡ����//
		switch (n)
		{
		case 0:
			printf("\n\t\t\t\t\t\t    ***��ӭ�´�ʹ��***\t\t\t\n");
			printf("\t\t\t\t\t=============================================\n");
			exit(0); 
			break;
		case 1: input();		//����ģ��// 
			break;		
		case 2: search();		//����ģ�飨ѧ�ţ�//
			break;
		case 3: search2();		//����ģ��(����)//
			break;
		case 4: update();		//�޸�ģ��//
			break;
		case 5: deleted();		//ɾ��ģ��//
			break;
		case 6: sort();			//����ģ��//
			break;
		case 7: display();		//��ʾģ��//
		default:printf("����������������������(0~7):\n");		//�������� 
				goto loop; 
			break;
		}
		system("pause");				
		menu();		//�ٴε������˵�//
	}
	
	return 0;
}

