#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>

#include "repo.h"
#include "service.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    Repo repo;
    Service service;

    QLineEdit* editTitluVechi = nullptr;
    QLineEdit* editTitlu = nullptr;
    QLineEdit* editGen = nullptr;
    QLineEdit* editAn = nullptr;
    QLineEdit* editActor = nullptr;
    QListWidget* listaFilme = nullptr;
    QLabel* labelMesaj = nullptr;

    void initGui();
    void initConnect();
    void reloadList(const std::vector<Film>& filme);
    void setMessage(const QString& mesaj);
    void clearFields();
    void loadSelectedFilm();
};
#endif // MAINWINDOW_H
