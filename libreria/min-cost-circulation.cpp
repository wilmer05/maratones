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


//infinito
const int oo = 1<<16;

//codigo que encuentra el min-cost circulation en un grafo

struct mincirc{

  //grafo
  int edges;
  vector<int> cost,caps,dest,from;
  vector<int> dist,par,vis;
  int id_flow;//contiene el id del edge que dara max_flow
  int mincost;

  //cantidad de nodos
  int V,S,T;

  mincirc(){
  }

  //constructor que se debe usar, V es la cantidad de nodos en el grafo
  mincirc(int nodos, int source, int t):V(nodos),S(source),T(t){
    id_flow = -1;
    cost.clear(); 
    caps.clear();
    dest.clear();
    from.clear();
    dist = vector<int>(V);
    par = vector<int>(V);
    vis = vector<int>(V);
    edges = 0;
  }

  void add_vertex(){
    V++;
    dist.push_back(-1);
    par.push_back(-1);
    vis.push_back(-1);
  }
 
  void make_edge(int s, int t, int c, int capa){
    int id = cost.size();

    if(c==-oo && capa == oo && s==T && t==S)
      id_flow = id;  

    edges++;
    from.push_back(s);
    cost.push_back(c);
    caps.push_back(capa);
    dest.push_back(t);
  }

  //agrega un arco de s a t con c de costo y capa de capacidad
  void add_edge(int s, int t, int c, int capa){
    //cout << s << " -> "<< t << " " << c<< endl;
    make_edge(s,t,c,capa); 
    make_edge(t,s,-c,0); 
  }

  int act(int ret){
    for(int j=0;j<edges;j++){
        int s=from[j],t=dest[j]; 
        int cc = cost[j];
        int ca = caps[j];
        if(ca && dist[t]>dist[s]+cc){
           dist[t]=dist[s]+cc;
           par[t]=j;
           if(ret)
            return t;
           
        }         
      }

    return -1;
  }
 
  int find_cycle(){
    for(int i=0;i<V;i++) par[i]=-1,dist[i]=oo;
  
    par[S]=S;
    dist[S]=0; 
    
    for(int i=0;i<V+1;i++)
      act(0); 

    return act(1);
  } 

  void cancel_cycle(int st){
    int mincap = oo;
  //  int end = st;
    //cout <<"found" << endl;
    for(int i=0;i<V;i++) vis[i]=0;

    do{
      vis[st]++;
      int e = par[st];
      if(vis[st]==2){
        mincap = min(mincap,caps[e]);
      }
      st = from[e];
    //  cout << st << endl;
    } while(vis[st]<3);

    for(int i=0;i<V;i++) vis[i]=0;


    while(!vis[st]){
      vis[st]=1;
      int e = par[st];
      mincost+=mincap*cost[e]; 
      caps[e]-=mincap;
      caps[e^1]+=mincap;
      st = from[e];
    } 
    
  }

  //funcion que se debe llamar para calcular 
  //la menor circulacion
  void find_circ(){
    mincost = 0;
    int tmp;
    while((tmp=find_cycle())>=0)
      cancel_cycle(tmp);
  }
  
  //solo se puede usar una vez, y luego se tiene que crear otra clase
  //nueva debido a que las capacidades no se restauran a su forma original
  //de querer usar varias veces el mismo grafo pero con cosas cambiadas
  //se debe editar el grafo a pata
  int get_flow(){
    add_edge(T,S,-oo,oo); 
    find_circ();
    int ret = mincost;
    int e = id_flow;
    if(e>-1){
      int flow = caps[e^1];
      ret -= flow*cost[e];
    }
    return ret;
  }  
};


int main(){
  int t;
  cin >> t;
  while(t--){
    int c1,c2,t1,t2,cc;
    cin >> c1 >> c2;
    mincirc ans(c1+c2+2,c1+c2,c1+c2+1);
    while(cin >> t1 >> t2 >> cc && t1){
      t1--;t2--;
      ans.add_edge(t1,c1+t2,-cc,1);
    }
    FOR(i,c1) ans.add_edge(c1+c2,i,0,1);
    FOR(i,c2) ans.add_edge(c1+i,c1+c2+1,0,1);
    cout << -ans.get_flow() << endl;
    FOR(i,ans.edges) if(ans.caps[i]<0)cout << ans.caps[i] << endl;
  }



	return 0;
}
