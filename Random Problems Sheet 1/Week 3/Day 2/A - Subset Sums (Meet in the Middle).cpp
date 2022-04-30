//https://vjudge.net/contest/491611#problem/A
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define mem(dp, num) memset(dp,num,sizeof dp);
#define memN(dp, num, n) memset(dp[0],num,n*sizeof dp[0]);
const int N = 1e5 + 9, M = 2e3 + 9, OO = 0x3f3f3f3f, MOD = 1e7;
ll sums[1 << 17], arr[34];

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int x, y;
    x = n / 2, y = n - x;
    for (int i = 0; i < (1 << x); i++)
        for (int j = 0; j < x; j++)
            if ((i >> j) & 1)sums[i] += arr[j];

    sort(sums, sums + (1 << x));
    ll res = 0;
    for (int i = 0; i < (1 << y); i++) {
        ll sum = 0;
        for (int j = 0; j < y; j++)
            if ((i >> j) & 1)sum += arr[j + x];
        res += upper_bound(sums, sums + (1 << x), b - sum) - lower_bound(sums, sums + (1 << x), a-sum);
    }

    cout << res << endl;
    return 0;
}
