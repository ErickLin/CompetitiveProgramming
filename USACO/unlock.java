/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: unlock
*/
import java.io.*;
import java.util.*;

class unlock
{
    public static final int LO = 0, HI = 9, MAX = 99999999;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("unlock.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("unlock.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int[] areas = new int[3];
        for (int i = 0; i < areas.length; i++)
            areas[i] = Integer.parseInt(line.nextToken());
        Shape[] shapes = new Shape[areas.length];
        //number of moves that happens before declared impossible
        int maxMoves = 0;
        for (int i = 0; i < areas.length; i++)
        {
            Block[] blocks = new Block[areas[i]];
            int x1 = HI, x2 = LO, y1 = HI, y2 = LO;
            for (int j = 0; j < areas[i]; j++)
            {
                line = new StringTokenizer(in.readLine());
                int x = Integer.parseInt(line.nextToken());
                int y = Integer.parseInt(line.nextToken());
                blocks[j] = new Block(x, y);
                if (x < x1)
                    x1 = x;
                if (x > x2)
                    x2 = x;
                if (y < y1)
                    y1 = y;
                if (y > y2)
                    y2 = y;
            }
            shapes[i] = new Shape(x1, x2, y1, y2, blocks);
            maxMoves += (x2 - x1 + y2 - y1);
        }
        //System.out.println(maxMoves);
        in.close();
        int minMoves = MAX;
        ArrayList<State> states = new ArrayList<State>();
        LinkedList<State> queue = new LinkedList<State>();
        State init = new State(shapes, 0);
        /*for (int i = 0; i < 3; i++)
        {
            System.out.println(init.shapes[i].x1 + " " + init.shapes[i].x2 + " " + init.shapes[i].y1 + " " + init.shapes[i].y2);
            System.out.println(init.shapes[i].free(init.shapes));
        }*/
        /*init.shapes[2].move(1, 0);
        init.shapes[1].move(0, 1);
        init.shapes[0].move(-3, 0);
        for (int i = 0; i < 3; i++)
        {
            System.out.println(init.shapes[i].x1 + " " + init.shapes[i].x2 + " " + init.shapes[i].y1 + " " + init.shapes[i].y2);
            System.out.println(init.shapes[i].free(init.shapes));
        }*/
        shapes = null;
        states.add(init);
        queue.add(init);
        while (!queue.isEmpty())
        {
            State now = queue.poll();
            //System.out.println(queue.size());
            now.visited = true;
            if (now.free())
            {
                /*for (int i = 0; i < 3; i++)
                    System.out.println(now.shapes[i].x1 + " " + now.shapes[i].x2 + " " + now.shapes[i].y1 + " " + now.shapes[i].y2);*/
                if (now.moves < minMoves)
                {
                    minMoves = now.moves;
                    break;
                }
            }
            else for (int i = 0; i < 3; i++)
            {
                Shape shape = now.shapes[i];
                for (int d = -1; d <= 1; d += 2)
                    for (int dir = 0; dir <= 1; dir++)
                    {
                        int dx, dy;
                        if (dir == 0)
                        {
                            dx = d;
                            dy = 0;
                        }
                        else
                        {
                            dx = 0;
                            dy = d;
                        }
                        if (!shape.collision(now.shapes, dx, dy))
                        {
                            if (i == 0)
                            {
                                for (int j = 1; j < 3; j++)
                                    now.shapes[j].move(-dx, -dy);
                            }
                            else
                                shape.move(dx, dy);
                            State then = new State(now);
                            if (i == 0)
                            {
                                for (int j = 1; j < 3; j++)
                                    now.shapes[j].move(dx, dy);
                            }
                            else
                                shape.move(-dx, -dy);
                            //System.out.println((now == then) + " " + now.equals(then));
                            if (!states.contains(then))
                                states.add(then);
                            if (!states.get(states.indexOf(then)).visited && !queue.contains(then))
                                queue.add(then);
                        }
                    }
            }
            if (queue.isEmpty() || now.moves >= maxMoves)
            {
                minMoves = -1;
                break;
            }
        }
        out.println(minMoves);
        out.close();
        System.exit(0);
    }
    
    public static class State
    {
        Shape[] shapes;
        int moves;
        boolean visited;
        
