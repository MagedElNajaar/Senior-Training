//https://vjudge.net/contest/490538#problem/A
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define mem(dp, num) memset(dp,num,sizeof dp);
#define memN(dp, num, n) memset(dp[0],num,n*sizeof dp[0]);
const int N = 1e3 + 9, M = 2e3 + 9, OO = 0x3f3f3f3f, MOD = 1e7;
int n, dp[N][N], mth[N][N], dp2[N][N];
char s[N], s1[N];

int main() {
    while (scanf("%d", &n), n) {
        scanf("%s%s", s, s1);
        int n1 = strlen(s), n2 = strlen(s1);
        for (int i = n1; ~i; i--) {
            for (int j = n2; ~j; j--) {
                int &ret = dp[i][j];
                int &res = mth[i][j];
                int &ret2 = dp2[i][j];
                if (!s[i] || !s1[j]) {
                    ret2 = ret = res = 0;
                    continue;
                }
                res = 0;
                ret2 = max(dp2[i + 1][j], dp2[i][j + 1]);
                ret = 0;
                if (s[i] == s1[j]) {
                    res = max(res, 1 + mth[i + 1][j + 1]);
                    if (res >= n)
                        ret = dp2[i + n][j + n] + n;
                    if (dp[i + 1][j + 1]) ret = max(ret, 1 + dp[i + 1][j + 1]);
                    ret2 = max(ret2,ret);
                }
            }
        }
        printf("%d\n", dp2[0][0]);
    }
    return 0;
}
