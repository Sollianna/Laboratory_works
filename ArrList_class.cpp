#include <iostream>
#include <conio.h>
using namespace std;

class ArrList
{
private:

	int N;
    char* arr; //символ

	int add_back(char* arr, int first, int& N)
	{
        char* arr1 = new char[N + 10];
        for (int j = 0; j < N; j++)
        {
            arr1[j] = arr[j];
        }
        first = N - 1;
        N = N + 10;
        arr = arr1;
        delete [] arr;
        return first;
	}

public:

	ArrList()
	{
		N = 10;
        arr = new char[N];
		arr[0] = 0;
	}

    /*~ArrList()
    {
        delete[] arr;
    }*/

	void Get()
	{
        int end = 0;
        int i = 0;
        int first = 0;
        int enter = 0;
        bool c_out = 0;

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
                first = add_back(arr, first, N);
            }
        }
        cout << '\n';
	}

    int Read(int N)
    {
        return arr[N];
    }
};

class Stek
{
private:
    int size = 0;
    int N_S = 10;
    char* stek;
    void add_back()
    {
        char* arr1 = new char[N_S + 10];
        for (int j = 0; j < N_S; j++)
        {
            arr1[j] = stek[j];
        }
        N_S = N_S + 10;
        stek = arr1;
        delete[] stek;
    }

public:
    Stek()
    {
        N_S = 10;
        stek = new char[N_S];
        stek[0] = 0;
    }

    ~Stek()
    {
        delete[] stek;
    }

    void Push(char el)
    {
        stek[size] = el;
        if (size == N_S - 1)
        {
            add_back();
        }
        size++;
        stek[size] = 0;
    }

    int Pop()
    {
        size = size - 1;
        char time = stek[size];
        stek[size] = 0;
        return time;
    }

    int Read(int N)
    {
        return stek[N];
    }

};

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

int main()
{
    //ввод выражения + вывод для проверки корректности ввода
	ArrList arr1;
    arr1.Get();

    //перевод выражения в постфиксную форму
    int k = 0;
    int sig = 0;
    int i = 0;
    Stek S_first;

    while (arr1.Read(i) != 0)
    {
        char now = arr1.Read(i);
        if ((now > 47) && (now < 58))
            cout << now;
        else
        {
            char next = arr1.Read(i + 1);
            if ((next > 47) && (next < 58) && (next != 0) || ((next == 40) || (next == 41) || (now == 41)))
            {
                cout << " ";
                // проверка значимости
                if (k == 0)
                {
                    S_first.Push(now);
                    k++;
                }
                else
                {
                    char stek_early = S_first.Read(k - 1);
                    if (((k > 0) && (significacion(now) > significacion(stek_early))) || ((now == 40) || (stek_early == 40)))
                    {
                        S_first.Push(now);
                        k++;
                    }
                    else
                    {
                        if ((now == 41) && (k > 0))//если закрывающая скобка очистить до открывающей скобки
                        {
                            while (S_first.Read(k - 1) != 40)
                            {
                                if ((S_first.Read(k - 1) != 40) && (S_first.Read(k - 1) != 41))
                                {
                                    char a = S_first.Pop();
                                    cout << a << " ";
                                }
                                else
                                    S_first.Pop();
                                k--;
                            }
                            S_first.Pop();
                            k--;
                        }
                        else
                        {
                            while ((k > 0) && (now != 41) && (significacion(now) <= significacion(S_first.Read(k - 1))))
                            {
                                if ((S_first.Read(k) != 40) && (S_first.Read(k) != 41))
                                {
                                    char a = S_first.Pop();
                                    cout << a << " ";
                                }
                                else
                                    S_first.Pop();
                                k--;
                            }
                            S_first.Push(now);
                            k++;
                        }
                    }
                }
            }
            else
            {
                cout << "\n" << "Error. Two or more operations in a row";
                return(0);
            }
        }

        i++;
    }

    while (k > 0)
    {
        char a = S_first.Pop();
        cout << " " << a;
        k--;
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