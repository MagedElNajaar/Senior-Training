// problem link: https://vjudge.net/problem/URAL-1517
#include<bits/stdc++.h>
#define FIO ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
typedef long long ll;

const int MOD=1e9+7, OO=0x3f3f3f3f;
const ll LOO=0x3f3f3f3f3f3f3f3f;
const long double EPS=1e-8;

const int N=2e5+5, ALPH=256;

unsigned char str[N];
int len;
int suff[N], newSuff[N];
int rnk[N], newRnk[N], gStart[N];
int* head=newRnk, *nxt=newSuff;
int LCP[N];


void buildLCP(){
  int cnt=0;
  for(int i=0; i<len-1; i++){
    int j=suff[rnk[i]-1];
    while(str[i+cnt]==str[j+cnt]) cnt++;
    LCP[rnk[i]]=cnt;
    if(cnt) cnt--;

  }
}

void buildSuff(){
  memset(head, -1, sizeof(head[0])*ALPH);
  for(len=0; !len || str[len-1]; len++){
    nxt[len]=head[str[len]];
    head[str[len]]=len;
  }
  int currSt=0, numOfGroups=-1;
  for(int i=0; i<ALPH; i++){
    if(head[i]==-1) continue;
    gStart[++numOfGroups]=currSt;
    for(int j=head[i]; ~j; j=nxt[j]){
      rnk[j]=numOfGroups;
      suff[currSt++]=j;
    }
  }
  newRnk[len-1]=numOfGroups;
  newSuff[0]=suff[0];
  newRnk[0]=0;
  for(int h=1; newRnk[len-1]!=len-1; h<<=1){
    for(int i=0; i<len; i++){
      int j=suff[i]-h;
      if(j<0) continue;
      newSuff[gStart[rnk[j]]++]=j;
    }
    
    numOfGroups=1;
    for(int i=1; i<len; i++){
      bool newG=rnk[newSuff[i-1]] < rnk[newSuff[i]] || rnk[newSuff[i-1]] == rnk[newSuff[i]] && rnk[newSuff[i-1]+h] < rnk[newSuff[i]+h];
      newRnk[i]=newRnk[i-1]+newG;
      if(newG) gStart[numOfGroups++]=i;
    }
    for(int i=0; i<len; i++) rnk[suff[i]=newSuff[i]]=newRnk[i];
  }
}


int main(){
  FIO 
  // freopen("input.txt","rt",stdin);
  // freopen("output.txt","wt",stdout);
  int n;
  cin>>n;
  cin>>str>>str+n+1;
  str[n]=-1;
  buildSuff();
  buildLCP();
  int mx=0, mxi=0;
  for(int i=1; i<len; i++){
    if((suff[i]<n) != (suff[i-1]<n)){
      if(LCP[i]>mx) mx=LCP[i], mxi=suff[i];
    }
  }
  str[mxi+mx]=0;
  cout<<str+mxi<<'\n';


  return 0;
}v#include<bits/stdc++.h>
#define FIO ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
typedef long long ll;

const int MOD=1e9+7, OO=0x3f3f3f3f;
const ll LOO=0x3f3f3f3f3f3f3f3f;
const long double EPS=1e-8;

const int N=2e5+5, ALPH=256;

unsigned char str[N];
int len;
int suff[N], newSuff[N];
int rnk[N], newRnk[N], gStart[N];
int* head=newRnk, *nxt=newSuff;
int LCP[N];


void buildLCP(){
  int cnt=0;
  for(int i=0; i<len-1; i++){
    int j=suff[rnk[i]-1];
    while(str[i+cnt]==str[j+cnt]) cnt++;
    LCP[rnk[i]]=cnt;
    if(cnt) cnt--;

  }
}

