import java.util.ArrayList;
import java.util.List;

public class CommandLineExpressionParser implements ExpressionParser {
    @Override
    public ArithmeticExpression parse(String[] arguments) {
        if (arguments.length == 0) {
            throw new IllegalArgumentException("The expression is empty.");
        }

        List<ComplexNumber> numbers = new ArrayList<>();
        List<Operation> operations = new ArrayList<>();
        int index = 0;

        while (index < arguments.length) {
            NumberRead numberRead = readNumber(arguments, index);
            numbers.add(numberRead.number());
            index = numberRead.nextIndex();

            if (index == arguments.length) {
                break;
            }

            String symbol = arguments[index++];
            operations.add(OperationFactory.getInstance().createOperation(symbol));
            if (index == arguments.length) {
                throw new IllegalArgumentException("A number is missing after " + symbol + ".");
            }
        }
        return new ArithmeticExpression(numbers, operations);
    }

    private NumberRead readNumber(String[] arguments, int index) {
        if (arguments[index].equals("i")) {
            return new NumberRead(new ComplexNumber(0, 1), index + 1);
        }

        double real;
        try {
            real = Double.parseDouble(arguments[index]);
        } catch (NumberFormatException exception) {
            throw new IllegalArgumentException("Invalid number: " + arguments[index]);
        }

        if (index + 2 < arguments.length && arguments[index + 1].equals("*") && arguments[index + 2].equals("i")) {
            return new NumberRead(new ComplexNumber(0, real), index + 3);
        }
        if (index + 2 < arguments.length && isSign(arguments[index + 1]) && arguments[index + 2].equals("i")) {
            double imaginary = arguments[index + 1].equals("-") ? -1 : 1;
            return new NumberRead(new ComplexNumber(real, imaginary), index + 3);
        }
        if (index + 4 < arguments.length && isSign(arguments[index + 1])
                && arguments[index + 3].equals("*") && arguments[index + 4].equals("i")) {
            try {
                double imaginary = Double.parseDouble(arguments[index + 2]);
                if (arguments[index + 1].equals("-")) {
                    imaginary = -imaginary;
                }
                return new NumberRead(new ComplexNumber(real, imaginary), index + 5);
            } catch (NumberFormatException exception) {
                throw new IllegalArgumentException("Invalid number: " + arguments[index + 2]);
            }
        }
        return new NumberRead(new ComplexNumber(real, 0), index + 1);
    }

    private boolean isSign(String value) {
        return value.equals("+") || value.equals("-");
    }

    private record NumberRead(ComplexNumber number, int nextIndex) { }
}
