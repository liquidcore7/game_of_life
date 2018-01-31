#include <iostream>
#include "field.h"
#include "app.h"
#include "setup.h"

int main(int argc, char** argv) {
    if (argc != 2)
    {
        std::cerr << "1 argument (cell count) excepted, " << argc - 1 << " provided";
        return  -1;
    }
    std::vector<bool> arg;
    size_t cnt = std::stoull(std::string(argv[1]));
    Setup g(cnt, arg);
    nana::API::modal_window(g);
    g.show();

    App main(arg);
    main.show();

    nana::exec();
}