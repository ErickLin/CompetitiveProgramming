public class KMP {

    public static void main(String[] args) {
        String s = "ABC ABCDAB ABCDABCDABDE";
        String w = "ABCDABD";
        System.out.println(getMatchingPos(s.toCharArray(), w.toCharArray()));
    }

    public static int getMatchingPos(char[] s, char[] w) {
        int m = 0;
        int i = 0;
        int[] t = buildTable(w);
        while (m + i < s.length) {
            if (w[i] == s[m + i]) {
                if (i == w.length - 1) {
                    return m;
                }
                i++;
            } else {
                if (t[i] > -1) {
                    m += i - t[i];
                    i = t[i];
                } else {
                    i = 0;
                    m++;
                }
            }
        }
        return s.length;
    }

    public static int[] buildTable(char[] w) {
        int[] t = new int[w.length];
        t[0] = -1;
        t[1] = 0;
        int pos = 2;
        int candidatePos = 0;
        while (pos < w.length) {
            if (w[pos - 1] == w[candidatePos]) {
                candidatePos++;
                t[pos] = candidatePos;
                pos++;
            } else if (candidatePos > 0) {
                candidatePos = t[candidatePos];
            } else {
                t[pos] = 0;
                pos++;
            }
        }
        return t;
    }
}