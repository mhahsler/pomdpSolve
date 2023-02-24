#' @title `r packageDescription("pomdpSolve")$Package`: `r packageDescription("pomdpSolve")$Title`
#'
#' @description Installs an updated version of 'pomdp-solve', a program to solve Partially Observable Markov Decision Processes (POMDPs) using a variety of exact and approximate value iteration algorithms. This package only provides the executable and a few reading routines. A convenient R infrastructure to use the solver is provided in the separate package \pkg{pomdp} ([pomdp::pomdp-package]).
#' 
#' @section Key functions:
#' - Find and run the pomdp-solve executable using [find_pomdp_solve()].
#' - Define a POMDP using [pomdp::POMDP]
#' - Solve a POMDP using [pomdp::solve_POMDP()]
#'
#' @author Michael Hahsler
#' @docType package
#' @name pomdpSolve-package
NULL
