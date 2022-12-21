# 木の重心分解

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/tree/centroid-decomposition.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/tree/centroid-decomposition.hpp)

## 主な機能

$n$ 頂点の無向木 $T$ がある。頂点には番号(0-based) が振られている。

任意の無向木には、重心と呼ばれる頂点が $1$ 個または $2$ 個存在する。そのような頂点のうち $1$ 子を削除すると、分離した各部分は頂点数が元の $\frac{1}{2}$ 倍以下である。よって、 $T$ を重心で再帰的に分割すると高さ $\log_2 n$ 程度の根付き木が生成される。根付き木の頂点には、その分割で選択されていた元の木の重心を割り当てる。

そのようにして生成された根付き木を、便宜上、 "重心分解木" と呼ぶことにする。

## struct CentroidDecomposition

### コンストラクタ

```c++
nachia::CentroidDecomposition() // (#)
nachia::CentroidDecomposition(CsrArray<int> edges); // (1)
nachia::CentroidDecomposition(const Graph& g); // (2)
```

[CsrArray とは？](../array/csr-array.md)

`(#)` ダミーを生成する。このコンストラクタで生成したインスタンスでは他のメンバを使用してはいけない。

`(1)` `(2)`

- 頂点数 $n$ : $1 \leq n \leq 5\times 10^5$
- $g$ は無向木を表す。
- $\text{edges}$ は無向木の隣接リスト表現。各辺は双方向でなければならない。
- $O(n \log n)$ 時間

前処理を行う。

### parentOf

```c++
int parentOf(int v) const ;
```

重心分解木において $v$ の親を取得する。 $v$ が根ならば $-1$ を返す。

### depthOf

```c++
int depthOf(int v) const ;
```

重心分解木において $v$ の深さを取得する。根の深さは $0$ である。

### bfsLayer

```c++
BFSUnit bfsLayer(int s, int layer) const ;
```

- 計算量のオーダーは、出力長に対して線形。

木 $T$ の部分木の情報を返す。この部分木は、 $s$ から始めて（重心分解木における）深さが $\text{layer}$ 以下の頂点のみ通って到達できる頂点で構成される、 $T$ の部分木である。

BFSUnit は $2$ つのリスト $I$ , $P$ で構成される。

```c++
struct BFSUnit {
    std::vector<int> I;
    std::vector<int> P;
};
```

$I$ は、対象の部分木で $s$ から幅優先探索したときの頂点の訪問順として適切なリストである。 $P[i]$ は部分木の根を $s$ としたときの $I[i]$ の親である。例外として $I[0]=-1$ である。

$s$ の重心分解木における深さが $\text{layer}$ 以下でなかった場合、 $I$ も $P$ も空の状態で返す。

## 参考

次にリンクする問題で活用することができる。

- [https://yukicoder.me/problems/no/1796](https://yukicoder.me/problems/no/1796)

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
