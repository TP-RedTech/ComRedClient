#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

#include "form.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void registerClick(QString);
    void loginClick(QString);

private slots:
    void registration(void);
    void login(void);
    void logout(void);

    void sendText(void);
    void showForm(QString title);

    void getUserData(QStringList);

private:
    Ui::MainWindow *ui;
    QPushButton *buttons[3];
    QLabel *userData;
    Form *form;
};

#endif // MAINWINDOW_H
