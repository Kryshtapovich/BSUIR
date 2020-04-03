#include "ll_cycle.h"

bool ll_has_cycle(node *head) 
{
    node* turtle = head;
    node* hare = head;

    while (turtle && hare && hare->next)
    {
        turtle = turtle->next;
        hare = hare->next->next;

        if(turtle == hare)
        {
            return true;
        }
    }
    
    return false;
}