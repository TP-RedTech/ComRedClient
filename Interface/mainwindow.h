#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>

#include "form.h"
#include "documentform.h"

#define BTN_COUNT 2

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool eventFilter(QObject *widget, QEvent *event);

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

    void createDoc(QString name);
    void openDoc(QString name);

private:
    Ui::MainWindow *ui;
    QPushButton *buttons[BTN_COUNT];
    QLabel *userData;
    Form *form;
    DocumentForm *docForm;
    bool docOpened, shift, caps;
};

#endif // MAINWINDOW_H
