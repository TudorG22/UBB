#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QMainWindow>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

#include "include/repo.h"
#include "include/service.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Repo repo{"../../repo.csv"};
    Service service;
    Ui::MainWindow *ui;
    QListWidget* listaCarti = nullptr;
    QComboBox* comboGen = nullptr;
    QLineEdit* editIsbn = nullptr;
    QLabel* labelDetalii = nullptr;
    QLineEdit* editComandaIsbn = nullptr;
    QLineEdit* editComandaNr = nullptr;
    QPushButton* btnComanda = nullptr;
    QLabel* labelComanda = nullptr;
    std::vector<Carte> cartiAfisate;

    void initGui();
    void reloadList(const std::vector<Carte>& carti);
    void reloadList(const std::vector<const Carte*>& carti);
    void loadSelectedCarte();
    void loadGenuri();
};
#endif // MAINWINDOW_H
