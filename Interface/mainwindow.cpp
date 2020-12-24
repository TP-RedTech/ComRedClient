#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ComRed");
    QString btn_labels[3] = { "Зарегистрироваться", "Войти", "На будущее" };
    for (int i = 0; i < 3; i++)
    {
        buttons[i] = new QPushButton(btn_labels[i]);
        ui->authOrName->addWidget(buttons[i]);
    }
    form = new Form;

    connect(buttons[0], SIGNAL(clicked()), this, SLOT(registration()));
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(login()));
    connect(buttons[2], SIGNAL(clicked()), this, SLOT(logout()));
    connect(this, SIGNAL(registerClick(QString)), this, SLOT(showForm(QString)));
    connect(this, SIGNAL(loginClick(QString)), this, SLOT(showForm(QString)));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendText()));
    connect(form, SIGNAL(sendUserData(QStringList)), this, SLOT(getUserData(QStringList)));
}

MainWindow::~MainWindow()
{
    if (userData)
        delete userData;
    for (int i = 0; i < 3; i++)
        if (buttons[i])
            delete buttons[i];
    if (form)
        delete form;
    delete ui;
}

void MainWindow::registration()
{
    emit registerClick(buttons[0]->text());
}

void MainWindow::login()
{
    emit loginClick(buttons[1]->text());
}

void MainWindow::logout()
{
    QList<QListWidgetItem*> lst = ui->memberslistWidget->findItems(userData->text(), Qt::MatchExactly);
    ui->memberslistWidget->removeItemWidget(lst[0]);
    delete userData;
    userData = NULL;
    for (int i = 0; i < 3; i++)
        buttons[i]->setHidden(false);
}

void MainWindow::sendText()
{
    delete userData;
    userData = NULL;
    for (int i = 0; i < 3; i++)
        buttons[i]->setHidden(false);
}

void MainWindow::showForm(QString title)
{
    form->setWindowTitle(title);
    form->show();
}

void MainWindow::getUserData(QStringList data)
{
    QString str;
    for (int i = 0; i < data.size(); i++)
        str += data[i] + " ";
    for (int i = 0; i < 2; i++)
        buttons[i]->setHidden(true);
    userData = new QLabel(str);
    ui->authOrName->addWidget(userData);
    ui->memberslistWidget->addItem(str);
}
