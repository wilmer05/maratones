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


//tamanio maximo de la cadena con #
const int k_maxn = 6e4+50;
char cad[k_maxn];
int palin[k_maxn];

//funcion que transforma un string al string que utiliza manacher con
//caracteres de tipo # intercalados
int transform(){
  int sz = strlen(cad);

  for(int i=sz-1;i>=0;i--){
    cad[2*i+1]=cad[i];
  }

  for(int i=0;i<=sz;i++) cad[2*i]='#';
  sz = 2*sz+1;
  
  return sz;
}

//manacher asume que la cadena esta guardada en cad y el tamanio es sz
//las posiciones impares en palin guardan palindromos de tamanio impar
//y la de las posiciones pares guardan palindromos de tamanio par
void manacher(int sz){
  int ind = 0;
  int end = 0;
  int last = -1;
  palin[0]=-1;
  
  while(ind<sz){
    int tmp1 = end-1-ind;
    int tmp2 = end-1-last;
    int tmp3 = -1;
    int tmp4 = ind-last;
    if(last-tmp4>=0){
      tmp3 = palin[last-tmp4];
    }
   
    if(tmp3>=0 && ind+tmp3<end-1){
      palin[ind++]=tmp3;
      continue;
    }
 
    while(2*ind-end>=0 && end<sz && cad[2*ind-end]==cad[end]) 
      end++;
 
    palin[ind]=end-ind-1;
    last = ind;
    ind++;
  }
  
  
}


//codigo de un programa cualquiera
int k;
int main(){
  cin >> k;
  cin >> cad;
  
  int sz =transform();
  manacher(sz);
  int cnt =0 ;
  //cout << cad << endl;
  for(int i=0;i<sz;i++){
    //cout << cad[i] << " " << palin[i] << endl;
    if(cad[i]!='#' && k%2 && palin[i]>=k)
      cnt++;
    else if(cad[i]=='#' && k%2==0 && palin[i]>=k)
      cnt++;
      
  }
  cout << cnt << endl;

	return 0;
}
