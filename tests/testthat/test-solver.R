test_that("the installed solver executable can be found", {
  installed_executable <- system.file(
    "bin",
    .Platform$r_arch,
    c("pomdp-solve", "pomdp-solve.exe"),
    package = "pomdpSolve"
  )[1]
  skip_if(installed_executable == "", "requires an installed package")

  executable <- find_pomdp_solve()

  expect_true(nzchar(executable))
  expect_true(file.exists(executable))
  expect_match(basename(executable), "^pomdp-solve(\\.exe)?$")
})

test_that("the bundled tiger model can be solved", {
  installed_executable <- system.file(
    "bin",
    .Platform$r_arch,
    c("pomdp-solve", "pomdp-solve.exe"),
    package = "pomdpSolve"
  )[1]
  skip_if(installed_executable == "", "requires an installed package")

  model <- system.file("tiger.aaai.POMDP", package = "pomdpSolve")
  expect_true(nzchar(model))

  workdir <- withr::local_tempdir()
  withr::local_dir(workdir)
  expect_true(file.copy(model, "tiger.aaai.POMDP"))

  status <- pomdp_solve(
    "tiger.aaai.POMDP",
    options = list(method = "incprune", horizon = 3),
    verbose = FALSE
  )

  expect_identical(status, 0L)
  expect_true(file.exists("tiger.aaai-0.alpha"))
  expect_true(file.exists("tiger.aaai-0.pg"))

  alpha <- read_alpha_file("tiger.aaai-0.alpha")
  policy_graph <- read_pg_file("tiger.aaai-0.pg")

  expect_true(is.matrix(alpha))
  expect_identical(colnames(alpha), c("V1", "V2"))
  expect_equal(nrow(alpha), nrow(policy_graph))
  expect_named(policy_graph, c("N", "A", "Z1", "Z2"))
})
