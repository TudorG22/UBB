public class Main {
    public static void main(String[] args) {
        ExpressionParser parser = new CommandLineExpressionParser();
        System.out.println(parser.parse(args).evaluate());
    }
}
