/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: castle
*/
import java.io.*;
import java.util.*;

class castle
{
    static int N, M, roomNums[][], roomNum, roomArea[], maxArea, removeN, removeM, removeDir;
    static boolean[][][] connected;
    
    public static void main(String[] args) throws IOException
    {
        read();
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("castle.out")));
        firstRound();
        out.println(roomNum + "\n" + maxArea);
        secondRound();
        out.print(maxArea + "\n" + (removeN + 1) + " " + (removeM + 1) + " ");
        if (removeDir == 0)
            out.println("W");
        if (removeDir == 1)
            out.println("N");
        if (removeDir == 2)
            out.println("E");
        if (removeDir == 3)
            out.println("S");
        out.close();
        System.exit(0);
    }
    
    public static void read() throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("castle.in"));
        StringTokenizer firstLine = new StringTokenizer(in.readLine());
        M = Integer.parseInt(firstLine.nextToken());
        N = Integer.parseInt(firstLine.nextToken());
        connected = new boolean[N][M][4];
        roomNums = new int[N][M];
        for (int n = 0; n < N; n++)
        {
            StringTokenizer hall = new StringTokenizer(in.readLine());
            for (int m = 0; m < M; m++)
            {
                roomNums[n][m] = -1;
                int wallSum = Integer.parseInt(hall.nextToken());
                //south
                if (wallSum >= 8)
                    wallSum -= 8;
                else if (n < N - 1)
                    connected[n][m][3] = true;
                //east
                if (wallSum >= 4)
                    wallSum -= 4;
                else if (m < M - 1)
                    connected[n][m][2] = true;
                //north
                if (wallSum >= 2)
                    wallSum -= 2;
                else if (n > 0)
                    connected[n][m][1] = true;
                //west
                if (wallSum >= 1)
                    wallSum -= 1;
                else if (m > 0)
                    connected[n][m][0] = true;
            }
        }
        in.close();
    }
    
    public static void firstRound()
    {
        roomNum = 0;
        roomArea = new int[N * M];
        for (int n = 0; n < N; n++)
            for (int m = 0; m < M; m++)
                if (roomNums[n][m] == -1)
                {
                    label(n, m, roomNum);
                    roomNum++;
                }
    }
    
    public static void label(int n, int m, int num)
    {
        roomNums[n][m] = num;
        roomArea[num]++;
        if (roomArea[num] > maxArea)
            maxArea = roomArea[num];
        //west
        if (m > 0 && connected[n][m][0] && roomNums[n][m - 1] == -1)
            label(n, m - 1, num);
        //north
        if (n > 0 && connected[n][m][1] && roomNums[n - 1][m] == -1)
            label(n - 1, m, num);
        //east
        if (m < M - 1 && connected[n][m][2] && roomNums[n][m + 1] == -1)
            label(n, m + 1, num);
        //south
        if (n < N - 1 && connected[n][m][3] && roomNums[n + 1][m] == -1)
            label(n + 1, m, num);
    }
    
    public static void secondRound()
    {
        for (int m = M - 1; m >= 0; m--)
            for (int n = 0; n < N; n++)
            {
                //east
                if (m < M - 1 && roomNums[n][m] != roomNums[n][m + 1])
                {
                    int totalArea = roomArea[roomNums[n][m]] + roomArea[roomNums[n][m + 1]];
                    if (totalArea > maxArea)
                        maxArea = totalArea;
                    if (totalArea == maxArea)
                    {
                        removeN = n;
                        removeM = m;
                        removeDir = 2;
                    }
                }
                //north
                if (n > 0 && roomNums[n][m] != roomNums[n - 1][m])
                {
                    int totalArea = roomArea[roomNums[n][m]] + roomArea[roomNums[n - 1][m]];
                    if (totalArea > maxArea)
                        maxArea = totalArea;
                    if (totalArea == maxArea)
                    {
                        removeN = n;
                        removeM = m;
                        removeDir = 1;
                    }
                }
                /* OLD CODE
                //south
                if (n < N - 1 && !connected[n][m][3])
                {
                    connected[n][m][3] = true;
                    //System.out.println((n + 1) + " " + m);
                    changeLabel(n + 1, m, roomNums[n][m], n + 1, m, 1);
                    connected[n][m][3] = false;
                }
                //west
                if (m > 0 && !connected[n][m][0])
                {
                    connected[n][m][0] = true;
                    //System.out.println(n + " " + (m - 1));
                    changeLabel(n, m - 1, roomNums[n][m], n, m - 1, 2);
                    connected[n][m][0] = false;
                }*/
            }
    }
    
    /*public static void changeLabel(int n, int m, int num, int startN, int startM, int startDir)
    {
        int actualNum = roomNums[n][m];
        if (num == actualNum)
            return;
        int actualArea = roomArea[num];
        //temporarily change the room number
        roomNums[n][m] = num;
        roomArea[num]++;
        if (roomArea[num] > maxArea)
            maxArea = roomArea[num];
        if (roomArea[num] == maxArea)
        {
            removeN = startN;
            removeM = startM;
            removeDir = startDir;
        }
        if (m > 0 && roomNums[n][m - 1] == actualNum)
            changeLabel(n, m - 1, num, startN, startM, startDir);
        if (n > 0 && roomNums[n - 1][m] == actualNum)
            changeLabel(n - 1, m, num, startN, startM, startDir);
        if (m < M - 1 && roomNums[n][m + 1] == actualNum)
            changeLabel(n, m + 1, num, startN, startM, startDir);
        if (n < N - 1 && roomNums[n + 1][m] == actualNum)
            changeLabel(n + 1, m, num, startN, startM, startDir);
        //change the room number back
        roomNums[n][m] = actualNum;
        roomArea[num] = actualArea;
    }
    
    public static void printRoomNums()
    {
        for (int n = 0; n < N; n++)
        {
            for (int m = 0; m < M; m++)
                System.out.print(roomNums[n][m] + " ");
            System.out.println();
        }
        System.out.println();
    }
    
    public static void printConnections()
    {
        for (int n = 0; n < N; n++)
        {
            for (int m = 0; m < M; m++)
            {
                for (int d = 0; d < 4; d++)
                {
                    if (connected[n][m][d])
                        System.out.print("1");
                    else
                        System.out.print("0");
                }
                System.out.print(" ");
            }
            System.out.println();
        }
    }*/
}