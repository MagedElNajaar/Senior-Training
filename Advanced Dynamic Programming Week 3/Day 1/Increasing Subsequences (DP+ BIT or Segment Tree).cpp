//https://vjudge.net/problem/SPOJ-INCSEQ
#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 9, K = 59, MOD = 5e6;
int arr[N], sorted[N];
int mx = 0;

struct BIT {
    int arr[N];

    void add(int i, int v) {
        for (i++; i <= mx + 1; i += (i & -i)) {
            arr[i - 1] += v;
            if (arr[i - 1] >= MOD)
                arr[i - 1] -= MOD;
        }
    }

    int get(int i) {
        int ret = 0;
        for (i++; i; i -= (i & -i)) {
            ret += arr[i - 1];
            if (ret >= MOD)
                ret -= MOD;
        }
        return ret;
    }
} dp[K];

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", arr + i), sorted[i] = arr[i];
    sort(sorted, sorted + n);

    for (int i = 0; i < n; i++) {
        arr[i] = lower_bound(sorted, sorted + n, arr[i]) - sorted;
        mx = max(mx, arr[i]);
    }
    for (int i = 0; i < n; i++) {
        int v = arr[i];
        dp[1].add(v, 1);
        for (int j = 2; j <= k; j++) {
            dp[j].add(v, dp[j - 1].get(v - 1));
        }
    }
    cout << dp[k].get(mx) << "\n";


    return 0;
}
