

#include<iostream>

#include"Eom1.h"
#include"Hwang1.h"
int main()
{
	std::cout << "Eom입니다.\n";



	Eom1 sumClass;
	int sum =	sumClass.calSum({ 1, 2, 3, 4, 5, 6 });

	Hwang1 printClass;
	printClass.Print(sum);

}

