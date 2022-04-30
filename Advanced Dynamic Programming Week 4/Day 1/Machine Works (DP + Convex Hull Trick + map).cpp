//https://vjudge.net/contest/490713#problem/O
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define mem(dp, num) memset(dp,num,sizeof dp);
#define memN(dp, num, n) memset(dp,num,(n)*sizeof dp[0]);
const int N = 1e5 + 9, OO = 0x3f3f3f3f, MOD = 1e7;
int S[N], P[N], B[N], D[N], sorted[N];
ll dp[N];
int n;
#define M first
#define C second
typedef pair<ll, ll> seg;

double intersect(const seg &l1, const seg &l2) {
    return (l2.C - l1.C) / (l1.M - l2.M - 0.0);
}

bool usefull(const seg &l1, const seg &l2, const seg &l3) {
    double d12 = intersect(l1, l2);
    double d23 = intersect(l2, l3);
    return d12 < d23;
}

ll subs(const seg &s, ll x) {
    return s.M * x + s.C;
}

ll solve() { //day index
    map<ll, ll> mp;
    mp[0] = 0;
    for (int ii = 0; ii <= n + 1; ii++) {
        auto &ret = dp[ii];

        int i = sorted[ii];
        ret = 0;
        /*for (auto &it: mp) {
            ll m, c;
            tie(m, c) = it;
            ll x = D[i];
            ll cur = m * x + c;
            ret = max(ret, cur);
        }*/
        ll x = D[i];
        while (mp.size() > 1) {
            auto s = mp.begin(), f = s++;
            if (subs(*s, x) >= subs(*f, x)) {
                mp.erase(f);
            } else break;
        }
        ll m, c;
        tie(m, c) = *mp.begin();
        ret = m * x + c;
        m = P[i];
        c = ret + S[i] - B[i] + (-D[i] - 1ll) * P[i];
        if (ret >= B[i]) {
            auto l2 = mp.emplace(m, c).first;
            l2->second = max(l2->second, c);
            if (l2 != mp.begin() and l2 != --mp.end()) {
                auto l1 = l2, l3 = l2;
                l1--, l3++;
                if (!usefull(*l1, *l2, *l3)) {
                    mp.erase(l2);
                    continue;
                }
            }
            while(l2 != mp.begin()){
                auto p = l2;
                if(--p == mp.begin()) break;
                auto q = p;
                if(!usefull(*--q,*p,*l2)) mp.erase(p);
                else break;
            }
        }
        /*for (int jj = 0; jj < ii; jj++) {
            int j = sorted[jj];
            ll money = dp[jj];
            if (money < B[j]) continue;
            //ll cur = money + S[j] - B[j] + (D[i] - D[j] - 1) * P[j];
            //ll cur = money + S[j] - B[j] + D[i] * P[j] + (-D[j] - 1) * P[j];
            ll m = P[j];
            ll c = money + S[j] - B[j] + (-D[j] - 1) * P[j];
            ll x = D[i];
            ll cur = m * x + c;
            ret = max(ret, cur);
        }
    }*/
    }
    return dp[n + 1];
}

int main() {
    int t = 0, days;
    while (scanf("%d%d%d", &n, &S[0], &days), n or S[0] or days) {
        D[n + 1] = days + 1;
        for (int i = 1; i <= n; i++)
            scanf("%d%d%d%d", D + i, B + i, S + i, P + i), sorted[i] = i;
        memN(dp, -1, n + 2);
        sorted[n + 1] = n + 1;
        sort(sorted, sorted + n + 1, [](int a, int b) { return D[a] < D[b]; });
        printf("Case %d: %lld\n", ++t, solve());
    }
    return 0;
}
