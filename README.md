# matrix-recoverability
On the recoverability of matrices based on regular bipartite graphs/code part

We consider random sparse n × m matrices over Finite Fields F[2k], F[p] (p prime),
F[pk] (p prime), used for linear erasure codes. The matrices are balanced or are derived
from balanced matrices via the erasure of rows. The entries are non-zero uniformly distributed
values. The target of the project is to analyze and simulate the rank of the matrices
and the recoverability depending on the number of entries, the size of the matrix, and the
field size pk.
First, we analyze the rank of these matrices over varying finite field size. The analysis
shows that the full rank probability increases with increasing field size, and converges
to 1 − 1q
, for large field sizes q. Then we try to solve the rank problem analytically,
coming up with a rank probability formula for small matrices. Lastly, the analytical
approach provides the foundation for an automated approach, i.e., an algorithm, to solve
the problem. The algorithm is the main result of this work. It is based on conclusions
from the analytical analysis and calculations.
