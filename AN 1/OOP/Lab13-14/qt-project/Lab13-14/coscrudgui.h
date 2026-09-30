#ifndef COSCRUDGUI_H
#define COSCRUDGUI_H

#include <QLabel>
#include <QTableView>
#include <QWidget>

#include "filmtablemodel.h"
#include "observer.h"
#include "service.h"

class CosCRUDGUI : public QWidget, public Observer {
public:
    explicit CosCRUDGUI(Service& service, QWidget* parent = nullptr);
    ~CosCRUDGUI() override;

    void update() override;

private:
    Service& service;
    QTableView* listaCos = nullptr;
    QLabel* labelMesaj = nullptr;
    FilmTableModel* modelCos = nullptr;

    void initGui();
    void initConnect();
    void reloadList();
    void setMessage(const QString& mesaj);
};

#endif // COSCRUDGUI_H
