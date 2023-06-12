# quaternion
A bunch of note and code on the topic of Quaternion: applications in graphics and vision 

## Properities
\[ **Definition** \]. A quaternion is a ring of number which can be written as
$$\mathbf{H} = \\{ x + y\mathbf{i} + z\mathbf{j} + w\mathbf{k} | x,y,z,w \in \mathbf{R} \\},$$
where $\mathbf{i}, \mathbf{j}, \mathbf{k}$ are complex roots in terms of production, which safisfies 
$$\mathbf{i}^2=\mathbf{j}^2=\mathbf{k}^2=-1,  \mathbf{i}\mathbf{j}=\mathbf{k}, \mathbf{j}\mathbf{k}=\mathbf{i},\mathbf{k}\mathbf{i}=\mathbf{j}.$$

The quaternion is a vector sapce in terms of adding, scalaring and norming, which means,
$$(x_1 + y_1\mathbf{i} + z_1\mathbf{j} + w_1\mathbf{k}) + (x_2 + y_2\mathbf{i} + z_2\mathbf{j} + w_2\mathbf{k}) = (x_1 + x_2) + (y_1+y_2)\mathbf{i} + (z_1+z_2)\mathbf{j} + (w_1+w_2)\mathbf{k},$$
$$\lambda(x + y\mathbf{i} + z\mathbf{j} + w\mathbf{k}) = \lambda x + \lambda y\mathbf{i} + \lambda z\mathbf{j} + \lambda w\mathbf{k}\lambda \in \mathbf{R}.$$
$$||x + y\mathbf{i} + z\mathbf{j} + w\mathbf{k}|| = \sqrt{x^2+y^2+z^2+w^2}.$$
We have production of two quaternions by the linearity and production rule of $`\{\mathbf{i},\mathbf{j},\mathbf{k}\}`$, by caculation,

$$
\begin{align}
(x + y\mathbf{i} + z\mathbf{j} + w\mathbf{k})(a + b\mathbf{i} + c\mathbf{j} + d\mathbf{k}) = &   (xa - yb - zc - wd) + (xb + ya + zd - wc) \mathbf{i} \\
                                                                                           + & (xc + wa + wb - yd)\mathbf{j} + (xd + wa + yc - zb) \mathbf{k}.
\end{align}
$$

So that we can proof,
$$\forall p, q\in\mathbf{H}, ||pq|| = ||p||\cdot||q||.$$
And especially, a quaternion has its conjugation, which is $\*(x + y\mathbf{i} + z\mathbf{j} + w\mathbf{k})=x - y\mathbf{i} - z\mathbf{j} - w\mathbf{k}$.
We can prove that,
$$\*p\times p = p\times\*p = ||p||^2$$
So that, a quaternion can obtain its inverse apparently. 
$$\frac{\*p}{||p||^2} \times p = p \times \frac{\*p}{||p||^2} = 1, \Rightarrow p^{-1} = \frac{\*p}{||p||^2}.$$


\[ **Vector Representation** \]. We denote a quaternion $q = x + y\mathbf{i} + z\mathbf{j} + w\mathbf{k} = x + \mathbf{v}$, where $\mathbf{v}$ can be viewed as a correspondence of $\mathbf{R}^3$. The initial benifit is the production of quaternions, 

$$
\begin{align}
(x + y\mathbf{i} + z\mathbf{j} + w\mathbf{k})(a + b\mathbf{i} + c\mathbf{j} + d\mathbf{k}) = & (x + \mathbf{t})(a + \mathbf{r}) \\
                                                                                           = & (xa - \langle \mathbf{t}, \mathbf{r} \rangle) + x \mathbf{r} + a \mathbf{t} + \mathbf{t} \wedge \mathbf{r}.
\end{align}
$$

And naturally, a vector from $\mathbf{R}^3$ can be embedded into $\mathbf{H}$, that $\forall (x,y,z) \in \mathbf{R}^3, H(x, y, z) = x\mathbf{i} + y\mathbf{j} + z\mathbf{k} \in \mathbf{H}$.


