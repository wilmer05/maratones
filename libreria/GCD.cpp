//Codigo hecho por FTL
//Codigo hecho por Wilmer Bandres
//Codigo que implementa el algoritmo de euclides extendido
#include<iostream>
#include<utility>
#include<cstdio>

using namespace std;


//Este codigo retorna:
//En el first del pair: el coeficiente del primer valor en la primera llamada del gcd
//En el second del pair: el coeficiente del segundo valor en la primera llamada del gcd
//Se cumple que x*e_gcd(x,y).first + y*e_gcd(x,y).second = gcd(x,y) 

pair<long long, long long> e_gcd(long long a, long long b){
  if(!a) return make_pair(0LL,1LL);
  if(!b) return make_pair(1LL,0LL);
  if(b%a==0) return make_pair(1LL,0LL);
  if(a%b==0) return make_pair(0LL,1LL);
  if((b%(a%b))==0) return make_pair(1LL,-a/b);
  pair<long long,long long> tmp = e_gcd(b,a%b);
  return make_pair(tmp.second,tmp.first+tmp.second*(-a/b));
}

int main(){

  long long x,y;
  cin >> x >> y;
  cout << e_gcd(x,y).first << " y " << e_gcd(x,y).second <<endl;
  return 0;
}
