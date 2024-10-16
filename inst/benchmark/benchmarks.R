R <- function(seed, n) {
  set.seed(seed)
  runif(n)
}

C <- function(seed, n) {
  Random::MT(seed, n)
}

CPP <- function(seed, n) {
  Random::MT_CPP(seed, n, 1)
}

CPP_TS <- function(seed, n) { # thread safe
  Random::MT_CPP(seed, n, 6)
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
