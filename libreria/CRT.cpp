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

long long CRT(vector<long long> &as, vector<long long> &bs){
  long long prod = 1;
  long long ret = 0;
  for(int i=0;i<bs.size();i++) prod*=bs[i];
  for(int i=0;i<as.size();i++) {
    ret+=((((as[i]%prod)*((prod/bs[i])%prod))%prod)*(e_gcd(prod/bs[i],bs[i]).first%prod))%prod;
    ret%=prod;
  }
  
  while(ret<0) ret+=prod;

  return ret;
}

int main(){

  int c;
  cin >> c ;
  vector<long long> as, bs;
  for(int i=0;i<c;i++) {as.push_back(0);bs.push_back(0);cin >>as[i]>>bs[i]; }
    
    cout << CRT(as,bs);
  return 0;
}
