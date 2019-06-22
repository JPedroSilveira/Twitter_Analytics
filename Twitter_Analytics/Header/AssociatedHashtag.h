#ifndef _ASSOCIATEDHASHTAGH_
#define _ASSOCIATEDHASHTAGH_

#define ASSOCIATED_HASHTAG_NAME_LENGTH 50
#define ASSOCIATED_COMPARE_BIGGER 1
#define ASSOCIATED_COMPARE_SMALLER -1
#define ASSOCIATED_COMPARE_EQUAL 0

typedef struct s_AssociatedHashtag {
	char name[ASSOCIATED_HASHTAG_NAME_LENGTH];
	int count;
} AssociatedHashTag;

AssociatedHashTag* AssociatedHashTag_New();

#endif _ASSOCIATEDHASHTAGH_