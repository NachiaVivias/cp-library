# 重心分解二分探索木

[C++ 用ライブラリ一覧に戻る](../index.md)

## 主な機能

$n$ 頂点の静的な根付き無向木 $T$ がある。頂点には番号(0-based) が振られている。

頂点 $p$ からの距離が $d_l$ 以上 $d_r$ 未満の頂点すべてに対するクエリを、矩形クエリを $1$ 次元区間クエリに変換する。性質上、集約関数の可換性を仮定する。

区間クエリ用のデータ構造の必要数は高々 $2 \log _ 2 n + O(1)$ で、それぞれが $n$ 点を高々 $1$ 個ずつ管理する。 $d$ 個目の区間クエリ用のデータ構造の $i$ 番目の位置で管理される点の番号を $A[d][i]$ とする。

## パフォーマンス

(2022/08/15 時点) 私が試したわけではないけど、使ってみると suisen さんの実装のほうが高速に動作するらしいし、ユーザーの負担が少ない（例えば [これ](https://suisen-cp.github.io/cp-library-cpp/library/tree/point_set_range_contour_product.hpp) ）。一方、こちらのライブラリは頂点列の構築および領域の分解を明示的に返すので柔軟性が高いと思われる。

## struct CentroidDecompositionBinaryTree

### コンストラクタ

```c++
CentroidDecompositionBinaryTree(); // (#)
nachia::CentroidDecompositionBinaryTree(const nachia::AdjacencyList& adj); // (1)
```

[AdjacencyList とは？](./../graph/adjacency-list.md)

`(#)` ダミーを生成する。このコンストラクタで生成したインスタンスでクエリを呼んではいけない。

`(1)`

- $\text{adj.size()} = n$
- $2 \leq n \leq 5\times 10^5$
- 引数は無向木を表すリスト。各辺は双方向になければならない。
- $O(n \log n)$ 時間

前処理を行う。

### get_array_count

```c++
int get_array_count() const;
```

- $O(1)$ 時間

区間クエリ用のデータ構造の個数を返す。

### get_array

```c++
const std::vector<int>& get_array(int id) const;
```

- $0 \leq \text{id} \lt a$ ( $a$ は `get_array_count` が返す値 )
- $O(n)$ 時間

区間クエリ用のデータ構造が管理するデータ列を頂点番号で取得する。

### get_update_points

```c++
const std::vector<UpdatePoint> get_update_points(int vtx);
```

- $0\leq\text{vtx}\lt n$
- $O(\log n)$ 時間

頂点 $\text{vtx}$ に対応する点のリストを返す。

構造体 `QueryRange` は $i$ , $p$ の組からなり $i$ 番目（ $\text{id}=i$ ）の区間データ構造のインデックス $p$ を指定する。

### get_query_range

```c++
const std::vector<QueryRange>& get_query_range(int from, int distl, int distr);
```

- $0 \leq \text{from} \lt n$
- $-10^9 \leq \text{distl} \leq \text{distr} \leq 10^9$
- $O(\log n)$ 時間

引数を順に $p$ , $d _ l$ , $d _ r$ とする。

頂点 $p$ からの距離が $d_l$ 以上 $d_r$ 未満である頂点がちょうど $1$ 回ずつ現れるようにデータ列中の区間のリストを構築し、返す。

構造体 `QueryRange` は $i$ , $l$ , $r$ の組からなり $i$ 番目（ $\text{id}=i$ ）の区間データ構造の区間 $[l,r)$ を指定する。

返されるリストには長さ $0$ の区間が含まれるかもしれない。

## 参考

- [mathenachia](https://www.mathenachia.blog/mergetech-and-logn/)


---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
