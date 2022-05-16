//https://vjudge.net/contest/495976#problem/A
#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

#define ll long long
#define mem(dp, num) memset(dp,num,sizeof dp);
#define memN(dp, num, n) memset(dp[0],num,n*sizeof dp[0]);
const int N = 1e5 + 9, M = 2e3 + 9, OO = 0x3f3f3f3f, MOD = 1e7;
int n, m, mod;

struct mul {
    int d;

    mul(int d) : d(d) {
    }

    vector<vector<int>> operator()(const vector<vector<int>> &a, const vector<vector<int>> &b) {
        vector<vector<int>> ret(a.size(), vector<int>(b[0].size()));
        for (int i = 0; i < ret.size(); i++)
            for (int j = 0; j < ret[i].size(); j++) {
                int &ref = ret[i][j];
                for (int k = 0; k < b.size(); k++) {
                    ref += a[i][k] * 1ll * b[k][j] % mod;
                    if (ref >= mod) ref -= mod;
                }
            }
        return ret;
    }
};

vector<vector<int>> identity_element(const mul &m) {
    vector<vector<int>> ret(m.d, vector<int>(m.d));
    for (int i = 0; i < m.d; i++)
        ret[i][i] = 1;
    return ret;
}

ll p(ll x, ll y) {
    ll ret = 1;
    while (y) {
        if (y & 1) ret *= x;
        x *= x;
        y >>= 1;
    }
    return ret;
}


int main() {
    while (~scanf("%d%d", &n, &m)) {
        mod = 1 << m;
        vector<vector<int>> mat = {{0, 1},
                                   {1, 1}}, v = {{0},
                                                 {1}};
        mul mm(2);
        mat = power(mat, n, mm);
        v = mm(mat, v);
        cout << v[0][0] << endl;
    }


    return 0;
}
