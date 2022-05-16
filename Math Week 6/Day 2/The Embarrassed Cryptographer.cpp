//https://vjudge.net/contest/495976#problem/G

/*
sieve is a linear sieve function calculate if any number from 1 to n is prime or not
			   	  sieve is a linear sieve function calculate for any number from 1 to n it's least prime factor

		factorization in log(N) using seive       https://ideone.com/oQwx5v
*/

#include <cstdio>
#include <string>
using namespace std;
const int N=1e6+1;
int primes[80000],lpf[N],sz;
/*void sieve(){
    isComposite[0]=isComposite[1]=1;
    for(int i=2;i<N;i++){
        if(!isComposite[i])primes[sz++]=i;
        for(int j=0;j<sz&&primes[j]*i<N;j++){
            isComposite[primes[j]*i]=1;
            if(!(i%primes[j]))break;
        }
    }
}*/
void sieve2(){
    lpf[0]=lpf[1]=1;
    for(int i=2;i<N;i++){
        if(!lpf[i])lpf[i]=i,primes[sz++]=i;
        for(int j=0;j<sz&&primes[j]*i<N&&primes[j]<=lpf[i];j++){
            lpf[primes[j]*i]=primes[j];
        }
    }
}
char k[105];
int main(){
    sieve2();
    int l;
    while(scanf("%s%d",k,&l),k[0]!='0'||l){
        int bad=0;
        for(int i=0;i<sz&&primes[i]<l;i++){
            int sum=0;
            for(int j=0;k[j];j++)sum*=10,sum+=(k[j]-'0'),sum%=primes[i];
            if(!sum){
                bad=primes[i];
                break;
            }
        }
        if(bad)printf("BAD %d\n",bad);
        else puts("GOOD");
    }
    return 0;
}
