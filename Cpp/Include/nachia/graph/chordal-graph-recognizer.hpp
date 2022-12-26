#pragma once
#include "../graph/graph.hpp"
#include <vector>
#include <algorithm>

namespace nachia{

// for simple undirected graph
struct ChordalGraphRecognizer{
private:
    Graph graph;
    CsrArray<int> adj;
    std::vector<int> m_mcsordered;
    bool m_ischordalgraph;
    CsrArray<int> adj2;
    int m_x, m_y, m_z;
    std::vector<int> m_inducedCycle;
    int m_phase;
    static std::vector<bool> AdjacencyQuery(
        const CsrArray<int>& adj,
        const Graph& queries
    ){
        int n = adj.size(), q = queries.numEdges();
        std::vector<bool> res(q, false);
        auto qadj = queries.getEdgeIndexArray(false);
        std::vector<int> buf(n, -1);
        for(int i=0; i<n; i++){
            for(int nx : adj[i]) buf[nx] = i;
            for(int qi : qadj[i]) if(buf[queries[qi].to] == i) res[qi] = true;
        }
        return res;
    }
public:
    ChordalGraphRecognizer(Graph g) : graph(std::move(g)), m_phase(0) {}
    std::vector<int> getMaximumCardinalitySearchOrder(){
        if(m_phase >= 1) return m_mcsordered;
        adj = graph.getAdjacencyArray(true);
        int n = adj.size();
        std::vector<int> res(n), lp(n*2+1), rp(n*2+1), idx(n, 0);
        for(int i=0; i<=n*2; i++) lp[i] = rp[i] = i;
        int li = n;
        auto Insert = [&](int i, int j){
            rp[lp[j]] = i;
            lp[i] = lp[j];
            lp[j] = i;
            rp[i] = j;
        };
        auto Erase = [&](int i){
            rp[lp[i]] = rp[i];
            lp[rp[i]] = lp[i];
        };
        for(int i=0; i<n; i++) Insert(i, n);
        for(int i=0; i<n; i++){
            li++;
            while(lp[li] == li) li--;
            int v = lp[li];
            idx[v] = -1;
            Erase(v);
            for(int nx : adj[v]) if(idx[nx] >= 0){ Erase(nx); Insert(nx, n+(++idx[nx])); }
            res[i] = v;
        }
        m_phase = 1;
        return m_mcsordered = std::move(res);
    }

    bool isChordalGraph(){
        if(m_phase < 1) getMaximumCardinalitySearchOrder();
        if(m_phase >= 2) return m_ischordalgraph;
        int n = graph.numVertices();
        std::vector<int> invMcs(n);
        for(int i=0; i<n; i++) invMcs[m_mcsordered[i]] = i;
        std::vector<int> pre(n, -1);
        Graph ng = graph; ng.contract(n, invMcs);
        adj2 = ng.getAdjacencyArray(true);
        for(int i=0; i<n; i++) for(int j : adj2[i]) if(j < i && pre[i] < j) pre[i] = j;
        Graph queries(n, false);
        std::vector<int> Z;
        for(int i=0; i<n; i++) if(pre[i] != -1){
            for(int j : adj2[i]) if(j < pre[i]){
                queries.addEdge(pre[i], j);
                Z.push_back(i);
            }
        }
        auto qres = AdjacencyQuery(adj2, queries);
        m_x = m_y = m_z = -1;
        for(int i=0; i<queries.numEdges(); i++){
            if(!qres[i]){
                m_x = queries[i].to;
                m_y = queries[i].from;
                m_z = Z[i];
                break;
            }
        }
        m_phase = 2;
        return m_ischordalgraph = (m_z == -1);
    }

    std::vector<int> findInducedCycle(){
        if(m_phase >= 3) return m_inducedCycle;
        if(isChordalGraph()){ m_phase = 3; return m_inducedCycle = {}; }
        int n = graph.numVertices();
        std::vector<int> dist(n, 0);
        std::vector<int> parent(n, -1);
        std::vector<int> bfs = {m_x, m_y};
        for(int inc : adj2[m_z]) parent[inc] = -2;
        dist[m_x] = -1; dist[m_y] = 1;
        parent[m_x] = parent[m_y] = m_z;
        int d = n+1, xx = -1, yy = -1;
        for(int i=0; i<(int)bfs.size(); i++){
            int p = bfs[i];
            for(int q : adj2[p]) if(q < p && parent[q] != -2){
                if(dist[p] < 0 && dist[q] > 0 && dist[q] - dist[p] < d){
                    d = dist[q] - dist[p]; xx = p; yy = q;
                }
                else if(dist[p] > 0 && dist[q] < 0 && dist[p] - dist[q] < d){
                    d = dist[p] - dist[q]; xx = q; yy = p;
                }
                else if(dist[q] == 0){
                    dist[q] = dist[p] + ((dist[p] < 0) ? -1 : 1);
                    parent[q] = p;
                    bfs.push_back(q);
                }
            }
        }
        std::vector<int> res(d+1);
        int off = -dist[xx];
        res[off] = m_mcsordered[m_z];
        do { res[dist[xx]+off] = m_mcsordered[xx]; xx = parent[xx]; } while(xx != m_z);
        do { res[dist[yy]+off] = m_mcsordered[yy]; yy = parent[yy]; } while(yy != m_z);
        m_phase = 3;
        return m_inducedCycle = std::move(res);
    }

    std::vector<int> getPerfectEliminationOrdering(){
        if(!isChordalGraph()) return {};
        auto res = getMaximumCardinalitySearchOrder();
        std::reverse(res.begin(), res.end());
        return res;
    }
};


} // namespace nachia
