#include <stdio.h>


void calculate(int a)
{
    if (a == 0)
    {
        return;
    }
    a = 6;
    calculate(a);
}
int main(void)
{
    int a = 5;
    calculate(a);
}