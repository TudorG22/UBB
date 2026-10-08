public abstract class AbstractTaskRunner implements TaskRunner{
    protected final TaskRunner taskRunner;

    protected AbstractTaskRunner(TaskRunner taskRunner){
        this.taskRunner = taskRunner;
    }

    @Override
    public void addTask(Task t){
        taskRunner.addTask(t);
    }

    @Override
    public boolean hasTask() {
        return taskRunner.hasTask();
    }
}
