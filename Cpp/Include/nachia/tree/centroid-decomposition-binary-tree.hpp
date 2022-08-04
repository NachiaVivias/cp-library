#pragma once

#include "../graph/adjacency-list.hpp"

#include <vector>
#include <algorithm>
#include <utility>
#include <cassert>
#include <queue>


namespace nachia {

struct CentroidDecompositionBinaryTree{
public:
    struct UpdatePoint { int i; int p; };
    struct QueryRange { int i, l, r; };
private:
    struct VectorIntView{
        using Iter = typename std::vector<int>::iterator;
        Iter li, ri;
        VectorIntView(std::vector<int>& src, int l, int r) :
            li(src.begin() + l) ,
            ri(src.begin() + r)
        {}
        Iter begin() const { return li; }
        Iter end() const { return ri; }
        int size() const { return ri - li; }
        int& operator[](int i) const { return li[i]; }
    };

    struct CDBTNode{
        int array_idx;
        int cd_depth;
        int sib;
        int parent;
        int array_left;
        int size;
        int exclude_cent;
    };

    std::vector<std::vector<int>> cd_dist;
    std::vector<CDBTNode> bt_nodes;
    std::vector<std::vector<int>> bt_arrays;
    std::vector<std::vector<int>> bt_arrays_sep;
    std::vector<std::vector<UpdatePoint>> update_points;

    QueryRange get_one_node_range(const CDBTNode& node, int l, int r){
        QueryRange res;
        res.i = node.array_idx;
        res.l = bt_arrays_sep[res.i][node.array_left + std::max(0, std::min(l - node.exclude_cent, node.size))];
        res.r = bt_arrays_sep[res.i][node.array_left + std::max(0, std::min(r - node.exclude_cent, node.size))];
        return res;
    }

    VectorIntView array_for_node(std::vector<std::vector<int>>& src, const CDBTNode& node){
        return VectorIntView(src[node.array_idx], node.array_left, node.array_left + node.size);
    }
    VectorIntView sep_for_node(std::vector<std::vector<int>>& src, const CDBTNode& node){
        return VectorIntView(src[node.array_idx], node.array_left, node.array_left + (node.size + 1));
    }

    static int find_centroid(
        const nachia::AdjacencyList& adj,
        std::vector<int>& Z,
        int root
    ){
        while(true){
            int nx = -1;
            for(int c : adj[root]) if(Z[c] * 2 > Z[root]){ nx = c; break; }
            if(nx < 0) break;
            Z[root] -= Z[nx]; Z[nx] += Z[root];
            root = nx;
        }
        return root;
    }

public:

