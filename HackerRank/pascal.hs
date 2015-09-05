import Data.Char

main = do
    n <- getLine
    putStrLn $ unlines $ reverse $ tri ((read n :: Int) - 1)

tri :: Int -> [String]
tri 0 = [row 0 0]
tri n = row n n : tri (n - 1)

row :: Int -> Int -> String
row n (-1) = ""
row n c = show (fac n `div` fac c `div` fac (n - c)) ++ ' ' : row n (c - 1)

fac :: (Integral a) => a -> a
fac 0 = 1
fac 1 = 1
fac n = n * fac(n - 1)