void buildSuff(){
  memset(head, -1, sizeof(head[0])*ALPH);
  for(len=0; !len || str[len-1]; len++){
    nxt[len]=head[str[len]];
    head[str[len]]=len;
  }
  int currSt=0, numOfGroups=-1;
  for(int i=0; i<ALPH; i++){
    if(head[i]==-1) continue;
    gStart[++numOfGroups]=currSt;
    for(int j=head[i]; ~j; j=nxt[j]){
      rnk[j]=numOfGroups;
      suff[currSt++]=j;
    }
  }
  newRnk[len-1]=numOfGroups;
  newSuff[0]=suff[0];
  newRnk[0]=0;
  for(int h=1; newRnk[len-1]!=len-1; h<<=1){
    for(int i=0; i<len; i++){
      int j=suff[i]-h;
      if(j<0) continue;
      newSuff[gStart[rnk[j]]++]=j;
    }
    
    numOfGroups=1;
    for(int i=1; i<len; i++){
      bool newG=rnk[newSuff[i-1]] < rnk[newSuff[i]] || rnk[newSuff[i-1]] == rnk[newSuff[i]] && rnk[newSuff[i-1]+h] < rnk[newSuff[i]+h];
      newRnk[i]=newRnk[i-1]+newG;
      if(newG) gStart[numOfGroups++]=i;
    }
    for(int i=0; i<len; i++) rnk[suff[i]=newSuff[i]]=newRnk[i];
  }
}


int main(){
  FIO 
  // freopen("input.txt","rt",stdin);
  // freopen("output.txt","wt",stdout);
  int n;
  cin>>n;
  cin>>str>>str+n+1;
  str[n]=-1;
  buildSuff();
  buildLCP();
  int mx=0, mxi=0;
  for(int i=1; i<len; i++){
    if((suff[i]<n) != (suff[i-1]<n)){
      if(LCP[i]>mx) mx=LCP[i], mxi=suff[i];
    }
  }
  str[mxi+mx]=0;
  cout<<str+mxi<<'\n';


  return 0;
}#include<bits/stdc++.h>
#define FIO ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
typedef long long ll;

const int MOD=1e9+7, OO=0x3f3f3f3f;
const ll LOO=0x3f3f3f3f3f3f3f3f;
const long double EPS=1e-8;

const int N=2e5+5, ALPH=256;

unsigned char str[N];
int len;
int suff[N], newSuff[N];
int rnk[N], newRnk[N], gStart[N];
int* head=newRnk, *nxt=newSuff;
int LCP[N];


void buildLCP(){
  int cnt=0;
  for(int i=0; i<len-1; i++){
    int j=suff[rnk[i]-1];
    while(str[i+cnt]==str[j+cnt]) cnt++;
    LCP[rnk[i]]=cnt;
    if(cnt) cnt--;

  }
}

void buildSuff(){
  memset(head, -1, sizeof(head[0])*ALPH);
  for(len=0; !len || str[len-1]; len++){
    nxt[len]=head[str[len]];
    head[str[len]]=len;
  }
  int currSt=0, numOfGroups=-1;
  for(int i=0; i<ALPH; i++){
    if(head[i]==-1) continue;
    gStart[++numOfGroups]=currSt;
    for(int j=head[i]; ~j; j=nxt[j]){
      rnk[j]=numOfGroups;
      suff[currSt++]=j;
    }
  }
  newRnk[len-1]=numOfGroups;
  newSuff[0]=suff[0];
  newRnk[0]=0;
  for(int h=1; newRnk[len-1]!=len-1; h<<=1){
    for(int i=0; i<len; i++){
      int j=suff[i]-h;
      if(j<0) continue;
      newSuff[gStart[rnk[j]]++]=j;
    }
    
    numOfGroups=1;
    for(int i=1; i<len; i++){
      bool newG=rnk[newSuff[i-1]] < rnk[newSuff[i]] || rnk[newSuff[i-1]] == rnk[newSuff[i]] && rnk[newSuff[i-1]+h] < rnk[newSuff[i]+h];
      newRnk[i]=newRnk[i-1]+newG;
      if(newG) gStart[numOfGroups++]=i;
    }
    for(int i=0; i<len; i++) rnk[suff[i]=newSuff[i]]=newRnk[i];
  }
}


int main(){
  FIO 
  // freopen("input.txt","rt",stdin);
  // freopen("output.txt","wt",stdout);
  int n;
  cin>>n;
  cin>>str>>str+n+1;
  str[n]=-1;
  buildSuff();
  buildLCP();
  int mx=0, mxi=0;
  for(int i=1; i<len; i++){
    if((suff[i]<n) != (suff[i-1]<n)){
      if(LCP[i]>mx) mx=LCP[i], mxi=suff[i];
    }
  }
  str[mxi+mx]=0;
  cout<<str+mxi<<'\n';


  return 0;
}
