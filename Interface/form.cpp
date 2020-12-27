#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    connect(ui->submitButton, SIGNAL(clicked()), this, SLOT(submitButtonClicked()));
}

Form::~Form()
{
    delete ui;
}

void Form::submitButtonClicked()
{
    QStringList data;
    data.append(ui->lineEditLogin->text());
    data.append(ui->lineEditPassword->text());
    ui->lineEditLogin->clear();
    ui->lineEditPassword->clear();
    this->close();
    emit sendUserData(data);
}
