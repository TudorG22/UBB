package socialnetwork.config;

/** Available storage types. */
public enum RepositoryType {
    /** Temporary in-memory storage. */
    MEMORY,
    /** UTF-8 text files. */
    FILE,
    /** Database placeholder for Lab 4. */
    DATABASE;

    /** Parses the configured type.
     * @param value configuration value
     * @return storage type
     * @throws IllegalArgumentException if missing or unknown
     */
    public static RepositoryType fromString(String value) {
        if (value == null || value.isBlank()) {
            throw new IllegalArgumentException("Lipseste proprietatea repository.type.");
        }
        try {
            return RepositoryType.valueOf(value.trim().toUpperCase());
        } catch (IllegalArgumentException exception) {
            throw new IllegalArgumentException("repository.type necunoscut: " + value);
        }
    }
}
