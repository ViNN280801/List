#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <list>

using namespace std;

template<typename T>
struct dataS
{
	T Data;		// Данные
	dataS<T> *next;	// Адрес следующего элемента списка
	dataS<T> *previous; // Адрес предыдущего элемента списка
};

template<typename T>
class SList {
	dataS<T> *first;								// Адрес первого элемента списка
	dataS<T> *last;								// Адрес последнего элемента списка
	size_t count;								// Количество элементов в списке
	size_t iterator;                              // Итератор
private:
	dataS<T> *buffer(dataS<T>* next);
	dataS<T> *buffer(dataS<T> *next, size_t pos, int kol);
	void buffer(dataS<T> *next, const SList<T> &Data, int i); //возвращает структуру по указанному адресу и рекурсивно приходят следующий элемент
	void del_element();
public:
	SList();									// конструктор по умолчанию
	SList(const SList<T>&Data);					// конструктор копирования
	SList(SList<T>&&Data);						// конструктор перемещения
	SList<T>& operator=(const SList<T>&Data);	// оператор равно копированием
	SList<T>& operator=(SList<T>&&Data);		// оператор равно перемещением
	T& operator[](size_t pos);					// оператор индексирования

	void AddToHead(const T &Data);				// добавление элемента в начало 
	void AddToTail(const T &Data);				// добавление элемента в конец 
	T front();									// возвращает первое значение
	T back();									// возвращает последнее значение
	T DeleteFromHead();							// удаление первого элемента
	T DeleteFromTail();							// удаление последнего элемента
	void DeleteAll();							// удаление всех элементов
	void Show();								// отображение всех элементов
	size_t size();								// количество элементов

	void begin();								// Возвращает итератор уакзываающий на начало списка

	bool next();								// Перемещает итератор на следующий элемент
	T& get();									// Получить значение по текущей позиции итератора

	void InsertAt(size_t pos, const T &Data);	// вставка в указанную позицию
	void DeleteAt(size_t pos);					// удаление по указанной позиции
	size_t Find(const T&Data);					// поиск элемента (0 в случае неудачи)
	void FindAndReplace(const T&Data, const T&replData);	// поиск и замена всех элементов

	~SList();									// деструктор
};

template<typename T>
void PrintList(const list<T> &lst)
{
	for (int i = lst.cbegin(); i != lst.cend(); ++i)  //cbegin = const begin
		cout << *i << endl;                           //cend = const end
}
int main() {
	srand(time_t(NULL));
	SList<int> first, second;

#pragma region LibraryList
	list<int> myList = { 15, 45, 213, 12, 421 };
	
	myList.push_front(1);
	myList.push_back(1000);
	PrintList(myList);


	myList.size();
	PrintList(myList);

	myList.sort();
	PrintList(myList);

	myList.reverse();
	PrintList(myList);
#pragma endregion

	int size = rand() % 100;

	for (int i = 0; i < size; i++) {
		first.AddToHead(rand() % 10);
	}
	first.Show();

	first.DeleteFromHead();
	first.DeleteFromTail();
	first.Show();

	size = rand() % 100;
	for (int i = 0; i < size; i++) {
		second.AddToHead(rand() % 10);
	}
	second.Show();

	second.AddToTail(rand() % 10);
	second.Show();

	SList<int> third(second);
	third.Show();

	SList<int> fourth;
	fourth = first;
	fourth.Show();

	size = fourth.size();
	for (int i = 0; i < size; i++) {
		int value = fourth[i];
		cout << value << " " << endl;
	}

	first.DeleteAt(3);
	first.Show();

	first.InsertAt(4, 4);
	first.Show();

	first.DeleteAll();
	first.Show();

	size_t result = first.Find(10);
	if (result != 0)
		cout << "The number ten is in position: " << result << endl;
	else
		cout << "Numbers ten not found" << endl;

	first.FindAndReplace(10, 1000);

	first.begin();
	while (first.next())
		cout << first.get() << " ";

	cin.get();
	return 0;
}

template<typename T>
dataS<T>* SList<T>::buffer(dataS<T>* next, size_t pos, int kol)
{
	if ((next->next != NULL) || (pos == kol))
		return 	buffer(next->next, pos, ++kol);
	else return next;

	return 0;
}

template<typename T>
void SList<T>::buffer(dataS<T>* next, const SList<T>& Data, int i)
{
	if (next == NULL || i == Data.count)
	{
		next = new dataS<T>;
		next->Data = Data[i];
		buffer(next->next, Data, ++i);
	}
	delete next;
}

template<typename T>
dataS<T>* SList<T>::buffer(dataS<T>* next)
{
	if (next->next != NULL)
		return 	buffer(next->next);
	else return next;

	return EXIT_SUCCESS;
}

