# Solving a POMDP with 'pomdp-solve'

This function provides a bare bones interface to run pomdp-solve on a
POMDP file. The results can be read with the functions provided in
[read_write](https://michael.hahsler.net/pomdpSolve/reference/read_write.md).

## Usage

``` r
pomdp_solve(pomdp, options = list(), verbose = TRUE)

pomdp_solve_help()
```

## Arguments

- pomdp:

  the POMDP file to solve.

- options:

  a list with options for pomdp-solve.

- verbose:

  logical; show the program text output?

## Value

An integer exit status returned by
[`system2()`](https://rdrr.io/r/base/system2.html): `0` indicates
success, and a nonzero value indicates an error.

## Details

Calling `pomdp_solve()` first cleans results from previous runs and then
executes pomdp-solve with the specified options.

The options are specified in `options` as a list with entries of the
form `<option> = <value>`. `pomdp_solve_help()` displays the available
options. Note that the leading dash is not used on the option name. For
example: `list(method = "grid", epsilon = 0.1)` sets the method option
to grid and epsilon to 0.1. Here is a slightly more [detailed
description of pomdp-solve's
options.](https://michael.hahsler.net/pomdpSolve/pomdp-solve_manual)

## References

Anthony R. Cassandra, pomdp-solve code and documentation,
<https://www.pomdp.org/code/>

Anthony R. Cassandra, pomdp-solve GitHub repository,
<https://github.com/cassandra/pomdp-solve>

## See also

find_pomdp_solve read_write

## Examples

``` r
# display available options
pomdp_solve_help()

# solve a POMDP file that ships with this package in a temporary directory
old_wd <- setwd(tempdir())

file.copy(system.file("tiger.aaai.POMDP", package = "pomdpSolve"), "./tiger.aaai.POMDP")
#> [1] TRUE

# Example 1: run solver to completion
pomdp_solve("tiger.aaai.POMDP", options = list(method = "incprune"))
#> Calling: /home/runner/work/_temp/Library/pomdpSolve/bin//pomdp-solve -method incprune -pomdp tiger.aaai.POMDP 
#> 
dir()
#> [1] "bslib-e9b2b13fa612f50d23e4850d93d60d01"
#> [2] "downlit"                               
#> [3] "tiger.aaai-0.alpha"                    
#> [4] "tiger.aaai-0.pg"                       
#> [5] "tiger.aaai.POMDP"                      
# you can inspect the files with file.show()

# read the raw policy graph (-0 means infinite horizon solution)
read_pg_file("tiger.aaai-0.pg")
#>   N A Z1 Z2
#> 1 1 2  5  5
#> 2 2 1  4  1
#> 3 3 1  5  1
#> 4 4 1  6  2
#> 5 5 1  7  3
#> 6 6 1  8  4
#> 7 7 1  9  5
#> 8 8 1  9  6
#> 9 9 3  5  5

# read the raw value function
read_alpha_file("tiger.aaai-0.alpha")
#>                V1          V2
#>  [1,] -98.5499208  11.4500792
#>  [2,] -12.3030600   6.6603020
#>  [3,] -10.8542987   6.5169374
#>  [4,]  -0.3391277   3.2077906
#>  [5,]   1.9334390   1.9334390
#>  [6,]   3.2077906  -0.3391277
#>  [7,]   6.5169374 -10.8542987
#>  [8,]   6.6603020 -12.3030600
#>  [9,]  11.4500792 -98.5499208

# Example 2: use method finite grid (point-based algorithm) and save the used belief points
pomdp_solve("tiger.aaai.POMDP", options = list(method = "grid", fg_save = TRUE))
#> Calling: /home/runner/work/_temp/Library/pomdpSolve/bin//pomdp-solve -method grid -fg_save true -pomdp tiger.aaai.POMDP 
#> 
dir()
#> [1] "bslib-e9b2b13fa612f50d23e4850d93d60d01"
#> [2] "downlit"                               
#> [3] "tiger.aaai-0.alpha"                    
#> [4] "tiger.aaai-0.belief"                   
#> [5] "tiger.aaai-0.pg"                       
#> [6] "tiger.aaai.POMDP"                      

read_belief_file("tiger.aaai-0.belief")
#>                 V1           V2
#>  [1,] 5.000000e-01 5.000000e-01
#>  [2,] 8.500000e-01 1.500000e-01
#>  [3,] 1.500000e-01 8.500000e-01
#>  [4,] 9.697987e-01 3.020134e-02
#>  [5,] 3.020134e-02 9.697987e-01
#>  [6,] 9.945344e-01 5.465587e-03
#>  [7,] 5.465587e-03 9.945344e-01
#>  [8,] 9.990311e-01 9.688763e-04
#>  [9,] 9.688763e-04 9.990311e-01
#> [10,] 9.998289e-01 1.711147e-04
#> [11,] 1.711147e-04 9.998289e-01
#> [12,] 9.999698e-01 3.020097e-05
#> [13,] 3.020097e-05 9.999698e-01
#> [14,] 9.999947e-01 5.329715e-06
#> [15,] 5.329715e-06 9.999947e-01
#> [16,] 9.999991e-01 9.405421e-07
#> [17,] 9.405421e-07 9.999991e-01
#> [18,] 9.999998e-01 1.659782e-07
#> [19,] 1.659782e-07 9.999998e-01
#> [20,] 1.000000e+00 2.929027e-08
#> [21,] 2.929027e-08 1.000000e+00
#> [22,] 1.000000e+00 5.168871e-09
#> [23,] 5.168871e-09 1.000000e+00
#> [24,] 1.000000e+00 9.121536e-10
#> [25,] 9.121536e-10 1.000000e+00

# Example 3: Stop value iteration after 50 epochs and then continue with a second call
pomdp_solve("tiger.aaai.POMDP", options = list(method = "incprune", horizon = 50))
#> Calling: /home/runner/work/_temp/Library/pomdpSolve/bin//pomdp-solve -method incprune -horizon 50 -pomdp tiger.aaai.POMDP 
#> 
alpha <- read_alpha_file("tiger.aaai-0.alpha")

write_terminal_values("terminal.alpha", alpha)
pomdp_solve("tiger.aaai.POMDP", options = list(method = "incprune", 
  terminal_values = "terminal.alpha"))
#> Calling: /home/runner/work/_temp/Library/pomdpSolve/bin//pomdp-solve -method incprune -terminal_values terminal.alpha -pomdp tiger.aaai.POMDP 
#> 

# return to the old directory
setwd(old_wd)
```
