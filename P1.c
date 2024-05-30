#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "front.h"

/* Global Variable */
int nextToken;

/* Local Variables */
static int charClass;
static char lexeme[100];
static char nextChar;
static int lexLen;
static FILE *in_fp;

/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();
void TokenOutput();

/* Function to print token code as a string */



/* main driver */
int main(int argc, char *argv[]) {
    /* Open the input data file and process its contents */
    /*Modified from original*/
    char *file = argv[1];
    printf("DCooke Parser :: R11787304\n");
    if ((in_fp = fopen(file, "r")) != NULL) {
        getChar();
            do {
                lex();
                //expr();
            } while (nextToken != EOF );

    } else {
        printf("ERROR - cannot open file \n");

    }

    return 0;
}


/* lookup - a function to lookup operators and parentheses and return the token */
/*Modified from original*/
static int lookup(char ch) {
    switch (ch) {
        case '(':
            addChar();
            return LEFT_PAREN;
            break;
        case ')':
            addChar();
            return RIGHT_PAREN;
            break;
        case '+':
            addChar();
            getChar();
            if(nextChar == '+'){
                addChar();
                return INC_OP;
            }
            else if(nextChar == '-'){
                addChar();
                return UNKNOWN;

            }
            fseek(in_fp,-1,SEEK_CUR);
            return ADD_OP;
            break;
        case '-':
            addChar();
            getChar();
            if(nextChar == '-'){
                addChar();
                return  DEC_OP;
            }
            else if(nextChar == '+'){
                addChar();
                return UNKNOWN;
            }
            fseek(in_fp,-1,SEEK_CUR);
            return SUB_OP;
            break;
        case '*':
            addChar();
            return MULT_OP;
            break;
        case '/':
            addChar();
            return DIV_OP;
            break;
        case '\0':
            addChar();
            return EOF;
            break;

        case '<':
            addChar();
            getChar();

            if(nextChar == '>'){
                addChar();
                return NEQUAL_OP;

            }
            else if(nextChar == '='){
                addChar();
                return LEQUAL_OP;

            }
            fseek(in_fp,-1,SEEK_CUR);
            return LESSER_OP;
            break;

        case '>':
            addChar();
            getChar();

            if(nextChar == '='){
                addChar();
                return GEQUAL_OP;

            }
            fseek(in_fp,-1,SEEK_CUR);
            return GREATER_OP;
            break;
        case '%':
            addChar();
            return MOD_OP;
            break;
        case ';':
            addChar();
            return SEMICOLON;
            break;
        case ':':
            addChar();
            getChar();
            if(nextChar == '='){
                addChar();
                return ASSIGN_OP;
            }  else{
                fseek(in_fp,-1,SEEK_CUR);
                return COLON;
                }
            break;
        case '=':
            addChar();
            return EQUAL_OP;
            break;
        default:
            addChar();
            return UNKNOWN;
            break;
    }

    return nextToken;
}


/* addChar - a function to add nextChar to lexeme */
static void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;

    }
      else
    {
        printf("Error - lexeme is too long \n");
    }
}

/* getChar - a function to get the next character of input and determine its character class */
static void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
}

/* getNonBlank - a function to call getChar until it returns a non-whitespace character */
static void getNonBlank() {
    while (isspace(nextChar)) getChar();
}

/* lex - a simple lexical analyzer for arithmetic expressions */
// Been Modified
int lex() {
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
        /* Parse identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER) {
                addChar();
                getChar();
           }
            if(strcmp(lexeme,"read")==0){
                nextToken = KEY_READ;
            }
            else if(strcmp(lexeme,"if")==0){
                nextToken = KEY_IF;
            }
            else if(strcmp(lexeme,"fi")==0){
                nextToken = KEY_FI;
            }
            else if(strcmp(lexeme,"else")==0){
                nextToken = KEY_ELSE;
            }
            else if(strcmp(lexeme,"then")==0){
                nextToken = KEY_THEN;
            }
            else if(strcmp(lexeme,"write")==0){
            nextToken = KEY_WRITE;
            }

            else{
                nextToken = IDENT;
            }

            break;

        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        /* Parentheses and operators */
        case UNKNOWN:
            nextToken = lookup(nextChar);
            getChar();
            break;

        /* EOF */
        case EOF:
            nextToken = EOF;
            return EOF;
            break;
    }



    printf("%s",lexeme);
    TokenOutput(nextToken);
    printf("\n");
    return nextToken;
}





// Added to code
void TokenOutput(int nextToken) {
    switch (nextToken) {
        case INT_LIT:
            printf( "\t\tINT_LIT");
            break;
        case IDENT:
            printf("\t\tIDENT");
            break;
        case ASSIGN_OP:
            printf("\t\tASSIGN_OP");
            break;
        case ADD_OP:
            printf("\t\tADD_OP");
            break;
        case SUB_OP:
            printf("\t\tSUB_OP");
            break;
        case MULT_OP:
            printf("\t\tMULT_OP");
            break;
        case DIV_OP:
            printf("\t\tDIV_OP");
            break;
        case LEFT_PAREN:
            printf("\t\tLEFT_PAREN");
            break;
        case RIGHT_PAREN:
            printf("\t\tRIGHT_PAREN");
            break;
        case EOF:
            break;
        case KEY_READ:
            printf("\t\tKEY_READ");
            break;
        case LESSER_OP:
            printf("\t\tLESSER_OP");
            break;
        case GREATER_OP:
            printf("\t\tGREATER_OP");
            break;
        case EQUAL_OP:
            printf("\t\tEQUAL_OP");
            break;
        case KEY_WRITE:
            printf("\t\tKEY_WRITE");
            break;
        case COLON:
            printf("\t\tCOLON");
            break;
        case SEMICOLON:
            printf("\t\tSEMICOLON");
            break;
        case MOD_OP:
            printf("\t\tMOD_OP");
            break;
        case KEY_ELSE:
            printf("\t\tKEY_ELSE");
            break;
        case KEY_THEN:
            printf("\t\tKEY_THEN");
            break;
        case KEY_IF:
            printf("\t\tKEY_IF");
            break;
        case KEY_FI:
            printf("\t\tKEY_FI");
            break;
        case DEC_OP:
            printf("\t\tDEC_OP");
            break;
        case INC_OP:
            printf("\t\tINC_OP");
            break;
        case NEQUAL_OP:
            printf("\t\tNEQUAL_OP");
            break;
        case LEQUAL_OP:
            printf("\t\tLEQUAL_OP");
            break;
        case GEQUAL_OP:
            printf("\t\tGEQUAL_OP");
            break;
        default:
            printf("\t\tUNKNOWN");
            break;
    }
}