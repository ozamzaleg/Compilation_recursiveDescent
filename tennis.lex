%{
#include "tennis.h"

extern int atoi (const char *);
extern void exit(int);
union _lexVal lexicalValue; // semantic value of current token

%}
%option noyywrap
%option yylineno

%%

"** Winners **" {return TITLE;}

18[5-9][0-9]|19[0-9]{2}|[2-9][0-9]{3,} { lexicalValue.year = atoi(yytext); return YEAR;}

["`'][a-zA-Z]+(" "[a-zA-Z]+)*["`'] {
  if(yytext[0] == yytext[strlen(yytext)-1]){
    strcpy(lexicalValue.name,yytext+1); lexicalValue.name[strlen(lexicalValue.name)-1]='\0';return PLAYER_NAME;
  }else{
    sprintf(e, "Name must start with a character %c and end with the same character !!! ", yytext[0]);  
    errorMsg(e); 
    exit(1);
  }
  }

\<Woman\> {lexicalValue.typeGender = WOMAN; return GENDER; }

\<Man\> {lexicalValue.typeGender = MAN; return GENDER; }

\<name\> {return NAME;}

\<Wimbledon\> { return WIMBLEDON; }

\<Australian" "Open\> { return AUSTRALIAN_OPEN; }

\<French" "Open\>  { return FRENCH_OPEN; }

","  {return ',';}

"-" {return '-';}

[\t\n\r ]+   /* skip white space */

.          {
            sprintf(e, "unrecognized token %c", yytext[0]);  
            errorMsg(e);  
            exit(1);
           }

%%

/* useful for error messages */
char *token_name(enum token token)
{
    static char *names[] = {
         "EOF","TITLE","YEAR","GENDER","NAME","WIMBLEDON","AUSTRALIAN_OPEN",
         "FRENCH_OPEN","PLAYER_NAME"  };
         
    return token <= PLAYER_NAME ? names[token] : "unknown token";
}
