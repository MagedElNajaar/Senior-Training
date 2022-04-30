//https://vjudge.net/contest/490713#problem/O
#include <bits/stdc++.h>
using namespace std;

int n;
long long S[int(1e5 + 9)], P[int(1e5 + 9)], B[int(1e5 + 9)], D[int(1e5 +9)];
int Sorted[int(1e5 + 9)];
long long memo[int(1e5 +9)];

long long solve(int curr){
    int i = Sorted[curr];
    long long &ret = memo[curr];
    if(~ret) return ret; // ~ same as != -1 "Not working with double"
    ret = 0;
    for(int prev = 0;prev < curr;prev++){
        int j = Sorted[prev];
        long long m = solve(prev); //Money I have in day j
        if(m < B[j]) continue;
        long long profit = m - B[j] + S[j] + P[j] * (D[i] - D[j] - 1);
        ret = max(ret,profit);
    }
    return ret;
}

int main(){
    int N,Days,t=0;
    while(cin>>N>>S[0]>>Days && N && S[0] && Days){
        t++;
        memset(memo + 1,-1, (N+1) * sizeof(memo[0]));
        D[N+1] = Days + 1;
        for(int i = 1; i <= N;i++){
            cin>>D[i]>>B[i]>>S[i]>>P[i];
            Sorted[i] = i;
        }
        Sorted[N+1] = N+1;
        sort(Sorted + 1,Sorted + (N+1),[](int i,int j){return D[i]<D[j];});
        cout << "Case " << t <<": " <<solve(N+1) << endl;
    }
}
