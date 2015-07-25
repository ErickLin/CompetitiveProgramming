/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: packrec
*/
import java.io.*;
import java.util.*;

class packrec
{
    static ArrayList<Rectangle> rects, bigRects;
    static int minArea = 10000;
    
    public static class Rectangle implements Comparable<Rectangle>
    {
        private int length, height;
        
        public Rectangle(int l, int h)
        {
            length = l;
            height = h;
        }
        
        @Override
        public String toString()
        {
            if (height < length)
                return Integer.toString(height) + " " + Integer.toString(length);
            else
                return Integer.toString(length) + " " + Integer.toString(height);
        }
        
        public int getLength()
        {
            return length;
        }
        
        public int getHeight()
        {
            return height;
        }
        
        /*public boolean equals(Rectangle other)
        {
            if ((length == other.getLength() && height == other.getHeight())
                    || (length == other.getHeight() && height == other.getLength()))
                return true;
            return false;
        }*/
        
        @Override
        public int compareTo(Rectangle other)
        {
            int factor, otherFactor;
            if (length < height)
                factor = length;
            else
                factor = height;
            if (other.getLength() < other.getHeight())
                otherFactor = other.getLength();
            else
                otherFactor = other.getHeight();
            return new Integer(factor).compareTo(otherFactor);
        }
        
        public int area()
        {
            return length * height;
        }
        
        public void rotate()
        {
            int temp = length;
            length = height;
            height = temp;
        }
        
        /*public Rectangle copy()
        {
            return new Rectangle(length, height);
        }
        
        public Rectangle rotate()
        {
            return new Rectangle(height, length);
        }*/
    }
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("packrec.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("packrec.out")));
        rects = new ArrayList<Rectangle>();
        String ln;
        while ((ln = in.readLine()) != null)
        {
            StringTokenizer line = new StringTokenizer(ln);
            rects.add(new Rectangle(Integer.parseInt(line.nextToken()), Integer.parseInt(line.nextToken())));
        }
        in.close();
        permute(0);
        Collections.sort(bigRects);
        out.println(minArea);
        for (int i = 0; i < bigRects.size(); i++)
            out.println(bigRects.get(i));
        out.close();
        System.exit(0);
    }
    
    public static void swapRects(int a, int b)
    {
        Rectangle temp = rects.get(a);
        rects.set(a, rects.get(b));
        rects.set(b, temp);
    }
    
    public static void permute(int n)
    {
        if (n == 4)
            checkRotation(0);
        else for (int i = n; i < 4; i++)
        {
            swapRects(i, n);
            permute(n + 1);
            swapRects(i, n);
        }
    }
    
    public static void checkRotation(int n)
    {
        
        if (n == 4)
            pack();
        else
        {
            //check both rotations of the following rectangle
            checkRotation(n + 1);
            rects.get(n).rotate();
            checkRotation(n + 1);
            rects.get(n).rotate();
        }
    }
    
    public static void pack()
    {
        // 1) all in line
        int l = 0, h = 0;
        for (int i = 0; i < 4; i++)
        {
            l += rects.get(i).getLength();
            h = Math.max(h, rects.get(i).getHeight());
        }
        check(new Rectangle(l, h));

        // 2) 3 on top of 1
        l = 0;
        h = 0;
        for (int i = 0; i < 3; i++)
        {
            l += rects.get(i).getLength();
            h = Math.max(h, rects.get(i).getHeight());
        }
        h += rects.get(3).getHeight();
        l = Math.max(l, rects.get(3).getLength());
        check(new Rectangle(l, h));

        // 3) 2 on top of 1
        l = rects.get(0).getLength() + rects.get(1).getLength();
        h = Math.max(rects.get(0).getHeight(), rects.get(1).getHeight());
        h += rects.get(2).getHeight();
        l = Math.max(l, rects.get(2).getLength());
        l += rects.get(3).getLength();
        h = Math.max(h, rects.get(3).getHeight());
        check(new Rectangle(l, h));

        // 4, 5) 1 on top of 1
        l = rects.get(0).getLength() + rects.get(1).getLength();
        h = Math.max(rects.get(0).getHeight(), rects.get(1).getHeight());
        l += Math.max(rects.get(2).getLength(), rects.get(3).getLength());
        h = Math.max(h, rects.get(2).getHeight() + rects.get(3).getHeight());
        check(new Rectangle(l, h));

        // 6) 2 on top of 2
        l = rects.get(0).getLength() + rects.get(1).getLength();
        h = Math.max(rects.get(0).getHeight() + rects.get(2).getHeight(), rects.get(1).getHeight() + rects.get(3).getHeight());
        //if bottom-left and top-right touch
        if(rects.get(0).getHeight() < rects.get(1).getHeight())
            l = Math.max(l, rects.get(2).getLength()+rects.get(1).getLength());
        //if bottom two touch
        if(rects.get(0).getHeight()+rects.get(2).getHeight() > rects.get(1).getHeight())
            l = Math.max(l, rects.get(2).getLength()+rects.get(3).getLength());
        //if bottom-right and top-left
        if(rects.get(1).getHeight() < rects.get(0).getHeight())
            l = Math.max(l, rects.get(0).getLength()+rects.get(3).getLength());
        //if bottom two are separate
        l = Math.max(l, rects.get(2).getLength());
        l = Math.max(l, rects.get(3).getLength());
        check(new Rectangle(l, h));  
    }
    
    public static void check(Rectangle r)
    {
        if (r.area() < minArea)
        {
            bigRects = new ArrayList<Rectangle>();
            bigRects.add(r);
            minArea = r.area();
        }
        if (r.area() == minArea)
        {
            for (int i = 0; i < bigRects.size(); i++)
                if (r.compareTo(bigRects.get(i)) == 0)
                    return;
            bigRects.add(r);
        }
    }
}