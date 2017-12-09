//HEMC-helper  beta
//version 0.1.160903
//Copyright(c) 2016 @ypingcn

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#include "io.h"
#include "ui.h"
#include "func.h"


int main()
{
	int option;
	load();
	welcome();
	while( menu_main() , option=getnum(1,7) )
	{
		if(option == 1)
			intro();
		else if(option == 2)
			web();
		else if(option == 3)
			lib();
		else if(option == 4)
			edusys();
		else if(option == 5)
			about();
		else if(option == 6)
			code();
		else if(option == 7)
			quit();
	}
	return 0;
}



