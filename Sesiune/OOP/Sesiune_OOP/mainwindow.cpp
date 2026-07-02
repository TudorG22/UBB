#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , service(repo)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initGui();
    initConnect();
    loadTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGui() {
    model = new StudentTableModel(this);

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::initConnect() {
    connect(ui->btnIntinerire, &QPushButton::clicked, this, [this]() {
        service.intinerire();
        loadTable();
    });

    connect(ui->btnImbatrinire, &QPushButton::clicked, this, [this]() {
        service.imbatrinire();
        loadTable();
    });

    connect(ui->btnSterge, &QPushButton::clicked, this, [this]() {
        QModelIndexList linii = ui->tableView->selectionModel()->selectedRows();
        std::vector<Student> deSters;

        for (int i = 0; i < linii.size(); i++) {
            int poz = linii[i].row();
            if (poz >= 0 && poz < studentiAfisati.size()) {
                deSters.push_back(studentiAfisati[poz]);
            }
        }

        for (int i = 0; i < deSters.size(); i++) {
            service.stergeStudent(deSters[i]);
        }

        loadTable();
    });

    connect(ui->btnUndo, &QPushButton::clicked, this, [this]() {
        service.doUndo();
        loadTable();
    });

    connect(ui->btnRedo, &QPushButton::clicked, this, [this]() {
        service.doRedo();
        loadTable();
    });
}

void MainWindow::loadTable() {
    studentiAfisati = service.serviceSortByVarsta();
    model->setStudents(studentiAfisati);
}
