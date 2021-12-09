#include <iostream>

using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
 
class Element
{
	int Data; // �������� ��������
	Element* pNext; // ����� ���������� ��������
	static int count; // ���������� ���������
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
int Element::count = 0; // ����������� ���������� ����� ���� ������������������� ������ �� �������.
class ForwardList
{
	Element* Head; // ����� �����, ��������� �� ��������� ������� ������.
public:
	ForwardList()
	{
		this->Head = nullptr; // ���� ������ ��������� �� 0, �� ������ ������ ����.
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	// �������� � �� ������  Adding Elements:
	void push_front(int Data)
	{
		// 1)������ �������
		Element* New = new Element(Data);
		// 2)������������ ����� ������� � ������
		New->pNext = Head;
		// 3) ��������� ������ �� ����� �������
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
			cout << "Error: ����� �� ������� ������, ���������� ��������� �������" << endl;
			return;
		}
		if (Index == 0 || Head == nullptr) return push_front(Data);
	    //1) ������ ����� �������
		Element* New = new Element(Data);
		//2) ������� �� ������� ��������
		Element* Temp = Head;
		for (int i = 0; i < Index-1; i++) Temp = Temp->pNext;
		// ������������ ������� ������ �������� � ������
		//3 �����������
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}
	// Methods:
	void print()const
	{
		Element* Temp = Head; // Temp - ��� ��������
		// �������� - ��� ��������� ��� ������ �������� ����� �������� ������ � ��������� ��������� ������
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; // ������� �� ��������� �������
		}
		cout << "���������� ��������� ������: " << Head->count << endl;
	}
};
void main()
{
	setlocale(LC_ALL, "");
	int n; // ������ ������
	cout << "������� ������ ������ "; cin >> n;
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
	cout << "������� ������ ������������ ��������:\n"; cin >> index;
	cout << "������� �������� ������������ ��������:\n"; cin >> value;
	list.insert(value, index);
	list.print();
}