#include "documentform.h"
#include "ui_documentform.h"

DocumentForm::DocumentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocumentForm)
{
    ui->setupUi(this);
}

DocumentForm::~DocumentForm()
{
    delete ui;
}

void DocumentForm::createDocument()
{
    this->setWindowTitle(CREATE);
    this->show();
}

void DocumentForm::openDocument()
{
    this->setWindowTitle(OPEN);
    this->show();
}

void DocumentForm::on_pushButton_clicked()
{
    this->close();
    if (this->windowTitle() == CREATE)
        emit create(ui->lineEdit->text());
    else if (this->windowTitle() == OPEN)
        emit open(ui->lineEdit->text());
}
