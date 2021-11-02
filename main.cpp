#include <iostream>
#include <string>

using namespace std;

class NamePrice{
    string *name;
    int *cost;
    int length;
    public:
    NamePrice(){
        name = nullptr;
        cost = nullptr;
        length = 0;
    }
    ~NamePrice(){
        delete [] name;
        delete [] cost;
    }
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
    int operator()(string str){
        for(int i=0; i<length; i++){
            if (str == name[i])
                return cost[i];
        }
        return 0;
    }
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
    setlocale(LC_ALL, "Russian");
    NamePrice colorTypes, type;
    colorTypes.Add("Белый", 1);
    colorTypes.Add("Синий", 2);
    colorTypes.Add("Красный", 3);
    type.Add("Кисть", 3);
    type.Add("Валик", 4);
    int size, countPaint;
    string color, item;
    cout << "Площадь потолка в метрах: ";
    cin >> size;
    cout << "Количество литров краски на 1 квадратный метр: ";
    cin >> countPaint;
    cout << "Цвет краски: " << colorTypes.Out();
    cin >> color;
    cout << "Чем будете красить: " << type.Out();
    cin >> item;
    
    int ans = size*countPaint*colorTypes(color)*type(item);
    if (ans == 0)
        cout << "Введены неверные данные";
    else
        cout << "Стоимость покраски составит - " << ans << " рублей";

    cout << colorTypes.Out();
    cout << endl << endl;
    return 0;
}
