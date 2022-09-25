# Теория

## Треугольная норма(t-норма)

Треугольная норма(t-норма) T: [0,1]$\times$[0,1]→[0,1], удовлетворяющая условиям:

- $T(0, 0) = 0, T(\mu_a, 1) = \mu_a$ (ограниченность);
- $T(\mu_a, \mu_b) = T(\mu_b, \mu_a)$ (коммутативность);
- $T(\mu_a, T(\mu_b, \mu_c)) = T(T(\mu_a, \mu_b), \mu_c)$ (ассоциативность);
- $T(\mu_a, \mu_b)\le T(\mu_c, \mu_d)$, если $\mu_a\le\mu_c$ и $\mu_b\le\mu_d$ (монотонность).

### Пример

- $T_m(\mu_a, \mu_b) = min(\mu_a, \mu_b)$;
- $T_p(\mu_a, \mu_b) = \mu_a*\mu_b$;
- $T_l(\mu_a, \mu_b) = max(0, \mu_a+\mu_b-1)$;
- $T_d(\mu_a, \mu_b) =
\begin{cases}
\mu_a &, \text{если }\mu_b=1\\
\mu_b &, \text{если }\mu_a=1\\
0 &,  \text{в других случаях}\\
\end{cases}$

## Треугольная конорма(t-конорма)

Треугольная норма(t-норма) $\perp$: [0,1]$\times$[0,1]→[0,1], удовлетворяющая условиям:

- $\perp(1, 1) = 1, \perp(\mu_a, 0) = \mu_a$ (ограниченность);
- $\perp(\mu_a, \mu_b) = \perp(\mu_b, \mu_a)$ (коммутативность);
- $\perp(\mu_a, \perp(\mu_b, \mu_c)) = \perp(\perp(\mu_a, \mu_b), \mu_c)$ (ассоциативность);
- $\perp(\mu_a, \mu_b)\le \perp(\mu_c, \mu_d)$, если $\mu_a\le\mu_c$ и $\mu_b\le\mu_d$ (монотонность).

### Пример

- $\perp_m(\mu_a, \mu_b) = max(\mu_a, \mu_b)$;
- $\perp_p(\mu_a, \mu_b) = \mu_a+\mu_b-\mu_a*\mu_b$;
- $\perp_l(\mu_a, \mu_b) = min( \mu_a+\mu_b, 1)$;
- $\perp_d(\mu_a, \mu_b) =
\begin{cases}
\mu_a &, \text{если }\mu_b=0\\
\mu_b &, \text{если }\mu_a=0\\
1 &,  \text{в других случаях}\\
\end{cases}$

## Специальные t-нормы и t-конормы

### Майор-Торренс

$$
T(\mu_a, \mu_b) = 
\begin{cases}
max(\mu_a+\mu_b-\lambda, 0) &, \text{ если }\lambda\in[0, 1] \text{ и }(\mu_a, \mu_b)\in[0,\lambda]^2\\
min(\mu_a, \mu_b) &, \text{ если } \lambda=0 \text{ или }\mu_a>\lambda \text{ или } \mu_b>\lambda\\ 
\end{cases}

\newline
\perp(\mu_a, \mu_b) = 
\begin{cases}
min(\mu_a+\mu_b+\lambda-1, 1) &, \text{ если }\lambda\in[0, 1] \text{ и }(\mu_a, \mu_b)\in[1-\lambda, 1]^2\\
max(\mu_a, \mu_b) &, \text{ если } \lambda=0 \text{ или }\mu_a<1-\lambda \text{ или } \mu_b<1-\lambda\\ 
\end{cases}

$$

### Ягер

$$
T(\mu_a, \mu_b) = 
\begin{cases}
max\left(1-\left((1-\mu_a)^\lambda+(1-\mu_b)^\lambda\right)^{\frac{1}{\lambda}}, 0\right) &, \text{ если }\lambda\in(0, +\infty)\\
T_d(\mu_a, \mu_b) &, \text{ если }\lambda=0\\
T_m(\mu_a, \mu_b) &, \text{ если }\lambda=\infty\\ 
\end{cases}

