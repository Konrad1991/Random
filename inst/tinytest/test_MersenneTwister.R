library(Random)
library(tinytest)

n <- 10^5

# Test C version
set.seed(1234)
vals <- runif(n)
vals_own <- Random::unif_mt_c(1234, n)
expect_equal(sum(vals == vals_own), n)

set.seed(9999)
vals <- runif(n)
vals_own <- Random::unif_mt_c(9999, n)
expect_equal(sum(vals == vals_own), n)

set.seed(432145)
vals <- runif(n)
vals_own <- Random::unif_mt_c(432145, n)
expect_equal(sum(vals == vals_own), n)


# Test C++ version
set.seed(1234)
vals <- runif(n)
vals_own <- Random::unif_mt_cpp(1234, n)
expect_equal(sum(vals == vals_own), n)

set.seed(9999)
vals <- runif(n)
vals_own <- Random::unif_mt_cpp(9999, n)
expect_equal(sum(vals == vals_own), n)

set.seed(432145)
vals <- runif(n)
vals_own <- Random::unif_mt_cpp(432145, n)
expect_equal(sum(vals == vals_own), n)


# Test parallised C++ version with one thread
set.seed(1234)
vals <- runif(n)
vals_own <- Random::unif_mt_cpp_parallel(1234, n, 1)
expect_equal(sum(vals == vals_own), n)

set.seed(9999)
vals <- runif(n)
vals_own <- Random::unif_mt_cpp_parallel(9999, n, 1)
expect_equal(sum(vals == vals_own), n)

set.seed(432145)
vals <- runif(n)
vals_own <- Random::unif_mt_cpp_parallel(432145, n, 1)
expect_equal(sum(vals == vals_own), n)


# Test parallised C++ version with 2 threads
set.seed(1234)
vals1 <- runif(n / 2)
set.seed(9999)
vals2 <- runif(n / 2)
vals <- c(vals1, vals2)
vals_own <- Random::unif_mt_cpp_parallel(c(1234, 9999), n, 2)
expect_equal(sum(vals == vals_own), n)


# Test Wichmann Hill
set.seed(1234, kind = "Wich")
vals <- runif(n)
vals_own <- Random::unif_wh_cpp(1234, n)
expect_equal(sum(vals == vals_own), n)

set.seed(9999)
vals <- runif(n)
vals_own <- Random::unif_wh_cpp(9999, n)
expect_equal(sum(vals == vals_own), n)

set.seed(432145)
vals <- runif(n)
vals_own <- Random::unif_wh_cpp(432145, n)
expect_equal(sum(vals == vals_own), n)
