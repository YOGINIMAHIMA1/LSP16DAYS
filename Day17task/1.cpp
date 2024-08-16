#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

void readFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("File not found");
    }

    std::string line;
    while (std::getline(file, line)) {
        try {
            // Assuming we expect the line to be an integer
            int value = std::stoi(line);
            std::cout << "Read value: " << value << std::endl;
        } catch (const std::invalid_argument&) {
            std::cerr << "Invalid data format: " << line << std::endl;
        } catch (const std::out_of_range&) {
            std::cerr << "Data out of range: " << line << std::endl;
        }
    }

    if (file.bad()) {
        throw std::runtime_error("Error reading file");
    }

    file.close();
}

int main() {
    try {
        readFile("data.txt");
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}
