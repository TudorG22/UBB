#include "filmtablemodel.h"

int FilmTableModel::rowCount(const QModelIndex&) const {
    return int(filme.size());
}

int FilmTableModel::columnCount(const QModelIndex&) const {
    return 4;
}

QVariant FilmTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }

    const auto& film = filme[index.row()];

    if (index.column() == 0) {
        return QString::fromStdString(film.getTitlu());
    } else if (index.column() == 1) {
        return QString::fromStdString(film.getGen());
    } else if (index.column() == 2) {
        return film.getAn();
    } else if (index.column() == 3) {
        return QString::fromStdString(film.getActor());
    }

    return {};
}

QVariant FilmTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return {};
    }

    if (orientation != Qt::Horizontal) {
        return {};
    }

    if (section == 0) {
        return "Titlu";
    } else if (section == 1) {
        return "Gen";
    } else if (section == 2) {
        return "An";
    } else if (section == 3) {
        return "Actor";
    }

    return {};
}

void FilmTableModel::setFilme(const std::vector<Film>& filmeNoi) {
    beginResetModel();
    filme = filmeNoi;
    endResetModel();
}
