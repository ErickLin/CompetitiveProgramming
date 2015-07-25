/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: bteams
*/
import java.io.*;
import java.util.*;

class bteams
{
    static int skillDiff;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("bteams.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("bteams.out")));
        ArrayList<Integer> skillLvls = new ArrayList<Integer>(12);
        for (int i = 0; i < 12; i++)
            skillLvls.add(Integer.parseInt(in.readLine()));
        in.close();
        Collections.sort(skillLvls);
        skillDiff = 9999999;
        enumTeams(skillLvls);
        out.println(skillDiff);
        out.close();
        System.exit(0);
    }
    
    public static void enumTeams(ArrayList<Integer> skillLvls)
    {
        ArrayList<Integer> order = new ArrayList<Integer>(12);
        ArrayList<ArrayList<Integer>> groups = new ArrayList<ArrayList<Integer>>(4);
        recurse(groups, new ArrayList<Integer>(3), skillLvls);
        /*System.out.print("check modification: ");
        for (int i = 0; i < skillLvls.size(); i++)
            System.out.print(skillLvls.get(i) + " ");
        System.out.println();*/
    }
    
    public static void recurse(ArrayList<ArrayList<Integer>> groups, ArrayList<Integer> group, ArrayList<Integer> remaining)
    {
        //System.out.println(groups);
        if (groups.size() == 3)
        {
            /*System.out.print("next order: ");
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    System.out.print(groups.get(i).get(j) + " ");
            System.out.println();*/
            int groupTotal = 0, min = 9999999, max = 0;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                    groupTotal += groups.get(i).get(j);
                if (groupTotal > max)
                    max = groupTotal;
                if (groupTotal < min)
                    min = groupTotal;
                groupTotal = 0;
            }
            for (int i = 0; i < 3; i++)
                groupTotal += remaining.get(i);
            /*if (groups.get(0).equals(groups.get(1)) && groups.get(0).equals(groups.get(2))
                        && groups.get(0).equals(remaining))
                    System.out.println(groupTotal + " " + min + " " + max);*/
            if (groupTotal > max)
                max = groupTotal;
            if (groupTotal < min)
                min = groupTotal;
            if (max - min < skillDiff)
                skillDiff = (max - min);
        }
        else for (int i = 0; i < remaining.size(); i++)
        {
            int num = remaining.get(i);
            //skip repeat numbers
            if (i > 0 && remaining.get(i).equals(remaining.get(i - 1)))
                continue;
            //store numbers only in ascending order
            if (group.size() > 0 && num < group.get(group.size() - 1))
                continue;
            group.add(num);
            remaining.remove(i);
            if (group.size() == 3)
            {
                groups.add(group);
                recurse(groups, new ArrayList<Integer>(3), remaining);
                groups.remove(groups.size() - 1);
            }
            else
                recurse(groups, group, remaining);
            group.remove(group.size() - 1);
            remaining.add(i, num);
            //System.out.println(remaining);
        }
    }
}