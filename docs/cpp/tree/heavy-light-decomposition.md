# Heavy-Light Decomposition

[C++ 用ライブラリ一覧に戻る](../index.md)

[nachia/tree/heavy-light-decomposition.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/tree/heavy-light-decomposition.hpp)

## 主な機能

$n$ 頂点の静的な根付き無向木 $T$ がある。頂点には番号(0-based) が振られている。

- $2$ 頂点 $x,y$ の Lowest Common Ancestor を $\mathrm{LCA}(x,y)$ と表す。
- $2$ 頂点 $x,y$ 間の距離（各辺の長さは $1$ とする） を $\mathrm{dist}(x,y)$ と表す。

$T$ の頂点を適切な順序に並べた列を $A=(A[0],A[1],A[2], \ldots ,A[n-1])$ とする。各要素は [`toVtx`](#toVtx) で得られる。

様々なメンバを持つ。特に、 $T$ に対して以下の計算を行う。前処理の計算量は $O(n)$ である。

- [`lca(x,y)`](#lca) ： $\text{LCA}(x,y)$ を求める。（ $O(\log n)$ 時間）
- [`path(r,c)`](#path) ： $r$ とその子孫 $c$ について、 $r,c$ 間の単純パス上の頂点列を $A$ の区間 $O(\log n)$ 個で表す。（ $O(\log n)$ 時間）
- [`subtree(r)`](#subtree) ：頂点 $r$ の部分木が含む頂点の集合を $A$ の区間で表す。（ $O(1)$ 時間）
- [`dist(x,y)`](#dist) ： $\text{dist}(x,y)$ を求める。（ $O(\log n)$ 時間）
- [`median(x,y,z)`](#median) : 頂点・辺の構造はそのままで根を頂点 $x$ に変更したときの $\text{LCA}(y,z)$ を求める。（ $O(\log n)$ 時間）
- [`la(from,to,d)`](#la) : $\text{from}$ から $\text{to}$ に向かう単純パスにおいて、 $\text{from}$ から距離 $d$ の頂点を求める。（ $O(\log n)$ 時間）

## struct HeavyLightDecomposition

### コンストラクタ

```c++
nachia::HeavyLightDecomposition(
    const Graph& tree,
    int root = 0
);

nachia::HeavyLightDecomposition(
    const CsrArray<int>& E = CsrArray<int>::Construct(1, {}),
    int root = 0
);
```

[nachia::Graph とは？](./../graph/graph.md)

[nachia::CsrArray とは？](./../array/csr-array.md)

- 頂点数 $n$ : $1 \leq n \leq 5\times 10^6$
- $0\leq\text{root}\lt n$
- $O(n)$ 時間

$\text{root}$ を根として、 heavy-light decomposition を行う。

木は隣接リストで与えてもよい。その場合、根付き木の親から子へ向かう辺は含まれていなければいけないが、親へ向かう辺は含まなくてもよい。

### toSeq

```c++
int toSeq(int vtx) const;
```

- 引数を $v$ として、 $0 \leq v \lt n$
- $O(1)$ 時間

$A[i]=v$ を満たす $i$ を返す。

### toVtx

```c++
int toVtx(int seqidx) const;
```

- 引数を $i$ として、 $0 \leq i \lt n$
- $O(1)$ 時間

$A[i]$ を返す。

### toSeq2In, toSeq2Out

```c++
int toSeq2In(int vtx) const;
int toSeq2Out(int vtx) const;
```

- 引数を $i$ として、 $0 \leq i \lt n$
- $O(1)$ 時間

`toSeq` で得られる順序と同じ順序で DFS を行いながら、各頂点で次の $2$ 回タイミングを記録したとする。

- (In) その頂点に初めて訪れたとき
- (Out) その頂点の子をすべて訪れた後、最後にその頂点を訪れたとき

これにより $2n$ 回タイミングが記録されるが、それに順に $0,1,\ldots ,2n-1$ の番号を振る。この関数では、このように付けられた番号を取得する。

### depth

```c++
int depth(int p) const;
```

- $0 \leq p \lt n$
- $O(1)$ 時間

頂点 $p$ の深さ（つまり、根と頂点 $p$ との距離）を返す。

### parentOf

```c++
int parentOf(int v) const;
```

- $0 \leq v \lt n$
- $O(1)$ 時間

頂点 $v$ の親の番号を返す。 $v$ が根の場合は $-1$ を返す。

### heavyRootOf, heavyChildOf

```c++
int heavyRootOf(int v) const;  // (1)
int heavyChildOf(int v) const; // (2)
```

- $0 \leq v \lt n$
- $O(1)$ 時間

(1) : 頂点 $v$ と同じ heavy path に含まれている頂点のうち、最も根に近い頂点を返す。

(2) : 頂点 $v$ に heavy path でつながれた子の番号を返す。存在しない場合、 $-1$ を返す。

### lca

```c++
int lca(int x, int y) const;
```

- $0 \leq x,y \lt n$
- $O(\log n)$ 時間

$\text{LCA}(x,y)$ を返す。

### dist

```c++
int dist(int x, int y) const;
```

- $0 \leq x,y \lt n$
- $O(\log n)$ 時間

$\text{dist}(x,y)$ を返す。

### path

```c++
vector<Range> path(int r, int c, bool include_root = true, bool reverse_path = false) const;
```

- $0 \leq r,c \lt n$
- $r=c$ または、頂点 $r$ は頂点 $c$ の祖先である。
- $O(\log n)$ 時間

$r$ から $c$ へ向かう単純パスをいくつかの**半開**区間 $[l _ 0,r _ 0),[l _ 1,r _ 1),\cdots ,[l _ {k-1},r _ {k-1})$ で表し、一列に並べて返す。

パスに含まれる頂点の列を $(r=I _ 0,I _ 1,I _ 2, \cdots ,I _ {L-1}=c)$ 、と表したとき、 $2$ つの数列

- $S _ 1 = (I _ 0,I _ 1, \cdots ,I _ {L-1})$
- $S _ 2 = (A[l _ 0],A[l _ 0+1],A[l _ 0+2],\cdots,A[r _ 0-1],A[l _ 1],\cdots,A[r _ 1-1],A[l _ 2],\cdots,A[r _ {k-1}-1])$

は一致する。

`include_root` が `false` のとき、 $r$ から $c$ へ向かう単純パスは $r$ を除いたものとする。
`reverse_path` が `true` のとき、返す直前に次の手順を実行する。

1. 返す配列を逆順にする。
2. 各ペア $(l _ i,r _ i)$ を $(n-r _ i,n-l _ i)$ に変更する。

$c$ から $r$ へ向かうパスを扱うときは、数列 $A$ を逆順にとり、 `reverse_path` を真にしてこの関数を利用するとよい。

`Range` は以下で定義される。

```c++
struct Range{
    int l; int r;
    int size() const { return r-l; }
    bool includes(int x) const { return l <= x && x < r; }
};
```

### subtree

```c++
Range subtree(int r) const;
```

- $0 \leq r \lt n$
- $O(1)$ 時間

頂点 $r$ の部分木を**半開**区間 $[l _ 0,r _ 0)$ で表したものを返す。

頂点 $r$ の部分木に含まれる頂点をある DFS の行きがけ順に並べた列を $(r=I _ 0,I _ 1, \cdots ,I _ {L-1})$ としたとき、 $2$ つの数列

- $S _ 1 = (I _ 0,I _ 1, \cdots ,I _ {L-1})$
- $S _ 2 = ( A[l _ 0],A[l _ 0+1],A[l _ 0+2],\cdots,A[r _ 0-1] )$

は一致する。

### median

```c++
int median(int x, int y, int z) const;
```

- $0 \leq x,y,z \lt n$
- $O(\log n)$ 時間

頂点・辺の構造はそのままで根を頂点 $x$ に変更したときの $\text{LCA}(y,z)$ を返す。

$\text{median}(x,y,z)$ の性質として、 $x,y,z$ の順番をどのように入れ替えても結果は変わらない。

### la

```c++
int la(int from, int to, int d) const;
```

- $0 \leq \text{from},\text{to} \lt n$
- $0 \leq d$
- $O(\log n)$ 時間

$0 \leq d \leq \text{dist(from,to)}$ のとき、 $\text{from}$ から $\text{to}$ へ向かう単純パスにおいて、 $\text{from}$ から距離 $d$ の位置にある頂点を返す。それ以外のとき、 $-1$ を返す。

これは、 $\text{from}$ を根としたときの Level Ancestor と同じことである。

### children

```c++
ChildrenIterRange children(int v) const;
```

- $0 \leq v \lt n$

次のように呼び出すことで、 $v$ の子が列挙される。 $1$ ステップごとに $O(1)$ 時間で返す。

```c++
for(int w : hld.children(v)){
    // do with w
}
```

## 参考

- [単位重み木のユーティリティに関する @noshi91 によるツイート](https://twitter.com/noshi91/status/1253703019977256961)
- [median の実装に関する @noshi91 によるツイート](https://twitter.com/noshi91/status/1336562191080726528)


---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
