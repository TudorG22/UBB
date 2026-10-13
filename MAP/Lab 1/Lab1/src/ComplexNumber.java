public class ComplexNumber {
    private final double real;
    private final double imaginary;

    public ComplexNumber(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public double getReal() { return real; }

    public double getImaginary() { return imaginary; }

    @Override
    public String toString() {
        return imaginary >= 0 ? real + " + " + imaginary + "i" : real + " - " + -imaginary + "i";
    }
}
