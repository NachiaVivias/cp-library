# 固有多項式

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/linear-modulo/characteristic-polynomial.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/linear-modulo/characteristic-polynomial.hpp)

## 主な機能

正方行列 $A$ に対して、 $L=\lvert \lambda E-A\rvert$ ( $E$ は単位行列 ) は $\lambda$ の多項式であり $A$ の固有多項式と呼ばれている。

このライブラリの機能は、 $A$ の固有多項式の各次の係数を求めることである。

### 関数 CharacteristicPolynomial

```c++
template<class Elem>
std::vector<Elem> CharacteristicPolynomial(MatrixModulo<Elem> mat);
```

- `mat` は $n\times n$ 型行列
- $0 \leq n$
- $O(n^3)$ 時間

`mat` で表される行列の固有多項式を計算する。返り値を `a` とすろと、 `a` は長さ $n+1$ の列であり、 `a[i]` は固有多項式の ${\lambda }^i$ の係数である。

## 参考

- Library Checker : Characteristic Polynomial [https://judge.yosupo.jp/problem/characteristic_polynomial](https://judge.yosupo.jp/problem/characteristic_polynomial)

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>