        public State(Shape[] shps, int mvs)
        {
            /*this.xA = xA;
            this.xB = xB;
            this.xC = xC;
            this.yA = yA;
            this.yB = yB;
            this.yC = yC;*/
            shapes = shps;
            moves = mvs;
            visited = false;
        }
        
        public State(State other)
        {
            shapes = new Shape[3];
            for (int i = 0; i < 3; i++)
                shapes[i] = new Shape(other.shapes[i]);
            moves = other.moves + 1;
            visited = false;
        }
        
        public boolean free()
        {
            if (shapes[0].free(shapes) && shapes[1].free(shapes) && shapes[2].free(shapes))
                return true;
            return false;
        }
        
        @Override
        public boolean equals(Object other)
        {
            if (!(other instanceof State))
                return false;
            for (int i = 0; i < 3; i++)
            {
                if (shapes[i].getX1() != ((State)other).shapes[i].getX1()
                        || shapes[i].getY1() != ((State)other).shapes[i].getY1())
                    return false;
            }
            return true;
        }
    }
    
    public static class Shape
    {
        //boundaries
        private int x1, x2, y1, y2;
        //set of blocks that make up this shape
        private Block[] blocks;
        
        public Shape(int x1, int x2, int y1, int y2, Block[] blks)
        {
            this.x1 = x1;
            this.x2 = x2;
            this.y1 = y1;
            this.y2 = y2;
            blocks = blks;
        }
        
        public Shape(Shape other)
        {
            x1 = other.getX1();
            x2 = other.getX2();
            y1 = other.getY1();
            y2 = other.getY2();
            blocks = new Block[other.getBlocks().length];
            for (int i = 0; i < blocks.length; i++)
                blocks[i] = new Block(other.getBlocks()[i]);
        }
        
        public int getX1()
        {
            return x1;
        }
        
        public int getX2()
        {
            return x2;
        }
        
        public int getY1()
        {
            return y1;
        }
        
        public int getY2()
        {
            return y2;
        }
        
        public Block[] getBlocks()
        {
            return blocks;
        }
        
        @Override
        public boolean equals(Object other)
        {
            if (!(other instanceof Shape))
                return false;
            for (int i = 0; i < blocks.length && i < ((Shape)other).getBlocks().length; i++)
                if (!blocks[i].equals(((Shape)other).getBlocks()[i]))
                    return false;
            return true;
        }
        
        public boolean collision(Shape[] shapes, int dx, int dy)
        {
            for (Shape other : shapes)
            {
                if (this == other)
                    continue;
                for (Block a : blocks)
                    for (Block b : other.getBlocks())
                        if (a.x + dx == b.getX() && a.y + dy == b.getY())
                            return true;
            }
            return false;
        }
        
        public void move(int dx, int dy)
        {
            x1 += dx;
            x2 += dx;
            y1 += dy;
            y2 += dy;
            for (Block a : blocks)
                a.move(dx, dy);
        }
        
        public boolean free(Shape[] shapes)
        {
            for (Shape other : shapes)
            {
                if (this == other)
                    continue;
                //if bounding boxes don't intersect
                if (((x1 <= other.getX2() && x1 >= other.getX1()) || (x2 >= other.getX1() && x2 <= other.getX2())) &&
                        ((y1 <= other.getY2() && y1 >= other.getY1()) || ((y2 >= other.getY1()) && y2 <= other.getY2())))
                    return false;
            }
            /*boolean left = false, above = false, right = false, below = false;
            for (Block a : blocks)
                for (Block b : other.getBlocks())
                {
                    if (a.x < b.getX())
                        left = true;
                    if (a.x > b.getX())
                        right = true;
                    if (a.y < b.getY())
                        below = true;
                    if (a.y > b.getY())
                        above = true;
                    if ((left && right) || (below && above))
                        return false;
                }*/
            return true;
        }
    }
    
    public static class Block
    {
        private int x, y;
        
        public Block(int xVal, int yVal)
        {
            x = xVal;
            y = yVal;
        }
        
        public Block(Block other)
        {
            x = other.getX();
            y = other.getY();
        }
        
        public int getX()
        {
            return x;
        }
        
        public int getY()
        {
            return y;
        }
        
        @Override
        public boolean equals(Object other)
        {
            if (!(other instanceof Block))
                return false;
            if (x == ((Block)other).getX() && y == ((Block)other).getY())
                return true;
            return false;
        }
        
        public void move(int dx, int dy)
        {
            x += dx;
            y += dy;
        }
    }
}