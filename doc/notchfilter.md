# Notch filter design

## IIR Notch filter 

Given by this transfer function
$$
H(z) = b_0\frac{1-(2\cos{\omega_0})z^{-1}+z^{-2}}{1-(2r\cos{\omega_0})z^{-1}+r^2 z^{-2}}
$$

where $r$ describes how much of frequency around $\omega_0$ is going to be away ( $r\rightarrow1$ give more selective notch filter )

$\omega_0$ is frequency to get rid of  $\omega_0=2\pi\frac{f}{f_s}$

## Structure

![IIR transposed direct 2][iir.png]

Filter will be realized with most used IIR transposed direct form 2 ( zero first )

given by
$$y[n] = v_1[n-1]+b_0 x[n]$$
$$v_1[n] = v_2[n-1]-a_1y[n]+b_1x[n]$$
$$v_2[n] = b_2x[n] - a_2 y[n]$$

for a 2 order IIR filter described by
$$H(z) = \frac{b_0+b_1 z^{-1}+b_2 z^{-2}}{1+a_1 z^{-1} + a_2 z^{-2}}$$

So for our notch filter:
* $a_1 = 2\cdot r \cos{2\pi\frac{f}{f_s}}$
* $a_2 = r^2$
* $b_0 = b_2 = 1$  ( gain 1 )
* $b_1 = 2\cdot\cos{2\pi\frac{f}{f_s}}$

## Psuedo Code
```
1. define static variables - prev_v1, prev_v2, prev_yn = 0
2. compute constant coefficients based on sampling freq, target freq, and degree of selection
3. compute v2 = xn - r^2*yn 
4. compute v1 = prev_v2 - 2*r*cos(2*PI*f/fs)*yn + 2*cos(2*PI*f/fs)*xn
5. compute yn = prev_v1 + xn
6. update static variables
7. return xn
```
