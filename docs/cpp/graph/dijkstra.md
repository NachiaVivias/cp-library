# Dijkstra法 ( ダイクストラ法 )

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/graph/dijkstra.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/dijkstra.hpp)

## 主な機能

辺に非負の重みがついたグラフ上で、 $s$ を始点とする最短路を計算する。 $s$ から到達できる頂点すべてについて最短路長一度に求まる。

始点を複数設定した場合、それらのうちどこを始点としてもよいとして最短路を計算する。

## struct DijkstraShortestPath

### テンプレート引数

```c++
template<class Weight = long long, class Weight2 = Weight>
struct DijkstraShortestPath;
```

最短路の計算には `Weight` 型を使用する。入力のみ別の型を用いたい場合、 `Weight2` に設定する。

`Weight` 型の変数 `A` , `B` および `Weight2` 型の変数 `a` に関して、次の演算を正しく行えなければならない。

- `A + B`
- `A < B`
- `(Weight)a`

### コンストラクタ

```c++
DijkstraShortestPath(
    nachia::Graph graph,
    const std::vector<Weight2>& weight,
    const std::vector<std::pair<int, Weight>>& starting,
    const Weight Inf
)
```

メインの計算を行う。

`graph` は無向でも有向でもよい。

`weight` は各辺の重みである。

`starting` は最短路の始点となり得る頂点と、その場合の初期重みの組を集めたものである。

`Inf` は最短距離が存在しない場合または `Inf` 以上であった場合に設定される値である。

- 頂点数： $0 \leq n \leq 10^7$
- 辺数： $0 \leq m \leq 10^7$
- 始点の個数： $1 \leq k \leq 10^7$
- $\text{weight.size()}=N$
- `weight` の要素は非負
- $O((n+m+k) \log (m+k))$ 時間 （ heap として std::priority_queue を使用したときのダイクストラ法の計算量）

$G$ が無向グラフの場合、双方向に同じ重みの辺があるものとして計算する。

### distTo

```c++
Weight distTo(int v) const;
```

- $O(1)$ 時間

始点から頂点 $v$ までの最短距離を返す。

### prevEdge

```c++
int prevEdge(int v) const;
```

- $O(1)$ 時間

頂点 $v$ に到達する直前に通る辺の番号を返す。 $v$ が始点になる場合は負の値を返す。

### pathTo

```c++
std::vector<int> pathTo(int v) const
```

- $O(L)$ 時間（ $L$ は出力長）

始点から $v$ へ至る最短路を辺列で表す。

## 使用例

[Library Checker | Shorest Path](https://judge.yosupo.jp/problem/shortest_path)

```c++
#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include "nachia/graph/dijkstra.hpp"
#include "nachia/graph/graph.hpp"
#include "nachia/misc/fastio.hpp"

int main(){
    using nachia::cin, nachia::cout;

    int N, M; cin >> N >> M;
    int s, t; cin >> s >> t; // 始点 s 、終点 t

    // グラフと重みを初期化
    nachia::Graph G(N, false);
    std::vector<int> W(M);
    for(int i=0; i<M; i++){
        int u,v,c; cin >> u >> v >> c;
        G.addEdge(u, v);
        W[i] = c;
    }

    // 最短路長の上限
    long long INF = 1ll << 60;

    // グラフ、重み、始点、上限を設定してダイクストラ法を実行
    auto res = nachia::DijkstraShortestPath(G, W, {{s,0}}, INF);

    // 到達できないなら、 -1 を出力
    if(res.distTo(t) == INF){
        cout << "-1\n";
    }
    // 到達できるなら、距離とパスを出力
    else {
        auto path = res.pathTo(t);
        cout << res.distTo(t) << ' ' << path.size() << '\n';
        for(int e : path) cout << G[e].from << ' ' << G[e].to << '\n';
    }
    return 0;
}
```

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
