
#include <iostream>
#include <driver.h>

int main(int argc, char** argv) {
    int result = 0;
    Driver driver;

    for (int i = 1; i < argc; ++i) {
        if (argv[i] == std::string("-p")) {
            driver.trace_parsing = true;
        } else if (argv[i] == std::string("-s")) {
            driver.trace_scanning = true;
        } else if (!driver.Parse(argv[i])) {
            driver.Evaluate();
            driver.BuildIrTree();
            driver.Print();
        } else {
            result = 1;
        }
    }

    return result;
}