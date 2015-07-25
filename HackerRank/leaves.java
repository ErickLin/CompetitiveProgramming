import java.io.*;

public class leaves {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        boolean[] eaten = new boolean[n + 1];
        int k = Integer.parseInt(in.readLine());
        for (int i = 0; i < k; i++) {
            int a = Integer.parseInt(in.readLine());
            for (int j = 1; a * j <= n; j++) {
                eaten[a * j] = true;
            }
        }
        in.close();
        int count = 0;
        for (int i = 1; i <= n; i++) {
            if (!eaten[i]) {
                count++;
            }
        }
        System.out.println(count);
        System.exit(0);
    }
}
