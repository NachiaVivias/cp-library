#define PROBLEM "https://yukicoder.me/problems/no/1600"
#include "../../Include/nachia/tree/heavy-light-decomposition.hpp"
#include "../../Include/nachia/graph/graph.hpp"
#include "../../Include/nachia/set/dsu.hpp"
#include "../../Include/nachia/misc/fastio.hpp"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const ull MOD = 1000000007;
#define rep(i,n) for(int i=0; i<(int)(n); i++)

struct mll{
  using u32 = uint32_t;
  using u64 = uint64_t;
  u32 v;
  mll(u32 x = 0) : v(x) {}
  u32 val() const { return v; }
  mll& operator+=(const mll& r){ v += r.val(); if(v >= MOD) v -= MOD; return *this; }
  mll& operator-=(const mll& r){ v += MOD - r.val(); if(v >= MOD) v -= MOD; return *this; }
  mll& operator*=(const mll& r) { v = (u64)v * r.val() % MOD; return *this; }
  mll operator+(const mll& r) const { mll res = *this; res += r; return res; }
  mll operator-(const mll& r) const { mll res = *this; res -= r; return res; }
  mll operator*(const mll& r) const { mll res = *this; res *= r; return res; }
  mll operator-() const { return v ? mll(MOD-v) : mll(0); }
};

struct Edge{ int u,v,i; };

int N, M;
vector<Edge> J;
vector<vector<Edge>> E;
vector<Edge> flows;
vector<mll> cost;

vector<int> P;
vector<int> Eidx;
vector<mll> dep;

vector<int> iEidx;
vector<int> flowIdx;

nachia::HeavyLightDecomposition hld;



void read_graph(){
  using nachia::cin;
  cin >> N >> M;
  E.resize(N);
  vector<pair<int,int>> idE;
  cost.resize(M);
  cost[0] = 2;
  for(int i=1; i<M; i++) cost[i] = cost[i-1] * 2;
  nachia::Dsu G1(N);
  rep(i,M){
    int u,v; cin >> u >> v; u--; v--;
    J.push_back({u,v,i});
    if(G1.same(u, v)){
      flows.push_back({u,v,i});
    }
    else{
      G1.merge(u,v);
      E[u].push_back({u,v,i});
      E[v].push_back({v,u,i});
      idE.push_back({ u,v });
    }
  }
  hld = nachia::HeavyLightDecomposition(nachia::Graph(N, idE, true).getAdjacencyArray());
}

void initLCA(){
  vector<int> I;
  P.assign(N,-1);
  I.push_back(0);
  dep.assign(N,0);
  Eidx.assign(N,-1);
  rep(i,I.size()){
    int p = I[i];
    for(Edge e : E[p]) if(P[p] != e.v){
      P[e.v] = p;
      dep[e.v] = dep[p] + cost[e.i];
      Eidx[e.v] = e.i;
      I.push_back(e.v);
    }
  }
}

int LCA(int u,int v){
  return hld.lca(u,v);
}

int dist0(int u,int v){
  return hld.dist(u,v);
}
mll dist1(int u,int v){
  int g = LCA(u,v);
  return dep[u] + dep[v] - dep[g] * 2;
}

void build_flows(){

  iEidx.assign(M,-1);
  rep(i,N) if(Eidx[i] != -1) iEidx[Eidx[i]] = i;

  flowIdx.assign(N,-1);
  
  nachia::Dsu G2(N);
  for(Edge e : flows){
    int g = G2.leader(LCA(e.u,e.v));
    for(int s : {e.u,e.v}){
      int p = G2.leader(s);
      while(p != g){
        flowIdx[p] = e.i;
        p = G2.merge(P[p],p);
      }
    }
  }
}

int path_includes(int u,int v,int z){
  if(iEidx[z] == -1) return -1;
  if(hld.median(u,v,J[z].u) != J[z].u) return -1;
  if(hld.median(u,v,J[z].v) != J[z].v) return -1;
  int res = flowIdx[iEidx[z]];
  if(res == -1) return -2;
  return res;
}

mll shortest_using(int u,int v,int z){
  mll ans = cost[z];
  if(dist0(u,J[z].u) + dist0(v,J[z].v) < dist0(u,J[z].v) + dist0(v,J[z].u))
    ans += dist1(u,J[z].u) + dist1(v,J[z].v);
  else
    ans += dist1(u,J[z].v) + dist1(v,J[z].u);
  return ans;
}


int main(){
  using nachia::cin;
  using nachia::cout;
  read_graph();
  initLCA();
  build_flows();
  int Q; cin >> Q;
  rep(q,Q){
    int u,v,z; cin >> u >> v >> z; u--; v--; z--;
    int inc = path_includes(u,v,z);
    if(inc == -2){ cout << "-1\n"; continue; }
    if(inc == -1){ cout << dist1(u,v).val() << "\n"; continue; }
    auto e = J[inc];
    mll ans = shortest_using(u,v,e.i);
    cout << ans.val() << "\n";
  }
  return 0;
}
