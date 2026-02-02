#include <bits/stdc++.h>
using namespace std;
class Solution
{
    const int MOD = 1e9 + 7;

public:
    long long gcd(long long a, long long b)
    {
        if (b == 0)
            return a;
        return gcd(b, a % b);
    }

    long long lcm(long long a, long long b) { return (a / gcd(a, b)) * b; }

    int nthMagicalNumber(int n, int a, int b)
    {
        long long low = 1LL * min(a, b);
        long long high = 1LL * n * min(a, b);
        long long L = 1LL * lcm(a, b);

        while (low < high)
        {
            long long mid = low + (high - low) / 2;
            long long cnt = mid / a + mid / b - mid / L;

            if (cnt < n)
                low = mid + 1;
            else
                high = mid;
        }

        return (int)(low % MOD);
    }
};