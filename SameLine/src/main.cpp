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

typedef enum {
    languageType_C,
    languageType_CPP,
    languageType_Obj_C,
    languageType_Obj_CPP,
    languageType_JS,
    languageType_Swift,
    languageType_Unknown,
} languageType;

//Javascript only
string JS_headerLv(int indentLv) {
    return "h"+to_string(indentLv+2);
}

string filenameAppend(string original, string tag) {
    size_t found = original.rfind("/");
    if (found == string::npos) {
        //Not found
        return tag+original;
    } else {
        return string(original, 0, found+1) + tag + string(original, found+1);
    }
}

string filenameStrip(string original) {
    size_t found = original.rfind("/");
    if (found == string::npos) {
        //Not found
        return original;
    } else {
        return string(original, found+1);
    }
}

string directotyStrip(string original) {
    size_t found = original.rfind("/");
    if (found == string::npos) {
        //Not found
        return "";
    } else {
        return string(original, 0, found+1);
    }
}

//String operation
string operator *(string source, unsigned int time) {
    string result;
    for (int i = 0; i < time; i++) {
        result += source;
    }
    return result;
}

//Language specific
languageType extToLang(string extension) {
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    if (extension == "c")
        return languageType_C;
    if (extension == "cpp")
        return languageType_CPP;
    if (extension == "m")
        return languageType_Obj_C;
    if (extension == "mm")
        return languageType_Obj_CPP;
    if (extension == "js")
        return languageType_JS;
    if (extension == "swift")
        return languageType_Swift;
    return languageType_Unknown;
}

string langToExt(languageType type) {
    switch (type) {
        case languageType_C:
            return "c";
        case languageType_CPP:
            return "cpp";
        case languageType_Obj_C:
            return "m";
        case languageType_Obj_CPP:
            return "mm";
        case languageType_JS:
            return "js";
        case languageType_Swift:
            return "swift";
        default:
            return "";
    }
}

string langToMainExt(languageType type) {
    switch (type) {
        case languageType_C:
            return "c";
        case languageType_CPP:
            return "cpp";
        case languageType_Obj_C:
            return "m";
        case languageType_Obj_CPP:
            return "mm";
        case languageType_JS:
            return "html";
        case languageType_Swift:
            return "swift";
        default:
            return "";
    }
}

string funcBody(languageType type, string funcName, string funcBody, string returnType) {
    string result;
    switch (type) {
        case languageType_C:
        case languageType_CPP:
        case languageType_Obj_C:
        case languageType_Obj_CPP:
            result = returnType+" "+funcName+"(){\n";
            result += funcBody;
            result += "}\n";
            break;
        case languageType_JS:
            result = "function " + funcName +"(){\n";
            result += funcBody;
            result += "}\n";
            break;
        case languageType_Swift:
            result = "func " + funcName + "(){\n";
            result += funcBody;
            result += "}\n";
            break;
        default:
            break;
    }
    return result;
}

string funcHeader(languageType type, string funcName) {
    string result;
    switch (type) {
        case languageType_C:
        case languageType_CPP:
        case languageType_Obj_C:
        case languageType_Obj_CPP:
            result = "void "+funcName+"();\n";
            break;
        case languageType_JS:
            result = "function " + funcName +"();\n";
            break;
        default:
            break;
    }
    return result;
}

string printRaw(languageType type, string content) {
    string result;
    switch (type) {
        case languageType_C:
        case languageType_CPP:
            result = "printf(\""+content+"\");";
            break;
        case languageType_Obj_C:
        case languageType_Obj_CPP:
            result = "NSLog(@\"" + content + "\");";
            break;
        case languageType_JS:
            result = "document.write(\""+content+"\");";
            break;
        case languageType_Swift:
            result = "print(\""+content+"\");";
            break;
        default:
            break;
    }
    return result+"\n";
}

