#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int choice, count = 0, count3 = 0, v, e = 0, p1, s1 = 0, s2 = 0, s3 = 0;  //count:节点数， count1: 是否输出排名 e: 成绩库输出\n p:标记choice
char s[20][20], w[20], up[10] = "0", down[10] = "1", down1[20];                 //s:存放文件地址， w:临时用
struct student
{
	char name[20];
	char num[10];
	char banji[20];
	char score1[5];
	char score2[5];
	char score3[5];
	char mima[50];
	char state[50];
	int rank;
	int rank1;
	int rank2;
	int rank3;
	int total;
	struct student *next;

};


struct student *ptemp, *phead, *p, *ppre, *pend, *pnew, *phead1;
char pbanji[20], pxuehao[20], pmima[20], pstate[20], pname[20];


Read1()                            //从文件读到链表(学生信息)
{
	int i;
	char ch;
	FILE *fp;
	fp = fopen(s[choice], "r");
	count = 0;

	if (fp == NULL) {
		printf("error\n");
		getch();
	} else {
		phead = pend = (struct student*)malloc(sizeof(struct student));
    	while (!feof(fp)) {
			pnew = (struct student*)malloc(sizeof(struct student));
			fscanf(fp, "%s", pnew->name);
			fgetc(fp);
	    	fscanf(fp, "%s", pnew->num);
    		fgetc(fp);
	    	fscanf(fp, "%s", pnew->banji);
			fgetc(fp);
	    	fscanf(fp, "%s", pnew->score1);
			fgetc(fp);
	    	fscanf(fp, "%s", pnew->score2);
			fgetc(fp);
	    	fscanf(fp, "%s", pnew->score3);
			fgetc(fp);
			count++;
			pnew->next = NULL;
			pend->next = pnew;
			pend = pnew;
		}
	}
	fclose(fp);
	return phead;
}

Read2()                                    //读登录信息
{
	char ch;
	FILE *fp;
	fp = fopen("d:\\password.txt", "r");
	if (fp == NULL) {
		printf("error\n");
		getch();
	} else {
		phead = pend = ptemp = (struct student*)malloc(sizeof(struct student));
		while (1) {
			pnew = (struct student*)malloc(sizeof(struct student));
	    	fscanf(fp, "%s", pnew->num);
			fgetc(fp);
	    	fscanf(fp, "%s", pnew->mima);
    		fgetc(fp);
	    	fscanf(fp, "%s", pnew->state);
    		fgetc(fp);
	    	fscanf(fp, "%s", pnew->banji);
			ch = fgetc(fp);
			pnew->next = NULL;
			pend->next = pnew;
			pend = pnew;
			if (ch == EOF) {
				break;
			}
		}
	}
	fclose(fp);
	ptemp = phead->next;
	return;
}

Read3()                                     //读待办信息
{
	char ch;
	FILE *fp;
	fp = fopen(s[choice], "r");
	if (fp == NULL) {
		printf("error\n");
		getch();
	} else {
		phead = pend = (struct student*)malloc(sizeof(struct student));
		while (!feof(fp)) {
			pnew = (struct student*)malloc(sizeof(struct student));
			fscanf(fp, "%s", pnew->num); 
			fgetc(fp);
	    	fscanf(fp, "%s", pnew->mima);
    		fgetc(fp);
	    	fscanf(fp, "%s", pnew->state);
    		fgetc(fp);
	    	fscanf(fp, "%s", pnew->banji);
			fgetc(fp);
			pnew->next = NULL;
			pend->next = pnew;
			pend = pnew;
		}
	}
	fclose(fp);
	return;
}

Search1()                //密码进入的查找
{

	FILE *fp;
	fp = fopen("d:\\password.txt", "r");
	Read2();
	ptemp = (struct student*)malloc(sizeof(struct student));
	ptemp = phead->next;
	while (ptemp != NULL) {
		if ((strcmp(pxuehao, ptemp->num) == 0) && (strcmp(pmima, ptemp->mima) == 0)){
		    strcpy(pbanji,  ptemp->banji);
			return 1;
		}
		ptemp = ptemp->next;
	}
	return 0;
}

Search2()                       //个人信息的查找
{
	char t[20];
	Read1();
	ptemp = (struct student*)malloc(sizeof(struct student));
	ptemp = phead->next;
	while (1) {
	   	if ((strcmp(ptemp->num, pxuehao) == 0) || (strcmp(ptemp->name, pname) == 0)){
		   	printf("\t\t\t您所查找的信息如下\n\t\t\t\n");
			printf("\t\t\t---------------------------\n");
			printf("\t\t\t姓名   score1 score2 score3\n\n\t\t\t");
		   	printf("%s %s     %s    %s\n", ptemp->name, ptemp->score1, ptemp->score2, ptemp->score3);
			printf("\t\t\t---------------------------\n");
           	strcpy(pxuehao, w);
			return 1;
		}
    	ptemp = ptemp->next;
		if (ptemp == NULL) {
			if (v == 0) {
				printf("\n\t\t你所查找的学生不在本班级， 是否要访问成绩库\n\n");
				printf("\t\t1.访问成绩库\n");
				printf("\t\t2.退出\n\n");
				while (1) {
					scanf("%s", t);
					if (T(t) == 1) {
						v = 1;
						p1 = choice;
						choice = 6;
						if (Search2() == 1) {
					    	strcpy(pxuehao, w);
					    	choice = p1;
					    	return;
						} else {
							printf("\n\t\t您所找的学生不存在\n");
				    		strcpy(pxuehao, w);
					    	choice = p1;
							return;
						}
					}
					if (T(t) == 2) {
						strcpy(pxuehao, w);
						return;
					} else {
			 			printf("\n\t\t输入有误，请重新输入\n");
					}
				}
			} else {
				return 0;
			}
		}

	}	

}

