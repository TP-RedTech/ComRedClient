/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QWidget *centralWidget;
    QFrame *line;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *authOrName;
    QFrame *line_2;
    QPushButton *sendButton;
    QTextEdit *textEdit;
    QPushButton *exitButton;
    QListWidget *memberslistWidget;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(960, 720);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(720, 0, 20, 661));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(760, 20, 171, 80));
        authOrName = new QVBoxLayout(verticalLayoutWidget);
        authOrName->setSpacing(6);
        authOrName->setContentsMargins(11, 11, 11, 11);
        authOrName->setObjectName(QStringLiteral("authOrName"));
        authOrName->setContentsMargins(0, 0, 0, 0);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(730, 120, 231, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        sendButton = new QPushButton(centralWidget);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        sendButton->setGeometry(QRect(542, 630, 171, 28));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(20, 20, 691, 591));
        exitButton = new QPushButton(centralWidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(762, 630, 171, 28));
        memberslistWidget = new QListWidget(centralWidget);
        memberslistWidget->setObjectName(QStringLiteral("memberslistWidget"));
        memberslistWidget->setGeometry(QRect(760, 150, 171, 461));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 960, 26));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QStringLiteral("menuMenu"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMenu->menuAction());
        menuMenu->addAction(action);
        menuMenu->addAction(action_2);
        menuMenu->addAction(action_3);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", 0));
        action_2->setText(QApplication::translate("MainWindow", "\320\235\320\276\320\262\321\213\320\271", 0));
        action_3->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", 0));
        sendButton->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", 0));
        exitButton->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", 0));
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
