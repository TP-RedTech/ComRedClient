#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <memory>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QMessageBox>

#include "form.h"
#include "documentform.h"
#include "../Application/include/application.h"

#define BTN_COUNT 2

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int editorId, QWidget *parent = 0);
    ~MainWindow();

protected:
    bool eventFilter(QObject *widget, QEvent *event);
    void timerEvent(QTimerEvent *event);

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

    shared_ptr<Application> app;
};

#endif // MAINWINDOW_H
