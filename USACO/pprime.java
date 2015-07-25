/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: pprime
*/
import java.io.*;
import java.util.*;

class pprime
{
    static ArrayList<Integer> primes, palindromes;
    static final int bound = 100000000;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("pprime.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("pprime.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int a = Integer.parseInt(line.nextToken());
        int b = Integer.parseInt(line.nextToken());
        in.close();
        //only primes up to the square root of the max number are needed
        boolean[] prime = sieve((int)Math.sqrt(bound));
        primes = new ArrayList<Integer>((int)Math.sqrt(bound));
        for (int num = 2; num <= (int)Math.sqrt(bound); num++)
            if (prime[num])
                primes.add(num);
        /*for (int num = 1; num <= (int)Math.sqrt(bound); num++)
            if (prime[num])
                System.out.println(num);*/
        palindromes = new ArrayList<Integer>(99999);
        genOddPals(a, b);
        Collections.sort(palindromes);
        for (int i = 0; i < palindromes.size(); i++)
            if (isPrime(palindromes.get(i)))
                out.println(palindromes.get(i));
        out.close();
        System.exit(0);
    }
    
    //Sieve of Eratosthenes - prime-finding algorithm
    public static boolean[] sieve(int bound)
    {
        boolean[] prime = new boolean[bound + 1];
        for (int num = 2; num <= bound; num++)
            prime[num] = true;
        for (int num = 2; num <= bound; num++)
            if (prime[num])
                for (int n = 2; num * n <= bound; n++)
                    prime[num * n] = false;
        return prime;
    }
    
    //Remember: a prime number is indivisible by all primes less than or equal to its square root
    public static boolean isPrime(int num)
    {
        if (num <= 1)
            return false;
        for (int j = 0; j < primes.size() && primes.get(j) <= (int)Math.sqrt(num); j++)
            if (num % primes.get(j) == 0)
                return false;
        return true;
    }
    
    public static void genOddPals(int low, int high)
    {
        for (int a = 1; a <= 9; a += 2)
        {
            record(a, low, high);
            record(10*a + a, low, high);
            for (int b = 0; b <= 9; b++)
            {
                record(100*a + 10*b + a, low, high);
                record(1000*a + 100*b + 10*b + a, low, high);
                for (int c = 0; c <= 9; c++)
                {
                    record(10000*a + 1000*b + 100*c + 10*b + a, low, high);
                    record(100000*a + 10000*b + 1000*c + 100*c + 10*b + a, low, high);
                    for (int d = 0; d <= 9; d++)
                    {
                        record(1000000*a + 100000*b + 10000*c + 1000*d + 100*c + 10*b + a, low, high);
                        record(10000000*a + 1000000*b + 100000*c + 10000*d + 1000*d + 100*c + 10*b + a, low, high);
                        for (int e = 0; e <= 9; e++)
                        {
                            record(100000000*a + 10000000*b + 1000000*c + 100000*d + 10000*e + 1000*d + 100*c + 10*b + a, low, high);
                        }
                    }
                }
            }
                            
        }
    }
    
    public static void record(int pal, int low, int high)
    {
        if (pal >= low && pal <= high)
            palindromes.add(pal);
    }
    
    /*public static boolean isPrime(int num)
    {
        if (num % 2 == 0)
            return false;
        for (int div = 3; div < num; div += 2)
            if (num % div == 0)
                return false;
        return true;
    }
    * 
    public static boolean isPalindrome(int num)
    {
        String str = Integer.toString(num);
        if (str.equals(new StringBuilder(str).reverse().toString()))
            return true;
        return false;
    }*/
}