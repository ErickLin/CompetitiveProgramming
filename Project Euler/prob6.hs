sumSqDiff :: (Integral a) => a -> a
sumSqDiff n = ((^2) . sum) [1..n] - (sum . map (^2)) [1..n]
