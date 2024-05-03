# Incremental Forest

[C++ 用ライブラリ一覧に戻る](../index.md)

[nachia/tree/incremental-forest.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/tree/incremental-forest.hpp)

## 主な機能

森（グラフ）を管理する。頂点の追加と辺の追加に対応する。

各連結成分に根を $1$ つ決めて管理する。

## struct IncrementalForest

### コンストラクタ

```c++
IncrementalForest(int n = 0);
```

- 頂点数 $n$ : $1 \leq n \leq 1\times 10^8$
- $O(n)$ 時間

辺を持たない $n$ 頂点のグラフで初期化する。頂点番号は $0$ から $n-1$ までの整数である。

### addNode

```c++
int addNode();
```

- 操作後の頂点数 $n$ : $1 \leq n \leq 1\times 10^8$
- 償却 $O(1)$ 時間

頂点を追加し、新しい頂点の番号を返す。

### addEdge

```c++
int addEdge(int u, int v);
```

- $0\leq u \lt n$
- $0\leq v \lt n$
- 償却 $O(1)$ 時間

頂点 $u$ , $v$ 間に辺を追加し、新しい辺の番号を返す。

### 諸 getter

```c++
int numVertices();
int rootOf(int u);
bool areConnected(int u, int v);
int componentSize(int u);
int parentOf(int u);
int parentEdgeOf(int u);
int depth(int u);
```

* `numVertices` : 頂点数を返す。 $O(1)$ 時間。
* `rootOf` : 頂点 $u$ を含む連結成分の根を返す。 $O(\log n)$ 時間。
* `areConnected` : 頂点 $u$ と頂点 $v$ が同じ連結成分に属するなら `true` 。 $O(\log n)$ 時間。
* `componentSize` : 頂点 $u$ を含む連結成分の頂点数を返す。 $O(\log n)$ 時間。
* `parentOf` : 頂点 $u$ の親の頂点番号、なければ $-1$ を返す。 $O(1)$ 時間。
* `parentEdgeOf` : 頂点 $u$ とその親を結ぶ辺の番号、なければ $-1$ を返す。 $O(1)$ 時間。
* `depth` : 頂点 $u$ 深さを返す。 $O(1)$ 時間。

### lca

```c++
int lca(int u, int v);
```

- $0 \leq u \lt n$
- $0 \leq v \lt n$
- $O(\log n)$ 時間

$2$ 頂点 $u$ , $v$ の Lowest Common Ancestor を返す。

### dist

```c++
int dist(int x, int y);
```

- $0 \leq x, y \lt n$
- $O(\log n)$ 時間

$2$ 頂点 $x$ , $y$ 間の距離を返す。

### median

```c++
int median(int x, int y, int z);
```

- $0 \leq x,y,z \lt n$
- $O(\log n)$ 時間

頂点・辺の構造はそのままで根を頂点 $x$ に変更したときの $\text{LCA}(y,z)$ を返す。

$\text{median}(x,y,z)$ の性質として、 $x,y,z$ の順番をどのように入れ替えても結果は変わらない。

### la

```c++
int la(int u, int d);             // (1)
int la(int from, int to, int d);  // (2)
```

- $0 \leq u \lt n$
- $0 \leq \text{from},\text{to} \lt n$
- $0 \leq d$
- $O(\log n)$ 時間

(1)

頂点 $u$ の祖先であって深さ $d$ の頂点の番号、ただし存在しなければ $-1$ を返す。

(2)

$0 \leq d \leq \text{dist(from,to)}$ のとき、 $\text{from}$ から $\text{to}$ へ向かう単純パスにおいて、 $\text{from}$ から距離 $d$ の位置にある頂点を返す。それ以外のとき、 $-1$ を返す。

### children

```c++
ChildrenIterRange children(int v);
```

- $1 \leq v \lt n$

次のように呼び出すことで、 $v$ の子が列挙される。

```c++
for(int w : forest.children(v)){
    // do with w
}
```

## 参考

* https://twitter.com/kude_coder/status/1781708815517569192
* [codeforces blog "Binary Lifting, No Memory Wasted" (By Urbanowicz)](https://codeforces.com/blog/entry/74847)

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
