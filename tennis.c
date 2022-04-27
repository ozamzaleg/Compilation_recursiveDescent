#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* for exit() */
#include "tennis.h"

extern union _lexVal lexicalValue;
extern enum token yylex(void);

void match(int expectedToken)
{
    if (lookahead == expectedToken)
        lookahead = yylex();
    else
    {
        char e[100];
        sprintf(e, "error: expected token %s, found token %s",
                token_name(expectedToken), token_name(lookahead));
        errorMsg(e);
        exit(1);
    }
}

void parse()
{
    lookahead = yylex();
    start();
    if (lookahead != 0)
    {
        errorMsg("EOF expected");
        exit(1);
    }
}

void start()
{

    match(TITLE);
    struct player p = list_of_players();
    if (p.playerGender == -1)
    {
        printf("We don't have woman that win in Wimbledon\n");
    }
    else
    {
        printf("Woman with greatest number of wins at Wimbledon: %s (%d wins)\n",
               p.namePlayer, p.timesInWimbledon);
    }
}

struct player list_of_players()
{

    struct player maxWinsPlayer = {-1, "", -1};
    while (lookahead == NAME)
    {
        struct player p = player();
        if (p.playerGender == WOMAN)
            maxWinsPlayer = max_win(maxWinsPlayer, p);
    }
    return maxWinsPlayer;
}

struct player player()
{
    struct player p = {-1, "", -1};
    char name[MAX_SIZE];
    match(NAME);
    strcpy(p.namePlayer, lexicalValue.name);
    match(PLAYER_NAME);
    match(GENDER);
    p.playerGender = lexicalValue.typeGender;
    p.timesInWimbledon = optional_wimbledon();
    optional_australian_open();
    optional_french_open();
    return p;
}

int optional_wimbledon()
{
    int timesWins = 0;
    if (lookahead == WIMBLEDON)
    {
        match(WIMBLEDON);
        timesWins = list_of_years();
    }
    return timesWins;
}

int optional_australian_open()
{
    int timesWins = 0;
    if (lookahead == AUSTRALIAN_OPEN)
    {
        match(AUSTRALIAN_OPEN);
        timesWins = list_of_years();
    }
    return timesWins;
}

int optional_french_open()
{
    int timesWins = 0;
    if (lookahead == FRENCH_OPEN)
    {
        match(FRENCH_OPEN);
        timesWins = list_of_years();
    }
    return timesWins;
}

int list_of_years()
{
    int sumYears = 0;
    sumYears += year_spec();
    while (lookahead == ',')
    {
        match(',');
        sumYears += year_spec();
    }
    return sumYears;
}

int year_spec()
{
    int y2, y1;
    match(YEAR);
    y1 = lexicalValue.year;
    if (lookahead == '-')
    {
        match('-');
        match(YEAR);
        y2 = lexicalValue.year;
        return calculateYears(y1, y2);
    }
    return 1;
}

int main(int argc, char **argv)
{
    extern FILE *yyin;
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input-file-name>\n", argv[0]);
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if (yyin == NULL)
    {
        fprintf(stderr, "failed to open %s\n", argv[1]);
        return 2;
    }

    parse();

    fclose(yyin);
    return 0;
}

void errorMsg(const char *s)
{
    extern int yylineno;
    fprintf(stderr, "line %d: %s\n", yylineno, s);
}

int calculateYears(int year1, int year2)
{
    return (year2 - year1) + 1;
}

struct player max_win(struct player player1, struct player player2)
{
    return player1.timesInWimbledon >= player2.timesInWimbledon ? player1 : player2;
}
