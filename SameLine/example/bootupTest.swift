//
//  bootupTest.swift
//  SameLine
//
//  Created by Wai Man Chan on 10/28/16.
//  Copyright © 2016 Wai Man Chan. All rights reserved.
//

import Foundation

//Test: section start MathObj
class MathObj: NSObject {
    let value: Int
    
    //Test: setup let a = MathObj(value: 3)
    //Test: setup let b = MathObj(value: 3)
    //Test: setup let c = MathObj(value: 4)
    init(value _value: Int) {
        value = _value
    }
    
    //Test: case Square
    //Test: testCode a.square() == 9
    //Test: testCode b.square() == 9
    //Test: testCode c.square() == 16
    //Test: endCase
    func square()->Int {
        return value * value
    }
    
    //Test: case para
    //Test: testCode a.para() == c.square()
    //Test: testCode b.para() == 16
    //Test: testCode c.para() == 25
    //Test: endCase
    func para()->Int {
        return square()+2*value+1
    }
    
    //Test: case Equal To
    //Test: testCode a == b
    //Test: testCode a != c
    //Test: endCase
    override func isEqual(_ object: Any?) -> Bool {
        if let object = object as? MathObj {
            return object.value == value
        } else { return false }
    }
}
