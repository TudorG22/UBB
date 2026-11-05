package curs.ex.functional;

public class Patrat {
    private final double latura;

    public Patrat(double latura) {
        this.latura = latura;
    }

    public double getLatura() {
        return latura;
    }

    public String toString() {
        return "Patrat{" +
                "latura=" + latura +
                '}';
    }
}
