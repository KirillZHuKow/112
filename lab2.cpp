//треугольная матрица и стек 
#include <iostream>
#include <math.h>
template <class T>
class DynamicArray{
private:
    //поля
    T* data;//элементы
    int size;//количество элементов 
    int capacity;//вместимость массива
public:
    //создание
    DynamicArray(){//конструктор по умолчанию
        data = NULL;
        size = 0;
        capacity = 0;
    }


    void Delete(){//удаление массива
        delete[] this->m_DATA;
    }
    DynamicArray(int size){//конструктор с числом элементов
        size = size;
        capacity = size;
        data = new T[size];
    }

    DynamicArray(T* items,int count){//копирование элементов(в том числе из переданного массива)
        if(items == nullptr){
            data= nullptr;
            size = 0;
            capacity = 0;
        }
        else{
            size = count;			
            capacity = count;
            data = new T[count];
            for (int i = 0; i < count; ++i)
            {
                data[i] = items[i];
            }
        }
    }

    DynamicArray(const DynamicArray<T> &dynamicArray){//копирующий конструктор
        if(&dynamicArray == nullptr){
            data = nullptr;
            size = 0;
            capacity = 0;
        }
        else{
            size = dynamicArray.size;
            capacity = size;
            data = new T[size];
            for (int i = 0; i < dynamicArray.size; ++i)
            {
                data[i] = dynamicArray.data[i];
            }
        }
    }

