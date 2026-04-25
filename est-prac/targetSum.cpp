#include <bits/stdc++.h>
using namespace std;

int solve(vector<int> &nums, int target, int idx, int val)
{
    if (idx == nums.size())
    {
        return val == target;
    }

    return solve(nums, target, idx + 1, val + nums[idx]) +
           solve(nums, target, idx + 1, val - nums[idx]);
}

int main()
{
    vector<int> nums = {1, 1, 1, 1, 1};
    int target = 3;

    cout << solve(nums, target, 0, 0) << endl;
}
