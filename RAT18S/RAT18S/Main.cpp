//
//  main.cpp
//  lexar
//


#include <iostream>
#include <fstream>
#include <string.h>
#include <array>
#include <iomanip>
#include <stdio.h>
#include <ctype.h>
#include "token.h"

using namespace std;

int isKey(char  buffer[]) {

    char keywords[62][10] = { "if","int","else","endif","while","return","get",
        "put", "print", "scan", "assign","bool", "break","case","catch","char","class",
		"const","delete","do","double","false","true","float", "for","unsigned","using","friend",
		"long","namespace","new","private","public","void","return","short","signed","sizeof","static",
		"struct","switch","this","continue","default","cast","enum","dynamic","extern","union","goto","inline",
		"mutable","virtual","operator","protected","register","Volitile","template","throw","try","typedef","typeid"}; // set of key words to choose from
    int i, flag = 0;
    for (i = 0; i < 62; i++) {

        if (strcmp(buffer,keywords[i]) == 0) { // if word buffer matches keyword return true

            flag = 1;
            break;
        }
    }
    return flag; // default return false
};

int isOperator(const char * ch) {
    char op[] = "+-*/%=&<>#$-:?@^`~!_"; //set of operators to choose from

    int i, flag = 0;
    for (i = 0; i < 20; i++) {
        if (op[i] == *ch) { // if ch matches operator return true

            flag = 1;
            break;
        }
    }
    return flag; //default return false
};

int isSeparator(const char * ch) {
	char separator[] = "()[];|%,'{}";
    int i, flag = 0;
    for (i = 0; i < 11; i++) {

        if (separator[i] == *ch) {

            flag = 1;
            break;
        }
    }
    return flag;
};

int isInt(char buff[])
{
    int val, flag = 0;
    val = atoi(buff); // if conversion from string to int is valid 
                      //  return true else return 0
    if (val != 0)
    {
        flag = 1;
    }
    return flag; // default return false
};

int isIdentifier(char buff[], int buffsize)
{
    char keywords[11][10] = { "if","int","else","endif","while","return","get",
        "put", "print", "scan", "assign" };
    int i, flag = 0;
    if (buffsize >= 1) {
        for (i = 0; i < 11; i++) {
            if (strcmp(keywords[i], buff) != 0) { // if word buffer does not match keyword continue
                {
                    if (isalpha(buff[0]) && (isalpha(buff[buffsize - 1]) || (buff[buffsize - 1] == '$'))) {  // check if first character is a letter
                                                                                                       // and the last character is a letter or $ sign
                        for (int k = 1; k < buffsize - 1; k++)
                        {
                            if (!(isalpha(buff[k])) && !(isdigit(buff[k]))) // loop through the center of the identifier to check for numbers and letters
                            {
                                // not a valid identifier
                                return 0;
                            }
                        }
                        flag = 1; // is a valid identifier
                    }

                    return flag;

                }
            }
        }
    }
    return flag; // default return false


};

void lexer(listToken * list) {
	int isValid = 0, bufferSize = 0, temptype = 0, chartype = 0, EOS = 0;
	char c = '\t';
	char buffer[32] = { '/0' };
	listToken *Lexical = list;
	ifstream fin("test.txt");

	if (!fin.is_open())
	{
		cout << "Error: unable to open file." << endl;
	}
	else
	{
		while (!fin.eof())
		{
			if (isValid == 1) {                                          // TRIGGERED IF ISVALID FLAG CHECKED
				for (int i = 0; i < 32; i++) { buffer[i] = '\0'; }              // clears buffer array
				isValid = 0;
				bufferSize = 0;
				temptype = 0;
				chartype = 0;
				EOS = 0;           // RESET ALL FLAGS
			}

			if (fin.get(c))
			{
				if (c == '!') //checks to see if it's the start of a comment
				{
					EOS = 1;
					while (fin.get(c)) //loops until it sees the end of the comment
					{
						if (c == '!')
						{
							break;
						}
					}

				}
				if (isspace(c))
				{

					EOS = 1;
				}
				if (ispunct(c)) {
					if (c == '.')
					{
						chartype = 7;
						EOS = 1;
					}
					if (isOperator(&c) == 1) //operators set as 5
					{

						// now will make a token in the end
						// sets it as a operator type
						chartype = 5;            //create operator token
						EOS = 1;

					}
					else // sepatarators are set as 4
					{
						if (isSeparator(&c) == 1) {


							//create separator token
							// now will make a token in the end
							// sets it as a operator type
							chartype = 4;
							EOS = 1;



						}
					}
				}
				// INC THE BUFFER
				if (EOS == 1) {

					if (isInt(buffer) && temptype == 0)       // ints set as 2
					{

						temptype = 2;   // sets it as a operator type
										// now will make a token in the end
					}
					if (isKey(buffer) && temptype == 0)     //keys set as 3
					{

						temptype = 3;                                     //sets keyword type


					}
					if (isIdentifier(buffer, bufferSize) && temptype == 0)   //identifiers set as 1
					{

						temptype = 1;
						//create identifier token
					}
				}
				if (EOS == 1)                                      //IF END OF STRING TRIGGERED
				{
					// clears buffer and sets the 
					if (temptype == 0 && bufferSize >= 1) Lexical->newtoken(buffer, 0, bufferSize);
					if (bufferSize >= 1 && temptype != 0) Lexical->newtoken(buffer, temptype, bufferSize);                  //  sets the invalid token  
					if (chartype != 0 && !isspace(c)) Lexical->newtoken(&c, chartype, 1);
					c = ' ';
					isValid = 1;

				}
				else {
					buffer[bufferSize] = c;
					bufferSize++;
				}

			}


			// stores character into buffer

		}
	}

}



int main() {

	char pause;
	listToken Lexical;
	lexer(&Lexical);
   
    cout << "\nDATA         | LEXERME\n-----------------------\n";
    Lexical.printTokens();
    cout << "\n\nEnter anykey to continue...\n>";
    cin >> pause;
    return 0;
    }
