/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: msquare
*/

import java.io.*;
import java.util.*;

class msquare {
    public static void main(String[] args) throws IOException {
        double t = System.currentTimeMillis();
        BufferedReader in = new BufferedReader(new FileReader("msquare.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("msquare.out")));
        int[] array = new int[8];
        for (int i = 0; i < 8; i++) {
            array[i] = i + 1;
        }
        Square iniSq = new Square(array, "");
        array = new int[8];
        StringTokenizer line = new StringTokenizer(in.readLine());
        for (int i = 0; i < 8; i++)
            array[i] = Integer.parseInt(line.nextToken());
        Square finalSq = new Square(array, "");
        in.close();
        //System.out.println(finalSq.equals(iniSq.b().c().a().b().c().c().b()));
        boolean[] visited = new boolean[(int) 362881];
        HashSet<Square> memo = new HashSet<Square>();
        PriorityQueue<Square> q = new PriorityQueue<Square>();
        q.add(iniSq);
        while (!q.isEmpty()) {
            Square sq = q.poll();
            if (sq.equals(finalSq)) {
                out.println(sq.seq.length());
                out.println(sq.seq);
                break;
            }
            int factorial = 1;
            int hash = 1;
            for (int i = 0; i < 8; i++) {
                factorial *= i + 1;
                hash += sq.sq[i] * factorial;
            }
            if (!visited[hash]) {
                visited[hash] = true;
                q.add(sq.a());
                q.add(sq.b());
                q.add(sq.c());
            }
        }
        out.close();
        System.out.println(System.currentTimeMillis() - t);
        System.exit(0);
    }
    
    public static class Square implements Comparable<Square> {
        public int[] sq;
        public String seq;
        
        public Square(int[] sq, String seq) {
            this.sq = sq;
            this.seq = seq;
        }
        
        @Override
        public boolean equals(Object other) {
            if (other == null)
                return false;
            if (other instanceof Square) {
                for (int i = 0; i < 8; i++)
                    if (sq[i] != ((Square) other).sq[i])
                        return false;
                return true;
            }
            return false;
        }

        @Override
        public int hashCode() {
            int hash = 7;
            hash = 47 * hash + Arrays.hashCode(this.sq);
            return hash;
        }
        
        @Override
        public int compareTo(Square other) {
            if (seq.length() == other.seq.length())
                return seq.compareTo(other.seq);
            return Integer.valueOf(seq.length()).compareTo(other.seq.length());
        }
        
        @Override
        public String toString() {
            //return Arrays.toString(sq);
            return seq;
        }
        
        public Square a() {
            int[] sq2 = new int[8];
            for (int i = 0; i < 8; i++)
                sq2[i] = sq[7 - i];
            return new Square(sq2, seq + "A");
        }
        
        public Square b() {
            int[] sq2 = new int[8];
            sq2[0] = sq[3];
            sq2[7] = sq[4];
            for (int i = 1; i < 4; i++)
                sq2[i] = sq[i - 1];
            for (int i = 4; i < 7; i++)
                sq2[i] = sq[i + 1];
            return new Square(sq2, seq + "B");
        }
        
        public Square c() {
            int[] sq2 = new int[8];
            sq2[0] = sq[0];
            sq2[1] = sq[6];
            sq2[2] = sq[1];
            sq2[3] = sq[3];
            sq2[4] = sq[4];
            sq2[5] = sq[2];
            sq2[6] = sq[5];
            sq2[7] = sq[7];
            return new Square(sq2, seq + "C");
        }
    }
}
