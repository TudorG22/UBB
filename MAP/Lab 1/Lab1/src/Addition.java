public class Addition implements Operation {
    @Override
    public ComplexNumber apply(ComplexNumber first, ComplexNumber second) {
        return new ComplexNumber(first.getReal() + second.getReal(), first.getImaginary() + second.getImaginary());
    }
}
