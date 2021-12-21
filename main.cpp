#include <iostream>
#include <vector>
#include <string>

using namespace std;

//Структура краски
struct paint_item {
    int type;
    string color; 
    int volume;
    double price;
};

//Расчёт стоимости покраски
double coloring_cost(double square, int typeCost, int colorCost, int layerCount){
    return square*colorCost*layerCount;
}
double WallSquare(){
    string command;
    double width, height, square;
    cout << "Введите + чтобы добавить стену и - чтобы добавить выподающий участок. Для продолжения - 0" << endl;
    cin >> command;
    //Цикл вводящий стены и считающий их общую площадь
    while (command != "0"){
        //Добавление стены
        if (command == "+"){
            cout << "Ширина: ";
            cin >> width;
            cout << "Высота: ";
            cin >> height;
            //Увеличение площади
            square += width*height;
        }
        //Вычитание выступающего участка
        else if (command == "-"){
            cout << "Ширина: ";
            cin >> width;
            cout << "Высота: ";
            cin >> height;
            //Вычитание стены
            square -= width*height;
            //Если площадь меньше 0 то установить площадь равной нулю
            if (square < 0)
                square = 0;
        }
        //Если не удалось распознать команду сообщить об ошибке
        else cout << "Такой команды не существует" << endl;
        //Ввод новой команды
        cin >> command;
    }
    return square;
}
//Расчёт количества банок
int package_optional(double volumePackage, double volume){
    return int(volume/volumePackage)+(volume-(volumePackage*int(volume/volumePackage))==0?0:1);
}
//Расчёт оптимальной покраски
void budget_options(double square, int budget, vector<paint_item> paints){
    //Объявление переменных
    int layers_number=2;
    paint_item current;
    bool colorChoice = false;
    //Перебор всех красок
    for (int i=0; i<paints.size(); i++){
        //Проверка есть ли возможность покрасить хотя бы в два слоя(Меньше слоёв - слишком не качественно)
        if (package_optional(paints[i].volume, square*2)*paints[i].price<=budget){
            //Подсчёт максимального количества слоёв при заданом бюджете
            while(package_optional(paints[i].volume, square*(layers_number+1))*paints[i].price < budget)
                layers_number++;
            current = paints[i];
            //Переменная показывает выбрали ли мы хотябы один вариант - если нет, то выводим что недостаточно бюджета
            colorChoice = true;
            break;
        }
    }
    //Если хватило бюджета
    if (colorChoice){
        //Если слоёв больше 7 то оставляем 7
        if (layers_number > 7)
            layers_number = 7;
        //Выводим результат
        cout << "Будет потрачено: " << package_optional(current.volume, current.volume*layers_number)*current.price << " руб." <<
        endl << "Цвет краски - " << current.color << endl << "Количество банок " << package_optional(current.volume, square*layers_number) << endl
        << "Количество слоёв для покраски: " << layers_number << endl << "Сорт краски: " << (current.volume?"высший":"стандартный") << endl;
    }
    else
        cout << "Невозможно покрасить - недостаточно средств" << endl;
}
//Вывод красок
void PaintsOut(vector<paint_item> paints){
    //Пустые строки - разделители
    for (int i=0; i<paints.size(); i++){
        if (paints[i].type == 1)
            cout << "    Цвет - " << paints[i].color << ", цена - " << paints[i].price << " руб, объём банки - " << paints[i].volume << endl;
    }
    cout << endl << "Краски среднего сорта:" << endl;
    for (int i=0; i<paints.size(); i++){
        if (paints[i].type == 0)
            cout << "    Цвет - " << paints[i].color << ", цена - " << paints[i].price << " руб, объём банки - " << paints[i].volume << endl;
    }
    //Пустые строки - разделители
    cout << endl << endl;
}
//Стоимость покраски
void PaintingCost(vector<paint_item> paints){
    //Пустые строки - разделители
    cout << endl << endl;
    //Переменные
    paint_item it;
    string command;
    double square=0, width, height;
    int layerNumber, paintsChoice;
    square = WallSquare();
    //Пустые строки - разделители
    cout << endl << endl;
    //Вывод всех видов краски с их номерами
    for (int i=0; i<paints.size(); i++){
        cout << i+1 << ") Цвет - " << paints[i].color << ", сорт - " << (paints[i].type?"высший":"стандартный")
        << ", цена - " << paints[i].price << " руб, объём банки - " << paints[i].volume << endl;
    }
    //Ввод номера краски
    cout << endl << "Введите номер краски: ";
    cin >> paintsChoice;
    //Установка краски в переменную it
    it = paints[paintsChoice-1];
    //Ввод количества слоёв
    cout << "Введите количество слоёв: ";
    cin >> layerNumber;
    //Вывод расчёта стоимости
    cout << endl << "Стоимость покраски составит - " << coloring_cost(square, it.type, it.price, layerNumber) << " руб.";
    //Пустые строки - разделители
    cout << endl << endl << endl;
}
//Оптимальная покраска при фиксированном бюджете
void OptimalPainting(vector<paint_item> paints){
    //Объявление переменных
    double width, height, square=0;
    int budget;
    string command;
    //Ввод буджета
    cout << "Введите свой бюджет: ";
    cin >> budget;
    square = WallSquare();
    //Строки разделители
    cout << endl << endl;
    //Вывод оптимальной покраски с помощью функции budget_options
    budget_options(square, budget, paints);
    //Строки разделители
    cout << endl << endl;
}

int main()
{
    vector<paint_item> paints;
    //Важно добавлять цвета в нужном порядке - сначало дорогие потом дешовые
    paints.push_back({1, "белый", 5, 2200});
    paints.push_back({1, "бежевый", 5, 2000});
    paints.push_back({1, "чёрный", 5, 1990});
    paints.push_back({1, "белый", 5, 1900});
    paints.push_back({1, "бежевый", 5, 1700});
    paints.push_back({0, "чёрный", 5, 1650});
    paints.push_back({0, "синий", 5, 1500});
    paints.push_back({0, "красный", 5, 1300});
    paints.push_back({0, "синий", 5, 1200});
    paints.push_back({0, "красный", 5, 1000});
    //переменная номер команды
    int command;
    cout << "Введите номер режима(1 - Справочник красок, 2 - Поверхность и стоимость, 3 - Нормы и ограничения, 4 - Выход): ";
    cin >> command;
    //Цикл отправляющий команды в фнкцию MainMenu
    while (command != 4){
        switch (command){
            case 1: PaintsOut(paints); break;
            case 2: PaintingCost(paints); break;
            case 3: OptimalPainting(paints); break;
            default: cout << "Такой команды не существует\n\n"; break;
        }
        cout << "Введите номер режима(1 - Справочник красок, 2 - Поверхность и стоимость, 3 - Нормы и ограничения, 4 - Выход): ";
        cin >> command;
    }
    return 0;
}
