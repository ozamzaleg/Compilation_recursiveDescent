#ifndef TENNIS

char e[100];

enum sizeArr
{
    MAX_SIZE = 50
};

enum gender
{
    MAN,
    WOMAN
};
// yylex returns 0 when EOF is encountered
enum token
{
    TITLE = 1,
    YEAR,
    GENDER,
    NAME,
    WIMBLEDON,
    AUSTRALIAN_OPEN,
    FRENCH_OPEN,
    PLAYER_NAME
};

char *token_name(enum token token);

struct player
{
    int timesInWimbledon;
    char namePlayer[MAX_SIZE];
    int playerGender;
};

union _lexVal
{
    int year;
    char name[MAX_SIZE];
    int timesWins;
    enum gender typeGender;
    struct player _player;
};

int lookahead;
int calculateYears(int year1, int year2);
struct player max_win(struct player player1, struct player player2);

void errorMsg(const char *s);
void match(int expectedToken);
void parse();
void start();
struct player list_of_players();
struct player player();
int optional_wimbledon();
int optional_australian_open();
int optional_french_open();
int list_of_years();
int year_spec();

#endif