Register()                              //注册
{
	FILE *fp;
	int i, c = 0;
	char num[10], banji[20], mima1[20], mima2[20], a[20], p[20];

	fp = fopen("d:\\注册申请.txt", "a");
	while (1) {
    	printf("\n\t\t请输入学号\t");
		scanf("%s", num);
		choice = 12;
		Read2();
		while (ptemp != NULL) {
			if (strcmp(ptemp->num, num) == 0) {
				printf("\n\t\t! 该账号已被注册,请重新输入\n");
				c = 1;
				break;
			}
			ptemp = ptemp->next;
		}
		if (c == 1) {
			c = 0;
			continue;
		}
		printf("\n\t\t请输入密码\t");
		for (i = 0; ; i++) {
			mima1[i] = getch();
			if (((int)mima1[i] == 10) || ((int)mima1[i] == 32) || ((int)mima1[i] == 13)) {
				mima1[i] = '\0';
				break;
			}
			if ((int)mima1[i] == 8) {
				i = i - 2;
				printf("\b \b");
			} else {
            	 printf("*");
			}
		}
    	printf("\n\t\t确认密码\t");
		for (i = 0; ; i++) {
			mima2[i] = getch();
			if (((int)mima2[i] == 10) || ((int)mima2[i] == 32) || ((int)mima2[i] == 13)) {
				mima2[i] = '\0';
				printf("\n");
				break;
			}
			if ((int)mima2[i] == 8) {
				i = i - 2;
				printf("\b \b");
			} else {
            	 printf("*");
			}
		}	
		if (strcmp(mima1, mima2) != 0) {
			printf("\t\t两次输入不同，按enter键重新输入\n");
			gets(a);
			system("cls");
			continue;
		} else {
			printf("\n\n\n\t\t请输入注册类型\n\n");
			printf("\t\t1.学生\n");
			printf("\t\t2.教师\n");
			printf("\t\t3.管理员\n\n\t\t");
			while (1) {
				scanf("%s", p);
				if (T(p) == 1) {
					choice = (int)num[1] - 48;
					if ((choice >= 1) && (choice <= 5)) {
						Read1();
						ptemp = (struct student*)malloc(sizeof(struct student));
						ptemp = phead->next;
						while (1) {
							if (strcmp(ptemp->num, num) == 0) {	
								fprintf(fp, "%s ", num);
								fprintf(fp, "%s ", mima1);
								fprintf(fp, "student ");
								fprintf(fp, "网络%d班\n", choice);
								fclose(fp);
								printf("\n\t\t< 已交由管理员审核 >");
								return ;
							}	
							ptemp = ptemp->next;
							
							if (ptemp == NULL) {
								printf("\t\t< 学号有误,按enter键后重新输入 >\n");
								gets(a);
								system("pause");
								system("cls");
								c = 1;
								break;
							}
						}
					} else {
						printf("\t\t< 学号有误,按enter键后重新输入 >\n");
						c = 1;
						gets(a);
						gets(a);
						system("pause");
						system("cls");
					}
					if (c == 1) {
						c = 0;
					    break;
					}
				}
				if (T(p) == 2) { 
					printf("请输入所带班级\n");
					scanf("%s", banji);
					fprintf(fp, "%s %s teacher %s\n", num, mima1, banji);
					printf("已交由管理员审核\n");
					fclose(fp);
					return;
				}
				if (T(p) == 3) {
					fprintf(fp, "%s %s charger all\n", num, mima1);
					printf("已交由管理员审核\n");
					fclose(fp);
					return;
				} else {
					printf("输入有误，请重新输入\n");
					continue;
				}
			}
		}
	}
}

Correct2()                          //密码修改
{	
	char xuehao[20], mima1[20], mima2[20], p[20];
	FILE *fp;
	fp = fopen("d:\\密码修改申请.txt", "a");
	Read2();
	ptemp = (struct student*)malloc(sizeof(struct student));
	while (1) {
		printf("\t\t请输入账号\t");
		scanf("%s", xuehao);
		printf("\n\t\t请输入原密码\t");
		scanf("%s", mima1);
		ptemp = phead->next;
    	while (ptemp != NULL) {
			if (strcmp(ptemp->num, xuehao) == 0) {
				if (strcmp(ptemp->mima, mima1) == 0) {
					printf("\n\t\t输入新密码\t");
					scanf("%s", mima2);
					fprintf(fp, "%s ", xuehao);
					fprintf(fp, "%s ", mima2);
					fprintf(fp, "%s ", ptemp->state);
					fprintf(fp, "%s\n", ptemp->banji);
					printf("\n\n< 已交由管理员处理 >\n");
		 			return;
				} else {
	    			printf("\n< 原密码错误 >\n\n");
					printf("请选择是否继续, 按1继续\n");
					scanf("%s", p);
					if (T(p) != 1) {
						return;
					} else {
						break;
					}
				}
			}
			ptemp = ptemp->next;
			if (ptemp == NULL) {
				printf("\n该学号未被注册\n");
				printf("\n请选择是否继续, 按1继续\n");
				scanf("%d", &p);
				if (p != 1) {
					return;
				} else {
					break;
				}
			}
		}
	}
}


Find()                                      //密码找回， 即换新密码
{
	char xuehao[20], mima2[20];
	FILE *fp;
	fp = fopen("d:\\密码找回申请.txt", "a");
	Read2();
	ptemp = (struct student*)malloc(sizeof(struct student));
	while (1) {
		printf("\t\t请输入要找回的学号\t");
		scanf("%s", xuehao);
    	ptemp = phead->next;
		while (ptemp != NULL) {
			if (strcmp(ptemp->num, xuehao) == 0) {
				printf("\n\t\t输入新密码\t");
				scanf("%s", mima2);
				fprintf(fp, "%s ", xuehao);
				fprintf(fp, "%s ", mima2);
				fprintf(fp, "%s ", ptemp->state);
				fprintf(fp, "%s\n", ptemp->banji);
				printf("\n\n\t\t< 已交由管理员处理 >\n");
				return;
			}
			ptemp = ptemp->next;
			if (ptemp == NULL) {
				printf("\n该学号未被注册\n\n");
				printf("请选择是否继续, 按1继续\n");
				scanf("%d", &p);
				if (p != 1) {
					return;
				} else {
					break;
				}
			}
		}
	}
}





	
			

Land()                                     //登录
{
	int i;
	while (1) {
		printf("\n\n\n\n");
    	printf("\t\t用户名");
		printf("\t\t\t");
    	scanf("%s", pxuehao);
    	printf("\n\t\t密码");
		printf("\t\t\t");
 		for (i = 0; ; i++) {
			pmima[i] = getch();
			if (((int)pmima[i] == 10) || ((int)pmima[i] == 32) || ((int)pmima[i] == 13)) {
				pmima[i] = '\0';
				break;
			}
			if ((int)pmima[i] == 8) {
				i = i - 2;
				printf("\b \b");
			} else {
            	 printf("*");
			}
		}
    	if (Search1() == 1) {
        	printf("\n\n\n\n\n登录成功!\n\n\n");
			system("pause");
			system("cls");
			if (strcmp(ptemp->banji, "网络1班") == 0) {
				choice = 1;
			}
			if (strcmp(ptemp->banji, "all") == 0) {
				choice = 6;
			}
			if (strcmp(ptemp->banji, "网络2班") == 0) {
				choice = 2;
			} 
			if (strcmp(ptemp->banji, "网络3班") == 0) {
				choice = 3;
			} 
			if (strcmp(ptemp->banji, "网络4班") == 0) {
				choice = 4;
			}
			if (strcmp(ptemp->banji, "网络5班") == 0) {
				choice = 5;
			}
			if (strcmp(ptemp->state, "student") == 0) {
				return 1;
			}
			if (strcmp(ptemp->state, "teacher") == 0) {
				return 2;
			}
			if (strcmp(ptemp->state, "charger") == 0) {
				return 3;
			}
		} else {
	    	printf("\n\n\n< 用户名或密码错误，请重新输入 >\n");
			system("pause");
			system("cls");
		}
	}
}
T(char a[])                         //变字符串为整数
{
	int i = strlen(a), sum = 0, j, g;
	for (j = i - 1, g = 1; j >= 0; j--, g = g * 10) {
		sum += ((int)a[j] - 48) * g;
	}
	return sum;
}


