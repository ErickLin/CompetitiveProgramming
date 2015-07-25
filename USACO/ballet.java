/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: ballet
*/
import java.io.*;

class ballet
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("ballet.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("ballet.out")));
        int numMoves = Integer.parseInt(in.readLine());
        Dancer bessie = new Dancer();
        boolean tripped = false;
        for (int i = 0; i < numMoves; i++)
        {
            if (bessie.move(in.readLine()) == false)
            {
                tripped = true;
                break;
            }
            //System.out.println(bessie);
        }
        in.close();
        if (tripped)
            out.println("-1");
        else
            out.println(bessie.getMinArea());
        out.close();
        System.exit(0);
    }
    
    public static class Dancer
    {
        //FL, FR, RL, RR in order
        public int[][] feetLocs;
        //current direction (N, E, S, W in order) and maximums
        public int dir, north, south, east, west;
        
        public Dancer()
        {
            feetLocs = new int[4][2];
            feetLocs[0] = new int[]{0, 1};
            feetLocs[1] = new int[]{1, 1};
            feetLocs[2] = new int[]{0, 0};
            feetLocs[3] = new int[]{1, 0};
            dir = 0;
            north = 1;
            south = 0;
            east = 1;
            west = 0;
        }
        
        public boolean move(String instruction)
        {
            String foot = instruction.substring(0, 2);
            String action = instruction.substring(2);
            int footNum = 0;
            if (foot.equals("FR"))
                footNum = 1;
            else if (foot.equals("RL"))
                footNum = 2;
            else if (foot.equals("RR"))
                footNum = 3;
            //pivot around the foot corresponding to "footNum"
            if (action.equals("P"))
            {
                for (int i = 0; i < 4; i++)
                    if (i != footNum)
                    {
                        int xDiff = feetLocs[footNum][0] - feetLocs[i][0];
                        int yDiff = feetLocs[footNum][1] - feetLocs[i][1];
                        feetLocs[i][0] = feetLocs[footNum][0] - yDiff;
                        feetLocs[i][1] = feetLocs[footNum][1] + xDiff;
                    }
                dir = (dir + 1) % 4;
                //System.out.println(dir);
                setMaximums();
                return true;
            }
            else
            {
                int moveDir = dir;
                if (action.equals("R"))
                    moveDir += 1;
                if (action.equals("B"))
                    moveDir += 2;
                if (action.equals("L"))
                    moveDir += 3;
                moveDir %= 4;
                if (moveDir == 0)
                    feetLocs[footNum][1]++;
                if (moveDir == 1)
                    feetLocs[footNum][0]++;
                if (moveDir == 2)
                    feetLocs[footNum][1]--;
                if (moveDir == 3)
                    feetLocs[footNum][0]--;
                for (int i = 0; i < 4; i++)
                    if (i != footNum)
                        if (feetLocs[footNum][0] == feetLocs[i][0] && feetLocs[footNum][1] == feetLocs[i][1])
                            return false;
                setMaximums();
                return true;
            }
        }
        
        //set the new maximum coordinates of the stage after each move
        public void setMaximums()
        {
            for (int i = 0; i < 4; i++)
            {
                if (feetLocs[i][0] > east)
                    east = feetLocs[i][0];
                if (feetLocs[i][0] < west)
                    west = feetLocs[i][0];
                if (feetLocs[i][1] > north)
                    north = feetLocs[i][1];
                if (feetLocs[i][1] < south)
                    south = feetLocs[i][1];
            }
        }
        
        public int getMinArea()
        {
            return (north - south + 1) * (east - west + 1);
        }
        
        @Override
        public String toString()
        {
            return "(" + feetLocs[0][0] + ", " + feetLocs[0][1] + ")"
                    + "(" + feetLocs[1][0] + ", " + feetLocs[1][1] + ")"
                    + "(" + feetLocs[2][0] + ", " + feetLocs[2][1] + ")"
                    + "(" + feetLocs[3][0] + ", " + feetLocs[3][1] + ")";
        }
    }
}