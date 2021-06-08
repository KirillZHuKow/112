#include <iostream>
#include <math.h>
template <class T>
class DynamicArray{
private:
    T* data;
    int size;
    int capacity;
public:
    DynamicArray(){
        data = NULL;
        size = 0;
        capacity = 0;
    }


    void Delete(){
        delete[] this->data;
    }
    DynamicArray(int size){
        size = size;
        capacity = size;
        data = new T[size];
    }

    DynamicArray(T* items,int count){
        if(items == nullptr){
            data = nullptr;
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
    void Resize(int newSize){
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

    T Get(int index){
        if(index < 0 || index >= capacity)
            throw "\nGet Message : Index Out Of Range\n";
        return data[index];
    }

    void Set(int index,T value){
        if(index < 0 || index > capacity)
            throw "\nSet Message : Index Out Of Range\n";
        data[index] = value;

    }

    int GetSize() const{
        return size;
    }

    void Append(T val){
        Resize(size + 1);
        data[size - 1] = val;
    }

    void Prepend(T val){
        Resize(size + 1);
        for (int i = size - 2; i >= 0; --i)
        {
            data[i + 1] = data[i];
        }
        data[0] = val;
    }

    T & operator [] (int i){
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
std::ostream & operator << (std::ostream & out, DynamicArray<T> a){
    for(int i = 0; i < a.GetSize();++i){
        out << a[i] << " ";
    }
    return out;
}
//==================================================================================================================//
template<typename T>
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
class Node{
public:
    Node* pNext;
    Node* pPrev;
    T data;
    Node(T data = T(),Node* pPrev = nullptr,Node* pNext = nullptr){
        this->data = data;
        this->pPrev = pPrev;
        this->pNext = pNext;
    }
};

template<typename T>
class LinkedList{
public:



    ~LinkedList(){
        clear();
    }


    LinkedList(){
        size = 0;
        head = nullptr;
    }

    LinkedList(T* items,int count){
        if(items == nullptr){
            size = 0;
            head = nullptr;
        }
        else{
            size = 0;
            this->head = nullptr;
            this->tail = nullptr;
            for (int i = 0; i < count; ++i) {
                Append(items[i]);
            }
        }
    }


    LinkedList(const LinkedList<T>& list){
        size = 0;
        this->head = nullptr;
        Node<T>* current = list.head;
        for (int i = 0; i < list.size; ++i) {
            this->Append(current->data);
            current = current->pNext;
        }
    }


    LinkedList<T>* Concat(LinkedList<T>* list){
        this->tail->pNext = list->head;
        list->head->pPrev = this->tail;
        this->tail = list->tail;
        size+=list->size;

        return this;
    }


    T Get(int index){
        if(index < 0 || index >= size)
            throw "\nGet Message : Index Out Of Range\n";

        Node<T>* current;

        if(index < size/2){
            current = head;
            for (int i = 0; i < index; ++i) {
                current = current->pNext;
            }
        }else{
            current = tail;
            for (int i = 0; i < size-index-1; ++i) {
                current = current->pPrev;
            }
        }
        return current->data;

    }


    T GetFirst() {
        if(size == 0)
            throw "\nGetFirst Message : Index Out Of Range\n";
        return Get(0);
    }


    T GetLast(){
        if(size == 0)
            throw "\nGetLast Message : Index Out Of Range\n";
        return Get(size - 1);
    }


    LinkedList<T>* GetSubLinkedList(int startIndex,int endIndex){
        if(startIndex < 0 || endIndex < 0 || startIndex >= size || endIndex >=size)
            throw "\nGetSubLinkedList Message : Index Out Of Range\n";
        Node<T>* current = this->head;
        for (int i = 0; i < startIndex; ++i) {
            current = current->pNext;
        }
        T* items;
        items = (T*)malloc(sizeof(T*)*(endIndex - startIndex + 1));
        for (int i = 0; i < endIndex - startIndex + 1; ++i) {
            items[i] = current->data;
            current = current->pNext;
        }

        LinkedList<T>* result = new LinkedList<T>(items,endIndex - startIndex + 1);
        return result;

    }


    void PrintFromEnd(){//печать с конца списка
        Node<T>* tmp = this->tail;
        if(size == 1)
            std::cout << tail->data << " ";
        else{
            while(tmp != nullptr){
                std::cout << tmp->data <<" ";
                tmp = tmp->pPrev;
            }
        }
        std::cout << std::endl;
    }


    void PrintFromBegin(){//печать с начала списка
        if(head != nullptr){
            Node<T>* tmp = this->head;
            if(size == 1)
                std::cout << head->data << " ";
            else{
                while(tmp != nullptr){
                    std::cout << tmp->data <<" ";
                    tmp = tmp->pNext;
                }
            }
            std::cout << std::endl;
        }
    }



    void Append(T data){
        if(head == nullptr){
            head = new Node<T>(data);
            this->tail = head;

        }else{
            Node<T>* current = this->head;
            Node<T>* tmp;
            while(current->pNext != nullptr){
                tmp = current;
                current = current->pNext;
                current->pPrev = tmp;
            }

            this->tail = new Node<T>(data,current,current->pNext);
            current->pNext = tail;
        }
        size++;
    }


    void Prepend(T data) {
        if(head == nullptr){
            head = new Node<T>(data);
            this->tail = head;
        }
        else{
            Node<T>* one_more = new Node<T>(data,head->pPrev,head);
            head->pPrev = one_more;
            this->head = one_more;
            Node<T>* current = head;
            while(current->pNext != nullptr){
                current = current->pNext;
            }
            this->tail = current;
        }
        size++;
    }


    void pop_front() {
        if(size == 1){
            delete [] tail;
            size--;
        }
        else{
            Node<T>* tmp = head;
            head = head->pNext;
            head->pPrev = nullptr;
            delete [] tmp;
            size--;
        }

    }


    void pop_back(){
        Node<T>* tmp = tail;
        tail = tail->pPrev;
        tail->pNext = nullptr;
        delete [] tmp;
        size--;
    }

    void InsertAt(T data, int index) {
        if(index < 0 || index >= size)
            throw "\nInsertAt Message : Index Out Of Range\n";
        Node<T>* previous;
        Node<T>* new_elem;
        Node<T>* tmp;
        if(index <= size/2){
            if(index == 0)
                Prepend(data);
            previous = head;
            for (int i = 0; i < index - 1; ++i) {
                previous = previous->pNext;
            }
        }
        else{

            previous = tail;
            for (int i = 0; i < size - index; ++i) {
                previous = previous->pPrev;
            }
        }
        tmp = previous->pNext;
        new_elem = new Node<T>(data,previous,previous->pNext);
        previous->pNext = new_elem;
        tmp->pPrev = new_elem;

        size++;
    }
    int GetLength(){return size;}
    void removeAt(int index) {
        if(index < 0 || index >= size)
            throw "removeAt Message : Index Out Of Range\n";
        if(index == 0)
            pop_front();
        else{
            if(index == size - 1)
                pop_back();
            else{
                Node<T>* previous;
                Node<T>* toDelete;
                if(index <= size/2){
                    previous = head;
                    for (int i = 0; i < index - 1; ++i) {
                        previous = previous->pNext;
                    }
                }
                else{
                    previous = tail;
                    for (int i = 0; i < size - index; ++i) {
                        previous = previous->pPrev;
                    }
                }

                toDelete = previous->pNext;
                previous->pNext = toDelete->pNext;
                toDelete->pNext->pPrev = previous;

                delete[] toDelete;
            }
            size--;
        }
    }
    void ChangeValue(int index,T value){
        Node<T>* curr = head;
        for (int i = 0; i < index; ++i) {
            curr = curr->pNext;
        }
        curr->data = value;
    }
    void clear(){
        while(size){
            pop_front();
        }
    }

    T& operator[](const int index) {
        int counter;
        Node<T> *current;
        if (index <= size / 2) {
            counter = 0;
            current = this->head;
            while (current != nullptr) {
                if (counter == index) {
                    return current->data;
                }
                current = current->pNext;
                counter++;
            }
        } else {
            counter = size - 1;
            current = this->tail;
            while (current != nullptr) {
                if (counter == index) {
                    return current->data;
                }
                current = current->pPrev;
                counter--;
            }
        }
    }
private:
    int size;
    Node<T>* head;
    Node<T>* tail;
};

//==================================================================================================================//


template<typename T>
class Sequence{
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
        data = *tmp;
    }

    ArraySequence(T* item,int count){

        DynamicArray<T>* tmp = new DynamicArray<T>(item,count);
        data = *tmp;

    }

    ArraySequence(ArraySequence<T>& array){

        DynamicArray<T>* tmp = new DynamicArray<T>(array.data);
        data = *tmp;
    }

    ArraySequence(LinkedList<T>& list){
        T* items;
        items = (T*)malloc(sizeof(T)*(list.GetLength()));
        for (int i = 0; i < list.GetLength(); ++i) {
            items[i] = list.Get(i);
        }

        DynamicArray<T>* tmp = new DynamicArray<T>(items,list.GetLength());
        data = *tmp;
    }
    int GetLength(){
        return data.GetSize();
    }
    T Get(int index){
        return data.Get(index);
    }
    T GetFirst(){
        return data.Get(0);
    }
    T GetLast(){
        return data.Get(data.GetSize()-1);
    }

    void Append(T item){
        data.Append(item);
    }
    void Prepend(T item){
        data.Prepend(item);
    }
    void InsertAt(T item,int index){
        if(index >= data.GetSize() || index < 0)
            throw "\nInsertAt Message : Index Out Of Range";
        data.Resize(data.GetSize()+1);
        for (int i = data.GetSize()-2; i >= index ; --i) {
            data.Set(i+1,data.Get(i));
        }
        data.Set(index,item);
    }
    void Print(){
        data.Print();
    }

    ArraySequence<T>* GetSubsequence(int startIndex,int endIndex){
        T* items = (T*)malloc(sizeof(T)*(endIndex-startIndex));
        for (int i = startIndex; i < endIndex; ++i) {
            items[i-startIndex] = data.Get(i);
        }
        ArraySequence<T>* result = new ArraySequence<T>(items,endIndex-startIndex);
        return result;
    }

    ArraySequence<T>* Concat(Sequence<T>* list){
        if(list->GetLength() != 0){
            T* items = (T*)malloc(sizeof(T)*(data.GetSize()+list->GetLength()));
            for (int i = 0; i < data.GetSize(); ++i) {
                items[i] = data.Get(i);
            }
            for (int i = 0; i < list->GetLength(); ++i) {
                items[i+data.GetSize()] = list->Get(i);
            }
            ArraySequence<T>* result = new ArraySequence<T>(items,data.GetSize()+list->GetLength());

            return result;
        }else{
            ArraySequence<T>* result = new ArraySequence<T>(*this);
            return result;
        }

    }
private:
    DynamicArray<T> data;
};
//==================================================================================================================//
template<typename T>
class LinkedListSequence : public Sequence<T>{
public:
    LinkedListSequence(){
        LinkedList<T>* tmp = new LinkedList<T>();
        data = *tmp;
    }
    LinkedListSequence(T* items,int count){
        LinkedList<T>* tmp = new LinkedList<T>(items,count);
        data = *tmp;

    }

    LinkedListSequence<T>* Concat(Sequence<T>* list){
        for (int i = 0; i < list->GetLength(); ++i) {
            data.Append(list->Get(i));
        }
        T* items;
        items = (T*)malloc(sizeof(T*)*(data.GetLength()+list->GetLength()));
        for (int i = 0; i < data.GetLength(); ++i) {
            items[i] = data.Get(i);
        }

        LinkedListSequence<T>* result = new LinkedListSequence<T>(items,data.GetLength());
        return result;
    }

    LinkedListSequence(const LinkedList<T>& list){
        LinkedList<T>* tmp = new LinkedList<T>(list);
        std::cout<< "Constructor by object . . .\n";
        data = *tmp;
    }
    LinkedListSequence<T>* GetSubsequence(int startIndex,int endIndex){
        LinkedList<T>* tmp = data.GetSubLinkedList(startIndex,endIndex);
        T* items;
        items = (T*)malloc(sizeof(T*)*(endIndex-startIndex));
        for (int i = 0; i < endIndex-startIndex; ++i) {
            items[i] = tmp->Get(i);
        }

        LinkedListSequence<T>* result = new LinkedListSequence<T>(items,endIndex-startIndex);

        return result;
    }
    int GetLength(){
        return data.GetLength();
    }
    T GetFirst(){
        data.GetFirst();
    }
    T GetLast(){
        data.GetLast();
    }
    T Get(int index){
        data.Get(index);
    }

    void Append(T item){
        data.Append(item);
    }
    void Prepend(T item){
        data.Prepend(item);
    }
    void InsertAt(T item,int index){
        data.InsertAt(item,index);
    }
    void removeAt(int index){
        data.removeAt(index);
    }
    void Print(){
        data.PrintFromBegin();
    }
private:
    LinkedList<T> data;
};
//==================================================================================================================//
template<typename T>
class TriangularMatrix{
private:
    DynamicArray<DynamicArray<T>> data;
    int m;//размерность матрицы
public:
    TriangularMatrix(){
        m = 0;
    }

    TriangularMatrix(TriangularMatrix<T>* example){
        m = example->GetSize();
        data.Resize(m);

        for (int i = 0; i < m; ++i) {
            data[i].Resize(i+1);
            for (int j = 0; j < i + 1; ++j) {
                data[i].Set(j,example->Get(i,j));
            }
        }
    }

    TriangularMatrix(int size){

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

    int GetSize(){
        return m;
    }
    T Get(int i,int j) {
        return data[i].Get(j);
    }
    void Set(int i,int j,T value){
        data[i].Set(j,value);
    }

    TriangularMatrix<T>* Sum(TriangularMatrix<T>* example){
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

    void multiplication_of_a_triangular_matrix_by_a_scalar(T scalar){
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < i + 1; ++j) {
                this->Set(i,j,this->Get(i,j) * scalar);
            }
        }
    }

    T calculating_the_norm_of_a_matrix(){
        if(this != nullptr && m != 0){
            T result = this->Get(0,0);
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
//==================================================================================================================//
template<typename T>
class DiagonalMatrix{
private:
    DynamicArray<T> data;
    int m;
public:
    DiagonalMatrix() {
     
        m = 0;
    
    }
    DiagonalMatrix(T* items,int count){
        m = count;
        data.Resize(count);
        for (int i = 0; i < m; ++i) {
            data.Set(i,items[i]);
        }
    }
    DiagonalMatrix(DiagonalMatrix<T>* example){
        m = example->GetSize();
        data.Resize(m);
        for (int i = 0; i < m; ++i) {
            data.Set(i,example->Get(i));
        }
    }

    int GetSize(){
        return m;
    }
    T Get(int i){
        return data.Get(i);
    }
    void Set(int i,T value){
        data.Set(i,value);
    }

    DiagonalMatrix<T>* Sum(DiagonalMatrix<T>* example){
        if(m == example->GetSize()){
            DiagonalMatrix<T>* result = new DiagonalMatrix<T>(this);
            for (int i = 0; i < m; ++i) {
                result->Set(i,result->Get(i) + example->Get(i));
            }
            return result;
        }else{
            std::cout << "Can't be summed! ! !\n";
            return nullptr;
        }
    }
    void multiplying_a_diagonal_matrix_by_a_scalar(T scalar){
        if(this != nullptr){
            for (int i = 0; i < m; ++i) {
                data.Set(i,data.Get(i) * scalar);
            }
        }
    }
    T calculating_the_norm_of_a_matrix(){//вычисление нормы данной матрицы
        if(this != nullptr && m != 0){
            T result = data.Get(0);//в качестве начального результата берем первый элемент на главной диагонали
            for (int i = 0; i < m; ++i) {
                if(data.Get(i) >= result)
                    result = data.Get(i);
            }
            return result;
        }else{
            std::cout << "Calculation error ! ! !\n";
            return -1;//возвращаем -1 так как нужно вернуть какое то число
        }
    }

    void Print(){
        if(this != nullptr){
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < m; ++j) {
                    if(i == j)
                        std::cout << data.Get(i) << "\t";
                    else
                        std::cout << "0" << "\t";
                }
                std::cout << std::endl;
            }
        }else{
            std::cout << "Can't be printed ! ! !\n";
        }

    }

};

template<typename T>
class Stack{
private:
    LinkedList<T>* data;
    int size;
public:
    Stack(){//конструктор по умолчанию
        data = nullptr;
        size = 0;
    }
    Stack(LinkedList<T>* items, int count){
        data = items;
        size = count;
    }
    Stack(T* items, int count){//конструктор по массиву элементов
        data = new LinkedList<T>(items, count);
        size = count;
    }

    int GetSize(){//получение размера стека
        return size;
    }

    T Get(int index){//получение элемента по индексу
        return data->Get(index);
    }

    void Append(T value){//добавление элемента в конец стека
        data->Append(value);
    }

    void Print(){
        if(this != nullptr && data != nullptr && size != 0)
            data->PrintFromEnd();//у стека нет возможности идти с начала(тк все операции происходят на последних элементах)
    }

    //map, where, reduce
    void Map(T(*func)(T)){//возведение в квадрат
        for (int i = 0 ; i < size ; i++) {
            data->ChangeValue(i,func(data->Get(i)));
            //изменяем значение по данному индексу
        }
    }

    Stack<T>* Where(bool(*func)(T)){
        int count = 0;
        for (int i = 0; i < size; ++i) {
            if(!func(data->Get(i))){
                count++;
            }
        }
        if(count > 0){
            T* items = new T[count];
            int index = 0;
            for (int i = 0; i < size; ++i) {
                if(!func(data->Get(i))){
                    items[index] = data->Get(i);
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

    T Reduce(T(*func)(T,T)){
        T sum = 0;
        for (int i = 0; i < size; ++i) {
            sum = func(sum, data->Get(i));
        }
        return sum;
    }

    Stack<T>* Concat(Stack<T>* example){
        T* items = new T[size + example->GetSize()];
        for (int i = 0; i < size; ++i) {
            items[i] = data->Get(i);
        }
        for (int i = 0; i < example->GetSize(); ++i) {
            items[size + i] = example->Get(i);
        }

        Stack<T>* result = new Stack<T>(items, size + example->GetSize());
        return result;
    }

    Stack<T>* GetSubsequenceFromStack(int start, int end){
        Stack<T>* result = new Stack<T>(data->GetSubLinkedList(start,end),end - start + 1);
        return result;
    }
};
//===============================================================================================================================
//Тестирование
template<typename T>
void ArraySequenceTesting(T* items,int count,int index,T data,int start,int end){
    std::cout << "\t\t Start ArraySequence tests ";
    ArraySequence<T> first(items,count);
    first.Print();
    std::cout << "\nDemonstration of CopyConstructor , copied from first :";
    ArraySequence<T> copy(first);
    copy.Print();

    try{
        std::cout << "\n" << first.Get(index);
    }catch(const char* msg){
        std::cout << msg;
    }
    try{
        std::cout << first.GetFirst();
    }catch(const char* msg){
        std::cout << msg;
    }
    try{
        std::cout << first.GetLast() << "\n";
    }catch(const char* msg){
        std::cout << msg;
    }

    first.Append(data);
    first.Print();

    first.Prepend(data);
    first.Print();

    try{
        first.InsertAt(index,data);
        first.Print();
    }catch(const char* msg){
        std::cout << msg;
    }
    std::cout << "\n\nConcatenation of empty and non-empty objects";
    ArraySequence<T>* e = new ArraySequence<T>();
    ArraySequence<T>* q = new ArraySequence<T>();
    ArraySequence<T>* a = e->Concat(&first);
    std::cout << "\nResult of concatenation of empty and non-empty objects:";
    a->Print();
    std::cout << "\n\nConcatenation of non-empty and non-empty objects";
    ArraySequence<T>* c = first.Concat(&first);
    std::cout << "\nСoncatenation result of non-empty and non-empty objects:";
    c->Print();

    try {
        std::cout << "\n\nGetSubsequence start = " << start << " end = " << end << "\n";
        ArraySequence<T>* sub = first.GetSubsequence(start,end);
        sub->Print();
    }catch(const char* msg){
        std::cout << msg;
    }
    std::cout << "\t\tFinish ArraySequence tests";
}

template<typename T>
void LinkedListSequenceTesting(T* items,int count,int index,T data,int start,int end){
    std::cout << "\t\tStart LinkedListSequence tests";
    LinkedListSequence<T> first(items,count);
    first.Print();
    //сначала попытки узнать первый,последний и элемент по индексу
    try{
        std::cout << "\nGet index = " << index << "\n" <<first.Get(index);
    }catch(const char* msg) {
        std::cout << msg;
    }

    try{
        std::cout << first.GetFirst();
    }catch(const char* msg) {
        std::cout << msg;
    }

    try{
        std::cout << first.GetLast();
    }catch(const char* msg) {
        std::cout << msg;
    }
    std::cout<<"\n\nAppend data = " << data << "\n";
    std::cout<<"\nPrepend data = " << data << "\n";
    first.Append(data);
    first.Prepend(data);
    first.Print();

    try{
        first.InsertAt(data,index);
        first.Print();
    }catch (const char* msg){
        std::cout << msg;
    }


    try{
        std::cout << "\n\nGetSubsequence start = " << start << " end = " << end << "\n";
        LinkedListSequence<T>* second = first.GetSubsequence(start,end);
        second->Print();
        std::cout << "\n\nConcat :";
        first.Print();
        std::cout << "\nand";
        second->Print();
        std::cout << "\n";
        std::cout << "Result of Concatination:";
        LinkedListSequence<T>* third = first.Concat(second);
        third->Print();
    }catch(const char* msg){
        std::cout << msg;
    }
    std::cout << "\n\nDemonstration of Copy constructor , copied from first :";
    first.Print();
    std::cout << "\nCopy of first:";
    LinkedListSequence<T> copy(first);
    copy.Print();
    std::cout << std::endl;
    try{
        copy.removeAt(index);
    }
    catch(const char* msg){
        std::cout << msg;
    }
    copy.Print();
    std::cout << "\t\tFinish LinkedListSequence tests";
}
//===============================================================================================================================
int main(){
    int flag;
    std::cout << "Testing a stack or a triangular matrix or a diagonal matrix ? (1 - stack , 2 - triangular matrix, 3 - diagonal matrix)\n";
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
        first->Print();//элементы печатаются с конца, так как все операции стека должны происходить и начинаться на последнем элементе

        std::cout <<"Enter size of stack : \n";
        std::cin >> n;
        std::cout <<"Enter " << n <<" elements of vector : \n";
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
        try{//демонстрация работы метода получения подпоследовательности из стека,в случае некорректных индексов выбрасывается исключение
            Stack<int>* sub = first->GetSubsequenceFromStack(begin,end);
            sub->Print();
        }catch (const char* msg){
            std::cout << msg << std::endl;
        }
        std::cout << "The result of concatenating the first and second stacks :\n";
        Stack<int>* concat = first->Concat(second);//демонстрация работы функции конкатенации
        concat->Print();
        std::cout << "The first stack after squaring it's elements :\n";
        first->Map(sqr);//возведение всех элементов в квадрат
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

            std::cout << "The norm of first matrix : " << test1->calculating_the_norm_of_a_matrix() << std::endl;//вычисление нормы для матрицы test1
        }
        else{
            if(flag == 3){
                int m;
                std::cout << "Enter size of matrix :\n";
                std::cin >> m;
                int* items = new int[m];
                int tmp;
                std::cout << "Enter " << m << " elements for diagonal:\n";
                for (int i = 0; i < m; ++i) {
                    std::cin >> tmp;
                    items[i] = tmp;
                }
                DiagonalMatrix<int>* test1 = new DiagonalMatrix<int>(items,m);
                test1->Print();

                std::cout << "Enter size of matrix :\n";
                std::cin >> m;
                items = new int[m];
                std::cout << "Enter " << m << " elements for diagonal:\n";
                for (int i = 0; i < m; ++i) {
                    std::cin >> tmp;
                    items[i] = tmp;
                }
                DiagonalMatrix<int>* test2 = new DiagonalMatrix<int>(items,m);
                test2->Print();

                DiagonalMatrix<int>* sum = test1->Sum(test2);
                std::cout << "Sum of first and second matrix :\n";
                sum->Print();

                int scalar;
                std::cout << "Enter scalar for multiplication on a first matrix :\n";
                std::cin >> scalar;
                std::cout << "Multiplication of the first matrix by a scalar = " << scalar << ":\n";
                test1->multiplying_a_diagonal_matrix_by_a_scalar(scalar);
                test1->Print();

                std::cout << "The norm of the first matrix : " << test1->calculating_the_norm_of_a_matrix() << std::endl;
            }
        }
        
	}
	std::cout << "Start testing for classes Y/N(1/2)?\n";
    std::cin >> flag;
    if(flag == 1){
        int* t;
        t = (int*)malloc(sizeof(int)*4);
        for (int i = 0; i < 4; ++i) {
            t[i] = 10 + i;
        }

        ArraySequenceTesting(t,4,10,100,2,3);
        ArraySequenceTesting((int*)nullptr,2,4,100,-100,100);

        LinkedListSequenceTesting(t,4,10,100,2,3);
        LinkedListSequenceTesting((int*)nullptr,2,4,100,-100,100);
    }

    return 0;
}