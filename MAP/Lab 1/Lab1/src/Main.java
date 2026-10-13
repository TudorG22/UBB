public class Main {
    public static void main(String[] args) {
        ExpressionParser parser = new CommandLineExpressionParser();
        try {
            System.out.println(parser.parse(args).evaluate());
        } catch (IllegalArgumentException exception) {
            System.out.println(exception.getMessage());
        }
    }
}