All()                       //按总成绩名次
{
	int i, j, t1, t2, t3;
	Read1();
	ppre = p = ptemp = pnew = phead1 = pend = (struct student*)malloc(sizeof(struct student));              //pnew phead1是新链表成绩区间
	ptemp = phead->next;
	for (i = 1; i < count; i++) {                                                  //score1
		ppre = phead;
		ptemp = phead->next;
		for (j = 1; j <= count - i; j++) {
			if (T(ptemp->next->score1) > T(ptemp->score1)) {
				p = ptemp->next;
				ppre->next = ptemp->next;
				ptemp->next = p->next;
				p->next = ptemp;
				ppre = p;
			} else {
				ptemp = ptemp->next;
				ppre = ppre->next;
				p = ptemp->next;
			}
		}
	}
	j = 0;
	ptemp = phead->next;
	while (ptemp != NULL) {
		s1 += T(ptemp->score1);
		ptemp->rank1 = ++j;
		ptemp = ptemp->next;
	}

	for (i = 1; i < count; i++) {                                              //score2
		ppre = phead;
		ptemp = phead->next;
		for (j = 1; j <= count - i; j++) {
			if (T(ptemp->next->score2) > T(ptemp->score2)) {
				p = ptemp->next;
				ppre->next = ptemp->next;
				ptemp->next = p->next;
				p->next = ptemp;
				ppre = p;
			} else {
				ptemp = ptemp->next;
				ppre = ppre->next;
				p = ptemp->next;
			}
		}
	}
	j = 0;
	ptemp = phead->next;
	while (ptemp != NULL) {
		s2 += T(ptemp->score2);
		ptemp->rank2 = ++j;
		ptemp = ptemp->next;
	}

	for (i = 1; i < count; i++) {                                              //score3
		ppre = phead;
		ptemp = phead->next;
		for (j = 1; j <= count - i; j++) {
			if (T(ptemp->next->score3) > T(ptemp->score3)) {
				p = ptemp->next;
				ppre->next = ptemp->next;
				ptemp->next = p->next;
				p->next = ptemp;
				ppre = p;
			} else {
				ptemp = ptemp->next;
				ppre = ppre->next;
				p = ptemp->next;
			}
		}
	}
	j = 0;
	ptemp = phead->next;
	while (ptemp != NULL) {
		s3 += T(ptemp->score3);
		ptemp->rank3 = ++j;
		ptemp = ptemp->next;
	}

	ppre = p = ptemp = (struct student*)malloc(sizeof(struct student));
	ptemp = phead->next;
	pend = phead1;
	while (ptemp != NULL) {
		t1 = T(ptemp->score1);
		t2 = T(ptemp->score2);
		t3 = T(ptemp->score3);
		ptemp->total = t1 + t2 + t3;
		if ((ptemp->total >= T(down)) && (ptemp->total <= T(up)) && (T(ptemp->score1) > T(down1))) {
			pend->next = ptemp;
			pend = ptemp;
		}
		ptemp = ptemp->next;
	}
	pend->next = NULL;
	if (T(up) >= T(down)) {
		return phead1;
	}
	for (i = 1; i < count; i++) {                                 //总成绩
		ppre = phead;
    	ptemp = phead->next;
		for (j = 1; j <= count - i; j++) {
			if (ptemp->next->total > ptemp->total) {
		       	p = ptemp->next;
				ppre->next = ptemp->next;
				ptemp->next = p->next;
				p->next = ptemp;
				ppre = p;
			} else {
				ptemp = ptemp->next;
				ppre = ppre->next;
				p = ptemp->next;
			}
		}
	}
	j = 0;
	ptemp = phead->next;
	while (1) {
		ptemp->rank = ++j;
		ptemp = ptemp->next;
		if (ptemp == NULL) {
			break;
		}
	}
	return;
}

Printf()                         //输出学生信息
{	
	ptemp = (struct student*)malloc(sizeof(struct student));
	ptemp = phead->next;
	if (count3 == 1) {
		printf("姓名    学号    班级       score1  score2  score3   排名\n\n");
	} else {
		printf("姓名    学号    班级       score1  score2  score3\n\n");
	}
	while(ptemp != NULL) {
		printf("%-8s", ptemp->name);
		printf("%-8s", ptemp->num);
		printf("%-12s", ptemp->banji);
		printf("%-8s", ptemp->score1);
		printf("%-8s", ptemp->score2);
		printf("%-8s", ptemp->score3);
		if (count3 == 1) {
			printf("%-5d\n", ptemp->rank);
		} else {
			printf("\n");
		}
	   	ptemp = ptemp->next;
	}
	return;
}

Printf2()                                //管理员输出账号信息， 以及账号更新信息
{
	ptemp = (struct student*)malloc(sizeof(struct student));
	ptemp = phead->next;
	printf("---------------------------------------------------------------------------------------------\n");
	printf("\n账号                 密码                 状态        班级\n");
	while (ptemp != NULL) {
		printf("%-20s ", ptemp->num);
		printf("%-20s ",ptemp->mima);
		printf("%-10s ", ptemp->state);
		printf("%-8s\n", ptemp->banji);
		ptemp = ptemp->next;
	}
	printf("\n---------------------------------------------------------------------------------------------\n\n");
	return;
}


Printf3()                                //管理员输出账号密码
{
	Read2();
	ptemp = (struct student*)malloc(sizeof(struct student));
	ptemp = phead->next;
	printf("----------------------------------------------------\n");
	printf("\n账号                 密码\n");
	while(ptemp != NULL) {
		printf("%-20s", ptemp->num);
		printf("%-20s\n", ptemp->mima);
	   	ptemp = ptemp->next;
	}
	printf("----------------------------------------------------\n");
	return;
}


Save()                                      //学生信息保存到文件
{
	FILE *fp;
	fp = fopen(s[choice], "w");
	if (fp == NULL) {
		printf("error\n");
		getch();
	} else {
		ptemp = p = (struct student*)malloc(sizeof(struct student));
		ptemp = phead->next;
		while (ptemp != NULL) {
	    	fprintf(fp, "%s ", ptemp->name);
	    	fprintf(fp, "%s ", ptemp->num);
	    	fprintf(fp, "%s ", ptemp->banji);
	    	fprintf(fp, "%s ", ptemp->score1);
	    	fprintf(fp, "%s ", ptemp->score2);
	    	fprintf(fp, "%s", ptemp->score3);
			ptemp = ptemp->next;
			if (ptemp != NULL) {
				fprintf(fp, "\n");
			}
		}
	}
	fclose(fp);
	printf("\t\t< 已将修改内容保存至源文件 >");
	return;
}

