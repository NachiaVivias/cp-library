
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


struct heavy_light_decomposition{
private:

  int N;
  vector<int> P;
  vector<int> PP;
  vector<int> PD;
  vector<int> D;
  vector<int> I;

  vector<int> rangeL;
  vector<int> rangeR;

public:

  heavy_light_decomposition(const vector<vector<int>>& E = {{}}){
    N = E.size();
    P.assign(N, -1);
    I = {0};
    I.reserve(N);
    for(int i=0; i<I.size(); i++){
      int p = I[i];
      for(int e : E[p]) if(P[p] != e){
        I.push_back(e);
        P[e] = p;
      }
    }
    vector<int> Z(N, 1);
    vector<int> nx(N, -1);
    PP.resize(N);
    for(int i=0; i<N; i++) PP[i] = i;
    for(int i=N-1; i>=1; i--){
      int p = I[i];
      Z[P[p]] += Z[p];
      if(nx[P[p]] == -1) nx[P[p]] = p;
      if(Z[nx[P[p]]] < Z[p]) nx[P[p]] = p;
    }

    for(int p : I) if(nx[p] != -1) PP[nx[p]] = p;

    PD.assign(N,N);
    PD[0] = 0;
    D.assign(N,0);
    for(int p : I) if(p != 0){
      PP[p] = PP[PP[p]];
      PD[p] = min(PD[PP[p]], PD[P[p]]+1);
      D[p] = D[P[p]]+1;
    }
    
    rangeL.assign(N,0);
    rangeR.assign(N,0);
    vector<int> dfs;
    dfs.push_back(0);
    while(dfs.size()){
      int p = dfs.back();
      rangeR[p] = rangeL[p] + Z[p];
      int ir = rangeR[p];
      dfs.pop_back();
      for(int e : E[p]) if(P[p] != e) if(e != nx[p]){
        rangeL[e] = (ir -= Z[e]);
        dfs.push_back(e);
      }
      if(nx[p] != -1){
        rangeL[nx[p]] = rangeL[p] + 1;
        dfs.push_back(nx[p]);
      }
    }

    I.resize(N);
    for(int i=0; i<N; i++) I[rangeL[i]] = i;
  }

  int depth(int p) const {
    return D[p];
  }

  int lca(int u, int v) const {
    if(PD[u] < PD[v]) swap(u, v);
    while(PD[u] > PD[v]) u = P[PP[u]];
    while(PP[u] != PP[v]){ u = P[PP[u]]; v = P[PP[v]]; }
    return (D[u] > D[v]) ? v : u;
  }

  vector<pair<int,int>> path(int r, int c) const {
    vector<pair<int,int>> res;
    while(PD[r] < PD[c]){
      res.push_back({ rangeL[PP[c]], rangeL[c]+1 });
      c = P[PP[c]];
    }
    if(PP[r] != PP[c]) return {};
    if(D[r] > D[c]) return {};
    res.push_back({ rangeL[r], rangeL[c]+1 });
    reverse(res.begin(),res.end());
    return move(res);
  }

  const vector<int>& idxs() const {
    return rangeL;
  }

  int meet(int x, int y, int z){
    return lca(x,y) ^ lca(y,z) ^ lca(x,z);
  }

  int jump(int from, int to, int d){
    int g = lca(from,to);
    int dist0 = D[from] - D[g] * 2 + D[to];
    if(dist0 > d) return -1;
    int p = from;
    if(D[from] - D[g] > d){ p = to; d = dist0 - d; }
    while(D[p] - D[PP[p]] > d){
      d -= D[p] - D[PP[p]] + 1;
      p = P[PP[p]];
    }
    return I[rangeL[p] - d];
  }
};

