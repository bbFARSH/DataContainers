#include <iostream>

using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
 
class Element
{
	int Data; // Значение элемента
	Element* pNext; // адрес следующего элемента
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "Econstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "Edustructor:\t" << this << endl;
	}
	friend class ForwardList;
};
class ForwardList
{
	Element* Head; // Точка входа, указывает на начальный элемент списка.
public:
	ForwardList()
	{
		this->Head = nullptr; // Если голова указывает на 0, то значит список пуст.
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	// сОздадим в нём секции  Adding Elements:
	void push_front(int Data)
	{
		// 1)Создаём элемент
		Element* New = new Element(Data);
		// 2)Присоединяем новый элемент к списку
		New->pNext = Head;
		// 3) Переносим голову на новый элемент
		Head = New;
	}
	void pop_front()
	{
		Head = Head->pNext;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext != NULL)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = NULL;
	}
	// Methods:
	void print()const
	{
		Element* Temp = Head; // Temp - это итератор
		// Итератор - это указатель при помощи которого можно получить доступ к элементам структуры данных
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; // Переход на следующий элемент
		}
	}
};
void main()
{
	setlocale(LC_ALL, "");
	int n; // Размер списка
	cout << "Введите размер списка "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	cout << endl;
	list.pop_front();
	list.print();
	cout << endl;
	list.pop_back();
	list.print();
	cout << endl;
}