

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cstdio>
 
#define MAXN 110
#define INF 1000000000;
 
using namespace std;

//Codigo obtenido por FTL gracias a la implementacion de zobayer
//Este codigo al hacer un add de un arco se debe agregar el contrario tambien, y solo colocarle capacidad al primero
//Al principio de cada caso que se haga se debe hacer un memset de la matriz capacity 
vector<int> graph[MAXN];
int capacity[MAXN][MAXN];
 
int max_flow(int source, int sink) {
    int residual[MAXN][MAXN]; memset(residual, 0, sizeof(residual));
    while(1) {
        int prev[MAXN]; memset(prev, -1, sizeof(prev));
        int actual[MAXN]; memset(actual, 0, sizeof(actual));
        prev[source] = source;
        actual[source] = INF;
        queue<int> q; q.push(source);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int i = 0; i < graph[u].size(); i++) {
                int v = graph[u][i];
                if(capacity[u][v] - residual[u][v] > 0 && prev[v] == -1) {
                    prev[v] = u;
                    actual[v] = min(actual[u], capacity[u][v] - residual[u][v]);
                    if(v != sink) {
                        q.push(v);
                    } else {
                        while(prev[v] != v) {
                            u = prev[v];
                            residual[u][v] += actual[sink];
                            residual[v][u] -= actual[sink];
                            v = u;
                        }
                        goto end;
                    }
                }
            }
        }
        end:;
        if(prev[sink] == -1) {
            int sum = 0;
            for(int i = 1; i < MAXN; i++) {
                sum += residual[source][i];
            }
            return sum;
        }
    }
}
int main(){

	//graph[0].push_back(1);
  memset(capacity,0,sizeof capacity);
  graph[0].push_back(1);
  graph[1].push_back(0);
  graph[0].push_back(2);
  graph[2].push_back(0);
  graph[1].push_back(3);
  graph[3].push_back(1);
  graph[1].push_back(4);
  graph[4].push_back(1);
  graph[2].push_back(7);
  graph[7].push_back(2);
  graph[7].push_back(4);
  graph[4].push_back(7);
  graph[3].push_back(5);
  graph[5].push_back(3);
  graph[5].push_back(6);
  graph[6].push_back(5);
  graph[4].push_back(6);
  graph[6].push_back(4);
  capacity[0][1] =1;
  capacity[0][2] =1;
  capacity[1][3] =1;
  capacity[1][4] =1;
  capacity[2][7] =1;
  capacity[7][4] =1;
  capacity[3][5] =1;
  capacity[5][6] =1;
  capacity[4][6] =1;

  cout << max_flow(0,6) << endl;
  return 0;
}
