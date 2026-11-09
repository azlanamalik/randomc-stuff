#include <iostream>
#include <random>
class NumberGuess{
    private:
    int number;
    void generateNumber(){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1,100);
        number = dist(gen);
    }
    public:
    NumberGuess(){
        generateNumber();
        int guess{};//cannot be 0
    }
    bool inputGuess(int guess){
        std::cout << number;
        if(guess == number){
            return true;
        }
        return false;
    }
};

int main(){
    NumberGuess num;
    bool isGuessCorrect {false};
    int guess{};
    while (!isGuessCorrect){
        std::cout << "enter another guess";
        std::cin >> guess;
        isGuessCorrect = num.inputGuess(guess);
        isGuessCorrect ? std::cout << "correct" : std::cout << "wrong";
    }
}