#include "coscrudgui.h"

#include <QHeaderView>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QPushButton>
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

    listaCos = new QTableView;
    labelMesaj = new QLabel;
    modelCos = new FilmTableModel(this);

    listaCos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listaCos->setModel(modelCos);
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
    modelCos->setFilme(service.cosGetAll());
}

void CosCRUDGUI::setMessage(const QString& mesaj) {
    labelMesaj->setText("Rezultat: " + mesaj);
}
