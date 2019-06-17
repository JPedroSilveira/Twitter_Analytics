#include "../Header/Tweet.h"

//Funções inicializadoras das estruturas

UserInfo UserInfo_New()
{
	UserInfo userInfo;
	userInfo.likeCount = 0;
	userInfo.mentionCount = 0;
	userInfo.retweetCount = 0;
	userInfo.tweetCount = 0;

	return userInfo;
}

User* UserP_New()
{
	User* user = malloc(sizeof(User));
	
	user->info = UserInfo_New();
	user->tweetList = List_New();
	user->mentionTweetList = List_New();

	return user;
}

User User_New()
{
	User user;
	UserInfo userInfo;

	user.info = UserInfo_New();

	return user;
}

Hashtag* HashtagP_New()
{
	Hashtag* hashtag = malloc(sizeof(Hashtag)); 
	hashtag->tweetList = List_New();
	hashtag->tweetCount = 0;

	return hashtag;
}

Tweet* TweetP_New()
{
	Tweet* tweet = malloc(sizeof(Tweet));
	tweet->hashtagList = List_New();
	tweet->mentionList = List_New();
	tweet->likeCount = 0;
	tweet->reTweetCount = 0;

	return tweet;
}

