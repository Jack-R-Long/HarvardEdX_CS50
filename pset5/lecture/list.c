#include <stdio.h>
#include <stdlib.h>

// Create a node struct
typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    // // How the computer actually creates an array of array[3]
    // int *list = malloc(3 * sizeof(int));
    // if (list == NULL)
    // {
    //     return 1; 
    // }
    // // pointer arthimitic | same as list[0] = 1 and so on
    // *list = 1;
    // *(list + 1) = 2;
    // *(list + 2) = 3;
    
    // // Copy array to insert a fourth value
    // int *tmp = realloc(list, 4 * sizeof(int));
    
    // for (int i = 0; i < 3; i++)
    // {
    //     tmp[i] = list[i];
    // }
    // tmp[4] = 4;
    // free(list);
    // list = tmp;
    // // Print the shit with a loop
    // free(list);
    
    
    // Linked lists begin

    
    // Instantiate a node
    node *list = NULL;
    
    node *n= malloc(sizeof(node));
    // always do this to catch mem errors
    if (n == NULL)
    {
        return 1; 
    }
    // Assign fields with the nice . * syntactic sugar ->
    n->number = 1;
    n->next = NULL;
    list = n;
    
    node *n= malloc(sizeof(node));
    // always do this to catch mem errors
    if (n == NULL)
    {
        free(list);
        return 1; 
    }
    n->number = 2;
    n->next = NULL;
    list->next = n;
    
    node *n= malloc(sizeof(node));
    // always do this to catch mem errors
    if (n == NULL)
    {
        free(list->next);
        free(list);
        return 1; 
    }
    n->number = 3;
    n->next = NULL;
    list->next->next = n;
    
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }
    // Free the nodes dynamically
    while (node *list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
        // Free list wihout breaking the 'chain'
    }
}