#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: comred_client <editorId>" << std::endl;
        return 0;
    }

    QApplication a(argc, argv);
    MainWindow w(std::stoi(argv[1]));
    w.show();

    return a.exec();
}
