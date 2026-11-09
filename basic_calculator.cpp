#include <iostream>
class calculator{
    private:
    double var1;
    double var2;
    double calculate(char operation){
        double result {};
        if (operation == '/'){
            if (var2 == 0){
                std::cerr << "issue";
                return -1;
            }
            result = var1 / var2;
        }else if (operation == '+'){
            result = var1 + var2;

        }else if (operation == '-'){
            result = var1 - var2;
        }else if (operation == '*'){
            result = var1 * var2;
        }else{
            std::cout << "input error" << operation << std::endl;
        }
        return result;
    }
    public:
    calculator(double &x,char operation, double &y){
        var1 = x;
        var2 = y;
        double result = calculate(operation);
        std::cout << result;
    };
    calculator(){
        std::cout << "overloaded the construction constructor";
    };
};
int main(){
    std::ios::sync_with_stdio(false);//prevents c print stuff
    std::cin.tie(nullptr);
    double var1{}, var2{};
    char operation{};
    std::cout << "enter your first numeber" << std::flush;
    std::cin >> var1;
    std::cout << "enter your operation" << std::flush;
    std::cin >> operation;
    std::cout << "enter you second number" << std::flush;
    std::cin >> var2;
    calculator calc(var1,operation,var2);
    calculator calc2;
    return 0;
}