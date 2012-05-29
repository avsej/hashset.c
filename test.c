#include <stdio.h>
#include <assert.h>
#include "hashset.h"

static void trivial(void)
{
    char *missing = "missing";
    char *items[] = {"zero", "one", "two", "three", NULL};
    char *foo = "foo";
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

    assert(hashset_remove(set, items[1]) == 1);
    assert(hashset_num_items(set) == 3);
    assert(hashset_remove(set, items[1]) == 0);

    assert(hashset_add(set, foo) == 1);
    assert(hashset_add(set, foo) == 0);

    hashset_destroy(set);
}

static void test_gaps(void)
{
    hashset_t set = hashset_create();

    /* fill the hashset */
    hashset_add(set, (void *)0xbabe);
    hashset_add(set, (void *)0xbeef);
    hashset_add(set, (void *)0xbad);
    hashset_add(set, (void *)0xf00d);
    /* 0xf00d (nil) (nil) (nil) (nil) 0xbad 0xbabe 0xbeef */

    /* make a gap */
    hashset_remove(set, (void *)0xbeef);
    /* 0xf00d (nil) (nil) (nil) (nil) 0xbad 0xbabe 0x1 */

    /* check that 0xf00d is still reachable */
    assert(hashset_is_member(set, (void *)0xf00d));

    /* add 0xbeef back */
    hashset_add(set, (void *)0xbeef);
    /* 0xf00d (nil) (nil) (nil) (nil) 0xbad 0xbabe 0xbeef */

    /* verify */
    assert(hashset_is_member(set, (void *)0xbeef));
    assert(hashset_is_member(set, (void *)0xf00d));
}

static void test_exceptions(void)
{
    hashset_t set = hashset_create();

    assert(hashset_add(set, (void *)0) == -1);
    assert(hashset_add(set, (void *)1) == -1);
}

static void test_rehashing_items_placed_beyond_nitems(void)
{
    hashset_t set = hashset_create();

    assert(hashset_add(set, (void *)20644128) == 1);
    assert(hashset_add(set, (void *)21747760) == 1);
    assert(hashset_add(set, (void *)17204864) == 1);
    assert(hashset_add(set, (void *)22937440) == 1);
    assert(hashset_add(set, (void *)14734272) == 1);
    assert(hashset_add(set, (void *)13948320) == 1);
    assert(hashset_add(set, (void *)18116496) == 1);
    assert(hashset_add(set, (void *)18229952) == 1);
    assert(hashset_add(set, (void *)20390128) == 1);
    assert(hashset_add(set, (void *)23523264) == 1);
    assert(hashset_add(set, (void *)22866784) == 1);
    assert(hashset_add(set, (void *)17501248) == 1);
    assert(hashset_add(set, (void *)17168832) == 1);
    assert(hashset_add(set, (void *)13389824) == 1);
    assert(hashset_add(set, (void *)15795136) == 1);
    assert(hashset_add(set, (void *)15154464) == 1);
    assert(hashset_add(set, (void *)22507840) == 1);
    assert(hashset_add(set, (void *)22977920) == 1);
    assert(hashset_add(set, (void *)20527584) == 1);
    assert(hashset_add(set, (void *)21557872) == 1);
    assert(hashset_add(set, (void *)23089952) == 1);
    assert(hashset_add(set, (void *)21606240) == 1);
    assert(hashset_add(set, (void *)25168704) == 1);
    assert(hashset_add(set, (void *)25198096) == 1);
    assert(hashset_add(set, (void *)25248000) == 1);
    assert(hashset_add(set, (void *)25260976) == 1);
    assert(hashset_add(set, (void *)25905520) == 1);
    assert(hashset_add(set, (void *)25934608) == 1);
    assert(hashset_add(set, (void *)26015264) == 1);
    assert(hashset_add(set, (void *)26044352) == 1);
    assert(hashset_add(set, (void *)24784800) == 1);
    assert(hashset_add(set, (void *)24813888) == 1);
    assert(hashset_add(set, (void *)24663936) == 1);
    assert(hashset_add(set, (void *)24693536) == 1);
    assert(hashset_add(set, (void *)24743792) == 1);
    assert(hashset_add(set, (void *)24756480) == 1);

    assert(hashset_is_member(set, (void *)20644128) == 1);
    assert(hashset_is_member(set, (void *)21747760) == 1);
    assert(hashset_is_member(set, (void *)17204864) == 1);
    assert(hashset_is_member(set, (void *)22937440) == 1);
    assert(hashset_is_member(set, (void *)14734272) == 1);
    assert(hashset_is_member(set, (void *)13948320) == 1);
    assert(hashset_is_member(set, (void *)18116496) == 1);
    assert(hashset_is_member(set, (void *)18229952) == 1);
    assert(hashset_is_member(set, (void *)20390128) == 1);
    assert(hashset_is_member(set, (void *)23523264) == 1);
    assert(hashset_is_member(set, (void *)22866784) == 1);
    assert(hashset_is_member(set, (void *)17501248) == 1);
    assert(hashset_is_member(set, (void *)17168832) == 1);
    assert(hashset_is_member(set, (void *)13389824) == 1);
    assert(hashset_is_member(set, (void *)15795136) == 1);
    assert(hashset_is_member(set, (void *)15154464) == 1);
    assert(hashset_is_member(set, (void *)22507840) == 1);
    assert(hashset_is_member(set, (void *)22977920) == 1);
    assert(hashset_is_member(set, (void *)20527584) == 1);
    assert(hashset_is_member(set, (void *)21557872) == 1);
    assert(hashset_is_member(set, (void *)23089952) == 1);
    assert(hashset_is_member(set, (void *)21606240) == 1);
    assert(hashset_is_member(set, (void *)25168704) == 1);
    assert(hashset_is_member(set, (void *)25198096) == 1);
    assert(hashset_is_member(set, (void *)25248000) == 1);
    assert(hashset_is_member(set, (void *)25260976) == 1);
    assert(hashset_is_member(set, (void *)25905520) == 1);
    assert(hashset_is_member(set, (void *)25934608) == 1);
    assert(hashset_is_member(set, (void *)26015264) == 1);
    assert(hashset_is_member(set, (void *)26044352) == 1);
    assert(hashset_is_member(set, (void *)24784800) == 1);
    assert(hashset_is_member(set, (void *)24813888) == 1);
    assert(hashset_is_member(set, (void *)24663936) == 1);
    assert(hashset_is_member(set, (void *)24693536) == 1);
    assert(hashset_is_member(set, (void *)24743792) == 1);
    assert(hashset_is_member(set, (void *)24756480) == 1);
}

int main(int argc, char *argv[])
{
    trivial();
    test_gaps();
    test_exceptions();
    test_rehashing_items_placed_beyond_nitems();

    (void)argc;
    (void)argv;
    return 0;
}
