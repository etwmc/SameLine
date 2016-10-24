//
//  bootupTest.c
//  SameLine
//
//  Created by Wai Man Chan on 10/19/16.
//  Copyright © 2016 Wai Man Chan. All rights reserved.
//

//Test: setup var result = 9;
//Test: setup var i = 3;

//Test: section start Square function
//Test: case Positive
//Test: testCode square(i)==result
//Test: section stop
function square(x) { return x*x; }

//Test: section start Para
//Test: case Equalavent
//Test: testCode para(i)==square(i+1)
//Test: endCase
//Test: section stop
function para(x) { return square(x)+2*x+1; }
