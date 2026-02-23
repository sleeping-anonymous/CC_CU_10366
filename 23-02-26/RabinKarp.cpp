#include <bits/stdc++.h>
using namespace std;

class RabinKarp
{
public:
    static const int d = 256; // number of characters
    static const int q = 101; // prime modulus

    static void search(const string &text, const string &pattern)
    {

        int n = text.length();
        int m = pattern.length();

        int pHash = 0; // pattern hash
        int tHash = 0; // text window hash
        int h = 1;

        // compute h = pow(d, m-1) % q
        for (int i = 0; i < m - 1; i++)
        {
            h = (h * d) % q;
        }

        // initial hash for pattern and first window
        for (int i = 0; i < m; i++)
        {
            pHash = (d * pHash + pattern[i]) % q;
            tHash = (d * tHash + text[i]) % q;
        }

        // slide window over text
        for (int i = 0; i <= n - m; i++)
        {

            // check hash match
            if (pHash == tHash)
            {
                bool match = true;

                for (int j = 0; j < m; j++)
                {
                    if (text[i + j] != pattern[j])
                    {
                        match = false;
                        break;
                    }
                }

                if (match)
                {
                    cout << "Pattern found at index: " << i << endl;
                }
            }

            // compute next window hash
            if (i < n - m)
            {
                tHash = (d * (tHash - text[i] * h) + text[i + m]) % q;

                // ensure positive
                if (tHash < 0)
                    tHash += q;
            }
        }
    }
};

int main()
{
    string text = "abcabcabcadeba";
    string pattern = "cab";

    RabinKarp::search(text, pattern);
    return 0;
}