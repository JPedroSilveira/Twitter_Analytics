#include "../Header//AssociatedHashtag.h"

AssociatedHashTag* AssociatedHashTag_New() {
	AssociatedHashTag* aHashtag = (AssociatedHashTag*)malloc(sizeof(AssociatedHashTag));
	aHashtag->count = 0;

	return aHashtag;
}