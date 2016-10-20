//
//  parser.h
//  SameLine
//
//  Created by Wai Man Chan on 9/23/16.
//  Copyright © 2016 Wai Man Chan. All rights reserved.
//

#include <vector>
#include <map>
#include <string>
using namespace std;

#ifndef parser_h
#define parser_h

struct TestCode {
    int lineNum;
    string content;
};

struct TestCase {
    string name;
    vector<struct TestCode*> codes;
    vector<string> setup;
};

struct TestSection {
    string name;
    struct TestSection *parentSection;
    map<string, struct TestCase *> cases;
    map<string, struct TestSection *> subSection;
    vector<string> setup;
};

struct strippedCode {
    
};

extern bool tagState;
extern string buffer;
extern string code;

extern TestSection *rootSection;
extern TestSection *currentSection;
extern TestCase    *currentCase;

extern FILE * yyin;
extern int yylineno;
int yylex();
int yyparse();

void initSection(string fileName);

#define YYSTYPE void*

#endif /* parser_h */
