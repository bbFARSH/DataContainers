#include <iostream>

using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
 
class Element
{
	int Data; // Значение элемента
	Element* pNext; // адрес следующего элемента
	static int count; // КОЛИЧЕСТВО ЭЛЕМЕНТОВ
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "Econstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "Edustructor:\t" << this << endl;
	}
	friend class ForwardList;
};
int Element::count = 0; // Статические переменные могут быть проинициализированы только за классом.
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
	void push_back(int Data)
	{
		if (Head == nullptr)return	push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;
		Temp->pNext = new Element(Data);

	}
	void pop_front()
	{
		Element* erased = Head;
		 Head = Head->pNext;
		 delete erased;
	}
	void pop_back()
	{
		if (Head->pNext == nullptr) return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}
	void insert(int Data, int Index)
	{
		if (Index > Head->count)
		{
			cout << "Error: Выход за пределы списка, попробуйте соблюдать границы" << endl;
			return;
		}
		if (Index == 0 || Head == nullptr) return push_front(Data);
	    //1) Создаём новый элемент
		Element* New = new Element(Data);
		//2) Доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < Index-1; i++) Temp = Temp->pNext;
		// Осуществляем вставку нового элемента в список
		//3 Привязываем
		New->pNext = Temp->pNext;
		Temp->pNext = New;
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
		cout << "Количество элементов списка: " << Head->count << endl;
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
		list.push_back(rand() % 100);	
	}
	list.print();
	cout << endl;
	list.pop_front();
	list.print();
	cout << endl;
	list.pop_back();
	list.print();
	cout << endl; 
	list.push_back(123);
	list.print();
	cout << endl;
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента:\n"; cin >> index;
	cout << "Введите Значение добавляемого элемента:\n"; cin >> value;
	list.insert(value, index);
	list.print();
}