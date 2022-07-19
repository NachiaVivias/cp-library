#pragma once

#include <vector>
#include <utility>

namespace nachia{

struct AdjacencyListEdgeIndexed{
public:
    struct Edge { int to; int edgeidx; };
    struct AdjacencyListRange{
        using iterator = typename std::vector<Edge>::const_iterator;
        iterator begi, endi;
        iterator begin() const { return begi; }
        iterator end() const { return endi; }
        int size() const { return (int)std::distance(begi, endi); }
        const Edge& operator[](int i) const { return begi[i]; }
    };
private:
    int mn;
    std::vector<Edge> E;
    std::vector<int> I;
public:
    AdjacencyListEdgeIndexed(int n, const std::vector<std::pair<int,int>>& edges, bool rev){
        mn = n;
        std::vector<int> buf(n+1, 0);
        for(auto [u,v] : edges){ ++buf[u]; if(rev) ++buf[v]; }
        for(int i=1; i<=n; i++) buf[i] += buf[i-1];
        E.resize(buf[n]);
        for(int i=(int)edges.size()-1; i>=0; i--){
            auto [u,v] = edges[i];
            E[--buf[u]] = { v, i };
            if(rev) E[--buf[v]] = { u, i };
        }
        I = std::move(buf);
    }
    AdjacencyListEdgeIndexed() : AdjacencyListEdgeIndexed(0, {}, false) {}
    AdjacencyListRange operator[](int u) const {
        return AdjacencyListRange{ E.begin() + I[u], E.begin() + I[u+1] };
    }
    int num_vertices() const { return mn; }
    int size() const { return num_vertices(); }
    int num_edges() const { return E.size(); }
    AdjacencyListEdgeIndexed reversed_edges() const {
        AdjacencyListEdgeIndexed res;
        int n = res.mn = mn;
        std::vector<int> buf(n+1, 0);
        for(auto [v,i] : E) ++buf[v];
        for(int i=1; i<=n; i++) buf[i] += buf[i-1];
        res.E.resize(buf[n]);
        for(int u=0; u<n; u++) for(auto [v,i] : operator[](u)) res.E[--buf[v]] = {u,i};
        res.I = std::move(buf);
        return res;
    }
};

} // namespace nachia
