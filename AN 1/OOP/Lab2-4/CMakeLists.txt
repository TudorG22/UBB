cmake_minimum_required(VERSION 3.16)
project(BugetFamilie C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

set(FISIERE_CORE
    src/domain/cheltuiala.c
    src/repository/repo_cheltuieli.c
    src/service/service_cheltuieli.c
    src/validation/validator_domain.c
    src/validation/validator_repo.c
    src/validation/validator_service.c
    src/utils/vector_dinamic.c
)

set(FISIERE_APLICATIE
    src/main.c
    src/ui/interfata_consola.c
    ${FISIERE_CORE}
)

add_executable(aplicatie_buget_familie ${FISIERE_APLICATIE})

set(FISIERE_TESTE_SURSE
    tests/test_main.c
    tests/test.c
)

add_executable(teste_buget_familie ${FISIERE_TESTE_SURSE} ${FISIERE_CORE})

# warning level 4
target_compile_options(aplicatie_buget_familie PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(teste_buget_familie PRIVATE -Wall -Wextra -Wpedantic)