\newline
\perp(\mu_a, \mu_b) = 
\begin{cases}
min\left((\mu_a^\lambda+\mu_b^\lambda)^{\frac{1}{\lambda}}, 1\right) &, \text{ если }\lambda\in(0, +\infty)\\
\perp_d(\mu_a, \mu_b) &, \text{ если }\lambda=0\\
\perp_m(\mu_a, \mu_b) &, \text{ если }\lambda=\infty\\ 
\end{cases}

$$

# Домашнее задание

1. Доказать: $T_d\le T_l\le T_p\le T_m$;
2. Доказать: $\forall t\text{-нормы } T: T_d\le T \le T_m;$
3. Доказать: $\perp_d\ge \perp_l\ge \perp_p\ge \perp_m$;
4. Доказать: $\forall t\text{-конормы } \perp: \perp_d\le \perp \le \perp_m;$
5. Проверить выполнение свойств t-норм и t-конорм для t-нормы и t-конормы Майора-Торренса;
6. Проверить выполнение свойств t-норм и t-конорм для t-нормы и t-конормы Ягера

## 2. Доказать: $\forall t\text{-нормы } T: T_d\le T \le T_m;$

__Доказательство:__
1. Из свойств $T(\mu_a, \mu_b) \le T(\mu_c, \mu_d), \text{ если } \mu_a\le\mu_c, \mu_b\le\mu_d$,
   $T(0, 0) = 0, T(\mu_a, 1) = \mu_a$ => $\forall T \forall (\mu_a, \mu_b)\in[0,1]^2$:
   - $T(\mu_a, \mu_b) \le T(\mu_a, 1)=\mu_a$;
   - $T(\mu_a, \mu_b) \le T(1, \mu_b)=\mu_b$;
2. На границе $[0, 1]^2$ $T(0, 0)=T(0, 1)=T(1, 0)=0, T(1, 1)=1$;
3. $\forall(\mu_a, \mu_b)\in[0, 1]^2$ и $\forall T$
    $T(\mu_a, \mu_b)\ge 0=T_d(\mu_a, \mu_b)$ и $T(\mu_a, \mu_b)\le min(\mu_a, \mu_b)$(п.1).

## 1. Доказать: $T_d\le T_l\le T_p\le T_m$

__Доказательство:__
1. Докажем, что $max(0, \mu_a+\mu_b-1)\le\mu_a*\mu_b$:
   1. 1-ый случай, когда $\mu_a+\mu_b-1\le0\le\mu_a*\mu_b$;
   2. 2-ой случай, когда $\mu_a+\mu_b-1>0 => \mu_a+\mu_b-1-\mu_a*\mu_b=-(1-\mu_a)*(1-\mu_b)\le 0$
2. Получили, что $T_l\le T_p$;
3. Тогда используем утверждение из __2-ой задачи__ и получаем, что 
   __$T_d\le T_l\le T_p\le T_m$__

## 4. Доказать: $\forall t\text{-конормы } \perp: \perp_d\le \perp \le \perp_m;$

__Доказательство:__
1. Из свойств конормы $\perp(\mu_a, \mu_b)\le\perp(\mu_c, \mu_d) <= \mu_a\le\mu_c, \mu_b\le\mu_d$
   и $\perp(1, 1)=1, \perp(\mu_a, 0)=\mu_a$ получаем
   $\forall \perp \forall (\mu_a, \mu_b)\in[0, 1]^2$:
   - $\perp(\mu_a, \mu_b) \ge \perp(\mu_a, 0)=\mu_a$;
   - $\perp(\mu_a, \mu_b) \ge \perp(0, \mu_b)=\mu_b$;
