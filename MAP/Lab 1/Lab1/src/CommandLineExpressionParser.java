public class CommandLineExpressionParser implements ExpressionParser {
    @Override
    public ArithmeticExpression parse(String[] arguments) {
        ComplexNumber[] numbers = new ComplexNumber[arguments.length];
        Operation[] operations = new Operation[arguments.length];
        int numberCount = 0;
        int operationCount = 0;
        int index = 0;

        // validare 
        if (arguments.length % 6 != 5) {
        throw new IllegalArgumentException("Invalid expression");
        }

        for (int i = 0; i < arguments.length; i += 6) {
            if ((!arguments[i + 1].equals("+") && !arguments[i + 1].equals("-"))
                    || !arguments[i + 3].equals("*")
                    || !arguments[i + 4].equals("i")) {
                throw new IllegalArgumentException("Invalid expression");
            }
        }

        //
        while (index < arguments.length) {
            double real = Double.parseDouble(arguments[index]);
            double imaginary = Double.parseDouble(arguments[index + 2]);

            if (arguments[index + 1].equals("-")) {
                imaginary = -imaginary;
            }

            numbers[numberCount] = new ComplexNumber(real, imaginary);
            numberCount++;
            index += 5;

            if (index < arguments.length) {
                operations[operationCount] = OperationFactory.getInstance().createOperation(arguments[index]);
                operationCount++;
                index++;
            }
        }
        return new ArithmeticExpression(numbers, operations, operationCount);
    }
}
