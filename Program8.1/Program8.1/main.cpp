//
//  main.cpp
//  Program8.1
//
//  Created by Игорь Аралин on 26.12.20.
//

#include <iostream>

using namespace std;

struct Customer
{
    short id;
    char name[16];
    char secname[16];
    char surname[16];
    char address[32];
    float discount;
};

Customer* AddStruct(Customer* database, int id);
void DB_Fill(Customer* database, int id);
void DB_Show(Customer* database, int id);
void DB_Edit(Customer* database, int id);
void DB_Sort(Customer* database, int id);

int main()
{
    int id = 0;
    Customer* DataBase = 0;
    int newcust = 1;
    
//    Заполнение клиентской базы
    do
    {
        DataBase = AddStruct(DataBase, id);
        DB_Fill(DataBase, id);
        id++;
        printf("Продолжить ввод данных клиентов? (1 - Да, 0 - Нет) ");
        scanf("%d", &newcust);
    } while (newcust != 0);
    
//    Работа с фукциями клиентской базы
    int action;
    do
    {
        printf("\n\n\n");
        printf("Выберите действие с Базой Клиентов:\n 0 - Выход,\n 1 - Вывод Базы,\n 2 - Изменение Базы,\n 3 - Сортировка Базы,\n 4 - Добавить нового клиента,\n 5 - Список клиентов с 5%% скидкой\n");
        scanf("%d", &action);
    
        switch (action)
        {
            case 1:
                for (int i = 0; i < id; i++)
                    DB_Show(DataBase, i);
                break;
            
            case 2:
                int edit;
                printf("Введите номер(ID) клиента: ");
                scanf("%d", &edit);
            
                if (id < edit) printf("Данного клиента не существует!");
                else DB_Edit(DataBase, edit);
                break;
            
            case 3:
                DB_Sort(DataBase, id);
                break;
            
            case 4:
                DataBase = AddStruct(DataBase, id);
                DB_Fill(DataBase, id);
                id++;
                break;
            case 5:
                for (int i = (id - 1); DataBase[i].discount >= 5; i--)
                    if (DataBase[i].discount == 5) DB_Show(DataBase, i);
                break;
            default:
                break;
        }
    } while (action != 0);
    
    return 0;
}

Customer* AddStruct(Customer* database, int id)
{
    if (id == 0) database = new Customer[id + 1];
    else
    {
        Customer* tempdb = new Customer[id + 1];
        for (int i = 0; i < id; i++)
            tempdb[i] = database[i];
        database = tempdb;
    }
    return database;
}

//    Ввод данных клиентской базы
void DB_Fill(Customer* database, int id)
{
    database[id].id = id;
    printf("Введите ФИО клиента: ");
    scanf("%s", database[id].surname);
    scanf("%s", database[id].name);
    scanf("%s", database[id].secname);
    
    
    printf("Введите адрес клиента (без пробелов): ");
    scanf("%s", database[id].address);
    
    printf("Введите объем скидки клиента(%%): ");
    scanf("%f", &database[id].discount);
}

//  Вывод данных базы клиентов
void DB_Show(Customer* database, int id)
{
    printf("\nID клиента: %d\n", database[id].id);
    printf("ФИО клиента: %s", database[id].surname);
    printf(" %s", database[id].name);
    printf(" %s\n", database[id].secname);
    printf("Адрес клиента: %s\n", database[id].address);
    printf("Скидка клиента: %f%%\n", database[id].discount);
    printf("\n<----------------------------------------------->\n\n");
}

//  Изменение базы клиентов
void DB_Edit(Customer* database, int id)
{
    int edit;
    printf("Введите номер поля для изменения (1 - ФИО, 2 - Адрес, 3 - Объем скидки): ");
    scanf("%d", &edit);
//  Выбор поля для изменения
    switch (edit)
    {
        case 1:
            printf("Введите новое ФИО клиента: ");
            scanf("%s", database[id].surname);
            scanf("%s", database[id].name);
            scanf("%s", database[id].secname);
            break;
            
        case 2:
            printf("Введите новый адрес клиента (без пробелов): ");
            scanf("%s", database[id].address);
            break;
        
        case 3:
            printf("Введите новую скидку клиента(%%): ");
            scanf("%f", &database[id].discount);
            break;
    }
}

//  Сортировка клиентской базы вставкой по возрастанию
void DB_Sort(Customer* database, int id)
{
    Customer* temp = new Customer[1];
    int previd;
        for (int i = 1; i < id; i++)
        {
            temp[0] = database[i];
            previd = i - 1;
//            Перестановка компонентов клиентской базы
            while(previd >= 0 && database[previd].discount > temp[0].discount)
            {
                database[previd+1] = database[previd];
                database[previd] = temp[0];
                previd--;
            }
        }
}
