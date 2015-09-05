main = do
    nStr <- getLine
    let n = (read nStr :: Int)
    line <- getLine
    putStrLn $ show $ lcm' $ map read $ words line

lcm' :: [Int] -> Int
lcm' = foldl1 (\x y -> lcm x y)