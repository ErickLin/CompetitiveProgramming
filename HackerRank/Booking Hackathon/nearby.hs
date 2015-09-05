import Data.Tuple

pi :: (Floating a) => a
pi = 3.14159265359

data Point a b = Point { lat :: a
                       , long :: b
                       } deriving (Eq, Show, Read)

data Attraction i p = Attraction { _id :: i
                                 , loc :: p
                                 } deriving (Eq, Show, Read)

data Guest p v t = Guest{ loc2 :: p
                        , speed :: v
                        , time :: t
                        } deriving (Eq, Show, Read)

degree2radians :: (Floating f) => f -> f
degree2radians = (* (Main.pi / 180));

distanceBetween :: (Floating f) => Point f f -> Point f f -> f
distanceBetween (Point {lat = lat1, long = long1}) (Point {lat = lat2, long = long2}) =
    let earth_radius = 6371
    in earth_radius * acos((sin . degree2radians) lat1 * (sin . degree2radians) lat2
        + (cos . degree2radians) lat1 * (cos . degree2radians) lat2 * cos(degree2radians long2
        - degree2radians long1))

convertToAttraction :: String -> Attraction Int (Point Double Double)
convertToAttraction line =
    let ws = words line
        __id = read (head ws) :: Int
        _lat = read (ws !! 1) :: Double
        _long = read (last ws) :: Double
        _loc = Point {lat = _lat, long = _long}
    in Attraction {_id = __id, loc = _loc}

convertToAttractions :: [String] -> [Attraction Int (Point Double Double)]
convertToAttractions = map convertToAttraction

convertToGuest :: String -> Guest (Point Double Double) Int Int
convertToGuest line =
    let ws = words line
        _lat = read (head ws) :: Double
        _long = read (ws !! 1) :: Double
        _loc2 = Point {lat = _lat, long = _long}
        transport = ws !! 2
        _speed = if transport == "metro" then 20 else if transport == "bike" then 15 else 5
        _time = read (last ws) :: Int
    in Guest {loc2 = _loc2, speed = _speed, time = _time}

convertToGuests :: [String] -> [Guest (Point Double Double) Int Int]
convertToGuests = map convertToGuest

cmpAttractions :: Attraction Int (Point Double Double) -> Attraction Int (Point Double Double)
        -> Point Double Double -> Bool
cmpAttractions a b start
    | distanceBetween (loc a) start == distanceBetween (loc b) start = (_id a) < (_id b)
    | otherwise = distanceBetween (loc a) start < distanceBetween (loc b) start

sort :: Point Double Double -> [Attraction Int (Point Double Double)] -> [Attraction Int (Point Double Double)]
sort p [] = []
sort p (a:as) =
    let less = sort p [x | x <- as, cmpAttractions x a p]
        more = sort p [x | x <- as, cmpAttractions a x p]
    in  less ++ [a] ++ more

solveOne :: Guest (Point Double Double) Int Int -> [Attraction Int (Point Double Double)] -> [Int]
solveOne g as = let maxDist = (fromIntegral $ speed g) * (fromIntegral $ time g) / 60.0
    in map _id $ sort (loc2 g) $ filter (\a -> distanceBetween (loc2 g) (loc a) <= maxDist) as

solveAll :: [Guest (Point Double Double) Int Int] -> [Attraction Int (Point Double Double)] -> [[Int]]
solveAll (g:gs) as = solveOne g as : solveAll gs as
solveAll [] as = []

getLines :: (Integral a) => a -> IO [String]
getLines n = do
    if n > 0
        then do
            line <- getLine
            _lines <- getLines $ n - 1
            return (line:_lines)
        else
            return []

putStrLines :: [String] -> IO ()
putStrLines (s:ss) = do
    putStrLn s
    if ss == []
        then do
            return ()
        else
            putStrLines ss

main :: IO ()
main = do
    nStr <- getLine
    let n = read nStr :: Int
    attractionData <- getLines n
    let attractions = convertToAttractions attractionData
    mStr <- getLine
    let m = read mStr :: Int
    guestData <- getLines m
    let guests = convertToGuests guestData
    putStrLines $ map (foldr1 (\x y -> x ++ " " ++ y) . map show) $ solveAll guests attractions