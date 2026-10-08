public interface Container {
    Task remove();
    void add(Task t);
    int size();
    boolean empty();
}
