//
//  main.c
//  SameLine
//
//  Created by Wai Man Chan on 9/23/16.
//  Copyright © 2016 Wai Man Chan. All rights reserved.
//

#include <stdio.h>

#include "parser.hpp"

#include <sstream>

string genTestCode(struct TestCode *code, string filename) {
    
    return "\tif (("+code->content+"))\n"
    + "\t\tprintf(\"Success on line " + to_string(code->lineNum) + " in " + filename + "\\n\");\n"
    + "\telse\n"
    + "\t\tprintf(\"Error on line " + to_string(code->lineNum) + " in " + filename + "\\n\");\n"
    ;
}

string genTestCase(struct TestCase *c, string prefix, string setup, string filename) {
    string allSetup = setup;
    //Generate setup
    for (auto it = c->setup.begin(); it != c->setup.end(); it++) {
        allSetup += "\t" + *it + "\n";
    }
    //Generate the test function
    string name = prefix;
    if (name.size() > 0) name += "_";
    name += c->name;
    string result = "void TestCase_"+name+"(){\n";
    result += "\t//Setup\n"+allSetup;
    for (auto it = c->codes.begin(); it != c->codes.end(); it++) {
        result += "\n\t//Code";
        //Call test case
        result += "\n" + genTestCode(*it, filename);
        
    }
    result += "}\n";
    return result;
}

string genTestSection(struct TestSection *section, string prefix, string setup, string filename) {
    string result;
    string allSetup = setup;
    vector<string> funcCall;
    
    string name = prefix;
    if (name.size() > 0) name += "_";
    name += section->name;
    
    //Generate setup
    for (auto it = section->setup.begin(); it != section->setup.end(); it++) {
        allSetup += "\t"+*it + "\n";
    }
    //Generate case
    for (auto it = section->cases.begin(); it != section->cases.end(); it++) {
        result += "\n"+genTestCase(it->second, name, allSetup, filename)+"\n";
        funcCall.push_back("\tTestCase_"+name+"_"+it->second->name+"();\n");
    }
    //Generate subSection
    for (auto it = section->subSection.begin(); it != section->subSection.end(); it++) {
        result += "\n"+genTestSection(it->second, name, allSetup, filename)+"\n";
        funcCall.push_back("\tTestSection_"+name+"_"+it->second->name+"();\n");
    }
    //Generate the test function
    result += "void TestSection_"+name+"(){\n";
    for (auto it = funcCall.begin(); it != funcCall.end(); it++) {
        
        //Call test case
        result += *it;
        
    }
    result += "}\n";
    return result;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    vector<string> testName;
    
    for (int i = 1; i < argc; i++) {
        //The last item must be the filename
        
        const char *filename = argv[i];
        
        FILE *input = fopen(filename, "r");
        yyin = input;
        
        initSection(filename);
        
        int parseRes = yyparse();
        
        if (parseRes == 0) {
            {
                //Write the main code section
                string newFileName = "compile_";
                newFileName += filename;
                FILE *input = fopen(newFileName.c_str(), "w");
                fwrite(code.c_str(), sizeof(char), code.length(), input);
                fclose(input);
            }
            {
                //Add the test
                testName.push_back("TestSection_"+rootSection->name);
                //Write the test file
                string newFileName = "test_";
                newFileName += filename;
                FILE *input = fopen(newFileName.c_str(), "w");
                fwrite(code.c_str(), sizeof(char), code.length(), input);
                
                {
                    //Add the test cases
                    string testSection = genTestSection(rootSection, "", "", filename);
                    fwrite(testSection.c_str(), sizeof(char), testSection.size(), input);
                }
                
                fclose(input);
            }
        }
    }
    
    FILE *testMain = fopen("test.c", "w");
    string result = "//Declartion\n";
    for (auto it = testName.begin(); it != testName.end(); it++) {
        result += "void "+*it+"();\n";
    }
    result += "\n\n//Test\n";
    result += "int main() {\n";
    for (auto it = testName.begin(); it != testName.end(); it++) {
        result += "\t"+*it+"();\n";
    }
    result += "}";
    fwrite(result.c_str(), sizeof(char), result.length(), testMain);
    fclose(testMain);
    
    return 0;
}
