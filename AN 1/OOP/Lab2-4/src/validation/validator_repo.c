#include "validation/validator_repo.h"

int valideaza_repo(const RepoCheltuieli* repo) {
    (void)repo;
    return 1;
}

int valideaza_repo_index(const RepoCheltuieli* repo, size_t index) {
    return index < repo_dimensiune(repo);
}
