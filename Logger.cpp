#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

class Logger {
public:
    Logger(const std::string& filename) : filename(filename), file(filename, std::ios_base::app) {}

    void writeLog(const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex);
        file << message << '\n';
    }

    std::string readLog() {
        std::lock_guard<std::mutex> lock(mutex);
        file.seekg(0, std::ios_base::beg);
        std::string line;
        std::string lastLine;
        while (std::getline(file, line)) {
            lastLine = line;
        }
        return lastLine;
    }

    ~Logger() {
        file.close();
    }

private:
    std::string filename;
    std::ofstream file;
    std::mutex mutex;
};

// Пример использования
int main() {
    Logger logger("log.txt");
    logger.writeLog("Сообщение 1");
    logger.writeLog("Сообщение 2");
    std::string lastLog = logger.readLog();
    std::cout << lastLog << std::endl;
    return 0;
}