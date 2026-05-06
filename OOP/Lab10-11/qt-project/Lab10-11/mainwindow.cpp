#include "mainwindow.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

namespace {
QString filmToQString(const Film& film) {
    return QString::fromStdString(
        film.getTitlu() + " | " + film.getGen() + " | " +
        std::to_string(film.getAn()) + " | " + film.getActor());
}
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , service(repo)
{
    initGui();
    initConnect();
    reloadList(service.serviceGetAll());
    setMessage("Aplicatia a pornit.");
}

void MainWindow::initGui() {
    auto* central = new QWidget;
    auto* mainLayout = new QVBoxLayout;
    auto* formLayout = new QFormLayout;
    auto* buttonLayout = new QHBoxLayout;

    editTitluVechi = new QLineEdit;
    editTitlu = new QLineEdit;
    editGen = new QLineEdit;
    editAn = new QLineEdit;
    editActor = new QLineEdit;
    listaFilme = new QListWidget;
    labelMesaj = new QLabel;

    formLayout->addRow("Titlu vechi:", editTitluVechi);
    formLayout->addRow("Titlu:", editTitlu);
    formLayout->addRow("Gen:", editGen);
    formLayout->addRow("An:", editAn);
    formLayout->addRow("Actor:", editActor);

    auto* btnAdd = new QPushButton("Adauga");
    auto* btnDelete = new QPushButton("Sterge");
    auto* btnModify = new QPushButton("Modifica");
    auto* btnUndo = new QPushButton("Undo");
    auto* btnShowAll = new QPushButton("Afiseaza toate");

    buttonLayout->addWidget(btnAdd);
    buttonLayout->addWidget(btnDelete);
    buttonLayout->addWidget(btnModify);
    buttonLayout->addWidget(btnUndo);
    buttonLayout->addWidget(btnShowAll);

    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(listaFilme);
    mainLayout->addWidget(labelMesaj);

    central->setLayout(mainLayout);
    setCentralWidget(central);
    setWindowTitle("Lab10-11");
    resize(700, 400);

    btnAdd->setObjectName("btnAdd");
    btnDelete->setObjectName("btnDelete");
    btnModify->setObjectName("btnModify");
    btnUndo->setObjectName("btnUndo");
    btnShowAll->setObjectName("btnShowAll");
}

void MainWindow::initConnect() {
    auto* btnAdd = findChild<QPushButton*>("btnAdd");
    auto* btnDelete = findChild<QPushButton*>("btnDelete");
    auto* btnModify = findChild<QPushButton*>("btnModify");
    auto* btnUndo = findChild<QPushButton*>("btnUndo");
    auto* btnShowAll = findChild<QPushButton*>("btnShowAll");

    connect(btnAdd, &QPushButton::clicked, this, [this]() {
        try {
            service.serviceAdd(
                editTitlu->text().toStdString(),
                editGen->text().toStdString(),
                editAn->text().toInt(),
                editActor->text().toStdString());
            reloadList(service.serviceGetAll());
            setMessage("Film adaugat.");
        } catch (const std::exception& ex) {
            setMessage(ex.what());
        }
    });

    connect(btnDelete, &QPushButton::clicked, this, [this]() {
        try {
            service.serviceDel(editTitluVechi->text().toStdString());
            reloadList(service.serviceGetAll());
            setMessage("Operatie finalizata.");
        } catch (const std::exception& ex) {
            setMessage(ex.what());
        }
    });

    connect(btnModify, &QPushButton::clicked, this, [this]() {
        try {
            service.serviceModify(
                editTitluVechi->text().toStdString(),
                editTitlu->text().toStdString(),
                editGen->text().toStdString(),
                editAn->text().toInt(),
                editActor->text().toStdString());
            reloadList(service.serviceGetAll());
            setMessage("Film modificat.");
        } catch (const std::exception& ex) {
            setMessage(ex.what());
        }
    });

    connect(btnUndo, &QPushButton::clicked, this, [this]() {
        try {
            service.undo();
            reloadList(service.serviceGetAll());
            setMessage("Undo realizat.");
        } catch (const std::exception& ex) {
            setMessage(ex.what());
        }
    });

    connect(btnShowAll, &QPushButton::clicked, this, [this]() {
        reloadList(service.serviceGetAll());
        setMessage("Lista a fost actualizata.");
    });
}

void MainWindow::reloadList(const std::vector<Film>& filme) {
    listaFilme->clear();
    for (const auto& film : filme) {
        listaFilme->addItem(filmToQString(film));
    }
}

void MainWindow::setMessage(const QString& mesaj) {
    labelMesaj->setText("Rezultat: " + mesaj);
}
