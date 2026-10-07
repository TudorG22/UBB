import java.util.Arrays;

public class AbstractContainer implements Container {
    protected Task[] tasks;
    protected int size;

    public AbstractContainer() {
        tasks = new Task[10];
        size = 0;
    }

    @Override
    public void add(Task t){
        if(size == tasks.length) {
            tasks = Arrays.copyOf(tasks, tasks.length * 2);
        }
        tasks[size++] = t;
    }

    @Override
    public int size(){
        return this.size;
    }

    @Override
    public boolean empty() {
        return this.size == 0;
    }


}
