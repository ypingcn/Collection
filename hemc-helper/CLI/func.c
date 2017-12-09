//HEMC-helper  beta
//version 0.1.160903
//Copyright(c) 2016 @ypingcn

#include<stdio.h>
#include<windows.h>

void intro(void)
{
	system("cls");
	system("title HEMC-helper !! Introdution of Guangzhou HEMC");
	dyput("***************************************************************");
	dyput("");
	dyput("                           Guangzhou HEMC");
	dyput("");
	dyput("***************************************************************");
	dyput("HEMC means \"Higher Education Mega Center\"");
	dyput("Location : XinZao,PanYu district,Guangzhou city,China.");
	dyput("Area : 18 square kilometers.");
	dyput("Places worth visiting : ");
	dyput("# HuangPu Military Academy");
	dyput("# XinHai revolution memorial hall");
	dyput("# Memorial Hall to Dr.Sun Yat sen");
	dyput("Sep 1th,2014,ten universities or colleges moved in it.They are");
	dyput("# Sun Yat-Sen University");
	dyput("# Guangzhou University");
	dyput("# South China University of Technology");
	dyput("# South China Normal University");
	dyput("# Guangdong University of Technology");
	dyput("# Guangzhou University of Chinese Medicine");
	dyput("# Guangdong University of Foreign Studies");
	dyput("# Guangdong Pharmaceutical University");
	dyput("# Guangzhou Academy of Fine Arts");
	dyput("# Xinghai Conservatory of Music");
	dyput("Later Ji'nan University and Guangzhou Medical University will in it");
	dyput("");
	dyput("******press c to know more,others to quit******");
	printf("\t");
	fflush(stdin);
	char ch=getchar();
	if( ch == 'c' )
		system("start http://baike.baidu.com/view/4557.htm");
}

void web(void)
{
	system("cls");
	system("title HEMC-helper !! Homepage");
	menu_sch();
	int choice=getnum(1,12);
	switch(choice)
	{
		case 1: system("start http://www.sysu.edu.cn");		break;
		case 2: system("start http://www.jnu.edu.cn");		break;
		case 3: system("start http://www.gzhu.edu.cn");		break;
		case 4: system("start http://www.scut.edu.cn");		break;
		case 5: system("start http://www.scnu.edu.cn");		break;
		case 6: system("start http://www.gdut.edu.cn");		break;
		case 7: system("start http://www.gzhtcm.edu.cn");	break;
		case 8: system("start http://www.gdufs.edu.cn");	break;
		case 9: system("start http://www.gdpu.edu.cn/");	break;
		case 10: system("start http://www.gzarts.edu.cn/");	break;
		case 11: system("start http://www.gzhmc.edu.cn/");	break;
		case 12: system("start http://www.xhcom.edu.cn/");	break;
		default:	break;
	}
}

void lib(void)
{
	system("cls");
	system("title HEMC-helper !! libraries");
	int choice;
	menu_sch();
	choice=getnum(1,12);
	switch(choice)
	{
		case 1: system("start http://library.sysu.edu.cn");	break;
		case 2: system("start http://libgp.jnu.edu.cn");	break;
		case 3: system("start http://lib.gzhu.edu.cn");	break;
		case 4: system("start http://www.lib.scut.edu.cn");	break;
		case 5: system("start http://lib.scnu.edu.cn");	break;
		case 6: system("start http://library.gdut.edu.cn");	break;
		case 7: system("start http://library.gzhtcm.edu.cn");	break;
		case 8: system("start http://lib.gdufs.edu.cn");	break;
		case 9: system("start http://www.lib.gdpu.edu.cn/rgzn/gzzd");	break;
		case 10: system("start http://lib.gzarts.edu.cn");	break;
		case 11: system("start http://lib.gzhmc.edu.cn");	break;
		case 12: system("start http://www.xhcomlib.cn");	break;
		default:	break;

	}
}

void edusys(void)
{
	system("cls");
	system("title HEMC-helper !! Educational administration system");
	menu_sch();
	int choice=getnum(1,12);
	switch(choice)
	{
		case 1: system("start http://uems.sysu.edu.cn/jwxt");	break;
		case 2: system("start http://jwc.jnu.edu.cn");	break;
		case 3: system("start http://jwc.gzhu.edu.cn");	break;
		case 4: system("start http://www.scut.edu.cn/jw2005");	break;
		case 5: system("start http://jw.scnu.edu.cn");	break;
		case 6: system("start http://jwgl.gdut.edu.cn");	break;
		case 7: system("start http://210.38.111.228/");	break;
		case 8: system("start http://jwc.gdufs.edu.cn"); break;
		case 9: system("start http://dep.gdpu.edu.cn/jwc/"); break;
		case 10: system("start http://jwxt.gzarts.edu.cn"); break;
		case 11: system("start http://jwc.gzhmc.edu.cn"); break;
		case 12: system("start http://jwc.xhcom.edu.cn"); break;
		default:break;

	}
} 

void about(void)
{
	system("cls");
	system("title HEMC-helper !! About");
	dyput("*******************************************************");
	dyput("");
	dyput("                Assistance for GZ HEMC");
	dyput("This is just a C program.And you can get its source code.");
	dyput("Welcome to connect with us to tell your suggestion.");
	dyput("");
	dyput("*******************************************************");
	printf("\tpress any key to continue.");
	fflush(stdin);
	getchar();
}

void code(void)
{
	system("cls");
	system("title HEMC-helper !! Get source code");
	dyput("*******************************************************");
	dyput("");
	dyput("You can get the source code via Github.");
	dyput("https://github.com/ypingcn/Assistance-for-GZ-HEMC");
	dyput("");
	dyput("*******************************************************");
	printf("\tpress v to visit,others to continue.");
	fflush(stdin);
	char ch=getchar();
	if( ch == 'v' )
		system("start https://github.com/ypingcn/HEMC-helper");
}

void quit(void)
{
	system("cls");
	system("title HEMC-helper !! Quit");
	dyput("*******************************");
	dyput("");
	dyput("          Thank you~");
	dyput("");
	dyput("*******************************");
	Sleep(2000);
	exit(0);
}


