import java.time.LocalDateTime;

public class DelayTaskRunner extends AbstractTaskRunner{
    private long delay = 3000;

    public DelayTaskRunner(TaskRunner taskRunner, long delay){
        super(taskRunner);
        this.delay = delay;
    }

    @Override
    public boolean hasTask(){
        return taskRunner.hasTask();
    }

    @Override
    public void executeOneTask(){
        if(hasTask()){
            try{
                Thread.sleep(delay);
            } catch (InterruptedException e){
                Thread.currentThread().interrupt();
                return;
            }
        }
        taskRunner.executeOneTask();
        System.out.println("Task executat cu intarziere");
    }

    @Override
    public void executeAll(){
        while(hasTask()){
            executeOneTask();
        }
    }
}
