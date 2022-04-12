//https://vjudge.net/contest/488773#problem/AB
#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 9;
char str[N];
int suff[N], rnk[N], newRank[N], len;
int lcp[N];

void buildLcp() {
    int cnt = 0;
    for (int i = 0; str[i]; i++) {
        int j = suff[rnk[i] - 1];
        while (str[i + cnt] == str[j + cnt]) cnt++;
        lcp[rnk[i]] = cnt;
        if (cnt) cnt--;
    }

}

void buildSuffix() {

    for (len = 0; !len || str[len - 1]; len++) {
        suff[len] = len;
        rnk[len] = str[len];
    }
    int h = 1;
    do {
        auto cmp = [h](int a, int b) {
            return rnk[a] < rnk[b] || rnk[a] == rnk[b] && rnk[a + h] < rnk[b + h];
        };
        sort(suff, suff + len, cmp);
        newRank[0] = 0;
        for (int i = 1; i < len; i++)
            newRank[i] = newRank[i - 1] + cmp(suff[i - 1], suff[i]);
        for (int i = 0; i < len; i++)
            rnk[suff[i]] = newRank[i];
        h <<= 1;
    } while (newRank[len - 1] != len - 1);
}

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s%s", str, str + n + 1);
    str[n] = '#';
    buildSuffix();
    buildLcp();
    int mx = 0, mxi;
    for (int i = 1; i < len; i++)
        if ((suff[i] < n) != (suff[i - 1] < n))
            if (lcp[i] > mx) {
                mx = lcp[i];
                mxi = suff[i];
            }
    str[mx + mxi] = 0;
    printf("%s", str + mxi);
    return 0;
}
