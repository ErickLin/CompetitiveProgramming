/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: frac1
*/
import java.io.*;
import java.util.*;

class frac1
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("frac1.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("frac1.out")));
        int maxDenom = Integer.parseInt(in.readLine());
        in.close();
        ArrayList<Fraction> fractions = new ArrayList<Fraction>();
        fractions.add(new Fraction(0, 1));
        for (int i = 1; i <= maxDenom; i++)
            for (int j = 1; j <= i; j++)
                if (gcd(i, j) == 1)
                    fractions.add(new Fraction(j, i));
        Collections.sort(fractions);
        for (int i = 0; i < fractions.size(); i++)
            out.println(fractions.get(i));
        out.close();
        System.exit(0);
    }
    
    public static class Fraction implements Comparable<Fraction>
    {
        private int num, denom;
        
        public Fraction(int n, int d)
        {
            num = n;
            denom = d;
        }
        
        @Override
        public int compareTo(Fraction other)
        {
            return new Integer(getNum() * other.getDenom()).compareTo(other.getNum() * getDenom());
        }
        
        public int getNum()
        {
            return num;
        }
        
        public int getDenom()
        {
            return denom;
        }
        
        @Override
        public String toString()
        {
            return num + "/" + denom;
        }
    }
    
    static int gcd(int n1, int n2)
	{
        int lg, sm, r;
		//decides which of the two input numbers is larger and which is smaller
		if (n1 >= n2)
		{
			lg = n1;
			sm = n2;
		}
		else
		{
			lg = n2;
			sm = n1;
		}
		do
		{
			//Step 1: Compute the r when the larger number is divided by the smaller number.
			r = lg % sm;
			//Step 2: Replace the larger number with the smaller number.
			lg = sm;
			//Step 3: Replace the smaller number with the r.
			sm = r;
		}
		while (sm > 0);
        //the larger number at the end is the GCD
        return lg;
	}
}