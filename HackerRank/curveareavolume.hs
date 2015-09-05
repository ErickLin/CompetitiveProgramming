import Text.Printf (printf)

-- This function should return a list [area, volume].
solve :: Int -> Int -> [Int] -> [Int] -> [Double]
solve l r a b = [(/1000) . sum $ map (\x -> sum $ map (\y -> (fromIntegral (a !! y)) * x**(fromIntegral (b !! y)))
        [0, 1 .. length a - 1]) [fromIntegral l, fromIntegral l + 0.001 .. fromIntegral r]
        , (/1000) . sum $ map (\x -> (pi *) $ (**2) $ sum $ map (\y -> ((fromIntegral (a !! y)) * x**(fromIntegral (b !! y))))
        [0, 1 .. length a - 1]) [fromIntegral l, fromIntegral l + 0.001 .. fromIntegral r]]

--Input/Output.
main :: IO ()
main = getContents >>= mapM_ (printf "%.1f\n"). (\[a, b, [l, r]] -> solve l r a b). map (map read. words). lines