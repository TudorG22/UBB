#include "repo.h"
#include "service.h"
#include "ui.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    bool useMap = false;
    bool useDate = false;

    for (int i = 1; i < argc; ++i) {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        const std::string arg = argv[i];
        if (arg == "--map") {
            useMap = true;
        } else if (arg == "--date") {
            useDate = true;
        }
    }

    if (useMap) {
        RepoMap repo;
        Service service(repo, 0);
        UI ui(service, "map", useDate);
        ui.run();
    } else {
        RepoVector repo;
        Service service(repo, 0);
        UI ui(service, "vector", useDate);
        ui.run();
    }
    return 0;
}
