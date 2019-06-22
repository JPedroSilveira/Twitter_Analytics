#ifndef _TWEETH_
#define _TWEETH_

#include <string.h>
#include "./List.h"

#define USER_NAME_LENGTH 50
#define TWEET_TEXT_LENGTH 280
#define HASHTAG_NAME_LENGTH 50

typedef struct s_UserInfo {
	int retweetCount;
	int likeCount;
	int engagementCount;
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

//Funcoes compartilhadas
void User_AddTweet(User* user, Tweet* tweet);

#endif _TWEETH_