string printLine(languageType type, int indentLv, string content) {
    switch (type) {
        case languageType_C:
        case languageType_CPP:
        case languageType_Obj_C:
        case languageType_Obj_CPP:
            content = string(indentLv, '\t')+content+"\\n";
            break;
        case languageType_Swift:
            content = string("\\t")*indentLv+content+"\\n";
            break;
        case languageType_JS:
            content = string("&emsp;")*indentLv+content+"<br>";
        default:
            break;
    }
    return printRaw(type, content);
}

string printHeader(languageType type, int indentLv, string headerName) {
    switch (type) {
        case languageType_JS:
            return printRaw(type, "<"+JS_headerLv(indentLv)+">"+string("&emsp;")*indentLv+headerName+"</"+JS_headerLv(indentLv)+">");
            break;
            
        default:
            return printLine(type, indentLv, headerName);
            break;
    }
}

string include(languageType type, string file) {
    switch (type) {
        case languageType_JS:
            return "<script src=\""+file+"\"> </script>";
            break;
        default:
            return "";
            break;
    }
}

string runFunc(languageType type, string funcName) {
    switch (type) {
        case languageType_Swift:
            return funcName+"()";
        default:
            return funcName+"();";
    }
}

string mainFunction(languageType type, vector<string>include, vector<string>lines) {
    switch (type) {
        case languageType_C:
        case languageType_CPP:
        case languageType_Obj_C:
        case languageType_Obj_CPP:
        {
            //Need main function
            string body = "";
            
            if (include.size())
                body += "//Declartion\n";
            for (auto it = include.begin(); it != include.end(); it++) {
                body += "\t" + *it + "\n";
            }
            
            if (lines.size())
                body += "//Test\n";
            for (auto it = lines.begin(); it != lines.end(); it++) {
                body += "\t" + *it + "\n";
            }
            return funcBody(type, "main", body, "int");
        }
            break;
        case languageType_JS: {
            string result = "<html>\n\t<head />\n\t<body>\n";
            
            if (include.size())
                result += "\t\t<!--Declartion-->\n";
            for (auto it = include.begin(); it != include.end(); it++) {
                result += "\t\t"+*it + "\n" ;
            }
            
            string body;
            if (lines.size())
                body += "\t\t\t//Test\n";
            for (auto it = lines.begin(); it != lines.end(); it++) {
                body += "\t\t\t"+*it+"\n";
            }
            result += "\t\t<script type=\"text/javascript\">\n"+body+"\t\t</script>\n";
            result += "\t</body>\n</html>";
            return result;
        }
        case languageType_Swift:
        {
            //No need for main function, just print it out
            string body = "";
            if (lines.size())
                body += "//Test\n";
            for (auto it = lines.begin(); it != lines.end(); it++) {
                body += *it + "\n";
            }
            return body;
        }
        default:
            return "";
            break;
    }
}

//Test generation
string genTestCode(struct TestCode *code, int indentLv, string filename, languageType type) {
    
    return "\tif (("+code->content+")) {\n"
    + "\t\t"+printLine(type, indentLv, "Success on line " + to_string(code->lineNum) + " in " + filename)
    + "\t} else {\n"
    + "\t\t"+printLine(type, indentLv, "Error on line " + to_string(code->lineNum) + " in " + filename) + "}\n"
    ;
}

string genTestCase(struct TestCase *c, int indentLevel, string prefix, string setup, string filename, languageType type) {
    string allSetup = setup;
    //Generate setup
    for (auto it = c->setup.begin(); it != c->setup.end(); it++) {
        allSetup += "\t" + *it + "\n";
    }
    //Generate the test function
    string name = prefix;
    if (name.size() > 0) name += "_";
    name += c->name;
    string body = "\t//Setup\n"+allSetup;
    
    //Print test name
    body += "\n\t" + printLine(type, indentLevel, "Test Case: "+c->name);
    
    for (auto it = c->codes.begin(); it != c->codes.end(); it++) {
        body += "\n\t//Code";
        //Call test case
        body += "\n" + genTestCode(*it, indentLevel+1, filename, type);
        
    }
    
    string result = funcBody(type, "TestCase_"+name, body, "void");
    
    return result;
}

