#include <iostream>
#include <stack>
#include <string>
#include <cctype>

int getPriority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

void processOperator(std::stack<int>& numbers, char op) {
    int right = numbers.top();
    numbers.pop();
    int left = numbers.top();
    numbers.pop();

    switch (op) {
    case '+': numbers.push(left + right); break;
    case '-': numbers.push(left - right); break;
    case '*': numbers.push(left * right); break;
    case '/': numbers.push(left / right); break;
    }
}

int calculateExpression(const std::string& expression) {
    std::stack<int> numbers;
    std::stack<char> operators;

    for (int i = 0; i < expression.length(); ++i) {
        if (isspace(expression[i])) {
            continue;
        }

        if (isdigit(expression[i])) {
            int value = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                value = value * 10 + (expression[i] - '0');
                i++;
            }
            numbers.push(value);
            i--;
        }
        else if (expression[i] == '(') {
            operators.push(expression[i]);
        }
        else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                processOperator(numbers, operators.top());
                operators.pop();
            }
            operators.pop(); // Удаляем '('
        }
        else {
            while (!operators.empty() && getPriority(operators.top()) >= getPriority(expression[i])) {
                processOperator(numbers, operators.top());
                operators.pop();
            }
            operators.push(expression[i]);
        }
    }

    while (!operators.empty()) {
        processOperator(numbers, operators.top());
        operators.pop();
    }

    return numbers.top();
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string expression;
    std::cout << "Введите математическое выражение: ";
    std::getline(std::cin, expression);

    int result = calculateExpression(expression);
    std::cout << "Результат: " << result << std::endl;

    return 0;
}
