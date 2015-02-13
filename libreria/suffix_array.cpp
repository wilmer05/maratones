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


const int k_maxn = 2e5+20;
char cad[k_maxn];
int bucket[k_maxn];
int aux[k_maxn];
int bound;
int cnt;

//transforma la cadena cad en esa misma cadena con un monton de # al final
int transform(char *str){
  int sz = strlen(str);
  for(int i=sz;i<2*sz;i++)
    str[i]='#';
  
  str[2*sz]='\0';
  return 2*sz;
}
//contiene la posicion en el arreglo de buckets de un indice
struct suffix{
  int idx;
  
  bool operator<(const suffix &sfx) const {
    if(!bound)
      return cad[idx] <cad[sfx.idx];
    else if(bucket[idx]==bucket[sfx.idx])
      return bucket[idx+bound]<bucket[sfx.idx+bound];
    else
      return bucket[idx]<bucket[sfx.idx];
  }
  
  bool operator==(const suffix &sfx) const{
    return !((*this)<sfx) && !(sfx<(*this));
  }
} pos[k_maxn];

int update(int sz1){
  int st = 0,id=0,cnt=0;
  for(int i=0;i<sz1;i++){
    if(i && !(pos[i]==pos[i-1])){
      st = i;
      id++;
    }
    if(i!=st){
      cnt=1;
    }
    aux[pos[i].idx] = id;
  }
  memcpy(bucket,aux,sz1*4);
  return cnt;
}

void start(int sz1 ,int sz2){
  //sort inicial
  sort(pos,pos+sz1);
  for(int i=sz1;i<sz2;i++){
    bucket[i]=-1;
  }
  cnt = update(sz1);

  for(bound=1;cnt;bound*=2){
    sort(pos,pos+sz1);
    cnt = update(sz1);
 //         for(int i=0;i<sz1;i++) cout << bucket[i] << " " ;
   // cout << endl;
//    cout << bound << endl;
  }
  
}

int suffix_array(char *str){
  int sz1,sz2;
  
  sz2 = transform(str);
  sz1 = sz2/2;
  bound = 0;
  int ind = sz2-1;
//  cout << str << endl;
  for(int i=0;i<sz2;i++){
    pos[i].idx = i;
  }
  start(sz1,sz2);
  
}



int main(){
  cin >> cad;
  int sz = strlen(cad);
  suffix_array(cad);

  for(int i=0;i<sz;i++) cout << pos[i].idx << endl ;

  


	return 0;
}
