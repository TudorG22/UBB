import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public void main(){
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

        Message m1 = new Message("1", "subject", "body", "sender", "receiver", LocalDateTime.now());
        Task mtr = new MessageTaskRefactor(m1);
        mtr.execute();

        Container c = TaskContainerFactory.getInstance().createContainer(Strategy.FIFO);

        Task t1 = new MessageTask("1", "desc1", "msg1",
                "sender1", "receiver1", LocalDateTime.now());
        Task t2 = new MessageTask("2", "desc2", "msg2",
                "sender2", "receiver2", LocalDateTime.now().minusYears(50));
        Task t3 = new MessageTask("3", "desc3", "msg3",
                "sender3", "receiver3", LocalDateTime.now().minusHours(61));

        addTasks(c, t1, t2, t3);

        while(!c.empty()){
            Task removed = c.remove();
            System.out.println("Scos din FIFO: " + removed);
        }

        Container stack = TaskContainerFactory.getInstance().createContainer(Strategy.LIFO);

        addTasks(stack, t1, t2, t3);

        while(!stack.empty()){
            Task removed = stack.remove();
            System.out.println("Scos din LIFO: " + removed);
        }

        TaskContainerFactory factory1 = TaskContainerFactory.getInstance();
        TaskContainerFactory factory2 = TaskContainerFactory.getInstance();
        System.out.println("factory1 == factory2: " + (factory1 == factory2));

        TaskRunner runnerFIFO = new StrategyTaskRunner(Strategy.FIFO);
        runnerFIFO.addTask(t1);
        runnerFIFO.addTask(t2);
        runnerFIFO.addTask(t3);
        System.out.println("Toate taskurile:");
        runnerFIFO.executeAll();

        TaskRunner taskRunnerDelay = new DelayTaskRunner(runnerFIFO, 3000);
        taskRunnerDelay.addTask(t1);
        taskRunnerDelay.addTask(t2);
        taskRunnerDelay.addTask(t3);
        taskRunnerDelay.executeAll();
    }

    private static void addTasks(Container c, Task t1, Task t2, Task t3){
        c.add(t1);
        c.add(t2);
        c.add(t3);
    }
}
