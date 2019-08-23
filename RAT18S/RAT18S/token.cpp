#include "token.h"


const string listToken::typeNames[] = {"INVALID","Identifier","Integer","Keyword","Seperator","Operator","Real","DOT"};

string listToken::getTokenType(int token) const
{
    return typeNames[token];
}

void listToken::newtoken(const char * dataToken, int typeToken,int sizeofToken)

    {
        Token * temp = new Token (dataToken,typeToken, NULL,sizeofToken);
        strncpy_s(temp->buffer, dataToken, sizeofToken);
        temp->typeToken = typeToken;
        if (head == NULL)
        {
            head = temp;
            tail = temp;
            temp = NULL;
        }
        else
        {
            tail->next = temp;
            tail = temp;
        }


    }
void listToken::printTokens()
{
    makeReal();
    Token * temp = new Token;
    temp = head;
    while (temp != NULL)
    {
        cout << setw(10);
        cout << temp->buffer << "   |   " << getTokenType(temp->typeToken) << endl;
        temp = temp->next;
    }
}

void listToken::makeReal() {
    if (head != NULL && head->next != NULL && head->next->next != NULL) {

      
        Token *prev, *curr, *next;
        prev = head;
        curr = head->next;
        next = head->next->next;
        while (next != NULL) {

            if (curr->typeToken == 7 && next->typeToken == 2 && prev->typeToken == 2) {

                prev->typeToken = 6;
                prev->next = next->next;
                strcat_s(prev->buffer, curr->buffer);
                strcat_s(prev->buffer, next->buffer);
                delete curr;
                delete next;
                prev = head;
                curr = prev->next;
                next = prev->next->next;
				
            }
			if (curr->typeToken == 1 && next->typeToken == 5 && next->buffer[0] == '$') {
				strcat_s(curr->buffer, next->buffer);
				curr->next = next->next;
				delete next;
				prev = head;
				curr = prev->next;
				next = prev->next->next;
			}
            prev = curr;
            curr = next;
            next = next->next;

        }

    }
    

}

Token::Token(const char * dataToken, int TypeT, Token * nextToken,int bufferSize)
{
    strncpy_s(buffer, dataToken, bufferSize);
    typeToken = TypeT;
    next = nextToken;
 
}
