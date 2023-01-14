#include <iostream>
#include <stack>
#include <cmath>
#include <sstream>

const double Pi = acos(-1); // объясняем программе, чему равно число Пи

double Sin(double x) { // округляем значение синуса
    return (round(sin(x) * 10000000) / 10000000);
}

double Cos(double x) { // округленяем значение косинуса
    return (round(cos(x) * 10000000) / 10000000);
}

double Ctg(double x) { // функция для котангенса
    double a = cos(x);
    double b = Sin(x);
    return (a / b);
}

struct defenition { // структура, описывающая числа или операции
    char type; // тип: 0 для чисел, "+" для операций сложения и т.д.
    double value; // значение
};

bool Maths(std::stack<defenition> &Stack_numbers, std::stack<defenition> &Stack_oper,
           defenition &item) { // функция, производящая все расчёты и записывающая результат ответа в стек. Аргументы - ссылка на стек с операциями, на стек с числами, на значение (defenition) item. Тип bool, чтобы можно было проводить проверки на True/False
    double number1, number2, summ, sub, multiplication, division, degree, sinus, cosine, tangent, cotangent, e;
    number1 = Stack_numbers.top().value; //записываем самый верхний элемент из стека с числами в переменную. Но обращаемся не к структурному типу элемента (defenition), а его значению value
    Stack_numbers.pop(); // удаляем верхний элемент в стеке с числами. Он нам не нужен, уже записан в переменную
    switch (Stack_oper.top().type) { //Проверяем тип верхней операции из стека с операциями (не значение (для операций всегда 0), а сама операция +/-/* и т.д.

        case '+': // если верхняя операция сложение
            number2 = Stack_numbers.top().value;
            Stack_numbers.pop();
            summ = number1 + number2;
            item.type = '0'; // прописываем тип и значение для нового элемента 'summ'
            item.value = summ;
            Stack_numbers.push(item); //добавляем в стек с числами получившуюся сумму
            Stack_oper.pop(); // удаляем верхний элемент в стеке с операциями
            break;

        case '-': // если вычитание
            number2 = Stack_numbers.top().value;
            Stack_numbers.pop();
            sub = number2 - number1; // меняем number1 и number2 местами т.к. некоммутативная операция
            item.type = '0';
            item.value = sub;
            Stack_numbers.push(item);
            Stack_oper.pop();
            break;

        case '*': // если умножение
            number2 = Stack_numbers.top().value;
            Stack_numbers.pop();
            multiplication = number1 * number2;
            item.type = '0';
            item.value = multiplication;
            Stack_numbers.push(item);
            Stack_oper.pop();
            break;

        case '/': // если деление
            number2 = Stack_numbers.top().value;
            if (number1 == 0) {
                std::cerr << "Error";
                return false;
            } else {
                Stack_numbers.pop();
                division = number2 / number1;
                item.type = '0';
                item.value = division;
                Stack_numbers.push(item);
                Stack_oper.pop();
                break;
            }

        case '^': // возведение числа в степень
            number2 = Stack_numbers.top().value;
            Stack_numbers.pop();
            degree = pow(number2, number1);
            item.type = '0';
            item.value = degree;
            Stack_numbers.push(item);
            Stack_oper.pop();
            break;

        case 's': // синус
            sinus = Sin(number1);
            item.type = '0';
            item.value = sinus;
            Stack_numbers.push(item);
            Stack_oper.pop();
            break;

        case 'c': // косинус
            cosine = Cos(number1);
            item.type = '0';
            item.value = cosine;
            Stack_numbers.push(item);
            Stack_oper.pop();
            break;

        case 't': // тангенс
            if (Cos(number1) == 0) {
                std::cerr << "\nError argument for tangent!\n";
                return false;
            } else {
                tangent = tan(number1);
                item.type = '0';
                item.value = tangent;
                Stack_numbers.push(item);
                Stack_oper.pop();
                break;
            }

        case 'g': // котангенс
            if (Sin(number1) == 0) {
                std::cerr << "\nError argument for cotangent!\n";
                return false;
            } else {
                cotangent = Ctg(number1);
                item.type = '0';
                item.value = cotangent;
                Stack_numbers.push(item);
                Stack_oper.pop();
                break;
            }

        case 'e': // экспонента
            e = exp(number1);
            item.type = '0';
            item.value = e;
            Stack_numbers.push(item);
            Stack_oper.pop();
            break;

        default: //возвращает ошибку, если введённая операция не соответствует списку операций реализуемых программой
            std::cerr << "\nError!\n";
            return false;
            break;
    }
    return true;
}

int Operations_Rang(char a) { // функция возвращает приоритет (rang) текущей операции
    if (a == '+' || a == '-') return 1; // если текущая операция - это сложение/вычитание, то функция возвращает 1
    if (a == '*' || a == '/') return 2;
    if (a == '^') return 3;
    if (a == 's' || a == 'c' || a == 't' || a == 'g' || a == 'e') return 4;
    else return 0; // в противном случае, если ничего из вышеперечисленного не выполняется, функция возвращает 0
}

