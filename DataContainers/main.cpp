#include <iostream>

using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
 
class Element
{
	int Data; // �������� ��������
	Element* pNext; // ����� ���������� ��������
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
		Element* Temp = Head; // Temp - ��� ��������
		// �������� - ��� ��������� ��� ������ �������� ����� �������� ������ � ��������� ��������� ������
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; // ������� �� ��������� �������
		}
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