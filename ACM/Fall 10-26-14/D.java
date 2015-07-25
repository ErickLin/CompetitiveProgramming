package fall_10_26_14;

import java.io.*;
import java.util.*;

public class D {
    static final int MAX = 99999999;
    static Point start;
    
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        ArrayList<Point> pts = new ArrayList<Point>(n);
        for (int i = 0; i < n; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            pts.add(new Point(Integer.parseInt(line.nextToken()), Integer.parseInt(line.nextToken())));
        }
        ArrayList<Point> shape = graham(pts);
        System.out.println(area(shape));
        String steps = in.readLine();
        ArrayList<Point> ptsX = new ArrayList<Point>(n);
        ArrayList<Point> ptsY = new ArrayList<Point>(n);
        for (int i = 0; i < n; i++) {
            ptsX.add(pts.get(i));
            ptsY.add(pts.get(i));
        }
        Collections.sort(ptsX, new Comparator<Point>() {
            @Override
            public int compare(Point p1, Point p2) {
                return new Integer(p1.x).compareTo(p2.x);
            }
        });
        Collections.sort(ptsY, new Comparator<Point>() {
            @Override
            public int compare(Point p1, Point p2) {
                return new Integer(p1.y).compareTo(p2.y);
            }
        });
        for (int i = 0; i < n - 3; i++) {
            if (steps.substring(i, i + 1).equals("L")) {
                /*
                int minX = MAX;
                Point pt = null;
                for (Point p : pts) {
                    if (p.x < minX) {
                        minX = p.x;
                        pt = p;
                    }
                }
                pts.remove(pt);
                */
                Point pt = ptsX.remove(0);
                ptsY.remove(pt);
                pts.remove(pt);
                System.out.println(area(graham(pts)));
            }
            if (steps.substring(i, i + 1).equals("R")) {
                /*
                int maxX = 0;
                Point pt = null;
                for (Point p : pts) {
                    if (p.x > maxX) {
                        maxX = p.x;
                        pt = p;
                    }
                }
                */
                Point pt = ptsX.remove(ptsX.size() - 1);
                ptsY.remove(pt);
                pts.remove(pt);
                System.out.println(area(graham(pts)));
            }
            if (steps.substring(i, i + 1).equals("U")) {
                /*
                int maxY = 0;
                Point pt = null;
                for (Point p : pts) {
                    if (p.y > maxY) {
                        maxY = p.y;
                        pt = p;
                    }
                }
                */
                Point pt = ptsY.remove(ptsY.size() - 1);
                ptsX.remove(pt);
                pts.remove(pt);
                System.out.println(area(graham(pts)));
            }
            if (steps.substring(i, i + 1).equals("D")) {
                /*
                int minY = MAX;
                Point pt = null;
                for (Point p : pts) {
                    if (p.y < minY) {
                        minY = p.y;
                        pt = p;
                    }
                }
                */
                Point pt = ptsY.remove(0);
                ptsX.remove(pt);
                pts.remove(pt);
                System.out.println(area(graham(pts)));
            }
        }
        in.close();
        System.exit(0);
    }
    
    public static ArrayList<Point> graham(ArrayList<Point> pts) {
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
        Collections.sort(pts, new Comparator<Point>() {
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
        convexHull.add(pts.get(1));
        for (int i = 2; i < pts.size(); i++) {
            //determinant for triangle formed by points that make clockwise turn or are collinear
            while (convexHull.size() >= 2 && det(convexHull.get(convexHull.size() - 2), convexHull.get(convexHull.size() - 1), pts.get(i)) <= 0) {
                convexHull.remove(convexHull.size() - 1);
            }
            convexHull.add(pts.get(i));
        }
        return convexHull;
    }
    
    public static double area(ArrayList<Point> polygon) {
        double area = 0;
        for (int i = 0; i < polygon.size() - 2; i++) {
            area += Math.abs(det(polygon.get(0), polygon.get(i + 1), polygon.get(i + 2))) / 2;
        }
        return area;
    }
    
    public static double det(Point p1, Point p2, Point p3) {
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
