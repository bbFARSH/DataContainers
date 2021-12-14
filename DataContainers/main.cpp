#include<iostream>
using namespace std;
using std::cout;
using std::endl;
using std::cin;
#define tab "\t"
#define DEBUG
class Element
{
	int Data;//�������� ��������
	Element* pNext;//����� ���������� ��������
	static int count; //���-�� ���������
public:
	int getData()const
	{
		return Data;
	}
	Element* getpNext()const
	{
		return pNext;
	}
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend class Iterator;
};

int Element::count = 0;//���� ���������� ����� ���� ������������������� ������ �� �������

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
#ifdef DEBUG
		cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Iterator()
	{
#ifdef DEBUG
		cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
	}

	//            OPERATORS:
	Iterator& operator++() // Prefix increment	
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator& operator++(int) // Suffix increment	
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	const int operator*()const
	{
		return Temp->Data;
	}
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other) const
	{
		return this->Temp != other.Temp;
	}
	operator bool()const
	{
		return Temp;
	}
};
class ForwardList
{
	Element* Head;//��������� �� ��������� �������.�������� ������ ����� � ������
	size_t size;//=unsigned int
public:
	Element* getHead()const
	{
		return Head;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	// CONSTRUCTORS:

	ForwardList()
	{
		this->Head = nullptr;//���� ������ ��������� �� 0, ������ ������ ����
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		for (const int* it = il.begin(); it != il.end(); it++)
		{
			//it - �������� ��� ����������� �� il
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other)
	{
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) this->push_back(Temp->Data);
		cout << "LCopyConstructor: " << this << endl;
	}
	~ForwardList()
	{
		while (Head) pop_front();//��������� �������� ������ ����� ���������
		cout << "LDestructor:\t" << this << endl;
		cout << "---------------------------------------------------\n";
	}
	//Operators

	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other) return *this;
		while (Head) pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) this->push_back(Temp->Data);
		cout << "LCopyConstructor: " << this << endl;
		return *this;
	}

	//Adding elements
	void push_front(int Data)
	{
		/*//1)������� �������
		Element* New = new Element(Data,Head);
		//2)������������ ����� ������� � ������
		New->pNext = Head;
		//3)��������� ������ �� ����� �������
		Head = New;*/

		Head = new Element(Data, Head);
		size++;

	}

	void push_back(int Data)
	{
		if (Head == nullptr) return	push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext) Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}

	//Erasing elements

	void pop_front()
	{
		//1)���������� ����� ���������� ��������
		Element* Erased = Head;
		//2)��������� ������� �� ������
		Head = Head->pNext;
		//3)������� ������� �� ������
		delete Erased;
		size--;
	}
	void pop_back()
	{
		if (Head->pNext == nullptr) return pop_front();
		//1)������� �� �������������� ��������
		Element* Temp = Head;
		while (Temp->pNext->pNext) Temp = Temp->pNext;
		//�� ��������� � ������������� ��������
		//2)������� ��������� ������� �� ������
		delete Temp->pNext;
		//3)�������� �� ��������� ��������, �� ���� �������� ��� ����� �����
		Temp->pNext = nullptr;
		//������ Temp �������� ��������� ��������� ������
		size--;
	}

	void insert(int Data, int Index)
	{
		if (Index > Head->count)
		{
			cout << "����� �� ������� ������" << endl;
			return;
		}
		if (Index == 0 || Head == nullptr)return push_front(Data);
		//0)������� �� ������� ��������
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		//1)������� ����� �������
		/*Element* New = new Element(Data);
		//�c���������� ������� ������ �������� � ������
		//2)����������� ����� ������� � ������
		New->pNext = Temp->pNext;
		//3)�������� ������� � ������
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	void erase(int Index)
	{
		//����������� �����
		if (Index > Head->count)
		{
			cout << "����� �� ������� ������" << endl;
			return;
		}
		if (Index == 0) return pop_front();
		if (Index == Head->count - 1) return pop_back();

		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
		size++;

	}


	void print()const
	{
		/*Element* Temp = Head;//Temp-��������,� ��� ��� ����� �������� ������
		//� ��������� ��������� ������
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;//������� �� ���� �������
		}*/

		//for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		//for (Iterator Temp = Head; Temp!=nullptr; Temp++)
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		for (Iterator Temp = Head; Temp != nullptr; Temp++)
			cout << *Temp << tab;
		cout << "���������� ��������� � ������: " << size << endl;
		cout << "����� ���������� ���������: " << Head->count << endl;
	}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList result = left;
	//for (Element* Temp = right.getHead(); Temp; Temp = Temp->getpNext()) // �������� �� ������� ������
	//	result.push_back(Temp->getData()); // ��������� ��� ��� �������� � ����� ����������
	for (Iterator Temp = right.getHead(); Temp; Temp++)
	{
		result.push_back(*Temp);
	}
	return result;
}

//#define BASE_CHECK
//#define COUNT_CHECK
//#define COPY_METHODS_CHECK
//#define operator_plus_check
//#define RANGE_BASED_FOR_ARR
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;//������ ������
	cout << "������ ������ ������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	/*list.pop_back();
	list.print();*/
	int Index;
	int value;
	cout << "������� ������ ������������ ��������: "; cin >> Index;
	cout << "������� �������� ������������ �������: "; cin >> value;
	list.insert(value, Index);
	list.print();
	/*cout << "������� ������ ���������� ��������: "; cin >> Index;
	list.erase(Index);
	list.print();*/
#endif // BASE_CHECK
#ifdef COUNT_CHECK

	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(894);

	list1.print();
	list2.print();
#endif // COUNT_CHECK
#ifdef COPY_METHODS_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	//list1 = list1;
	list1.print();

	//ForwardList list2 = list1;//CopyConstructor
	ForwardList list2;
	list2 = list1;//CopyAssignments
	list2.print();
#endif // COPY_METHODS_CHECK

	/*int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
		cout << arr[i] << tab;
	cout << endl;*/
#ifdef operator_plus_check
	ForwardList list1 = { 3,5,8,13,21 };
	list1.print();
	ForwardList list2 = { 34,55,89 };
	list2.print();
	ForwardList list3 = list1 + list2;
	list3.print();
#endif // operator_plus_check
#ifdef RANGE_BASED_FOR_ARR
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
		cout << arr[i] << tab;
	cout << endl;
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARR
	ForwardList list = { 3,5,8,13,21 };
	cout << "\n---------------------------------\n";
	for (int i : list)
	{
		cout << i << tab;
	}cout << endl;
	cout << "\n---------------------------------\n";
}