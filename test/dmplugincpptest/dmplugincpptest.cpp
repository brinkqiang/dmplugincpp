
#include "dmplugincpp.h"

int main( int argc, char* argv[] ) {

    Idmplugincpp* module = dmplugincppGetModule();
    if (module)
    {
        module->Test();
        module->Release();
    }
    return 0;
}
