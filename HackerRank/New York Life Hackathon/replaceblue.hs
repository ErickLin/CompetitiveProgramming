import Data.Bits

isBLUE :: String -> Bool
isBLUE x = let a = 0 :: Int in length x == 4 && containsLetters x a

containsLetters :: (Integral a, Bits a) => String -> a -> Bool
containsLetters _ 15 = True
containsLetters "" _ = False
containsLetters (x:xs) accum
    | x == 'B'  = containsLetters xs $ accum .|. (1 `shiftL` 0)
    | x == 'L'  = containsLetters xs $ accum .|. (1 `shiftL` 1)
    | x == 'U'  = containsLetters xs $ accum .|. (1 `shiftL` 2)
    | x == 'E'  = containsLetters xs $ accum .|. (1 `shiftL` 3)
    | otherwise = containsLetters xs accum

replaceBLUE :: String -> String
replaceBLUE = unlines . map (unwords . map (\x -> if isBLUE x then "XXXX" else x) . words) . lines