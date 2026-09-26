# Read and Write Files for 'pomdp-solve'

Read and write files for the pomdp-solve executable.

## Usage

``` r
read_alpha_file(file)

read_pg_file(file)

read_belief_file(file)

write_grid_file(file, belief_points, digits = 7)

write_terminal_values(file, alpha, digits = 7)
```

## Arguments

- file:

  name of the file to read from or to write to.

- belief_points:

  a numeric matrix with the number of states columns. Rows represent
  belief points.

- digits:

  number of digits used to write files.

- alpha:

  a numeric alpha vector with the length of the number of states.

## Value

- `read_alpha_file()` returns the value function (alpha vectors) as a
  matrix.

- `read_pg_file()` returns the policy graph as a data.frame.

- `read_belief_file()` returns a matrix if the solver wrote a belief
  file.

- `write_grid_file()` returns nothing.

- `write_terminal_values()` returns nothing.

## Details

pomdp-solve uses text format for its input and output. The input is a
[POMDP file](https://www.pomdp.org/code/pomdp-file-spec.html). The
outputs are the following.

**Value Function**

The value function is returned as files with the extension `.alpha` in
the format:


    A
    V1 V2 V3 ... VN

    A
    V1 V2 V3 ... VN

    ...

Where `A` is an action number and the `V1` through `VN` are real values
representing the components of a particular vector that has the
associated action. The action number is the 0-based index of the action
as specified in the input POMDP file. The vector represents the
coefficients of a hyperplane representing one facet of the piecewise
linear and convex (PWLC) value function. Note that the length of the
lists needs to be equal to the number of states in the POMDP.

`read_alpha_file()` reads the V components from the file and returns a
matrix.

**Policy Graph**

The policy graph is returned as a file with the extension `.pg`. Each
line of the file represents one node of the policy graph and its
contents are:


    N A  Z1 Z2 Z3 ...
    ...

Here `N` is a node ID giving the node a unique name, numbered
sequentially and lining up with the value function vectors in the
corresponding output `.alpha` file above.

The `A` is the action number defined for this node; it is an integer
referring to the the POMDP file actions by its 0-based index number.
These are followed by a list of node IDs, one for each observation. Thus
the list will have a length equal to the number of observations in the
POMDP. This list specifies the transitions in the policy graph. The nth
number in the list will be the index of the node that follows this one
when the observation received is `n`.

`read_pg_file()` returns a data.frame with the nodes in the policy graph
as rows.

**Terminal Values**

Terminal values can be specified as a single alpha vector.

**Grid-based Solver Specific Files**

The grid-based method can write the used belief points do disk (command
line option `-fg_save`). The file can be read using
`read_belief_file()`.

A matrix with belief points can be written using `write_grid_file()`.
This file can be used

Details about the file formats and pomdp-solve can be found in the
References section.

See
[`pomdp_solve()`](https://michael.hahsler.net/pomdpSolve/reference/pomdp_solve.md)
for examples.

## References

Anthony R. Cassandra, pomdp-solve documentation,
<https://www.pomdp.org/code/>

## See also

find_pomdp_solve
