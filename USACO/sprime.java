/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: sprime
*/
import java.io.*;
import java.util.*;

class sprime
{
    static ArrayList<Integer> primes;
    static int bound;
    static PrintWriter out;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("sprime.in"));
        out = new PrintWriter(new BufferedWriter(new FileWriter("sprime.out")));
        int numDigits = Integer.parseInt(in.readLine());
        in.close();
        bound = (int)Math.pow(10, numDigits);
        boolean[] prime = sieve((int)Math.sqrt(bound));
        primes = new ArrayList<Integer>((int)Math.sqrt(bound));
        for (int num = 2; num <= (int)Math.sqrt(bound); num++)
            if (prime[num])
                primes.add(num);
        /*for (int num = 1; num <= (int)Math.sqrt(bound); num++)
            if (prime[num])
                System.out.println(num);
        for (int i = 0; i < primes.size(); i++)
            System.out.println(primes.get(i));*/
        enumSuperPrimes("", numDigits);
        out.close();
        System.exit(0);
    }
    
    public static void enumSuperPrimes(String strNum, int pos)
    {
        if (strNum.length() == 0)
        {
            enumSuperPrimes(strNum + "2", pos - 1);
            enumSuperPrimes(strNum + "3", pos - 1);
            enumSuperPrimes(strNum + "5", pos - 1);
            enumSuperPrimes(strNum + "7", pos - 1);
        }
        else
        {
            int num = Integer.parseInt(strNum);
            if (isPrime(num))
            {
                if (pos == 0)
                {
                    out.println(num);
                    return;
                }
            }
            else
                return;
            enumSuperPrimes(strNum + "1", pos - 1);
            enumSuperPrimes(strNum + "3", pos - 1);
            enumSuperPrimes(strNum + "7", pos - 1);
            enumSuperPrimes(strNum + "9", pos - 1);
        }
    }
    
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
    
    public static boolean isPrime(int num)
    {
        if (num <= 1)
            return false;
        for (int j = 0; j < primes.size() && primes.get(j) <= (int)Math.sqrt(num); j++)
            if (num % primes.get(j) == 0)
                return false;
        return true;
    }
    
    /*public static boolean isSuperPrime(int n)
    {
        if (isPrime(n))
        {
            if (n < 10)
                return true;
            //System.out.println(n/10);
            return (isSuperPrime(n / 10));
        }
        return false;
    }*/
}