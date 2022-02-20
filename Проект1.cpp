#include <iostream>
#include <string>
#include <cmath>

using namespace std;
//Кол-во дней в месяце
int CountDayInMonth(int month, int year){
    if (month==1||month==3||month==5||month==7||month==8||month==10||month==12){
        return 31;
    }
    if (month==4||month==6||month==9||month==11){
        return 30;
    }
    if (month==2){
        return 28+(year%4==0);
    }
    return 0;
}
//Функция для расчёта первого дня в неделе
int FirstDayInMonth(int month, int year){
    //Расчёт первого дня в году (календари совпадают каждые 28 лет, а високосные года каждый год делящийся на 4)
    int FirstDayInYear = ((year-1)%28+((year-1)%28/4)-1)%7+1;
    int CountDay = 0;
    //Считаем первый день в месяце, добавляя кол-во дней в месяцах перед текущим
    for (int i=1; i<month; i++){
        CountDay += CountDayInMonth(i, year);
    }
    return (FirstDayInYear+CountDay-1)%7+1;
}
//Функция перевода номера месяцов в названия
string MonthLabel(int month){
    switch (month){
        case 1: return "Январь";
        case 2: return "Февраль";
        case 3: return "Март";
        case 4: return "Апрель";
        case 5: return "Май";
        case 6: return "Июнь";
        case 7: return "Июль";
        case 8: return "Август";
        case 9: return "Сентябрь";
        case 10: return "Октябрь";
        case 11: return "Ноябрь";
        case 12: return "Декабрь";
    }
    return "0";
}
//Выводит календарь
void printCalendar(int FirstDay, int month, int year){
    cout << endl << endl << "====================" << endl << MonthLabel(month) << ", "  << year  << endl << endl;
    cout << "ПН ВТ СР ЧТ ПТ СБ ВС" << endl;
    //Пропускает место перед первым числом
    for (int i=1; i<FirstDay; i++){
            cout << "   ";
    }
    //Дата
    int date=1;
    //Цикл пока дата меньше количества дней в месяце
    while (date <= CountDayInMonth(month, year)){
        //Если день недели больше 7 делаем равным 1
        if (FirstDay>7){
            FirstDay = 1;
            cout << endl;
        }
        //Если дата в один символ добавляем пробел
        if (date < 10)
            cout << ' ';
        cout << date << ' ';
        //Увеличивем дату и день недели
        date++;
        FirstDay++;
    }
    cout << endl << endl << "====================" << endl << endl;
}
//Функция перевода char в int
int ConvertSymbolToInt(char symbol){
    switch(symbol){
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        default: return -1;
    }
}
//Функция перевода string в int
int ParseUnsignedInt(string valueString){
    int value=0;
    for (int i=0; i<valueString.length(); i++){
        if (ConvertSymbolToInt(valueString[i]) == -1)
            return -1;
        value+=ConvertSymbolToInt(valueString[i])*pow(10, valueString.length()-i-1);
    }
    return value;
}
//Функция общего вывода
void output(int year, int month){
    //Если данные верные то выводим календарь с помощью функции printCalendar
    if (year>=1919 && year<=2029 && month>=1 && month<=12 && month != -1 && year != -1) 
        printCalendar(FirstDayInMonth(month, year), month, year);
    //Если пользователь ошибся в формате данных
    else if(month == -1||year == -1) 
        cout << endl <<"Неверные данныеее...." << endl << "Я ломаюсь..... АААААААААААААААААА" << endl << endl;
    //Если ошибся в диапазоне
    else
        cout << endl << "Дата вне диапазона - 01.01.1919 --- 31.12.2029" << endl << endl;
}
int main(){
    //Добавляем русский язык
    setlocale(LC_ALL, "Russian");
    //Объявоение еременные
    int year=-1, month=-1, i=0;
    string input, yearStr, monthStr;
    bool ErrorData = false;
    //Пояснение ввода программы
    cout << "print date in format mm dddd: ";
    //Ввод строки(с учётом пробелов)
    getline(cin, input);
    //Цикл "вытаскивающий" из строки месяц
    for (;input[i]!=' ';i++){
        monthStr.push_back(input[i]);
        //Если цикл заходит за пределы слова, значит пробел не найден ->
        //-> перевести ErrorData на true
        if (i>=input.length()){
            ErrorData = true;
            break;
        }
    }
    //Пропускаем разделитель(пробел)
    i++;
    //Достаём вторую чать слова
    for (;i<input.length()&&ErrorData==false;i++)
        yearStr.push_back(input[i]);
    //Если ошибки не найдены то переводим стоки в int с помощью функции PaseUnsignedInt
    if (!ErrorData){
        month = ParseUnsignedInt(monthStr);
        year = ParseUnsignedInt(yearStr);
    }
    output(year, month);
    return 0;
}
