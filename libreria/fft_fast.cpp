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
#include<complex>

#define ri(X) scanf("%d",&X)
#define rii(X,Y) scanf("%d %d",&X,&Y)
#define rf(X) scanf("%lf",&X)
#define rff(X,Y) scanf("%lf %lf",&X,&Y)
#define mp(X,Y) make_pair(X,Y)
#define pii pair<int,int>
#define FOR(i,j) for(int i=0;i<j;i++)
#define FORC(i,j,c) for(int i=0;i<j;i+=c)

using namespace std;

//NOTA: los polinomios que manejan estas funciones tienen que tener 
//      2^k coeficientes para algun k, y si no los tienen deben ser
//      rellenados

//tipo de valores del num complejo
ttypedef double tipo;

typedef complex<tipo> comp;

typedef vector<comp> vc;

//parametro que le indica al fft si usa en inverso o no 
double mult = 1.0;

int rev(int val, int lg){
    int ret = 0;
    lg--;
    while(val){
        ret|=(val%2)<<lg;
        val>>=1;
        lg--;
    }
    return ret;
}

//el vector a debe ser de una longitud potencia de 2
//mult = 1 FFt
//mult = -1 lo usa el inv_fft
//el vector a debe ser de una longitud potencia de 2
//mult = 1 FFt
//mult = -1 lo usa el inv_fft
vc fft(vc &a){

  int n = a.size();
  vc y(n);
  int lg = 0;

  while((1<<lg)<n) lg++;

  for(int i=0;i<n;i++){
    y[rev(i,lg)]=a[i];
  }

  for(int i = 1; i <= lg; i++){
    int m = 1<<i;
    for(int k=0;k<n;k+=m){
        for(int j=0;j<m/2;j++){
            double angle = (mult*j*2.0*M_PI)/m;
            comp w = comp(cos(angle),sin(angle));;
            comp t = w * y[k+j+m/2];
            comp u = y[k+j];
            y[k+j]=u+t;
            y[k+j+m/2]=u-t;
        }
    }
  }
  return y; 
}

//se encarga de calcular el DFT-1 de coeficientes
vc inv_fft(vc &a){
  mult = -1.0;
  vc ret = fft(a);
  int n = ret.size();
  for(int i=0;i<n;i++) ret[i]/=n;
  mult = 1.0;
  return ret;
}

//se encarga de evaluar un polinomio v en el valor val
//los coeficientes deben estar ordenados en orden creciente
// de la potencia de X
comp eval(vc v, comp val){
    comp s;
    for(int i=0;i<v.size();i++) 
        s+=pow(val,i)*v[i];
    return s;
}

//Dado dos polinomios cuyos coeficientes estan en A y en B,
//retorna los coeficientes del polinomio que resulta
//de la multiplicacion de los mismos
//Nota: los coeficientes deben estar en orden creciente de
//      la potencia de las X's, es decir que si el polinomio es
//      p = a0 + a1*X + a2*X^2 + ...
//      el vector de sus coeficientes debe ser (a0,a1,a2,...)

vc get_coef(vc &A, vc &B){
    vc y1 = fft(A);
    //cout << y1.size() << endl;
    //FOR(i,y1.size()) cout << y1[i] << endl;
    vc y2 = fft(B);

    for(int i=0;i<y1.size();i++) 
        y1[i]*=y2[i];

    return inv_fft(y1);
}

//ejemplo
int main(){
    //for(int i=0;i<8;i++)
    //    cout << i << " " << rev(i,3) << endl;
  vc co1,co2;
  co1 = vc(8,0);
  co1[0]=1;co1[3]=0;
  co1[1]=1;co1[2]=0;
  //for(int i=0;i<4;i++) cout << co1[i] << endl;
  co2 = vc(8,0);
  co2[0]=0;co2[2]=0;
  co2[1]=1;co2[3]=0;
  
    double val;
    cout <<"da valor" << endl;
    cin >> val;
    
    vc ans = get_coef(co1,co2);
    for(int i=0;i<ans.size();i++) cout << i << " " << ((ans[i])) << endl;    
    cout << eval(get_coef(co1,co2),val) << endl;


  //for(int i=0;i<ans.size();i++) cout << ((ans[i])) << endl;
  /*comp s;
  for(int i=0;i<ans.size();i++) s+=ans[i];
  cout <<"suma= " << norm(s) << endl;
  */
	return 0;
}
