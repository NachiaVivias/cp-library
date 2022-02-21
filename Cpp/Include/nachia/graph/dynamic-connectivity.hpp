#pragma once



#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>


namespace nachia{

namespace dycon_internal{

template<
    class S,
    class F,
    S op(S l, S r),
    S e(),
    void reverseprod(S& x),
    S mapping(F f, S x),
    F composition(F f, F x),
    F id()
>
struct SplayTreeByIdx{
    static SplayTreeByIdx *NIL;

    using MyType = SplayTreeByIdx;

    MyType *l = nullptr;
    MyType *r = nullptr;
    MyType *p = nullptr;
    S a = e();
    S mprod = e();
    F f = id();
    bool propagated = true;
    int rev = 0;

    SplayTreeByIdx(){
    }

    void prepareDown(){
        if(!propagated){
            if(l != NIL){
                l->a = mapping(f, l->a);
                l->mprod = mapping(f, l->mprod);
                l->f = composition(f, l->f);
                l->propagated = false;
            }
            if(r != NIL){
                r->a = mapping(f, r->a);
                r->mprod = mapping(f, r->mprod);
                r->f = composition(f, r->f);
                r->propagated = false;
            }
            f = id();
            propagated = true;
        }
        if(rev){
            ::std::swap(l, r);
            if(l != NIL) l->rev ^= 1;
            if(r != NIL) r->rev ^= 1;
            rev = 0;
        }
    }
    void prepareUp(){
        mprod = op(op(l->mprod, a), r->mprod);
    }
    MyType*& parentchild(){
        if(p == NIL) return NIL;
        if(p->l == this) return p->l;
        else return p->r;
    }
    void rotL(){
        auto t = p;
        if(t->p != NIL) t->parentchild() = this;
        p = t->p;
        t->p = this;
        if(l != NIL) l->p = t;
        t->r = l;
        l = t;
    }
    void rotR(){
        auto t = p;
        if(t->p != NIL) t->parentchild() = this;
        p = t->p;
        t->p = this;
        if(r != NIL) r->p = t;
        t->l = r;
        r = t;
    }
    void splay(){
        prepareDown();
        while(p != NIL){
            auto pc = p;
            auto ppc = pc->p;
            if(ppc != NIL) ppc->prepareDown();
            if(pc != NIL) pc->prepareDown();
            prepareDown();
            if(pc->l == this){
                if(ppc == NIL){ rotR(); }
                else if(ppc->l == pc){ pc->rotR(); rotR(); }
                else if(ppc->r == pc){ rotR(); rotL(); }
            }
            else{
                if(ppc == NIL){ rotL(); }
                else if(ppc->r == pc){ pc->rotL(); rotL(); }
                else if(ppc->l == pc){ rotL(); rotR(); }
            }
            if(ppc != NIL) ppc->prepareUp();
            if(pc != NIL) pc->prepareUp();
        }
        prepareUp();
    }
    static MyType* get_new_node(S a){
        MyType* nx = new MyType(*get_nil());
        nx->a = nx->mprod = a;
        return nx;
    }
    void reverse(){
        if(!is_root()) splay();
        rev ^= 1;
        prepareDown();
    }
    void apply(F ff){
        if(!is_root()) splay();
        a = mapping(ff, a);
        mprod = mapping(ff, mprod);
        f = composition(ff, f);
        propagated = false;
        prepareDown();
    }
    S prod(){
        if(!is_root()) splay();
        return mprod;
    }

    static MyType* get_nil(){
        if(NIL) return NIL;
        NIL = new MyType();
        NIL->l = NIL->r = NIL->p = NIL;
        return NIL;
    }

    bool is_nil(){ return this == NIL; }
    bool is_root(){ return p->is_nil(); }

    MyType* front(){
        auto c = this;
        if(!c->is_root()) c->splay();
        prepareDown();
        while(!c->l->is_nil()){
            c->prepareDown();
            c = c->l;
        }
        c->splay();
        return c;
    }

