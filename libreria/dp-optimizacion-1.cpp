#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<set>
#include<map>
#include<vector>
#include<utility>
#include<queue>
#include<stack>
#include<string>
#include<algorithm>
#include<cmath>

#define ri(X) scanf("%d",&X)
#define rii(X,Y) scanf("%d %d",&X,&Y)
#define rf(X) scanf("%lf",&X)
#define rff(X,Y) scanf("%lf %lf",&X,&Y)
#define mp(X,Y) make_pair(X,Y)
#define pii pair<int,int>
#define FOR(i,j) for(int i=0;i<j;i++)
#define FORC(i,j,c) for(int i=0;i<j;i+=c)

using namespace std;

//esta optimizacion trae como consecuencia 
//bajar la complejidad de un DP de O(N^2) a O(N)
//y requiere que a[i]<=a[i+1] y que b[j]>=b[j+1]
//si no ocurre que a[i]<=a[i+1] entonces se debe
//hacer con un set lo que agrega a la complejidad un 
//factor logaritmico, es decir que queda como
//O(N log(N))

const int mn = 1e5+10;
long long as[mn];
long long bs[mn];

long long memo[mn];
//las rectas para aplicar el truco de convex-hull se representan de la forma
//memo[i]+b[i]*x
//y el x donde evaluamos es a[j]
vector<int> q;
int n;


double find_inter(double m1, double b1, double m2, double b2){
  return (b1-b2)/(m2-m1);
}

void dp(){
 memo[0]=0LL; 
 q.push_back(0);
 int idx = 0;
 for(int i=1;i<n;i++){
    double x = as[i];
    while(idx+1<q.size() && \
         find_inter(bs[q[idx]],memo[q[idx]],bs[q[idx+1]],memo[q[idx+1]])<=x) idx++;
    
    memo[i] = memo[q[idx]]+as[i]*bs[q[idx]];

    int last = q.size(); last--;
   
    while(last && \
         find_inter(bs[q[last]],memo[q[last]],bs[q[last-1]],memo[q[last-1]])>=\
         find_inter(bs[q[last-1]],memo[q[last-1]],bs[i],memo[i])){
         q.pop_back();
         last--;
         idx = min(idx,last); 
    }   
    q.push_back(i);   
 
 }
}

int main(){
  cin >> n;
  FOR(i,n) cin >> as[i];
  FOR(i,n) cin >> bs[i];
  dp();
  cout << memo[n-1] << endl;   
	return 0;
}
