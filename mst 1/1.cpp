#include <bits/stdc++.h>
using namespace std;

static int cmp(vector<int> &a, vector<int> &b)
{
    return (b[1] - b[0]) < (a[1] - a[0]);
}

int main()
{
    vector<vector<int>> energy = {{1, 2}, {2, 4}, {4, 8}};

    sort(energy.begin(), energy.end(), cmp);

    int curr = 0;
    int ans = 0;

    for (int i = 0; i < energy.size(); i++)
    {
        int mini = energy[i][1];
        int act = energy[i][0];

        if (curr < mini)
        {
            ans += mini - curr;
            curr = mini;
        }
        curr -= act;
    }
    cout << ans;
    return 0;
}