

#include "network.h"

int main()
{
    network net;

    int i;
    for (i = 0; i < 350; i++)
        net.add_router();

    net.print();

    return 0;
}
