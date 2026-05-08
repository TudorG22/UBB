#include "mainwindow.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QDialog>

namespace {
constexpr int inceptionYear = 2010;
constexpr int titanicYear = 1997;
constexpr int gladiatorYear = 2000;
constexpr int interstellarYear = 2014;
constexpr int shrekYear = 2001;

QString filmToQString(const Film& film) {
    return QString::fromStdString(
        film.getTitlu() + " | " + film.getGen() + " | " +
        std::to_string(film.getAn()) + " | " + film.getActor());
}
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), service(repo)
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
    auto* btnDate = new QPushButton("Date initiale");
    auto* btnClear = new QPushButton("Goleste campuri");
    auto* btnSort = new QPushButton("Sorteaza");

    buttonLayout->addWidget(btnAdd);
    buttonLayout->addWidget(btnDelete);
    buttonLayout->addWidget(btnModify);
    buttonLayout->addWidget(btnUndo);
    buttonLayout->addWidget(btnShowAll);
    buttonLayout->addWidget(btnDate);
    buttonLayout->addWidget(btnClear);
    buttonLayout->addWidget(btnSort);

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
    btnDate->setObjectName("btnDate");
    btnClear->setObjectName("btnClear");
    btnSort->setObjectName("btnSort");
}

void MainWindow::initConnect() {
    auto* btnAdd = findChild<QPushButton*>("btnAdd");
    auto* btnDelete = findChild<QPushButton*>("btnDelete");
    auto* btnModify = findChild<QPushButton*>("btnModify");
    auto* btnUndo = findChild<QPushButton*>("btnUndo");
    auto* btnShowAll = findChild<QPushButton*>("btnShowAll");
    auto* btnDate = findChild<QPushButton*>("btnDate");
    auto* btnClear = findChild<QPushButton*>("btnClear");
    auto* btnSort = findChild<QPushButton*>("btnSort");

    connect(btnAdd, &QPushButton::clicked, this, [this]() {
        try {
            service.serviceAdd(
                editTitlu->text().toStdString(),
                editGen->text().toStdString(),
                editAn->text().toInt(),
                editActor->text().toStdString());
            reloadList(service.serviceGetAll());
            clearFields();
            setMessage("Film adaugat.");
        } catch (const std::exception& ex) {
            setMessage(ex.what());
        }
    });

    connect(btnDelete, &QPushButton::clicked, this, [this]() {
        try {
            service.serviceDel(editTitluVechi->text().toStdString());
            reloadList(service.serviceGetAll());
            clearFields();
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
            clearFields();
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

    connect(btnDate, &QPushButton::clicked, this, [this]() {
        try {
            service.serviceAdd("Inception", "SF", inceptionYear, "Leonardo DiCaprio");
            service.serviceAdd("Titanic", "Drama", titanicYear, "Leonardo DiCaprio");
            service.serviceAdd("Gladiator", "Actiune", gladiatorYear, "Russell Crowe");
            service.serviceAdd("Interstellar", "SF", interstellarYear, "Matthew McConaughey");
            service.serviceAdd("Shrek", "Animatie", shrekYear, "Mike Myers");
            reloadList(service.serviceGetAll());
            clearFields();
            setMessage("Datele initiale au fost adaugate.");
        } catch (const std::exception& ex) {
            setMessage(ex.what());
        }
    });

    connect(btnClear, &QPushButton::clicked, this, [this]() {
        clearFields();
        setMessage("Campurile au fost golite.");
    });

    connect(listaFilme, &QListWidget::itemSelectionChanged, this, [this]() {
        loadSelectedFilm();
    });

    connect(btnSort, &QPushButton::clicked, this, [this]() {
        auto* dlg = new QDialog(this);
        dlg->setWindowTitle("Alege sortarea");

        auto* layout = new QVBoxLayout(dlg);
        auto* btnTitlu = new QPushButton("Titlu");
        auto* btnActor = new QPushButton("Actor");
        auto* btnAnGen = new QPushButton("An + gen");

        layout->addWidget(btnTitlu);
        layout->addWidget(btnActor);
        layout->addWidget(btnAnGen);

        connect(btnTitlu, &QPushButton::clicked, dlg, [this, dlg]() {
            reloadList(service.serviceSort(1));
            setMessage("Sortare dupa titlu.");
            dlg->accept();
        });

        connect(btnActor, &QPushButton::clicked, dlg, [this, dlg]() {
            reloadList(service.serviceSort(2));
            setMessage("Sortare dupa actor.");
            dlg->accept();
        });

        connect(btnAnGen, &QPushButton::clicked, dlg, [this, dlg]() {
            reloadList(service.serviceSort(3));
            setMessage("Sortare dupa an si gen.");
            dlg->accept();
        });

        dlg->exec();
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

void MainWindow::clearFields() {
    editTitluVechi->clear();
    editTitlu->clear();
    editGen->clear();
    editAn->clear();
    editActor->clear();
}

void MainWindow::loadSelectedFilm() {
    const int index = listaFilme->currentRow();
    if (index < 0) {
        return;
    }

    const auto& filme = service.serviceGetAll();
    if (index >= static_cast<int>(filme.size())) {
        return;
    }

    const auto& film = filme[static_cast<std::size_t>(index)];
    editTitluVechi->setText(QString::fromStdString(film.getTitlu()));
    editTitlu->setText(QString::fromStdString(film.getTitlu()));
    editGen->setText(QString::fromStdString(film.getGen()));
    editAn->setText(QString::number(film.getAn()));
    editActor->setText(QString::fromStdString(film.getActor()));
}
