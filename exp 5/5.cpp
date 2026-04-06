#include <bits/stdc++.h>
using namespace std;

int main()
{

    int n, m;
    cin >> n >> m;

    unordered_set<string> st;

    // input stored strings
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        st.insert(s);
    }

    // process queries
    while (m--)
    {
        string s;
        cin >> s;

        bool found = false;

        for (int i = 0; i < s.size(); i++)
        {
            char original = s[i];

            for (char c : {'a', 'b', 'c'})
            {
                if (c == original)
                    continue;

                s[i] = c;

                if (st.count(s))
                {
                    found = true;
                    break;
                }
            }

            s[i] = original; // restore

            if (found)
                break;
        }

        cout << (found ? "YES\n" : "NO\n");
    }

    return 0;
}