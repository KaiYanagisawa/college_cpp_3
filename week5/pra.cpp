#include <iostream>
int main()
{
    int x;
    int ptr = 10;
    int *a = &ptr;
    x = *a;
    std::cout << x;
}