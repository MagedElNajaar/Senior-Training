//https://vjudge.net/contest/488773#problem/Z
#include "bits/stdc++.h"

using namespace std;
const int N = 1e5 + 1e2 + 9;
unsigned char str[N];
int suff[N], rnk[N], newRank[N], len;
int lcp[N], ID[N], frq[109];


struct monotonicQueue {
    queue<int> q;
    deque<int> dq;

    void push(int x) {
        q.push(x);
        while (dq.size() and dq.back() > x)
            dq.pop_back();
        dq.push_back(x);

    }

    void pop() {
        if (dq.front() == q.front())
            dq.pop_front();
        q.pop();
    }

    int front() {
        return q.front();
    }

    int getMin() {
        return dq.front();
    }
};

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
    char *sep = "";
    while (scanf("%d", &n), n) {
         char *s = (char*)str;
        int *p = ID;
        for (int i = 0; i < n; i++) {
            scanf("%s", s);
           do {
               *p++ = i;
           } while (*s++);
            *(s-1) = -1 - i;
        }
        *s = *p = 0;
        buildSuffix();
        buildLcp();
        int st = 0, ed = 0, cnt = 0;
        memset(frq, 0, n * sizeof frq[0]);
        monotonicQueue mQ;
        int mx = 0;
        vector<int> ans;
        while (ed < len) {
            while (ed < len and cnt * 2 <= n) mQ.push(lcp[ed]), cnt += !frq[ID[suff[ed++]]]++;
            while (cnt * 2 > n) mQ.pop(), cnt -= !--frq[ID[suff[st++]]];
            if (mQ.getMin() > mx) ans.clear(), mx = mQ.getMin();
            if (mQ.getMin() == mx and mx) {
                ans.push_back(suff[st]);
            }
        }
        set<string> stt;
        for (auto &it: ans) {
            unsigned char c = str[it + mx];
            str[it + mx] = 0;
            stt.insert((char*)str + it);
            str[it + mx] = c;
        }
        cout << sep;
        if (!mx) cout << "?\n";
        else {
            for (auto &it: stt) cout << it << "\n";
        }
        sep = "\n";
    }
    return 0;
}