\[ **Rotation** \]. Actually, every $q \in \mathbf{H}$ satisfies $||q||=1$ can represent a rotation map in $\mathbf{R}^3$ by given,

$$\forall \mathbf{x} \in \mathbf{R}^3, \mbox{Rot}\[q\](\mathbf{x}) = q H(\mathbf{x}) q^{-1}.$$

Where the true background mean of that can be represented as, 

$$\forall q \in \mathbf{H}, ||q||=1 \Rightarrow q = \cos \frac{\theta}{2} + \sin \frac{\theta}{2} \mathbf{t}, \mathbf{t}\in \mathbf{R}^3, ||\mathbf{t}||=1.$$

The meaning behind it is, $\mathbf{t}$ is the unchanged vector in $\mbox{Rot}\[q\]$, $\theta$ is the angle rotated by $\mathbf{t}$ by the rule of right hand orientation.

And it is natual to to think of rotation matrices, here we explore the relation ship between the two objects.

Suppose $q = \cos \frac{\theta}{2} + \sin \frac{\theta}{2} \mathbf{v}$, then $\forall \mathbf{x} = (x, y, z) \in \mathbf{R}^3$, here,

$$
\begin{align}
\mbox{Rot}\[q\](x)  & = (\cos \frac{\theta}{2} + \sin \frac{\theta}{2} \mathbf{v}) \mathbf{x} (\cos \frac{\theta}{2} - \sin \frac{\theta}{2} \mathbf{v}) \\
                    & = (\cos \frac{\theta}{2} + \sin \frac{\theta}{2} \mathbf{v}) (\sin \frac{\theta}{2} \langle \mathbf{x}, \mathbf{v} \rangle + \cos \frac{\theta}{2} \mathbf{x} + \sin \frac{\theta}{2} \mathbf{v} \wedge \mathbf{x}) \\ 
                    & = \cos \frac{\theta}{2} \sin \frac{\theta}{2} \langle \mathbf{x}, \mathbf{v} \rangle - \langle \sin \frac{\theta}{2} \mathbf{v}, \cos \frac{\theta}{2} \mathbf{x} + \sin \frac{\theta}{2} \mathbf{v} \wedge \mathbf{x} \rangle
                     + \sin^2 \frac{\theta}{2} \langle \mathbf{x}, \mathbf{v} \rangle \mathbf{v} + \cos^2 \frac{\theta}{2} \mathbf{x} + \cos \frac{\theta}{2} \sin \frac{\theta}{2} \mathbf{v} \wedge \mathbf{x} + \sin \frac{\theta}{2} \cos \frac{\theta}{2} \mathbf{v} \wedge \mathbf{x} + \sin^2 \frac{\theta}{2} \mathbf{v} \wedge (\mathbf{v} \wedge \mathbf{x})\\
                    & = \sin \theta \mathbf{v} \wedge \mathbf{x} + \cos \theta \mathbf{x} + (1 - \cos\theta)\mathbf{v}\mathbf{v}^T\mathbf{x}.
\end{align}
$$

So that, 
$$\mbox{Rot}\[q\] = \sin \theta \[\mathbf{v}\]_{\times}+(I-\mathbf{v}\mathbf{v}^T)\cos\theta.$$

Note that, $\mathbf{v}$ is a eigen value correspond to $\mbox{Rot}\[q\]$, so that $\forall \mathbf{R}\in \mathbf{O}(3)$, $\mathbf{v}$ can be computed by the null space of $\mbox{Rot}\[q\] - I$.

Since then, there equation can be viewed as a linear equation to $\sin \theta, \cos \theta$.


## Implementation

### C++ 

### Rust

### Python Binding

## References
* Wikipedia: [Quaternions](https://en.wikipedia.org/wiki/Quaternion), [Quaternions and saptial rotation](https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation).

* Courses: [CMU15.462: Computer Graphics](http://15462.courses.cs.cmu.edu/fall2021/lecture/3drotations),
[GAMES105](https://games-105.github.io/ppt/02%20-%20Math%20Background.pdf).
