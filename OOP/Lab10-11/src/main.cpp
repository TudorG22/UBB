#include "repo.h"
#include "service.h"
#include "ui.h"

#include <string>

namespace {
constexpr int inceptionYear = 2010;
constexpr int titanicYear = 1997;
constexpr int gladiatorYear = 2000;
constexpr int interstellarYear = 2014;
constexpr int shrekYear = 2001;
}

int main(int argc, char* argv[]) {
    Repo repo;
    Service service(repo);
    
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    if (argc > 1 && std::string(argv[1]) == "--date") {
        service.serviceAdd("Inception", "SF", inceptionYear, "Leonardo DiCaprio");
        service.serviceAdd("Titanic", "Drama", titanicYear, "Leonardo DiCaprio");
        service.serviceAdd("Gladiator", "Actiune", gladiatorYear, "Russell Crowe");
        service.serviceAdd("Interstellar", "SF", interstellarYear, "Matthew McConaughey");
        service.serviceAdd("Shrek", "Animatie", shrekYear, "Mike Myers");
    }

    UI ui(service);
    ui.run();
    return 0;
}

