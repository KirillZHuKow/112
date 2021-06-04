#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

template<typename T>
class tree_elem{//класс элемент дерева
public:
    T data;
    tree_elem* left;
    tree_elem* right;

    tree_elem(T key){//конструктор для создания нового узла
        data = key;
        left = NULL;
        right = NULL;
    }
    tree_elem(T key,tree_elem<T>* left,tree_elem<T>* right){//конструктор для копирования конкретного узла
        data = key;
        left = left;
        right = right;
    }
};

template<typename T>
void sqr(tree_elem<T>* curr){//(для Map)
    curr->data = curr->data * curr->data;
}

template<typename T>
bool is_more_than_10(tree_elem<T>* curr){//для удаления всех элементов больших 10 (для Where)
    if(curr->data >= 10)
        return true;
    return false;
}

template<typename T>
T sum(tree_elem<T>* curr,T curr_sum){//(для Reduce)
    return curr_sum + curr->data;
}

template<typename T>
class BinaryTree{
private:

    tree_elem<T>* m_root;

    int size;

    void Maprecurs(void(*func)(tree_elem<T>*),tree_elem<T>* curr){//для рекурсивного выполнения Map
        if(curr){
            Maprecurs(func ,curr->left);
            func(curr);
            Maprecurs(func,curr->right);
        }
    }

    void Whererecurs(bool(*func)(tree_elem<T>*),tree_elem<T>* curr){//для рекурсивного выполнения Where
        if(curr){
            Whererecurs(func,curr->left);

            if(func(curr)){
                delete_elem(curr->data);
            }

            Whererecurs(func,curr->right);
        }
    }

    void upgrade_sub_tree(BinaryTree<T>* result,tree_elem<T>* curr){//для рекурсивного заполнения нового экземпляра
        if(curr){
            upgrade_sub_tree(result,curr->left);
            result->insert(curr->data);
            upgrade_sub_tree(result,curr->right);
        }
    }

    void tree_to_stringrecurs(tree_elem<T>* curr,std::vector<std::string>& curr_str){//представляет деерево в виде строки
        if(curr){
            tree_to_stringrecurs(curr->left,curr_str);
            curr_str.push_back(std::to_string(curr->data));
            tree_to_stringrecurs(curr->right,curr_str);
        }
    }

    void print_tree(tree_elem<T>* curr){//вывод дерева
        if(curr){
            print_tree(curr->left);
            std::cout << curr->data << " ";
            print_tree(curr->right);
        }
    }
public:

    BinaryTree(){//конструктор по умолчанию
        m_root = nullptr;
        size = 0;
    }

    //конструктор с добавлением корня
    BinaryTree(int key){
        m_root = new tree_elem<T>(key);
        size = 1;
    }
    ~BinaryTree(){//деструктор
        delete_tree(m_root);
    }
    int get_size(){return size;}//получить колво элементов дерева

    //получение поддерева по узлу
    BinaryTree<T>* get_sub_tree(T key){

        tree_elem<T>* curr = m_root;
        while(curr && curr->data!=key)
            if(curr->data < key)
                curr = curr->right;
            else
                curr = curr->left;
        BinaryTree<T>* result = new BinaryTree<T>(curr->data);
        upgrade_sub_tree(result,curr);

        return result;
    }

    //печать дерева
    void print(){
        print_tree(m_root);
        std::cout << std::endl;
    }

    //удаление дерева
    void delete_tree(tree_elem<T>* curr){
        if(curr){
            delete_tree(curr->left);
            delete[] curr;
            delete_tree(curr->right);
        }
    }

    //поиск элемента в дереве
    bool find(int key){//поиск значения

        tree_elem<T>* curr = m_root;
        while(curr && curr->data != key){
            if(curr->data > key)
                curr = curr->left;
            else
                curr = curr->right;
        }
        return (bool)curr;
    }

    //добавление элемента
    void insert(int key){//добавление нового элемента в дерево
        if(m_root == nullptr){
            m_root = new tree_elem<T>(key);
            size = 1;
        }else{
            tree_elem<T>* curr = m_root;
            while(curr && curr->data != key){
                if(curr->data > key){
                    if(curr->left)
                        curr = curr->left;
                    else{
                        curr->left = new tree_elem<T>(key);
                        size++;
                        return;
                    }
                }
                else{
                    if(curr->right)
                        curr = curr->right;
                    else{
                        curr->right = new tree_elem<T>(key);
                        size++;
                        return;
                    }
                }
            }
        }
    }

