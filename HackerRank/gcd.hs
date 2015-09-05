gcd' :: Integral a => a -> a -> a
gcd' n m
    | n `mod` m == 0 = m
    | m `mod` n == 0 = n
    | n > m = gcd' (n - m) m
    | otherwise = gcd' (m - n) n