/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: crypt1
*/
import java.io.*;
import java.util.*;

class crypt1
{
    static ArrayList<Integer> digits;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("crypt1.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("crypt1.out")));
        int numDigits = Integer.parseInt(in.readLine());
        digits = new ArrayList<Integer>(numDigits);
        StringTokenizer line = new StringTokenizer(in.readLine());
        for (int i = 0; i < numDigits; i++)
            digits.add(Integer.parseInt(line.nextToken()));
        in.close();
        int numSol = 0;
        for (int a = 0; a < numDigits; a++)
        for (int b = 0; b < numDigits; b++)
        for (int c = 0; c < numDigits; c++)
        for (int d = 0; d < numDigits; d++)
        {
            int A = digits.get(a);
            int B = digits.get(b);
            int C = digits.get(c);
            int D = digits.get(d);
            int topNum = A*100 + B*10 + C;
            Product part1 = new Product(topNum * D);
            if (part1.isValid() && part1.getLength() == 3)
            {
                for (int e = 0; e < numDigits; e++)
                {
                    int E = digits.get(e);
                    Product part2 = new Product(topNum * E);
                    if (part2.isValid() && part2.getLength() == 3)
                    {
                        Product product = new Product(part1.getValue()*10 + part2.getValue());
                        if (product.isValid() && product.getLength() == 4)
                        {
                            //System.out.println(A + " " + B + " " + C + " " + D + " " + E + ": " + part1 + " " + part2 + ": " + product);
                            numSol++;
                        }
                    }
                }
            }
        }
        out.println(numSol);
        out.close();
        System.exit(0);
    }
    
    public static class Product
    {
        private int value;
        
        public Product(int z)
        {
            value = z;
        }
        
        public int getValue()
        {
            return value;
        }
        
        @Override
        public String toString()
        {
            return Integer.toString(value);
        }
        
        public int getLength()
        {
            int length = 0;
            for (int place = 1; place <= value; place *= 10)
                length++;
            return length;
        }
        
        public int getDigit(int place)
        {
            int z = value;
            return z % (place * 10) / place;
        }
        
        public boolean isValid()
        {
            for (int place = 1; place <= value; place *= 10)
                if (!digits.contains(getDigit(place)))
                    return false;
            return true;
        }
    
        public boolean containsDigit(int digit)
        {
            for (int place = 1; place <= value; place *= 10)
                if (getDigit(place) == digit)
                    return true;
            return false;
        }
    }
}