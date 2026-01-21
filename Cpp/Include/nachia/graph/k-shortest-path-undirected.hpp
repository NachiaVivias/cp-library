#pragma once
#include <vector>
#include <queue>
#include <utility>
#include <optional>
#include <algorithm>

namespace nachia {

    template<class Weight>
    struct KShortestPathUndirected {
        struct Edge { int u, v, uv, id; Weight w; };
        int n;
        Weight inf;
        Weight zero;
        std::vector<Edge> edges;
        std::vector<std::vector<int>> inc;
        int s;
        int t;

        KShortestPathUndirected(int _n, Weight _inf, Weight _zero, int _s, int _t)
            : n(_n), inf(_inf), zero(_zero), edges(), inc(_n), s(_s), t(_t) {}

        int addEdge(int u, int v, Weight w){
            int e = edges.size();
            edges.push_back({ u, v, u ^ v, e, w });
            inc[u].push_back(e);
            inc[v].push_back(e);
            return e;
        }

        struct ShortestPathTree {
            std::vector<int> parent;
            std::vector<Weight> dist;
            std::vector<int> root;
            void resize(int n, Weight inf){
                parent.resize(n, -1);
                dist.resize(n, inf);
                root.resize(n, -1);
            }
        };

        void updateTree(const std::vector<bool>& edgeMask, ShortestPathTree& tree){
            ShortestPathTree t; std::swap(t, tree);
            using Node = std::pair<Weight, int>;
            std::priority_queue<Node, std::vector<Node>, std::greater<Node>> que;
            auto check = [&](int v, int p, int r, Weight d) -> void {
                if(!(d < t.dist[v])) return;
                t.dist[v] = d;
                t.parent[v] = p;
                t.root[v] = r;
                que.push({ d, v });
            };
            for(int v=0; v<n; v++) if(t.root[v] != -1) que.push({t.dist[v], v});
            while(que.size()){
                auto [d, v] = que.top(); que.pop();
                if(t.dist[v] < d) continue;
                for(int e : inc[v]) if(edgeMask[e]){
                    check(v ^ edges[e].uv, e, t.root[v], d + edges[e].w);
                }
            }
            std::swap(t, tree);
        }

