import java.util.Scanner;
import java.util.regex.*;

// 注意类名必须为 Main, 不要有任何 package xxx 信息
public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String s = in.nextLine();
        String pattern = in.nextLine();
        Pattern p = Pattern.compile(pattern);
        if (p.matcher(s).matches()) {
            System.out.println("1");
        } else {
            System.out.println("0");
        }
    }
}