/*
 * hashset_itr.h
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
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
 */

#ifndef HASHSET_ITR_H_
#define HASHSET_ITR_H_

#include "hashset.h"

#ifdef __cplusplus
extern "C" {
#endif

struct hashset_itr_st {
  hashset_t set;
  size_t index;
};

typedef struct hashset_itr_st *hashset_itr_t;

/* create a hashset iterator, advances to first value is available*/
hashset_itr_t hashset_iterator(hashset_t set);

/* returns the value at the current index */
size_t hashset_iterator_value(hashset_itr_t itr);

/* return 1 is can advance, 0 otherwise */
int hashset_iterator_has_next(hashset_itr_t itr);

/*
 * check if iterator can advance, if so advances
 * returns current index if can advance and -1 otherwise
 */
int hashset_iterator_next(hashset_itr_t itr);

#endif /* HASHSET_ITR_H_ */

#ifdef __cplusplus
}
#endif
