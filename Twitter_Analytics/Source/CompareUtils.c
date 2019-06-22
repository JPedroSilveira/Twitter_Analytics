#include "../Header/CompareUtils.h"

int CompareUtils_maxInt(int a, int b) {
	return (a > b) ? a : b;
}

int CompareUtils_Int(int* a, int* b) {
	int A = *a;
	int B = *b;

	if (A > B) {
		return COMPARE_BIGGER;
	} else if (A == B) {
		return COMPARE_EQUAL;
	} else {
		return COMPARE_SMALLER;
	}
}

int CompareUtils_Char(char* a, char* b) {
	char A = *a;
	char B = *b;

	if (A > B) {
		return COMPARE_BIGGER;
	} else if (A == B) {
		return COMPARE_EQUAL;
	} else {
		return COMPARE_SMALLER;
	}
}

int CompareUtils_String(char* a, char* b) {
	int cmp = strcmp(a, b);
	if (cmp > 0) { //caso a > b
		return COMPARE_BIGGER;
	} else if (cmp < 0) { //caso a < b
		return COMPARE_SMALLER;
	} else { //caso a == b
		return COMPARE_EQUAL;
	}
}

int CompareUtils_UserByName(User* a, User* b) {
	return CompareUtils_String(a->name, b->name) * (-1); //Inverte para ordem de mais citadas e nomes menores (alfabética)
}

int CompareUtils_UserByTweetCount(User* a, User* b) {
	int result = CompareUtils_Int(&(a->tweetList->length), &(b->tweetList->length));
	if (result == COMPARE_EQUAL) {
		result = CompareUtils_String(a->name, b->name) * (-1); //Inverte para ordem de mais citadas e nomes menores (alfabética) 
	}

	return result;
}

int CompareUtils_UserByMentionCount(User* a, User* b) {
	int result = CompareUtils_Int(&(a->mentionTweetList->length), &(b->mentionTweetList->length));
	if (result == COMPARE_EQUAL) {
		result = CompareUtils_String(a->name, b->name) * (-1); //Inverte para ordem de mais citadas e nomes menores (alfabética) 
	}

	return result;
}

int CompareUtils_UserByRetweetCount(User* a, User* b) {
	int result = CompareUtils_Int(&(a->info.retweetCount), &(b->info.retweetCount));
	if (result == COMPARE_EQUAL) {
		result = CompareUtils_String(a->name, b->name) * (-1); //Inverte para ordem de mais citadas e nomes menores (alfabética) 
	}

	return result;
}

int CompareUtils_UserByEngagementCount(User* a, User* b) {
	int result = CompareUtils_Int(&(a->info.engagementCount), &(b->info.engagementCount));
	if (result == COMPARE_EQUAL) {
		result = CompareUtils_String(a->name, b->name) * (-1); //Inverte para ordem de mais citadas e nomes menores (alfabética) 
	}

	return result;
}

int CompareUtils_HashtagByTweetCount(Hashtag* a, Hashtag* b) {
	int result = CompareUtils_Int(&(a->tweetList->length), &(b->tweetList->length));
	if (result == COMPARE_EQUAL) {
		result = CompareUtils_String(a->name, b->name) * (-1); //Inverte para ordem de mais citadas e nomes menores (alfabética) 
	}
	
	return result;
}

int CompareUtils_HashtagByName(Hashtag* a, Hashtag* b) {
	return CompareUtils_String(a->name, b->name) * (-1); //Inverte para ordem de mais citadas e nomes menores (alfabética) 
}

int CompareUtils_TweetByReTweetCountAndText(Tweet* a, Tweet* b) {
	int result = CompareUtils_Int(&(a->likeCount), &(b->likeCount));
	if (result == COMPARE_EQUAL) {
		result = CompareUtils_String(a->text, b->text);
	}

	return result;
}

int CompareUtils_TweetByText(Tweet* a, Tweet* b) {
	return CompareUtils_String(a->text, b->text);
}

