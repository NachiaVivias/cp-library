#pragma once
#include "../graph/graph.hpp"
#include <vector>
#include <utility>
#include <cassert>

namespace nachia{

struct ThreeEdgeConnectedComponents{
public:
    ThreeEdgeConnectedComponents(Graph G = Graph(0, true)){
        solve(std::move(G));
    }
    int num2EdgeCCComponents() const noexcept { return m_num2Component; }
    int num3EdgeCCComponents() const noexcept { return m_num3Component; }
    int operator[](int w) const { return m_color3[w]; }
    CsrArray<int> get3EdgeCCVertices() const {
        return InvMapping(num3EdgeCCComponents(), m_color3);
    }
    CsrArray<int> get2EdgeCCVertices() const {
        return InvMapping(num2EdgeCCComponents(), m_color2);
    }
    std::vector<int> getVertexMapping() const { return m_color3; }
private:
    int m_num2Component;
    int m_num3Component;
    std::vector<int> m_color3;
    std::vector<int> m_color2;
    int numVertices() const { return int(m_color3.size()); }
    static CsrArray<int> InvMapping(int m, const std::vector<int>& a){
        int n = int(a.size());
        std::vector<int> sep(m+1);
        std::vector<int> val(n);
        for(int i=0; i<n; i++) sep[a[i]]++;
        for(int i=0; i<m; i++) sep[i+1] += sep[i];
        for(int i=0; i<n; i++) val[--sep[a[i]]] = i;
        return CsrArray<int>::FromRaw(std::move(val), std::move(sep));
    }
    static int assignColors(std::vector<int>& a, const std::vector<int>& idx){
        int i = 0;
        for(int v : idx) a[v] = (a[v] == -1 ? i++ : a[a[v]]);
        return i;
    }
    void solve(Graph G){
        assert(G.isUndirected());
        int n = G.numVertices();
        int m = G.numEdges();
        std::vector<int> parEdge(n, -1);
        std::vector<int> dfsin(n, -1);
        std::vector<int> dfsout(n, 0);
        std::vector<int> lowpt(n, n);
        std::vector<int> deg(n, 0);
        std::vector<int> path(n, -1);
        m_color2.assign(n, -1);
        m_color3.assign(n, -1);
        auto inc = G.getEdgeIndexArray(true);
        int dfsid = 0;
        auto absorb = [&](int x, int borderl, int borderr){
            while(path[x] >= 0){
                int y = path[x];
                if(borderl < dfsin[y] || dfsout[y] < borderr) break;
                deg[x] += deg[y] - 2; deg[y] = 0;
                path[x] = path[y];
                m_color3[y] = x;
            }
        };
        for(int s=0; s<n; s++) if(dfsin[s] == -1){
            dfsin[s] = dfsid++;
            int w = s;
            while(true){
                if(inc[w].size() <= dfsout[w]){
                    dfsout[w] = dfsid;
                    if(parEdge[w] < 0) break;
                    int u = w; w = w ^ G[parEdge[w]].xorval();
                    if(dfsin[w] >= lowpt[u]){
                        m_color2[u] = w;
                        int lowpt_u = lowpt[u];
                        if(deg[u] == 2){ deg[u] -= 2; u = path[u]; }
                        if(lowpt[w] <= lowpt_u){
                            int buf = path[w];
                            path[w] = u;
                            absorb(w, n, -1);
                            path[w] = buf;
                        } else {
                            lowpt[w] = lowpt_u;
                            absorb(w, n, -1);
                            path[w] = u;
                        }
                    } else {
                        deg[w] -= 1;
                        deg[u] -= 1;
                    }
                    continue;
                }
                int e = inc[w][dfsout[w]++];
                int u = w ^ G[e].xorval();
                if(u == w) continue;
                deg[w] += 1;
                if(e == parEdge[w]){
                    continue;
                }
                if(dfsin[u] == -1){
                    dfsin[u] = dfsid++;
                    parEdge[u] = e;
                    w = u; continue;
                }
                if(dfsin[u] < dfsin[w]){
                    if(dfsin[u] < lowpt[w]){
                        lowpt[w] = dfsin[u];
                        absorb(w, n, -1);
                    }
                } else {
                    absorb(w, dfsin[u], dfsout[u]);
                    deg[w] -= 2;
                }
            }
        }
        for(int i=0; i<n; i++) dfsout[dfsin[i]] = i;
        m_num2Component = assignColors(m_color2, dfsout);
        m_num3Component = assignColors(m_color3, dfsout);
    }
};

} // namespace nachia

