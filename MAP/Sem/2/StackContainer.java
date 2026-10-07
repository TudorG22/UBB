public class StackContainer extends AbstractContainer {
    @Override
    public Task remove() {
        if (isEmpty()) {
            return null;
        }

        Task task = tasks[size - 1];
        tasks[size - 1] = null;
        size--;
        return task;
    }
}
