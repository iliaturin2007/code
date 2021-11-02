#include <iostream>
#include <string>

using namespace std;


//Класс NamePrice для добавления позиций
class NamePrice{
    //Динамические массивы - что бы память расширялась
    string *name;
    int *cost;
    //Длиная массива(нужна чтобы понять сколько элементов в массиве)
    int length;
    public:
    //Конструктор
    NamePrice(){
        name = nullptr;
        cost = nullptr;
        length = 0;
    }
    //Деструктор
    ~NamePrice(){
        delete [] name;
        delete [] cost;
    }
    //Метод для добавления позиции
    void Add(string Name, int Cost){
        string *out = new string[length+1];
        int *outCost = new int[length+1];
        for (int i = 0; i<length; i++){
            out[i] = name[i];
            outCost[i] = cost[i];
        }
        delete [] name;
        delete [] cost;
        out[length] = Name;
        outCost[length] = Cost;
        name = out;
        cost = outCost;
        length++;
    }
    //Перегруженый оператор () для получения цены по позиции (возвращает ноль, если позиция не существует)
    int operator()(string str){
        for(int i=0; i<length; i++){
            if (str == name[i])
                return cost[i];
        }
        return 0;
    }
    //Метод возвращающий названия позиций в скобках через запятую
    string Out(){
        string out;
        out.push_back('(');
        out.append(name[0]);
        for(int i=1; i<length; i++){
            out.push_back(',');
            out.push_back(' ');
            out.append(name[i]);
        }
        out.push_back(')');
        return out;
    }

};


int main(){
    //Локализация(часть компиляторов на переваривает русский)
    setlocale(LC_ALL, "Russian");
    //Объекты класса NamePrice для хранения цветов и типов предметов для покраски
    NamePrice colorTypes, type;
    //Добавление позиций
    colorTypes.Add("Белый", 1);
    colorTypes.Add("Синий", 2);
    colorTypes.Add("Красный", 3);
    type.Add("Кисть", 3);
    type.Add("Валик", 4);
    //Переменный размера потолка, цены краски
    int size, countPaint;
    //Строки принимающие цвет и предмет для покраски
    string color, item;
    //Куча ввода-вывода(тут вроде всё просто и понятно)
    cout << "Площадь потолка в метрах: ";
    cin >> size;
    cout << "Количество литров краски на 1 квадратный метр: ";
    cin >> countPaint;
    cout << "Цвет краски: " << colorTypes.Out();
    cin >> color;
    cout << "Чем будете красить: " << type.Out();
    cin >> item;
    //Перемножение всех данных
    int ans = size*countPaint*colorTypes(color)*type(item);
    //Если произведение равно нулю - то данные неверны(тк при введении невеной позиции возвращает 0)
    if (ans == 0)
        cout << "Введены неверные данные";
    //Иначе выводим результат
    else
        cout << "Стоимость покраски составит - " << ans << " рублей";
    //Вывод двух пустых строк(для разделения)
    cout << endl << endl;
    //Окончание программы(по стандарту c++ функция main должна возвращать 0, ведь в случает ошибки будет возвращено другое значение)
    return 0;
}
