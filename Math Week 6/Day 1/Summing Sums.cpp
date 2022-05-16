//https://vjudge.net/contest/495976#problem/B

#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

#define ll long long
#define mem(dp, num) memset(dp,num,sizeof dp);
#define memN(dp, num, n) memset(dp[0],num,n*sizeof dp[0]);
const int N = 5e4 + 9, M = 2e3 + 9, OO = 0x3f3f3f3f, MOD = 1e7;
int n, m, mod = 98765431;

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

int arr[N], sum;

int main() {
    int t;
    scanf("%d%d", &n, &t);
    for (int i = 0; i < n; i++) {
        scanf("%d", arr + i);
        sum += arr[i];
        if (sum >= mod) sum -= mod;
    }
    vector<vector<int>> mat = {{mod - 1, 1},
                               {0,       (n + mod - 1) % mod}}, v = {{0},
                                                                     {sum}};
    mul mm(2);
    mat = power(mat, t, mm);
    for (int i = 0; i < n; i++) {
        v[0][0] = arr[i];
        cout << mm(mat, v)[0][0] << endl;
    }

return 0;
}
