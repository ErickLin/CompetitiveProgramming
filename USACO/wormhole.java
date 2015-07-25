/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: wormhole
*/
import java.io.*;
import java.util.*;

class wormhole
{
    static Point[] points;
    static ArrayList<PairCombination> combinations;
    static int numWormholes;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("wormhole.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("wormhole.out")));
        numWormholes = Integer.parseInt(in.readLine());
        points = new Point[numWormholes];
        for (int i = 0; i < numWormholes; i++)
        {
            StringTokenizer line = new StringTokenizer(in.readLine());
            points[i] = new Point(Integer.parseInt(line.nextToken()), Integer.parseInt(line.nextToken()));
        }
        combinations = new ArrayList<PairCombination>();
        for (int i = 1; i < numWormholes; i++)
            enumPairs(0, i, points, new PairCombination());
        int critCombinations = 0;
        for (int i = 0; i < combinations.size(); i++)
        {
            if (combinations.get(i).hasCycle())
            {
                //System.out.println("Cycle\n");
                critCombinations++;
            }
            //else
                //System.out.println("No cycle\n");
        }
        //System.out.println(combinations.size());
        out.println(critCombinations);
        out.close();
        //System.exit(0);
    }
    
    /*adds the Points at indices "a" and "b" as a Pair to the ArrayList<Pair>, and
      forms the rest of the Points in "set" into Pairs*/
    public static void enumPairs(int a, int b, Point[] set, PairCombination combination)
    {
        //copies the given PairCombination
        PairCombination newCombination = new PairCombination(combination);
        newCombination.add(new Pair(set[a], set[b]));
        if (set.length > 2)
        {
            //form a new array of Points identical to the previous, minus a pairing
            Point[] subset = new Point[set.length - 2];
            int subIndex = 0;
            for (int index = 0; index < set.length; index++)
            {
                if (index != a && index != b)
                {
                    subset[subIndex] = set[index];
                    subset[subIndex] = set[index];
                    subIndex++;
                }
            }
            for (int i = 1; i < subset.length; i++)
                enumPairs(0, i, subset, newCombination);
        }
        else
        {
            combinations.add(newCombination);
            //System.out.println(newCombination.toString());
        }
    }
    
    public static class Point
    {
        private int x, y;
        
        public Point(int xVal, int yVal)
        {
            x = xVal;
            y = yVal;
        }
        
        public int getX()
        {
            return x;
        }
        
        public int getY()
        {
            return y;
        }
        
        public boolean equals(Point other)
        {
            if (getX() == other.getX() && getY() == other.getY())
                return true;
            return false;
        }
        
        public String toString()
        {
            return "(" + x + ", " + y + ")";
        }
    }
    
    public static class Pair
    {
        private Point points[];
        
        public Pair(Point[] p)
        {
            points = new Point[2];
            points[0] = p[0];
            points[1] = p[1];
        }
        
        public Pair(Point p0, Point p1)
        {
            points = new Point[2];
            points[0] = p0;
            points[1] = p1;
        }
        
        public Point getPoint0()
        {
            return points[0];
        }
        
        public Point getPoint1()
        {
            return points[1];
        }
        
        public Point getConjugatePoint(Point point)
        {
            if (point.equals(getPoint0()))
                return getPoint1();
            if (point.equals(getPoint1()))
                return getPoint0();
            return null;
        }
        
        public String toString()
        {
            return points[0].toString() + "-" + points[1].toString();
        }
    }
    
    public static class PairCombination
    {
        private ArrayList<Pair> pairs;
        
        public PairCombination()
        {
            pairs = new ArrayList<Pair>();
        }
        
        public PairCombination(PairCombination other)
        {
            pairs = (ArrayList<Pair>)other.getPairs().clone();
        }
        
        public Pair get(int index)
        {
            return pairs.get(index);
        }
        
        public void add(Pair pair)
        {
            pairs.add(pair);
        }
        
        public ArrayList<Pair> getPairs()
        {
            return pairs;
        }
        
        public boolean hasCycle()
        {
            Point[] points = new Point[pairs.size() * 2];
            HashMap<Point,Pair> map = new HashMap<Point,Pair>();
            //get all points, associating them with their respective pairs
            for (int i = 0; i < pairs.size(); i++)
            {
                Point point0 = pairs.get(i).getPoint0();
                points[i * 2] = point0;
                Point point1 = pairs.get(i).getPoint1();
                points[i * 2 + 1] = point1;
                map.put(point0, pairs.get(i));
                map.put(point1, pairs.get(i));
            }
            //go through with all possible starting points
            for (int i = 0; i < points.length; i++)
            {
                Point startPoint = points[i];
                Point currentPoint = map.get(startPoint).getConjugatePoint(startPoint);
                //run through each cycle
                for (int j = 0; j < points.length; j++)
                {
                    //System.out.print(currentPoint.toString() + "->");
                    int dist = -1;
                    Point rightPoint = null;
                    //find the next available point
                    for (int k = 0; k < points.length; k++)
                    {
                        if (points[k].getY() == currentPoint.getY() && points[k].getX() > currentPoint.getX()
                                && (dist == -1 || points[k].getX() - currentPoint.getX() < dist))
                        {
                            dist = points[k].getX() - currentPoint.getX();
                            rightPoint = points[k];
                        }
                    }
                    if (rightPoint == null)
                        break;
                    else
                        currentPoint = rightPoint;
                    //ending back at the start constitutes a cycle
                    if (currentPoint.equals(startPoint))
                        return true;
                    currentPoint = map.get(currentPoint).getConjugatePoint(currentPoint);
                }
            }
            return false;
        }
        
        public String toString()
        {
            String string = " || ";
            for (int i = 0; i < pairs.size(); i++)
                string += pairs.get(i).toString() + " || ";
            return string;
        }
    }
}