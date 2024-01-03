# ビット演算

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/misc/bit-operations.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/misc/bit-operations.hpp)

## 主な機能

64 ビットのビット演算を計算する。マクロ `__GNUC__` が定義されているときはビルトイン関数を使う。

### MsbIndex

```c++
int MsbIndex(unsigned long long x) noexcept;
```

* $x\neq 0$

下位ビットから順に $0$～$63$ とするとき、立っているビットのうち最も大きいものの番号を返す。

### LsbIndex

```c++
int LsbIndex(unsigned long long x) noexcept;
```

* $x\neq 0$

下位ビットから順に $0$～$63$ とするとき、立っているビットのうち最も小さいものの番号を返す。

### Popcount

```c++
int Popcount(unsigned long long x) noexcept;
```

立っているビットの個数を返す。

## 参考

- https://www.mathenachia.blog/re-nouse-msb-method/

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>


