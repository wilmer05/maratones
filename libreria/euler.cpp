#include<bits/stdc++.h>
#define ri(X) scanf("%d",&X)
#define rii(X,Y) scanf("%d %d",&X,&Y)
#define rf(X) scanf("%lf",&X)
#define rff(X,Y) scanf("%lf %lf",&X,&Y)
#define mp(X,Y) make_pair(X,Y)
#define pii pair<int,int>
#define FOR(i,j) for(int i=0;i<j;i++)
#define FORC(i,j,c) for(int i=0;i<j;i+=c)

using namespace std;
const int mn = 60;
int N,T;

struct cj{
  int from, to;
  cj *nx;
  cj(int f,int t):from(f),to(t){
    nx = NULL;
  }
};

struct euler{
  
  int E,V;
  cj *pr,*lt,*fix,*c;
  vector<int> sl,kk;
  vector<vector<int> > g;
  vector<vector<int> >lado;
  vector<bool> listo,vis,en_cola;
  vector<cj *> last;
  queue<int> cola;

  void clear(){
    g.clear();
    lado.clear();
    listo.clear();
    sl.clear();
    kk.clear();
    last.clear();
    vis.clear();
    en_cola.clear();
  }

  void init(){
    clear();
    lt = pr = fix = c = NULL;
    sl.resize(V,0);
    kk.resize(V,0);
    g.resize(V);
    listo.resize(E,false);
    vis.resize(V,false);
    lado.resize(V);
    last.resize(V,NULL);
    en_cola.resize(V,false);
  } 
  
  void addEdge(int u, int v, int number){
    g[u].push_back(v);
    lado[u].push_back(number);
    if(u==v) 
      sl[u]++;
  }
  
  euler(int v, int e):V(v),E(e){
    init();
  }

  void dfs(int nod){
    if(vis[nod]) return;
    vis[nod]=1;
    FOR(i,g[nod].size()) dfs(g[nod][i]);
  }

  bool is_eulerian(int begin){
    dfs(begin);
    int k=0;
    FOR(i,V){
      int sz = g[i].size();
      k+=((((sz)-sl[i])%2) || (g[i].size() && !vis[i]));
    }
    return 0==k;
  }

  void solve(int nod){
    int begin = nod;
    fix = NULL;
    c = last[nod];
    if(c!=NULL)
     fix = c->nx;
    while(1){
      if(!en_cola[nod] && nod!=begin){
        cola.push(nod);
        en_cola[nod]=true;
      }
      int &tk = kk[nod];
      int sz = g[nod].size();
      while((tk<sz) && listo[lado[nod][tk]])
        tk++;

      if(tk>=sz){
        if(fix!=NULL && c!=NULL) {
          c->nx = fix;
        }

        return;
      }
      int ot = g[nod][tk];

      listo[lado[nod][tk]]=1;
      cj *niu = new cj(nod,ot);
      last[ot]=niu;
      lt = niu;
      tk++;
      if(c!=NULL){
        c->nx = niu;
      }
      if(pr==NULL){
        pr = niu;
      }
      c = niu;
      nod = ot;
    }
  }
  
  vector<pair<int,int> > get(){
    vector<pair<int,int> > edges;
    int cota = 0;
    cj *pr2 = NULL;
    cj *pr3;
    pr3 = pr;
    while(cota<N){

      edges.push_back(mp(pr->from+1,pr->to+1));
      pr2 = pr;
      pr = pr->nx;
      cota++;
      free(pr2);
    }
    return edges;
  }
  
  vector<pair<int,int> > get_eulerian(int begin){
    cola.push(begin);  
    while(!cola.empty()){
      int go = cola.front();
      cola.pop();
      solve(go);
      if(begin==go && lt!=NULL){
          lt->nx = pr;
      }
    }
    return get();
  }
};
int main(){
  return 0;
}
