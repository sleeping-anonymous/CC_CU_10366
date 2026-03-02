#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    unordered_map<string, int> mp;
    vector<string> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        mp[arr[i]]++;
    }

    string ans = "";
    int cnt = 0;

    for (auto &mpp : mp)
    {
        if (mpp.second > cnt)
        {
            cnt = mpp.second;
            ans = mpp.first;
        }
    }

    cout << ans;
    return 0;
}