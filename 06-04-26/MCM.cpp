// // C++ code to implement the
// // matrix chain multiplication using recursion
// #include <bits/stdc++.h>
// using namespace std;

// // Matrix Ai has dimension arr[i-1] x arr[i]
// int minMultRec(vector<int> &arr, int i, int j)
// {

//     // If there is only one matrix
//     if (i + 1 == j)
//         return 0;

//     int res = INT_MAX;

//     for (int k = i + 1; k < j; k++)
//     {
//         int curr = minMultRec(arr, i, k) + minMultRec(arr, k, j) + arr[i] * arr[k] * arr[j];

//         res = min(curr, res);
//     }

//     // Return minimum count
//     return res;
// }

// int matrixMultiplication(vector<int> &arr , vector<vector<int>>& dp)
// {

//     int n = arr.size();
//     return minMultRec(arr, 0, n - 1 ,);
// }

// int main()
// {
//     vector<int> arr = {2, 1, 3, 4};
//     int n = arr.size();
//     vector<vector<int>> dp(n,vector<int>(n,-1));
//     cout << matrixMultiplication(arr ,dp );
//     return 0;
// }

// C++ code to implement the
// matrix chain multiplication using tabulation
#include <bits/stdc++.h>
using namespace std;

int matrixMultiplication(vector<int> &arr)
{

    int n = arr.size();

    // Create a 2D DP array to store the minimum
    // multiplication costs
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Fill the DP array.
    // Here, len is the chain length
    for (int len = 2; len < n; len++)
    {
        for (int i = 0; i < n - len; i++)
        {
            int j = i + len;
            dp[i][j] = INT_MAX;

            for (int k = i + 1; k < j; k++)
            {
                int cost = dp[i][k] + dp[k][j] + arr[i] * arr[k] * arr[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    // The minimum cost is stored in dp[0][n-1]
    return dp[0][n - 1];
}

int main()
{

    vector<int> arr = {2, 1, 3, 4};
    cout << matrixMultiplication(arr);
    return 0;
}