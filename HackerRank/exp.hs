solve :: Double -> Double
solve x = sum $ take 10 $ map (\y -> x**y / product [1..y]) [0.0, 1.0..]