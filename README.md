# quaternion
A bunch of note and code on the topic of Quaternion: applications in graphics and vision 

## Properities
**Definition**. A quaternion is a ring of number which can be written as $`q= x + y\mathbf{i} + z\mathbf{j} + w\mathbf{k}`$, where $`x,y,z,w \in \mathbf{R}`$ and $`\mathbf{i}, \mathbf{j}, \mathbf{k}`$ are complex roots which safisfies $`\mathbf{i}^2=\mathbf{j}^2=\mathbf{k}^2=-1`$ and $`\mathbf{i}\mathbf{j}=\mathbf{k}, \mathbf{j}\mathbf{k}=\mathbf{i},\mathbf{k}\mathbf{i}=\mathbf{j}$ in quaternion production. And in terms of adding, scalaring, the quaternion satisfies the properties of vector sapce, which means,
$$q_1+q_2 = x_1 + y_1\mathbf{i} + z_1\mathbf{j} + w_1\mathbf{k} + x_2 + y_2\mathbf{i} + z_2\mathbf{j} + w_2\mathbf{k} = (x_1 + x_2) + (y_1+y_2)\mathbf{i} + (z_1+z_2)\mathbf{j} + (w_1+w_2)\mathbf{k},$$
$$\lambda(x + y\mathbf{i} + z\mathbf{j} + w\mathbf{k}) = \lambda x + \lambda y\mathbf{i} + \lambda z\mathbf{j} + \lambda w\mathbf{k}\lambda \in \mathbf{R}.$$
And especially, a quaternion has its conjugation, which is $`\*(x + y\mathbf{i} + z\mathbf{j} + w\mathbf{k})=x - y\mathbf{i} - z\mathbf{j} - w\mathbf{k}`$.
We define the norm of a quaternion by 
$$||x + y\mathbf{i} + z\mathbf{j} + w\mathbf{k}|| = \sqrt{x^2+y^2+z^2+w^2}.$$
And of course we have production of two quaternions by the linearity and production rule of $`\{\mathbf{i},\mathbf{j},\mathbf{k}\}`$. And it was worth mentioning that,
$$p, q\in\mathbf{H}, ||pq|| = ||p||\times||q||.$$
And we can prove that,
$$*pp = p*p = ||p||^2$$
So that, 
$$ \frac{*p}{||p||^2} \times p = p \times \frac{*p}{||p||^2} = 1, \Rightarrow p^{-1} = \frac{*p}{||p||^2} \times p.$$


**Vector Representation**.

**Common Properities**.

**Rotation and map**.



## Implementation

### C++ 

### Rust

### Python Binding

## References

