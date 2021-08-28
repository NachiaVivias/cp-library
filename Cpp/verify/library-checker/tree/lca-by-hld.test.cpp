#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../../../Include/tree/heavylightdecomposition.hpp"

using namespace std;

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;

int main() {
  int N,Q; cin >> N >> Q;
  vector<vector<int>> E(N);
  for(int i=1; i<N; i++){
    int p; cin >> p;
    E[p].push_back(i);
  }

  heavy_light_decomposition hld(E);

  for(int i=0; i<Q; i++){
    int u,v; cin >> u >> v;
    int res = hld.lca(u,v);
    cout << res << "\n";
  }
  return 0;
}


struct ios_do_not_sync{
  ios_do_not_sync(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
  }
} ios_do_not_sync_instance;


