//Codigo hecho por FTL
//Codigo hecho por Wilmer Bandres que emplea el teorema chino del resto (o CRT)
#include<iostream>
#include<utility>
#include<cstdio>
#include<vector>
using namespace std;

// Las formulas son escritas de la forma: x = as[i] mod bs[i]
//Este codigo retorna:
//El valor que cumple con las formulas dadas haciendo uso del teorema chino del resto

pair<long long, long long> e_gcd(long long a, long long b){
  if(!a) return make_pair(0LL,1LL);
  if(!b) return make_pair(1LL,0LL);
  if(b%a==0) return make_pair(1LL,0LL);
  if(a%b==0) return make_pair(0LL,1LL);
  if((b%(a%b))==0) return make_pair(1LL,-a/b);
  pair<long long,long long> tmp = e_gcd(b,a%b);
  return make_pair(tmp.second,tmp.first+tmp.second*(-a/b));
}

int a,b;
int main(){
  while(cin >>a >> b){  
    pair<int,int> p = e_gcd(a,b);
    int p1 = p.first;
    int p2 = p.second;
    if(p1>p2) swap(p1,p2);
    cout << p1 << " " << p2 << " " << __gcd(a,b) << endl;;
  }

  return 0;
}
