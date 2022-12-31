#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum"
#include "../../../Include/nachia/graph/dynamic-connectivity.hpp"
#include "../../../Include/nachia/misc/fastio.hpp"
#include <vector>
#include <algorithm>
#include <cassert>


namespace nachia {

struct LinkCutTree {
    struct S{
        unsigned long long x = 0;
        S operator+(const S& r) const { return { x+r.x }; }
        S operator-(const S& r) const { return { x-r.x }; }
        void reverse(){  }
    };

    struct Node {
        Node* l = 0, * r = 0, * p = 0;
        S a;
        S prod;
        // lazy & 1 : reverse
        // lazy & 2 : deta
        int lazy = 0;
        
        void prepareDown() {
            if (lazy & 1) {
                std::swap(l, r);
                if (l) { l->lazy ^= 1; l->prod.reverse(); }
                if (r) { r->lazy ^= 1; r->prod.reverse(); }
            }
            lazy = 0;
        }
        Node** p_parentchild() {
            if(!p) return nullptr;
            if(p->l == this) return &p->l;
            else if(p->r == this) return &p->r;
            return nullptr;
        }
        void rotL() {
            Node* t = p;
            Node** parentchild_p = t->p_parentchild();
            if(parentchild_p){ *parentchild_p = this; }
            t->prod = t->prod - prod;
            prod = prod + t->prod;
            if(l) t->prod = t->prod + l->prod;
            p = t->p;
            t->p = this;
            t->r = l;
            if(l) l->p = t;
            l = t;
        }
        void rotR() {
            Node* t = p;
            Node** parentchild_p = t->p_parentchild();
            if(parentchild_p){ *parentchild_p = this; }
            t->prod = t->prod - prod;
            prod = prod + t->prod;
            if(r) t->prod = t->prod + r->prod;
            p = t->p;
            t->p = this;
            t->l = r;
            if(r) r->p = t;
            r = t;
        }
    };

    std::vector<Node> A;
    LinkCutTree(int n = 0) {
        A.resize(n);
    }
    LinkCutTree(const std::vector<S>& a) : LinkCutTree(a.size()) {
        for (int i = 0; i < (int)a.size(); i++) A[i].prod = A[i].a = a[i];
    }
    Node* at(int idx) {
        return &A[idx];
    }
    void splay(Node* c) {
        c->prepareDown();
        while(true) {
            Node* p = c->p;
            if(!p) break;
            Node* pp = p->p;
            if(pp) pp->prepareDown();
            p->prepareDown();
            c->prepareDown();
            if(p->l == c){
                if(!pp){ c->rotR(); }
                else if(pp->l == p){ p->rotR(); c->rotR(); }
                else if(pp->r == p){ c->rotR(); c->rotL(); }
                else{ c->rotR(); }
            }
            else if(p->r == c){
                if(!pp){ c->rotL(); }
                else if(pp->r == p){ p->rotL(); c->rotL(); }
                else if(pp->l == p){ c->rotL(); c->rotR(); }
                else{ c->rotL(); }
            }
            else break;
        }
    }
    void expose(int c) {
        auto Hc = at(c);
        auto p = Hc;
        while(p){ splay(p); p = p->p; }
        p = Hc;
        while(p->p){ p->p->r = p; p = p->p; }
        splay(Hc);
        Hc->r = nullptr;
    }
    void evert(int c) {
        auto Hc = at(c);
        expose(c);
        Hc->lazy ^= 1;
        Hc->prod.reverse();
        Hc->prepareDown();
    }
    void link(int c, int r) {
        if(c == r) return;
        auto Hc = at(c);
        auto Hr = at(r);
        evert(c);
        evert(r);
        if(Hc->p) return;
        Hr->prod = Hr->prod + Hc->prod;
        Hc->p = Hr;
    }
    void cut(int c) {
        auto Hc = at(c);
        expose(c);
        if(!Hc->l) return;
        Hc->prod = Hc->prod - Hc->l->prod;
        Hc->l->p = nullptr;
        Hc->l = nullptr;
    }
    S prod(int c) {
        auto Hc = at(c);
        expose(c);
        return Hc->prod;
    }
    S get(int c) {
        auto Hc = at(c);
        expose(c);
        return Hc->a;
    }
    void set(int c, S x) {
        auto Hc = at(c);
        expose(c);
        Hc->prod = Hc->prod - Hc->a + x;
        Hc->a = x;
    }
};

}


namespace LCT{
    using u64 = unsigned long long;

    struct S{
        u64 x = 0;
        S operator+(const S& r) const { return { x+r.x }; }
        void reverse(){  }
    };
    using LCT = nachia::LinkCutTree;
}

int main(){
    using nachia::cin;
    using nachia::cout;
    int N = cin.nextU32();
    int Q = cin.nextU32();

    nachia::OnlineFullyDynamicConnectivityBySplayEtt dycon(N);
    LCT::LCT component_sum(N);

    for(int i=0; i<N; i++){
        int a = cin.nextU32();
        component_sum.set(i, { (LCT::u64)a });
    }

    for(int i=0; i<Q; i++){
        int t = cin.nextU32();
        if(t == 0){
            int u,v; cin >> u >> v;
            auto forestlink = dycon.link(u, v);
            if(forestlink.first != -1){
                component_sum.link(forestlink.first, forestlink.second);
            }
        }
        else if(t == 1){
            int u = cin.nextU32();
            int v = cin.nextU32();
            auto [forestcut, forestlink] = dycon.cut(u, v);
            if(forestcut.first != -1){
                component_sum.evert(forestcut.first);
                component_sum.cut(forestcut.second);
            }
            if(forestlink.first != -1){
                component_sum.link(forestlink.first, forestlink.second);
            }
        }
        else if(t == 2){
            int v = cin.nextU32();
            int x = cin.nextU32();
            component_sum.set(v, { component_sum.get(v).x + x });
        }
        else if(t == 3){
            int v = cin.nextU32();
            auto ans = component_sum.prod(v).x;
            cout << ans << '\n';
        }
    }
    return 0;
}