        std::vector<int> getPath(const ShortestPathTree& t, int start){
            std::vector<int> path;
            for(int v=start; t.root[v]!=v; v^=edges[path.back()].uv){
                if(t.parent[v] < 0) return {};
                path.push_back(t.parent[v]);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        ShortestPathTree solve(const std::vector<bool>& edgeMask){
            ShortestPathTree tree; tree.resize(n, inf);
            tree.root[s] = s;
            tree.dist[s] = zero;
            updateTree(edgeMask, tree);
            return tree;
        }

        struct Instance {
            KShortestPathUndirected* data;
            std::vector<bool> edgeMask;
            Weight wt;
            std::vector<int> path;
            std::vector<std::pair<int, Weight>> cand;
            int lim;

            struct SplitResult {
                std::vector<int> path;
                std::vector<Instance> newInstances;
            };

            Instance(KShortestPathUndirected* _data, std::vector<bool> _edgeMask)
                : data(_data), edgeMask(_edgeMask) {}

            bool solve(){
                auto tree = data->solve(edgeMask);
                path = data->getPath(tree, data->t);
                if(path.empty()) return false;
                lim = path.size();
                return true;
            }

            bool solve2nd(){
                ShortestPathTree treeS, treeT;
                treeS.resize(data->n, data->inf);
                treeT.resize(data->n, data->inf);
                int pathLen = path.size();
                std::vector<int> pathVtx(pathLen + 1);
                pathVtx[0] = data->s;
                for(int i=0; i<pathLen; i++) pathVtx[i+1] = pathVtx[i] ^ data->edges[path[i]].uv;

                for(int h : {data->s, data->t}){
                    treeS.dist[h] = data->zero;
                    treeS.root[h] = h;
                    for(int i=0; i<pathLen; i++){
                        auto e = data->edges[path[i]];
                        treeS.root[pathVtx[i+1]] = pathVtx[i+1];
                        treeS.dist[pathVtx[i+1]] = treeS.dist[pathVtx[i]] + e.w;
                    }
                    data->updateTree(edgeMask, treeS);
                    std::swap(treeS, treeT);
                    std::reverse(path.begin(), path.end());
                    std::reverse(pathVtx.begin(), pathVtx.end());
                }
                std::vector<int> mainPath(data->edges.size(), -1);
                for(int i=0; i<pathLen; i++) mainPath[path[i]] = i;
                std::vector<int> mainPathVtx(data->n, -1);
                for(int i=0; i<=pathLen; i++) mainPathVtx[pathVtx[i]] = i;

                std::vector<Weight> nextWeight(pathLen, data->inf);
                for(int i=0; i<int(data->edges.size()); i++) if(edgeMask[i] && mainPath[i] == -1){
                    auto e = data->edges[i];
                    for(int t=0; t<2; t++){
                        std::swap(e.u, e.v);
                        if(treeS.root[e.u] < 0 || treeT.root[e.v] < 0) continue;
                        if(mainPathVtx[treeS.root[e.u]] >= mainPathVtx[treeT.root[e.v]]) continue;
                        Weight& dest = nextWeight[mainPathVtx[treeS.root[e.u]]];
                        dest = std::min(dest, e.w + treeS.dist[e.u] + treeT.dist[e.v]);
                    }
                }

                Weight minWeight = data->inf;
                for(int i=0; i<lim; i++) if(nextWeight[i] < minWeight){
                    minWeight = nextWeight[i];
                    cand.push_back({ i, minWeight });
                }
                wt = minWeight;
                return !cand.empty();
            }

            static SplitResult split(Instance src){
                SplitResult res;
                auto [rank, weight] = src.cand.back();
                src.cand.pop_back();

                {
                    auto nextEdgeMask = src.edgeMask;
                    int p = src.data->s;
                    for(int i=0; i<rank; i++){
                        for(int e : src.data->inc[p]) nextEdgeMask[e] = false;
                        p ^= src.data->edges[src.path[i]].uv;
                    }
                    for(int i=0; i<rank; i++) nextEdgeMask[src.path[i]] = true;
                    nextEdgeMask[src.path[rank]] = false;
                    Instance buf(src.data, std::move(nextEdgeMask));
                    buf.solve();
                    res.path = buf.path;
                    if(buf.solve2nd()) res.newInstances.push_back(std::move(buf));
                }

                {
                    auto nextEdgeMask = src.edgeMask;
                    int p = src.data->s;
                    for(int i=0; i<=rank; i++){
                        for(int e : src.data->inc[p]) nextEdgeMask[e] = false;
                        p ^= src.data->edges[src.path[i]].uv;
                    }
                    for(int i=0; i<=rank; i++) nextEdgeMask[src.path[i]] = true;
                    Instance buf(src.data, std::move(nextEdgeMask));
                    buf.path = src.path;
                    buf.lim = src.lim;
                    if(buf.solve2nd()) res.newInstances.push_back(std::move(buf));
                }
                
                if(src.cand.size()){
                    src.wt = src.cand.back().second;
                    src.lim = rank;
                    res.newInstances.push_back(std::move(src));
                }
                
                return res;
            }
        };

        struct CmpWt {
            bool operator()(const Instance& l, const Instance& r){
                return r.wt < l.wt;
            }
        };

        std::priority_queue<Instance, std::vector<Instance>, CmpWt> que;
        bool KthStarted = false;

        std::optional<std::vector<int>> getNextSmallest(){
            if(!KthStarted){
                KthStarted = true;
                Instance inst(this, std::vector<bool>(edges.size(), true));
                if(!inst.solve()) return std::nullopt;
                auto res = inst.path;
                if(inst.solve2nd()) que.push(std::move(inst));
                return res;
            }
            if(que.empty()) return std::nullopt;
            auto h = Instance::split(que.top()); que.pop();
            for(auto& nx : h.newInstances) que.push(std::move(nx));
            return h.path;
        }
    };

} // namespace nachia
