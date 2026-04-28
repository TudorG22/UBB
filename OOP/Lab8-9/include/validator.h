#pragma once

#include "domain.h"

#include <stdexcept>
#include <string>

class AppError : public std::runtime_error {
public:
    explicit AppError(const std::string& mesaj);
};

class ValidationError : public std::runtime_error {
public:
    explicit ValidationError(const std::string& mesaj);
};

class Validator {
public:
    static void valideazaFilm(const std::string& titlu, const std::string& gen, int an, const std::string& actor);
};
