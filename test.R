log_file <- "set_seed_1234"
file.create(log_file)
log_file <- paste0(getwd(), "/", "set_seed_1234")
set.seed(1234)
f <- readLines(log_file) |> as.numeric()
fc <- readLines("set_seed_1234_c.txt") |> as.numeric()
tail(f)
tail(fc)
identical(f, fc)
