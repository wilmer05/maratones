//Codigo de FTL
//Hecho por Wilmer Bandres
//Algoritmo para sacar un maximum matching de un grafo bipartito con ford fulkerson,es decir tiempo O(f*|E|) 
#include<iostream>
#include<cstring>
using namespace std;

#define MAXN1 100
#define MAXN2 100

//Matriz que indica entre cuales nodos existe un lado
bool pued[MAXN1][MAXN2];

//Arreglo que verifica con quien esta aginado los nodos de la derecha
int asig[MAXN2];

//Arreglo que indica si un nodo de la derecha ya ha sido visitado
bool ya[MAXN2];

//Variables que indican cuantos nodos hay del lado izquierdo (n nodos) y derecho(m nodos) del matching
int n,m;

bool matching(int nod){
  if(nod == -1) return true;
  for(int x=0;x<m;x++){
    if(pued[nod][x]){
      int tmp = asig[x];
      if(!ya[x]){
	ya[x] = true;
	if(matching(tmp)){
	  asig[x] = nod;
	  return true;
	}
      }
    }
  }

  return false;

}


int match(){
  int tot = 0;
  memset(asig,-1,sizeof asig);
  for(int x=0;x<n;x++){
    memset(ya,false,sizeof(ya));
    if(matching(x))
      tot++;
  }
  return tot;
}

int main(){
  return 0;
}
