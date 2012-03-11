#include <stdio.h>
#include <assert.h>
#include "hashset.h"

static void trivial(void)
{
	char *missing = "missing";
	char *items[] = {"zero", "one", "two", "three", NULL};
	size_t ii, nitems = 4;
	hashset_t set = hashset_create();

	if (set == NULL) {
		fprintf(stderr, "failed to create hashset instance\n");
		abort();
	}

	for (ii = 0; ii < nitems; ++ii) {
		hashset_add(set, items[ii]);
	}

	for (ii = 0; ii < nitems; ++ii) {
		assert(hashset_is_member(set, items[ii]));
	}
	assert(hashset_is_member(set, missing) == 0);

	hashset_destroy(set);
}

int main(int argc, char *argv[])
{
	trivial();

	(void)argc;
	(void)argv;
	return 0;
}