template<typename T>
void SList<T>::del_element()
{
	if (last != NULL)
	{
		dataS<T>*delete_ = last;
		for (;;) {
			if (delete_ != NULL) {
				last = delete_->previous;
				delete delete_->next;
			}
			else break;
		}
	}
}

template<typename T>
SList<T>::SList()
{
	first = nullptr;
	last = nullptr;
	count = NULL;
	iterator = -1;
}

template<typename T>
SList<T>::SList(const SList<T>& Data)
{
	count = Data.count;
	iterator = -1;
	buffer(first, Data, 0);
	last = buffer(first, Data.count - 1, 0);
}

template<typename T>
SList<T>::SList(SList<T>&& Data)
{
	this->first = Data.first;
	this->last = Data.last;
	this->count = Data.count;
	this->iterator = Data.iterator;

	Data.first = nullptr;
	Data.last = nullptr;
	Data.count = NULL;
	Data.iterator = -1;

	return *this;
}

template<typename T>
SList<T>& SList<T>::operator=(const SList<T>& Data)
{
	this->first = Data.first;
	this->last = Data.last;
	this->count = Data.count;
	this->iterator = Data.iterator;

	return *this;
}

template<typename T>
SList<T>& SList<T>::operator=(SList<T>&& Data)
{
	this->first = Data.first;
	this->last = Data.last;
	this->count = Data.count;
	this->iterator = Data.iterator;

	Data.first = nullptr;
	Data.last = nullptr;
	Data.count = NULL;
	Data.iterator = -1;

	return *this;
}

template<typename T>
T& SList<T>::operator[](size_t pos)
{
	if (first != NULL)
		return buffer(first, pos, 0)->Data;

	return buffer(nullptr, NULL, NULL)->Data;
}

template<typename T>
void SList<T>::AddToHead(const T & Data)
{
	dataS<T> second_;
	second_.next = this->first;
	first->previous = &second_;
	second_.previous = NULL;
	this->first = &second_;
	second_.Data = Data;
}

template<typename T>
void SList<T>::AddToTail(const T & Data)
{
	dataS<T> second_;
	second_.next = nullptr;
	first->previous = &second_;
	second_.previous = this->last;
	this->last = &second_;
	second_.Data = Data;
}

template<typename T>
T SList<T>::front()
{
	return first->Data;
}

template<typename T>
T SList<T>::back()
{
	return last->Data;
}

template<typename T>
T SList<T>::DeleteFromHead()
{
	dataS<T>*temp = first->next;
	T returnData = first->Data;
	delete first;
	first = temp;

	return returnData;
}

template<typename T>
T SList<T>::DeleteFromTail()
{
	dataS<T>*temp = last->previous;
	T returnData = last->Data;
	delete last;
	last = temp;

	return returnData;
}

template<typename T>
void SList<T>::DeleteAll()
{
	del_element();
	iterator = -1;
	count = NULL;
	first = nullptr;
	last = nullptr;
}

template<typename T>
void SList<T>::Show()
{
	if (first != NULL)
	{
		dataS<T>*temp_Data = first;
		for (;;)
		{
			if (temp_Data->next != NULL) {
				cout << temp_Data->Data << " ";
				temp_Data = temp_Data->next;
			}
			else break;
		}
	}
}

template<typename T>
size_t SList<T>::size()
{
	return this->count;
}

template<typename T>
void SList<T>::begin()
{
	iterator = -1;
}

template<typename T>
bool SList<T>::next()
{
	iterator++;
	if (buffer(first, iterator, 0) != NULL)
		return true;
	else return false;
}

template<typename T>
T & SList<T>::get()
{
	return buffer(first, iterator, 0)->Data;
}

template<typename T>
void SList<T>::InsertAt(size_t pos, const T & Data)
{
	dataS<T> *new_element = new dataS<T>;
	new_element->Data = Data;
	new_element->next = buffer(first, pos, 0);
	new_element->previous = buffer(first, --pos, 0);
	new_element->next->previous = new_element;
	new_element->previous->next = new_element;
}

template<typename T>
void SList<T>::DeleteAt(size_t pos)
{
	dataS<T> *temp = buffer(first, pos, 0);
	temp->previous->next = temp->next->previous;

}

template<typename T>
size_t SList<T>::Find(const T & Data)
{
	size_t check = 0;
	dataS<T> *data_Temp;
	if (first != NULL)
	{
		data_Temp = first;
		for (;;)
		{
			++check;
			if (data_Temp->Data == Data)
				return check;
			else if (check == count)
				return NULL;
		}
	}
}

template<typename T>
void SList<T>::FindAndReplace(const T & Data, const T & replData)
{

}

template<typename T>
SList<T>::~SList()
{
	del_element();
}
