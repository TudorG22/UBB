public class OperationFactory {
    private static final OperationFactory instance = new OperationFactory();

    private OperationFactory() { }

    public static OperationFactory getInstance() { return instance; }

    public Operation createOperation(String symbol) {
        return switch (symbol) {
            case "+" -> new Addition();
            case "-" -> new Subtraction();
            case "*" -> new Multiplication();
            case "/" -> new Division();
            default -> throw new IllegalArgumentException("Invalid operation: " + symbol);
        };
    }
}
