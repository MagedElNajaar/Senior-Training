//https://vjudge.net/problem/FZU-1499
//https://vjudge.net/problem/计蒜客-T3496


#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define mem(dp, num) memset(dp,num,sizeof dp);
#define memN(dp, num, n) memset(dp[0],num,n*sizeof dp[0]);
const int N = 130, M = 2e3 + 9, OO = 0x3f3f3f3f, MOD = 1e7;
int boards[N], frq[N], req[M];
int sumBoards;


bool BT(int i, int len, int waste, int cnt, int mxLen) {
    if (waste < 0) return false;
    if (!cnt) return true;
    bool canCut = false;
    for (int j = len; j <= mxLen; j++) {
        if (!frq[j]) continue;
        if (j > boards[i]) break;
        canCut = true;
        boards[i] -= j;
        frq[j]--;
        bool ret = false;
        if (BT(i, j, waste, cnt - 1, mxLen)) ret = true;
        boards[i] += j;
        frq[j]++;
        if (ret) return true;
    }
    if (!canCut) return BT(i + 1, 1, waste - boards[i], cnt, mxLen);
    return false;
}

bool solve(int cnt) {
    mem(frq, 0);
    int sumReq = 0;
    for (int i = 0; i < cnt; i++) frq[req[i]]++, sumReq += req[i];
    return BT(0, 1, sumBoards - sumReq, cnt, req[cnt - 1]);
}

int main() {
    int n, m;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", boards + i), sumBoards += boards[i];
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
        scanf("%d", req + i);
    int st = 0, ed = m;
    sort(req, req + m);
    sort(boards, boards + n);
    //reverse(boards, boards + n);
    while (st < ed) {
        int mid = st + (ed - st + 1) / 2;
        if (solve(mid)) st = mid;
        else ed = mid - 1;

    }
    cout << st << endl;
    return 0;
}