2. На границе $[0, 1]^2 \perp(0, 0)=0, \perp(0, 1)=\perp(1, 0)=\perp(1, 1)=1$;
3. $\forall(\mu_a, \mu_b)\in[0, 1]^2$ и $\forall \perp: \perp(\mu_a, \mu_b)\le 1=\perp_d(\mu_a, \mu_b)$ 
   и $\perp(\mu_a, \mu_b)\ge max(\mu_a, \mu_b)=\perp_m(\mu_a, \mu_b)$.
   
## 3. Доказать: $\perp_d\ge \perp_l\ge \perp_p\ge \perp_m$;

__Доказательство:__
1. Докажем, что $min(\mu_a+\mu_b, 1)\ge\mu_a+\mu_b-\mu_a*\mu_b$:
   1. 1-ый случай, когда 
      $\mu_a+\mu_b\ge1 => |1-\mu_a-\mu_b+\mu_a*\mu_b\ge0| => 1\ge \mu_a+\mu_b-\mu_a*\mu_b$; 
   2. 2-ой случай, когда $\mu_a+\mu_b<1 => \mu_a+\mu_b-\mu_a-\mu_b+\mu_a*\mu_b \ge 0$;
2. Тогда используя решение п.4
   $\perp_d\ge\perp_l\ge\perp_p\ge\perp_m$.
   
## 5. Проверить выполнение свойств t-норм и t-конорм для t-нормы и t-конормы Майора-Торренса;

### t-норма 
$$ 
T(\mu_a, \mu_b) = 
\begin{cases}
max(\mu_a+\mu_b-\lambda, 0) &, \text{ если }\lambda\in[0, 1] \text{ и }(\mu_a, \mu_b)\in[0,\lambda]^2\\
min(\mu_a, \mu_b) &, \text{ если } \lambda=0 \text{ или }\mu_a>\lambda \text{ или } \mu_b>\lambda\\ 
\end{cases}
$$
- Проверка свойств:
   1. $$ 
      T(0, 0) =
      \begin{cases}
         max(-\lambda, 0) &, \text{ если }\lambda\in[0, 1] \text{ и }(\mu_a, \mu_b)\in[0,\lambda]^2\\
         min(0, 0) &, \text{ если } \lambda=0 \text{ или }\mu_a>\lambda \text{ или } \mu_b>\lambda\\ 
      \end{cases} = 0;
      $$
      $$
      T(\mu_a, 1) = min(\mu_a, 1) = \mu_a;
      $$
   2. Комутативность очевидна;
   3. $$ 
      T(\mu_a, T(\mu_b, \mu_c)) = 
      \begin{cases}
         max(\mu_a+max(\mu_b+\mu_c-\lambda, 0)-\lambda, 0)\\
         min(\mu_a, min(\mu_b, \mu_c)) \\ 
      \end{cases} = \newline 
      \begin{cases}
         max(max(\mu_a+\mu_b-\lambda, 0)+\mu_c-\lambda, 0) \\
         min(min(\mu_a, \mu_b), \mu_c) \\ 
      \end{cases}
      $$
   4. Монотонность следует из монотонности максимума и минимума.

### t-конорма
$$
   \perp(\mu_a, \mu_b) = 
   \begin{cases}
      min(\mu_a+\mu_b+\lambda-1, 1) &, \text{ если }\lambda\in[0, 1] \text{ и }(\mu_a, \mu_b)\in[1-\lambda, 1]^2\\
      max(\mu_a, \mu_b) &, \text{ если } \lambda=0 \text{ или }\mu_a<1-\lambda \text{ или } \mu_b<1-\lambda\\ 
   \end{cases}
$$

- Проверка свойств:
   1. $$
      \perp(1, 1) = 
      \begin{cases}
         min(1+\lambda, 1) \\
         max(1, 1) \\ 
      \end{cases} = 1;
      $$
      $$ 
      \perp(\mu_a, 0) = 
      \begin{cases}
         min(\mu_a+\lambda-1, 1) \\
         max(\mu_a, 0) \\ 
      \end{cases} = \mu_a
      $$
   2. Коммутативность и монотонность следует из монотонности максимума и минимума;
   3. Ассоциативность, как и в случае t-нормы.

