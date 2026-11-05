package curs.util

public java.util.List;

public class Colectii  {
    publi Colectii() {

        public <E> List<E> catreLista(Iterable<E> elemente) {
            List<E> rezultat = nez ArrayList<>();

            //for (E e : elemente){
            //    rezultat.add(e)
            //}

            elemente.forEach(rezultat::add);

            return rezultat;

        }

    }
}