Save2()                                      //学生信息保存到文件
{
	FILE *fp;
	fp = fopen(s[choice], "a");
	if (fp == NULL) {
		printf("error\n");
		getch();
	} else {
		fprintf(fp, "\n");
		ptemp = p = (struct student*)malloc(sizeof(struct student));
		ptemp = phead->next;
		while (ptemp != NULL) {
	    	fprintf(fp, "%s ", ptemp->name);
	    	fprintf(fp, "%s ", ptemp->num);
	    	fprintf(fp, "%s ", ptemp->banji);
	    	fprintf(fp, "%s ", ptemp->score1);
	    	fprintf(fp, "%s ", ptemp->score2);
	    	fprintf(fp, "%s", ptemp->score3);
			ptemp = ptemp->next;
			if (ptemp != NULL) {
				fprintf(fp, "\n");
			}
		}
	}
	fclose(fp);
	printf("\t\t< 已将修改内容保存至源文件 >");
	return;
}


Save3()
{
	FILE *fp;
	fp = fopen(s[choice], "w");
	if (fp == NULL) {
		printf("error\n");
		getch();
	} else {
		ptemp = p = (struct student*)malloc(sizeof(struct student));
		ptemp = phead->next;
		while (ptemp != NULL) {
	    	fprintf(fp, "%s ", ptemp->num);
			fprintf(fp, "%s ", ptemp->mima);
			fprintf(fp, "%s ", ptemp->state);
			fprintf(fp, "%s", ptemp->banji);
			ptemp = ptemp->next;
			if (ptemp != NULL) {
				fprintf(fp, "\n");
			}
		}
	}
	fclose(fp);
	printf("\t\t< 已将修改内容保存至源文件 >");
	return;
}


Sort()                     //成绩分析：排名
{
	int count1 = 0, count2 = 0;	
	All();
	ptemp = (struct student*)malloc(sizeof(struct student));
	ptemp = phead->next;
	while (ptemp != NULL) {
		if (strcmp(ptemp->num, pxuehao) == 0) {    //自己排名
			printf("\t\t********************************************************************\n\n");
			if (T(ptemp->score1) < 60) {
				count1++;
			}
			if (T(ptemp->score2) < 60) {
				count1++;
			}
			if (T(ptemp->score3) < 60) {
				count1++;
			}
			printf("\t\t 姓名   科目一 科目二 科目三 总分   总排名 排名一 排名二 排名三\n");

			printf("\t\t %s", ptemp->name);
	    	printf(" %-6s", ptemp->score1);
	    	printf(" %--6s", ptemp->score2);
	    	printf(" %-6s", ptemp->score3);
	     	printf(" %-6d", ptemp->total);
	    	printf(" %-6d", ptemp->rank);
			printf(" %-6d", ptemp->rank1);
			printf(" %-6d", ptemp->rank2);
			printf(" %-6d\n", ptemp->rank3);
			break;
		} else {
	       	ptemp = ptemp->next;
		}
		if (ptemp == NULL) {
			printf("本班没有你要查找的学生\n");
			count2 = 1;
		}
	}
	if (count2 == 0) {
    	printf("\n\t\t 总分为%d,排名第%d,需要重修%d门课 \n", ptemp->total, ptemp->rank, count1);
		printf("\t\t\t                                  \n");
		printf("\t\t********************************************************************\n");
	}
	printf("\n是否要查看全班成绩\n");
	printf("1.查看全班排名\n");
   	printf("2.返回\n");
   	scanf("%d", &count1);
 	while (1) {
	   	if (count1 == 1) {
			count3 = 1;
			Printf();
			count3 = 0;
			return;
		}
		if (count1 == 2) {
			return;
		} else {
		   	printf("输入有误， 请重新输入");
		}
	}

}

Add()                                //教师增加学生信息
{	
	int a = 0, i;
	char s1[6][20];
	FILE *fp;
	fp = fopen(s[choice], "a");
	strcpy(s1[1], "网络1班");
	strcpy(s1[2], "网络2班");
	strcpy(s1[3], "网络3班");
	strcpy(s1[4], "网络4班");
	strcpy(s1[5], "网络5班");
	ptemp = p = (struct student*)malloc(sizeof(struct student));
	printf("\n请输入要插入的学生信息\n");
	printf("姓名       ");
	scanf("%s", p->name);
	printf("学号       ");
	while (1) {
		a = 0;
		scanf("%s", p->num);
		for (i = 0; p->num[i] != '\0'; i++){
			if ((p->num[i] > '9') || (p->num[i] < 0)) {
				a = 1;
				break;
			}
		}
		if (a == 1) {
			printf("输入有误，请重新输入\n");
			continue;
		} else {
			if (((int)(p->num[1]) - 48) != choice) {
				printf("请输入正确的学号格式（学号的第二个数表示班级）\n");
				continue;
			}
		}
		Read1();
		ptemp = phead->next;
		while (ptemp != NULL) {
			if (strcmp(p->num , ptemp->num) == 0) {
				break;
			}
			ptemp = ptemp->next;
			if (ptemp == NULL) {
				break;
			}
		}
		if (ptemp != NULL) {
			if (strcmp(p->num , ptemp->num) == 0) {
				printf("该账号已存在，请重新输入\n");
				continue;
			}
		}
	   	break;
	}
	puts(pbanji);
    strcpy(p->banji, pbanji);
	printf("三门课成绩 ");
	printf("score1: \n");
	while (1) {
		a = 0;
    	scanf("%s", p->score1);
		for (i = 0; p->score1[i] != '\0'; i++) {
			if (p->score1[0] == 0) {
				a = 1;
				break;
			}
			if ((p->score1[i] > '9') || (p->score1[i] < '0')) {
				a = 1;
				break;
			}
		}
		if (a == 1) {
			printf("输入有误，请重新输入score1\n");
		} else {
			break;
		}
	}
	printf("score2:\n");
	while (1) {
		a = 0;
    	scanf("%s", p->score2);
		for (i = 0; p->score2[i] != '\0'; i++) {
			if (p->score2[0] == 0) {
				a = 1;
				break;
			}
			if ((p->score2[i] > '9') || (p->score2[i] < '0')) {
				a = 1;
				break;
			}
		}
		if (a == 1) {
			printf("输入有误，请重新输入score2\n");
		} else {
			break;
		}
	}
	printf("score3:\n");
	while (1) {
		a = 0;
    	scanf("%s", p->score3);
		for (i = 0; p->score3[i] != '\0'; i++) {
			if (p->score3[0] == 0) {
				a = 1;
				break;
			}
			if ((p->score3[i] > '9') || (p->score3[i] < '0')) {
				a = 1;
				break;
			}
		}
		if (a == 1) {
			printf("输入有误，请重新输入score3\n");
		} else {
			break;
		}
	}
	fprintf(fp, "\n%s ", p->name);
	fprintf(fp, "%s ", p->num);
	fprintf(fp, "%s ", pbanji);
	fprintf(fp, "%s ", p->score1);
	fprintf(fp, "%s ", p->score2);
	fprintf(fp, "%s", p->score3);
	count++;
	fclose(fp);
	printf("\n\n\n修改成功\n\n");

	return;
}

