#include "cartwindow.h"

#include <QHeaderView>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QVBoxLayout>

CartWindow::CartWindow(Service& service, QWidget* parent)
    : QWidget(parent), service(service) {
    setWindowFlag(Qt::Window);
    initGui();
    initConnect();
    reloadList();
    setMessage("Cos pregatit.");
}

void CartWindow::initGui() {
    auto* mainLayout = new QVBoxLayout;
    auto* buttonLayout = new QHBoxLayout;

    auto* btnCartEmpty = new QPushButton("Goleste cos");
    auto* btnCartAdd = new QPushButton("Adauga in cos");
    auto* btnCartGenerate = new QPushButton("Genereaza cos");
    auto* btnCartShow = new QPushButton("Afiseaza cos");
    auto* btnCartSave = new QPushButton("Salveaza cos");

    listaCos = new QTableWidget;
    labelMesaj = new QLabel;

    listaCos->setColumnCount(4);
    listaCos->setHorizontalHeaderLabels(QStringList{"Titlu", "Gen", "An", "Actor"});
    listaCos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listaCos->horizontalHeader()->setStretchLastSection(true);
    listaCos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    buttonLayout->addWidget(btnCartEmpty);
    buttonLayout->addWidget(btnCartAdd);
    buttonLayout->addWidget(btnCartGenerate);
    buttonLayout->addWidget(btnCartShow);
    buttonLayout->addWidget(btnCartSave);

    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(listaCos);
    mainLayout->addWidget(labelMesaj);

    setLayout(mainLayout);
    setWindowTitle("Cos de cumparaturi");
    resize(600, 300);

    btnCartEmpty->setObjectName("btnCartEmpty");
    btnCartAdd->setObjectName("btnCartAdd");
    btnCartGenerate->setObjectName("btnCartGenerate");
    btnCartShow->setObjectName("btnCartShow");
    btnCartSave->setObjectName("btnCartSave");
}

void CartWindow::initConnect() {
    auto* btnCartEmpty = findChild<QPushButton*>("btnCartEmpty");
    auto* btnCartAdd = findChild<QPushButton*>("btnCartAdd");
    auto* btnCartGenerate = findChild<QPushButton*>("btnCartGenerate");
    auto* btnCartShow = findChild<QPushButton*>("btnCartShow");
    auto* btnCartSave = findChild<QPushButton*>("btnCartSave");

    connect(btnCartEmpty, &QPushButton::clicked, this, [this]() {
        service.cosGoleste();
        reloadList();
        setMessage("Cos golit.");
    });

    connect(btnCartAdd, &QPushButton::clicked, this, [this]() {
        try {
            const QString titlu = QInputDialog::getText(this, "Adauga in cos", "Titlu de adaugat in cos:");
            if (titlu.isNull()) {
                return;
            }

            service.cosAdauga(titlu.toStdString());
            reloadList();
            setMessage("Film adaugat in cos.");
        } catch (const std::exception& ex) {
            setMessage(ex.what());
        }
    });

    connect(btnCartGenerate, &QPushButton::clicked, this, [this]() {
        bool ok = false;
        const int numarFilme = QInputDialog::getInt(this, "Genereaza cos", "Numar filme in cos:", 0, 0, 1000000, 1, &ok);
        if (!ok) {
            return;
        }

        try {
            service.cosGenereaza(numarFilme);
            reloadList();
            setMessage("Cos generat.");
        } catch (const std::exception& ex) {
            setMessage(ex.what());
        }
    });

    connect(btnCartShow, &QPushButton::clicked, this, [this]() {
        reloadList();
        setMessage("Cos afisat.");
    });

    connect(btnCartSave, &QPushButton::clicked, this, [this]() {
        try {
            const QString numeFisier = QInputDialog::getText(this, "Salveaza cos", "Nume fisier:");
            if (numeFisier.isNull()) {
                return;
            }

            service.cosSalveazaFisier(numeFisier.toStdString());
            setMessage("Cos salvat.");
        } catch (const std::exception& ex) {
            setMessage(ex.what());
        }
    });
}

void CartWindow::reloadList() {
    const auto& filme = service.cosGetAll();
    listaCos->clearContents();
    listaCos->setRowCount(static_cast<int>(filme.size()));

    for (int i = 0; i < static_cast<int>(filme.size()); ++i) {
        const auto& film = filme[static_cast<std::size_t>(i)];
        listaCos->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(film.getTitlu())));
        listaCos->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(film.getGen())));
        listaCos->setItem(i, 2, new QTableWidgetItem(QString::number(film.getAn())));
        listaCos->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(film.getActor())));
    }
}

void CartWindow::setMessage(const QString& mesaj) {
    labelMesaj->setText("Rezultat: " + mesaj);
}
