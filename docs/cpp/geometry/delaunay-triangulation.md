# ドロネー三角形分割

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/geometry/delaunay-triangulation.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/geometry/delaunay-triangulation.hpp)

## 主な機能

ドロネー三角形分割で得られる辺を列挙する。

## 構造体テンプレート DelaunayTriangulation

### テンプレート引数

```c++
template<class Int = long long, class Int2 = long long, class Int3 = Int2>
class DelaunayTriangulation;
```

入力に使用する整数型 `Int` と、内部で使用する大きい整数型 `Int2`, `Int3` を設定できる。

入力される点の座標は `nachia::VecI2<Int,Int2>` 型で表現する。

### コンストラクタ

```c++
DelaunayTriangulation();
DelaunayTriangulation(std::vector<VecI2<Int,Int2>> x_points);
```

* 要素数 $n$ : $0 \leq n \leq 10^8$
* 座標が同じ $2$ 点はない
* $2$ 座標の差の絶対値の最大を $d$ とするとき、
    * `Int` 型は $\pm d$ の範囲を扱える。
    * `Int2` 型は $\pm 4d^2$ の範囲を扱える。
    * `Int3` 型は $\pm 12d^4$ の範囲を扱える。
* $O(n\log n)$ 時間

引数を与えない場合は $0$ 頂点について計算を行う。

### getEdges

```c++
std::vector<std::pair<int, int>> getEdges();
```

計算された辺をすべて得る。 $(a,b)$ 間に辺がある場合、 $(a,b)$ または $(b,a)$ のどちらか一方のみが出力に含まれる。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
