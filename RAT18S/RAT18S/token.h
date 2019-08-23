#pragma once
#ifndef TOKEN1_H
#define TOKEN1_H
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;



struct Token {

    char buffer[32];
    int typeToken;
    Token * next;
    Token(const char * dataToken = "N/A", int typeToken = 9, Token * nextToken = NULL, int buffSize = 0);

  
};

class listToken
{
private:
    int count = 0;
    Token *head, *tail;
    static const string typeNames[];
public:
    listToken()
    {
        head = NULL;
        tail = NULL;
    }
    string getTokenType(int token) const;
    void newtoken(const char * dataToken = "FAIL" , int typeToken = 0, int sizeToken = 0);
    
    void printTokens();
    void makeReal();
};
#endif