    //операции
    void Resize(int newSize){//перераспределение памяти
        if(newSize > capacity){
            int new_capacity = std::max(2 * size, newSize);
            T* new_data = new T[new_capacity];
            for (int i = 0; i < size; ++i)
            {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
        size = newSize;
    }

    T Get(int index){//возвращение элемента по индексу
        if(index < 0 || index >= capacity)
            throw "\nGet Message : Index Out Of Range\n";
        return data[index];
    }

    void Set(int index,T value){//задаём элемент по индексу
        if(index < 0 || index > capacity)
            throw "\nSet Message : Index Out Of Range\n";
        data[index] = value;

    }

    int GetSize() const{//получить размера массива
        return size;
    }

    void Append(T val){//добавить в конец массива
        Resize(size + 1);
        data[size - 1] = val;
    }

    void Prepend(T val){//добавить в начало массива
        Resize(size + 1);
        for (int i = size - 2; i >= 0; --i)
        {
            data[i + 1] = data[i];
        }
        data[0] = val;
    }

    T & operator [] (int i){//перегрузка оператора "[]" 
        return data[i];
    }

    void Print(){
        if(size > 0 && data != nullptr){
            std::cout << std::endl;
            for (int i = 0; i < size; ++i) {
                std::cout << data[i] << "\t";
            }
            std::cout << std::endl;
        }
        else{
            std::cout << "\nObject is empty!\n";
        }
    }
};


template <typename T>
std::ostream & operator << (std::ostream & out, DynamicArray<T> a){//перегрузка оператора << 
    for(int i = 0; i < a.GetSize();++i){
        out << a[i] << " ";
    }
    return out;
}
//==================================================================================================================//
template<typename T>//функции в стеке
T sqr(T value){
    return value * value;
}

template<typename T>
bool is_more_than_10(T value){
    if(value >= 10)
        return true;
    return false;
}

template<typename T>
T sum(T first,T second){
    return first + second;
}

template<typename T>
class ListEl{//один элемент двусвязного списка
public:
    ListEl* pNext;
    ListEl* pPrev;
    T DATA;
    ListEl(T DATA = T(),ListEl* pPrev = nullptr,ListEl* pNext = nullptr){
        this->DATA = DATA;
        this->pPrev = pPrev;
        this->pNext = pNext;
    }
};

template<typename T>
class LinkedList{//класс список 
public:



    ~LinkedList(){//деструктор
        clear();
    }


    LinkedList(){
        Size = 0;
        head = nullptr;
    }

    //считываем значений из массива
    LinkedList(T* items,int count){
        if(items == nullptr){
            Size = 0;
            head = nullptr;
        }
        else{
            Size = 0;
            this->head = nullptr;
            this->tail = nullptr;
            for (int i = 0; i < count; ++i) {
                Append(items[i]);
            }
        }
    }


    LinkedList(const LinkedList<T>& list){//копирующий конструктор
        Size = 0;
        this->head = nullptr;
        ListEl<T>* current = list.head;
        for (int i = 0; i < list.Size; ++i) {
            this->Append(current->DATA);
            current = current->pNext;
        }
    }


    LinkedList<T>* Concat(LinkedList<T>* list){//конкатенация 
        this->tail->pNext = list->head;
        list->head->pPrev = this->tail;
        this->tail = list->tail;
        Size+=list->Size;

        return this;
    }


    T Get(int index){//получение 
        if(index < 0 || index >= Size)
            throw "\nGet Message : Index Out Of Range\n";

        ListEl<T>* current;//бегаем по списку и берем элементы

        if(index < Size/2){
            current = head;
            for (int i = 0; i < index; ++i) {
                current = current->pNext;
            }
        }else{
            current = tail;
            for (int i = 0; i < Size-index-1; ++i) {
                current = current->pPrev;
            }
        }
        return current->DATA;

    }


    T GetFirst() {//получение первого элемента 
        if(Size == 0)
            throw "\nGetFirst Message : Index Out Of Range\n";
        return Get(0);
    }


    T GetLast(){//получение последнего элемента 
        if(Size == 0)
            throw "\nGetLast Message : Index Out Of Range\n";
        return Get(Size - 1);
    }


    LinkedList<T>* GetSubLinkedList(int startIndex,int endIndex){//получение подсписка
        if(startIndex < 0 || endIndex < 0 || startIndex >= Size || endIndex >=Size)
            throw "\nGetSubLinkedList Message : Index Out Of Range\n";
        //std::cout<<"\nGetSubLinkedList\n";
        ListEl<T>* current = this->head;
        for (int i = 0; i < startIndex; ++i) {
            current = current->pNext;
        }
        T* items;
        items = (T*)malloc(sizeof(T*)*(endIndex - startIndex + 1));
        for (int i = 0; i < endIndex - startIndex + 1; ++i) {
            items[i] = current->DATA;
            current = current->pNext;
        }

        LinkedList<T>* result = new LinkedList<T>(items,endIndex - startIndex + 1);
        return result;

    }


    void PrintFromEnd(){//печать с конца списка
        //std::cout << std::endl;
        ListEl<T>* tmp = this->tail;
        if(Size == 1)
            std::cout << tail->DATA << " ";
        else{
            while(tmp != nullptr){
                std::cout << tmp->DATA <<" ";
                tmp = tmp->pPrev;
            }
        }
        std::cout << std::endl;
    }


    void PrintFromBegin(){//печать с начала списка
        if(head != nullptr){
            //std::cout << std::endl;
            ListEl<T>* tmp = this->head;
            if(Size == 1)
                std::cout << head->DATA << " ";
            else{
                while(tmp != nullptr){
                    std::cout << tmp->DATA <<" ";//std::endl;
                    tmp = tmp->pNext;
                }
            }
            std::cout << std::endl;
        }
    }



    void Append(T DATA){//добавление в конец
        if(head == nullptr){
            head = new ListEl<T>(DATA);
            this->tail = head;

        }else{
            ListEl<T>* current = this->head;
            ListEl<T>* tmp;
            while(current->pNext != nullptr){
                tmp = current;
                current = current->pNext;
                current->pPrev = tmp;
            }

            this->tail = new ListEl<T>(DATA,current,current->pNext);
            current->pNext = tail;
        }
        Size++;
    }


    void Prepend(T DATA) {//в начало
        if(head == nullptr){
            head = new ListEl<T>(DATA);
            this->tail = head;
        }
        else{
            ListEl<T>* one_more = new ListEl<T>(DATA,head->pPrev,head);//создание нового узла(следующий - HEAD,предыдущего нет)
            head->pPrev = one_more;
            this->head = one_more;
            ListEl<T>* current = head;
            while(current->pNext != nullptr){
                current = current->pNext;
            }
            this->tail = current;
        }
        Size++;
    }


    void pop_front() {//удаление с начала
        if(Size == 1){
            delete [] tail;
            Size--;
        }
        else{
            ListEl<T>* tmp = head;
            head = head->pNext;
            head->pPrev = nullptr;
            delete [] tmp;
            Size--;
        }

    }


    void pop_back(){//с конца
        ListEl<T>* tmp = tail;
        tail = tail->pPrev;
        tail->pNext = nullptr;
        delete [] tmp;
        Size--;
    }

    
    void InsertAt(T DATA, int index) {//вставляет на заданную позицию элемент 
        if(index < 0 || index >= Size)
            throw "\nInsertAt Message : Index Out Of Range\n";
        ListEl<T>* previous;
        ListEl<T>* new_element;
        ListEl<T>* tmp;
        if(index <= Size/2){//идём с начала
            if(index == 0)
                Prepend(DATA);
            previous = head;
            for (int i = 0; i < index - 1; ++i) {
                previous = previous->pNext;
            }
        }
        else{//идём с конца

            previous = tail;
            for (int i = 0; i < Size - index; ++i) {
                previous = previous->pPrev;
            }
        }
        tmp = previous->pNext;
        new_element = new ListEl<T>(DATA,previous,previous->pNext);
        previous->pNext = new_element;
        tmp->pPrev = new_element;

        Size++;
    }

   
    void removeAt(int index) {//удалить элемент с заданной позиции
        if(index < 0 || index >= Size)
            throw "removeAt Message : Index Out Of Range\n";
        if(index == 0)
            pop_front();
        else{
            if(index == Size - 1)
                pop_back();
            else{
                ListEl<T>* previous;
                ListEl<T>* toDelete;
                if(index <= Size/2){
                    previous = head;
                    for (int i = 0; i < index - 1; ++i) {
                        previous = previous->pNext;
                    }
                }
                else{
                    previous = tail;
                    for (int i = 0; i < Size - index; ++i) {
                        previous = previous->pPrev;
                    }
                }

                toDelete = previous->pNext;
                previous->pNext = toDelete->pNext;
                toDelete->pNext->pPrev = previous;

                delete[] toDelete;
            }
            Size--;
        }
    }
    void ChangeValue(int index,T value){//изменяет по заданному индексу значение на value
        ListEl<T>* curr = head;
        for (int i = 0; i < index; ++i) {
            curr = curr->pNext;
        }
        curr->DATA = value;
    }
    //очистка памяти
    void clear(){
        while(Size){
            pop_front();
        }
    }

    
    T& operator[](const int index) {//перегрузка оператора []
        int counter;
        ListEl<T> *current;
        if (index <= Size / 2) {//идём с начала
            counter = 0;
            current = this->head;
            while (current != nullptr) {
                if (counter == index) {
                    return current->DATA;
                }
                current = current->pNext;
                counter++;
            }
        } else {//идём с конца
            counter = Size - 1;
            current = this->tail;
            while (current != nullptr) {
                if (counter == index) {
                    return current->DATA;
                }
                current = current->pPrev;
                counter--;
            }
        }
    }
private:
    int Size;
    ListEl<T>* head;
    ListEl<T>* tail;
};

//==================================================================================================================//


template<typename T>
class Sequence{//класс последовательности (абстрактный)
public:
    virtual Sequence<T>* GetSubsequence(int startIndex,int endIndex) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;

    virtual T GetFirst() = 0;
    virtual T GetLast() = 0;
    virtual T Get(int index) = 0;
    virtual int GetLength() = 0;

    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item,int index) = 0;

    virtual void Print() = 0;
};
//==================================================================================================================//
template<typename T>
class ArraySequence : public Sequence<T>{
public:
    ArraySequence(){
        DynamicArray<T>* tmp = new DynamicArray<T>();
        DATA = *tmp;
    }

