# 2 次元整数座標のデータ型

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/geometry/veci2.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/geometry/veci2.hpp)

## 主な機能

$2$ 次元整数座標を扱うデータ型を提供する。

## 構造体テンプレート VecI2

### テンプレート引数

```c++
template<class Int = long long, class Int2 = long long>
struct VecI2;
```

通常使用する整数型 `Int` と、乗算結果のための大きい整数型 `Int2` を設定できる。

### コンストラクタ

```c++
VecI2();                      // (1)
VecI2(std::pair<Int, Int> _p) // (2)
VecI2(Int _x, Int _y);        // (3)
```

* (1) : $(0,0)$ で初期化する。
* (2) : 座標を $(x,y)$ のペアで与えて初期化する。
* (3) : 座標を与えて初期化する。

### 基本的な演算子

```c++
VecI2& operator+=(VecI2 r);
VecI2& operator-=(VecI2 r);
VecI2& operator*=(Int r);
VecI2 operator+(VecI2 r) const;
VecI2 operator-(VecI2 r) const;
VecI2 operator*(Int r) const;
VecI2 operator-() const;
```

加減算と定数倍。

### 内積

```c++
Int2 operator*(VecI2 r) const;  // (1)
Int2 norm() const;              // (2)
```

* (1) `this` と `r` の内積を計算する。
* (2) $x^2+y^2$ の値を計算して返す。

### 行列式

```c++
Int2 operator^(VecI2 r);
```

`this` を $(x _ 1,y _ 1)$ 、 `r` を $(x _ 2,y _ 2)$ とするとき、 $x _ 1y _2-x _ 2y _ 1$ の値を計算して返す。

### 辞書順比較

```c++
static bool compareYX(VecI2 a, VecI2 b); // (1)
static bool compareXY(VecI2 a, VecI2 b); // (2)
bool operator<(VecI2 r) const;           // (3)
```

* (1) $(y,x)$ の辞書順で比較する。
* (2) $(x,y)$ の辞書順で比較する。
* (3) $(x,y)$ の辞書順で比較する。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
