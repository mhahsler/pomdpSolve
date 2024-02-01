#' @title `r packageDescription("pomdpSolve")$Package`: `r packageDescription("pomdpSolve")$Title`
#'
#' @description Installs an updated version of 'pomdp-solve', a program to solve Partially Observable Markov Decision Processes (POMDPs) using a variety of exact and approximate value iteration algorithms. This package only provides the executable and a few reading routines. A convenient R infrastructure to use the solver is provided in the separate package \pkg{pomdp} ([pomdp::pomdp-package]).
#' 
#' @section Key functions:
#' - Solve a POMDP file with pomdp-solve using [pomdp_solve()].
#' - Read and write files for pomdp-solve (see [read_write]).
#' - Find the pomdp-solve executable using [find_pomdp_solve()].
#' 
#' Package pomdp provides more convenient support to
#' - Define a POMDP using [pomdp::POMDP]
#' - Solve a POMDP using [pomdp::solve_POMDP()]
#'
#' @author Michael Hahsler
#' @docType package
#' @references 
#' Anthony R. Cassandra, pomdp-solve source code GitHub repository,
#' \url{https://github.com/cassandra/pomdp-solve}
#' @name pomdpSolve-package
NULL
