# Find the executable for 'pomdp-solve'

Find the `pomdp-solve` executable to solve Partially Observable Decision
Processes (POMDPs) (Kaelbling et al, 1998) installed by the pomdpSolve
package.

## Usage

``` r
find_pomdp_solve()
```

## Value

returns the path to the 'pomdp-solve' executable as a string or stops
with an error.

## Details

This package only provides a direct interface to the executable. A more
convenient and powerful interface is provided by the function
[`pomdp::solve_POMDP()`](https://rdrr.io/pkg/pomdp/man/solve_POMDP.html)
in package pomdp.

The executable of `pomdp-solve` in this direct interface needs to be
called with [`system2()`](https://rdrr.io/r/base/system2.html) and runs
in a separate process. This way, a failure in the solver will not
compromise the R session. `pomdp-solve` creates files with the value
function and the policy graph (see
[read_write](https://michael.hahsler.net/pomdpSolve/reference/read_write.md)).

## References

Kaelbling, L.P., Littman, M.L., Cassandra, A.R. (1998). Planning and
acting in partially observable stochastic domains. *Artificial
Intelligence.* **101** (1–2): 99-134.
[doi:10.1016/S0004-3702(98)00023-X](https://doi.org/10.1016/S0004-3702%2898%2900023-X)

Anthony R. Cassandra, pomdp-solve documentation,
<https://www.pomdp.org/code/>

Anthony R. Cassandra, pomdp-solve source code GitHub repository,
<https://github.com/cassandra/pomdp-solve>

## See also

read_write

## Examples

``` r
# find the location of the pomdp-solve executable
find_pomdp_solve()
#> [1] "/home/runner/work/_temp/Library/pomdpSolve/bin//pomdp-solve"

# get pomdp-solve options
system2(find_pomdp_solve(), args = "-h")

# an example of how to solve a simple POMDP can be found in the man page
# for read_write.
```
