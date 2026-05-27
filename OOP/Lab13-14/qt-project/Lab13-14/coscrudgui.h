#ifndef COSCRUDGUI_H
#define COSCRUDGUI_H

#include <QLabel>
#include <QTableWidget>
#include <QWidget>

#include "observer.h"
#include "service.h"

class CosCRUDGUI : public QWidget, public Observer {
public:
    explicit CosCRUDGUI(Service& service, QWidget* parent = nullptr);
    ~CosCRUDGUI() override;

    void update() override;

private:
    Service& service;
    QTableWidget* listaCos = nullptr;
    QLabel* labelMesaj = nullptr;

    void initGui();
    void initConnect();
    void reloadList();
    void setMessage(const QString& mesaj);
};

#endif // COSCRUDGUI_H
