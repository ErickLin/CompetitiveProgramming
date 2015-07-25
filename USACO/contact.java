/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: contact
*/

import java.io.*;
import java.util.*;

class contact {
    public static void main(String[] args) throws IOException {
        long t = System.currentTimeMillis();
        BufferedReader in = new BufferedReader(new FileReader("contact.in"));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int lo = Integer.parseInt(line.nextToken());
        int hi = Integer.parseInt(line.nextToken());
        int n = Integer.parseInt(line.nextToken());
        StringBuilder msg = new StringBuilder(in.readLine());
        String ln;
        while ((ln = in.readLine()) != null)
            msg = msg.append(ln);
        in.close();
        String txt = msg.toString();
        //System.out.println(System.currentTimeMillis() - t);
        HashMap<String, Integer> freqs = makePatterns(txt, lo, hi);
        //System.out.println(System.currentTimeMillis() - t);
        ArrayList<Pattern> patterns = toList(freqs);
        //System.out.println(System.currentTimeMillis() - t);
        printSol(n, patterns);
        //System.out.println(System.currentTimeMillis() - t);
        System.exit(0);
    }
    
    public static HashMap<String, Integer> makePatterns(String msg, int lo, int hi) {
        HashMap<String, Integer> freqs = new HashMap<String, Integer>();
        for (int i = 0; i <= msg.length() - lo; i++) {
            for (int len = lo; i + len <= msg.length() && len <= hi; len++) {
                String str = msg.substring(i, i + len);
                if (freqs.containsKey(str))
                    freqs.put(str, freqs.get(str) + 1);
                else {
                    freqs.put(str, 1);
                    for (int len2 = len + 1; i + len2 <= msg.length() && len2 <= hi; len2++) {
                        String str2 = msg.substring(i, i + len2);
                        freqs.put(str2, 1);
                    }
                    break;
                }
            }
            /*
            gen("", len);
            */
        }
        return freqs;
    }
    
    public static ArrayList<Pattern> toList(HashMap<String, Integer> freqs) {
        ArrayList<Pattern> patterns = new ArrayList<Pattern>(freqs.size());
        for (Map.Entry<String, Integer> entry : freqs.entrySet()) {
            patterns.add(new Pattern(entry.getKey(), entry.getValue()));
        }
        Collections.sort(patterns);
        return patterns;
    }
    
    public static void printSol(int n, ArrayList<Pattern> patterns) throws IOException {
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("contact.out")));
        int numOnFreq = 1;
        for (int i = 0; i < patterns.size(); i++) {
            if (i == 0 || patterns.get(i).freq != patterns.get(i - 1).freq) {
                if (n == 0 || patterns.get(i).freq <= 0)
                    //we are done
                    break;
                n--;
                numOnFreq = 1;
                out.println(patterns.get(i).freq);
                //System.out.println(patterns.get(i).freq);
            }
            out.print(patterns.get(i).str);
            //System.out.print(patterns.get(i).str);
            if (numOnFreq % 6 > 0 && (i + 1 < patterns.size()
                    && (patterns.get(i + 1).freq == patterns.get(i).freq))) {
                //System.out.print(" ");
                out.print(" ");
            }
            else {
                //System.out.print("\n");
                out.print("\n");
            }
            numOnFreq++;
        }
        out.close();
    }
    
    static class Pattern implements Comparable<Pattern> {
        String str;
        int freq;
        
        public Pattern(String s, int f) {
            str = s;
            freq = f;
        }
        
        public Pattern(String s) {
            str = s;
            freq = 1;
        }
        
        @Override
        public boolean equals(Object other) {
            if (!(other instanceof Pattern))
                return false;
            return str.equals(((Pattern)other).str);
        }
        
        @Override
        public int compareTo(Pattern other) {
            if (freq == other.freq) {
                if (str.length() == other.str.length())
                    return str.compareTo(other.str);
                else
                    return new Integer(str.length()).compareTo(other.str.length());
            }
            else
                return new Integer(other.freq).compareTo(freq);
        }
        
        @Override
        public String toString() {
            return str + " " + freq;
        }
    }
}