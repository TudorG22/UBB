public class Multiplication implements Operation {
    @Override
    public ComplexNumber apply(ComplexNumber first, ComplexNumber second) {
        double real = first.getReal() * second.getReal() - first.getImaginary() * second.getImaginary();
        double imaginary = first.getReal() * second.getImaginary() + first.getImaginary() * second.getReal();
        return new ComplexNumber(real, imaginary);
    }
}
