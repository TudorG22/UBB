package curs.ex;

/**
 * Quiz: what does the program print? (try - catch - finally)
 */
class A {
    public int x = 0;
}

public class G10 {

    /**
     *
     * @return an object A whose field x was modified in try, catch and finally
     */
    public A foo() {
        A a = new A();
        try {
            a.x = 1;
            throw new NullPointerException();
        } catch (Exception e) {
            a.x = 2;
            return a;
        } finally {
            a.x = 3;
        }
    }

    /**
     *
     * @param args - command line arguments (not used)
     */
    public static void main(String[] args) {
        G10 ex = new G10();
        System.out.println(ex.foo().x);
    }
}
