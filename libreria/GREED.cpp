#include <cmath>
#include <vector>
#include <iostream>
#include <cstdio>
#include <climits>
#include <cstring>

using namespace std;

#define MAXN 510

typedef pair<short, short> PII;

const int INF = SHRT_MAX;

short N;
short cap[MAXN][MAXN], flow[MAXN][MAXN], cost[MAXN][MAXN];
short found[MAXN];
short dist[MAXN], pi[MAXN], width[MAXN];
PII dad[MAXN];

void inic (short N) {
	memset(cap, 0, sizeof(cap));
	memset(flow, 0, sizeof(flow));
	memset(cost, 0, sizeof(cost));
	memset(found, 0, sizeof(found));
	memset(dist, 0, sizeof(dist));
	memset(pi, 0, sizeof(pi));
	memset(width, 0, sizeof(width));
	memset(dad, 0, sizeof(dad));
}

void AddEdge(int from, int to, int cap, int cost) {
	cap[from][to] = cap;
	cost[from][to] = cost;
}

void Relax(int s, int k, int cap, int cost, int dir) {
	int val = dist[s] + pi[s] - pi[k] + cost;
	if (cap && val < dist[k]) {
		dist[k] = val;
		dad[k] = make_pair(s, dir);
		width[k] = min(cap, width[s]);
	}
}

int Dijkstra(int s, int t) {
	memset(found, false, sizeof(found));
	for (int i=0 ; i<dist.size() ; i++)
		dist[i] = INF;
	memset(width, 0, sizeof(width));
	dist[s] = 0;
	width[s] = INF;

	while (s != -1) {
		int best = -1;
		found[s] = true;
		for (int k = 0; k < N; k++) {
			if (found[k]) continue;
			Relax(s, k, cap[s][k] - flow[s][k], cost[s][k], 1);
			Relax(s, k, flow[k][s], -cost[k][s], -1);
			if (best == -1 || dist[k] < dist[best]) best = k;
		}
		s = best;
	}

	for (int k = 0; k < N; k++)
		pi[k] = min(pi[k] + dist[k], INF);
	return width[t];
}

pair<int,int> GetMaxFlow(int s, int t) {
	int totflow = 0, totcost = 0;
	while (int amt = Dijkstra(s, t)) {
		totflow += amt;
		for (int x = t; x != s; x = dad[x].first) {
			if (dad[x].second == 1) {
				flow[dad[x].first][x] += amt;
				totcost += amt * cost[dad[x].first][x];
			} else {
				flow[x][dad[x].first] -= amt;
				totcost -= amt * cost[x][dad[x].first];
			}
		}
	}
	return make_pair(totflow, totcost);
}

int main () {
	int T, N, E, x, y, S;
	scanf("%d", &T);
	while (T-->0) {
		scanf("%d", &N);
		S = N+2;
		inic(N+3);
		vector<int> cant(N+1,0);
		for (int i=1 ; i<=N ; i++) {
			scanf("%d", &x);
			AddEdge(i,N+1,1,0);
			cant[x]++;
		}

		for (int i=1 ; i<=N ; i++)
			if (cant[i] > 0)
				AddEdge(S,i,cant[i],0);

		scanf("%d", &E);
		for (int i=0 ; i<N ; i++) {
			scanf("%d%d", &x, &y);
			AddEdge(x,y,S,1);
			AddEdge(y,x,S,1);
		}

		PII res = GetMaxFlow(N+2,N+1);

		cout << res.second << endl;
	}
	return 0;
}