    //удаление элемента
    void delete_elem(T key){
        tree_elem<T>* curr = m_root;
        tree_elem<T>* prev = nullptr;
        while(curr && curr->data != key){
            prev = curr;
            if(curr->data > key){
                curr = curr->left;
            }
            else
                curr = curr->right;
        }
        if(!curr)
            return;

        if(prev != nullptr){
            if(prev->right == curr){
                if(curr->right == nullptr && curr->left == nullptr){
                    prev->right = nullptr;
                    delete[] curr;
                    size--;
                    return;
                }
                if(curr->left == nullptr){
                    prev->right = curr->right;
                    delete[] curr;
                    size--;
                    return;
                }
                if(curr->right == nullptr){
                    prev->right = curr->left;
                    delete[] curr;
                    size--;
                    return;
                }
            }

            if(prev->left == curr){
                if(curr->right == nullptr && curr->left == nullptr){
                    prev->left = nullptr;
                    delete[] curr;
                    size--;
                    return;
                }
                if(curr->left == nullptr){
                    prev->left = curr->right;
                    delete[] curr;
                    size--;
                    return;
                }
                if(curr->right == nullptr){
                    prev->left = curr->left;
                    delete[] curr;
                    size--;
                    return;
                }
            }

            tree_elem<T>* tmp = curr->right;
            while(tmp->left)
                tmp = tmp->left;

            T minimum = tmp->data;



            if(prev->left == curr){
                delete_elem(tmp->data);
                prev->left = new tree_elem<T>(minimum,curr->left,curr->right);
                delete[] curr;
                size--;
                return;
            }
            if(prev->right == curr){
                delete_elem(tmp->data);
                prev->right = new tree_elem<T>(minimum,curr->left,curr->right);
                delete[] curr;
                size--;
                return;
            }
        }

    }



    //map,where,reduce
    void Map(void(*func)(tree_elem<T>*)){
        tree_elem<T>* curr = m_root;
        Maprecurs(func,curr);
    }

    void Where(bool(*func)(tree_elem<T>*)){
        tree_elem<T>* curr = m_root;
        Whererecurs(func,curr);
    }



    //представление дерева в виде строки
    std::string tree_to_string(){

        tree_elem<T>* curr = m_root;
        std::vector<std::string> result;
        tree_to_stringrecurs(curr,result);

        std::string result_str = "";
        for (int i = 0; i < result.size(); ++i) {
            result_str += result[i] + " ";
        }
        return result_str;
    }


};


