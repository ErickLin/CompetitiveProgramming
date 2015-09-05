fib :: (Integral a) => a -> a
fib n
    | n <= 1 = 0
    | n == 2 = 1
    | otherwise = fib (n - 2) + fib (n - 1)