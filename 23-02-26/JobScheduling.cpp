#include <bits/stdc++.h>
using namespace std;

class JobScheduling
{
public:
    vector<int> jobSequencing(vector<int> &deadline, vector<int> &profit)
    {
        int n = deadline.size();

        // store jobs as {deadline, profit}
        vector<pair<int, int>> jobs;
        for (int i = 0; i < n; i++)
        {
            jobs.push_back({deadline[i], profit[i]});
        }

        // sort by deadline (ascending)
        sort(jobs.begin(), jobs.end());

        // min-heap to store selected profits
        priority_queue<int, vector<int>, greater<int>> pq;

        int totalProfit = 0;

        for (int i = 0; i < n; i++)
        {
            int time = jobs[i].first;
            int p = jobs[i].second;

            if ((int)pq.size() < time)
            {
                pq.push(p);
                totalProfit += p;
            }
            else if (!pq.empty() && pq.top() < p)
            {
                totalProfit -= pq.top();
                pq.pop();

                pq.push(p);
                totalProfit += p;
            }
        }

        // result: number of jobs done, total profit
        return {(int)pq.size(), totalProfit};
    }
};