#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

#include "include/repo.h"
#include "include/service.h"
#include "studenttablemodel.h"

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
    Repo repo{"repo.txt"};
    Service service;
    StudentTableModel* model = nullptr;
    std::vector<Student> studentiAfisati;
    Ui::MainWindow *ui;

    void initGui();
    void initConnect();
    void loadTable();
};
#endif // MAINWINDOW_H
