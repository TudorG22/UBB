#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSignalBlocker>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , service(repo)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initGui();
    loadGenuri();
    reloadList(service.serviceGetAll());

    connect(listaCarti, &QListWidget::itemSelectionChanged, this, [this]() {
        loadSelectedCarte();
    });

    connect(comboGen, &QComboBox::currentTextChanged, this, [this](const QString& text) {
        if (text == "Toate") {
            reloadList(service.serviceGetAll());
        } else {
            reloadList(service.serviceFilterByGen(text.toStdString()));
        }
    });

    connect(btnComanda, &QPushButton::clicked, this, [this]() {
        try {
            Comanda comanda = service.serviceCumpara(editComandaIsbn->text().toInt(), editComandaNr->text().toInt());
            labelComanda->setText(
                QString::fromStdString(comanda.carte.getTitlu() + " -- " + comanda.carte.getAutor()) +
                " | total: " + QString::number(comanda.costTotal)
            );
        } catch (const ServiceError& ex) {
            QMessageBox::warning(this, "Eroare", ex.what());
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGui() {
    auto* central = new QWidget;
    auto* layout = new QHBoxLayout;
    auto* leftLayout = new QVBoxLayout;
    auto* rightLayout = new QVBoxLayout;
    auto* formLayout = new QFormLayout;
    auto* comandaLayout = new QFormLayout;

    listaCarti = new QListWidget;
    comboGen = new QComboBox;
    editIsbn = new QLineEdit;
    labelDetalii = new QLabel;
    editComandaIsbn = new QLineEdit;
    editComandaNr = new QLineEdit;
    btnComanda = new QPushButton("Comanda");
    labelComanda = new QLabel;

    formLayout->addRow("ISBN:", editIsbn);
    formLayout->addRow("Detalii:", labelDetalii);
    comandaLayout->addRow("ISBN comandat:", editComandaIsbn);
    comandaLayout->addRow("Exemplare:", editComandaNr);

    leftLayout->addWidget(comboGen);
    leftLayout->addWidget(listaCarti);

    rightLayout->addLayout(formLayout);
    rightLayout->addLayout(comandaLayout);
    rightLayout->addWidget(btnComanda);
    rightLayout->addWidget(labelComanda);

    layout->addLayout(leftLayout);
    layout->addLayout(rightLayout);

    central->setLayout(layout);
    setCentralWidget(central);
    setWindowTitle("Librarie");
    resize(600, 400);
}

void MainWindow::reloadList(const std::vector<Carte>& carti) {
    const QSignalBlocker blocker(listaCarti);

    cartiAfisate = carti;
    listaCarti->clear();
    editIsbn->clear();
    labelDetalii->clear();

    for (const Carte& carte : carti) {
        QString text = QString::fromStdString(carte.getTitlu() + " -- " + carte.getAutor());
        listaCarti->addItem(text);
    }

    if (!cartiAfisate.empty()) {
        listaCarti->setCurrentRow(0);
        loadSelectedCarte();
    }
}

void MainWindow::reloadList(const std::vector<const Carte*>& carti) {
    const QSignalBlocker blocker(listaCarti);

    cartiAfisate.clear();
    listaCarti->clear();
    editIsbn->clear();
    labelDetalii->clear();

    for (const Carte* carte : carti) {
        cartiAfisate.push_back(*carte);
        QString text = QString::fromStdString(carte->getTitlu() + " -- " + carte->getAutor());
        listaCarti->addItem(text);
    }

    if (!cartiAfisate.empty()) {
        listaCarti->setCurrentRow(0);
        loadSelectedCarte();
    }
}

void MainWindow::loadSelectedCarte() {
    int poz = listaCarti->currentRow();
    if (poz < 0 || poz >= static_cast<int>(cartiAfisate.size())) {
        editIsbn->clear();
        labelDetalii->clear();
        return;
    }

    const Carte& carte = cartiAfisate.at(poz);
    editIsbn->setText(QString::number(carte.getIsbn()));
    labelDetalii->setText(
        QString::fromStdString(carte.getGen()) +
        " | pret: " + QString::number(carte.getPret()) +
        " | stoc: " + QString::number(carte.getStoc())
    );
}

void MainWindow::loadGenuri() {
    comboGen->addItem("Toate");

    for (const Carte& carte : service.serviceGetAll()) {
        QString gen = QString::fromStdString(carte.getGen());
        if (comboGen->findText(gen) == -1) {
            comboGen->addItem(gen);
        }
    }
}