    CentroidDecompositionBinaryTree() {}
    CentroidDecompositionBinaryTree(const nachia::AdjacencyList& adj){
        int n = adj.num_vertices();
        assert(1 <= n);
        std::vector<int> Z;
        {
            std::vector<int> bfs = {0};
            std::vector<int> P(n,-1);
            for(int i=0; i<n; i++){
                int p = bfs[i];
                for(int e : adj[p]) if(P[p] != e){
                    P[e] = p;
                    bfs.push_back(e);
                }
            }
            Z.assign(n, 1);
            for(int i=n-1; i>=1; i--) Z[P[bfs[i]]] += Z[bfs[i]];
        }

        std::vector<std::pair<int,int>> cd_bfs;
        std::vector<int> cd_bfs_adji = { 1 };
        std::vector<int> cd_dep(n, -1);
        std::vector<int> cd_component_size(n);
        cd_bfs.push_back(std::make_pair(-1, find_centroid(adj, Z, 0)));
        cd_dep[cd_bfs.front().second] = 0;
        for(int i=0; i<(int)cd_bfs.size(); i++){
            int g = cd_bfs[i].second;
            cd_component_size[g] = Z[g];
            Z[g] = 0;
            for(int nx : adj[g]) if(cd_dep[nx] == -1){
                int nxg = find_centroid(adj, Z, nx);
                cd_bfs.push_back(std::make_pair(nx, nxg));
                cd_dep[nxg] = cd_dep[g] + 1;
            }
            cd_bfs_adji.push_back(cd_bfs.size());
        }

        int cd_height = *std::max_element(cd_dep.begin(), cd_dep.end());
        cd_dist.assign(cd_height+1, std::vector<int>(n, -1));
        for(int dep=0; dep<=cd_height; dep++){
            std::vector<int> bfs;
            for(int s=0; s<n; s++) if(cd_dep[s] == dep) bfs.push_back(s);
            for(auto s : bfs) cd_dist[dep][s] = 0;
            for(int i=0; i<(int)bfs.size(); i++){
                int p = bfs[i];
                for(int e : adj[p]) if(cd_dep[e] > dep) if(cd_dist[dep][e] == -1){
                    bfs.push_back(e);
                    cd_dist[dep][e] = cd_dist[dep][p] + 1;
                }
            }
        }

        bt_nodes.resize(n*2-1);
        for(auto& v : bt_nodes) v.sib = v.array_idx = v.parent = -1;
        {
            std::vector<int> cdbt_root_id(n);
            for(int i=0; i<n; i++) cdbt_root_id[i] = i;
            int cdbt_node_count = n;

            std::vector<std::pair<int,int>> bt_children(n*2-1);
            for(int i=0; i<n; i++){
                bt_nodes[i].cd_depth = cd_dep[i];
                bt_nodes[i].array_idx = i;
                bt_nodes[i].size = 1;
            }

            std::priority_queue<std::pair<int,int>> Que; // ( -size, root )
            for(int ii=n-1; ii>=0; ii--){
                auto [nx,g] = cd_bfs[ii];
                Que.push(std::make_pair(-1, g));
                for(int ei=cd_bfs_adji[ii]; ei<cd_bfs_adji[ii+1]; ei++){
                    auto [enx,eg] = cd_bfs[ei];
                    Que.push(std::make_pair(-bt_nodes[cdbt_root_id[eg]].size, cdbt_root_id[eg]));
                }
                while(Que.size() >= 2){
                    auto a = Que.top().second; Que.pop();
                    auto b = Que.top().second; Que.pop();
                    int idx = cdbt_node_count;
                    bt_nodes[a].sib = b;
                    bt_nodes[b].sib = a;
                    bt_nodes[a].parent = idx;
                    bt_nodes[b].parent = idx;
                    bt_nodes[idx].cd_depth = cd_dep[g];
                    bt_nodes[idx].size = bt_nodes[a].size + bt_nodes[b].size;
                    bt_nodes[idx].exclude_cent = bt_nodes[a].exclude_cent & bt_nodes[b].exclude_cent;
                    bt_children[idx] = std::make_pair(a,b);
                    Que.push(std::make_pair(-bt_nodes[idx].size, idx));
                    cdbt_node_count++;
                }
                auto r = Que.top().second; Que.pop();
                bt_nodes[r].cd_depth--;
                cdbt_root_id[g] = r;
                bt_nodes[r].exclude_cent = 1;
            }

            bt_nodes.back().array_idx = -1;
            std::vector<int> arraysz;
            for(int idx=n*2-2; idx>=n; idx--){
                auto [a,b] = bt_children[idx];
                int array_idx = bt_nodes[idx].array_idx + 1;
                if((int)arraysz.size() == array_idx) arraysz.push_back(0);
                bt_nodes[a].array_idx = array_idx;
                bt_nodes[a].array_left = arraysz[array_idx];
                arraysz[array_idx] += bt_nodes[a].size;
                bt_nodes[b].array_idx = array_idx;
                bt_nodes[b].array_left = arraysz[array_idx];
                arraysz[array_idx] += bt_nodes[b].size;
            }

            bt_arrays.resize(arraysz.size());
            for(int i=0; i<(int)arraysz.size(); i++) bt_arrays[i].resize(arraysz[i]);
            bt_arrays_sep.resize(arraysz.size());
            for(int i=0; i<(int)arraysz.size(); i++) bt_arrays_sep[i].resize(arraysz[i] + 1);

            for(int idx=0; idx<n; idx++){
                auto& node = bt_nodes[idx];
                auto array_view = array_for_node(bt_arrays, node);
                auto sep_view = sep_for_node(bt_arrays_sep, node);
                array_view[0] = idx;
                sep_view[0] = node.array_left;
                sep_view[1] = node.array_left + 1;
            }

            std::vector<int> sep_buf(n+1, 0);
            for(int idx=n; idx<2*n-1; idx++) if(bt_nodes[idx].parent >= 0){
                auto& node = bt_nodes[idx];
                auto [a,b] = bt_children[idx];
                int dep = node.cd_depth;
                auto array_view = array_for_node(bt_arrays, node);
                auto sep_view = sep_for_node(bt_arrays_sep, node);
                int ex = node.exclude_cent;
                for(int i=0; i<=node.size; i++) sep_buf[i] = 0;
                for(int p : array_for_node(bt_arrays, bt_nodes[a])) sep_buf[cd_dist[dep][p] - ex]++;
                for(int p : array_for_node(bt_arrays, bt_nodes[b])) sep_buf[cd_dist[dep][p] - ex]++;
                for(int i=0; i<node.size; i++) sep_buf[i+1] += sep_buf[i];
                for(int p : array_for_node(bt_arrays, bt_nodes[a])) array_view[--sep_buf[cd_dist[dep][p] - ex]] = p;
                for(int p : array_for_node(bt_arrays, bt_nodes[b])) array_view[--sep_buf[cd_dist[dep][p] - ex]] = p;
                for(int i=0; i<=node.size; i++) sep_view[i] = sep_buf[i] + node.array_left;
            }
        }
        
        update_points.resize(n);
        for(int i=0; i<n; i++) update_points[i].resize(bt_nodes[i].array_idx + 1);
        for(int i=0; i<(int)bt_arrays.size(); i++){
            for(int j=0; j<(int)bt_arrays[i].size(); j++){
                update_points[bt_arrays[i][j]][i] = { i, j };
            }
        }
    }
    
    int get_array_count() const { return bt_arrays.size(); }
    const std::vector<int>& get_array(int id) const { return bt_arrays[id]; }
    const std::vector<UpdatePoint>& get_update_points(int vtx) const { return update_points[vtx]; }

    std::vector<QueryRange> get_query_range(int from, int distl, int distr){
        int p = from;
        std::vector<QueryRange> res;
        if(distl <= 0 && 0 < distr){
            res.push_back({
                bt_nodes[p].array_idx,
                bt_nodes[p].array_left,
                bt_nodes[p].array_left + 1
            });
        }
        while(bt_nodes[p].parent != -1){
            auto& sibnode = bt_nodes[bt_nodes[p].sib];
            int d = cd_dist[sibnode.cd_depth][from];
            auto tmp = get_one_node_range(sibnode, distl-d, distr-d);
            if(tmp.l < tmp.r) res.push_back(tmp);
            p = bt_nodes[p].parent;
        }
        return res;
    }
};

} // namespace nachia
