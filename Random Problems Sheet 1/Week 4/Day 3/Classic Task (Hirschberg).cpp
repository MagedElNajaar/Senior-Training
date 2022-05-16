//https://csacademy.com/contest/archive/task/classic-task/


#include <bits/stdc++.h>

using namespace std;
const int OO = 1e9;

const int N = 1e4 + 5;
int U[N], V[N], n, m;
long long memo1[2][N], memo2[2][N];

int get(int i, int j) {
    return (U[i] + j) ^ (V[j] + i);
}

long long *solve1(int minI, int maxI, int minJ, int maxJ) {

    for (int i = maxI + 1; i >= minI; i--) {
        for (int j = maxJ + 1; j >= minJ; j--) {
            long long &ret = memo1[i & 1][j];
            if (i == maxI + 1 || j == maxJ + 1)
                ret = 1e18;
            else if (i == maxI && j == maxJ) {
                ret = get(i, j);
            } else {
                ret = min(memo1[(i + 1) & 1][j], memo1[i & 1][j + 1]) + get(i, j);
            }

        }
    }

    return memo1[minI & 1];
}

long long *solve2(int minI, int maxI, int minJ, int maxJ) {
    for (int i = minI - 1; i <= maxI; i++) {
        for (int j = minJ - 1; j <= maxJ; j++) {
            long long &ret = memo2[i & 1][j];
            if (i == minI - 1 || j == minJ - 1)
                ret = 1e18;
            else if (i == minI && j == minJ) {
                ret = get(i, j);
            } else {
                ret = min(memo2[(i - 1) & 1][j], memo2[i & 1][j - 1]) + get(i, j);
            }

        }
    }

    return memo2[maxI & 1];

}

void Hirschberg(int s, int e, int minJ, int maxJ) {
    if (s == e) {
        for (int j = minJ; j < maxJ; j++)
            printf("R");
        return;
    }
    if (e < s)
        return;

    int mid = (s + e) / 2;
    long long *d1 = solve2(s, mid, minJ, maxJ);
    long long *d2 = solve1(mid + 1, e, minJ, maxJ);


    long long mn = 1e18, bestJ = 1;
    for (int j = minJ; j <= maxJ; j++) {
        long long x = d1[j] + d2[j];
        if (x < mn) {
            mn = x;
            bestJ = j;
        }
    }

    Hirschberg(s, mid, minJ, bestJ);
    printf("D");
    Hirschberg(mid + 1, e, bestJ, maxJ);
}


int main() {

    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", U + i);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", V + i);
    }

    Hirschberg(1,n,1,m);
    puts("");
}
