# グリッド上の隣接関係

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/multi-dimensional/grid-adj.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/multi-dimensional/grid-adj.hpp)

## 主な機能

$2$ 次元のマス目上のあるマスに対して、

* 上下左右の $4$ 方向に隣接するマス
* 斜めを含めた $8$ 方向に隣接するマス

を考えることがある。長方形のマス目の境界を考慮して、指定したマスに隣接するマスを列挙する。

## struct nachia::GridAdj4

### コンストラクタ

```c++
GridAdj4(int height, int width);
```

縦 $\text{height}$ 、横 $\text{width}$ マスのマス目を考える。

マスは $(y,x)$ で指定され、存在するマスは $0\leq y\lt\text{height}, 0\leq x\lt\text{width}$ を満たす部分である。

### operator()

```c++
GridAdj4Range operator()(int y, int x) const;
```

マス $(y,x)$ の上下左右に隣接する、高々 $4$ 個のマスを列挙するオブジェクトを返す。 `begin` , `end` が定義されていて、下のプログラムのように for each で要素を取り出せる。

```c++
#include <iostream>
#include <nachia/multi-dimensional/grid-adj.hpp>
int main(){
    nachia::GridAdj4 grid(7,5);
    // 4 entries
    for(auto [u,v] : grid(1,2)){
        std::cout << u << " " << v << std::endl;
    }
    std::cout << std::endl;
    // 2 entries
    for(auto [u,v] : grid(6,4)){
        std::cout << u << " " << v << std::endl;
    }
    std::cout << std::endl;
}
```

## struct nachia::GridAdj8

### コンストラクタ

```c++
GridAdj8(int height, int width);
```

縦 $\text{height}$ 、横 $\text{width}$ マスのマス目を考える。

マスは $(y,x)$ で指定され、存在するマスは $0\leq y\lt\text{height}, 0\leq x\lt\text{width}$ を満たす部分である。

### operator()

```c++
GridAdj8Range operator()(int y, int x) const;
```

マス $(y,x)$ の上下左右斜めに隣接する、高々 $8$ 個のマスを列挙するオブジェクトを返す。 `begin` , `end` が定義されていて、下のプログラムのように for each で要素を取り出せる。

```c++
#include <iostream>
#include <nachia/multi-dimensional/grid-adj.hpp>
int main(){
    nachia::GridAdj8 grid(7,5);
    // 8 entries
    for(auto [u,v] : grid(1,2)){
        std::cout << u << " " << v << std::endl;
    }
    std::cout << std::endl;
    // 3 entries
    for(auto [u,v] : grid(6,4)){
        std::cout << u << " " << v << std::endl;
    }
    std::cout << std::endl;
}
```

## 参考

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>


