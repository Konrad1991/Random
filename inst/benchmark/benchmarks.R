R <- function(seed, n) {
  set.seed(seed)
  runif(n)
}

C <- function(seed, n) {
  Random::unif_mt_c(seed, n)
}

CPP <- function(seed, n) {
  Random::unif_mt_cpp(seed, n)
}

CPP_TS <- function(seed, n) { # thread safe
  Random::unif_mt_cpp_parallel(rep(seed, 6), n, 6)
}

n <- 10^6
res <- microbenchmark::microbenchmark(
  R(1234, n),
  C(1234, n),
  CPP(1234, n),
  CPP_TS(1234, n),
  times = 300
)

print(res)
plot(res)
