
#include "../array/csr-array.hpp"
#include <utility>
#include <vector>
#include <algorithm>
#include <cassert>
#include <tuple>

namespace nachia{

class StaticTopTree{
public:
    int m_n;
    nachia::CsrArray<int> m_children;
    std::vector<int> m_parent;
    std::vector<int> m_parentEdge;
    int m_root;

    struct Node{
        int p = -1, l = -1, r = -1;
        enum Type{ TyCompress, TyRake1, TyRake2, TyEdge } ty = TyEdge;
    };
    std::vector<Node> m_node;

    StaticTopTree(int n, std::vector<std::pair<int,int>> tree, int root = 0){
        m_n = n;
        assert((int)tree.size() == n-1);
        assert(0 <= root && root < n);
        m_root = root;
        nachia::CsrArray<int> adj; {
            std::vector<std::pair<int,int>> dedges(n*2-2);
            for(int i=0; i<n-1; i++){
                assert(0 <= tree[i].first && tree[i].first < n);
                assert(0 <= tree[i].second && tree[i].second < n);
                dedges[i*2] = tree[i];
                dedges[i*2+1] = { tree[i].second, tree[i].first };
            }
            adj = nachia::CsrArray<int>::Construct(n, dedges);
        }
        m_parent.assign(n, -2);
        m_parentEdge.assign(n, -1);
        std::vector<int> bfs = {m_root};
        bfs.reserve(n);
        m_parent[m_root] = -1;
        for(int i=0; i<(int)bfs.size(); i++){
            int p = bfs[i];
            for(int nx : adj[p]) if(m_parent[nx] == -2){
                m_parent[nx] = p;
                bfs.push_back(nx);
            }
        }
        for(int i=0; i<n; i++) assert(m_parent[i] != -2); // not connected
        for(int i=0; i<n-1; i++){
            auto& e = tree[i];
            if(m_parent[e.first] == e.second) std::swap(e.first, e.second);
            m_parentEdge[e.second] = i;
        }
        adj = nachia::CsrArray<int>::Construct(n, tree);
        std::vector<int> nd(n, 1);
        for(int i=n-1; i>=1; i--) nd[m_parent[bfs[i]]] += nd[bfs[i]];
        for(int p=0; p<n; p++) for(int e=1; e<adj[p].size(); e++) if(nd[adj[p][0]] < nd[adj[p][e]]) std::swap(adj[p][0], adj[p][e]);
        m_node.resize(n*2-3);
        for(int i=0; i<n-1; i++) m_node[i].ty = Node::TyEdge;
        std::vector<int> troot(n, -1);
        int trp = n*2-3;
        troot[bfs[0]] = --trp;
        for(int s : bfs) if(m_parent[s] < 0 || adj[m_parent[s]][0] != s){
            struct SzNode { int sz, vid, nx; };
            std::vector<SzNode> sznode;
            std::vector<int> Hid = {0};
            std::vector<int> boundarySize;
            if(m_parent[s] >= 0){
                sznode.push_back({ 1, m_parentEdge[s], adj[m_parent[s]][0] });
                Hid.push_back(Hid.back()+1);
            }
            for(int p=s; ; p=adj[p][0]){
                if(adj[p].size() == 0) break;
                for(int e=1; e<adj[p].size(); e++){
                    if(adj[adj[p][e]].size() == 0) sznode.push_back({ 1, m_parentEdge[adj[p][e]], adj[p][e] });
                    else sznode.push_back({ nd[adj[p][e]], -1, adj[p][e] });
                    Hid.push_back(Hid.back());
                }
                sznode.push_back({ 1, m_parentEdge[adj[p][0]], adj[p][0] });
                Hid.push_back(Hid.back() + 1);
            }
            boundarySize.assign(sznode.size()+1, 0);
            for(int i=0; i<(int)sznode.size(); i++) boundarySize[i+1] = boundarySize[i] + sznode[i].sz;
            struct QueNode{ int p, l, r; };
            std::vector<QueNode> Que = { { troot[s], 0, (int)sznode.size() } };
            Que.reserve(sznode.size() * 2);
            for(int i=0; i<(int)Que.size(); i++){
                int tp = Que[i].p, l = Que[i].l, r = Que[i].r;
                if(r-l == 1){
                    troot[sznode[l].nx] = tp;
                    continue;
                }
                int m = Que[i].l;
                while(boundarySize[m] - boundarySize[l] < boundarySize[r] - boundarySize[m+1]) m++;
                if(Hid[l] == Hid[m]) m_node[tp].ty = Node::TyRake2;
                else if(Hid[m] == Hid[r]) m_node[tp].ty = Node::TyRake1;
                else m_node[tp].ty = Node::TyCompress;
                int pl = (m-l == 1) ? sznode[l].vid : -1;
                if(pl == -1) pl = --trp;
                int pr = (r-m == 1) ? sznode[m].vid : -1;
                if(pr == -1) pr = --trp;
                m_node[tp].l = pl;
                m_node[tp].r = pr;
                m_node[pl].p = tp;
                m_node[pr].p = tp;
                Que.push_back({ pl, l, m });
                Que.push_back({ pr, m, r });
            }
        }
        std::swap(m_children, adj);
    }

    StaticTopTree() : StaticTopTree(2, {{0,1}}) {}
};

} // namespace nachia
