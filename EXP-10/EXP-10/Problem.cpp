#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> counts(n, 0);
        vector<pair<int,int>> arr; // {value, original index}
        
        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }
        
        mergeSort(arr, 0, n - 1, counts);
        return counts;
    }

private:
    void mergeSort(vector<pair<int,int>>& arr, int left, int right, vector<int>& counts) {
        if (left >= right) return;
        
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, counts);
        mergeSort(arr, mid + 1, right, counts);
        merge(arr, left, mid, right, counts);
    }

    void merge(vector<pair<int,int>>& arr, int left, int mid, int right, vector<int>& counts) {
        vector<pair<int,int>> temp;
        int i = left, j = mid + 1;
        int rightCount = 0;

        while (i <= mid && j <= right) {
            if (arr[i].first <= arr[j].first) {
                counts[arr[i].second] += rightCount;
                temp.push_back(arr[i]);
                i++;
            } else {
                rightCount++;
                temp.push_back(arr[j]);
                j++;
            }
        }

        while (i <= mid) {
            counts[arr[i].second] += rightCount;
            temp.push_back(arr[i]);
            i++;
        }

        while (j <= right) {
            temp.push_back(arr[j]);
            j++;
        }

        for (int k = left; k <= right; k++) {
            arr[k] = temp[k - left];
        }
    }
};