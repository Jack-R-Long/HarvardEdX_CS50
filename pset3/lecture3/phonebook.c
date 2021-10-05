#include <stdio.h>
#include <cs50.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    person people[2];
    
    people[0].name = "Brian";
    people[0].number = "1-415-329-0941";
    
    people[1].name = "Jack";
    people[1].number = "1-210-231-3221";
    
    for (int i = 0; i < 2; i++)
    {
        if (strcmp(people[i].name, "Jack") == 0)
        {
            printf("Found Jack!\n");
            return 0;
        }
    }
    printf("Jack not found!\n");
    return 1;
}