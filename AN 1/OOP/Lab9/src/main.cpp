#include "repo.h"
#include "service.h"
#include "ui.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    bool useMap = false;
    bool useDate = false;
    double errorRate = 0;

    for (int i = 1; i < argc; ++i) {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        const std::string arg = argv[i];
        if (arg == "--map") {
            useMap = true;
        } else if (arg == "--date") {
            useDate = true;
        } else {
            try {
                errorRate = std::stod(arg);
            } catch (const std::exception&) {
                throw UIError("Probabilitate invalida.");
            }
        }

        
    }

    if (useMap) {
        RepoMap repo;
        Service service(repo, errorRate);
        UI ui(service, "map", useDate);
        ui.run();
    } else {
        RepoVector repo;
        Service service(repo, errorRate);
        UI ui(service, "vector", useDate);
        ui.run();
    }
    return 0;
}
