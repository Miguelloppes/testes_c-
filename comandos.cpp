#include <boost/process.hpp>
#include <iostream>
#include <string>

namespace bp = boost::process;

void run_command(const std::string& command) {
    try {
        bp::child c(bp::search_path("bash"), "-c", command);
        c.detach();  
        if (c.exit_code() != 0) {
            std::cerr << "Command failed with exit code: " << c.exit_code() << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void run_code() { 
    while (true){
        std::cout << "rodando codigo main" << "\n";
    }
}
int main() {
    std::string command1 = "python3 a.py";
    run_command(command1);
    std::string command2 = "python3 b.py";
    run_command(command2);
    run_code(); 

    return 0;
}
