//
//  bootupTest.m
//  SameLine
//
//  Created by Wai Man Chan on 10/28/16.
//  Copyright © 2016 Wai Man Chan. All rights reserved.
//

#import "bootupTest.h"

@interface MathObj ()
- (int)getVal;
@end

//Test: section start MathObj

@implementation MathObj

//Test: setup MathObj *a = [[MathObj alloc] init: 3];
//Test: setup MathObj *b = [[MathObj alloc] init: 3];
//Test: setup MathObj *c = [[MathObj alloc] init: 4];
- (id)init:(int)value {
    if ([super init])
        _value = value;
    return self;
}

- (int)getVal { return _value; }

//Test: case Square
//Test: testCode [a square] == 9
//Test: testCode [b square] == 9
//Test: testCode [c square] == 16
//Test: endCase
- (int)square {
    return _value*_value;
}

//Test: case para
//Test: testCode [a para] == [c square]
//Test: testCode [b para] == 16
//Test: testCode [c para] == 25
//Test: endCase
- (int)para {
    return [self square]+2*_value+1;
}

//Test: case Equal To
//Test: testCode [ a isEqualTo: b]
//Test: testCode ![ a isEqualTo: c]
//Test: endCase
- (BOOL)isEqualTo:(id)object {
    if ([object class] == [MathObj class])
        return [(MathObj *)object getVal] == _value;
    return false;
}

@end

//Test: section stop