    ArraySequence(T* item,int count){

        DynamicArray<T>* tmp = new DynamicArray<T>(item,count);
        DATA = *tmp;

    }

    ArraySequence(ArraySequence<T>& array){//копирующий конструктор для ArraySequence

        DynamicArray<T>* tmp = new DynamicArray<T>(array.DATA);
        DATA = *tmp;
    }

    ArraySequence(LinkedList<T>& list){//копирующий конструктор для  LinkedList
        T* items;
        items = (T*)malloc(sizeof(T)*(list.GetLength()));
        for (int i = 0; i < list.GetLength(); ++i) {
            items[i] = list.Get(i);
        }

        DynamicArray<T>* tmp = new DynamicArray<T>(items,list.GetLength());
        DATA = *tmp;
    }
    int GetLength(){//получение длины массива
        return DATA.GetSize();
    }
    T Get(int index){
        return DATA.Get(index);
    }
    T GetFirst(){//первый элемент
        return DATA.Get(0);
    }
    T GetLast(){//последний элемент
        return DATA.Get(DATA.GetSize()-1);
    }

    void Append(T item){//добавление в конец
        DATA.Append(item);
    }
    void Prepend(T item){//добавление в начало
        DATA.Prepend(item);
    }
    void InsertAt(T item,int index){//вставка элемента по индексу
        if(index >= DATA.GetSize() || index < 0)
            throw "\nInsertAt Message : Index Out Of Range";
        DATA.Resize(DATA.GetSize()+1);
        for (int i = DATA.GetSize()-2; i >= index ; --i) {
            DATA.Set(i+1,DATA.Get(i));
        }
        DATA.Set(index,item);
    }
    void Print(){
        DATA.Print();
    }

