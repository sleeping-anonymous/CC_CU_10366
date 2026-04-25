#include <bits/stdc++.h>
using namespace std;

// Function to compute gcd and coefficients x, y
// such that: ax + by = gcd(a, b)
long long extended_gcd(long long a, long long b, long long &x, long long &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    long long x1, y1;
    long long gcd = extended_gcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

int main()
{
    long long a, b;
    cin >> a >> b;

    long long x, y;
    long long gcd = extended_gcd(a, b, x, y);

    cout << "GCD: " << gcd << endl;
    cout << "Coefficients x and y: " << x << " " << y << endl;
    cout << "Check: " << a << "*" << x << " + " << b << "*" << y
         << " = " << (a * x + b * y) << endl;

    return 0;
}