Delete()                         //教师删除学生信息
{
	char a[20], b[20];
	ptemp = ppre = (struct student*)malloc(sizeof(struct student));
	Read1();
	while (1) {
		printf("请输入要删除的学生学号\n");
    	scanf("%s", a);
		ppre = phead;
		ptemp = phead->next;
		while (ptemp != NULL) {
			if (strcmp(a, ptemp->num) == 0) {
				ppre->next = ptemp->next;
				Save();
				count--;
				printf("已删除\n\n"); 
				return;
			}
			ppre = ptemp;
			ptemp = ptemp->next;
			if (ptemp == NULL) {
				printf("不存在该学号,按1继续输入\n");
				scanf("%s", b);
				if (T(b) == 1) {
					break;
				} else {
 					return;
				}
			}
		}
	}
}

Correct()                                   //教师修改学生信息
{
	int i, b, c = 0;
	char a[20];
	ptemp = p = (struct student*)malloc(sizeof(struct student));
	Read1();
	while (1) {
    	printf("请输入要修改的学生的学号\n");
    	scanf("%s", a);
		ptemp = phead->next;
		while (ptemp != NULL) {
			if (strcmp(a, ptemp->num) == 0) {
				printf("请输入修改后的学生信息\n");
				printf("姓名        ");
				scanf("%s", ptemp->name);
				printf("学号        ");
				while (1) {
					b = 0;
					scanf("%s", ptemp->num);
					for (i = 0; ptemp->num[i] != '\0'; i++){                             //是数字
						if ((ptemp->num[i] > '9') || (ptemp->num[i] < 0)) {
							b = 1;
							break;
						}
					}
					if (b == 1) {
						printf("输入有误，请重新输入\n");
						continue;
					} else {                                                                   //在本班
						if (((int)(ptemp->num[1]) - 48) != choice) {
							printf("请输入正确的学号格式（学号的第二个数表示班级）\n");
							continue;
						}
					}
					p = phead->next;
					while (p != NULL) {                                                    //和已有的不重复
						if (strcmp(p->num , ptemp->num) == 0) {
							c++;
							if (c == 2) {
						    	break;
							}
						}
						p = p->next;
						if (p == NULL) {
							break;
						}
					}
					if (p != NULL) {
						if (strcmp(p->num , ptemp->num) == 0) {
							printf("该账号已存在，请重新输入\n");
							continue;
						}
					}
					break;
				}
				printf("三门课成绩  ");
				printf("score1\n");
				while (1) {
		    		scanf("%s", ptemp->score1);
					if (Judge(ptemp->score1) == 0) {
						printf("输入有误，请重新输入\n");
					} else {
						break;
					}
				}
				printf("score2\n");
				while (1) {
		    		scanf("%s", ptemp->score2);
			    	if (Judge(ptemp->score2) == 0) {
				    	printf("输入有误，请重新输入\n");
					} else {
						break;
					}
				}	
				printf("score3\n");
				while (1) {
		    		scanf("%s", ptemp->score3);
			    	if (Judge(ptemp->score3) == 0) {
				    	printf("输入有误，请重新输入\n");
					} else {
						break;
					}
				}				
	        	Save();
	        	printf("修改成功\n\n");	
				return;
			}
			ptemp = ptemp->next;
			if (ptemp == NULL) {
				printf("该学号不存在或不在你管辖范围内, 按1继续\n");
				scanf("%d", &b);
				if (b == 1) {
					break;
				} else {
					return;
				}
			}
		}
	}
	Save();
	printf("修改成功\n\n");
}

Add3()                                   //管理员添加账号信息
{	
	char hao[20], mima[20], state[20], banji[20], a[20];
	FILE *fp;
	fp = fopen("d://password.txt", "a");
	printf("请输入要增加账号信息\n");
	while (1) {
		printf("账号\n");
		scanf("%s", hao);
		Read2();
		ptemp = phead->next;
		while (ptemp != NULL) {
			if (strcmp(ptemp->num, hao) == 0) {
				printf("该账号已存在， 按1继续输入\n");
				scanf("%s", a);
				if (T(a) == 1) {
					break;
				} else {
					return;
				}
			}
			ptemp = ptemp->next;
		}
		if (ptemp != NULL) {
			continue;
		} else {
			break;
		}
	}
	fprintf(fp, "\n%s ", hao);
	printf("密码\n");
	scanf("%s", mima);
	fprintf(fp, "%s ", mima);
	printf("身份\n");
	scanf("%s", state);
	fprintf(fp, "%s ", state);
	printf("所属班级\n");
	scanf("%s", banji);
	fprintf(fp, "%s", banji);
	fclose(fp);
	printf("添加成功\n");
}

Delete3()                                      //管理员输出账号信息
{
	char a[20];
	FILE *fp;
	fp = fopen("d://password.txt", "r");
	printf("请输入要删除的账号\n");
	scanf("%s", a);
	Read2();
	ptemp = ppre = (struct student*)malloc(sizeof(struct student));
	ppre = phead;
	ptemp = phead->next;
	while (ptemp != NULL) {
		if (strcmp(a, ptemp->num) == 0) {
			ppre->next = ptemp->next;
			break;
		}
		ppre = ptemp;
		ptemp = ptemp->next;
	}
	choice = 12;
	Save3();
	choice = 6;
	printf("已删除");
	return;
}

Correct3()                              //管理员修改账号信息
{
	char a[20], b[20];
	int c = 0;
	printf("请输入要修改的账号\n");
	scanf("%s", a);
	ptemp = p = (struct student*)malloc(sizeof(struct student));
	Read2();
	ptemp = phead->next;
	while (ptemp != NULL) {
		if (strcmp(a, ptemp->num) == 0) {
			printf("请输入修改后的账号信息\n");
			while (1) {
				printf("账号        ");
				scanf("%s", ptemp->num);
				p = phead->next;
				while (p != NULL) {
					if (strcmp(ptemp->num, p->num) == 0) {
						c++;
						if (c == 2) {
					     	printf("该账号已存在， 按1继续输入\n");
    						scanf("%s", b);
					    	if (T(b) == 1) {
					    		break;
							} else {
					    		return;
							}
						}
					}
				 	p = p->next;
				}
				if (p != NULL) {
					continue;
				} else {
					break;
				}
			}
			printf("密码        ");
			scanf("%s", ptemp->mima);
			printf("身份        ");
			scanf("%s", ptemp->state);
			printf("所属班级    ");
			scanf("%s", ptemp->banji);
			break;
		}
		ptemp = ptemp->next;
	}
	if (ptemp == NULL) {
		printf("你所要修改的账号不存在\n");
		choice = 6;
		return;
	}
	choice = 12;
	Save3();
	choice = 6;
	printf("修改成功");
	return;
}

