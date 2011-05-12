
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
    
    if (pTemp == NULL)
        return;

    do
    {
        pDel = pTemp;
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


/* print network */
void network::print()
{
    router* pTemp = m_pHead;
    
    if (pTemp == NULL)
        return;

    do
    {
        print_router(pTemp);
        printf("\n");
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
    
