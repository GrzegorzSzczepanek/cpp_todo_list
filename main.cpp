#include <iostream>
#include <filesystem>
#include <string>
#include <cstdlib>
#include <fstream>

namespace  fs = std::filesystem;

void generate_save_file(const fs::path& dir_path) {
    fs::path file_path = dir_path / "saves.txt";
    std::ofstream file(file_path);
    if (file.is_open()) {
        std::cout << "Saves file was created successfully" << std::endl;
    } else {
        std::cout << "Failed to create file" << std::endl;
    }
}

void generate_save_dir(const fs::path& dir_path) {

    if(!fs::exists(dir_path)){
        if(fs::create_directories(dir_path)){
            generate_save_file(dir_path);
            std::cout << "Directory for saves was created" << std::endl;
        } else {
            std::cout << "Failed to create directory" << std::endl;
        }
    } else {
        std::cout << "Welcome Back!" << std::endl;
    }
}

void add_new_task(fs::path& dir_path){
    std::string task;
    std::cout << "Type in your task: ";
    std::cin >> task;

    fs::path file_path = dir_path / "saves.txt";
    std::ofstream file(file_path.string(), std::ios_base::app);

    if (file.is_open()) {
        file << task << "\n";
    } else {
        std::cout << "Failed to load saves" << std::endl;
    }
    file.close();

    std::cout << "Task was added successfully!" << std::endl;
}

void remove_one_task(fs::path& dir_path){
    std::cout << "Task was removed successfully" << std::endl;
}

void check_tasks(fs::path& dir_path){
    std::cout << "Your current task:" << std::endl;
    fs::path file_path = dir_path / "saves.txt";
    std::ifstream file(file_path.string());
    if (file.is_open()) {
       std::string line;
       while (std::getline(file, line)) {
           std::cout << line << "\n";
       }
    } else {
       std::cout << "Failed to open file." << std::endl;
    }
    file.close();}

void remove_every_task(fs::path& dir_path){
    std::cout << "Every task was deleted successfully!" << std::endl;
}

void quit_the_app(fs::path& dir_path) {
    std::cout << "See you again!" << std::endl;
    exit(0);
}

void main_interface() {
    std::cout << "-----------------------" << std::endl;
    std::cout << "What do you want to do?" << std::endl;
    std::cout << "a) Check tasks" << std::endl;
    std::cout << "b) Add new task" << std::endl;
    std::cout << "c) Remove one task" << std::endl;
    std::cout << "d) Remove every task" << std::endl;
    std::cout << "e) Quit the app" << std::endl;
}

int main (int argc, char *argv[]) {
    std::string home_dir = getenv("HOME");
    fs::path dir_path = fs::path(home_dir) / ".local" / "share" / "cpp_todo_list";
    generate_save_dir(dir_path);

    while (true) {
        char choice;
        main_interface();
        std::cin >> choice;
        // Make it lowercase
        choice = std::tolower(choice, std::locale());
        switch (choice) {
            case 'a':
                check_tasks(dir_path);
                break;
            case 'b':
                add_new_task(dir_path);
                break;
            case 'c':
                remove_one_task(dir_path);
                break;
            case 'd':
                remove_every_task(dir_path);
                break;
            case 'e':
                quit_the_app(dir_path);
                break;
            default:
                std::cout << "Incorrect input. You have to type a, b, c, or d";
                break;
        }
    }

    return 0;
}
