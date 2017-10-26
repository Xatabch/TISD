#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SEARCH_NAME "Sidorov"

//списки да короче
struct person
{
    char *name;//ну ту имя этого кореша
    int born_year;//тут дата его рождения

    struct person *next;//это я тут тип понял так указатель на следующий элемент да
};

//создаем так сказать персону, да, личность, да)
struct person* create_person(char *name, int born_year)
{
    struct person *pers = malloc(sizeof(struct person));//малокнули короче размер да, для персоны на размер структуры

    if (pers)//если порядочек
    {
        pers->name = name;//имени имя
        pers->born_year = born_year;//дате дату
        pers->next = NULL;//и соответсна это вот так создается элемент, то у него тип просто элемент      
    }
        
    return pers;//вернули структурку
}

//это значит добавить перед элементом заданным да
struct person* add_front(struct person *head,//сюда передаем голову эелемента, ну, че добавлять то будем да)Ну, в голову да)
                                   struct person *pers)//а сюда соответсна структурку мою саму да
{
    pers->next = head;//вот это интересно бл, тут добавили короче к нехту голову да, во дела, хотя вроде как доабвили указатель на след элемент да
    return pers;//вернули структурку да
}

//вот тот короче пересоздает структуру, а этот он вообще красавчик, он уже структуру получает да, там все по схеме
void add_front_2(struct person **head,
                                   struct person *pers)
{
    pers->next = *head;
    *head = pers;
}

//а это короче да, в конец элемент добавить да
struct person* add_end(struct person *head, 
                                   struct person *pers)
{
    struct person *cur = head;//кюр = хед, ничего не понял но жа лана

    if (!head)//если не голова, тоесть чет вроде не имеет ссылки, то выернули персону да
        return pers;

    for ( ; cur->next; cur = cur->next)
        ;//тут вообще вне понимая че происходит

    cur->next = pers;//кюр да равняется переданной персоне

    return head;//вернули голову да
}

//тут поиск элемента, так как констатнтый указатель кидаем делай че хочешь короче
struct person* lookup(struct person *head,
                                     const char *name)
{
    for ( ; head; head = head->next)
        if (strcmp(head->name, name) == 0)
            return head;

    return NULL;
}


void apply(struct person *head,
             void (*f)(struct person*, void*),
                                         void* arg)
{
    for ( ; head; head = head->next)
        f(head, arg);
}


void print_person(struct person *pers, void *arg)
{
    char *fmt = arg;

    printf(fmt, pers->name, pers->born_year);
}


void count(struct person *pers, void *arg)
{
    int *counter = arg;

    (*counter)++;
}


void free_all(struct person *head)
{
    struct person *next;

    for ( ; head; head = next)
    {
        next = head->next;
        free(head);
    }
}


struct person* del_by_name(struct person *head,
                                         const char *name)
{
    struct person *cur, *prev = NULL;

    for (cur = head; cur; cur = cur->next)
    {
        if (strcmp(cur->name, name) == 0)
        {
            if (prev)
                prev->next = cur->next;
            else
                head = cur->next;

            free(cur);

            return  head;
        }

        prev = cur;
    }

    return NULL;
}


int main(void)
{
    struct person *head = NULL;
    struct person *node;
    int n = 0;

    // NB: "Ivanov" - ñòðîêîâûé ëèòåðàë, ò.å. ñòðîêîâàÿ êîíñòàíòà
    node = create_person("Ivanov", 1995);
    assert(node);
    head = add_front(head, node);

    node = create_person(SEARCH_NAME, 1994);
    assert(node);
    head = add_front(head, node);

    node = create_person("Petrov", 1995);
    assert(node);
    head = add_front(head, node);

    apply(head, print_person, "%s %d\n");

    printf("\n");

    node = create_person("Vasechkin", 1996);
    assert(node);
    head = add_end(head, node);

    apply(head, print_person, "%s %d\n");

    printf("\n");

    apply(head, count, &n);

    printf("List contains %d element(s)\n", n);

    node = lookup(head, SEARCH_NAME);

    printf("%s is in %p element\n", SEARCH_NAME, node);

    head = del_by_name(head, SEARCH_NAME);

    node = lookup(head, SEARCH_NAME);

    printf("%s is in %p element\n", SEARCH_NAME, node);

    free_all(head);

    return 0;
}


/*
// main äëÿ add_front_2
int main (void)
{
    struct person *head = NULL;
    struct person *node;

    node = create_person("Ivanov", 1995);
    assert(node);
    add_front_2(&head, node);

    node = create_person(SEARCH_NAME, 1994);
    assert(node);
    add_front_2(&head, node);

    node = create_person("Petrov", 1995);
    assert(node);
    add_front_2(&head, node);

    apply(head, print_person, "%s %d\n");

    printf("\n");

    free_all(head);

    return 0;
}
*/