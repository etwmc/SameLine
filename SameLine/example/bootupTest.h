//
//  bootupTest.h
//  SameLine
//
//  Created by Wai Man Chan on 10/28/16.
//  Copyright © 2016 Wai Man Chan. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MathObj : NSObject {
    int _value;
}
- (id)init:(int)value;
- (int)square;
- (int)para;
@end
