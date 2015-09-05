main = do
    x <- getLine
    y <- getLine
    putStr $ unlines $ map (\str -> show (length str) ++ " " ++ str) (transfer x y "")

transfer :: String -> String -> String -> [String]
transfer x "" p = [reverse p, x, ""]
transfer "" y p = [reverse p, "", y]
transfer (x:xs) (y:ys) p
    | x == y = transfer xs ys (x : p)
    | otherwise = [reverse p, (x:xs), (y:ys)]