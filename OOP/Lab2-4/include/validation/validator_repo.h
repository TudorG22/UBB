#ifndef VALIDATOR_REPO_H
#define VALIDATOR_REPO_H

#include <stddef.h>

#include "repository/repo_cheltuieli.h"

/* Valideaza repoul
Input: repo
Output: 1 valid / 0 invalid
Pre conditii: -
Post conditii: -
*/
int valideaza_repo(const RepoCheltuieli* repo);

/* Valideaza indexul in repo
Input: repo, index
Output: 1 valid / 0 invalid
Pre conditii: repo initializat
Post conditii: -
*/
int valideaza_repo_index(const RepoCheltuieli* repo, size_t index);

#endif