    ArraySequence<T>* GetSubsequence(int startIndex,int endIndex){//получение подпоследовательности
        T* items = (T*)malloc(sizeof(T)*(endIndex-startIndex));
        for (int i = startIndex; i < endIndex; ++i) {
            items[i-startIndex] = DATA.Get(i);
        }
        ArraySequence<T>* result = new ArraySequence<T>(items,endIndex-startIndex);
        return result;
    }

    ArraySequence<T>* Concat(Sequence<T>* list){//конкатенация
        if(list->GetLength() != 0){
            T* items = (T*)malloc(sizeof(T)*(DATA.GetSize()+list->GetLength()));
            for (int i = 0; i < DATA.GetSize(); ++i) {
                items[i] = DATA.Get(i);
            }
            for (int i = 0; i < list->GetLength(); ++i) {
                items[i+DATA.GetSize()] = list->Get(i);
            }
            ArraySequence<T>* result = new ArraySequence<T>(items,DATA.GetSize()+list->GetLength());

            return result;
        }else{
            ArraySequence<T>* result = new ArraySequence<T>(*this);
            return result;
        }

    }
private:
    DynamicArray<T> DATA;
};
//==================================================================================================================//
template<typename T>
class LinkedListSequence : public Sequence<T>{//
public:
    LinkedListSequence(){//конструктор по умолчанию
        LinkedList<T>* tmp = new LinkedList<T>();
        DATA = *tmp;
    }
    LinkedListSequence(T* items,int count){//конструктор по массиву
        LinkedList<T>* tmp = new LinkedList<T>(items,count);
        DATA = *tmp;

    }


    
    LinkedListSequence<T>* Concat(Sequence<T>* list){//конкатенация
        for (int i = 0; i < list->GetLength(); ++i) {
            DATA.Append(list->Get(i));
        }
        T* items;
        items = (T*)malloc(sizeof(T*)*(DATA.GetLength()+list->GetLength()));
        for (int i = 0; i < DATA.GetLength(); ++i) {
            items[i] = DATA.Get(i);
        }

        LinkedListSequence<T>* result = new LinkedListSequence<T>(items,DATA.GetLength());
        return result;
    }

    LinkedListSequence(const LinkedList<T>& list){//копирующий конструктор по объекту
        LinkedList<T>* tmp = new LinkedList<T>(list);
        std::cout<< "Constructor by object . . .\n";
        DATA = *tmp;
    }
    LinkedListSequence<T>* GetSubsequence(int startIndex,int endIndex){//получение подпсписка 
        LinkedList<T>* tmp = DATA.GetSubLinkedList(startIndex,endIndex);
        T* items;
        items = (T*)malloc(sizeof(T*)*(endIndex-startIndex));
        for (int i = 0; i < endIndex-startIndex; ++i) {
            items[i] = tmp->Get(i);
        }

        LinkedListSequence<T>* result = new LinkedListSequence<T>(items,endIndex-startIndex);

        return result;
    }
    int GetLength(){
        return DATA.GetLength();
    }
    T GetFirst(){
        DATA.GetFirst();
    }
    T GetLast(){
        DATA.GetLast();
    }
    T Get(int index){//элемент по индексу
        DATA.Get(index);
    }

