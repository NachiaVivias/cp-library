# 行列（剰余体 : $\mathbb{F} _ p=\mathbb{Z}/p\mathbb{Z}$ ）

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/linear-modulo/matrix-modulo.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/linear-modulo/matrix-modulo.hpp)

## 主な機能

体 $\mathbb{F} _ p$ 上の $h \times w$ 型行列 $A$ を管理する。スカラーの型には `atcoder::static_modint<p>` ( $p$ は奇素数) およびそれに準ずる構造体を指定できる。

## struct nachia::MatrixModulo

### テンプレート引数

```c++
namespace nachia{

    template<class Elem>
    struct MatrixModulo;

}
```

`Elem` は $\mathbb{F} _ p$ の要素の型である。 AtCoder Library の `atcoder::static_modint<p>` ( $p$ は奇素数) が望ましいが、同様のインターフェースを持つ他の構造体も利用できるようにしている。各メンバ関数で用いている機能が実装されていない場合は利用できないが、その詳細な条件は分量が多いゆえ説明を控える。

### コンストラクタ

```c++
MatrixModulo(int new_h, int new_w);
```

- $h=\text{new\_h}$
- $w=\text{new\_w}$
- $0 \leq hw \leq 10^7$
- $O(hw)$ 時間

$h \times w$ 型零行列で初期化される。

### height, width, numRow, numColumn

```c++
int height() const;
int width() const;
int numRow() const;
int numColumn() const;
```

- $O(1)$ 時間

`height` , `numRow` は $h$ の値を返す。

`width` , `numColumn` は $w$ の値を返す。

行列 $A$ の型を取得する。

### operator\[]

```c++
typename std::vector<Elem>::iterator operator[](int y);
typename std::vector<Elem>::const_iterator operator[](int y) const;
```

- $O(1)$ 時間

$y$ 行目の先頭を指すイテレータを取得する。


### Identity

```c++
static MatrixModulo Identity(int idx);
```

- $n=\text{idx}$
- $O(n^2)$ 時間

$n$ 次単位行列を取得する。

### operator*

```c++
MatrixModulo operator*(const MatrixModulo& r) const;
```

- `this->width() == r.height()`
- `this` を $n \times m$ 型の行列 $A$ 、 $r$ を $m \times k$ 型の行列 $B$ とする。
- $O(nmk)$ 時間

行列の積 $AB$ を返す。

### det

```c++
Elem det() const;
```

- $1 \leq h=w$
- $O(h^3)$ 時間

正方行列の行列式を返す。

### rank

```c++
int rank() const;
```

- $0 \leq h$
- $0 \leq w$
- $O(h^2w)$ 時間

ランクを計算し、返す。 $h=0$ または $w=0$ のときは $0$ を返す。

### linear_equation

```c++
MatrixModulo linear_equation() const;
```

- $1 \leq h$
- $2 \leq w$
- $O(h^2w)$ 時間

$w$ 次列ベクトル

$$\boldsymbol{x}= \left( \begin{matrix} x _ 0 \newline x _ 1 \newline \vdots \newline x _ {w-1} \end{matrix} \right) $$

であって、 $x _ {w-1}=1$ かつ $A\boldsymbol{x}=O$ を満たすものの集合を求める。

次の線形連立方程式を解くことに対応する。

$$
\left\{
    \begin{array}{l}
        A _ {0,0} x _ 0 + A _ {0,1} x_1 + \cdots + A _ {0,w-2} x _ {w-2} + A _ {0,w-1} = 0 \newline
        A _ {1,0} x _ 0 + A _ {1,1} x_1 + \cdots + A _ {1,w-2} x _ {w-2} + A _ {1,w-1} = 0 \newline
        \hspace{10px} \vdots \newline
        A _ {h-1,0} x _ 0 + A _ {h-1,1} x_1 + \cdots + A _ {h-1,w-2} x _ {w-2} + A _ {h-1,w-1} = 0 \newline
    \end{array}
\right.
$$

解がない場合は、 $h=0$ のインスタンスを返す。

解がある場合に返る行列を $B$ とする。 $B$ は $h' \times w$ 型行列 $(h' \leq h)$ である。 $B _ {0,w-1}=1,B _ {y,w-1}=0 \hspace{5px}(1 \leq y \lt h')$ を満たす。

$B$ の各行ベクトルを $\boldsymbol{b} _ 0,\boldsymbol{b} _ 1, \ldots ,\boldsymbol{b} _ {h'-1}$ とする。これらはいずれも零ベクトルでない。これらの線形結合の転置 $\boldsymbol{x}=(\sum_i t _ i \boldsymbol{b} _ i)^\top$ で方程式 $A\boldsymbol{x}=O$ の解が網羅される。ただし、線形連立方程式の定数項を正しく扱うには、 $\boldsymbol{b} _ 0$ の係数は $t _ 0=1$ としなければならない。

## 参考


---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>


