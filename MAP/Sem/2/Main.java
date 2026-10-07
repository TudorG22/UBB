import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args){
        //Task t = new Task("1", "test");
        //Nu se poate initializa, clasa abstracta

        MessageTask message = new MessageTask("1", "desc", "mesaj",
                "sender", "receiver", LocalDateTime.now());

        System.out.println(message);

        List<Task> list = new ArrayList<>();
        EmailTask email = new EmailTask("2", "descriere", "abcd@gmail.com");

        list.add(message);
        list.add(email);

        for(Task t : list){
            t.execute();
        }

        Message m1 = new Message("3", "descriere mesaj", "mesaj",
                "sender", "receiver", LocalDateTime.now());
        Task str = new MessageTaskRefactor(m1);
        str.execute();

        Container c = TaskContainerFactory.getInstance().createContainer(Strategy.FIFO);
        Task t1 = new EmailTask("4", "email 1", "email1@gmail.com");
        Task t2 = new EmailTask("5", "email 2", "email2@gmail.com");
        Task t3 = new EmailTask("6", "email 3", "email3@gmail.com");

        addTasks(c, t1, t2, t3);

    }

    private static void addTasks(Container c, Task t1, Task t2, Task t3){
        c.add(t1);
        c.add(t2);
        c.add(t3);
    }

}
