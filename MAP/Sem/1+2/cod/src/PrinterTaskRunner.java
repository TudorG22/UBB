import java.time.LocalDateTime;

public class PrinterTaskRunner extends AbstractTaskRunner{
    public PrinterTaskRunner(TaskRunner taskRunner){
        super(taskRunner);
    }

    @Override
    public boolean hasTask(){
        return taskRunner.hasTask();
    }

    @Override
    public void executeOneTask(){
        if(hasTask()){
            taskRunner.executeOneTask();
            System.out.println("Printer task executat la: " + LocalDateTime.now().getHour());
        }
    }

    @Override
    public void executeAll(){
        while(hasTask()){
            executeOneTask();
        }
    }
}
