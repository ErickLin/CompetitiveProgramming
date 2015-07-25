/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: poker
*/
import java.io.*;
import java.util.*;

class poker
{
    static int ranks, cards[], moves, start, longestLength;
    static long numCards;
    static ArrayList<Integer> zeros = new ArrayList<Integer>();
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("poker.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("poker.out")));
        ranks = Integer.parseInt(in.readLine());
        cards = new int[ranks];
        numCards = 0;
        for (int rank = 0; rank < ranks; rank++)
        {
            cards[rank] = Integer.parseInt(in.readLine());
            if (cards[rank] == 0)
                zeros.add(rank);
            else
                numCards += cards[rank];
        }
        in.close();
        moves = 0;
        while (numCards > 0)
        {
            setLongestLength();
            /*System.out.println(start + " " + (start + longestLength - 1));
            for (int i = 0; i < ranks; i++)
                System.out.print(cards[i] + " ");
            System.out.println();*/
            playStraight(start, start + longestLength - 1);
        }
        /*for (int num : cards)
            System.out.print(num + " ");
        System.out.print("\n");*/
        out.println(moves);
        out.close();
        System.exit(0);
    }
    
    //finds the longest chain of ranks in a row that are not empty
    public static void setLongestLength()
    {
        longestLength = 0;
        int st = 0;
        int length = 0;
        for (int i = 0; i < ranks; i++)
        {
            if (cards[i] > 0)
            {
                length++;
                if (length == 1)
                    st = i;
            }
            if (length > longestLength)
            {
                longestLength = length;
                start = st;
            }
            if (cards[i] == 0)
                length = 0;
        }
        /*if (zeros.size() > 0)
        {
            start = 0;
            longestLength = zeros.get(0);
            if (ranks - 1 - zeros.get(zeros.size() - 1) > longestLength)
            {
                start = zeros.get(zeros.size() - 1) + 1;
                longestLength = ranks - 1 - zeros.get(zeros.size() - 1);
            }
            for (int k = 0; k < zeros.size() - 1; k++)
                if (zeros.get(k + 1) - zeros.get(k) > longestLength)
                {
                    start = zeros.get(k) + 1;
                    longestLength = zeros.get(k + 1) - zeros.get(k);
                }
            }
        else
        {
            start = 0;
            longestLength = ranks;
        }*/
    }
    
    /*public static boolean cardsLeft()
    {
        for (int rank = 0; rank < ranks; rank++)
            if (cards[rank] > 0)
                return true;
        return false;
    }*/
    
    public static void playStraight(int i, int j)
    {
        int smallestNum = 100000;
        for (int rank = i; rank <= j; rank++)
            if (cards[rank] < smallestNum)
                smallestNum = cards[rank];
        for (int rank = i; rank <= j; rank++)
        {
            cards[rank] -= smallestNum;
            if (cards[rank] == 0)
            {
                if (zeros.isEmpty() || rank > zeros.get(zeros.size() - 1))
                    zeros.add(rank);
                else if (rank < zeros.get(0))
                    zeros.add(0, rank);
                else loop: for (int k = 0; k < zeros.size() - 1; k++)
                    if (rank > zeros.get(k) && rank < zeros.get(k + 1))
                    {
                        zeros.add(k, rank);
                        break loop;
                    }
            }
        }
        numCards -= (j - i + 1) * smallestNum;
        moves += smallestNum;
    }
}