    static MyType* merge(MyType* R1, MyType* R2){
        if(!R1->is_root()) R1->splay();
        if(!R2->is_root()) R2->splay();
        if(R1 == NIL) return R2;
        if(R2 == NIL) return R1;
        R2 = R2->front();
        R2->l = R1;
        R1->p = R2;
        R2->prepareUp();
        return R2;
    }
    static ::std::pair<MyType*, MyType*> split_l(MyType *R){
        if(!R->is_root()) R->splay();
        MyType* Rl = R->l;
        Rl->p = NIL;
        R->l = NIL;
        R->prepareUp();
        return ::std::make_pair(Rl, R);
    }
    static ::std::pair<MyType*, MyType*> split_r(MyType *R){
        if(!R->is_root()) R->splay();
        MyType* Rr = R->r;
        Rr->p = NIL;
        R->r = NIL;
        R->prepareUp();
        return ::std::make_pair(R, Rr);
    }

    void dump2(){
        if(is_nil()) return;
        l->dump2();
        ::std::cout << "(" << a.edgeidx.first << "," << a.edgeidx.second << ")";
        r->dump2();
    }
    void dump(){
        auto p = this;
        while(!p->is_root()) p = p->p;
        p->dump2();
        ::std::cout << ::std::endl;
    }
};

template<
    class S,
    class F,
    S op(S l, S r),
    S e(),
    void reverseprod(S& x),
    S mapping(F f, S x),
    F composition(F f, F x),
    F id()
>
    SplayTreeByIdx<S,F,op,e,reverseprod,mapping,composition,id> *
    SplayTreeByIdx<S,F,op,e,reverseprod,mapping,composition,id>
    ::NIL
    = get_nil();

} // namespace dycon_internal

} // namespace nachia

#include <unordered_map>

namespace nachia {

namespace dycon_internal {

template<
    class S,
    class F,
    S op(S l, S r),
    S e(),
    S newnode(),
    void reverseprod(S& x),
    S mapping(F f, S x),
    F composition(F f, F x),
    F id()
>
struct EulerTourTree{
    struct new_S {
        S internal_S;
        ::std::pair<int,int> edgeidx;
    };
    static new_S new_op(new_S l, new_S r){ return { op(l.internal_S, r.internal_S), {-1,-1} }; }
    static new_S new_e(){ return { e(), {-1,-1} }; }
    static void new_reverseprod(new_S& x){ reverseprod(x.internal_S); }
    static new_S new_mapping(F f, new_S x){ return { mapping(f, x.internal_S), x.edgeidx }; }

    //using SplayNode = SplayTreeByIdx<S, F, op, e, reverseprod, mapping, composition, id>;
    using SplayNode = SplayTreeByIdx<new_S, F, new_op, new_e, new_reverseprod, new_mapping, composition, id>;
    ::std::vector<SplayNode*> nodes;
    
    ::std::unordered_map<unsigned long long, SplayNode*> node_searcher;

    static unsigned long long edgeid_compress(int u, int v){
        return ((unsigned long long)u << 32) | v;
    }

    int num_nodes(){ return nodes.size(); }

    void delete_node(int u, int v){
        auto searcher_itr = node_searcher.find(edgeid_compress(u, v));
        delete(searcher_itr->second);
        node_searcher.erase(searcher_itr);
    }

    EulerTourTree(int n = 0){
        nodes.assign(n, SplayNode::get_nil());
    }

    ::std::pair<SplayNode*, SplayNode*> create_edge(int u, int v, S x){
        auto edgeuv = SplayNode::get_new_node({ x, {u,v} });
        node_searcher.insert_or_assign(edgeid_compress(u, v), edgeuv);
        auto edgevu = SplayNode::get_new_node({ x, {v,u} });
        node_searcher.insert_or_assign(edgeid_compress(v, u), edgevu);
        return ::std::make_pair(edgeuv, edgevu);
    }

