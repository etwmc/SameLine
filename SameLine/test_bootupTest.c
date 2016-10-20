//
//  bootupTest.c
//  SameLine
//
//  Created by Wai Man Chan on 10/19/16.
//  Copyright © 2016 Wai Man Chan. All rights reserved.
//

#include <stdio.h>


int square(int x) { return x*x; }

int para(int x) { return square(x)+2*x+1; }


void TestCase_bootupTest_Para_Equalavent(){
	//Setup
	intResult=9;
	intI=3;

	//Code
	if ((para(i)==square(i+1)))
		printf("Success on line 22 in bootupTest.c\n");
	else
		printf("Error on line 22 in bootupTest.c\n");
}

void TestSection_bootupTest_Para(){
	TestCase_bootupTest_Para_Equalavent();
}



void TestCase_bootupTest_SquareFunction_Positive(){
	//Setup
	intResult=9;
	intI=3;

	//Code
	if ((square(i)==result))
		printf("Success on line 16 in bootupTest.c\n");
	else
		printf("Error on line 16 in bootupTest.c\n");
}

void TestSection_bootupTest_SquareFunction(){
	TestCase_bootupTest_SquareFunction_Positive();
}

void TestSection_bootupTest(){
	TestSection_bootupTest_Para();
	TestSection_bootupTest_SquareFunction();
}
