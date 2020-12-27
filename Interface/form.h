#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

signals:
    void sendUserData(QStringList);

private slots:
    void submitButtonClicked(void);

private:
    Ui::Form *ui;
};

#endif // FORM_H
