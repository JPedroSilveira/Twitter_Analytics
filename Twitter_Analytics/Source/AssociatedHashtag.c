#include "../Header/AssociatedHashtag.h"

AssociatedHashtag* AssociatedHashtag_New() {
	AssociatedHashtag* aHashtag = (AssociatedHashtag*)malloc(sizeof(AssociatedHashtag));
	aHashtag->count = 0;

	return aHashtag;
}