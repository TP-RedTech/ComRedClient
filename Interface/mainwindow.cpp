#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ComRed");
    QString btn_labels[BTN_COUNT] = { "Зарегистрироваться", "Войти" };
    for (int i = 0; i < BTN_COUNT; i++)
    {
        buttons[i] = new QPushButton(btn_labels[i]);
        ui->authOrName->addWidget(buttons[i]);
    }
    form = new Form;
    docForm = new DocumentForm;
    userData = NULL;

    ui->labelName->setText("");
    ui->textEdit->installEventFilter(this);

    docOpened = false;
    shift = false;
    caps = false;

    connect(buttons[0], SIGNAL(clicked()), this, SLOT(registration()));
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(login()));
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(logout()));
    connect(this, SIGNAL(registerClick(QString)), this, SLOT(showForm(QString)));
    connect(this, SIGNAL(loginClick(QString)), this, SLOT(showForm(QString)));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendText()));
    connect(form, SIGNAL(sendUserData(QStringList)), this, SLOT(getUserData(QStringList)));
    connect(ui->openButton, SIGNAL(clicked()), docForm, SLOT(openDocument()));
    connect(ui->createButton, SIGNAL(clicked()), docForm, SLOT(createDocument()));
    connect(docForm, SIGNAL(create(QString)), this, SLOT(createDoc(QString)));
    connect(docForm, SIGNAL(open(QString)), this, SLOT(openDoc(QString)));
}

MainWindow::~MainWindow()
{
    if (userData)
        delete userData;
    for (int i = 0; i < BTN_COUNT; i++)
        if (buttons[i])
            delete buttons[i];
    if (form)
        delete form;
    if (docForm)
        delete docForm;
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
    for (int i = 0; i < BTN_COUNT; i++)
        buttons[i]->setHidden(false);
}

void MainWindow::sendText()
{
    cout << ui->textEdit->textCursor().position() << endl;
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
    for (int i = 0; i < BTN_COUNT; i++)
        buttons[i]->setHidden(true);
    userData = new QLabel(str);
    ui->authOrName->addWidget(userData);
    ui->memberslistWidget->addItem(str);
}

void MainWindow::createDoc(QString name)
{
    ui->labelName->setText(name); //call app func
}

void MainWindow::openDoc(QString name)
{
    ui->labelName->setText(name); //call app func
}

bool MainWindow::eventFilter(QObject *widget, QEvent *event)
{
    if (widget == ui->textEdit && event->type() == QKeyEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        QString text = ui->textEdit->toPlainText();
        int key = keyEvent->key();
        QTextCursor cursor = ui->textEdit->textCursor();
        int cursorPos = cursor.position();
        cout << cursorPos << endl;
        if (key == Qt::Key_Shift)
            shift = true;
        else if (key == Qt::Key_CapsLock)
            caps = !caps;
        else if (key == Qt::Key_Backspace)
        {
            cursorPos--;
            text.remove(cursorPos, 1); //instead remove call app func
        }
        else if (key == Qt::Key_Delete)
        {
            text.remove(cursorPos, 1); //and here
        }
        else
        {
            QString sym = QString(key);
            if (!shift && !caps)
                sym = sym.toLower();
            else if (shift)
                shift = !shift;
            text.insert(cursorPos, sym); //call app func
            cursorPos++;
        }
        ui->textEdit->setText(text);
        cursor.setPosition(cursorPos);
        ui->textEdit->setTextCursor((const QTextCursor) cursor);
        return true;
    }
    return false;
}
