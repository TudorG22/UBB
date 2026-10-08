public class StrategyTaskRunner implements TaskRunner {
    private final Container container;

    public StrategyTaskRunner(Strategy strategy){
        this.container = TaskContainerFactory.getInstance().createContainer(strategy);
    }

    @Override
    public void executeOneTask(){
        if(container.empty()){
            return;
        }
        Task removed = container.remove();
        removed.execute();
    }

    @Override
    public void executeAll(){
        while(!container.empty()){
            executeOneTask();
        }
    }

    @Override
    public void addTask(Task t){
        this.container.add(t);
    }

    @Override
    public boolean hasTask(){
        return !this.container.empty();
    }
}
