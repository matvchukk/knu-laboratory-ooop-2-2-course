#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

namespace test {
    int main_test(int argc, char* argv[]) {

        doctest::Context context;

        context.applyCommandLine(argc, argv);

        int res = context.run();

        if (context.shouldExit())
            return res;

        int client_stuff_return_code = 0;

        return res + client_stuff_return_code;
    }
}