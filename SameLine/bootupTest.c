//
//  bootupTest.c
//  SameLine
//
//  Created by Wai Man Chan on 10/19/16.
//  Copyright © 2016 Wai Man Chan. All rights reserved.
//

#include <stdio.h>

#pragma setup int result = 9;
#pragma setup int i = 3;

#pragma section start Square function
#pragma case Positive
#pragma testCode square(i)==result
#pragma section stop
int square(int x) { return x*x; }

#pragma section start Para
#pragma case Equalavent
#pragma testCode para(i)==square(i+1)
#pragma endCase
#pragma section stop
int para(int x) { return square(x)+2*x+1; }
