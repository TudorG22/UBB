#include "mainwindow.h"
#include "cartwindow.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QHeaderView>
#include <QStringList>
#include <QTableWidgetItem>
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

QString raportToQString(const std::map<std::string, int>& raport) {
    QStringList linii;
    for (const auto& pereche : raport) {
        linii.push_back(QString::fromStdString(pereche.first) + " | " + QString::number(pereche.second));
    }
    return linii.join('\n');
}
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), service(repo)
{
    initGui();
    cosWindow = new CartWindow(service, this);
    initConnect();
    reloadList(service.serviceGetAll());
    setMessage("Aplicatia a pornit.");
}

void MainWindow::initGui() {
    auto* central = new QWidget;
    auto* mainLayout = new QVBoxLayout;
    auto* formLayout = new QFormLayout;
    auto* buttonLayout1 = new QHBoxLayout;
    auto* buttonLayout2 = new QHBoxLayout;
    auto* buttonLayout3 = new QHBoxLayout;

    editTitluVechi = new QLineEdit;
    editTitlu = new QLineEdit;
    editGen = new QLineEdit;
    editAn = new QLineEdit;
    editActor = new QLineEdit;
    listaFilme = new QTableWidget;
    labelMesaj = new QLabel;

    listaFilme->setColumnCount(4);
    listaFilme->setHorizontalHeaderLabels(QStringList{"Titlu", "Gen", "An", "Actor"});
    listaFilme->setSelectionBehavior(QAbstractItemView::SelectRows);
    listaFilme->setSelectionMode(QAbstractItemView::SingleSelection);
    listaFilme->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listaFilme->horizontalHeader()->setStretchLastSection(true);
    listaFilme->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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
    auto* btnSearch = new QPushButton("Cauta");
    auto* btnFilter = new QPushButton("Filtreaza");
    auto* btnReport = new QPushButton("Raport genuri");
    auto* btnManageCart = new QPushButton("Gestioneaza cos");

    buttonLayout1->addWidget(btnAdd);
    buttonLayout1->addWidget(btnDelete);
    buttonLayout1->addWidget(btnModify);
    buttonLayout1->addWidget(btnUndo);
    buttonLayout1->addWidget(btnShowAll);
    buttonLayout1->addWidget(btnDate);

    buttonLayout2->addWidget(btnClear);
    buttonLayout2->addWidget(btnSort);
    buttonLayout2->addWidget(btnSearch);
    buttonLayout2->addWidget(btnFilter);
    buttonLayout2->addWidget(btnReport);

    buttonLayout3->addWidget(btnManageCart);

    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout1);
    mainLayout->addLayout(buttonLayout2);
    mainLayout->addLayout(buttonLayout3);
    mainLayout->addWidget(listaFilme);
    mainLayout->addWidget(labelMesaj);

    central->setLayout(mainLayout);
    setCentralWidget(central);
    setWindowTitle("Lab13-14");
    resize(700, 400);

    btnAdd->setObjectName("btnAdd");
    btnDelete->setObjectName("btnDelete");
    btnModify->setObjectName("btnModify");
    btnUndo->setObjectName("btnUndo");
    btnShowAll->setObjectName("btnShowAll");
    btnDate->setObjectName("btnDate");
    btnClear->setObjectName("btnClear");
    btnSort->setObjectName("btnSort");
    btnSearch->setObjectName("btnSearch");
    btnFilter->setObjectName("btnFilter");
    btnReport->setObjectName("btnReport");
    btnManageCart->setObjectName("btnManageCart");
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
    auto* btnSearch = findChild<QPushButton*>("btnSearch");
    auto* btnFilter = findChild<QPushButton*>("btnFilter");
    auto* btnReport = findChild<QPushButton*>("btnReport");
    auto* btnManageCart = findChild<QPushButton*>("btnManageCart");

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

    connect(listaFilme, &QTableWidget::itemSelectionChanged, this, [this]() {
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

    connect(btnSearch, &QPushButton::clicked, this, [this]() {
        try {
            const QString titlu = QInputDialog::getText(this, "Cauta dupa titlu", "Titlu cautat:");
            if (titlu.isNull()) {
                return;
            }

            const int poz = service.serviceCauta(titlu.toStdString());
            if (poz == -1) {
                setMessage("Filmul nu exista.");
                return;
            }

            const auto& film = service.serviceGetAll().at(static_cast<std::size_t>(poz));
            reloadList(std::vector<Film>{film});
            setMessage("Cautare finalizata.");
        } catch (const std::exception& ex) {
            setMessage(ex.what());
        }
    });

    connect(btnFilter, &QPushButton::clicked, this, [this]() {
        auto* dlg = new QDialog(this);
        dlg->setWindowTitle("Alege filtrarea");

        auto* layout = new QVBoxLayout(dlg);
        auto* btnTitlu = new QPushButton("Titlu");
        auto* btnAn = new QPushButton("An");

        layout->addWidget(btnTitlu);
        layout->addWidget(btnAn);

        connect(btnTitlu, &QPushButton::clicked, dlg, [this, dlg]() {
            const QString valoare = QInputDialog::getText(this, "Filtrare dupa titlu", "Valoare:");
            if (valoare.isNull()) {
                return;
            }

            try {
                reloadList(service.serviceFilter(1, valoare.toStdString()));
                setMessage("Filtrare dupa titlu.");
                dlg->accept();
            } catch (const std::exception& ex) {
                setMessage(ex.what());
            }
        });

        connect(btnAn, &QPushButton::clicked, dlg, [this, dlg]() {
            const QString valoare = QInputDialog::getText(this, "Filtrare dupa an", "Valoare:");
            if (valoare.isNull()) {
                return;
            }

            try {
                reloadList(service.serviceFilter(2, valoare.toStdString()));
                setMessage("Filtrare dupa an.");
                dlg->accept();
            } catch (const std::exception& ex) {
                setMessage(ex.what());
            }
        });

        dlg->exec();
    });

    connect(btnReport, &QPushButton::clicked, this, [this]() {
        const auto raport = service.raportGenuri();
        QMessageBox::information(this, "Raport genuri", raportToQString(raport));
        setMessage("Raport afisat.");
    });

    connect(btnManageCart, &QPushButton::clicked, this, [this]() {
        cosWindow->reloadList();
        cosWindow->show();
        cosWindow->raise();
        cosWindow->activateWindow();
        setMessage("Fereastra cos a fost deschisa.");
    });

}

void MainWindow::reloadList(const std::vector<Film>& filme) {
    filmeAfisate = filme;
    listaFilme->clearContents();
    listaFilme->setRowCount(static_cast<int>(filmeAfisate.size()));
    for (int i = 0; i < static_cast<int>(filmeAfisate.size()); ++i) {
        const auto& film = filmeAfisate[static_cast<std::size_t>(i)];
        listaFilme->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(film.getTitlu())));
        listaFilme->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(film.getGen())));
        listaFilme->setItem(i, 2, new QTableWidgetItem(QString::number(film.getAn())));
        listaFilme->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(film.getActor())));
    }
}

void MainWindow::reloadList(const std::vector<const Film*>& filme) {
    filmeAfisate.clear();
    listaFilme->clearContents();
    listaFilme->setRowCount(static_cast<int>(filme.size()));
    for (int i = 0; i < static_cast<int>(filme.size()); ++i) {
        const auto* film = filme[static_cast<std::size_t>(i)];
        filmeAfisate.push_back(*film);
        listaFilme->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(film->getTitlu())));
        listaFilme->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(film->getGen())));
        listaFilme->setItem(i, 2, new QTableWidgetItem(QString::number(film->getAn())));
        listaFilme->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(film->getActor())));
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

    if (index >= static_cast<int>(filmeAfisate.size())) {
        return;
    }

    const auto& film = filmeAfisate[static_cast<std::size_t>(index)];
    editTitluVechi->setText(QString::fromStdString(film.getTitlu()));
    editTitlu->setText(QString::fromStdString(film.getTitlu()));
    editGen->setText(QString::fromStdString(film.getGen()));
    editAn->setText(QString::number(film.getAn()));
    editActor->setText(QString::fromStdString(film.getActor()));
}