## 6. Проверить выполнение свойств t-норм и t-конорм для t-нормы и t-конормы Ягера

### t-норма
$$
   T(\mu_a, \mu_b) = 
   \begin{cases}
      max\left(1-\left((1-\mu_a)^\lambda+(1-\mu_b)^\lambda\right)^{\frac{1}{\lambda}}, 0\right) &, \text{ если }\lambda\in(0, +\infty)\\
      T_d(\mu_a, \mu_b) &, \text{ если }\lambda=0\\
      T_m(\mu_a, \mu_b) &, \text{ если }\lambda=\infty\\ 
   \end{cases}
$$

- Проверка свойств:
   1. $$
      T(0, 0) = 
      \begin{cases}
         max\left(1-2^{\frac{1}{\lambda}}, 0\right) &, \text{ если }\lambda\in(0, +\infty)\\
         T_d(0, 0) &, \text{ если }\lambda=0\\
         T_m(0, 0) &, \text{ если }\lambda=\infty\\ 
      \end{cases} = 0;
      \newline
      T(\mu_a, 1) = 
      \begin{cases}
         max\left(\mu_a, 0\right) &, \text{ если }\lambda\in(0, +\infty)\\
         T_d(\mu_a, 1) &, \text{ если }\lambda=0\\
         T_m(\mu_a, 1) &, \text{ если }\lambda=\infty\\ 
      \end{cases} = \mu_a;
      $$
   2. Коммутативность и монотонность(из свойств нормы и максимума) очевидна;
   3. Для ассоциативности проверим только 1-ый случай, остальные верны из определения t-нормы.
      Более того, для проверки ассоциативности __достаточно проверить следующее равенство:__
      $$ 
      max(1-y, 0) = 1-min(y, 1)
      $$
      1. $1-y<0 => y>1 => max(1-y, 0) = 0 = 1-min(y, 1)$
      2. $1-y>0 => 1>y => max(1-y, 0) = 1-y = 1-min(y, 1)$
      
      Тогда 
      $$
      max\left(1-\left((1-\mu_a)^\lambda+(1-\mu_b)^\lambda\right)^{\frac{1}{\lambda}},
      0\right) = 
      \newline
      1-min\left(((1-\mu_a)^\lambda+(1-\mu_b)^\lambda)^{\frac{1}{\lambda}},
      1\right) 
      $$
      Отсюда следует ассоциативность:
      $$
      (1-\mu_a)^\lambda+(1-1+min\left(((1-\mu_b)^\lambda+(1-\mu_c)^\lambda)^{\frac{1}{\lambda}},
      1\right)^\lambda =
      \newline
      (1-\mu_a)^\lambda + min\left((1-\mu_b)^\lambda+(1-\mu_c)^\lambda, 1\right)^\lambda
      $$
      (ассоциативность внешнего максимума показывается аналогично)
   4. Монтонность следует из п.3 и монотонности минимума

### t-конорма

$$
\perp(\mu_a, \mu_b) = 
\begin{cases}
   min\left((\mu_a^\lambda+\mu_b^\lambda)^{\frac{1}{\lambda}}, 1\right) &, \text{ если }\lambda\in(0, +\infty)\\
   \perp_d(\mu_a, \mu_b) &, \text{ если }\lambda=0\\
   \perp_m(\mu_a, \mu_b) &, \text{ если }\lambda=\infty\\ 
\end{cases}
$$

__Проверка свойств(только для первого случая, для конорм эти проверки уже выполнены):__
   1. $$
      \perp(1, 1) = min(2^\frac{1}{\lambda}, 1) = 1
      \newline
      \perp(\mu_a, 0) = min(\mu_a, 1) = \mu_a
      $$
   2. Коммутативность, ассоциативность и монотонность следуют из аналогичных рассуждений для
      t-нормы. 
