//HEMC-helper  beta
//version 0.1.160903
//Copyright(c) 2016 @ypingcn

#include<stdio.h>
#include<windows.h>

void welcome(void)
{
	system("cls");
	system("title HEMC-helper !! Welcome ");
	dyput("************************************************");
	dyput("");
	dyput("    HEMC-helper   beta 0.1.160903    ");
	dyput("");
	dyput("************************************************");
	Sleep(1500);
}

void load(void)
{
	int t1,t2;
	for(t1=0;t1<=10;t1++)
	{
		system("title HEMC-helper !! Loading");
		printf("\tloading.....%d%%\n\t",10*t1);
		for(t2=0;t2<=t1;t2++)
			printf(".");
		Sleep(100);
		system("cls");
	}
}

void menu_main(void)
{
	system("cls");
	system("title HEMC-helper !! Menu");
	dyput("*********************");
	dyput("*********************");
	dyput("");
	dyput("1. Introdution of Guangzhou HEMC");
	dyput("2. Homepage");
	dyput("3. Libraries");
	dyput("4. Educational administration system");
	dyput("5. About");
	dyput("6. Get source code");
	dyput("7. Quit");
	dyput("");
	dyput("*********************");
	dyput("*********************");
}

void menu_sch(void)
{
	system("cls");
	system("title HEMC-helper !! List");
	dyput("*******************************");
	dyput("");
	dyput("1. Sun Yat-Sen University");
	dyput("2. Ji'nan University");
	dyput("3. Guangzhou University");
	dyput("4. South China University of Technology");
	dyput("5. South China Normal University");
	dyput("6. Guangdong University of Technology");
	dyput("7. Guangzhou University of Chinese Medicine");
	dyput("8. Guangdong University of Foreign Studies");
	dyput("9. Guangdong Pharmaceutical University");
	dyput("10. Guangzhou Academy of Fine Arts");
	dyput("11. Guangzhou Medical University");
	dyput("12. Xinghai Conservatory of Music");
	dyput("");
	dyput("*******************************");
}