int main(){

    int n;
    std::cout << "Enter count of values in your first tree :\n";

    if(!(std::cin >> n)){
        std::cout << "Invalid input\n";
        return -1;
    }

    int* values = new int [n];
    int value;
    std::cout << "Enter "<< n <<" elements for your first tree :\n";

    for (int i = 0; i < n; ++i)
    {	if(std::cin >> value)
            values[i] = value;
        else{
            delete[] values;
            std::cout << "Invalid input\n";
            return -1;
        }
    }
    BinaryTree<int> first;
    for (int i = 0; i < n; ++i)
    {
        first.insert(values[i]);
    }

    std::cout << "First tree :\n";
    first.print();
    //===========================================================//
    std::cout << "Enter count of values in your second tree :\n";

    if(!(std::cin >> n)){
        delete[] values;
        std::cout << "Invalid input\n";
        return -1;
    }

    int* another_values = new int [n];
    std::cout << "Enter "<< n <<" elements for your second tree :\n";
    for (int i = 0; i < n; ++i)
    {	if(std::cin >> value)
            another_values[i] = value;
        else{
            delete[] values;
            delete[] another_values;
            std::cout << "Invalid input\n";
            return -1;
        }
    }
    BinaryTree<int> second;
    for (int i = 0; i < n; ++i)
    {
        second.insert(another_values[i]);
    }
    std::cout << "Second tree :\n";
    second.print();

    first.Map(sqr);
    std::cout << "First tree after squaring each element :\n";
    first.print();

    second.Where(is_more_than_10);
    std::cout << "All items less than 10 that belong to the second tree :\n";
    second.print();




    delete[] values;
    delete[] another_values;

    int flag;
    std::cout << "Start stress test Y/N ? (1/2) \n";
    std::cin >> flag;
    if(flag == 1){
        std::cout << "For the range 10,000 - 100,000, press 1\n"
                     "For the range 10,000,000 - 100,000,000 press 2\n";
        std::cin >> flag;
        if(flag == 1){

            int size;

            size = 10000;
            unsigned int start_time =  clock(); // начальное время
            BinaryTree<int> first1;
            for (int i = 0; i < size; ++i)
            {
                first1.insert(rand()%10);
            }
            first1.Map(sqr);
            unsigned int end_time = clock(); // конечное время
            unsigned int search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

            size = 20000;
            start_time =  clock(); // начальное время
            BinaryTree<int> first2;
            for (int i = 0; i < size; ++i)
            {
                first2.insert(rand()%10);
            }
            first2.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

            size = 30000;
            start_time =  clock(); // начальное время
            BinaryTree<int> first3;
            for (int i = 0; i < size; ++i)
            {
                first3.insert(rand()%10);
            }
            first3.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

            size = 40000;
            start_time =  clock(); // начальное время
            BinaryTree<int> first4;
            for (int i = 0; i < size; ++i)
            {
                first4.insert(rand()%10);
            }
            first4.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time<< " mls" << std::endl;

            size = 50000;
            start_time =  clock(); // начальное время
            BinaryTree<int> first5;
            for (int i = 0; i < size; ++i)
            {
                first5.insert(rand()%10);
            }
            first5.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

            size = 60000;
            start_time =  clock(); // начальное время
            BinaryTree<int> first6;
            for (int i = 0; i < size; ++i)
            {
                first6.insert(rand()%10);
            }
            first6.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

            size = 70000;
            start_time =  clock(); // начальное время
            BinaryTree<int> first7;
            for (int i = 0; i < size; ++i)
            {
                first7.insert(rand()%10);
            }
            first7.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

            size = 80000;
            start_time =  clock(); // начальное время
            BinaryTree<int> first8;
            for (int i = 0; i < size; ++i)
            {
                first8.insert(rand()%10);
            }
            first8.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

            size = 90000;
            start_time =  clock(); // начальное время
            BinaryTree<int> first9;
            for (int i = 0; i < size; ++i)
            {
                first9.insert(rand()%10);
            }
            first9.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

            size = 100000;
            start_time =  clock(); // начальное время
            BinaryTree<int> first10;
            for (int i = 0; i < size; ++i)
            {
                first10.insert(rand()%10);
            }
            first10.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;


        }
        else{
            if(flag == 2){

                int size;

                size = 10000000;
                unsigned int start_time =  clock(); // начальное время
                BinaryTree<int> first1;
                for (int i = 0; i < size; ++i)
                {
                    first1.insert(rand()%10);
                }
                first1.Map(sqr);
                unsigned int end_time = clock(); // конечное время
                unsigned int search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

                size = 20000000;
                start_time =  clock(); // начальное время
                BinaryTree<int> first2;
                for (int i = 0; i < size; ++i)
                {
                    first2.insert(rand()%10);
                }
                first2.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

                size = 30000000;
                start_time =  clock(); // начальное время
                BinaryTree<int> first3;
                for (int i = 0; i < size; ++i)
                {
                    first3.insert(rand()%10);
                }
                first3.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

                size = 40000000;
                start_time =  clock(); // начальное время
                BinaryTree<int> first4;
                for (int i = 0; i < size; ++i)
                {
                    first4.insert(rand()%10);
                }
                first4.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time<< " mls" << std::endl;

                size = 50000000;
                start_time =  clock(); // начальное время
                BinaryTree<int> first5;
                for (int i = 0; i < size; ++i)
                {
                    first5.insert(rand()%10);
                }
                first5.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

                size = 60000000;
                start_time =  clock(); // начальное время
                BinaryTree<int> first6;
                for (int i = 0; i < size; ++i)
                {
                    first6.insert(rand()%10);
                }
                first6.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

                size = 70000000;
                start_time =  clock(); // начальное время
                BinaryTree<int> first7;
                for (int i = 0; i < size; ++i)
                {
                    first7.insert(rand()%10);
                }
                first7.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

                size = 80000000;
                start_time =  clock(); // начальное время
                BinaryTree<int> first8;
                for (int i = 0; i < size; ++i)
                {
                    first8.insert(rand()%10);
                }
                first8.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

                size = 90000000;
                start_time =  clock(); // начальное время
                BinaryTree<int> first9;
                for (int i = 0; i < size; ++i)
                {
                    first9.insert(rand()%10);
                }
                first9.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

                size = 100000000;
                start_time =  clock(); // начальное время
                BinaryTree<int> first10;
                for (int i = 0; i < size; ++i)
                {
                    first10.insert(rand()%10);
                }
                first10.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;


            }
        }

    }


    return 0;
}