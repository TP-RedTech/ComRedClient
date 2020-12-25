/********************************************************************************
** Form generated from reading UI file 'documentform.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCUMENTFORM_H
#define UI_DOCUMENTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DocumentForm
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *DocumentForm)
    {
        if (DocumentForm->objectName().isEmpty())
            DocumentForm->setObjectName(QStringLiteral("DocumentForm"));
        DocumentForm->resize(320, 240);
        verticalLayoutWidget = new QWidget(DocumentForm);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(80, 70, 160, 85));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(verticalLayoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(DocumentForm);

        QMetaObject::connectSlotsByName(DocumentForm);
    } // setupUi

    void retranslateUi(QWidget *DocumentForm)
    {
        DocumentForm->setWindowTitle(QApplication::translate("DocumentForm", "Form", 0));
        label->setText(QApplication::translate("DocumentForm", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\264\320\276\320\272\321\203\320\274\320\265\320\275\321\202\320\260", 0));
        pushButton->setText(QApplication::translate("DocumentForm", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class DocumentForm: public Ui_DocumentForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCUMENTFORM_H
