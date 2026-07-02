#include "studenttablemodel.h"

#include <QBrush>
#include <QColor>

int StudentTableModel::rowCount(const QModelIndex&) const {
    return int(studenti.size());
}

int StudentTableModel::columnCount(const QModelIndex&) const {
    return 4;
}

QVariant StudentTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
        return {};
    }

    Student stud = studenti[index.row()];

    if (role == Qt::BackgroundRole) {
        if (stud.getFacultate() == "info") {
            return QBrush(QColor(180, 220, 255));
        } else if (stud.getFacultate() == "mate") {
            return QBrush(QColor(255, 220, 180));
        } else if (stud.getFacultate() == "mateinfo") {
            return QBrush(QColor(220, 255, 180));
        } else if (stud.getFacultate() == "ai") {
            return QBrush(QColor(255, 200, 230));
        }
    }

    if (role == Qt::ForegroundRole) {
        return QBrush(QColor(0, 0, 0));
    }

    if (role != Qt::DisplayRole) {
        return {};
    }

    if (index.column() == 0) {
        return stud.getNrMatricol();
    } else if (index.column() == 1) {
        return QString::fromStdString(stud.getNume());
    } else if (index.column() == 2) {
        return stud.getVarsta();
    } else if (index.column() == 3) {
        return QString::fromStdString(stud.getFacultate());
    }

    return {};
}

QVariant StudentTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return {};
    }

    if (orientation != Qt::Horizontal) {
        return {};
    }

    if (section == 0) {
        return "NrMatricol";
    } else if (section == 1) {
        return "Nume";
    } else if (section == 2) {
        return "Varsta";
    } else if (section == 3) {
        return "Facultate";
    }

    return {};
}

void StudentTableModel::setStudents(const std::vector<Student>& studentiNoi) {
    beginResetModel();
    studenti = studentiNoi;
    endResetModel();
}
