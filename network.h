

#ifndef NETWORK_H
#define NETWORK_H

#include <stdlib.h>
#include <stdio.h>

/* ip type */
#define IPSEGMENTS 4
typedef unsigned char uint8;

/* forward dec */
struct node;

/* router */
struct router
{
    router* pNext;
    node* pSubnet;
    uint8 ip[IPSEGMENTS];
    
    router()
    :   pNext(NULL),
        pSubnet(NULL)
    {
        int i;
        for (i = 0; i < IPSEGMENTS; i++)
            ip[i] = 0;
    }
};

/* node */
struct node
{
    router* pRouter;
    node* pNext;
    node* pPrev;
    uint8 ip[IPSEGMENTS];

    node()
    :   pRouter(NULL),
        pNext(NULL),
        pPrev(NULL)
    {
        int i;
        for (i = 0; i < IPSEGMENTS; i++)
            ip[i] = 0;
    }
};

/* network main class */
class network
{
    /* ringlist head */
    router* m_pHead;
    bool inc_router_ip(router* r);
    bool inc_node_ip(node* r);

    public:
    network();
    ~network();
    bool is_empty();
    void print_router(router* r);
    void print();

    router* add_router();
    node* add_node(router* r);
};

#endif
