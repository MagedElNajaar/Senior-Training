//https://vjudge.net/problem/UVA-10304
#include <bits/stdc++.h>

using namespace std;
int dp[251][251];
int freq[251],root[251][251];
int n;

int solve() {
    for (int len = 1; len <= n; len++) {
        for (int st = 1; st + len - 1 <= n; st++) {
            int ed = st + len - 1;
            int &ret = dp[st][ed];
            if (len == 1) {
                ret = 0;
                root[st][1] = st;
                continue;
            }
            ret = INT_MAX;
            for (int i = root[st][len-1]; i <= root[st+1][len - 1]; i++) {
                int cur = dp[st][i - 1] + dp[i + 1][ed] + freq[i - 1] - freq[st - 1] + freq[ed] - freq[i];
                if(cur < ret){
                    ret = cur;
                    root[st][len] = i;
                }
            }
        }
    }
    return dp[1][n];
}

int main() {

    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; i++)
            scanf("%d", &freq[i]), freq[i] += freq[i - 1];
        printf("%d\n", solve());
    }
    return 0;
}
