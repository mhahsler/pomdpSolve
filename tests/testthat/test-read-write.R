test_that("alpha files are read as numeric matrices", {
  file <- withr::local_tempfile(fileext = ".alpha")
  writeLines(c(
    "0", "1.5 -2", "",
    "1", "3 4", ""
  ), file)

  expected <- matrix(
    c(1.5, -2, 3, 4),
    nrow = 2,
    byrow = TRUE,
    dimnames = list(NULL, c("V1", "V2"))
  )

  expect_equal(read_alpha_file(file), expected)
})

test_that("policy graph files use R's one-based indexing", {
  file <- withr::local_tempfile(fileext = ".pg")
  writeLines(c("0 1 0 X", "1 0 - 1"), file)

  expected <- data.frame(
    N = c(1L, 2L),
    A = c(2L, 1L),
    Z1 = c(1L, NA_integer_),
    Z2 = c(NA_integer_, 2L)
  )

  expect_equal(read_pg_file(file), expected)
})

test_that("belief files are validated and read", {
  missing_file <- paste0(withr::local_tempfile(), "-0.belief")

  expect_null(read_belief_file(missing_file))
  expect_error(
    read_belief_file(withr::local_tempfile(fileext = ".belief")),
    "needs to end in -0.belief",
    fixed = TRUE
  )

  misleading_file <- paste0(missing_file, ".backup")
  writeLines("0.5 0.5", misleading_file)
  expect_error(
    read_belief_file(misleading_file),
    "needs to end in -0.belief",
    fixed = TRUE
  )

  writeLines(c("0.25 0.75", "0.6 0.4"), missing_file)
  expect_equal(
    unname(read_belief_file(missing_file)),
    matrix(c(0.25, 0.75, 0.6, 0.4), nrow = 2, byrow = TRUE)
  )
})

test_that("grid files use fixed-width numeric formatting", {
  file <- withr::local_tempfile(fileext = ".grid")
  belief_points <- matrix(c(0.1, 0.9, 0.25, 0.75), nrow = 2, byrow = TRUE)

  expect_invisible(write_grid_file(file, belief_points, digits = 3))
  expect_identical(
    readLines(file, warn = FALSE),
    c("0.100 0.900", "0.250 0.750")
  )

  vector_file <- withr::local_tempfile(fileext = ".grid")
  write_grid_file(vector_file, c(0.2, 0.8), digits = 2)
  expect_identical(readLines(vector_file, warn = FALSE), "0.20 0.80")

  expect_error(
    write_grid_file(withr::local_tempfile(), belief_points),
    "needs to be <model file without .pomdp>.grid",
    fixed = TRUE
  )
  expect_error(
    write_grid_file(
      withr::local_tempfile(fileext = ".grid.backup"),
      belief_points
    ),
    "needs to be <model file without .pomdp>.grid",
    fixed = TRUE
  )
})

test_that("terminal values round-trip through the alpha format", {
  file <- withr::local_tempfile(fileext = ".alpha")
  alpha <- matrix(c(1, 2, 3, 4), nrow = 2, byrow = TRUE)

  expect_invisible(write_terminal_values(file, alpha, digits = 2))
  expect_identical(
    readLines(file),
    c("0", "1.00 2.00", "", "0", "3.00 4.00", "")
  )

  colnames(alpha) <- c("V1", "V2")
  expect_equal(read_alpha_file(file), alpha)
})

test_that("terminal values accept a single vector", {
  file <- withr::local_tempfile(fileext = ".alpha")

  write_terminal_values(file, c(-1, 2.5), digits = 1)

  expect_identical(readLines(file), c("0", "-1.0 2.5", ""))
})
