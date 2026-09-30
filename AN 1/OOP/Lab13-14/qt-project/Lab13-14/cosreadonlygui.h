#ifndef COSREADONLYGUI_H
#define COSREADONLYGUI_H

#include <QWidget>
#include <vector>

#include "observer.h"
#include "service.h"

class CosReadOnlyGUI : public QWidget, public Observer {
public:
    explicit CosReadOnlyGUI(Service& service, QWidget* parent = nullptr);
    ~CosReadOnlyGUI() override;

    void update() override;
    void paintEvent(QPaintEvent* ev) override;

private:
    Service& service;
    std::vector<QPoint> puncte;

    void regenereazaPuncte();
};

#endif // COSREADONLYGUI_H
