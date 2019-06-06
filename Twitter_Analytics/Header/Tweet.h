#include <string.h>
#include "./List.h"

#define USER_NAME_LENGTH 20
#define TWEET_TEXT_LENGTH 140
#define HASHTAG_NAME_LENGTH 20

typedef struct s_userInfo {
	int tweetCount;
	int mentionCount;
	int retweetCount;
	int likeCount;
} UserInfo;

UserInfo UserInfo_New();

typedef struct s_User {
	char name[USER_NAME_LENGTH];
	List* tweetList;
	List* mentionTweetList;
	UserInfo info;
} User;

User* UserP_New();
User User_New();

typedef struct s_HashTag {
	char name[HASHTAG_NAME_LENGTH];
	List* tweetList;
	int tweetCount;
} Hashtag;

Hashtag* HashtagP_New();

typedef struct s_Tweet {
	User *creator;
	int reTweetCount;
	int likeCount;
	char text[TWEET_TEXT_LENGTH];
	List* mentionList; //Lista de User que um Tweet menciona
	List* hashtagList;
} Tweet;

Tweet* TweetP_New();

void opA(int qttHash, int qttCit); // Listar as hastags mais citadas em toda rede.
void opB(int userQtt);   // Listar os usu�rios que mais postam tweets.
void opC(int tweetsQtt); // Listar os tweets com maior n�mero de retweets.
void opD(int userQtt);   // Listar os usu�rios mais mencionados nos tweets.
void opE(int userQtt);   // Listar os usu�rios mais influentes (aquele que possui o maior n�mero de retweets.)
void opF(int userQtt);   // Listar os usu�rios mais engajados da rede. Engajamento � a intera��o do p�blico com as postagens do usu�rio e determina o alcance das postagens. O engajamento � contabilizado pela somat�rio da quantidade de intera��es dos tweets de um usu�rio, que inclui: gostar do tweet (like), quantidade de retweets e quantidade de men��es ao usu�rio.
