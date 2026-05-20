#include "../include/error.h"

AppError::AppError(const std::string& mesaj)
    : std::runtime_error(mesaj) {
}
