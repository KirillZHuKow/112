#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

typedef struct string
{
    int lenght;
    void* begin_str;
}string;
typedef struct strsearch
{
    int search;
    int first;
    int second;
}strsearch;

void output(string* str);
string* concatenation(string *str1,string *str2);
int menu();
string* input();
string* get_substring(int first, int second, string *str);
string* get_linc(int num);
void free_line_par(string* memory);
strsearch* substring_search(string *str, string *search_str, int operation);
void input_res_search(strsearch* get);
void free_res_search(strsearch* memory);


int main()
{
    int k = 1;
    while(k)
    {
        int func;
        func = menu();
        if (func == 1) {
            string *str1, *str2, *sum_str;
            printf("First string\n");
            str1 = input();
            printf("Second string\n");
            str2 = input();
            printf("Result string:  \n ");
            sum_str = concatenation(str1, str2);
            output(sum_str);
            free_line_par(sum_str);
            free_line_par(str1);
            free_line_par(str2);
        } else if (func == 2) {
            int first, second;
            string *str, *min_str;
            str = input();
            printf("From symbol: ");
            scanf("%d", &first);
            printf("To symmbol: ");
            scanf("%d", &second);
            printf("Result string: ");
            min_str = get_substring(first, second, str);
            output(min_str);
            free_line_par(min_str);
            free_line_par(str);
        } else if (func == 3 || func == 4) {
            strsearch *res;
            string *str, *search_str;
            printf("Source string\n");
            str = input();
            printf("Search string\n");
            search_str = input();
            res = substring_search(str, search_str, func);
            input_res_search(res);
            free_line_par(str);
            free_line_par(search_str);
            free_res_search(res);
        }
        else{break;}
    }
    return 0;
}

//меню
int menu()
{
    int function;
    printf("\nChoose a function: \n");
    printf("1 Concatenation\n");
    printf("2 Get a substring\n");
    printf("3 Case-sensetive substring search\n");
    printf("4 Case-insensetive substring search\n");
    printf("5 Exit\n");
    scanf("%d", &function);
    return function;
}
//ввод строки c консоли
string* input()
{
    string* str;
    int num;
    printf("Enter a string lenght: ");
    scanf("%d", &num);
    str = get_linc(num);
    printf("Enter string: ");
    for(int i = 0; str->lenght > i; i++)
    {
        scanf("%s", (str->begin_str+i));
    }
    return str;
}
//вывод строки на консоль
void output(string* str)
{
    for(int i=0;i< str->lenght;i++)
    {
        printf("%c", *(char*)(str->begin_str+i));
    }
}

//выделение памяти под структуру(в которой содержатся: начало строки, количество элементов)
string* get_linc(int num)
{
    string* get;
    get = (string*)malloc(sizeof(struct string));
    get->lenght = num;
    get->begin_str = (char *)malloc(get->lenght * sizeof(char));
    return get;
}

//1. конкантенация 2-х строк
string* concatenation(string *str1,string *str2)
{
    string* sum_str;
    sum_str = get_linc(str1->lenght + str2->lenght);
    for(int i = 0;i< str1->lenght;i++)
    {
        *(char*)(sum_str->begin_str + i) = *(char*)(str1->begin_str + i);
    }
    for(int i = 0;i < str2->lenght;i++)
    {
        *(char*)(sum_str->begin_str + str1->lenght + i) = *(char*)(str2->begin_str + i);
    }
    return sum_str;
}


//2. получение подстроки
string* get_substring(int first, int second, string *str)
{
    string* str_min;
    str_min = get_linc(second - first + 1);
    for (int i = 0; i < str_min->lenght;i++)
    {
        *(char*)(str_min->begin_str + i) = *(char*)(str->begin_str + i + first - 1);
    }
    return str_min;
}

