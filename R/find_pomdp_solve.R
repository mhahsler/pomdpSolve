#' Find the executable for 'pomdp-solve'
#' 
#' Find the `pomdp-solve` executable 
#' to solve Partially Observable Decision Processes (POMDPs) (Kaelbling et al, 1998)
#' installed by the \pkg{pomdpSolve} package.
#' 
#' This package only provides a direct interface to the executable. 
#' A more convenient and powerful interface is provided by the function
#' [pomdp::solve_POMDP()] in package \pkg{pomdp}.
#' 
#' The executable of `pomdp-solve` in this direct interface needs to be called with
#' [system2()] and runs in a separate process. This way, a failure in the solver will not compromise the
#' R session. `pomdp-solve` creates files with the value function and 
#' the policy graph (see [read_write]).
#' 
#' @returns  
#' returns the path to the 'pomdp-solve' executable as a string or stops with an error.
#' 
#' @aliases pomdp-solve pomdpsolve
#' 
#' @references
#' Kaelbling, L.P., Littman, M.L., Cassandra, A.R. (1998). 
#'   Planning and acting in partially observable stochastic domains. 
#'   _Artificial Intelligence._ **101** (1–2): 99-134.
#'   \doi{10.1016/S0004-3702(98)00023-X}
#' 
#' Anthony R. Cassandra, pomdp-solve documentation, 
#'   \url{https://www.pomdp.org/code/index.html}
#'   
#' @examples 
#' # find the location of the pomdp-solve executable
#' find_pomdp_solve()
#' 
#' # get pomdp-solve options
#' system2(find_pomdp_solve(), args = "-h")
#' @seealso read_write
#' @export
find_pomdp_solve <- function() {
  exec <-
    system.file(file.path(
      "bin",
      .Platform$r_arch,
      c("pomdp-solve", "pomdp-solve.exe")
    ), package = "pomdpSolve")[1]
  if (exec == "")
    stop("pomdp-solve executable not found. Reinstall package 'pomdpSolve'.")
  exec
}