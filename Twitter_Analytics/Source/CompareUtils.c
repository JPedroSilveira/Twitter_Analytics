#include "../Header/CompareUtils.h"

int CompareUtils_maxInt(int a, int b) {
	return (a > b) ? a : b;
}

int CompareUtils_Int(void* a, void* b) {
	int A = *((int*)a);
	int B = *((int*)b);

	if (A > B) {
		return COMPARE_BIGGER;
	} else if (A == B) {
		return COMPARE_EQUAL;
	} else {
		return COMPARE_SMALLER;
	}
}

int CompareUtils_Char(void* a, void* b) {
	char A = *((char*)a);
	char B = *((char*)b);

	if (A > B) {
		return COMPARE_BIGGER;
	} else if (A == B) {
		return COMPARE_EQUAL;
	} else {
		return COMPARE_SMALLER;
	}
}

int CompareUtils_String(void* a, void* b) {
	char* A = (char*)a;
	char* B = (char*)b;
	int cmp = strcmp(A, B);
	if (cmp > 0) { //caso a > b
		return COMPARE_BIGGER;
	} else if (cmp < 0) { //caso a < b
		return COMPARE_SMALLER;
	} else { //caso a == b
		return COMPARE_EQUAL;
	}
}

int CompareUtils_UserByName(User* a, User* b) {
	return CompareUtils_String(a->name, b->name);
}

int CompareUtils_HashtagByTweetCount(Hashtag* a, Hashtag* b) {
	int result = CompareUtils_Int(a->tweetCount, b->tweetCount);
	if (result == COMPARE_EQUAL) {
		return CompareUtils_String(a->name, b->name);
	}
}

int CompareUtils_TweetByReTweetCountAndText(Tweet* a, Tweet* b) {
	int result = CompareUtils_Int(&(a->likeCount), &(b->likeCount));
	if (result == COMPARE_EQUAL) {
		return CompareUtils_String(a->text, b->text);
	}
}
