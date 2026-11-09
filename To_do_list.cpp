#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <iomanip>
enum class Priority{
LOW,
MEDIUM,
HIGH,
EXTREME,
};
class To_do{
    private:
    Priority priority;
    std::string name;
    std::string description;
    std::string decodedPriority() const{
        switch (this->priority){
            case Priority::LOW: return "Low";
            case Priority::MEDIUM: return "Medium";
            case Priority::HIGH: return "High";
            case Priority::EXTREME: return "Extreme";
            default:
            std::cout << "error in parsing in the priority" << std::flush;
            return "";
        }

    }
    void setPriority(const std::string& priorityString) {
        if (priorityString == "Low")
            priority = Priority::LOW;
        else if (priorityString == "Medium")
            priority = Priority::MEDIUM;
        else if (priorityString == "High")
            priority = Priority::HIGH;
        else if (priorityString == "Extreme")
            priority = Priority::EXTREME;
        else
            throw std::invalid_argument("Invalid priority: use Low, Medium, High, or Extreme");
    }
    void setName(std::string const name){
        if (name.empty()){
            throw std::invalid_argument("Insert name");
        }
        this->name = name;
    }
    void setDesc(std::string const desc){
        if (desc.empty()){
            throw std::invalid_argument("Insert desc");
            }
        this->description = desc;
    }
    public:
    To_do(std::string const name, std::string const desc , std::string const priorityString){
        setName(name);
        setDesc(desc);
        setPriority(priorityString);
    }
    std::string getPriority() const{
        //key part it is a getter so we add const so it cant change internal data
        return this->decodedPriority();
    }
    std::string getName() const{
        return this->name;
    }
    std::string getDesc() const{
        return this->description;
    }
};
std::vector <To_do> readFromFile(){
    std::string name, desc, priority;
    std::vector <To_do> dynArrayToDo;
    try{
        std::ifstream file("todos.txt");
        while (file >> std::quoted(name) >> std::quoted(desc) >> std::quoted(priority)){
            dynArrayToDo.emplace_back(name,desc,priority);
        }
    }catch(const std::invalid_argument &err){
        std::cerr << err.what() << std::flush;
    }
    return dynArrayToDo;
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string inputFromUser{"start"} ,name{} , desc{}, priorityString{};
    std::vector <To_do> dynArrayToDo{}; 
    while(!inputFromUser.empty()){
        std::cout << "1 for adding a new todo , 2 to print out the todos, 3 to store the values, 4 to load in previous sessions, enter to quit"  << std::flush;
        std::getline(std::cin, inputFromUser);
        if (inputFromUser == "1"){
            try{
                std::cout << "Enter name of the To-Do: " <<std::flush;
                std::getline(std::cin, name);
                std::cout << "description of the thing you want to do: " << std::flush;
                std::getline(std::cin, desc);
                std::cout << "enter the priority of this To-do: " << std::flush;
                std::getline(std::cin, priorityString);
                dynArrayToDo.emplace_back(name, desc, priorityString);//this creates the object in the vector stack
                //careful dont create object and then push its 2 copies of the same object not reference             
            }catch(const std::invalid_argument &err){
                std::cerr << err.what() << std::flush;
                std::cout << "error in input";
                continue;
            }
        }
        if (inputFromUser == "2"){
            for (const To_do &todo : dynArrayToDo){
                std::cout << todo.getName() << ": "
              << todo.getDesc() << " ["
              << todo.getPriority() << "]\n";
            }
        }
        if (inputFromUser == "3"){
            std::ofstream file("todos.txt");
            for (const To_do &todo : dynArrayToDo){
                file << std::quoted(todo.getName()) << ' '
                    << std::quoted(todo.getDesc()) << ' '
                    << std::quoted(todo.getPriority()) << '\n';
                }
                if (!file){
                    std::cerr << "couldnt save todos\n";
                }
 
        }
        if (inputFromUser == "4"){
            const std::vector <To_do> readFromFileList = readFromFile();
            if (readFromFileList.empty()){
                std::cout << "error in parsing todos.txt" << std::flush;
            }
            dynArrayToDo.insert(dynArrayToDo.end() , readFromFileList.begin(), readFromFileList.end());
            std::cout << "successfully completed";
        }

    }
    return 0;
};
