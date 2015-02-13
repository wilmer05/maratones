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
const int k_maxn = 1e5+10;
int table[k_maxn];
string cad;
string pattern;

//construye la tabla de errores de KMP
void build_table(int sz){
  table[0]=-1;
  table[1]=0;
  int act = 2;
  int last = 0;
  while(act<=sz){
    if(pattern[last]==pattern[act-1]){
    
      table[act++]=++last;
      //cout << table[act-1] << " " ;
    }
    else if(last){
      last = table[last];
    }
    else table[act++]=0; 
  }
}

//encuentra la primera ocurrencia de la palabra
//sz1 es el tamanio de la cadena en donde se busca
//sz2 es le tamanio de la cadena a buscar
int find(int sz1, int sz2){
  int end = 0;
  int index = 0;
  while(end<sz1){
    while(end<sz1 && index<sz2 && cad[end]==pattern[index]) end++,index++;
 
    if(index==sz2)
      return end;
    if(end==sz1) 
      return -1;
      
    while(index>-1 && pattern[index]!=cad[end] ) index = table[index];
    index++;
    end++;
  
  }
  return -1;
}


int main(){
  
  while(cin>>pattern){

//    string s2 = pattern.substr(0,pattern.size()-1);
  //  reverse(s2.begin(),s2.end());
    //cad = pattern + s2;
//    cout << cad << endl;
    cad = pattern;
    reverse(pattern.begin(),pattern.end());
    build_table(pattern.size());

    cout << cad+pattern.substr(find(cad.size(),pattern.size()),pattern.size()) << endl;
  }


	return 0;
}
