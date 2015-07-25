/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: painting
*/
import java.io.*;
import java.util.*;

class painting
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("painting.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("painting.out")));
        int n = Integer.parseInt(in.readLine());
        ArrayList<Enclosure> encs = new ArrayList<Enclosure>(n);
        for (int i = 0; i < n; i++)
        {
            StringTokenizer coords = new StringTokenizer(in.readLine());
            encs.add(new Enclosure(Integer.parseInt(coords.nextToken()), Integer.parseInt(coords.nextToken()), Integer.parseInt(coords.nextToken()), Integer.parseInt(coords.nextToken())));
        }
        Collections.sort(encs);
        in.close();
        //the list of enclosures on the outside
        ArrayList<Enclosure> outside = new ArrayList<Enclosure>(n);
        for (int i = 0; i < n; i++)
        {
            //whether this enclosure should be added to the list of outside enclosures
            boolean willAdd = true;
            for (int j = 0; j < outside.size(); j++)
            {
                //compare enclosures to see if one is inside the other
                if (outside.get(j).contains(encs.get(i)) == 1)
                    willAdd = false;
                if (outside.get(j).contains(encs.get(i)) == -1)
                {
                    outside.remove(j);
                    j--;
                }
            }
            if (willAdd)
            {
                outside.add(encs.get(i));
                //System.out.println(encs.get(i) + "; A = " + encs.get(i).area());
                //System.out.println(outside.size());
            }
        }
        out.println(outside.size());
        out.close();
        System.exit(0);
    }
    
    public static class Enclosure implements Comparable<Enclosure>
    {
        int x1, y1, x2, y2;
        
        public Enclosure(int x1, int y1, int x2, int y2)
        {
            this.x1 = x1;
            this.y1 = y1;
            this.x2 = x2;
            this.y2 = y2;
        }
        
        public int contains(int x1, int y1, int x2, int y2)
        {
            if (this.x1 < x1 && this.x2 > x2 && this.y1 < y1 && this.y2 > y2)
                return 1;
            if (this.x1 > x1 && this.x2 < x2 && this.y1 > y1 && this.y2 < y2)
                return -1;
            else
                return 0;
        }
        
        public int contains(Enclosure other)
        {
            if (x1 < other.x1 && x2 > other.x2 && y1 < other.y1 && y2 > other.y2)
                return 1;
            if (x1 > other.x1 && x2 < other.x2 && y1 > other.y1 && y2 < other.y2)
                return -1;
            else
                return 0;
        }
        
        public int area()
        {
            return ((x2 - x1) / 1000) * ((y2 - y1) / 1000);
        }
        
        @Override
        public int compareTo(Enclosure other)
        {
            return new Integer(other.area()).compareTo(new Integer(area()));
        }
        
        public String toString()
        {
            return "(" + x1 + ", " + y1 + "), " + "(" + x2 + ", " + y2 + ")";
        }
    }
}