//выделение памяти под структуру для функции поиска подстроки(в которой содержится информация о вхождении строки, а также начального и конечного элемента)
strsearch* get_link_substring()
{
    strsearch* get;
    get = (strsearch*)malloc(sizeof(struct strsearch));
    return get;
}
//3. поиск подстроки
strsearch* substring_search(string *str, string *search_str, int func)
{
    strsearch* res;
    int i, y;
    res = get_link_substring();
    for(i=0; i<=(str->lenght-search_str->lenght); i++)
    {
        for(y=0;y < search_str->lenght;y++)
        {
            if(func==3)
            {
                if (tolower(*(char *) (str->begin_str + y + i)) !=tolower(*(char *) (search_str->begin_str + y))) { break; }
            }
            else
            {
                if (*(char *) (str->begin_str + y + i) !=*(char *) (search_str->begin_str + y)) { break; }            }
        }
        if(y ==search_str->lenght)
        {
            res->search = 1;
            res->first = i+1;
            res->second = search_str->lenght+i;
            break;
        }
        else
        {
            if(i==(str->lenght-search_str->lenght-1)) {res->search = 0;}
            else {continue;}
        }
    }
    return res;
}
//вывод результата поиска подстроки
void input_res_search(strsearch* get)
{
    if (get->search == 0){printf("This substring is not contained in the source string");}
    else
    {
        printf("This substring is contained in the source string from  %d to %d element", get->first,get->second);
    }
}

//освобождение памяти от структуры строки
void free_line_par(string* memory)
{
    free(memory->begin_str);
    free(memory);
}

//освобождение памяти от структуры результата поиска подстроки
void free_res_search(strsearch* memory)
{
    free(memory);
}
//тестирование
void tests()
{
    int i;
    string str1, str2, str3, str4;
    string *str1_new, *str2_new, *str3_new, *str4_new;
    str1.lenght = 5;
    str2.lenght = 3;
    str3.lenght = 2;
    str4.lenght = 5;
    str1.begin_str = (char*)malloc(str1.lenght*sizeof(char));
    str2.begin_str = (char*)malloc(str2.lenght*sizeof(char));
    str3.begin_str = (char*)malloc(str3.lenght*sizeof(char));
    str4.begin_str = (char*)malloc(str4.lenght*sizeof(char));
    *(char*)str1.begin_str = 'q';
    *(char*)(str1.begin_str + 1) = 'w';
    *(char*)(str1.begin_str + 2) = 'e';
    *(char*)(str1.begin_str + 3) = 'r';
    *(char*)(str1.begin_str + 4) = 't';
    *(char*)str2.begin_str= 'q';
    *(char*)(str2.begin_str + 1) = 'w';
    *(char*)(str2.begin_str + 2) = 'e';
    *(char*)str3.begin_str = 'r';
    *(char*)(str3.begin_str + 1) = 't';
    *(char*)str4.begin_str = 'z';
    *(char*)(str4.begin_str + 1) = 'w';
    *(char*)(str4.begin_str + 2) = 'x';
    *(char*)(str4.begin_str + 3) = 'r';
    *(char*)(str4.begin_str + 4) = 'c';
    str1_new = concatenation(&str2, &str3);
    assert(str1_new->number == str1.number);
    for(i = 0;i<str1.number;i++)
    {
        assert(*(char*)(str1.begin_str+i) == *(char*)(str1_new->begin_str+i));
    }
    str2_new = get_substring(1, 3, &str1);
    assert(str2_new->number == str2.number);
    for(i = 0;i<str2.number;i++)
    {
        assert(*(char*)(str2.begin_str+i) == *(char*)(str2_new->begin_str+i));
    }
    str3_new = get_substring(4, 5, &str1);
    assert(str3_new->number == str3.number);
    for(i = 0;i<str3.number;i++)
    {
        assert(*(char*)(str3.begin_str+i) == *(char*)(str3_new->begin_str+i));
    }
    freeing_line_par(str1_new);
    freeing_line_par(str2_new);
    freeing_line_par(str3_new);
    freeing_line_par(str4_new);
}
}






