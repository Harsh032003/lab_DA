// factorial.cpp
#include <iostream>
using namespace std;

int factorial(int n)
{
    int result = 1; // Assignment

    for (int i = 1; i <= n; i++)
    {                // Loop
        result *= i; // Assignment
    }

    return result; // Return statement
}

int main()
{
    int number = 5; // Assignment
    cout << "Factorial of " << number << " is " << factorial(number) << endl;
    return 0;
}
