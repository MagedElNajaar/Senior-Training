//https://vjudge.net/contest/490713#problem/R
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define mem(dp, num) memset(dp,num,sizeof dp);
#define memN(dp, num, n) memset(dp[0],num,n*sizeof dp[0]);
const int N = 1e4 + 9, M = 100 + 9, OO = 0x3f3f3f3f, MOD = 1e7;
string a, b;
int dp[2][M][M][2][2], k;

int solve() {
    for (int i = a.size(); ~i; i--)
        for (int n = 0; n < k; n++)
            for (int s = 0; s < min(100, k); s++)
                for (int eqlA = 0; eqlA < 2; eqlA++)
                    for (int eqlB = 0; eqlB < 2; eqlB++) {
                        int &ret = dp[i & 1][n][s][eqlA][eqlB];
                        if (i == a.size()) {
                            ret = (n == 0 and s == 0);
                            continue;
                        }
                        ret = 0;
                        for (int d = eqlA ? a[i] - '0' : 0; d <= (eqlB ? b[i] - '0' : 9); d++) {
                            ret += dp[(i + 1) & 1][(n * 10 + d) % k][(s + d) % k][eqlA and a[i] - '0' == d][
                                    eqlB and b[i] - '0' == d];
                        }
                    }

    return dp[0][0][0][1][1];
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> a >> b >> k;
        while (a.size() < b.size()) a = "0" + a;
        if (k > 85)
            cout << "Case " << i << ": " << 0 << endl;
        else
            cout << "Case " << i << ": " << solve() << endl;
    }

return 0;
}
