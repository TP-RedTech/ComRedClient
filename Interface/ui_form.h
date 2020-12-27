/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *labelLogin;
    QLineEdit *lineEditLogin;
    QLineEdit *lineEditPassword;
    QLabel *labelPassword;
    QPushButton *submitButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(320, 200);
        formLayoutWidget = new QWidget(Form);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(80, 70, 160, 61));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        labelLogin = new QLabel(formLayoutWidget);
        labelLogin->setObjectName(QStringLiteral("labelLogin"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelLogin);

        lineEditLogin = new QLineEdit(formLayoutWidget);
        lineEditLogin->setObjectName(QStringLiteral("lineEditLogin"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditLogin);

        lineEditPassword = new QLineEdit(formLayoutWidget);
        lineEditPassword->setObjectName(QStringLiteral("lineEditPassword"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditPassword);

        labelPassword = new QLabel(formLayoutWidget);
        labelPassword->setObjectName(QStringLiteral("labelPassword"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelPassword);

        submitButton = new QPushButton(Form);
        submitButton->setObjectName(QStringLiteral("submitButton"));
        submitButton->setGeometry(QRect(80, 140, 93, 28));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        labelLogin->setText(QApplication::translate("Form", "\320\233\320\276\320\263\320\270\320\275", 0));
        labelPassword->setText(QApplication::translate("Form", "\320\237\320\260\321\200\320\276\320\273\321\214", 0));
        submitButton->setText(QApplication::translate("Form", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
