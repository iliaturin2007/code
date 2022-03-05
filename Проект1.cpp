#include <iostream>
#include <iomanip>

using namespace std;

struct eternal_calendar { //Структура вечного календаря
    int month; //Месяцы
    int year; //Год
    string weekday; //Дни недели
    int days;
}; //Числа

//5) Вывод календаря в форме
void print_calendar(int month, int shift, int days){
    string months[12] = {"Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", 
    "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};
    cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~" << months[month - 1] << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    //6) Выводим дни недели:
    cout << "ПН\tВТ\tСР\tЧТ\tПТ\tСБ\tВС\n" << endl;

    for (int i = 0; i < shift; i++)
        cout << "\t";

    for (int d = shift + 1; d <= shift + days; d++) {
        cout << (d - shift)<< "\t"; 
        if(d % 7 == 0)
            cout<<"\n";
    }
    cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}
//3) Определяем високосный год или нет?
int days_in_month(int month, int year){
    int months_days [12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // количество дней в каждых месяцах
    // месяцы года
    if( month == 2 ) // 2 - это февраль, так как счёт начинается с 1 - января.
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) // проверка на високосность 
            return 29; // Год является високосным
    return months_days[month - 1];
}

int shift_in_month(int year, int month){
    //4) Определяем номер дня недели и шаг 
    //День недели = (день + код месяца + код года) % 7, день = 0
    static int m[] = {6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4}; //Код месяцев
    int ar = year % 100; //две цифры года
    return ar / 12 + ar % 12 + ar % 12 / 4 + m[month - 1] + (20 - year / 100); // код года
}

int main() {
    int month, year, days, shift;
    string weekday;
    cout << "Введите дату в формате: 1 2001(месяц !пробел! год)" << endl;    
    //1) Считам месяц и год:
    cin >> month; // считаем месяцы
    cin >> year; // считаем год
    //2) Выводим месяц и год
    cout << month << " " << year << endl; // выводим месяц и год
    while (month < 1 || month > 12) {
        cout <<"Неверно введён месяц.Правильный ввод месяца от 1 до 12, где 1 - январь, а 12-декабрь.";
        cin >> month;
    }
    while (year < 1919 || year > 2029) {
        cout << "Неверно введён год.Правильный ввод года от 1919 до 2029 включительно.";
        cin >> year;
    }
    days = days_in_month(month, year);
    shift = shift_in_month(year, month);
    if ((year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) && month <= 2) 
        shift--; //если год високосный
    shift = shift % 7;
    print_calendar(month, shift, days);
    return 0;
}

