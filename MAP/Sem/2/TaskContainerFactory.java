public class TaskContainerFactory {
    private static final TaskContainerFactory INSTANCE = new TaskContainerFactory();

    private TaskContainerFactory(){}

    public static TaskContainerFactory getInstance(){
        return INSTANCE;
    }

    public Container createContainer(Strategy strategy){
        return switch (strategy){
            case FIFO -> new QueueContainer();
            case LIFO -> new StackContainer();
        };
    }
}
