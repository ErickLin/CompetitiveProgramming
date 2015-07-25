import java.io.*;

public class count {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n1 = 0, n2 = 0, digit = 0;
        try {
            n1 = Integer.parseInt(in.readLine());
            if (n1 < 0 || n1 > 150000)
                throw new Exception();
            n2 = Integer.parseInt(in.readLine());
            if (n2 <= n1 || n2 > 150000)
                throw new Exception();
            digit = Integer.parseInt(in.readLine());
            if (digit < 0 || digit > 9)
                throw new Exception();
        } catch (Exception e) {
            System.out.println("Invalid Input");
            System.exit(0);
        }
        int count = 0;
        for (int i = n1; i <= n2; i++) {
            int num = i;
            int count2 = 0;
            if (num == 0 && digit == 0) {
                count2++;
            }
            while (num > 0) {
                if (num % 10 == digit) {
                    count2++;
                }
                num /= 10;
            }
            count += count2;
            System.out.println(i + " " + count2);
        }
        //if (in.readLine() == null)
        System.out.println("Count=" + count);
        //else
        //System.out.println("Invalid Input");
        in.close();
        System.exit(0);
    }
}
