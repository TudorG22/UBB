public class ArithmeticExpression {
    private final ComplexNumber[] numbers;
    private final Operation[] operations;
    private final int operationCount;

    public ArithmeticExpression(ComplexNumber[] numbers, Operation[] operations, int operationCount) {
        this.numbers = numbers;
        this.operations = operations;
        this.operationCount = operationCount;
    }

    public ComplexNumber evaluate() {
        ComplexNumber result = numbers[0];
        for (int index = 0; index < operationCount; index++) {
            result = operations[index].apply(result, numbers[index + 1]);
        }
        return result;
    }
}
