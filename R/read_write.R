#' Read and Write Files for 'pomdp-solve'
#' 
#' Read and write files for the pomdp-solve executable.
#' 
#' pomdp-solve uses text format for its input and output. The input is a [POMDP file](https://www.pomdp.org/code/pomdp-file-spec.html). The outputs are the following.
#' 
#' **Value Function**
#' 
#' The value function is returned as files with the extension `.alpha` 
#' in the format:
#' 
#' \preformatted{
#' A
#' V1 V2 V3 ... VN
#' 
#' A
#' V1 V2 V3 ... VN
#' 
#' ...
#' }
#' 
#' Where `A` is an action number and the `V1` through `VN` are real values
#' representing the components of a particular vector that has the 
#' associated action. The action number is the 0-based index of 
#' the action as specified in 
#' the input POMDP file. The vector represents the coefficients of a hyperplane
#' representing one facet of the piecewise linear and convex (PWLC) value 
#' function. Note that the length of the lists needs to be equal to the 
#' number of states in the POMDP.
#' 
#' `read_alpha_file()` reads the V components from the file and returns a matrix.
#' 
#' **Policy Graph**
#' 
#' The policy graph is returned as a file with the extension `.pg`.
#' Each line of the file represents one node of the policy graph and 
#' its contents are:
#' 
#' \preformatted{
#' N A  Z1 Z2 Z3 ...
#' ...
#' }
#' 
#' Here `N` is a node ID giving the node a unique name, numbered sequentially 
#' and lining up with the value function vectors in the 
#' corresponding output `.alpha` file above.
#' 
#' The `A` is the action number defined for this node; it is an integer referring 
#' to the the POMDP file actions by its 0-based index number.
#' These are followed by a list of node IDs, one for each observation. Thus the 
#' list will have a length equal to the number of observations in the POMDP. 
#' This list specifies the transitions in the policy graph. The nth number in 
#' the list will be the index of the node that follows this one when the 
#' observation received is `n`.
#'
#' `read_pg_file()` returns a data.frame with the nodes in the policy graph as rows. 
#' 
#' **Terminal Values**
#' 
#' Terminal values can be specified as a single alpha vector.
#' 
#' **Grid-based Solver Specific Files**
#' 
#' The grid-based method can write the used belief points do disk (command line option `-fg_save`). The 
#' file can be read using `read_belief_file()`.
#' 
#' A matrix with belief points can be written using `write_grid_file()`. This file can be used
#  with the command line option `-fg_points`.
#' 
#' Details about the file formats and pomdp-solve can be found in the References section.
#' 
#' See [pomdp_solve()] for examples.
#' 
#' @param file name of the file to read from or to write to.
#' @param belief_points a numeric matrix with the number of states columns. Rows represent belief points. 
#' @param alpha a numeric alpha vector with the length of the number of states.
#' @param digits number of digits used to write files.
#' 
#' @returns  
#' * `read_alpha_file()` returns the value function (alpha vectors) as a matrix. 
#' * `read_pg_file()` returns the policy graph as a data.frame.
#' * `read_belief_file()` returns a matrix if the solver wrote a belief file.
#' * `write_grid_file()` returns nothing.
#' * `write_terminal_values()` returns nothing.
#' 
#' @name read_write
#' @seealso find_pomdp_solve
#' 
#' 
#' @references
#' Anthony R. Cassandra, pomdp-solve documentation, 
#'   \url{https://www.pomdp.org/code/index.html}

#' @importFrom utils read.table
#' 
#' @export
read_alpha_file <- function(file) {
  ## importing alpha file
  alpha <- readLines(file)
  alpha <- alpha[seq(2, length(alpha), 3)]
  alpha <-
    do.call(rbind, lapply(alpha, function(a)
      as.numeric(strsplit(a, " ")[[1]])))
  
  colnames(alpha) <- paste0("V", seq_len(ncol(alpha)))
  
  alpha
  
}

#' @rdname read_write
#' @export
read_pg_file <- function(file) {
  pg <- read.table(
    file,
    header = FALSE,
    sep = "",
    colClasses = "integer",
    na.strings = c("-", "X")
  )
  pg <- pg + 1L # index has to start from 1 not 0
  
  colnames(pg) <- c("N", "A", paste0("Z", seq_len(ncol(pg) - 2L)))
  
  pg
}

#' @rdname read_write
#' @export
read_belief_file <- function(file) {
  if (!grepl("-0\\.belief", file))
    stop("belief file needs to end in -0.belief")
  
  if (!file.exists(file))
    return(NULL)
  
  belief <- as.matrix(read.table(file))
  belief
}

#' @rdname read_write
#' @export
write_grid_file <- function(file, belief_points, digits = 7) {
  if (length(grep(file, '\\.grid')) != 1L)
    stop("terminal values file needs to be <model file without .pomdp>.grid")
  if (!is.matrix(belief_points))
    belief_points <- rbind(belief_points)
  
  cat(.format_number_fixed(belief_points, digits), file = file)
}

#' @rdname read_write
#' @export
write_terminal_values <- function(file, alpha, digits = 7) {
    
  if (!is.matrix(alpha))
    alpha <- rbind(alpha)
  
  # we don't care about the action so we always use "0"
  for (i in seq(nrow(alpha)))
    cat(
      "0",
      paste0(.format_number_fixed(alpha[i, ], digits = digits), collapse = " "),
      "",
      file = file,
      sep = "\n",
      append = i > 1
    )
}




# sprintf wrapper for vectors and matrices
.format_number_fixed <- function(x, digits = 7, debug = "unknown") {
  if (is.null(x))
    stop("missing field ", debug)
  
  if (is.vector(x)) {
    if (!is.numeric(x))
      stop("Write_POMDP expects numbers, but got: ", dQuote(paste(x, collapse = ", ")))
    paste(sprintf(paste0("%.", digits, "f"), x), collapse = " ")
  } else if (is.matrix(x)) {
    paste(apply(
      x,
      MARGIN = 1,
      .format_number_fixed,
      digits = digits
    ),
      collapse = "\n")
  } else
    stop("formating not implemented for ", class(x), " in field ", debug)
}


