import java.util.List;

public class ArithmeticExpression {
    private final List<ComplexNumber> numbers;
    private final List<Operation> operations;

    public ArithmeticExpression(List<ComplexNumber> numbers, List<Operation> operations) {
        this.numbers = numbers;
        this.operations = operations;
    }

    public ComplexNumber evaluate() {
        ComplexNumber result = numbers.get(0);
        for (int index = 0; index < operations.size(); index++) {
            result = operations.get(index).apply(result, numbers.get(index + 1));
        }
        return result;
    }
}
