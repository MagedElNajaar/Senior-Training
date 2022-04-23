//https://vjudge.net/problem/UVA-1099
#include <bits/stdc++.h>

using namespace std;

int arr[20], dp[1 << 15][101], area[1 << 15];
int n;

int solve(int h, int m) {
    if (!(m & (m - 1))) return 1;
    int &ret = dp[m][h];
    if (~ret) return ret;
    ret = 0;
    int w = area[m] / h;
    for (int i = (m - 1) & m; i and !ret; i = (i - 1) & m) {
        int j = ~i & m;
        if(j > i) break;
        if (area[i] % w == 0)
            ret |= solve(w, i) and solve(w, j);
        if (!ret and area[i] % h == 0)
            ret |= solve(h, i) and solve(h, j);
    }
    return ret;
}

int main() {
    int h, w, tc = 1;
    while (scanf("%d", &n), n) {
        scanf("%d %d", &h, &w);
        for (int i = 0; i < n; i++)
            scanf("%d", arr + i);
        memset(dp, -1, sizeof dp);
        for (int i = 0; i < (1 << n); i++) {
            area[i] = 0;
            for (int j = 0; j < n; j++) {
                if ((i >> j) & 1) area[i] += arr[j];
            }
        }
        printf("Case %d: ", tc++);
        if (area[(1 << n) - 1] != w * h or !solve(h, (1 << n) - 1)) {
            puts("No");

        } else puts("Yes");


    }
    return 0;
}
