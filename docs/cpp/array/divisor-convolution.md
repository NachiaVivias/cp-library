# 約数包除・GCD畳み込み

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/array/divisor-convolution.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/array/divisor-convolution.hpp)

## 主な機能

約数・倍数の関係に基づく計算。

- ゼータ変換 / メビウス変換
- GCD 畳み込み / LCM 畳み込み

## 関数

### DivisorZeta, DivisorReversedZeta

```c++
template<class Elem>
void DivisorZeta(::std::vector<Elem>& a);
template<class Elem>
void DivisorReversedZeta(::std::vector<Elem>& a);
```

- $n = $ `a.size()` ${}-1$
- $1 \leq n \leq 10^8$
- `Elem` は可換群： `Elem` どうしで演算 `+=` ができる
- $O(n \log \log n)$ 時間

ゼータ変換。

$a[0]$ の値は無視される。

$1 \leq s$ について、 $a[s]$ の値を次の値で上書きする。

- `DivisorZeta` の場合 ： $s$ の正の約数 $t$ について $a[t]$ の総和
- `DivisorReversedZeta` の場合 ： $s$ の正の倍数 $t$ について $a[t]$ の総和

### DivisorMobius, DivisorReversedMobius

```c++
template<class Elem>
void DivisorMobius(::std::vector<Elem>& a);
template<class Elem>
void DivisorReversedMobius(::std::vector<Elem>& a);
```

- $n = $ `a.size()` ${}-1$
- $1 \leq n \leq 10^8$
- `Elem` は可換群： `Elem` どうしで演算 `-=` ができる
- $O(n \log \log n)$ 時間

メビウス変換。

$a[0]$ の値は無視される。

それぞれ `DivisorZeta` , `DivisorReversedZeta` の逆の変形。

### GcdConvolution

```c++
template<class Elem>
::std::vector<Elem> GcdConvolution(::std::vector<Elem> a, ::std::vector<Elem> b);
```

- `a.size()` $=$ `b.size()`
- $n = $ `a.size()` ${}-1$
- $1 \leq n \leq 10^8$
- `Elem` は可換環： `Elem` どうしで演算 `+=` , `-=` , `*=` ができる
- $O(n \log \log n)$ 時間

$a[0]$ の値は無視される。

次で表される数列 $\lbrace c[1] , c[2] , \ldots , c[n] \rbrace$ を返す。 $c[0]$ は定義しない。

$$c[k] = \sum _ {k=\gcd(i,j) , 1 \leq i \leq n , 1 \leq j \leq n} a[i] b[j] \hspace{10px} (1 \leq k \leq n)$$

### LcmConvolution

```c++
template<class Elem>
::std::vector<Elem> LcmConvolution(::std::vector<Elem> a, ::std::vector<Elem> b);
```

- `a.size()` $=$ `b.size()`
- $n := $ `a.size()` ${}-1$
- $1 \leq n \leq 10^8$
- `Elem` は可換環： `Elem` どうしで演算 `+=` , `-=` , `*=` ができる
- $O(n \log \log n)$ 時間

$a[0]$ の値は無視される。

次で表される数列 $\lbrace c[1] , c[2] , \ldots , c[n] \rbrace$ を返す。 $c[0]$ は定義しない。

$$c[k] = \sum _ {k=\operatorname{lcm}(i,j) , 1 \leq i \leq n , 1 \leq j \leq n} a[i] b[j] \hspace{10px} (1 \leq k \leq n)$$

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
