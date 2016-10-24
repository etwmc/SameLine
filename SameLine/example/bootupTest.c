//
//  bootupTest.c
//  SameLine
//
//  Created by Wai Man Chan on 10/19/16.
//  Copyright © 2016 Wai Man Chan. All rights reserved.
//

#include <stdio.h>

//Test: setup int result = 9;
//Test: setup int i = 3;

//Test: section start Square function

//Test: case Positive
//Test: testCode square(i)==result
//Test: end case

//Test: case Negative
//Test: setup int j = -3;
//Test: testCode square(i)==square(j)
//Test: end case

//Test: section stop
int square(int x) { return x*x; }

//Test: section start Para

//Test: case Equalavent
//Test: testCode para(i)==square(i+1)
//Test: endCase

//Test: case Minimum
//Test: testCode para(-1)==0

//Test: section stop
int para(int x) { return square(x)+2*x+1; }
