#include <bits/stdc++.h>
using namespace std;

// Step 1: Build LPS array
vector<int> buildLPS(const string &pattern)
{
    int m = pattern.length();
    vector<int> lps(m, 0);

    int len = 0; // length of previous longest prefix suffix
    int i = 1;

    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1]; // fallback
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// Step 2: KMP Search
vector<int> KMPsearch(const string &text, const string &pattern)
{
    int n = text.length();
    int m = pattern.length();

    vector<int> lps = buildLPS(pattern);
    vector<int> result;

    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            result.push_back(i - j); // match found at index
            j = lps[j - 1];          // continue searching
        }
        else if (i < n && text[i] != pattern[j])
        {
            if (j != 0)
            {
                j = lps[j - 1]; // fallback using LPS
            }
            else
            {
                i++;
            }
        }
    }
    return result;
}

int main()
{
    string text = "ababcabcabababd";
    string pattern = "ababd";

    vector<int> matches = KMPsearch(text, pattern);

    for (int idx : matches)
    {
        cout << "Pattern found at index: " << idx << endl;
    }

    return 0;
}