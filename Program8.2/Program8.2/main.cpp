//
//  main.cpp
//  Program8.2
//
//  Created by Игорь Аралин on 29.12.20.
//

#include <iostream>
#include <fstream>

using namespace std;

struct Customer
{
    short id;
    char date[11];
    char city[16];
    int citycode;
    int time;
    int packet;
    long tnumber;
    bool enabled;
};

//    Подключение файла
ofstream fout("/Users/exonymus/Projects/Program8/Program8.2/Program8.2/ATS_Base.txt", ios_base::app);
ifstream fin("/Users/exonymus/Projects/Program8/Program8.2/Program8.2/ATS_Base.txt");

Customer* AddStruct(Customer* database, int id);
void DB_Fill(Customer* database, int id);
void DB_Show(Customer* database, int id);
void DB_Edit(Customer* database, int id);
void DB_Sum(Customer* database, int id);

int main()
{
    char check;
    int id = 0;
    Customer* DataBase = 0;
    
//    Заполнение базы из файла
    fin >> check;
    if (check == '#')
        while (!fin.eof())
        {
            DataBase = AddStruct(DataBase, id);
            DataBase[id].id = id;
            fin >> DataBase[id].date >> DataBase[id].city >> DataBase[id].citycode >> DataBase[id].time >> DataBase[id].packet >> DataBase[id].tnumber >> check;
            DataBase[id].enabled = true;
            id++;
        }
    
//    Работа с фукциями клиентской базы
    int action;
    do
    {
        printf("Выберите действие с Базой Клиентов:\n 0 - Выход,\n 1 - Вывод Базы,\n 2 - Изменение Базы,\n 3 - Вывести общую информацию по городам,\n 4 - Добавить новую запись,\n 5 - Удалить запись:\n");
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
            
                if (id <= edit) printf("Данного клиента не существует!");
                else DB_Edit(DataBase, edit);
                break;
            
            case 3:
                DB_Sum(DataBase, id);
                break;
            
            case 4:
                DataBase = AddStruct(DataBase, id);
                DB_Fill(DataBase, id);
                id++;
                break;
                
            case 5:
                int del;
                printf("Введите номер(ID) клиента: ");
                scanf("%d", &del);
            
                if (id <= del) printf("Данного клиента не существует!");
                else DataBase[del].enabled = false;
                break;
            
            default:
                break;
        }
    } while (action != 0);
    
    fin.close();
    fout.close();
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
    printf("Введите дату разговора: ");
    scanf("%s", database[id].date);
    
    printf("Введите город клиента с кодом (в формате Город Код): ");
    scanf("%s", database[id].city);
    scanf("%d", &database[id].citycode);
    
    printf("Введите время разговора (в минутах): ");
    scanf("%d", &database[id].time);
    
    printf("Введите стоимость тарифа: ");
    scanf("%d", &database[id].packet);
    
    printf("Введите номер телефона: ");
    scanf("%ld", &database[id].tnumber);
    
//    Обновление данных в файле
    fout << "# "<< database[id].date << " " << database[id].city<< " " << database[id].citycode<< " " << database[id].time << " " << database[id].packet<< " " << database[id].tnumber << "\n";
    database[id].enabled = true;
}

//  Вывод данных базы клиентов
void DB_Show(Customer* database, int id)
{
    if (database[id].enabled == true)
    {
        printf("\nID клиента: %d\n", database[id].id);
        printf("Дата разговора: %s\n", database[id].date);
        printf("Город: %s(", database[id].city);
        printf("%d)\n", database[id].citycode);
        printf("Время разговора: %d\n", database[id].time);
        printf("Стоимость тарифа: %d\n", database[id].packet);
        printf("Номер телефона: %ld\n", database[id].tnumber);
        printf("\n<----------------------------------------------->\n\n");
    }
}

//  Изменение базы клиентов
void DB_Edit(Customer* database, int id)
{
    int edit;
    printf("Введите номер поля для изменения: \n1 - Дата,\n2 - Город/Код города,\n3 - Время разговора,\n4 - Стоимость тарифа,\n5 - Номер телефона: ");
    scanf("%d", &edit);
//  Выбор поля для изменения
    switch (edit)
    {
        case 1:
            printf("Введите дату разговора: ");
            scanf("%s", database[id].date);
            break;
            
        case 2:
            printf("Введите город клиента с кодом (в формате Город Код): ");
            scanf("%s", database[id].city);
            scanf("%d", &database[id].citycode);
            break;
        
        case 3:
            printf("Введите время разговора (в минутах): ");
            scanf("%d", &database[id].time);
            break;
            
        case 4:
            printf("Введите стоимость тарифа: ");
            scanf("%d", &database[id].packet);
            break;
            
        case 5:
            printf("Введите номер телефона: ");
            scanf("%ld", &database[id].tnumber);
            break;
    }
}

//  Вывод общей информации по городам
void DB_Sum(Customer* database, int id)
{
    int time = 0, money = 0;
        for (int i = 0; i < id; i++)
        {
            time = database[i].time;
            money = database[i].time * database[i].packet;
            
//            Проверка всех элементов вокруг заданного
            if (id > 1 && i != (id - 1) && database[i].enabled == true)
                {
                    for (int j = i+1; j != i;)
                    {
                        if (database[i].citycode == database[j].citycode)
                        {
                            database[j].enabled = false;
                            time += database[j].time;
                            money += database[j].time * database[j].packet;
                        }
                        j++;
                        if (j == id) j = 0;
                    }
                }
//            Проверка элементов вниз от крайнего
            else
                if (id > 1 && i == (id - 1) && database[i].enabled == true)
                {
                for (int j = 0; j != i;j++)
                    {
                        if (database[i].citycode == database[j].citycode)
                        {
                            database[j].enabled = false;
                            time += database[j].time;
                            money += database[j].time * database[j].packet;
                        }
                    }
                }
            
//            Вывод результата
            if (database[i].enabled == true)
            {
                printf("\nГород: %s\n", database[i].city);
                printf("Общее время разговоров: %d\n", time);
                printf("Общая cумма: %d\n\n", money);
                printf("\n<------------------------->\n\n");
            }
        }
    
//    Возвращение флага доступности всем элементам базы
    for (int i = 0; i < id; i++)
        database[i].enabled = true;
}
