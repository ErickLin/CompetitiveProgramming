import java.io.*;
import java.util.*;

public class squares {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(in.readLine());
        for (int i = 0; i < t; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(line.nextToken());
            int b = Integer.parseInt(line.nextToken());
            a = (int) Math.ceil(Math.sqrt(a));
            b = (int) Math.floor(Math.sqrt(b));
            System.out.println(b - a + 1);
        }
        in.close();
        System.exit(0);
    }
}
