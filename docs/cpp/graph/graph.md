# グラフの辺リスト

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/graph/graph.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/graph.hpp)

## 主な機能

グラフの辺のリストを管理する。有向グラフであるか無向グラフであるかは構築時に設定できるほか、隣接リスト表現に変換する際にも指定できる。

頂点数を $n$ 、辺数を $m$ とする。

各辺には $0$ から $m-1$ の番号が振られている。

## Graph

### struct Edge

```c++
    struct Edge{
        int from, to;
        void reverse(){ std::swap(from, to); }
    };
```

辺の両端点を表す。

### (コンストラクタ)

```c++
Graph(int n = 0, bool undirected = false, int m = 0); // (1)
Graph(int n, const std::vector<std::pair<int, int>>& edges, bool undirected = false); // (2)
```

$n$ は頂点数である。 `undirected` には、構築するグラフが有向グラフなら `true` 、有向グラフなら `false` 与えること。

- $0 \leq n \leq 10^8$
- $0 \leq m \leq 10^8$

(1)

- $n$ 頂点 $m$ 辺であるとして構築する。ただし、辺の内容は未初期化となる。

(2)

- 辺 $i$ は `edges[i].first` から `edges[i].second` までを結ぶものとしてグラフを構築する。

### 諸 getter

```c++
int numVertices() const noexcept;
int numEdges() const noexcept;
Edge& operator[](int ei) noexcept;
const Edge& operator[](int ei) const noexcept;
Edge& at(int ei);
const Edge& at(int ei) const;
auto begin();
auto end();
auto begin() const;
auto end() const;
bool isUndirected() const noexcept;
```

`Edge` の配列として機能する。

### addEdge

```c++
int addEdge(int from, int to);
```

辺を追加し、その辺の番号を返す。

### reverseEdges

```c++
void reverseEdges() noexcept;
```

すべての辺の向きを反転する。

### contract

```c++
void contract(int newV, const std::vector<int>& mapping);
```

- $n=\text{mapping.size()}$
- $0\leq\text{mapping}[i]\lt \text{newV}$

縮約前の頂点 $v$ が縮約後の頂点 $\text{mapping}[i]$ に対応するようにグラフを縮約する。

### induce

```c++
std::vector<Graph> induce(int num, const std::vector<int>& mapping) const;
```

- $n=\text{mapping.size()}$
- $-1\leq\text{mapping}[i]\lt \text{num}$

グラフの頂点集合を $\text{num}$ 個に分割し、各頂点集合の誘導部分グラフを得る。 $-1$ を設定した頂点は無視される。

### getEdgeIndexArray

```c++
CsrArray<int> getEdgeIndexArray(bool undirected) const;
CsrArray<int> getEdgeIndexArray() const;
```

各頂点 $v$ について、頂点 $v$ が始点であるような辺の番号のリストを取得する。

引数 `undirected` でこの関数の動作における有向・無向を設定できる。

* `undirected == false` なら、辺番号 $i$ ( $0\leq i \lt m$ ) は返り値の配列中に $1$ 回ずつ現れる。
* `undirected == true` なら、辺番号 $i$ ( $0\leq i \lt m$ ) は返り値の配列中に $2$ 回ずつ現れる。

### getAdjacencyArray

```c++
CsrArray<int> getAdjacencyArray(bool undirected) const;
CsrArray<int> getAdjacencyArray() const;
```

各頂点 $v$ について、頂点 $v$ が始点であるような辺の終点のリストを取得する。

引数 `undirected` でこの関数の動作における有向・無向を設定できる。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
