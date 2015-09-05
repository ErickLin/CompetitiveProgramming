import Control.Monad

main = do
    nStr <- getLine
    let n = read nStr :: Int
    words <- replicateM n getLine
    putStrLn $ unlines $ (map (\word -> foldl1 (\x y -> x ++ " " ++ y) $ rotate (length word) word) words)

rotate :: Int -> String -> [String]
rotate 1 (x:xs) = [xs ++ [x]]
rotate i (x:xs) = ((xs ++ [x]) : (rotate (i - 1) (xs ++ [x])))