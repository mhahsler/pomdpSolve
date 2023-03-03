#' Solving a POMDP with 'pomdp-solve'
#'
#' This function provides a bare bones interface to run pomdp-solve on a POMDP
#' file. The results can be read with the function provides in [read_write].
#' 
#' The options are specified in `options` as a list with entries of the form `<option> = <value>`. 
#' `pomdp_solve_help()` displays the available options. Note that the leading dash is not used on the option name. For example:
#' `list(method = "grid", epsilon = 0.1)` sets the method option to grid and epsilon to 0.1.
#' Here is a slightly more [detailed description of pomdp-solve's options.](https://mhahsler.github.io/pomdpSolve/pomdp-solve_manual)
#' 
#' 
#' @param pomdp the POMDP file to solve.
#' @param options a list with options for pomdp-solve. 
#' @param verbose logical; show the program text output?
#'
#' @returns nothing
#'
#' @seealso find_pomdp_solve read_write
#'
#' @references Anthony R. Cassandra, pomdp-solve documentation,
#' \url{https://www.pomdp.org/code/index.html}
#'
#' @examples
#' # display available arguments
#' pomdp_solve_help()
#' 
#' # solve a POMDP file that ships with this package in a temporary directory
#' tmp <- tempdir()
#' old_dir <- setwd(tmp)
#'
#' file.copy(system.file("tiger.aaai.POMDP", package = "pomdpSolve"), "./tiger.aaai.POMDP")
#'
#' pomdp_solve("tiger.aaai.POMDP", options = list(method = "grid"))
#' dir()
#'
#' # read the raw policy graph (-0 means infinite horizon solution)
#' read_pg_file("tiger.aaai-0.pg")
#'
#' # read the raw value function
#' read_alpha_file("tiger.aaai-0.alpha")
#'
#' # return to the old directory
#' setwd(old_dir)
#' @importFrom utils read.table
#'
#' @export
pomdp_solve <- function(pomdp, options = list(), verbose = TRUE) {
  # convert list to arguments and add pomdp
  
  options["pomdp"] <- pomdp
  
  options <- unlist(options)
  options <- as.vector(rbind(paste0("-", names(options)), options))
  
  options[options == "TRUE"] <- "true"
  options[options == "FALSE"] <- "false"
  
  if (verbose)
    cat("Calling:", find_pomdp_solve(), paste(options, collapse = " "), "\n\n") 
   
  system2(find_pomdp_solve(), args = options, stdout = if(verbose) "" else FALSE, stderr = if(verbose) "" else FALSE)
}

#' @rdname pomdp_solve
#' @export
pomdp_solve_help <- function() {
  system2(find_pomdp_solve(), args = "-h")
}

