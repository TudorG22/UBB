public class OperationFactory {
    private static final OperationFactory instance = new OperationFactory();

    private OperationFactory() { }

    public static OperationFactory getInstance() { return instance; }

    public Operation createOperation(String symbol) {
        switch (symbol) {
            case "+":
                return new Addition();
            case "-":
                return new Subtraction();
            case "*":
                return new Multiplication();
            case "/":
                return new Division();
            default:
                throw new IllegalArgumentException("Invalid operation: " + symbol);
        }
    }
}
