# Heavy-Light Decomposition

[C++ 用ライブラリ一覧に戻る](../../)

**注意：このライブラリの一部は verify されていない。**

## 主な機能

$N$ 頂点の静的な根付き無向木 $T$ がある。頂点には番号(0-based) が振られている。

- $2$ 頂点 $x,y$ の Lowest Common Ancestor を $\mathrm{LCA}(x,y)$ と表す。
- $2$ 頂点 $x,y$ 間の距離（各辺の長さは $1$ とする） を $\mathrm{dist}(x,y)$ と表す。

$T$ に対して、以下の操作を行う。前処理の計算量は $O(N)$ である。

- [`lca(x,y)`](#lca) ： $\mathrm{LCA}(x,y)$ を求める。（ $O(\log N)$ 時間）
- [`path(r,c)`](#path) ： $r$ とその子孫 $c$ について、 $r,c$ 間の単純パス上の頂点列を $O(\log N)$ 個の区間で表す。（ $O(\log N)$ 時間）
- [`subtree(r)`](#subtree) ：頂点 $r$ の部分木が含む頂点の集合を $1$ つの区間で表す。（ $O(1)$ 時間）
- [`dist(x,y)`](#dist) ： $\mathrm{dist}(x,y)$ を求める。（ $O(\log N)$ 時間）
- [`median(x,y,z)`](#median) : 頂点・辺の構造はそのままで根を頂点 $x$ に変更したときの $\mathrm{LCA}(y,z)$ を求める。（ $O(\log N)$ 時間）
- [`la(from,to,d)`](#la) : $\mathrm{from}$ から $\mathrm{to}$ に向かう単純パスにおいて、 $\mathrm{from}$ から距離 $d$ の頂点を求める。（ $O(\log N)$ 時間）

## class HLD

### コンストラクタ

```c++
HLD(const vector<vector<int>>& E);
```

- $E\mathrm{.size()} = N$
- $N \leq 5\times 10^5$
- $E[u]$ は頂点 $u$ に隣接する頂点のリストである。根付き木の親から子へ向かう辺は含まれていなければいけないが、親へ向かう辺は含まなくてもよい。
- $O(N)$ 時間

頂点 $0$ を根として前処理を行う。

### idxs

```c++
const vector<int>& idxs() const;
```

- $O(1)$ 時間

頂点を扱いやすい順序に並べ替えた後の位置を取得する。頂点 $u$ に振られた番号は `idxs()[u]` で得られる。

### depth

```c++
int depth(int p) const;
```

- $0 \leq p \lt N$
- $O(1)$ 時間

頂点 $p$ の深さ（つまり、根と頂点 $p$ との距離）を返す。

### lca

```c++
int lca(int x, int y) const;
```

- $0 \leq x,y \lt N$
- $O(\log N)$ 時間

$\mathrm{LCA}(x,y)$ を返す。

### dist

```c++
int dist(int x, int y) const;
```

- $0 \leq x,y \lt N$
- $O(\log N)$ 時間

$\mathrm{dist}(x,y)$ を返す。

### path

```c++
vector<pair<int,int>> path(int r, int c, bool include_root = true, bool reverse_path = false) const;
```

- $0 \leq r,c \lt N$
- $r=c$ または、頂点 $r$ は頂点 $c$ の祖先である。
- $O(\log N)$ 時間

$r$ から $c$ へ向かう単純パスをいくつかの**半開**区間 $[l_0,r_0),[l_1,r_1),\cdots ,[l_{k-1},r_{k-1})$ で表し、ペアの列 $ \left( (l_0,r_0),(l_1,r_1) \ldots (l_{k-1},r_{k-1}) \right) $ を返す。

パスに含まれる頂点の列を $(r=I_0,I_1,I_2, \cdots ,I_{L-1}=c)$ 、と表したとき、 $2$ つの数列

- $S_1 = (\mathrm{idxs()}[I_0],\mathrm{idxs()}[I_1], \cdots ,\mathrm{idxs()}[I_{L-1}])$
- $S_2 = (l_0,l_0+1,l_0+2,\cdots,r_0-1,l_1,\cdots,r_1-1,l_2,\cdots,r_{k-1}-1)$

は一致する。

`include_root` が `false` のとき、 $r$ から $c$ へ向かう単純パスは $r$ を除いたものとする。
`reverse_path` が `true` のとき、返す直前に次の手順を実行する。

1. 返す配列を reverse する。
2. 各ペア $(l_i,r_i)$ を $(N-r_i,N-l_i)$ に変更する。

### subtree

```c++
pair<int,int> subtree(int r) const;
```

- $0 \leq r \lt N$
- $O(1)$ 時間

頂点 $r$ の部分木を**半開**区間 $[l_0,r_0)$ で表し、ペア $l_1,r_1$ を返す。

頂点 $r$ の部分木に含まれる頂点をある DFS の行きがけ順に並べた列を $(r=I_0,I_1, \cdots ,I_{L-1})$ としたとき、 $2$ つの数列

- $S_1 = (\mathrm{idxs()}[I_0],\mathrm{idxs()}[I_1], \cdots ,\mathrm{idxs()}[I_{L-1}])$
- $S_2 = ( l_0,l_0+1,l_0+2,\cdots,r_0-1 )$

は一致する。

### median

```c++
int median(int x, int y, int z) const;
```

- $0 \leq x,y,z \lt N$
- $O(\log N)$ 時間

頂点・辺の構造はそのままで根を頂点 $x$ に変更したときの $\mathrm{LCA}(y,z)$ を返す。

$\mathrm{median}(x,y,z)$ の性質として、 $x,y,z$ の順番をどのように入れ替えても結果は変わらない。

### la (not verified)

```c++
int la(int from, int to, int d) const;
```

- $0 \leq \mathrm{from},\mathrm{to} \lt N$
- $0 \leq d$
- $O(\log N)$ 時間

$0 \leq d \leq \mathrm{dist}(\mathrm{from},\mathrm{to})$ のとき、 $\mathrm{from}$ から $\mathrm{to}$ へ向かう単純パスにおいて、 $\mathrm{from}$ から距離 $d$ の位置にある頂点を返す。

$\mathrm{dist}(\mathrm{from},\mathrm{to}) \lt d$ のとき、 $-1$ を返す。

## 参考

- [単位重み木のユーティリティに関する @noshi91 によるツイート](https://twitter.com/noshi91/status/1253703019977256961)
- [median の実装に関する @noshi91 によるツイート](https://twitter.com/noshi91/status/1336562191080726528)


---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>