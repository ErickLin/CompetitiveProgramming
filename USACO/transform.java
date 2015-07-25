/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: transform
*/
import java.io.*;
import java.util.*;

class transform
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("transform.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("transform.out")));
        int size = Integer.parseInt(in.readLine());
        Square initialSquare = new Square(size);
        for (int row = 0; row < size; row++)
        {
            String line = in.readLine();
            for (int column = 0; column < size; column++)
                initialSquare.setTile(row, column, line.substring(column, column + 1));
        }
        Square finalSquare = new Square(size);
        for (int row = 0; row < size; row++)
        {
            String line = in.readLine();
            for (int column = 0; column < size; column++)
                finalSquare.setTile(row, column, line.substring(column, column + 1));
        }
        in.close();
        initialSquare.print();
        int output;
        if (initialSquare.equals(finalSquare))
            output = 6;
        else
            output = 7;
        if (initialSquare.rotate(90).equals(finalSquare))
            output = 1;
        else if (initialSquare.rotate(180).equals(finalSquare))
            output = 2;
        else if (initialSquare.rotate(270).equals(finalSquare))
            output = 3;
        else if (initialSquare.reflect().equals(finalSquare))
            output = 4;
        else
        {
            Square newSquare = initialSquare.reflect();
            if (newSquare.rotate(90).equals(finalSquare) || newSquare.rotate(180).equals(finalSquare)
                    || newSquare.rotate(270).equals(finalSquare))
                output = 5;
        }
        out.println(output);
        out.close();
        System.exit(0);
    }
    
    static class Square
    {
        private int size;
        private String[][] tiles;
        
        public Square(int size)
        {
            this.size = size;
            tiles = new String[size][size];
        }
        
        public int getSize()
        {
            return size;
        }
        
        public String getTile(int row, int column)
        {
            return tiles[row][column];
        }
        
        public void setTile(int row, int column, String value)
        {
            tiles[row][column] = value;
        }
        
        public boolean equals(Square other)
        {
            boolean equal = true;
            for (int row = 0; row < getSize(); row++)
                for (int column = 0; column < getSize(); column++)
                    if (!getTile(row, column).equals(other.getTile(row, column)))
                        equal = false;
            return equal;
        }
        
        public Square rotate(int angle)
        {
            Square newSquare = new Square(getSize());
            for (int row = 0; row < getSize(); row++)
                for (int column = 0; column < getSize(); column++)
                {
                    if (angle == 90)
                        newSquare.setTile(column, getSize() - 1 - row, getTile(row, column));
                    else if (angle == 180)
                        newSquare.setTile(getSize() - 1 - row, getSize() - 1 - column, getTile(row, column));
                    else if (angle == 270)
                        newSquare.setTile(getSize() - 1 - column, row, getTile(row, column));
                    else //don't change
                        newSquare.setTile(row, column, getTile(row, column));
                }
            return newSquare;
        }
        
        public Square reflect()
        {
            Square newSquare = new Square(getSize());
            for (int row = 0; row < getSize(); row++)
                for (int column = 0; column < getSize(); column++)
                    newSquare.setTile(row, getSize() - 1 - column, getTile(row, column));
            return newSquare;
        }
        
        public void print()
        {
            for (int row = 0; row < getSize(); row++)
            {
                for (int column = 0; column < getSize(); column++)
                    System.out.print(getTile(row, column) + " ");
                System.out.print("\n");
            }
        }
    }
}