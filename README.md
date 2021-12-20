# Water Filling #

## Introduction ##

This is a C++ implementation of the following problem which is widely known as the "Water Filling Problem".

*Water-filling* We consider the convex optimization problem 
$$
\begin{aligned}
    \text{minimize} \quad & \sum_{i=1}^n -\log(\alpha_i + x_i)\\
    \text{subject to} \quad & x_i \succeq 0, \textbf{1}^T x=1
\end{aligned}
$$
where $\alpha_i > 0$.

## References ##

*Boyd S*, *Boyd S P*, *Vandenberghe L*. Convex optimization[M]. Cambridge university press, 2004.