    SplayNode* expose(int v){
        if(nodes[v]->is_nil()){
            nodes[v] = SplayNode::get_new_node({ newnode(), {v,v} });
            node_searcher.insert_or_assign(edgeid_compress(v,v), nodes[v]);
        }
        nodes[v]->splay();
        return nodes[v];
    }

    SplayNode* evert(int v){
        auto Hv = expose(v);
        auto [l,r] = SplayNode::split_l(Hv);
        Hv = SplayNode::merge(r, l);
        return Hv;
    }
    // u will be the new root
    SplayNode* link(int u, int v, S x){
        auto Hu = evert(u);
        auto Hv = evert(v);
        if(!Hu->is_root()) return Hv;
        auto [Huv, Hvu] = create_edge(u, v, x);
        return SplayNode::merge(SplayNode::merge(Hu, Huv), SplayNode::merge(Hv, Hvu));
    }

    SplayNode* find_ettnode(int u, int v){
        auto i = node_searcher.find(edgeid_compress(u, v));
        if(i == node_searcher.end()) return SplayNode::get_nil();
        return i->second;
    }

    ::std::pair<SplayNode*, SplayNode*> cut(int u, int v){
        SplayNode* Hvu = find_ettnode(v, u);
        SplayNode* Huv = find_ettnode(u, v);
        evert(u);
        Huv->splay();
        auto [Hu, R2] = SplayNode::split_l(Huv);
        Huv->splay();
        [[maybe_unused]] auto [edgeuv, R3] = SplayNode::split_r(Huv);
        Hvu->splay();
        auto [Hv, R4] = SplayNode::split_l(Hvu);
        Hvu->splay();
        [[maybe_unused]] auto [edgevu, Hu2] = SplayNode::split_r(Hvu);
        delete_node(u, v);
        delete_node(v, u);
        return ::std::make_pair(SplayNode::merge(Hu, Hu2), Hv);
    }

    S get(int u){
        return expose(u)->a.internal_S;
    }
    S get(int u, int v){
        auto Huv = find_ettnode(u, v);
        Huv->splay();
        return Huv->a.internal_S;
    }
    void set(int u, S x){
        auto Hu = expose(u);
        Hu->a.internal_S = x;
        Hu->prepareUp();
    }
    void set(int u, int v, S x){
        auto Huv = find_ettnode(u, v);
        Huv->splay();
        Huv->a.internal_S = x;
        Huv->prepareUp();
    }

    S component_prod(int u){
        return expose(u)->prod(u).internal_S;
    }

    bool is_connected(int u, int v){
        if(nodes[u]->is_nil()) return false;
        if(nodes[v]->is_nil()) return false;
        if(u == v) return true;
        auto Hu = expose(u);
        expose(v);
        return !(Hu->is_root());
    }
};

namespace DyConETT{
    using u32 = unsigned int;
    using u64 = unsigned long long;
    const u32 MOD = 998244353;

    struct S{ ::std::pair<int, int> justrank; u32 z; int edgemark; };
    struct F{  };
    S op(S l, S r){ return { ::std::max(l.justrank, r.justrank), l.z + r.z, ::std::max(l.edgemark, r.edgemark) }; }
    S e(){ return { { -1, -1 }, 0, -1 }; }
    S newnode(){ return { { -1, -1 }, 1, -1 }; }
    void reverseprod(S&) {}
    S mapping(F , S x){ return x; }
    F composition(F , F x){ return x; }
    F id(){ return {}; }
    using ETT = ::nachia::dycon_internal::EulerTourTree<S, F, op, e, newnode, reverseprod, mapping, composition, id>;
}

} // namespace dycon_internal

} // namespace nachia



#include <unordered_set>
#include <unordered_map>
#include <iostream>

