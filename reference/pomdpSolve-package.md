# pomdpSolve: Interface to 'pomdp-solve' for Partially Observable Markov Decision Processes

Installs an updated version of 'pomdp-solve', a program to solve
Partially Observable Markov Decision Processes (POMDPs) using a variety
of exact and approximate value iteration algorithms. This package only
provides the executable and a few reading routines. A convenient R
infrastructure to use the solver is provided in the separate package
pomdp
([pomdp::pomdp-package](https://rdrr.io/pkg/pomdp/man/pomdp-package.html)).

## Key functions

- Solve a POMDP file with pomdp-solve using
  [`pomdp_solve()`](https://michael.hahsler.net/pomdpSolve/reference/pomdp_solve.md).

- Read and write files for pomdp-solve (see
  [read_write](https://michael.hahsler.net/pomdpSolve/reference/read_write.md)).

- Find the pomdp-solve executable using
  [`find_pomdp_solve()`](https://michael.hahsler.net/pomdpSolve/reference/find_pomdp_solve.md).

Package pomdp provides more convenient support to

- Define a POMDP using
  [pomdp::POMDP](https://rdrr.io/pkg/pomdp/man/POMDP.html)

- Solve a POMDP using
  [`pomdp::solve_POMDP()`](https://rdrr.io/pkg/pomdp/man/solve_POMDP.html)

## References

Anthony R. Cassandra, pomdp-solve source code GitHub repository,
<https://github.com/cassandra/pomdp-solve>

## See also

Useful links:

- <https://github.com/mhahsler/pomdpSolve>

- Report bugs at <https://github.com/mhahsler/pomdpSolve/issues>

## Author

**Maintainer**: Michael Hahsler <mhahsler@lyle.smu.edu>
([ORCID](https://orcid.org/0000-0003-2716-1405)) \[copyright holder\]

Authors:

- Michael Hahsler <mhahsler@lyle.smu.edu>
  ([ORCID](https://orcid.org/0000-0003-2716-1405)) \[copyright holder\]

- Anthony R. Cassandra \[copyright holder\]
