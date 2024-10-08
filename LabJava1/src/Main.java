import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
//        SWAP
//        System.out.println("Enter two numbers to swap:");
//        int x = scanner.nextInt();
//        int y = scanner.nextInt();
//        int temp = x;
//        x=y;
//        y= temp;
//        System.out.println(x);
//        System.out.println(y);

//        ASCII VALUE
//        char charac = scanner.next().charAt(0);
//        int value  = (int) charac;
//
//        System.out.println(value);

//        INDEX of alphabet

//        char charac = scanner.next().charAt(0);
//        char lowercase = Character.toLowerCase(charac);
//        int value  = (int) lowercase;
//        System.out.println(value-96);
//

//         2 strings lexicographically.

//            String word1 = scanner.next();
//            String word2 = scanner.next();
//
//            int result = word1.compareTo(word2);
//            if(result == 0){
//                System.out.println("YES they are equal");
//            }
//            else{
//                System.out.println("NO they are not equal");
//            }

//          Vowels in string

            String [] vowels = {"a", "e", "i", "o", "u"};
            String word = scanner.next();
            int result = 0;
            for(int i=0;i< vowels.length;i++){
                if(word.contains(vowels[i])){
                    result++;
                }
            }
            System.out.println(result);




    }
}