    void Append(T item){//добавить в конец
        DATA.Append(item);
    }
    void Prepend(T item){//добавить в начало
        DATA.Prepend(item);
    }
    void InsertAt(T item,int index){//вставить по индексу
        DATA.InsertAt(item,index);
    }
    void removeAt(int index){//удалить по индексу
        DATA.removeAt(index);
    }
    void Print(){
        DATA.PrintFromBegin();
    }
private:
    LinkedList<T> DATA;
};
//==================================================================================================================//
template<typename T>
class TriangularMatrix{
private:
    DynamicArray<DynamicArray<T>> data;//здесь хранятся все значения матрицы
    int m;//размерность матрицы
public:
    TriangularMatrix(){
        m = 0;
    }

    TriangularMatrix(TriangularMatrix<T>* example){//копирующий конструктор
        m = example->GetSize();
        data.Resize(m);

        for (int i = 0; i < m; ++i) {
            data[i].Resize(i+1);
            for (int j = 0; j < i + 1; ++j) {
                data[i].Set(j,example->Get(i,j));
            }
        }
    }

    TriangularMatrix(int size){//конструктор с вводом элементов с консоли

        m = size;
        data.Resize(m);

        for (int i = 0; i < m; ++i) {
            data[i].Resize(i+1);
            std::cout << "Enter " << i + 1 << " values for " << i <<" matrix string\n";
            for (int j = 0; j < i + 1; ++j) {
                T value;
                if(std::cin >> value)
                    data[i].Set(j,value);
                else{
                    std::cout << "Invalid value ! ! !\n";
                    m = 0;
                    return;
                }
            }
        }
    }

    //методы для получения и записи характеристик матрицы
    int GetSize(){
        return m;
    }
    T Get(int i,int j) {
        return data[i].Get(j);
    }
    void Set(int i,int j,T value){
        data[i].Set(j,value);
    }

    TriangularMatrix<T>* Sum(TriangularMatrix<T>* example){//сумма матрицы,переданной в качестве параметра,и данной матрицы
        if(m == example->GetSize()){
            TriangularMatrix<T>* result = new TriangularMatrix<T>(example);
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < i + 1; ++j) {
                    result->Set(i,j,data[i].Get(j) + result->Get(i,j));
                }
            }
            return result;
        }else{
            return nullptr;
        }
    }

    void multiplication_of_a_triangular_matrix_by_a_scalar(T scalar){//умножение данной матрицы на скаляр
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < i + 1; ++j) {
                this->Set(i,j,this->Get(i,j) * scalar);
            }
        }
    }

    T calculating_the_norm_of_a_matrix(){//вычисление линейной нормы данной матрицы
        if(this != nullptr && m != 0){
            T result = this->Get(0,0);//
            for (int i = 0; i < m; ++i) {
                T tmp = 0;
                for (int j = 0; j < i + 1; ++j) {
                    tmp += this->Get(i,j);
                }
                if(tmp >= result)
                    result = tmp;
            }
            return result;
        }else{
            std::cout << "Error of calculations ! ! !\n";
            return -1;
        }

    }

    void Print(){
        if(this != nullptr && m != 0){
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < i + 1; ++j) {
                    std::cout << data[i].Get(j) << " ";
                }
                std::cout << std::endl;
            }
        }else{
            std::cout << "Can't print ! ! !\n";
        }
    }

};
template<typename T>
class Stack{//стэк
private:
    LinkedList<T>* DATA;
    int size;
public:
    Stack(){//конструктор по умолчанию
        DATA = nullptr;
        size = 0;
    }
    Stack(LinkedList<T>* items, int count){
        DATA = items;
        size = count;
    }
    Stack(T* items, int count){//конструктор по массиву элементов
        DATA = new LinkedList<T>(items, count);
        size = count;
    }

    int GetSize(){//получение размера стека
        return size;
    }

    T Get(int index){//получение элемента по индексу
        return DATA->Get(index);
    }

    void Append(T value){//добавление элемента в конец стека
        DATA->Append(value);
    }

    void Print(){
        if(this != nullptr && DATA != nullptr && size != 0)
            DATA->PrintFromEnd();
    }

    //map, where, reduce
    void Map(T(*func)(T)){//возведение в квадрат
        for (int i = 0 ; i < size ; i++) {
            DATA->ChangeValue(i,func(DATA->Get(i)));
            //изменяем значение по данному индексу
        }
    }

