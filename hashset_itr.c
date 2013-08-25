/*
 * hashset_itr.c
 *
 *   Copyright 2012 Couchbase, Inc.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#include <assert.h>
#include <stdio.h>
#include "hashset_itr.h"

hashset_itr_t hashset_iterator(hashset_t set)
{
  hashset_itr_t itr = calloc(1, sizeof(struct hashset_itr_st));
  if (itr == NULL)
    return NULL;

  itr->set = set;
  itr->index = 0;

  /* advance to the first item if one is present */
  if (set->nitems > 0)
    hashset_iterator_next(itr);

  return itr;
}

int hashset_iterator_has_next(hashset_itr_t itr)
{
  size_t index;

  /* empty or end of the set */
  if (itr->set->nitems == 0 || itr->index == itr->set->capacity - 1)
    return 0;

  /* peek to find another entry */
  index = itr->index;
  while(index <= itr->set->capacity -1)
  {
    size_t value = itr->set->items[index];
    if(value != 0)
      return 1;
  }

  /* Otherwise */
  return 0;

}

int hashset_iterator_next(hashset_itr_t itr)
{

  if(hashset_iterator_has_next(itr) == 0)
    return -1; /* Can't advance */

  itr->index++;

  while (itr->set->items[(itr->index)] == 0 && itr->index < itr->set->capacity) {
    itr->index++;
  }

  return itr->index;
}

size_t hashset_iterator_value(hashset_itr_t itr) {

  /* Check to verify we're not at a null value, this can happen if an iterator is created
   * before items are added to the set.
   */
  if(itr->set->items[itr->index] == 0)
  {
    hashset_iterator_next(itr);
  }

  return itr->set->items[itr->index];
}