namespace nachia {

struct OnlineFullyDynamicConnectivityBySplayEtt{
private:
    int n = 0;
    int RanksCount = 0;
    ::std::vector<dycon_internal::DyConETT::ETT> etts;
    ::std::vector<::std::vector<::std::unordered_set<int>>> edges;

    using SplayNode = typename dycon_internal::DyConETT::ETT::SplayNode;

    void add_ranked_edge(int k, int u, int v){
        if(edges[k][u].empty()) etts[k].set(u, {{-1,-1},1,u});
        if(edges[k][v].empty()) etts[k].set(v, {{-1,-1},1,v});
        edges[k][u].insert(v);
        edges[k][v].insert(u);
    }
    void erase_ranked_edge(int k, int u, int v){
        edges[k][u].erase(v);
        edges[k][v].erase(u);
        if(edges[k][u].empty()) etts[k].set(u, {{-1,-1},1,-1});
        if(edges[k][v].empty()) etts[k].set(v, {{-1,-1},1,-1});
    }

    ::std::pair<int,int> replace(int k, int u, int v){
        if(k >= RanksCount) return {-1,-1};
        if(!etts[k].is_connected(u, v)) return {-1,-1};
        auto [Hu, Hv] = etts[k].cut(u, v);
        auto [s,t] = replace(k+1,u,v);
        if(s != -1){
            etts[k].link(s, t, {{-1,-1},0,-1});
            return {s,t};
        }
        if(Hu->prod().internal_S.z > Hv->prod().internal_S.z){
            ::std::swap(u, v);
            ::std::swap(Hu, Hv);
        }
        while(Hu->prod().internal_S.justrank.first != -1){
            auto [eu, ev] = Hu->prod().internal_S.justrank;
            etts[k].set(eu, ev, {{-1,-1},0,-1});
            etts[k].set(ev, eu, {{-1,-1},0,-1});
            etts[k+1].link(eu, ev, {{eu,ev},0,-1});
            Hu->splay();
        }
        while(Hu->prod().internal_S.edgemark != -1){
            int x = Hu->prod().internal_S.edgemark;
            while(!edges[k][x].empty()){
                int y = *edges[k][x].begin();
                if(etts[k].is_connected(x, y)){
                    erase_ranked_edge(k, x, y);
                    add_ranked_edge(k+1, x, y);
                    continue;
                }
                erase_ranked_edge(k, x, y);
                etts[k].link(x, y, {{x,y},0,-1});
                return {x,y};
            }
            Hu->splay();
        }
        return {-1,-1};
    }
public:

    OnlineFullyDynamicConnectivityBySplayEtt(int new_n){
        n = new_n;
        RanksCount = 0; { int vn = n; while(vn){ RanksCount++; vn /= 2; } }
        etts.resize(RanksCount);
        for(auto& ett : etts){
            ett = dycon_internal::DyConETT::ETT(n);
        }
        edges.resize(RanksCount);
        for(auto& a : edges) a.resize(n);
    }

    struct ForestCutQuery{
        ::std::pair<int, int> forest_cut;
        ::std::pair<int, int> forest_link;
    };

    ::std::pair<int, int> link(int u, int v){
        if(etts[0].is_connected(u, v)){
            add_ranked_edge(0, u, v);
            return {-1,-1};
        }
        etts[0].link(u, v, { {u,v}, 0, -1 });
        return {u,v};
    }
    
    ForestCutQuery cut(int u, int v){
        if(etts[0].find_ettnode(u, v)->is_nil()){
            for(int k=0; k<RanksCount; k++){
                if(edges[k][u].find(v) != edges[k][u].end()){
                    erase_ranked_edge(k, u, v);
                    break;
                }
            }
            return { {-1,-1}, {-1,-1} };
        }
        return { {u,v}, replace(0, u, v) };
    }

    bool is_connected(int u, int v){
        if(u == v) return true;
        return etts[0].is_connected(u, v);
    }
};


} // namespace nachia