string genTestSection(struct TestSection *section, int indentLevel, string prefix, string setup, string filename, languageType type) {
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
        result += "\n"+genTestCase(it->second, indentLevel+1, name, allSetup, filename, type)+"\n";
        funcCall.push_back("\tTestCase_"+name+"_"+it->second->name+"();\n");
    }
    //Generate subSection
    for (auto it = section->subSection.begin(); it != section->subSection.end(); it++) {
        result += "\n"+genTestSection(it->second, indentLevel+1, name, allSetup, filename, type)+"\n";
        funcCall.push_back("\tTestSection_"+name+"_"+it->second->name+"();\n");
    }
    //Generate the test function
    string body = "\t"+printHeader(type, indentLevel, section->name);
    for (auto it = funcCall.begin(); it != funcCall.end(); it++) {
        //Call test case
        body += *it;
        
    }
    
    string testFunc = funcBody(type, "TestSection_"+name, body, "void");
    result += testFunc;
    return result;
}
string genTestSection(struct TestSection *section, string prefix, string setup, string filename, languageType type) { return genTestSection(section, 0, prefix, setup, filename, type); }

int main(int argc, const char * argv[]) {
    // insert code here...
    
    vector<string> testName;
    
    languageType type;
    
    vector<string> testFilenames;
    
    for (int i = 1; i < argc; i++) {
        //The last item must be the filename
        
        const char *filename = argv[i];
        
        FILE *input = fopen(filename, "r");
        yyin = input;
        
        string fileNameStr = "";
        fileNameStr += filename;
        
        string extension = fileNameStr.substr(fileNameStr.rfind('.')+1);
        
        type = extToLang(extension);
        
        initSection( filenameStrip(filename) );
        
        int parseRes = yyparse();
        
        if (argc < 2) {
            printf("SameLine filePath....\n");
            exit(1);
        }
        
        if (parseRes == 0) {
            {
                //Write the main code section
                string newFileName = filenameAppend(filename, "stripped_");
                FILE *input = fopen(newFileName.c_str(), "w");
                fwrite(code.c_str(), sizeof(char), code.length(), input);
                fclose(input);
            }
            {
                //Add the test
                testName.push_back("TestSection_"+rootSection->name);
                //Write the test file
                string newFileName = filenameAppend(filename, "test_");
                FILE *input = fopen(newFileName.c_str(), "w");
                fwrite(code.c_str(), sizeof(char), code.length(), input);
                
                testFilenames.push_back(filenameStrip(newFileName));
                
                {
                    //Add the test cases
                    string testSection = genTestSection(rootSection, "", "", filename, type);
                    fwrite(testSection.c_str(), sizeof(char), testSection.size(), input);
                }
                
//                if (type == languageType_JS) {
//                    //Javascript
//                    string result;
//                    string body;
//                    for (auto it = testName.begin(); it != testName.end(); it++) {
//                        body += "\t"+*it+"();\n";
//                    }
//                    result += funcBody(type, "main", body, "int");
//                    
//                    fwrite(result.c_str(), sizeof(char), result.size(), input);
//                }
                
                fclose(input);
            }
        }
    }
    
    //C/C++, need a separate main function
    //First import the includes
    vector<string> includes;
    for (auto it = testFilenames.begin(); it != testFilenames.end(); it++) {
        string includeStmt = include(type, *it);
        if (includeStmt.length() > 0) includes.push_back(includeStmt);
    }
    //Then how to run
    vector<string> codes;
    for (auto it = testName.begin(); it != testName.end(); it++) {
        codes.push_back( runFunc(type, *it) );
    }
    
    string mainStr = mainFunction(type, includes, codes);
    FILE *testMain = fopen( (directotyStrip(string(argv[1]))+"test."+langToMainExt(type)).c_str(), "w");
    fwrite(mainStr.c_str(), sizeof(char), mainStr.length(), testMain);
    fclose(testMain);
    return 0;
    }
