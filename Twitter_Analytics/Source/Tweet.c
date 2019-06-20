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
	User* user = (User*)malloc(sizeof(User));
	
	user->info = UserInfo_New();
	user->tweetList = List_New();
	user->mentionTweetList = List_New();

	return user;
}

User User_New()
{
	User user;

	user.info = UserInfo_New();

	return user;
}

Hashtag* HashtagP_New()
{
	Hashtag* hashtag = (Hashtag*)malloc(sizeof(Hashtag));
	hashtag->tweetList = List_New();
	hashtag->tweetCount = 0;

	return hashtag;
}

Tweet* TweetP_New()
{
	Tweet* tweet = (Tweet*)malloc(sizeof(Tweet));
	tweet->hashtagList = List_New();
	tweet->mentionList = List_New();
	tweet->likeCount = 0;
	tweet->reTweetCount = 0;

	return tweet;
}

void User_AddTweet(User* user, Tweet* tweet) {
	user->info.tweetCount = user->info.tweetCount + 1; //Incrementa um a quantidade de Tweets do usuario
	user->info.likeCount = user->info.likeCount + tweet->likeCount; //Incrementa o numero de likes que o usuario teve
	user->info.retweetCount = user->info.retweetCount + tweet->reTweetCount; //Incrementa o numero de reTweets do usuario
	List_Add(user->tweetList, tweet); //Adiciona o Tweet na lista de Tweets do usuario
}

