#define PROBLEM "https://yukicoder.me/problems/no/2296"
#include "nachia/tree/incremental-forest.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    using namespace std;
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int N, X, Q; cin >> N >> X >> Q;
    nachia::IncrementalForest forest(N);
    std::vector<long long> depth(N);
    std::vector<long long> weight;
    struct Diam { long long d; int v; int w; };
    std::vector<Diam> diam(N);
    for(int i=0; i<N; i++) diam[i] = { 0,i,i };
    auto dist = [&](int u, int v) -> long long {
        int g = forest.lca(u, v);
        if(g < 0) return -1;
        long long d = depth[u] - 2 * depth[g] + depth[v];
        return d;
    };
    auto mergeDiam = [&](Diam l, Diam r) -> Diam {
        Diam res = l;
        if(res.d < r.d) res = r;
        auto upd = [&](int v, int w){
            long long d = dist(v,w);
            if(res.d < d) res = { d,v,w };
        };
        upd(l.v, r.v);
        upd(l.v, r.w);
        upd(l.w, r.v);
        upd(l.w, r.w);
        return res;
    };
    for(int qi=0; qi<Q; qi++){
        int t; cin >> t;
        if(t == 1){
            int v, w; cin >> v >> w;
            int u = X;
            int ur = forest.rootOf(u);
            int vr = forest.rootOf(v);
            if(forest.addEdge(u, v) < 0){ cout << "#"; return 0; }
            int xr = forest.rootOf(v);
            weight.push_back(w);
            if(forest.parentOf(v) != u) std::swap(u, v);
            std::vector<int> bfs;
            bfs.push_back(v);
            for(int i=0; i<int(bfs.size()); i++){
                int x = bfs[i];
                depth[x] = depth[forest.parentOf(x)] + weight[forest.parentEdgeOf(x)];
                for(int y : forest.children(x)) bfs.push_back(y);
            }
            diam[xr] = mergeDiam(diam[ur], diam[vr]);
        }
        if(t == 2){
            int u, v; cin >> u >> v;
            long long d = dist(u, v);
            cout << d << '\n';
            if(d != -1) X = (X + d) % N;
        }
        if(t == 3){
            int v; cin >> v;
            cout << diam[forest.rootOf(v)].d << '\n';
        }
        if(t == 4){
            int v; cin >> v;
            X = (X + v) % N;
        }
    }
    return 0;
}
