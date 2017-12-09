//HEMC-helper  beta
//version 0.1.160903
//Copyright(c) 2016 @ypingcn

#include<stdio.h>
#include<windows.h>

void dyput(char * s)
{
	Sleep(30);
	printf("\t%s\n",s);
}

int getnum(int min,int max)
{
	char temp;
	int result;
	int wrong_time=0;
	printf("\tPlease input a number according to the menu:");
A:	if(wrong_time!=0)
		printf("\tInput again");
	while(scanf("%d",&result) != 1)
	{
		printf("\tWhat you input\" ");
		while((temp=getchar()) != '\n')
			putchar(temp);
		printf(" \"");
		printf("is illegal.\n");
		wrong_time++;
		goto A;
	}
	if(result < min || result > max)
	{
			printf("\tThe number you input\" %d \"is wrong,and",result);
			while((temp=getchar()) != '\n')
				putchar(temp);
			printf("isn't a option.\n");
			wrong_time++;
			goto A;
	}
	while((temp=getchar()) != '\n')
		putchar(temp);
	return result;
}

