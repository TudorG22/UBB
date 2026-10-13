public class Division implements Operation {
    @Override
    public ComplexNumber apply(ComplexNumber first, ComplexNumber second) {
        double denominator = second.getReal() * second.getReal() + second.getImaginary() * second.getImaginary();
        if (denominator == 0) {
            throw new IllegalArgumentException("Division by zero is not allowed.");
        }
        double real = (first.getReal() * second.getReal() + first.getImaginary() * second.getImaginary()) / denominator;
        double imaginary = (first.getImaginary() * second.getReal() - first.getReal() * second.getImaginary()) / denominator;
        return new ComplexNumber(real, imaginary);
    }
}