    Stack<T>* Where(bool(*func)(T)){//фильтрует элементы по функции переданной в параметр
        int count = 0;
        for (int i = 0; i < size; ++i) {
            if(!func(DATA->Get(i))){
                count++;
            }
        }
        if(count > 0){
            T* items = new T[count];
            int index = 0;
            for (int i = 0; i < size; ++i) {
                if(!func(DATA->Get(i))){
                    items[index] = DATA->Get(i);
                    index++;
                }
            }
            Stack<T>* result = new Stack<T>(items, count);
            return result;
        }else{
            std::cout << "There are no elements which bigger than 10 !\n";
            return nullptr;
        }

    }

    T Reduce(T(*func)(T,T)){//последовательное применение функции к элементам итерируемой коллекции
        T sum = 0;
        for (int i = 0; i < size; ++i) {
            sum = func(sum, DATA->Get(i));
        }
        return sum;
    }

    Stack<T>* Concat(Stack<T>* example){//конкатенация 
        T* items = new T[size + example->GetSize()];//поэлементно копируем в этот массив элементы из обоих стеков
        for (int i = 0; i < size; ++i) {
            items[i] = DATA->Get(i);
        }
        for (int i = 0; i < example->GetSize(); ++i) {
            items[size + i] = example->Get(i);
        }

        Stack<T>* result = new Stack<T>(items, size + example->GetSize());
        return result;
    }

    //извлечение подпоследовательности из стека
    Stack<T>* GetSubsequenceFromStack(int start, int end){
        Stack<T>* result = new Stack<T>(DATA->GetSubLinkedList(start,end),end - start + 1);
        return result;
    }
};
int main(){
    int flag;
    std::cout << "Testing a stack or a triangular matrix ? (1 - stack , 2 - triangular matrix)\n";
    std::cin >> flag;
    if(flag == 1){
        //==============================================================//
        int n;
        std::cout <<"Enter size of stack : \n";
        std::cin >> n;
        std::cout <<"Enter " << n <<" elements of stack : \n";
        int* tmp1 = new int[n];
        for (int i = 0; i < n; ++i) {
            int elem;
            std::cin >> elem;
            tmp1[i] = elem;
        }
        Stack<int>* first = new Stack<int>(tmp1, n);
        first->Print();

        std::cout <<"Enter size of stack : \n";
        std::cin >> n;
        std::cout <<"Enter " << n <<" elements of stack : \n";
        int* tmp2 = new int[n];
        for (int i = 0; i < n; ++i) {
            int elem;
            std::cin >> elem;
            tmp2[i] = elem;
        }
        Stack<int>* second = new Stack<int>(tmp2, n);
        second->Print();

        int begin, end;
        std::cout << "Enter the start and end indices to get a subsequence on the first stack :\n";
        std::cin >> begin >> end;
        try{
            Stack<int>* sub = first->GetSubsequenceFromStack(begin,end);
            sub->Print();
        }catch (const char* msg){
            std::cout << msg << std::endl;
        }
        std::cout << "The result of concatenating the first and second stacks :\n";
        Stack<int>* concat = first->Concat(second);
        concat->Print();
        std::cout << "The first stack after squaring it's elements :\n";
        first->Map(sqr);
        first->Print();

        std::cout << "Concatenation result after removing all elements, greater than 10 :\n";
        Stack<int>* for_where = concat->Where(is_more_than_10);
        for_where->Print();

        std::cout << "Sum of all elements in the first stack : " << first->Reduce(sum) << std::endl;
        //==============================================================//

    } else{
        if(flag == 2){
            int m;
            std::cout << "Enter size of first matrix :\n";
            std::cin >> m;
            TriangularMatrix<int>* test1 = new TriangularMatrix<int>(m);
            test1->Print();
            std::cout << "Enter size of second matrix :\n";
            std::cin >> m;
            TriangularMatrix<int>* test2 = new TriangularMatrix<int>(m);
            test2->Print();

            TriangularMatrix<int>* sum = test1->Sum(test2);
            sum->Print();

            std::cout << "Enter scalar for multiplication on a first matrix :\n";
            int scalar;
            std::cin >> scalar;
            test1->multiplication_of_a_triangular_matrix_by_a_scalar(scalar);
            test1->Print();

            std::cout << "The norm of first matrix : " << test1->calculating_the_norm_of_a_matrix() << std::endl;
        }
    }

    return 0;
}