#include "log.h"

namespace lg {

    std::fstream file;

    void log(std::string msg)
    {
        file.open("log.txt", std::ios::app);
        file << msg << std::endl;
        file.close();
    }

    void log(Matrix& m)
    {
        file.open("log.txt", std::ios::app);
        file << "Matrix: " << std::endl;
        for (auto i = m.rbegin(); i != m.rend(); i++) {
            for (auto col : *i) {
                file << col << " ";
            }
            file << std::endl;
        }
        file.close();
    }
}