Search3()                            //管理员查找账号及密码
{
	char a[20];
	FILE *fp;
	fp = fopen("d:\\password.txt", "r");
	Read2();
	printf("请输入要查找的账号\n");
	scanf("%s", a);
	ptemp = (struct student*)malloc(sizeof(struct student));
	ptemp = phead->next;
	while (ptemp != NULL) {
		if (strcmp(a, ptemp->num) == 0) {
			printf("你所要查找的账号信息如下\n\n");
			printf("----------------------------\n\n");
			printf("账号:\t");
			printf("%s", ptemp->num);
			printf("\n密码:\t");
			printf("%s", ptemp->mima);
			printf("\n身份:\t");
			printf("%s", ptemp->state);
			printf("\n班级:\t");
			printf("%s\n\n", ptemp->banji);
			printf("----------------------------\n\n");
			fclose(fp);
			return ;
		}
		ptemp = ptemp->next;
		if (ptemp == NULL) {
			printf("该账号未被注册\n");
			fclose(fp);
			return;
		}
	}
}

Luru3()                                //手动重新录入账号及密码
{
	int i, j = 0;
	char hao[20], mima[20], state[20], guanli[20], a[20];
	FILE *fp;
	printf("请输入要输入的账号的个数\n");
	while (1) {
    	scanf("%s", a);
		for (i = 0; a[i] != '\0'; i++) {
			if ((a[i] > '9') || (a[i] < '0')) {
				printf("输入有误， 请重新输入\n");
				j = 1;
				break;
			}
		}
		if (j == 1) {
			j = 0;
			continue;
		} else {
			break;
		}
	}
	fp = fopen("d://password.txt", "w");
	for (i = 1; i <= T(a); i++) {
		printf("账号\n");
		scanf("%s", hao);
		fprintf(fp, "%s ", hao);
		printf("密码\n");
		scanf("%s", mima);
		fprintf(fp, "%s ", mima);
		printf("状态\n");
		scanf("%s", state);
		fprintf(fp, "%s ", state);
		printf("管理班级\n");
		scanf("%s", guanli);
		fprintf(fp, "%s", guanli);

		if (i != T(a)) {
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
}

Luru4()                                  //手动重新录入学生信息
{
	FILE *fp;
	int a, i;
	char name[20], xuehao[20], banji[20], score[3][20], filename[30];
	printf("请输入文件名\n");
	gets(filename);
	gets(filename);
	printf("请输入要输入的账号的个数\n");
	scanf("%d", &a);
	fp = fopen(filename, "w");
	for (i = 1; i <= a; i++) {
		printf("姓名\n");
		scanf("%s", name);
		fprintf(fp, "%s ", name);
		printf("学号\n");
		scanf("%s", xuehao);
		fprintf(fp, "%s ", xuehao);
		printf("班级\n");
		scanf("%s", banji);
		fprintf(fp, "%s ", banji);
		printf("三门课成绩\n");
		scanf("%s", score[1]);
		scanf("%s", score[2]);
		scanf("%s", score[3]);
		fprintf(fp, "%s ", score[1]);
		fprintf(fp, "%s ", score[2]);
		fprintf(fp, "%s", score[3]);
		if (i != a) {
			fprintf(fp ,"\n");
		}
	}
	fclose(fp);
}

Shsu() 
{                                   //学生申诉
	FILE *fp;
	char xuehao[20], chji1[20], chji2[20], banji[20]; 
	fp = fopen("d://成绩申诉申请.txt", "a");
	printf("输入申请人学号\n");
	scanf("%s", xuehao);
	fprintf(fp, "%s ", xuehao);
	printf("输入申请人班级\n");
	scanf("%s", banji);
	fprintf(fp, "%s ", banji);
	printf("要申诉哪一门\n");
	scanf("%s", chji1);
	fprintf(fp, "%s ", chji1);
	printf("修改为:\n");
	scanf("%s", chji2);
	fprintf(fp, "%s\n", chji2);
	fclose(fp);
	printf("已通知管理员\n");
	return;
}

Update()                                         //教师告诉管理员成绩的申诉
{
	FILE *fp;
	char xuehao[20], chji1[20], chji2[20], banji[20];
	fp = fopen("d://成绩库.txt", "w");
	choice = 1;
	Read1();
	choice = 6;
	Save();
	fclose(fp);
	fclose(fp);
	choice = 2;
	Read1();
	choice = 6;
	Save2();
	fclose(fp);
	fclose(fp);
	choice = 3;
	Read1();
	choice = 6;
	Save2();
	fclose(fp);
	choice = 4;
	Read1();
	choice = 6;
	Save2();
	fclose(fp);
	choice = 5;
	Read1();
	choice = 6;
	Save2();
	fclose(fp);
	printf("\n成绩库更新完毕\n\n");
	return;
}

Judge(char a[])
{
	int i;
	for (i = 0; a[i] != '\0'; i++) {
		if ((a[i] > '9') || (a[i] < '0')) {
			return 0;
		}
	}
	return 1;
}


Student(int n)
{
	if (n == 1) {
		printf("\t\t\t-------------------------------------\n");
		printf("\t\t\t        请选择服务项目               \n");
		printf("\t\t\t-------------------------------------\n");	
		printf("\t\t\t         1.成绩查询                  \n");
		printf("\t\t\t         2.查询本班成绩              \n");
		printf("\t\t\t         3.成绩分析                  \n");
		printf("\t\t\t         4.成绩申诉                  \n");
		printf("\t\t\t         5.重新登录                  \n");
		printf("\t\t\t-------------------------------------\n");
		return;
	} else {
		printf("\t\t\t-------------------------------------\n");
		printf("\t\t\t           5.返回上一层              \n");
		printf("\t\t\t           6.重新登录                \n");
		printf("\t\t\t           0.退出                    \n");
		printf("\t\t\t-------------------------------------\n");
    	return;
	}
}
Teacher(int n)
{
	if (n == 1) {		
		printf("\t\t\t-------------------------------------\n");
		printf("\t\t\t         请选择服务项目              \n");
		printf("\t\t\t-------------------------------------\n");
		printf("\t\t\t        1、 增加学生信息               \n");
		printf("\t\t\t        2、 删除学生信息               \n");
		printf("\t\t\t        3、 修改学生信息               \n");
		printf("\t\t\t        4、 查询学生信息               \n");
		printf("\t\t\t        5、 输出本班成绩               \n");
		printf("\t\t\t        6、 下载到文件                 \n");
		printf("\t\t\t        7、 成绩分析                   \n");
		printf("\t\t\t        8、 提醒管理员进行成绩更新     \n");
		printf("\t\t\t        9、 重新登录                   \n");
		printf("\t\t\t-------------------------------------\n");
	} else {
		printf("\t\t\t-------------------------------------\n");
		printf("\t\t\t          9.返回上一层                 \n");
		printf("\t\t\t          10.重新登录                 \n");
		printf("\t\t\t          0.退出                       \n");
		printf("\t\t\t-------------------------------------\n");
	}
}

Charger(int n)
{
	if (n == 1) { 
		printf("\t\t\t-------------------------------------\n");
		printf("\t\t\t-----------请选择服务项目------------\n");
		printf("\t\t\t-------------------------------------\n");
		printf("\t\t\t|   1、 查看待办选项                 |\n");
		printf("\t\t\t|   2、 进入教师端进行信息修改       |\n");
		printf("\t\t\t|   3、 增加账号及密码               |\n");
		printf("\t\t\t|   4、 删除账号及密码               |\n");
		printf("\t\t\t|   5、 修改账号及密码               |\n");
		printf("\t\t\t|   6、 查找账号及密码               |\n");
		printf("\t\t\t|   7、 录入所以账号及密码           |\n");
		printf("\t\t\t|   8、 输出所有账号及密码           | \n");
		printf("\t\t\t|   9、 手动重新录入学生信息         |\n");
		printf("\t\t\t|   10、重新登录                     |\n");
    	printf("\t\t\t--------------------------------------\n");
	} else {
    	printf("\t\t\t--------------------------------------\n");
		printf("\t\t\t            a.返回上一层              \n");
		printf("\t\t\t            b.重新登录                \n");
		printf("\t\t\t            0.t退出                   \n");
    	printf("\t\t\t--------------------------------------\n");
	}
}

main()
{
	FILE *fp;
	int t, t1, k = 1, j = 0, m, i = 0;
	char a[20], b[20], d[20], c[20], h[20], q[20];
	strcpy(s[1], "d:\\网络1班.txt");
	strcpy(s[2], "d:\\网络2班.txt");
	strcpy(s[3], "d:\\网络3班.txt");
	strcpy(s[4], "d:\\网络4班.txt");
	strcpy(s[5], "d:\\网络5班.txt");
	strcpy(s[6], "d:\\成绩库.txt");
	strcpy(s[7], "d:\\注册申请.txt");
	strcpy(s[8], "d:\\密码修改申请.txt");
	strcpy(s[9], "d:\\密码找回申请.txt");
	strcpy(s[10], "d:\\成绩申诉申请.txt");
	strcpy(s[11], "d:\\message.txt");
	strcpy(s[12], "d:\\password.txt");
	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t+ + + + + 欢 迎 使 用 学 生 管 理 系 统 + + + + +\n\n\n\n\n\n\n");
	system("pause");
	system("cls");
	while (1) {
		j = 0;
		printf("\t\t\t             请选择服务项目            \n");
		printf("                                             \n");
		printf("\t\t\t=======================================\n");
		printf("                                             \n");
		printf("\t\t\t              1、 登录                 \n");
		printf("\t\t\t              2、 注册                 \n");
		printf("\t\t\t              3、修改密码              \n");
		printf("\t\t\t              4、找回密码              \n");
		printf("                                             \n");
		printf("\t\t\t=======================================\n");
		while (1) {
			scanf("%s", b);
			if (T(b) == 1) {               //q登录或注册
				system("pause");
				system("cls");
				t = Land();
				break;
			}
			if (T(b) == 2) {
				system("pause");
				system("cls");
				Register();
				printf("按1继续，\n");
				scanf("%d", &m);
				if (m == 1) {
					break;
				} else {
    				exit(0);
				}
			} 
			if (T(b) == 3) {
				system("pause");
				system("cls");
				Correct2();
				printf("按1继续，\n");
				scanf("%d", &m);
				if (m == 1) {
					break;
				} else {
    				exit(0);
				}
			} 
			if (T(b) == 4) {
				system("pause");
				system("cls");
				Find();
				printf("按1继续，\n");
				scanf("%d", &m);
				if (m == 1) {
					break;
				} else {
    				exit(0);
				}
			} 
			printf("错误，请重新输入\n");
			continue;
		}	
		system("cls");
		if (T(b) == 1) {

			while(1) {
				if (t == 1) { 
					printf("\n\n\n\n\n\n");
					printf("\t\t\t\t* * * * * * * * * * * * \n");
					printf("\t\t\t\t*                     * \n");
					printf("\t\t\t\t*   你已进入学生端    * \n");
					printf("\t\t\t\t*                     * \n");
					printf("\t\t\t\t* * * * * * * * * * * * \n");
					system("pause");
					system("cls");
					while (1) {
						Student(1);
						scanf("%s", b);
				    	system("pause");
					    system("cls");   
						switch (T(b)) {
						case 1 : strcpy(w, pxuehao); Search2(); break;
						case 2 : Read1(); Printf(); break;
						case 3 : Sort(); break;
						case 4 : Shsu(); break;
						case 5 : j = 1; break;
						default : printf("输入有误， 请重新输入\n");
						}
						if (j == 1) {
							break;
						}
						if ((T(b) > 4) || (T(b) < 1)) {
							continue;
						}
						system("pause");
						system("cls");
						while (1) {	
							Student(2);
							scanf("%s", b);
							system("pause");
							system("cls");
							switch (T(b)) {
							case 5 : break; 
							case 6 : j = 1; break;
							case 0 : exit(0);
							default : printf("输入有误， 请重新输入\n");
							}
							if ((T(b) == 5) || (T(b) == 6)) {
								system("cls");
								break;
							}
						}	
						if (j == 1) {
				    		system("cls");
				        	break;
						}
						system("cls");
					}
				}
				if (t == 2) {
					printf("\n\n\n\n\n\n");
					printf("\t\t\t\t* * * * * * * * * * * * \n");
					printf("\t\t\t\t*                     * \n");
					printf("\t\t\t\t*   你已进入教师端    * \n");
					printf("\t\t\t\t*                     * \n");
					printf("\t\t\t\t* * * * * * * * * * * * \n");
					system("pause");
					system("cls");	
					while (1) {
						if (k == 0) {
							printf("请选择要操作哪个班\n");
							while (1) {
								scanf("%s", k);
								if ((T(k) > 0) && (T(k) < 7)) {
									choice  = T(k);
									printf("已进入%d班\n", T(k));
									system("pause");
									system("cls");
									k = 0;
									break;
								} else {
									printf("输入有误，请重新输入\n");
								}
							}
						}
			         	Teacher(1);
						scanf("%s", b);
                    	system("pause");
						system("cls");
						switch (T(b)) {
						case 1 : Add();  break;
						case 2 : Delete(); break;
						case 3 : Correct(); break;
						case 4 : 
							printf("请输入要查找的学生学号或姓名或区间段\n");
							printf("1.学号\n");
							printf("2.姓名\n");
							printf("3.分数区间\n");
							while (1) {	
								scanf("%s", h);
								if (T(h) == 1) {                      //c查询方式
									printf("请输入学号\n");
									scanf("%s", a);
									strcmp(w, pxuehao);         //w[20]存教师自己的学号
									strcpy(pxuehao, a);
									break;
								}
								if (T(h) == 3) {
									while (1) {
										while (1) {
											printf("输入上限\n");
											scanf("%s", up);
											for (i = 0; up[i] != '\0'; i++) {
												if ((up[i] > '9') || (up[i] < '0')) {
													printf("输入有误，请重新输入\n");
													i++;
													break;
												}
											}
											if ((up[i - 1] > '9') || (up[i - 1] < '0')) {
												continue;
											} else {
												break;
											}
										}
										while (1) {
											printf("输入下限\n");
											scanf("%s", down);
											for (i = 0; down[i] != '\0'; i++) {
												if ((down[i] > '9') || (down[i] < '0')) {
													i++;
													break;
												}
											}
											if ((down[i - 1] > '9') || (down[i - 1] < '0')) {
												continue;
											} else {
												break;
											}
										}
										if (T(up) < T(down)) {
											printf("输入有误， 请重新输入(上限大于等于下限)\n");
											continue;
										}  else {
											break;
										}
									}
									while (1) {
										printf("输入score1下限\n");
										scanf("%s", down1);
										for (i = 0; down1[i] != '\0'; i++) {
											if ((down1[i] > '9') || (down1[i] < '0')) {
												i++;
												break;
											}
										}
										if ((down1[i - 1] > '9') || (down1[i - 1] < '0')) {
											continue;
										} else {
											break;
										}
									}
									break;
								}
								if (T(h) == 2) {
									printf("请输入姓名\n");
									scanf("%s", pname);
									break;
								} else {
									printf("输入有误，请重新输入\n");
								}
								
							}
							if (T(h) == 3) {
								All();
								ptemp = (struct student*)malloc(sizeof(struct student));
								ptemp = phead1->next;
								if (phead1->next != NULL) {
									printf("\t************************************************\n\n");
									printf("\t姓名      科目一     科目二     科目三     总分\n\t");
									while (ptemp != NULL) {
										printf("%-10s ", ptemp->name);
										printf("%-10s ", ptemp->score1);
										printf("%-10s ", ptemp->score2);
										printf("%-10s ", ptemp->score3);
										printf("%-10d\n\t", ptemp->total);
										ptemp = ptemp->next;
									}
									printf("\n\t**********************************************\n\n");
									strcpy(up, "0");
									strcpy(down, "1");
									break;
								} else {
									printf("没有满足查找条件的学生\n");
									break;
								}
							}
							
							Search2(); break;
						case 5 : Read1(); Printf(); break;
						case 6 : Save(); break;
						case 7 :
							All();
							printf("本班科目一平均分%d, 科目二平均分%d, 科目三平均分%d\n", (s1/count), (s2/count), (s3/count));
							printf("是否要查询查看本班个人成绩分析, 按<1>查看\n");
							scanf("%s", b);
							if (T(b) == 1) {
								while (1) {
									printf("请输入你要分析的学生学号\n");
									scanf("%s", a);
									strcmp(w, pxuehao);
									strcpy(pxuehao, a);
									Sort();
									strcpy(pxuehao, w);
									printf("按<1>继续输入分析\n");
									scanf("%s", h);
									if (T(h) != 1) {
										break;
									}
								}

							}	
							break;		
						case 8 : Update(); break;
						case 9 : j = 1; break;
						default : printf("输入有误， 请重新输入\n");
						} 
						if (j == 1) {
							break;
						}
						if ((T(b) < 1) || (T(b) > 8)) {
							continue;
						}	
						system("pause");
						system("cls");
						while (1) {	
							Teacher(2);
							scanf("%s", b);
				    		system("pause");
					    	system("cls");
					   		switch (T(b)) {
							case 9 : break;
							case 10 : j = 1; break;
							case 0 : exit(0);
							default : printf("输入有误， 请重新输入\n");
							}
					     	if ((T(b) == 9) || (T(b) == 10)) {
							break;
							}
						}
						if (j == 1) {
						break;
						}
						if (k == 0) {
							printf("\t\t\t是否退出教师端\n");
							printf("\t\t\t1.退出\n");
							printf("\t\t\t2.不退出\n\n\t\t\t");
							while (1) {
								scanf("%s", c);
								if (T(c) == 1) {
									t = 3;
									break;
								}
								if ((T(c) != 1) && (T(c) != 2)) {
									printf("输入有误，请重新输入\n");
								}
								if (T(c) == 2) {
									break;
								}
							}
						}
						if (T(c) == 1) {                        //管理员从教师端退出
							break;
						}
						system("pause");
						system("cls");
					}
				}
				if (t == 3) {
					printf("\n\n\n\n\n\n");
					printf("\t\t\t\t* * * * * * * * * * * * \n");
					printf("\t\t\t\t*                     * \n");
					printf("\t\t\t\t*   你已进入管理端    * \n");
					printf("\t\t\t\t*                     * \n");
					printf("\t\t\t\t* * * * * * * * * * * * \n");
					while (1) {	
						k = 1;
		            	system("pause");
		            	system("cls");
			        	Charger(1);
						scanf("%s", b);
						system("pause");
		    			system("cls");
						switch (T(b)) {
						case 1 : 
							while (1) {
								printf("密码注册申请\n");
								choice = 7;
								Read3();
								Printf2();
								printf("密码修改申请\n");
								choice = 8;
								Read3();
								Printf2();
								printf("密码找回申请\n");
								choice = 9;
								Read3();
								Printf2();
								printf("成绩申诉申请\n");
								choice = 10;
								Read3();
								Printf2();
								printf("更新成绩库申请\n");
								choice = 11;
								Read3();
								Printf2();
								printf("按1更新成绩库\n");
								scanf("%s", q);
								if (T(q) == 1) {
									Update();
								}
								break;
							}
							break;
						case 2 : 
							k = 0;
							break;
						case 3 : Add3(); break;
						case 4 : Delete3(); break;
						case 5 : Correct3(); break;
						case 6 : Search3(); break;
						case 7 : Luru3(); break;
						case 8 : Printf3(); break;
						case 9 : Luru4(); break;
						case 10 : j = 1; break;
						default : printf("输入有误， 请重新输入\n"); break;
						}
						if (j == 1) {
							break;
						}
						if (k == 0) {
							t = 2;
							break;
						}
						if ((T(b) < 1) || (T(b) > 9)) {
							continue;
						}
						system("pause");
						system("cls");
						Charger(2); 
						while (1) {
							scanf("%s", b);
							switch (T(b)) {
							case 49 : break;
							case 50 : j = 1; break;
							case 0 : exit(0);
							default : printf("输入有误， 请重新输入\n"); break;
							}
					    	if ((T(b) == 49) || (T(b) == 50)){
						    	break;
							}
						}
						if (j == 1) {
							system("cls");
							break;
						}
						system("cls");
					}
				}
		    	if (j == 1) {
		    		break;		
				}
             }
		   
		}
	}
}
