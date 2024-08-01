#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cctype>

int countWords(const char* filepath) {
    int fd = open(filepath, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return -1;
    }

    const size_t buffer_size = 4096;
    char buffer[buffer_size];
    ssize_t bytesRead;
    int word_count = 0;
    bool in_word = false;

    while ((bytesRead = read(fd, buffer, buffer_size)) > 0) {
        for (ssize_t i = 0; i < bytesRead; ++i) {
            if (std::isspace(buffer[i]) || buffer[i] == '\n' || buffer[i] == '\t') {
                if (in_word) {
                    in_word = false;
                    ++word_count;
                }
            } else {
                in_word = true;
            }
        }
    }

    if (in_word) {
        ++word_count; // Count the last word if file doesn't end with a delimiter
    }

    if (bytesRead < 0) {
        perror("Error reading file");
    }

    close(fd);
    return word_count;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file path>" << std::endl;
        return 1;
    }

    int word_count = countWords(argv[1]);
    if (word_count >= 0) {
        std::cout << "Number of words: " << word_count << std::endl;
    }

    return 0;
}
