#include "cosreadonlygui.h"

#include <QPainter>
#include <QRandomGenerator>

CosReadOnlyGUI::CosReadOnlyGUI(Service& service, QWidget* parent)
    : QWidget(parent), service(service) {
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::Window);
    service.addObserver(this);
    setWindowTitle("Cos Read Only");
    resize(500, 300);
    regenereazaPuncte();
}

CosReadOnlyGUI::~CosReadOnlyGUI() {
    service.removeObserver(this);
}

void CosReadOnlyGUI::update() {
    regenereazaPuncte();
    repaint();
}

void CosReadOnlyGUI::paintEvent(QPaintEvent* ev) {
    Q_UNUSED(ev);

    QPainter painter{this};
    painter.fillRect(rect(), Qt::white);
    painter.drawText(10, 20, "Filme in cos: " + QString::number(int(service.cosGetAll().size())));

    for (int i = 0; i < int(puncte.size()); ++i) {
        const int x = puncte[static_cast<std::size_t>(i)].x();
        const int y = puncte[static_cast<std::size_t>(i)].y();

        painter.setBrush(QColor::fromRgb(
            QRandomGenerator::global()->bounded(256),
            QRandomGenerator::global()->bounded(256),
            QRandomGenerator::global()->bounded(256)));
        painter.drawEllipse(x, y, 30, 30);
    }
}

void CosReadOnlyGUI::regenereazaPuncte() {
    puncte.clear();

    const int nrFilme = int(service.cosGetAll().size());
    const int latime = width() > 40 ? width() - 40 : 1;
    const int inaltime = height() > 60 ? height() - 60 : 1;

    for (int i = 0; i < nrFilme; ++i) {
        const int x = 10 + QRandomGenerator::global()->bounded(latime);
        const int y = 30 + QRandomGenerator::global()->bounded(inaltime);
        puncte.push_back(QPoint(x, y));
    }
}
