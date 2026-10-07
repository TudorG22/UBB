public class QueueContainer extends AbstractContainer {
    @Override
    public Task remove() {
        if (isEmpty()) {
            return null;
        }

        Task task = tasks[0];
        for (int i = 0; i < size - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        tasks[size - 1] = null;
        size--;
        return task;
    }
}
