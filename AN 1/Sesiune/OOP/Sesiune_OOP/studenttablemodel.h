#ifndef STUDENTTABLEMODEL_H
#define STUDENTTABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>

#include "include/student.h"

class StudentTableModel : public QAbstractTableModel {
public:
    explicit StudentTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void setStudents(const std::vector<Student>& studentiNoi);

private:
    std::vector<Student> studenti;
};

#endif // STUDENTTABLEMODEL_H
