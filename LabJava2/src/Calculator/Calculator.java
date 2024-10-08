package Calculator;

public class Calculator {

    // Method to perform calculation
    public double calculate(int num1, char operation, int num2) {
        switch (operation) {
            case '+':
                return num1 + num2;
            case '-':
                return num1 - num2;
            case '*':
                return num1 * num2;
            case '/':
                if (num2 == 0) {
                    return -1;  // Handle division by zero
                } else {
                    return (double) num1 / num2;  // Division can result in float outcome
                }
            default:
                System.out.println("Invalid operation.");
                return -1;  // Return -1 for invalid operation
        }
    }

    public static void main(String[] args) {
        Calculator calc = new Calculator();

        // Examples
        System.out.println(calc.calculate(1, '+', 2));  // Output: 3
        System.out.println(calc.calculate(2, '*', 4));  // Output: 8
        System.out.println(calc.calculate(10, '/', 2));  // Output: 5.0
        System.out.println(calc.calculate(10, '/', 0));  // Output: -1 (division by zero case)
    }
}
