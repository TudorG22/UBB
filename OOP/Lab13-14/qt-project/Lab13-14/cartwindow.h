#ifndef CARTWINDOW_H
#define CARTWINDOW_H

#include <QLabel>
#include <QTableWidget>
#include <QWidget>

#include "service.h"

class CartWindow : public QWidget {
public:
    explicit CartWindow(Service& service, QWidget* parent = nullptr);

    void reloadList();

private:
    Service& service;
    QTableWidget* listaCos = nullptr;
    QLabel* labelMesaj = nullptr;

    void initGui();
    void initConnect();
    void setMessage(const QString& mesaj);
};

#endif // CARTWINDOW_H
