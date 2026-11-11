// Simple console calculator.
// Reads expressions like "12.5 * 4" and prints the result.
// Type "q" to quit.

#include <iostream>
#include <sstream>
#include <string>

// Returns true if the calculation worked, false on an error
// (unknown operator or division by zero).
bool calculate(double a, char op, double b, double &result) {
    switch (op) {
        case '+': result = a + b; return true;
        case '-': result = a - b; return true;
        case '*': result = a * b; return true;
        case '/':
            if (b == 0) return false;
            result = a / b;
            return true;
        default:
            return false;
    }
}

int main() {
    std::cout << "Calculator. Enter: number operator number (example: 7 * 6)\n";
    std::cout << "Operators: + - * /   Quit: q\n";

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "q") break;

        std::istringstream input(line);
        double a, b;
        char op;
        if (!(input >> a >> op >> b)) {
            std::cout << "Could not read that. Example: 3 + 4\n";
            continue;
        }

        double result;
        if (calculate(a, op, b, result)) {
            std::cout << "= " << result << "\n";
        } else {
            std::cout << "Error: unknown operator or division by zero\n";
        }
    }
    return 0;
}
