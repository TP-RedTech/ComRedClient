#ifndef DOCUMENTFORM_H
#define DOCUMENTFORM_H

#include <QWidget>

#define CREATE "Создать"
#define OPEN "Открыть"

namespace Ui {
class DocumentForm;
}

class DocumentForm : public QWidget
{
    Q_OBJECT

public:
    explicit DocumentForm(QWidget *parent = 0);
    ~DocumentForm();

signals:
    void create(QString);
    void open(QString);

public slots:
    void createDocument(void);
    void openDocument(void);

private slots:
    void on_pushButton_clicked();

private:
    Ui::DocumentForm *ui;
};

#endif // DOCUMENTFORM_H
