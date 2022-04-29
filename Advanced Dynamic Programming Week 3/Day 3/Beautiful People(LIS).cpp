//https://vjudge.net/contest/490538#problem/B
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define mem(dp, num) memset(dp,num,sizeof dp);
#define memN(dp, num, n) memset(dp[0],num,n*sizeof dp[0]);
const int N = 1e5 + 9, M = 2e3 + 9, OO = 0x3f3f3f3f, MOD = 1e7;
int n, prv[N];
pair<int, int> arr[N];
int bestSeq[N];

struct cmp {
    bool operator()(int a, int b) const{
        return arr[a].second < arr[b].second;
    }
};

map<int, set<int, cmp>> mp;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &arr[i].first, &arr[i].second), mp[arr[i].first].insert(i);
    bestSeq[0] = n;
    arr[n] = {INT_MIN, INT_MIN};
    arr[n + 1] = {INT_MAX, INT_MAX};
    int mx = 0, bestl;
    for (auto &it: mp) {
        for (auto it2 = it.second.rbegin(); it2 != it.second.rend(); it2++) {
            int std = *it2;
            auto cmp = [](int a, int b) { return arr[a].second < arr[b].second; };
            int lb = lower_bound(bestSeq, bestSeq + mx + 1, std, cmp) - bestSeq;
            if (mx < lb) {
                mx = lb;
                bestl = std;
            }
            prv[std] = bestSeq[lb - 1];
            bestSeq[lb] = std;
        }

    }
    printf("%d\n", mx);
    for (int i = bestl; i != n; i = prv[i])
        printf("%d%c", i + 1, " \n"[prv[i] == n]);
    return 0;
}
