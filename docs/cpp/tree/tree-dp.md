# 全方位木 DP

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/tree/tree-dp.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/tree/tree-dp.hpp)

## 主な機能

ユーザーが基本操作を提供すると、プログラムは全方位木 DP によって木全体の集約を行う。

## 理論

木 $T$ に関して、 $T$ の頂点集合 $T'$ と $T$ の **根** $r$ の組 $(r,T')$ が次の条件をすべて満たすとき、その組をここでは **強クラスター** と呼ぶことにする。

- $r$ は $T'$ に含まれる。
- $T'$ はある部分木の頂点集合である。
- $T'$ の頂点であって $r$ でない頂点 $v$ と、 $T$ の頂点であって $T'$ に含まれないもの $w$ をそれぞれ任意にとったとき、 $v$ と $w$ は隣接しない。

いま、 $T$ の強クラスター $(r,T')$ に、それぞれ対応する値 $f(r,T')$ が割り当てられているとする。また、この値に対して次のような操作が許されているとする。

- `node` : $f(r,\lbrace r\rbrace )$ の値を得る。
- `rake` : $A\cap B =\lbrace r\rbrace$ で、 $f(r,A)$ と $f(r,B)$ の値がわかっているとき、 $f(r,A\cup B)$ の値を得る。
- `compress` : $u\notin T'$ であるとして、辺 $e=(u,v)$ の情報と $f(v, T')$ の値から、 $f(u, T'\cup \lbrace u\rbrace )$ の値を得る。

このとき、全方位木 DP では木の頂点数を $n$ として、操作回数を $O(n)$ に抑えて、重要な強クラスターについて $f(r,T')$ の値を得ることができる。

## クラス TreeDP

### テンプレート引数

```c++
template<class S>
class TreeDP;
```

強クラスターに対して計算される値の型を `S` として指定する。

## Inner 構造体

`Inner` 構造体は、 `TreeDP<S>` の内部に入れ子で実装される。
インスタンスはヘルパー関数から取得する。

### インスタンスの取得

```c++
// S node(int root)
// S rake(S a, S b, int root)
// S compress(S a, int edgeIndex, int newRoot)
template<
    class NodeInitializer,
    class RakeFunc,
    class CompressFunc
>
static auto Solver(
    const Graph& tree,
    NodeInitializer node,
    RakeFunc rake,
    CompressFunc compress
);
```

[nachia::Graph とは？](./../graph/graph.md)

- `S` は、集約値の型である。
- `node` は次の形式の関数として呼び出すことができる。この関数は、 $f(r,\lbrace r\rbrace )$ の値を返す。
    - `S node(int r)`
- `rake` は次の形式の関数として呼び出すことができる。この関数は、操作 `rake` を行う。
    - `S rake(S a, S b, int root)`
- `compress` は次の形式の関数として呼び出すことができる。この関数は、強クラスターに頂点 `newRoot` が追加され、元々の根と `newRoot` を接続している辺の番号が `edgeIdx` であるときの操作 `compress` を行う。
    - `S compress(S a, int edgeIdx, int newRoot)`
- 頂点数 $n$ : $1 \leq n \leq 2\times 10^8$ (その他、 `nachia::Graph` の制約による)
- グラフは木である
- $O(n)$ 時間 + $O(n)$ 回の呼び出し

メインの処理を行う。

### getAtVtx

```c++
S getAtVtx(int i);
```

- $0\leq i \lt n$
- $O(1)$ 時間 + $O(1)$ 回の呼び出し

木 $T$ 全体の頂点集合を $T'$ としたときの $f(r,T')$ の値を返す。

### getAtEdge

```c++
S getAtEdge(int root, int edge);
```

- $0\leq \text{root} \lt n$
- $0\leq \text{edge} \lt n-1$
- 辺 $\text{edge}$ は、頂点 $\text{root}$ に隣接している
- $O(1)$ 時間 + $O(1)$ 回の呼び出し

$v=\text{root}$ とし、 $w$ を辺 $\text{edge}$ の $2$ つの端点のうち $v$ でないほうとする。

木 $T$ のうち、 $\text{dist}(v,x)\lt\text{dist}(w,x)$ であるような頂点 $x$ の集合を $T'$ としたときの $f(v,T')$ の値を返す。



---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
