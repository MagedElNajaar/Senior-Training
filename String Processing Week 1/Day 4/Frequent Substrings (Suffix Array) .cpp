//https://vjudge.net/contest/488773#problem/AC
#include "bits/stdc++.h"

using namespace std;
const int N = 2e5 + 1e2 + 9;
unsigned char str[N], Orgn[N];
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
char dumy;
int getInt() {
    char tmp[10];
    scanf("%[^\n]%c", tmp,&dumy);
    int ret;
    sscanf(tmp, "%d", &ret);
    return ret;
}

int main() {

    while (~scanf("%[^\n]%c", Orgn,&dumy)) {
        unsigned char *f, *t;
        for (f = Orgn, t = str; *f; f++, t++)
            *t = tolower(*f);
        *t = 0;
        buildSuffix();
        buildLcp();
        int n = getInt();
        while (n--) {
            int ql = getInt();
            int st = 0, ed, mx = 1, mxi;
            for(int i = 0;i<len;i++)
            {
                if(len - suff[i] - 1 >= ql){
                    mxi = suff[i];
                    break;
                }
            }
            while (st < len) {
                while (st < len and lcp[st] < ql)
                    st++;
                ed = st;
                while (ed < len and lcp[ed] >= ql)
                    ed++;
                if (ed - st + 1 > mx) mx = ed - st + 1, mxi = suff[st];
                st = ed;
            }
            unsigned char c = str[mxi + ql];
            str[mxi + ql] = 0;
            printf("%d %s\n", mx, str + mxi);
            str[mxi + ql] = c;
        }
    }
    return 0;
}
