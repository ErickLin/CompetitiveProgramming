import java.util.*;

public class Graham {
    static final int MAX = 99999999;
    static Point start;
    
    public static void main(String[] args) {
        Point[] pts = new Point[6];
        pts[0] = new Point(0, 0);
        pts[1] = new Point(0, 5);
        pts[2] = new Point(-1, 4);
        pts[3] = new Point(-1, 1);
        pts[4] = new Point(-2, 4);
        pts[5] = new Point(-3, 5);
        ArrayList<Point> convexHull = graham(pts);
        for (Point p : convexHull) {
            System.out.println(p);
        }
    }
    
    public static ArrayList<Point> graham(Point[] pts) {
        int minY = MAX;
        int minX = MAX;
        for (Point pt : pts) {
            if (pt.y == minY) {
                if (pt.x < minX) {
                    minX = pt.x;
                    start = pt;
                }
            }
            if (pt.y < minY) {
                minY = pt.y;
                minX = pt.x;
                start = pt;
            }
        }
        //sort by polar angle
        Arrays.sort(pts, new Comparator<Point>() {
            @Override
            public int compare(Point p1, Point p2) {
                if (p1.y == start.y && p2.y == start.y)
                    return new Integer(p1.x).compareTo(p2.y);
                else if (p1.y == start.y)
                    return -1;
                else if (p2.y == start.y)
                    return 1;
                double angle1 = Math.atan(((double) (p1.y - start.y)) / (p1.x - start.x)) * 180 / Math.PI;
                if (angle1 < 0)
                    angle1 += 180;
                double angle2 = Math.atan(((double) (p2.y - start.y)) / (p2.x - start.x)) * 180 / Math.PI;
                if (angle2 < 0)
                    angle2 += 180;
                //System.out.println(p1 + " " + angle1);
                //System.out.println(p2 + " " + angle2);
                return new Double(angle1).compareTo(angle2);
            }
        });
        ArrayList<Point> convexHull = new ArrayList<Point>();
        convexHull.add(start);
        convexHull.add(pts[1]);
        for (int i = 2; i < pts.length; i++) {
            //determinant for triangle formed by points that make clockwise turn or are collinear
            while (convexHull.size() >= 2 && det(convexHull.get(convexHull.size() - 2), convexHull.get(convexHull.size() - 1), pts[i]) <= 0) {
                convexHull.remove(convexHull.size() - 1);
            }
            convexHull.add(pts[i]);
        }
        return convexHull;
    }
    
    public static int det(Point p1, Point p2, Point p3) {
        return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    }
    
    public static class Point {
        int x, y;
        
        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
        
        @Override
        public String toString() {
            return "(" + x + ", " + y + ")";
        }
    }
}