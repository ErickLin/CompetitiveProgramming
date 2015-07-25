/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: maze1
*/
import java.io.*;
import java.util.*;

class maze1
{
    static final int W = 0, N = 1, E = 2, S = 3, maxDist = 38 * 100;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("maze1.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("maze1.out")));
        StringTokenizer firstLine = new StringTokenizer(in.readLine());
        int w = Integer.parseInt(firstLine.nextToken());
        int h = Integer.parseInt(firstLine.nextToken());
        //boolean[][] blocked = new boolean[2 * h + 1][2 * w + 1];
        //boolean[][] exit = new boolean[2 * h + 1][2 * w + 1];
        //shortest distance from vertex to nearest exit
        //int[][] dist = new int[2 * h + 1][2 * w + 1];
        Square[][] grid = new Square[h][w];
        /*PriorityQueue<Square> locs = new PriorityQueue<Square>(h * w, new Comparator<Square>(){
            @Override
            public int compare(Square a, Square b)
            {
                return new Integer(a.dist).compareTo(b.dist);
            }
        });*/
        LinkedList<Square> locs = new LinkedList<Square>();
        for (int r = 0; r < h; r++)
            for (int c = 0; c < w; c++)
                grid[r][c] = new Square(r, c);
        for (int i = 0; i <= 2 * h; i++)
        {
            String line = in.readLine();
            if (i % 2 == 0) for (int j = 1; j < 2 * w; j += 2)
                if (line.substring(j, j + 1).equals(" "))
                {
                    //the square south of this position has an opening to the north
                    if (i / 2 < h)
                    {
                        Square sqSouth = grid[i / 2][(j - 1) / 2];
                        //if bordering the north edge, then this is an exit
                        if (i / 2 == 0)
                        {
                            sqSouth.dist = 1;
                            sqSouth.exit = 1 << N;
                            locs.add(sqSouth);
                        }
                        else //record adjacent square
                            sqSouth.adj |= 1 << N;
                    }
                    //the square north of this position has an opening to the south
                    if (i / 2 > 0)
                    {
                        Square sqNorth = grid[i / 2 - 1][(j - 1) / 2];
                        //if bordering the south edge, then this is an exit
                        if (i / 2 == h)
                        {
                            sqNorth.dist = 1;
                            sqNorth.exit = 1 << S;
                            locs.add(sqNorth);
                        }
                        else
                            sqNorth.adj |= 1 << S;
                    }
                }
            if (i % 2 == 1) for (int j = 0; j <= 2 * w; j += 2)
                if (line.substring(j, j + 1).equals(" "))
                {
                    //the square east of this position has an opening to the west
                    if (j / 2 < w)
                    {
                        Square sqEast = grid[(i - 1) / 2][j / 2];
                        //if bordering the west edge, then this is an exit
                        if (j / 2 == 0)
                        {
                            sqEast.dist = 1;
                            sqEast.exit = 1 << W;
                            locs.add(sqEast);
                        }
                        else
                            sqEast.adj |= 1 << W;
                    }
                    //the square west of this position has an opening to the east
                    if (j / 2 > 0)
                    {
                        Square sqWest = grid[(i - 1) / 2][j / 2 - 1];
                        //if bordering the east edge, then this is an exit
                        if (j / 2 == w)
                        {
                            sqWest.dist = 1;
                            sqWest.exit = 1 << E;
                            locs.add(sqWest);
                        }
                        else
                            sqWest.adj |= 1 << E;
                    }
                }
        }
        in.close();
        /*for (int r = 0; r < h; r++)
        {
            for (int c = 0; c < w; c++)
                System.out.print(grid[r][c].adj + " ");
            System.out.println();
        }*/
        //breadth-first search
        while (locs.size() > 0)
        {
            Square loc = locs.poll();
            loc.visited = true;
            Square neighbor;
            for (int dir = 0; dir < 4; dir++)
                if ((loc.adj & 1 << dir) > 0)
                {
                    if (dir == W)
                        neighbor = grid[loc.row][loc.col - 1];
                    else if (dir == N)
                        neighbor = grid[loc.row - 1][loc.col];
                    else if (dir == E)
                        neighbor = grid[loc.row][loc.col + 1];
                    else
                        neighbor = grid[loc.row + 1][loc.col];
                    if (!neighbor.visited && !locs.contains(neighbor))
                    {
                        neighbor.dist = loc.dist + 1;
                        locs.add(neighbor);
                    }
                }
        }
        int ans = 0;
        for (int r = 0; r < h; r++)
            for (int c = 0; c < w; c++)
                if (grid[r][c].dist > ans)
                    ans = grid[r][c].dist;
        out.println(ans);
        out.close();
        System.exit(0);
    }
    
    public static class Square
    {
        int row, col, adj, dist, exit;
        boolean visited;
        
        public Square(int r, int c)
        {
            row = r;
            col = c;
            //boolean array that shows which adjacent squares are reachable
            adj = 0;
            //shortest distance to the nearest exit
            dist = maxDist;
            //gives direction of any adjacent exit
            exit = 0;
            visited = false;
        }
    }
}