#include "ui/interfata_consola.h"

int main(void) {
    RepoCheltuieli repo = repo_creaza();
    ServiceCheltuieli service = service_creeaza(&repo);

    ruleaza_interfata(&service);

    repo_distruge(&repo);
    return 0;
}
