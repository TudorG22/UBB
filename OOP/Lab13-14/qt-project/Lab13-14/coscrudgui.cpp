#include "coscrudgui.h"

#include <QHeaderView>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QVBoxLayout>

CosCRUDGUI::CosCRUDGUI(Service& service, QWidget* parent)
    : QWidget(parent), service(service) {
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::Window);
    service.addObserver(this);
    initGui();
    initConnect();
    reloadList();
    setMessage("Cos pregatit.");
}

CosCRUDGUI::~CosCRUDGUI() {
    service.removeObserver(this);
}

void CosCRUDGUI::update() {
    reloadList();
}

void CosCRUDGUI::initGui() {
    auto* mainLayout = new QVBoxLayout;
    auto* buttonLayout = new QHBoxLayout;

    auto* btnCartEmpty = new QPushButton("Goleste cos");
    auto* btnCartGenerate = new QPushButton("Genereaza cos");

    listaCos = new QTableWidget;
    labelMesaj = new QLabel;

    listaCos->setColumnCount(4);
    listaCos->setHorizontalHeaderLabels(QStringList{"Titlu", "Gen", "An", "Actor"});
    listaCos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listaCos->horizontalHeader()->setStretchLastSection(true);
    listaCos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    buttonLayout->addWidget(btnCartEmpty);
    buttonLayout->addWidget(btnCartGenerate);

    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(listaCos);
    mainLayout->addWidget(labelMesaj);

    setLayout(mainLayout);
    setWindowTitle("Cos CRUD");
    resize(600, 300);

    btnCartEmpty->setObjectName("btnCartEmpty");
    btnCartGenerate->setObjectName("btnCartGenerate");
}

void CosCRUDGUI::initConnect() {
    auto* btnCartEmpty = findChild<QPushButton*>("btnCartEmpty");
    auto* btnCartGenerate = findChild<QPushButton*>("btnCartGenerate");

    connect(btnCartEmpty, &QPushButton::clicked, this, [this]() {
        service.cosGoleste();
        setMessage("Cos golit.");
    });

    connect(btnCartGenerate, &QPushButton::clicked, this, [this]() {
        bool ok = false;
        const int numarFilme = QInputDialog::getInt(this, "Genereaza cos", "Numar filme in cos:", 0, 0, 1000000, 1, &ok);
        if (!ok) {
            return;
        }

        try {
            service.cosGenereaza(numarFilme);
            setMessage("Cos generat.");
        } catch (const std::exception& ex) {
            setMessage(ex.what());
        }
    });
}

void CosCRUDGUI::reloadList() {
    const auto& filme = service.cosGetAll();
    listaCos->clearContents();
    listaCos->setRowCount(int(filme.size()));

    for (int i = 0; i < int(filme.size()); ++i) {
        const auto& film = filme[static_cast<std::size_t>(i)];
        listaCos->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(film.getTitlu())));
        listaCos->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(film.getGen())));
        listaCos->setItem(i, 2, new QTableWidgetItem(QString::number(film.getAn())));
        listaCos->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(film.getActor())));
    }
}

void CosCRUDGUI::setMessage(const QString& mesaj) {
    labelMesaj->setText("Rezultat: " + mesaj);
}
