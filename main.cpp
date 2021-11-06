#include <iostream>
#include <string>

//Добавляем пространство имён std
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
    //Конструктор копирования
    NamePrice(NamePrice &obj){
        this->length = obj.length;
        this->name = new string[length];
        this->cost = new int[length];
        for(int i=0; i<length; i++){
            this->cost[i] = obj.cost[i];
            this->name[i] = obj.name[i];
        }
    }
    //Перегрузка оператора =(для нормальной передачи в функцию)
    void operator=(NamePrice &obj){
        this->length = obj.length;
        this->name = new string[length];
        this->cost = new int[length];
        for(int i=0; i<length; i++){
            this->cost[i] = obj.cost[i];
            this->name[i] = obj.name[i];
        }
    }
    //Деструктор
    ~NamePrice(){
        delete [] name;
        delete [] cost;
    }
    //Метод для добавления позиции
    void Add(string Name, int Cost){
        //создаём массив имён который на один элемент больше старого
        string *out = new string[length+1];
        //создаём массив значений который на один элемент больше старого
        int *outCost = new int[length+1];
        //переносим элементы из основного массива в только что созданные
        for (int i = 0; i<length; i++){
            out[i] = name[i];
            outCost[i] = cost[i];
        }
        //Удаляет массивы
        delete [] name;
        delete [] cost;
        //Добавляем аргументы в массив
        out[length] = Name;
        outCost[length] = Cost;
        //Присваевам новый расширенный массив к старому указателю
        name = out;
        cost = outCost;
        //Меняем длину
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
    //Вывод всех имём отсортированного по значениям в порядке убывания
    string* AllNames(){
        string *out = new string[length];
        //Перенос массива
        for (int i = 0; i<length; i++){
            out[i] = name[i];
        }
        //Сортировка
        for (int i=0; i<length; i++){
            for (int j=i; j<length-1; j++){
                if (operator()(out[i])<operator()(out[i+1])){
                    swap(out[j], out[j+1]);
                }
            }
        }
        return out;
    }
    int l(){
        return length;
    }
};

class Painting{
    private:
        int budget, size;
        int paintConsuption, volume, container, countLayers, spent, countCans;
        string colorname;
        NamePrice paints;
    public:
        //Конструктор
        Painting(){
            budget = 0;
            size = 0;
        }
        //Конструктор для аргументов
        Painting(int budget, int size, NamePrice paints, int paintConsuption){
            this->budget = budget;
            this->size = size;
            this->paints = paints;
            this->paintConsuption = paintConsuption;
        }
        //Функция оптимального подсчёта покраски
        void OptimalPainting(){
            string *color = paints.AllNames();
            int cost;
            countLayers = -1;
            for (int i=0; i<paints.l(); i++){
                volume = size*paintConsuption;
                cost = paints(color[i]);
                if (cost*volume <= budget){
                    countLayers = ((budget/(cost*volume))<=5)?(budget/(cost*volume)):(5);
                    spent = cost*volume*countLayers;
                    colorname = color[i];
                    container = OptimalVolume(volume);
                    countCans = volume/container;
                    if (volume%container != 0)
                        countCans++;
                    break;
                }
            }
            delete [] color;
        }
        //Высчитывание оптимальной ёмкости
        int OptimalVolume(const int volume){
            int th = (3-volume%3)%3, f = (5-volume%5)%5, t=(10-volume%10)%10;
            if (t<=f&&t<=th)
                return 10;
            else if (f<=t&&f<=th)
                return 5;
            else
                return 3;
        }
        //Перезрузка вывода
        friend ostream& operator<<(ostream &out, Painting obj);
};
//Вывод
ostream& operator<<(ostream &out, Painting obj){
    if (obj.countLayers>0){
        out << endl << endl << "Красить " << obj.colorname << " краской в "  << obj.countLayers;
        if (obj.countLayers == 1)
            out << " слой";
        else if (obj.countLayers == 5)
            out << " слоёв";
        else
            out << " слоя";
        out << endl << "Нужно закупить " << obj.countCans;
        if ((obj.countCans>4&&obj.countCans<21)||obj.countCans%10==0||(obj.countCans%10>4&&obj.countCans%10<10))
            out << " банок";
        else if(obj.countCans==1)
            out << " банку";
        else
            out << " банки";
        out << " по " << obj.container;
        if (obj.container == 3)
            out << " литра" << endl;
        else
            out << " литров" << endl;
        int extra = obj.countCans*obj.container-obj.volume;
        if (extra!=0){
            out << "Останутся лишними " << extra;
            if (extra == 1)
                out << " литр";
            else if (obj.countLayers >= 5)
                out << " литров";
            else
                out << " литра";
            cout << " краски" << endl;
        }
        out << "Будет потрачено " << obj.spent << " рублей";
    }
    else
        out << "Невозможно покрасить такую площать при таком маленьком бюджетом!!!";
    return out;
}

int main(){
    //Локализация(часть компиляторов на переваривает русский)
    setlocale(LC_ALL, "Russian");
    //Объект с красками
    NamePrice paints;
    //Добавление краски
    paints.Add("красной эмалевой", 2);
    paints.Add("синей клеевой", 15);
    paints.Add("белой водоэмульсионной", 5);
    //Расход краски на метр квадратный для обного слоя
    const int paintConsuption = 1;
    int budget, size;
    //Ввод
    cout << "На какую сумму вы хотите покрасить: ";
    cin >> budget;
    cout << "Какой метраж вы хотите покрасить: ";
    cin >> size;
    //Создание класса покраски
    Painting p(budget, size, paints, paintConsuption); 
    //Вызов метода для оптимального подсчёта
    p.OptimalPainting();
    //Вывод
    cout << p;
    cout << endl << endl;
    //Конец программы
    return 0;
}
