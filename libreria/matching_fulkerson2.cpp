#include<bits/stdc++.h>
#define ri(X) scanf("%d",&X)
#define rii(X,Y) scanf("%d %d",&X,&Y)
#define rf(X) scanf("%lf",&X)
#define rff(X,Y) scanf("%lf %lf",&X,&Y)
#define mp(X,Y) make_pair(X,Y)
#define pii pair<int,int>
#define FOR(i,j) for(int i=0;i<j;i++)
#define FORC(i,j,c) for(int i=0;i<j;i+=c)

//Matching con fulkerson

const int mn1 = 210;
const int mn2 = 210;


//pued es la matriz de adyacencia
bool pued[mn1][mn2];

//ya es ver cuales nodos ya esta visitados del lado derecho
bool ya[mn2];

//link es ver con que nodos del lado izquierdo esta asociado un nodo del
//lado derecho
int link[mn2];

bool can(int nod, int c2){
  if(nod==-1) return true;
  FOR(i,c2){
    if(pued[nod][i] && !ya[i]){
      ya[i]=1;
      if(can(link[i],c2)){
        link[i]=nod;
        return true;
      }
    }
  }
  return false;
}

//c1 cantidad de nodos de lado izquierdo del grafo
//c2 del lado derecho
int match(int c1, int c2){
  int ret = 0;
  memset(link,-1,sizeof link);
  FOR(i,c1){
    memset(ya,0,sizeof ya);
    if(can(i,c2)){
      ret++;
    }
  }
  return ret;
}

int main(){
  
  return 0;
}
