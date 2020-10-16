#include <iostream>
#include <conio.h>
using namespace std;

int significacion(char a)
{
    int sig;
    if ((a == 40) || (a == 41)) // ( )
        sig = 0;
    else if ((a == 43) || (a == 45)) // + -
        sig = 1;
    else if ((a == 42) || (a == 47)) // * /
        sig = 2; 
    else if (a == 94) // ^
        sig = 3;
    else
    {
        cout << "invalid character";
        sig = -1;
    }
    return sig;
}

//реализация списка
class List
{
public:
    List();

    //добить элемент в конец списка
    void add_back(char data);

    //узнать длинну списка
    int get_lenght() { return lenght; }
    char& operator[](const char index);

private:

    class Node //узел - структура элемента списка
    {
    public:
        Node* nexst_node;
        char data;
        Node(char data = 0, Node* pNext = nullptr)
        {
            this->data = data;
            this->nexst_node = pNext;
        }
    };
    int lenght;
    Node* first;
};

List::List()
{
    lenght = 0;
    first = nullptr;
}

void List::add_back(char data)
{
    if (first == nullptr)
    {
        first = new Node(data);
    }
    else
    {
        Node* current = this->first;
        while (current->nexst_node != nullptr)
        {
            current = current->nexst_node;
        }
        current->nexst_node = new Node(data);
    }
    lenght++;
}

char& List::operator[](const char index)
{
    char counter = 0;
    Node* current = this->first;
    while (current != nullptr)
    {
        if (counter == index)
        {
            return current->data;
        }
        current = current->nexst_node;
        counter++;
    }
}


int main()
{
    bool end = 0;
    bool c_out = 0;
    int i = 0;
    int first = 0;
    int N = 10;
    int enter = 0;
    char* arr = new char[N];

    //ввод выражения + вывод для проверки корректности ввода

    while (end == 0)
    {
        for (i = first; i < N - 1; i++)
        {
            enter = _getch();
            if (enter == 13)
                break;
            arr[i] = enter;
            cout << arr[i];
            arr[i + 1] = '\0';
        }
        if ((enter == 13) && (c_out == 0))
        {
            arr[i] = 0;
            cout << '\n';
            int j = 0;
            while (arr[j] != '\0')
            {
                cout << arr[j];
                j++;
            }
            c_out = 1;
            end = 1;
        }
        if (i == N - 1)
        {
            char* arr1 = new char[N];
            for (int j = 0; j < N; j++)
            {
                arr1[j] = arr[j];
            }
            delete[] arr;
            first = N - 1;
            N = N + 10;
            arr = new char[N];
            for (int j = 0; j < first; j++)
            {
                arr[j] = arr1[j];
            }
            delete[] arr1;
        }
    }
    cout << '\n';

    //перевод выражения в постфиксную форму

    int N_S = 10;
    char* stek = new char[N_S];
    int k = 0;
    int sig = 0; //significance - значимость

    for (i = 0; arr[i] != 0; i++)
    {
        if ((arr[i] > 47) && (arr[i] < 58))
            cout << arr[i];
        else
        {
            //if ((arr[i + 1] > 47) && (arr[i + 1] < 58) && (arr[i + 1] != 0))
            if (((arr[i + 1] > 47) && (arr[i + 1] < 58) && (arr[i + 1] != 0))||((arr[i + 1] == 40) || (arr[i + 1] == 41) || (arr[i] == 41)))
            {
                cout << " ";
                // проверка значимости
                if (k == 0)
                {
                    stek[k] = arr[i];
                    stek[k + 1] = 0;
                    k++;
                }
                else
                {
                    if (((k > 0) && (significacion(arr[i]) > significacion(stek[k - 1])))||(arr[i] == 40))//если выше - записываем
                    {
                        stek[k] = arr[i];
                        stek[k + 1] = 0;
                        k++;
                    }
                    else
                    {
                        if ((arr[i] == 41) && (k > 0))//если закрывающая скобка - очищаем стек
                        {
                          
                            int t;
                            for (t = k; t > 0; t--)
                            {
                                if ((stek[t - 1] != 40) && (stek[t - 1] != 41))
                                {
                                    cout << " " << stek[t - 1];
                                }
                                stek[t - 1] = 0;
                                k--;
                            }
                          
                        }
                        while ((k > 0) && (significacion(arr[i]) <= significacion(stek[k - 1])))//если ниже - выводим стек, пока не станет выше и записываем
                        {
                            cout << stek[k - 1] << " ";
                            k--;

                        }
                        stek[k] = arr[i];
                        stek[k + 1] = 0;
                        k++;
                    }
                }
                if (k == N_S - 1)//проверяем, не пора ли раширить стек
                {
                    char* stek1 = new char[N];
                    for (int j = 0; j < N; j++)
                    {
                        stek1[j] = stek[j];
                    }
                    delete[] stek;
                    int p = N_S - 1;
                    N_S = N_S + 10;
                    stek = new char[N_S];
                    for (int j = 0; j < p; j++)
                    {
                        stek[j] = stek1[j];
                    }
                    delete[] stek1;
                }
            }
            else
            {
                cout << "\n" <<"Error. Two or more operations in a row";
                return(0);
            }
        }
    }
    //вывод остатков стека
    if (k > 0)
    {
        for (i = k; i > 0; i--)
        {
            if ((stek [i-1] != 40) && (stek [i-1] != 41))
                cout << " " << stek[i-1];
        }
    }
    //список
    List lst;
    char a;
    //работа со списком. Ввод по Enter, завершение ввода вводом символа #. Так как в основной программе не используется - закомментировала
   /* do
    {
        cin >> a;
        lst.add_back(a);

    } while (a != '#');
    for (int i = 0; i < lst.get_lenght(); i++)
    {
        cout << lst[i] << endl;
    }*/
    return 0;
}
