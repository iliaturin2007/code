#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct paint_item {
    int type;
    string color; 
    int volume;
    double price;
};

double coloring_cost(double square, int typeCost, int colorCost, int layerNumber){
    return square*(typeCost+1)*colorCost*layerNumber;
}

int package_optional(double volumePackage, double volume){
    return int(volume/volumePackage)+(volume-(volumePackage*int(volume/volumePackage))==0?0:1);
}
void budget_options(double square, int budget, vector<paint_item> paints){
    int layers_number=2;
    paint_item current;
    bool colorChoice = false;
    for (int i=0; i<paints.size(); i++){
        if (package_optional(paints[i].volume, square*2)*paints[i].price*(paints[i].type+1)<=budget){
            while(package_optional(paints[i].volume, square*(layers_number+1))*paints[i].price*(paints[i].type+1) < budget)
                layers_number++;
            current = paints[i];
            colorChoice = true;
            break;
        }
    }
    if (colorChoice){
        if (layers_number > 7)
            layers_number = 7;
        cout << "Стоимость краски в рублях: " << package_optional(current.volume, current.volume*layers_number)*current.price*(current.type+1) <<
        endl << "Цвет краски - " << current.color << endl << "Количество банок " << package_optional(current.volume, square*layers_number) << endl
        << "Количество слоёв для покраски: " << layers_number << endl << "Сорт краски: " << (current.volume?"высший":"стандартный") << endl;
    }
    else
        cout << "Невозможно покрасить - слишком низкий бюджет" << endl;
}

void MainMenu(int com, vector<paint_item> paints){
    if (com == 1){
        cout << endl << endl;
        cout << "Все виды красок: " << endl << endl;
        for (int i=0; i<paints.size(); i++){
            cout << "Цвет - " << paints[i].color << ", сорт - " << (paints[i].type?"высший":"стандартны")
            << ", цена - " << paints[i].price << ", объём банки - " << paints[i].volume << endl;
        }
        cout << endl << endl;
    }
    if (com == 2){
        cout << endl << endl;
        paint_item it;
        string command;
        double square=0, width, height;
        int layerNumber, paintsChoice;
        cout << "Введите + чтобы добавить стену и - чтобы добавить выподающий участок. Для продолжения - 0" << endl;
        cin >> command;
        while (command != "0"){
            if (command == "+"){
                cout << "Ширина: ";
                cin >> width;
                cout << "Высота: ";
                cin >> height;
                square += width*height;
            }
            else if (command == "-"){
                cout << "Ширина: ";
                cin >> width;
                cout << "Высота: ";
                cin >> height;
                square -= width*height;
                if (square < 0)
                    square = 0;
            }
            else{
                cout << "Такой команды не существует" << endl;
            }
            cin >> command;
        }
        cout << endl << endl;
        for (int i=0; i<paints.size(); i++){
            cout << i+1 << ") Цвет " << paints[i].color << " Цена - " << (paints[i].type+1)*paints[i].price << " ";
        }
        cout << endl << "Введите номер краски: ";
        cin >> paintsChoice;
        it = paints[paintsChoice-1];
        cout << "Введите количество слоёв: ";
        cin >> layerNumber;
        cout << endl << "Стоимость покраски составит - " << coloring_cost(square, it.type, it.price, layerNumber);
        cout << endl << endl << endl;
    }
    if (com == 3){
        double width, height, square=0;
        int budget;
        string command;
        cout << "Введите свой бюджет: ";
        cin >> budget;
        cout << "Введите + чтобы добавить стену и - чтобы добавить выподающий участок. Для продолжения - 0" << endl;
        cin >> command;
        while (command != "0"){
            if (command == "+"){
                cout << "Ширина: ";
                cin >> width;
                cout << "Высота: ";
                cin >> height;
                square += width*height;
            }
            else if (command == "-"){
                cout << "Ширина: ";
                cin >> width;
                cout << "Высота: ";
                cin >> height;
                square -= width*height;
                if (square < 0)
                    square = 0;
            }
            else{
                cout << "Такой команды не существует" << endl;
            }
            cin >> command;
        }
        cout << endl << endl;
        budget_options(square, budget, paints);
        cout << endl << endl;
    }
    //Справка
    if (com == 4){
        cout << endl << endl;
        cout << "Заполните справку";
        cout << endl << endl << endl;
    }
}

int main()
{
    vector<paint_item> paints;
    //Важно добавлять цвета в нужном порядке - сначало дорогие потом дешовые
    paints.push_back({1, "Красный", 5, 50});
    paints.push_back({1, "Синий", 5, 20});
    paints.push_back({1, "Чёрный", 5, 10});
    paints.push_back({0, "Белый", 5, 10});
    int command;
    cout << "Введите режим(1 - Справочник красок, 2 - Поверхность и стоимость, 3 - Нормы и ограничения, 4 - Справка, 5 - Выход): ";
    cin >> command;
    while (command != 5){
        MainMenu(command, paints);
        cout << "Введите режим(1 - Справочник красок, 2 - Поверхность и стоимость, 3 - Нормы и ограничения, 4 - Справка, 5 - Выход): ";
        cin >> command;
    }
    int width, height;
    return 0;
}
