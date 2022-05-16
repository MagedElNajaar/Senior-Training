//https://vjudge.net/contest/495975#problem/B

#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define mem(dp, num) memset(dp,num,sizeof dp);
#define memN(dp, num, n) memset(dp[0],num,n*sizeof dp[0]);
const int N = 1e5 + 9, M = 2e3 + 9, OO = 0x3f3f3f3f, MOD = 1e7;
int frq[10];
ll n;

bool BT(int idx, ll a = 0, ll b = 0, ll p = 1, bool az = false, bool bz = false) {
    if (!idx) return a * b == n;
    if ((a * b) % p != n % p) return false;
    for (int i = az; i < 10; i++) {
        if (!frq[i]) continue;
        frq[i]--;
        for (int j = bz; j < 10; j++) {
            if (!frq[j]) continue;
            frq[j]--;
            if (BT(idx - 2, a + p * i, b + p * j, p * 10, i == 0, j == 0))
                return true;
            frq[j]++;
        }
        frq[i]++;
    }
    return false;
}

int main() {
    while (cin >> n, n) {
        ll tmp = n, len = 0;
        memset(frq, 0, sizeof frq);
        while (tmp) {
            frq[tmp % 10]++;
            len++;
            tmp /= 10;
        }
        cout << n << ": " << (BT(len) ? "yes\n" : "no\n");
    }

}
