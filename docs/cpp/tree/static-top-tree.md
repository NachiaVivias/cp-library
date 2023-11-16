# cluster のマージ過程：静的な top tree

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/tree/static-top-tree.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/tree/static-top-tree.hpp)

## 主な機能

$n$ 頂点の木の辺を与えると、辺がバラバラの状態から全体の木に至る cluster のマージ過程を求める。 expose, link, cut などの操作をしない top tree に相当する。

以降では、まったく正確な表現ではないが、 cluster を boundary vertex かもしれない相異なる頂点の組 $(s,t)$ を用いて $s \rightarrow t$ で表す。

理論的には、マージ過程を表す木の高さの上限を $4\log _ 2(n)+O(1)$ にとることができる。

## class StaticTopTree

### コンストラクタ

```c++
StaticTopTree();
StaticTopTree(int n, std::vector<std::pair<int,int>> tree, int root = 0);
```

- $2 \leq n \leq 10^7$
- `tree` の要素を $(u,v)$ とすると、 $0\leq u\lt n$ かつ $0\leq v \lt n$
- `tree` を辺集合とすると、グラフは $n$ 頂点の木をなす
- $2 \leq \text{root} \lt n$
- $O(n\log n)$ 時間

$n$ 頂点の木を cluster のマージ過程で表す。マージ過程の情報は `m_node` から得られる。

`tree` の添え字が辺の番号として使われる。

引数が空の場合、 $2$ 頂点の木で構築する。

### m_node

```c++
struct Node{
    int p, l, r;
    enum Type{ TyCompress, TyRake1, TyRake2, TyEdge } ty;
};
std::vector<Node> m_node;
```

マージ過程を表す木のノードを表す。

原理的に要素数は $2n-3$ である。

$p$ が親、 $l$ が左の子、 $r$ が右の子の番号である。それぞれ存在しない場合は $-1$ である。

$\text{ty}$ はノードの種類である。

存在するならば左の子に対応する cluster を $s _ 1\rightarrow t _ 1$ 、右の子に対応する cluster を $s _ 2\rightarrow t _ 2$ とおく。

- `TyEdge` ： $1$ つの辺を表すノードである。子は持たない。ノード $0$ からノード $n-2$ がちょうどこの種類で、ノード $i$ が辺 $i$ に対応する。
- `TyCompress` ： $t _ 1=s _ 2$ が保証され、 $s _ 1\rightarrow t _ 2$ を新しい cluster とする。
- `TyRake1` ： $t _ 1=s _ 2$ が保証され、 $s _ 1\rightarrow t _ 1$ を新しい cluster とする。
- `TyRake2` ： $s _ 1=s _ 2$ が保証され、 $s _ 2\rightarrow t _ 2$ を新しい cluster とする。

番号 $i$ のノードについて、 $l\lt i$ と $r\lt i$ が保証される。また、マージ過程を表す木の根に対応する cluster $s\rightarrow t$ について、 $s=\text{root}$ （コンストラクタで与えた値）が保証される。

使用例 ： https://twitter.com/NachiaVivias/status/1571466672887963648

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
