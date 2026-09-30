#include "mainwindow.h"
#include "coscrudgui.h"
#include "cosreadonlygui.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QStringList>
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
    listaFilme = new QTableView;
    labelMesaj = new QLabel;
    modelFilme = new FilmTableModel(this);

    listaFilme->setSelectionBehavior(QAbstractItemView::SelectRows);
    listaFilme->setSelectionMode(QAbstractItemView::SingleSelection);
    listaFilme->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listaFilme->setModel(modelFilme);
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
    auto* btnCartAdd = new QPushButton("Adauga in cos");
    auto* btnCartEmpty = new QPushButton("Sterge cos");
    auto* btnCartGenerate = new QPushButton("Genereaza cos");
    auto* btnOpenCrud = new QPushButton("Deschide CosCRUD");
    auto* btnOpenReadOnly = new QPushButton("Deschide CosReadOnly");

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

    buttonLayout3->addWidget(btnCartAdd);
    buttonLayout3->addWidget(btnCartEmpty);
    buttonLayout3->addWidget(btnCartGenerate);
    buttonLayout3->addWidget(btnOpenCrud);
    buttonLayout3->addWidget(btnOpenReadOnly);

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
    btnCartAdd->setObjectName("btnCartAdd");
    btnCartEmpty->setObjectName("btnCartEmpty");
    btnCartGenerate->setObjectName("btnCartGenerate");
    btnOpenCrud->setObjectName("btnOpenCrud");
    btnOpenReadOnly->setObjectName("btnOpenReadOnly");
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
    auto* btnCartAdd = findChild<QPushButton*>("btnCartAdd");
    auto* btnCartEmpty = findChild<QPushButton*>("btnCartEmpty");
    auto* btnCartGenerate = findChild<QPushButton*>("btnCartGenerate");
    auto* btnOpenCrud = findChild<QPushButton*>("btnOpenCrud");
    auto* btnOpenReadOnly = findChild<QPushButton*>("btnOpenReadOnly");

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

    connect(listaFilme->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]() {
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

    connect(btnCartAdd, &QPushButton::clicked, this, [this]() {
        try {
            const QString titlu = QInputDialog::getText(this, "Adauga in cos", "Titlu de adaugat in cos:");
            if (titlu.isNull()) {
                return;
            }

            service.cosAdauga(titlu.toStdString());
            setMessage("Film adaugat in cos.");
        } catch (const std::exception& ex) {
            setMessage(ex.what());
        }
    });

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

    connect(btnOpenCrud, &QPushButton::clicked, this, [this]() {
        auto* cosCrud = new CosCRUDGUI(service, this);
        cosCrud->show();
        setMessage("Fereastra CosCRUD a fost deschisa.");
    });

    connect(btnOpenReadOnly, &QPushButton::clicked, this, [this]() {
        auto* cosReadOnly = new CosReadOnlyGUI(service, this);
        cosReadOnly->show();
        setMessage("Fereastra CosReadOnly a fost deschisa.");
    });

}

void MainWindow::reloadList(const std::vector<Film>& filme) {
    filmeAfisate = filme;
    modelFilme->setFilme(filmeAfisate);
}

void MainWindow::reloadList(const std::vector<const Film*>& filme) {
    filmeAfisate.clear();
    for (int i = 0; i < int(filme.size()); ++i) {
        const auto* film = filme[static_cast<std::size_t>(i)];
        filmeAfisate.push_back(*film);
    }
    modelFilme->setFilme(filmeAfisate);
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
    const int index = listaFilme->currentIndex().row();
    if (index < 0) {
        return;
    }

    if (index >= int(filmeAfisate.size())) {
        return;
    }

    const auto& film = filmeAfisate[static_cast<std::size_t>(index)];
    editTitluVechi->setText(QString::fromStdString(film.getTitlu()));
    editTitlu->setText(QString::fromStdString(film.getTitlu()));
    editGen->setText(QString::fromStdString(film.getGen()));
    editAn->setText(QString::number(film.getAn()));
    editActor->setText(QString::fromStdString(film.getActor()));
}
