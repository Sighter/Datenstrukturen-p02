
#include "network.h"


/* network constructor */
network::network()
:   m_pHead(NULL)
{
} 


/* destructor */
network::~network()
{
    router* pTemp = m_pHead;
    router* pDel = NULL;
    node* pSubWalker = NULL;
    node* pSubDel = NULL;
    
    if (pTemp == NULL)
        return;

    /* delete router ring */
    do
    {
        pDel = pTemp;

        /* delete subnet */
        pSubWalker = pDel->pSubnet;
        while (pSubWalker != NULL)
        {
            pSubDel = pSubWalker;
            pSubWalker = pSubWalker->pNext;
            delete pSubDel;
        }  

        pTemp = pTemp->pNext;
        delete pDel;
    } while (pTemp != m_pHead);
}
    

/* trivial */
bool network::is_empty()
{
    if (m_pHead == NULL)
        return true;
    else
        return false;
}


/* print a router */
void network::print_router(router* r)
{
    int i;
    for (i = 0; i < IPSEGMENTS - 1; i++)
        printf("%03d.", r->ip[i]);
    
    printf("%03d", r->ip[IPSEGMENTS - 1]);
}


/* print a node */
void network::print_node(node* r)
{
    int i;
    for (i = 0; i < IPSEGMENTS - 1; i++)
        printf("%03d.", r->ip[i]);
    
    printf("%03d", r->ip[IPSEGMENTS - 1]);
}


/* print network */
void network::print()
{
    router* pTemp = m_pHead;
    node* pSubWalker = NULL;
    
    if (pTemp == NULL)
        return;

    do
    {
        printf("ROUTER: ");
        print_router(pTemp);
        printf("\n");
        
        pSubWalker = pTemp->pSubnet;

        while (pSubWalker != NULL)
        {
            printf(" --> ");
            print_node(pSubWalker);
            printf("\n");
            pSubWalker = pSubWalker->pNext;
        }

        pTemp = pTemp->pNext;
    } while (pTemp != m_pHead);
}
        

/* increase a router ip */
bool network::inc_router_ip(router* r)
{
    int i;
    for (i = IPSEGMENTS - 2; i >= 0; i--)
    {
        r->ip[i]++;
        if (r->ip[i] == 0)
        {
            if (i == 0) 
            {
                r->ip[0]--;
                return false;
            }
            else
                continue;
        }
        break;
    }
    
    return true;
}


/* increase a node ip */
bool network::inc_node_ip(node* n)
{
    n->ip[IPSEGMENTS - 1]++;
    if (n->ip[IPSEGMENTS - 1] == 0)
    {
        n->ip[IPSEGMENTS - 1]--;
        return false;
    }
    return true;
}


/* add a router */
router* network::add_router()
{
    /* check for empty network */
    if (m_pHead == NULL)
    {
       m_pHead = new router;
       if (m_pHead == NULL)
           return NULL;

       m_pHead->pNext = m_pHead;
       inc_router_ip(m_pHead);
       return m_pHead;
    }
    else
    {
        router* pTemp = m_pHead;
        while (pTemp->pNext != m_pHead)
            pTemp = pTemp->pNext;

        router* pNew = new router;
        if (pNew == NULL)
            return NULL;
        
        pNew->pNext = pTemp->pNext;
        pTemp->pNext = pNew;
        
        int i;
        for (i = 0; i < IPSEGMENTS - 1; i++)
            pNew->ip[i] = pTemp->ip[i];
        
        /* ip availible */
        if (inc_router_ip(pNew) == false)
        {
            pTemp->pNext = pNew->pNext;
            delete pNew;
            return NULL;
        }
        
        return pNew;
    }

}


/* add node to router */
node* network::add_node(router* r)
{
    if (r == NULL)
        return NULL;

    if (r->pSubnet == NULL)
    {
        r->pSubnet = new node;
        r->pSubnet->pNext = NULL;
        r->pSubnet->pPrev = NULL;
        r->pSubnet->pRouter = r;

        int i;
        for (i = 0; i < IPSEGMENTS; i++)
            r->pSubnet->ip[i] = r->ip[i];

        inc_node_ip(r->pSubnet);
        return r->pSubnet;
    }

    /* case, if the subnet has at least one node */
    node* pSubWalker = r->pSubnet;
    
    while (pSubWalker->pNext != NULL)
        pSubWalker = pSubWalker->pNext;

    node* pNew = new node;
    if (pNew == NULL)
        return NULL;
    
    int i;
    for (i = 0; i < IPSEGMENTS; i++)
        pNew->ip[i] = pSubWalker->ip[i];

    /* case, if subnet is full */
    if (inc_node_ip(pNew) == false)
    {
        delete pNew;
        return NULL;
    }

    pNew->pNext = pSubWalker->pNext;
    pSubWalker->pNext = pNew;
    pNew->pPrev = pSubWalker;

    return pNew;
}


node* network::find_node(router* r, uint8* ip)
{
    if (r == NULL || ip == NULL)
        return NULL;
    
    router* pWalker = r;
    
    /* go around the router ring */
    do
    {
        bool found_router = true;
        int i = 0;
        for (i = 0; i < IPSEGMENTS - 1; i++)
        {
            if (pWalker->ip[i] != ip[i])
            {
                found_router = false;
                break;
            }
        }

        /* if router found look in the subnet */
        if (found_router == true)
        {
            node* pSubWalker = pWalker->pSubnet;
            
            while (pSubWalker != NULL)
            {
                if (pSubWalker->ip[IPSEGMENTS - 1] == ip[IPSEGMENTS -1])
                    return pSubWalker;
                pSubWalker = pSubWalker->pNext;
            }
        }
        
        pWalker = pWalker->pNext;
    } while (pWalker != r);

    return NULL;
}
