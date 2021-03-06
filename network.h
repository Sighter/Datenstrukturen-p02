

#ifndef NETWORK_H
#define NETWORK_H

#include <stdlib.h>
#include <stdio.h>


/* Exercise 1
 * **********
 * Here, you find all main datastructures defined.
 * 
 * router : structure for managing a router
 *
 * node : structure for managing a subnet node, that will be managed
 *        in a double linked list
 *
 * ip_node : element type for the ip list wich is needed
 *           by the package hunter (see Exercise 3)
 *
 * network class : This class manages the router ring. Hence,
 * it keeps track of a pointer for the ringlist.
 * Every router has a pointer to a ip_node, and is regarding to this,
 * connected to the subnet
 */

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


/* ip node for ip list */
struct ip_node
{
    ip_node* pNext;
    uint8 ip[IPSEGMENTS];
    
    ip_node()
    :   pNext(NULL)
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
    bool inc_node_ip(node* n);
    ip_node* ip_list_append(ip_node* pHead, uint8* ip);

    public:
    network();
    ~network();
    bool is_empty();
    void print_router(router* r);
    void print_node(node* r);
    void print();

    router* add_router();
    node* add_node(router* r);
    node* find_node(router* r, uint8* ip);
    ip_node* pac_hunter(node* pStart, uint8* targetIp);
    void ip_list_delete(ip_node* pHead);
    void ip_list_print(ip_node* pHead);
};

#endif
