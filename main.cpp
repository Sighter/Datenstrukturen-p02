

#include "network.h"
#include "stdlib.h"
#include "time.h"

int main()
{
    network net;

    router* pR = NULL;
    

    /* build a "random" network */
    int i;
    for (i = 0; i < 4; i++)
    {
        pR = net.add_router();

        srand(i);
        int k, r;
        r = rand() % 10;

        for (k = 0; k < r; k++)
            net.add_node(pR);
    }


    /* search for a node */
    uint8 ip[4] = {0,0,4,5};

    node* ret = net.find_node(pR, ip);
    if (ret != NULL)
    {
        printf("Node found: ");
        net.print_node(ret);
        printf("\n");
    }
    else
        printf("Node not found\n");


    
    net.print();

    return 0;
}
