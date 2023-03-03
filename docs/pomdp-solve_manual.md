---
title: pomdp-solve Options Available in the R package pomdpSolve
author: Anthony R. Cassandra and Michael Hahsler
output:
  html_document:
    toc: yes
    toc_depth: 3
    toc_float:
      collapsed: yes
      smooth_scroll: no
  pdf_document:
    toc: yes
    toc_depth: '2'
---

# Introduction 

The R package [pomdpSolve](https://github.com/mhahsler/pomdpSolve) installs a modified version of the C program pomdp-solve v5.4 by Antony R. Cassandra. This document contains a short description of the command line options of the program and how they can be used from R.

The options are passed to the program from the command line in the form `pomdp-solve -<option1> <value1> -<options2> <value2> ...`. 
An example command line call looks like `pomdp-solve -pomdp Tiger.pomdp -method grid`.

The R interface in `pomdp_solve(pomdp, options)` accepts a list for `options` with entries of the form `<option> = <value>`.
The same call from R is `pomdp_solve("Tiger.pomdp", options = list(method = "grid"))`. Note that the POMDP filename will be added automatically with the option `pomdp`.

A more convenient interface to solve POMDPs is available in the R package [pomdp](https://github.com/mhahsler/pomdp).

# General Options

Options that control where files are read from.

### `pomdp <filename>` 
Sets the POMDP model input file name to use.

All executions for solution of a POMDP needs a file as input to the solution process. This filename by convention will end with with or ".pomdp" or ".POMDP" and needs to conform to the pomdp-solve file format.

### `stdout <filename>`

Redirect programs stdout to a file of this name.

The pomdp-solve program displays much status and progress information to stdout. If you want to have this redirected to a file instead, provide the file name as this parameter. Not specifying this option will simply make this information go to normal stdout.

### `save_all [true or false (default)]`

Sets whether or not to save every iteration's solution.

Normally, only the final solution is saved to a file, but if you would like to write out the solution to every epoch of value iteration, then set this flag to true. The epoch number will be appended to the filenames of the alpha nad pg files.

### `save_penultimate [true or false (default)]`

Always keep a file with the last completed solution with the suffix `.prev.alpha`

### `o <filename prefix>` (default: pomdp filename)

Define the prefix name for the program solution files.

The result of solving a POMDP is a set of vectors representing the value function and also a policy graph file mapping the solution to the vectors of the previous solution. These files are suffixed with `.alpha` and `.pg` respectively and use the prefix specified here.

### `verbose [many possible values]` (repeatable)

Turns on extra debugging output for a module.

Each main module of pomdp-solve can be separately controlled as far as extra debugging output is concerned. This option can be used more than once to turn on debugging in more than one module. Not all modules produce extra output.
The module names are: context lp global timing stats cmdline main alpha proj crosssum agenda enum twopass witness incprune lpinterface vertexenum mdp pomdp param parsimonious region approx_mcgs zlz_speedup finite_grid.

# Algorithm Options

pomdp-solve offers several algorithms called methods. This section contains parameters specific to the behavior of different methods. 

### `method [enum, twopass, witness, incprune (default), grid]`

Selects the main solution algorithm to use.

The pomdp-solve program implements a number of different algorithms. This selects the one that should be used.

### `enum_purge [none, domonly, normal_prune (default), epsilon_prune]`

The pruning method to use when using the **enum algorithm**.

When using the enumeration method, there will be times where the set of value function components will need to be pruned or purged of useless components. This define the pruning method to use for this algorithm.

### `inc_prune [normal (default), restricted_region, generalized]`

The variation of the **incremental pruning algorithm**.

The incremental pruning algorithm has a number of variations. This parameter selects the variation.

### `fg_type [simplex pairwise search initial (default)]`

**Finite grid method** means to generate belief points.

The finite grid method needs a set of belief points to compute over. 
There are a number of ways to generate this grid, and this parameter selects the technique to use.

### `fg_points <int>` (default: 10000)

Maximal number of belief points to use in **finite grid**.

The finite grid method needs a set of belief points to compute over. There are a number of ways to generate this grid, 
and this parameter selects the maximum number of points that should be generated during this process.

### `fg_save [true or false (default)]`

Whether to save the points used in **finite grid**.

The finite grid method needs a set of belief points to compute over. This parameter can be used to save the used points
in a filed ending in `.belief`.

### `fg_purge [none, domonly, normal_prune (default), epsilon_prune]`

**Finite grid method** means to prune value functions.

Defines the technique to use during pruning when the finite grid method is being used.

### `rand_seed <string>`

Set the random seed for program execution.

For any functionality that requires random numbers, we want to be able to reproduce a given run by executing with the same random number seed. This parameter allows you to set the initial random seed by specifying a string consisting of three integers separated by a colon (e.g., "34523:12987:50732" ). Not setting this value will result in the random seed being pseudo-randomized based on the system clock.

### `force_rounding [true or false]`

Rounds the alpha list.

This flag will force the alpha vector coefficient values to be rounded in accordance with the epsilon value after each iteration.

# Value Iteration Options

Value iteration is used by all methods. The following options control value iteration.

### `stop_delta <double>` (default: 1e-9)

Sets the precision for the stopping criteria check.

When checking the stopping criteria at the end of each value iteration epoch, some of the stopping condition types use a tolerance/precision in their calculations. This parameter allows you to set that precision.

### `stop_criteria [exact, weak (default), bellman]`

Sets the value iteration stopping criteria.

At the end of each epoch of value iteration, a check is done to see whether the solutions have 'converged' to the (near) optimal infinite horizon solution. there are more than one way to determine this stopping condition. The exact semantics of each are not described here at this time.

### `terminal_values <filename>`

Sets the terminal value function for value iteration.

Since value iteration starts solving in reverse order, a terminal value function can be used specify
the start point. If no terminal values are specified, then the start point is a value function where 
the terminal value for states is set to zero.

The file format for the value function input file is identical to the output file format 
of pomdp-solve for `.alpha` files.

Use cases:

* Specifying terminal values for states after the last epoch (see horizon) in finite time horizon problems. Here the 
  value function consists of a single alpha vector specifying the terminal reward for each state.
* Continue a previous value iteration run with the returned alpha vectors as the input. 

### `discount <double>`

Set the discount factor to use in value iteration. It overwrites the discount definition in the POMDP file.

This sets the discount factor to use during value iteration which dictates the relative usefulness of future rewards compared to immediate rewards.

### `horizon <int>`

Sets the number of iterations of value iteration. It overwrites the horizon definition in the POMDP file.

Value iteration is iterative and thus we may want to find 'finite horizon' solutions for various reasons. To make pomdp-solve terminate after a fixed number of iterations (aka epochs) set this value to be some positive number. By default, value iteration will run for as many iterations as it take to 'converge' on the infinite horizon solution.

### `vi_variation [normal (default), zlz, adjustable_epsilon, fixed_soln_size]`

Sets the general category of value iteration to use.

Independent of particular algorithms for computing one iteration of value iteration are a number of variations of value iteration meant to help speed up convergence. Below are the options for each of these variations.

### `history_length <int>`

Sets history window to use for **adjustable epsilon VI**.

When using the 'adjustable_epsilon' value iteration variant, we need to compare solution sizes from the the previous epochs to see whether or not the solutions are staying relatively constant in size. To do this, we need to define a past window length, as well as a tolerance on how much variation in solution size we want to care about. This parameter defines the length of the epoch window history to use when determining whether it is time to adjust the precision of the value iteration solution.

### `start_epsilon <double>`

Sets the starting precision for **adjustable epsilon VI**.

When solving using the 'adjustable_epsilon' method of value iteration, we need to specify both a staring and ending precision. This is the starting precision.

### `end_epsilon <double>`

Sets the ending precision for **adjustable epsilon VI**.

When solving using the 'adjustable_epsilon' method of value iteration, we need to specify both a staring and ending precision. This is the ending precision.

### `epsilon_adjust <double>`

Sets the precision increment for **adjustable epsilon VI**.

When solving using the 'adjustable_epsilon' method of value iteration, we need to specify a staring and ending precision as well as thei increment to use for each adjustment. This is the precision increment.

### `history_delta <int>`

Sets solution size delta to use for **adjustable epsilon VI**.

When using the 'adjustable_epsilon' value iteration variant, we need to compare solution sizes from the the previous epochs to see whether or not the solutions are staying relatively constant in size. To do this, we need to define a past window length, as well as a tolerance on how much variation in solution size we want to care about. This parameter defines the tolerance on what we will consider all solutions to be of the same size.

### `max_soln_size <double>`

Sets the max size for the **fixed solution size VI**.

When solving using the 'fixed_soln_size' method we need to define what the maximal size of a solution we will tolerate. This sets that limit.

# Optimization Options

### `epsilon <double>` (default: 1e-9)

General solution precision level setting.

This is the main precision setting parameter which will effect the preciseness fo the solution procedures.

### `prune_epsilon <double>` (default: 1e-9)

Sets the precision level for the prune operations.

There are a number of ways to prune sets of value function components. Each uses a precision actor which is this parameter.

### `lp_epsilon <double>` (default: 1e-9)

Precision use in linear programs.

Many solution procedures employ linear programming in their algorithms. For those that do, this is the precision level used inside the linear programming routines.

### `fg_epsilon <double>` (default: 1e-9)

Precision used for the finite grid method.

### `dom_check [true (default) or false]`

Controls whether simple domination check is done or not.

There is a computationally simple, but not precision domination check that can be done to discover useless components of a value function. This is often useful, but there are circumstances in which it is best to turn this off.

### `proj_purge [one, domonly, normal_prune (default), epsilon_prune]`

Type of pruning to use for pre-iteration solving.

The first step for most algorithms is to compute the forward projection of the previous iteration solution components. Combinations of these will comprise the current solution. Prior to employing any algorithm to find which combinations are needed (the heart of the POMDP solution algorithms) we can employ a process of pruning the projected set, often reducing the complexity of the algorithms. This parameter decides what type of pruning to use at this step. Details on the semantics of each type of pruning are not yet given here.

### `q_purge [none, domonly, normal_prune (default), epsilon_prune]`

Type of pruning to use for a post-iteration solving.

Some algorithms will separately solve the problem for individual actions, then merge these results together. The individual action solutions are referred to as the "Q-functions". After merging, some pruning process will likely take place, but we can also choose to do a pre-merge pruning of these sets which often simplifies the merging process. This parameter defines the method to use for this pre-merge pruning.

### `witness_points [true or false (default)]`

Whether to include 'witness points' in solving.

Keeping 'witness points' means to track individual points that have been found that gave rise to individual value function components. These can often be used to help speed up the solution process.

### `alg_rand <int>` (default: 0)

How many points to use to seed value function creation.

One can speed up the discovery of the initial shape of the value function by randomly generating points and finding the value function components needed for those points. This technique is used if this parameter has a non-zero value.

### `prune_rand <int>` (default: 0)

How many points to use to seed pruning process.

When pruning sets of value function components, we can use a random set of points to help speed up the pruning process. This parameter, if specified and non-zero, will define the number of random points to use in this way.
