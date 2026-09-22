
# <img src="man/figures/logo.svg" align="right" height="139" /> R package pomdpSolve - Interface to ‘pomdp-solve’ for Partially Observable Markov Decision Processes

[![Package on
CRAN](https://www.r-pkg.org/badges/version/pomdpSolve)](https://CRAN.R-project.org/package=pomdpSolve)
[![CRAN RStudio mirror
downloads](https://cranlogs.r-pkg.org/badges/pomdpSolve)](https://CRAN.R-project.org/package=pomdpSolve)
![License](https://img.shields.io/cran/l/pomdpSolve) [![r-universe
status](https://mhahsler.r-universe.dev/badges/pomdpSolve)](https://mhahsler.r-universe.dev/pomdpSolve)

**Maintainer:** [Michael Hahsler](https://michael.hahsler.net)

Provides [pomdp-solve](http://www.pomdp.org/code/) (Cassandra, 2015) to
solve POMDPs using a variety of algorithms. A convenient interface is
provided in package [pomdp](https://michael.hahsler.net/pomdp/).

To cite package ‘pomdpSolve’ in publications use:

> Hahsler M, Cassandra AR (2025). “Pomdp: A computational infrastructure
> for partially observable Markov decision processes.” *The R Journal*,
> *16*(2), 1-18. ISSN 2073-4859. <doi:10.32614/RJ-2024-021>
> <https://doi.org/10.32614/RJ-2024-021>.

    @Article{,
      title = {Pomdp: A computational infrastructure for partially observable Markov decision processes},
      author = {Michael Hahsler and Anthony R. Cassandra},
      year = {2025},
      journal = {The R Journal},
      volume = {16},
      number = {2},
      pages = {1--18},
      doi = {10.32614/RJ-2024-021},
      issn = {2073-4859},
    }

## Installation

**Stable CRAN version:** Install from within R with

``` r
install.packages("pomdpSolve")
```

**Current development version:** Install from
[r-universe.](https://mhahsler.r-universe.dev/pomdpSolve)

``` r
install.packages("pomdpSolve",
    repos = c("https://mhahsler.r-universe.dev",
              "https://cloud.r-project.org/"))
```

## Usage

Solve a POMDP file that ships with this package in a temporary directory
and read the solution.

``` r
library(pomdpSolve)

old_wd <- setwd(tempdir())
file.copy(system.file("tiger.aaai.POMDP", package = "pomdpSolve"), "./tiger.aaai.POMDP")
```

    ## [1] TRUE

``` r
pomdp_solve("tiger.aaai.POMDP", options = list(method = "grid"), verbose = FALSE)
dir()
```

    ## [1] "tiger.aaai-0.alpha" "tiger.aaai-0.pg"    "tiger.aaai.POMDP"

``` r
read_alpha_file("tiger.aaai-0.alpha")
```

    ##         V1    V2
    ## [1,] -98.5  11.5
    ## [2,] -10.9   6.5
    ## [3,]   1.9   1.9
    ## [4,]   6.5 -10.9
    ## [5,]  11.5 -98.5

``` r
read_pg_file("tiger.aaai-0.pg")
```

    ##   N A Z1 Z2
    ## 1 1 2  3  3
    ## 2 2 1  3  1
    ## 3 3 1  4  2
    ## 4 4 1  5  3
    ## 5 5 3  3  3

``` r
setwd(old_wd)
```

The value function is defined by a set of alpha vectors represented as
rows in a matrix with $V$ components. Each alpha vector corresponds to a
node with the same row number in the policy graph. The policy graph
represents the policy in the form of a data.frame with one row for each
node. Nodes have a node id $N$, the action $A$ defined by the policy and
then for each observation $Z_i$ the id (row) of the policy graph node to
transition to.

A detailed description of the available solver options can be found
[here](https://michael.hahsler.net/pomdpSolve/pomdp-solve_manual).

## References

- Cassandra, A. (2015). pomdp-solve: POMDP Solver Software,
  <http://www.pomdp.org>.
