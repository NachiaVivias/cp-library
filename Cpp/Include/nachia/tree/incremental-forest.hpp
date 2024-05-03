#pragma once
#include <vector>
#include <algorithm>

namespace nachia {

struct IncrementalForest{
    struct Node {
        int jump;
        int parent;
        int parentEdge;
        int depth;
        int child;
        int brother;
    };
    IncrementalForest(int n = 0){
        nodes.assign(n, { -1, -1, -1, 0, -1, -1 });
        dsu.assign(n, -1);
        todbl.assign(1, false);
        makeToDbl(n);
        edgeIndex = 0;
    }
    int addNode(){
        int v = numVertices();
        nodes.push_back({ -1, -1, -1, 0, -1, -1 });
        makeToDbl(numVertices());
        return v;
    }
    int addEdge(int u, int v){
        std::vector<int> bfs;
        {
            int ru = rootOf(u);
            int rv = rootOf(v);
            if(ru == rv) return -1;
            if(-dsu[ru] < -dsu[rv]){ std::swap(u, v); std::swap(ru, rv); }
            bfs = std::vector<int>(-dsu[rv]);
            dsu[ru] += dsu[rv];
            dsu[rv] = ru;
        }
        int e = edgeIndex++;
        int bfsp = 0;
        auto setParent = [&](int v, int p) -> void {
            nodes[v].parent = p;
            nodes[v].depth = nodes[p].depth + 1;
            nodes[v].jump = todbl[nodes[v].depth - 1] ? nodes[nodes[p].jump].jump : p;
        };
        int p = u;
        int p2 = v;
        for(int x=nodes[v].child; x>=0; x=nodes[x].brother) bfs[bfsp++] = x;
        while(nodes[p2].parent >= 0){
            int w = nodes[p2].parent;
            for(int *pc=&nodes[w].child; *pc>=0; ){
                int x = *pc;
                if(x == p2){
                    *pc = nodes[x].brother;
                    std::swap(nodes[p2].parentEdge, e);
                    nodes[p2].brother = nodes[p].child;
                    nodes[p].child = p2;
                    setParent(p2, p);
                } else {
                    bfs[bfsp++] = x;
                    pc = &nodes[x].brother;
                }
            }
            p = p2; p2 = w;
        }
        std::swap(nodes[p2].parentEdge, e);
        nodes[p2].brother = nodes[p].child;
        nodes[p].child = p2;
        setParent(p2, p);
        for(int i=0; i<bfsp; i++){
            int w = bfs[i];
            setParent(w, nodes[w].parent);
            for(int x=nodes[w].child; x>=0; x=nodes[x].brother) bfs[bfsp++] = x;
        }
        return edgeIndex - 1;
    }
    int numVertices(){ return nodes.size(); }
    int rootOf(int u){ return (dsu[u] < 0) ? u : (dsu[u] = rootOf(dsu[u])); }
    bool areConnected(int u, int v){ return rootOf(u) == rootOf(v); }
    int componentSize(int u){ return -dsu[rootOf(u)]; }
    int parentOf(int u){ return nodes[u].parent; }
    int parentEdgeOf(int u){ return nodes[u].parentEdge; }
    int depth(int u){ return nodes[u].depth; }
    int lca(int u, int v){
        if(!areConnected(u, v)) return -1;
        if(depth(u) < depth(v)) std::swap(u, v);
        int dv = depth(v);
        while(depth(u) != dv){
            u = (depth(nodes[u].jump) >= dv ? nodes[u].jump : nodes[u].parent);
        }
        while(u != v){
            if(nodes[u].jump != nodes[v].jump){
                u = nodes[u].jump;
                v = nodes[v].jump;
            } else {
                u = nodes[u].parent;
                v = nodes[v].parent;
            }
        }
        return u;
    }
    int middle(int u, int v, int w){
        if(!areConnected(u, v) || !areConnected(v, w)) return -1;
        return lca(u,v) ^ lca(v,w) ^ lca(w,u);
    }
    int dist(int u, int v){
        if(!areConnected(u, v)) return -1;
        return depth(u) - depth(lca(u, v)) * 2 + depth(v);
    }
    int la(int u, int d){
        if(d < 0 || depth(u) < d) return -1;
        while(depth(u) > d){
            int j = nodes[u].jump;
            u = (depth(j) >= d ? j : parentOf(u));
        }
        return u;
    }
    int la(int from, int to, int d){
        int q = dist(from, to);
        if(q == -1 || d < 0 || q < d) return -1;
        if(depth(from) - d > depth(to) - (q-d)) return la(from, depth(from) - d);
        return la(to, depth(to) - (q-d));
    }
    
    struct ChildrenIterRange {
    struct Iter {
        std::vector<Node>::iterator nodes; int v;
        int operator*() const { return v; }
        Iter& operator++(){ v = nodes[v].brother; return *this; }
        Iter operator++(int) const { auto a = *this; return ++a; }
        bool operator==(Iter& r) const { return v == r.v; }
        bool operator!=(Iter& r) const { return v != r.v; }
    };
        std::vector<Node>::iterator nodes; int v;
        Iter begin() const { return { nodes, nodes[v].child }; }
        Iter end() const { return { nodes, -1 }; }
    };
    ChildrenIterRange children(int v){
        return ChildrenIterRange{ nodes.begin(), v };
    }
private:
    std::vector<Node> nodes;
    std::vector<int> dsu;
    std::vector<bool> todbl;
    int edgeIndex;
    void makeToDbl(int x){
        while(int(todbl.size()) < x){
            int z = int(todbl.size());
            todbl.resize(z*2+1);
            std::copy(todbl.begin(), todbl.begin() + z, todbl.begin() + z);
            todbl[z*2] = true;
        }
    }
};

} // namespace nachia
