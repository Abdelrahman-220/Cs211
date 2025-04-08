#include <iostream>
#include <sstream>
#include <cctype>
#include <string>

using namespace std;

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
#define END_OF_FILE -1

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

/* Global variables */
int charClass;
string lexeme;
char nextChar;
int lexLen;
int token;
int nextToken;
istringstream inStream; // Replacing file input with string stream for testing

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();
int lookup(char ch);

/******************************************************/
/* main driver */
int main() {
    // Load test input directly
    string input = "(sum + 47) / total";
    inStream.str(input);

    getChar();
    do {
        lex();
    } while (nextToken != END_OF_FILE);

    return 0;
}

/*****************************************************/
/* lookup - function to look up operators and parentheses */
int lookup(char ch) {
    switch (ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        default:
            addChar();
            nextToken = END_OF_FILE;
            break;
    }
    return nextToken;
}

/*****************************************************/
/* addChar - adds nextChar to lexeme */
void addChar() {
    if (lexeme.size() <= 98) {
        lexeme += nextChar;
    } else {
        cout << "Error - lexeme is too long" << endl;
    }
}

/*****************************************************/
/* getChar - gets the next character and sets charClass */
void getChar() {
    if (inStream.get(nextChar)) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    } else {
        charClass = END_OF_FILE;
    }
}

/*****************************************************/
/* getNonBlank - skips whitespace */
void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer */
int lex() {
    lexeme.clear();
    getNonBlank();

    switch (charClass) {
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = IDENT;
            break;

        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;

        case END_OF_FILE:
            nextToken = END_OF_FILE;
            lexeme = "EOF";
            break;
    }

    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}
