collatzLen :: (Integral a) => a -> a -> a
collatzLen len 1 = len + 1
collatzLen len n
    | n `mod` 2 == 0 = collatzLen (len + 1) (n `div` 2)
    | otherwise      = collatzLen (len + 1) (3 * n + 1)

maxCollatzLen :: (Integral a) => a -> a
maxCollatzLen n = foldl1 max $ map (collatzLen 0) [1..n]
