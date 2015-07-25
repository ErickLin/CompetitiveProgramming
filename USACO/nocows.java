/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: nocows
*/
import java.io.*;
import java.util.*;

class nocows
{
    static final int DIV = 9901;
    static int nodes, ht;
    static int[][] dp/*, combs*/;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("nocows.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("nocows.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        nodes = Integer.parseInt(line.nextToken());
        ht = Integer.parseInt(line.nextToken());
        in.close();
        dp = new int[ht + 1][nodes + 1];
        for (int h = 1; h <= ht; h++)
            dp[h][0] = dp[h][1] = 1;
        for (int h = 1; h <= ht; h++)
            for (int n = 1; n <= nodes; n += 2)
                //a = the number of possible sites to place a left subtree
                //n-1-a = remaining sites for the right subtree
                for (int a = 1; a < n; a += 2)
                    dp[h][n] = (dp[h][n] + dp[h-1][a] * dp[h-1][n-1-a]) % DIV;
        out.println((dp[ht][nodes] - dp[ht - 1][nodes] + DIV) % DIV);
        /*
        //min and max number of nodes for height ht
        int min = 2 * ht - 1;
        int max = (int)Math.pow(2, ht) - 1;
        if (nodes % 2 == 1 && nodes >= min && nodes <= max)
        {
            dp = new int[ht + 1][nodes + 1];
            dp[1][1] = 1;
            dp[2][2] = 1;
            combs = new int[nodes + 1][nodes + 1];
            iterate(3, 2, 3);
            int count = 0;
            for (int i = 2; i < nodes + 1; i += 2)
                count = (count + dp[ht][i]) % DIV;
            out.println(count);
        }
        else
            out.println(0);
        for (int lvl = 0; lvl <= ht; lvl++)
            for (int nodes = 0; nodes <= nodes; nodes++)
                if (dp[lvl][nodes] != 0)
                    System.out.println(lvl + " " + nodes + " " + dp[lvl][nodes]
        */
        out.close();
        System.exit(0);
    }
    
    /*
    public static void iterate(int lvl, int nodesLast, int nodesTot)
    {
        for (int nodesNew = 2; nodesNew <= 2*nodesLast; nodesNew += 2)
            if ((lvl < ht && nodesTot + nodesNew < nodes) || (lvl == ht && nodesTot + nodesNew == nodes))
            {
                //if there are fewer nodes than the minimum possible for current subtree
                if (nodesTot + nodesNew < 2 * lvl - 1)
                    continue;
                //more nodes than maximum possible
                if (nodesTot + nodesNew > (1 << lvl) - 1)
                    break;
                //if nodes nodes cannot be reached by the last level
                if (nodesTot + nodesNew + nodesNew * (1 << (ht - lvl)) < nodes)
                    continue;
                //number of combinations for new node placement (nodesLast CHOOSE nodesNew/2)
                int comb = 1;
                if (nodesNew/2 == 1 || nodesNew/2 == nodesLast - 1)
                    comb = nodesLast;
                else if (nodesNew/2 != nodesLast)
                    comb = combinations(nodesLast, nodesNew/2);
                //has all pedigrees of the previous level with previous number of nodes
                dp[lvl][nodesNew] = (dp[lvl][nodesNew] + dp[lvl - 1][nodesLast] * comb) % DIV;
                //System.out.println(lvl + " " + nodesLast + " " + nodesNew + " " + (nodesTot + nodesNew) + " " + dp[lvl][nodesNew]);
                if (lvl != ht)
                    iterate(lvl + 1, nodesNew, nodesTot + nodesNew);
            }
    }
    
    public static int combinations(int nodes, int k)
    {
        if (combs[nodes][k] != 0)
            return combs[nodes][k];
        if (k > nodes / 2)
            k = nodes - k;
        double comb = 1.0;
        ArrayList<Integer> numerator = new ArrayList<Integer>(k);
        ArrayList<Integer> denominator = new ArrayList<Integer>(k - 1);
        for (int i = 0; i < k; i++)
            numerator.add(nodes - i);
        loop: for (int i = 2; i <= k; i++)
        {
            for (int j = 0; j < numerator.size(); j++)
                //cancel out terms
                if (numerator.get(j) % i == 0)
                {
                    if (numerator.get(j).equals(i))
                        numerator.remove(j);
                    else
                        numerator.set(j, numerator.get(j) / i);
                    continue loop;
                }
            denominator.add(i);
        }
        //terms in numerator outnumber those in denominator
        for (int i = 0; i < denominator.size(); i++)
        {
            comb *= numerator.get(numerator.size() - 1 - i);
            comb /= denominator.get(i);
        }
        for (int j = numerator.size() - 1 - denominator.size(); j >= 0; j--)
            comb *= numerator.get(j);
        comb = (int)Math.round(comb);
        if (comb < 1.0)
            comb = 1.0;
        //System.out.println(nodes + " " + k + " " + (int)comb);
        combs[nodes][k] = (int)comb;
        combs[nodes][nodes - k] = (int)comb;
        return (int)comb;
    }
    */
}