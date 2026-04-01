#include "repo.h"
#include "service.h"
#include "ui_old.h"

#include <string>

int main(int argc, char* argv[]) {
    Repo repo;
    Service service(repo);

    if (argc > 1 && std::string(argv[1]) == "--date") {
        service.serviceAdd("Inception", "SF", 2010, "Leonardo DiCaprio");
        service.serviceAdd("Titanic", "Drama", 1997, "Leonardo DiCaprio");
        service.serviceAdd("Gladiator", "Actiune", 2000, "Russell Crowe");
        service.serviceAdd("Interstellar", "SF", 2014, "Matthew McConaughey");
        service.serviceAdd("Shrek", "Animatie", 2001, "Mike Myers");
    }

    UIOld ui(service);
    ui.run();
    return 0;
}
