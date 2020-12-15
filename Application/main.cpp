#include <iostream>
#include "include/application.h"

int main(int argc, const char * argv[]) {

    std::shared_ptr<Application> app(new Application(1, 30));

    app->connect();

    app->update(0, "1,hello");

    std::cout << "Hello, world!" << std::endl;

    return 0;
}
