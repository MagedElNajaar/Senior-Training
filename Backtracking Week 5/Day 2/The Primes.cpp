//https://vjudge.net/contest/495975#problem/D
#include<bits/stdc++.h>
#define FIO ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
typedef long long ll;

const int MOD=1e9+7, OO=0x3f3f3f3f;
const ll LOO=0x3f3f3f3f3f3f3f3f;
const long double EPS=1e-8;

const int N=161051+5;


vector<int> adj[N];
int si[]={0,1,2,3,4,0,0,0,0,0,0,4};
int sj[]={0,0,0,0,0,0,1,2,3,4,0,0};
int di[]={0,0,0,0,0,1,1,1,1,1,1,-1};
int dj[]={1,1,1,1,1,0,0,0,0,0,1,1};
int arr[]={0,1,2,3,4,5,6,7,8,9,10,11}, sz=12;
int grid[5][5];

vector<vector<vector<int>>>res;


int read(int ch){
  int i=si[ch], j=sj[ch];
  int s=0;
  for(int k=0; k<5; k++){
    s*=11;
    s+=grid[i][j];
    i+=di[ch];
    j+=dj[ch];
  }
  return s;
}


void write(int x, int ch, int base){
  int p=base*base*base*base;
  int i=si[ch], j=sj[ch];
  for(int k=0; k<5; k++){
    grid[i][j]=x/p%base;
    i+=di[ch];
    j+=dj[ch];
    p/=base;
  }
}

void backTrack(){
  if(sz==0){
    vector<vector<int>>vv(5);
    int i=0;
    for(auto& v : vv){
      v=vector<int>(grid[i], grid[i]+5);
      i++;
    }
    res.push_back(vv);
    return;
  }
  int mn=INT_MAX, best_i;
  int temp, ch;
  for(int i=0; i<sz; i++){
    int j=arr[i];
    int b11=read(j);
    int cnt=adj[b11].size();
    if(cnt<mn){
      mn=cnt;
      best_i=i;
      temp=b11;
      ch=j;
    }
  }
  swap(arr[best_i], arr[--sz]);

  for(int& x : adj[temp]){
    write(x, ch, 10);
    backTrack();
  }
  write(temp, ch, 11);
  swap(arr[best_i], arr[sz++]);

}

bool isPrime(ll n){
  for(ll i=2; i*i<=n; i++)
    if(n%i==0)
      return 0;
  return 1;
}

void addToShemes(int i){
  for(int mask=0; mask < (1<<5); mask++){
    int x=i, j=4, p=1, d, s=0;
    while(x){
      if((mask>>j) & 1){
        d=10;
      }
      else{
        d=x%10;
      }
      s+=p*d;
      x/=10;
      j--;
      p*=11;
    }
    adj[s].push_back(i);
  }
}

int solve(int sum){
  int cnt=0;
  for(int i=10001; i<100000; i++){
    int x=i, s=0;
    while(x){
      s+=x%10;
      x/=10;
    }
    if(s!=sum || !isPrime(i)) continue;
    addToShemes(i);
    // cnt++;
  }
  return cnt;
}


int main(){
  FIO 
  // freopen("input.txt","rt",stdin);
  // freopen("output.txt","wt",stdout);
  fill((int*)grid, (int*)grid+25, 10);
  int sum;
  cin>>sum>>grid[0][0];
  solve(sum);

  backTrack();

  sort(res.begin(), res.end());
  string sp="";
  for(auto& vv : res){
    cout<<sp;
    sp="\n";
    for(auto& v : vv){
      for(auto& x : v) cout<<x;
      cout<<'\n';
    }
  }
  
  return 0;
}
