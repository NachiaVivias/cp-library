# 木の同型性判定 AHU algorithm

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/tree/ahu-algorithm.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/tree/ahu-algorithm.hpp)

## 主な機能

$n$ 頂点の木の同型判定問題の効率的なアルゴリズムである。木の重心の計算と組み合わせると、 $O(n)$ 時間を達成する。

同時に、木のオイラーツアーであって、根から離れる向きを `1` 、根に戻る向きを `2` としたときに辞書順最小のものを求められる。

## struct AHUAlgorithmLinearTime

### コンストラクタ

```c++
AHUAlgorithmLinearTime(const AdjacencyList& E, int root = 0);
```

[AdjacencyList とは？](./../graph/adjacency-list.md)

- $1 \leq n \leq 10^8$
- $O(n)$ 時間

根を $\text{root}$ として AHU algorithm を適用する。

### メンバ変数

```c++
    std::vector<int> compressed;
    std::vector<int> depth;
    treetourlex_internal::CSRArray children_ordered;
```

`depth[i]` は頂点 $i$ の深さである。

`compressed[i]` は、深さ `depth[i]` の頂点の部分木を座標圧縮したとき、頂点 $i$ の部分木に対応する値である。

`children_ordered[i]` は、深さ優先探索で頂点 $i$ を訪れたあと、辞書順最小のツアー得るために子を訪れる順番を表す。一般的な構造とは別の型であるが、 `begin` , `end` , `size` , `operator[]` を用いることで配列同様に扱える。

## 使用例

根付き木の同型性判定をする場合、 $2$ つの木の根を新しい根につないだ木を作って AHU algorithm を適用するとよい。答えは $2$ つの木の根の `compressed` が同じ値であるかどうかである。

木の同型性判定をする場合、根を重心（ $1$ ～ $2$ 個である）に決め打つことで根付き木の同型性判定に帰着する。

## 参考

- [https://logic.pdmi.ras.ru/~smal/files/smal_jass08.pdf](https://logic.pdmi.ras.ru/~smal/files/smal_jass08.pdf)

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