int main() {
    while (true) {
        std::cout << "Hello! It's calculator. \nEnter the operation: ";
        std::string str;
        getline(std::cin, str);
        std::stringstream sstr{str};

        char a; // переменная, в которую мы записываем каждый новый обрабатываемый символ
        double value;
        bool flag = true; // отличаем отрицательное число от операции вычитания
        std::stack<defenition> Stack_numbers; // стек с числами
        std::stack<defenition> Stack_oper; // стек с операциями
        defenition item; // инициализируем каждый введённый элемент типом defenition, чтобы компилятор понимал, какие именно элементы мы будем класть в наши стеки.
        while (true) { // цикл, считывающий всю входную последовательность, а не только первый символ
            a = sstr.peek(); // смотрим на первый символ
            // std::cout << a << std::endl; - строчка - помощница при ошибках. Для отслеживания последовательности действий внутри программы
            if (a == '\377') {
                break; // если мы дошли до конца строки, то выходим из цикла
            }
            if (a == ' ') { // игнорируем пробелы, чтобы не считать их за ошибку
                sstr.ignore();
                continue;
            }
            if (a == 's' || a == 'c' || a == 't' || a == 'e') { // если нам попалась функция
                char foo[3]; //массив на 3 символа для определения типа прочитанной функции
                for (int i = 0; i < 3; i++) {
                    a = sstr.peek();
                    foo[i] = a;
                    sstr.ignore();
                }
                if (foo[0] == 's' && foo[1] == 'i' && foo[2] == 'n') { // если прочитанная функция - синус
                    item.type = 's';
                    item.value = 0;
                    Stack_oper.push(item); // кладём операцию в стек с операциями
                    continue;
                }
                if (foo[0] == 'c' && foo[1] == 'o' && foo[2] == 's') { // если косинус
                    item.type = 'c';
                    item.value = 0;
                    Stack_oper.push(item);
                    continue;
                }
                if (foo[0] == 't' && foo[1] == 'a' && foo[2] == 'n') { // тангенс
                    item.type = 't';
                    item.value = 0;
                    Stack_oper.push(item);
                    continue;
                }
                if (foo[0] == 'c' && foo[1] == 't' && foo[2] == 'g') { // котангенс
                    item.type = 'g';
                    item.value = 0;
                    Stack_oper.push(item);
                    continue;
                }
                if (foo[0] == 'e' && foo[1] == 'x' && foo[2] == 'p') { // экспонента
                    item.type = 'e';
                    item.value = 0;
                    Stack_oper.push(item);
                    continue;
                }
            }
            if (a == 'p') { // если прочитанное число - это число Пи
                item.type = '0';
                item.value = Pi;
                Stack_numbers.push(item); // число кладём в стек с числами
                flag = false;
                sstr.ignore();
                continue;
            }
            if (a >= '0' && a <= '9' || a == '-' && flag == true) { // если это число
                sstr >> value;
                item.type = '0'; // тип всех чисел "0"
                item.value = value; // значение введённого числа = значению прочитанной переменной
                Stack_numbers.push(item); // кладём число в стек с числами
                flag = false;
                continue;
            }
            if (a == '+' || a == '-' && flag == 0 || a == '*' || a == '/' || a == '^') { //если это операция
                if (Stack_oper.empty()) { // если стек с операциями пустой
                    item.type = a;
                    item.value = 0;
                    Stack_oper.push(item);
                    sstr.ignore();
                    continue;
                }
                if (Stack_oper.size() != 0 && Operations_Rang(a) > Operations_Rang(
                        Stack_oper.top().type)) { // если стек с операциями не пустой, и при этом приоритет текущей операции выше приоритета верхней операции в стеке, то кладём операцию с большим приоритетом наверх
                    item.type = a;
                    item.value = 0;
                    Stack_oper.push(item);
                    sstr.ignore();
                    continue;
                }
                if (Stack_oper.size() != 0 && Operations_Rang(a) <= Operations_Rang(
                        Stack_oper.top().type)) {// если стек с операциями не пустой, и при этом приоритет текущей операции ниже либо равен приоритету верхней операции в стеке, то мы сначала вызываем функцию Maths
                    if (Maths(Stack_numbers, Stack_oper, item) ==
                        false) { // если внутри функции найдена ошибка, то вся программа прекратит работу
                        system("pause");
                        return 0;
                    }
                    continue; // продолжаем цикл
                }
            }
            if (a == '(') { // если текуший символ - открывающаяся скобка, то мы кладем её в стек с операциями
                item.type = a;
                item.value = 0;
                Stack_oper.push(item);
                sstr.ignore();
                continue;
            }
            if (a ==
                ')') { // если текуший символ - закрывающаяся скобка, то мы не кладём эту скобку в стек, а выполняем операции после первой скобки до тех пор, пока не дойдём до закрывающейся скобки
                while (Stack_oper.top().type != '(') {
                    if (Maths(Stack_numbers, Stack_oper, item) ==
                        false) {
                        system("pause");
                        return 0;
                    } else continue; // всё хорошо
                }
                Stack_oper.pop(); // удалили открывающуюся скобку из стека с операциями
                sstr.ignore(); // после прочтения закрывающейся скобки переходим к следующему элементу
                continue;
            } else { // прочитали непонятный символ
                std::cout << "\nError!\n";
                system("pause");
                return 0;
            }
        }
        while (Stack_oper.size() !=
               0) { // вызываем функцию Maths до тех пор, пока размер стека с операциями не станет 0
            if (Maths(Stack_numbers, Stack_oper, item) ==
                false) { // если функция Maths жалуется на ошибку, то программа прекращает работу
                system("pause");
                return 0;
            } else continue; // всё хорошо, продолжаем работу
        }
        std::cout << "   Otvet: " << Stack_numbers.top().value << std::endl; // выводим ответ
        system("pause");
    }
    return 0;
}