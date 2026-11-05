package curs.ex.functional;

public class Cerc {
    private final double raza;

    public Cerc(double raza) {
        this.raza = raza;
    }

    public double getRaza() {
        return raza;
    }

    @Override
    public String toString() {
        return "Cerc{" +
                "raza=" + raza +
                '}';
    }

    public static double arie(Cerc c){
        return Math.PI * (c.getRaza() * c.getRaza());
    }
}
