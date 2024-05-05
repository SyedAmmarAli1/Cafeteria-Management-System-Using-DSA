#include<iomanip>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
using namespace std;
struct node
{
    char foodname[50];
    int quantity;
    float price;
    int data;
    struct node* prev;
    struct node* next;
};

struct node* headc = NULL, * temp, * tailc = NULL;
struct node* heada = NULL, * taila = NULL;
struct node* head_s;
void cls()
{
    system("cls");
}
void ccolor(int clr)
{

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, clr);

}

void adminmenu()
{
    cout << ("\n\t\t\t\t\t\t\t1. View total sales\n");
    cout << ("\t\t\t\t\t\t\t2. Add new items in the order menu\n");
    cout << ("\t\t\t\t\t\t\t3. Delete items from the order menu\n");
    cout << ("\t\t\t\t\t\t\t4. Display order menu\n");
    cout << ("\t\t\t\t\t\t\t5. Back To Main Menu \n\n");
    cout << ("\t\t\t\t\t\t\t   Enter Your Choice --->");
}

void customermenu()
{
    cout << ("\n\t\t\t\t\t\t\t1. Place your order\n");
    cout << ("\t\t\t\t\t\t\t2. View your ordered items\n");
    cout << ("\t\t\t\t\t\t\t3. Delete an item from order\n");
    cout << ("\t\t\t\t\t\t\t4. Display final bill\n");
    cout << ("\t\t\t\t\t\t\t5. Back To Main Menu \n\n");
    cout << ("\t\t\t\t\t\t\t   Enter Your Choice --->");
}

struct node* createadmin(struct node* head, int data, const char foodname[25], float price)
{
    temp = (struct node*)malloc(sizeof(struct node));

    temp->data = data;
    temp->price = price;
    temp->quantity = 0;
    strcpy_s(temp->foodname, foodname);
    temp->next = NULL;
    temp->prev = NULL;

    struct node* l = head;

    if (l == NULL)
        heada = taila = temp;
    else
    {
        while (l->next != NULL)
            l = l->next;

        l->next = temp;
        temp->prev = taila;
        taila = temp;
    }

    return heada;
}

struct node* createcustomer(struct node* head, int data, int quantity)
{
    temp = (struct node*)malloc(sizeof(struct node));

    struct node* l1 = heada;
    int flag = 0;
    while (l1 != NULL)
    {
        if (l1->data == data)
        {
            flag = 1;
            break;
        }
        l1 = l1->next;
    }

    if (flag == 1)
    {
        temp->data = data;
        temp->price = quantity * (l1->price);
        temp->quantity = quantity;
        strcpy_s(temp->foodname, l1->foodname);
        temp->next = NULL;
        temp->prev = NULL;

        struct node* l = head;

        if (l == NULL)
            headc = tailc = temp;
        else
        {
            while (l->next != NULL)
                l = l->next;

            l->next = temp;
            temp->prev = tailc;
            tailc = temp;
        }


    }
    else
    {
        cout << ("\n\t\t\t\t\t\t\tThis item is not present in the menu!\n");
    }
    return headc;
}

void displayList(struct node* head)
{
    struct node* l1 = head;
    if (l1 == NULL)
    {
        cout << ("\n\t\t\t\t\t\t\t\tList is empty!!\n\n");
    }
    else
    {
        cout << ("\n");
        while (l1 != NULL)
        {
            if (l1->quantity == 0) {

                cout << ("\n\t"); ccolor(240);
                cout << ("_______________________________________________________"); ccolor(26);
                cout << ("\n\t"); ccolor(240);
                cout << ("  Food Code          Name                Price         "); ccolor(26);
                cout << ("\n\t"); ccolor(240);
                cout << ("-------------------------------------------------------"); ccolor(26);




                cout << ("\n\t");
                cout << "  " << l1->data << "\t   |" << l1->foodname << " \t   |   " << l1->price;
                ccolor(26);
                cout << ("\n\t");
                cout << ("-------------------------------------------------------");

            }
            else
            {
                cout << ("\n\t"); ccolor(240);
                cout << ("____________________________________________________________________________"); ccolor(26);
                cout << ("\n\t"); ccolor(240);
                cout << ("  Food Code          Name                Price                Quantity      "); ccolor(26);
                cout << ("\n\t"); ccolor(240);
                cout << ("----------------------------------------------------------------------------"); ccolor(26);




                cout << ("\n\t");
                cout << "  " << l1->data << "\t   |" << l1->foodname << " \t   |   " << l1->price << " \t   |   " << l1->quantity;
                ccolor(26);
                cout << ("\n\t");
                cout << ("----------------------------------------------------------------------------");
            }

            l1 = l1->next;
        }
        cout << ("\n");
    }

}


struct node* totalsales(int data, int quantity)
{
    temp = (struct node*)malloc(sizeof(struct node));
    int flag = 0;

    struct node* l1 = heada;
    while (l1->data != data)
    {
        l1 = l1->next;
    }

    temp->data = data;
    temp->price = quantity * (l1->price);
    temp->quantity = quantity;
    strcpy_s(temp->foodname, l1->foodname);
    temp->next = NULL;
    temp->prev = NULL;

    struct node* l = head_s;

    if (l == NULL)
        head_s = temp;
    else
    {
        while (l->next != NULL)
        {
            if (l->data == data)
            {
                flag = 1;
                break;
            }
            l = l->next;
        }

        if (flag == 1)
        {
            l->quantity += temp->quantity;
            l->price += temp->price;
        }
        else
        {
            l->next = temp;
        }
    }

    return head_s;
}

void calculatetotsales()
{
    struct node* l = headc;
    while (l != NULL)
    {
        head_s = totalsales(l->data, l->quantity);
        l = l->next;
    }
}

struct node* deletee(int data, struct node* head, struct node* tail)
{
    if (head == NULL)
    {
        cout << ("\n\t\t\t\t\t\t\tList is empty\n");
    }
    else
    {
        struct node* l;
        if (data == head->data)
        {
            l = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            free(l);
        }
        else if (data == tail->data)
        {
            l = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(l);
        }
        else
        {
            l = head;
            while (data != l->data)
            {
                l = l->next;
            }
            (l->prev)->next = l->next;
            (l->next)->prev = l->prev;
            free(l);
        }
    }
    return head;
}

int deleteadmin()
{
    cout << ("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
    int num, count2 = 4;
up8:
    cin >> num;
    while (!cin.good() || num < 0)
    {
        if (count2 > 1 && count2 <= 4) {
            count2--;
            cout << "\n\n        " << count2 << " times left";
            cout << "\n\t\t\t\t\t\tInvalid serial no.! Enter again: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            goto up8;
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        system("pause");
        system("CLS");
    }

    struct node* l = heada;
    while (l != NULL)
    {
        if (l->data == num)
        {
            heada = deletee(num, heada, taila);
            return 1;
        }
        l = l->next;
    }

    return 0;
}

int deletecustomer()
{
    cout << ("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
    int num, count1 = 4;
up7:
    cin >> num;
    while (!cin.good() || num < 0)
    {
        if (count1 > 1 && count1 <= 4) {
            count1--;
            cout << "\n\n        " << count1 << " times left";
            cout << "\n\t\t\t\t\t\tInvalid serial no.! Enter again: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            goto up7;
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        system("pause");
        system("CLS");
    }

    struct node* l = headc;
    while (l != NULL)
    {
        if (l->data == num)
        {
            headc = deletee(num, headc, tailc);
            return 1;
        }
        l = l->next;
    }

    return 0;
}

void displaybill()
{
    displayList(headc);
    struct node* l = headc;
    float total_price = 0;
    while (l != NULL)
    {
        total_price += l->price;
        l = l->next;
    }

    cout << endl << endl;
    cout << "\t\t\t\tTotal Bill :" << total_price;
    cout << endl;


}

struct node* deleteList(struct node* head)
{
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        struct node* l = head;
        while (l->next != 0)
        {
            l = l->next;
            free(l->prev);
        }
        free(l);
        head = NULL;
    }

    return head;
}

void admin()
{
    cout << ("\n\t\t\t\t\t   ----------------------------------------------\n");
    cout << ("\t\t\t\t\t\t\t    ADMIN SECTION\n");
    cout << ("\t\t\t\t\t   ----------------------------------------------\n");
    cout << ("\n\t\t\t\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  ");
    char uid[20], pwd[20], c = ' ';
    int i = 0;
    int counter = 4;
up:
    cout << ("\n\n\t\t\t\t\t\t  ENTER USERNAME:-");
    cin >> uid;
    cout << ("\n\n\t\t\t\t\t\t  ENTER PASSWORD:-");
    c = ' '; i = 0;
    while (i < 20)
    {
        pwd[i] = _getch();
        c = pwd[i];
        if (c == '\r') break;
        else cout << ("*");
        i++;
    }

    pwd[i] = '\0';

    if (strcmp(uid, "admin") == 0 && strcmp(pwd, "admin123") == 0) {
        cout << ("\n\t\t\t\t\t   ----------------------------------------------\n");
        cout << ("\t\t\t\t\t\t\t    WELCOME ADMIN\n");
        cout << ("\t\t\t\t\t   ----------------------------------------------\n");
        Sleep(2000);




        while (1)
        {
        label:
            adminmenu();

            int opt;
        up6:
            cin >> opt;
            int counter1 = 4;

            while (!cin.good() || opt < 0)
            {
                if (counter1 > 1 && counter1 <= 4) {
                    counter1--;
                    cout << "\n\n        " << counter1 << " times left";
                    cout << "\n\t\t\t\t\t\tInvalid choice! Enter again: ";
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    goto up6;
                }
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                system("pause");
                system("CLS");
                goto label;
            }

            if (opt == 5)
                break;

            switch (opt)
            {
            case 1:
                displayList(head_s);
                break;
            case 2:
            {


                cout << ("\n\t\t\t\t\t\t\tEnter serial no. of the food item: ");
                int num, counter2 = 4, flag = 0;
                char name[50];
                float price;
            up5:
                cin >> num;
                while (!cin.good() || num < 0)
                {
                    if (counter2 > 1 && counter2 <= 4) {
                        counter2--;
                        cout << "\n\n        " << counter2 << " times left";
                        cout << "\n\t\t\t\t\t\tInvalid serial no. ! Enter again: ";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        goto up5;
                    }
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    system("pause");
                    system("CLS");
                    goto label;
                }

                struct node* l = heada;

                while (l != NULL)
                {
                    if (l->data == num)
                    {
                        cout << ("\n\t\t\t\t\t\tFood item with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    l = l->next;
                }

                if (flag == 1)
                    break;

            input:
                cout << ("\t\t\t\t\t\t\tEnter food item name: ");
                cin.ignore();
                cin.getline(name, 49);
                for (int i = 0; i < 50; i++) {
                    if (isdigit(name[i])) {
                        cout << "\t\t\t\t\t\t\tInvalid food name\n";
                        goto input;
                    }
                }
                cout << ("\t\t\t\t\t\t\tEnter price: ");
            up4:
                cin >> price;
                int counter3 = 4;
                while (!cin.good() || price < 0)
                {
                    if (counter3 > 1 && counter3 <= 4) {
                        counter3--;
                        cout << "\n\n        " << counter3 << " times left";
                        cout << "\n\t\t\t\t\t\tInvalid price ! Enter again : ";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        goto up4;
                    }
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    system("pause");
                    system("CLS");
                    goto label;
                }
                heada = createadmin(heada, num, name, price);
                cout << ("\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n");
                break;
            }
            case 3:
                if (deleteadmin())
                {
                    cout << ("\n\t\t\t\t\t\t### Updated list of food items menu ###\n");
                    displayList(heada);
                }
                else
                    cout << ("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!\n\n");

                break;
            case 4:
                cout << ("\n\t\t\t\t\t\t\t   ### Order menu ###\n");
                displayList(heada);
                break;

            default:
                cout << ("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
            }
        }
    }
    else {

        if (strcmp(uid, "admin") != 0 || strcmp(pwd, "admin123") != 0) {
            cout << "\n\n        INCORRECT USERNAME OR PASSWORD\n";
            if (counter > 1 && counter <= 4) {
                counter--;
                cout << "\n        " << counter << " times left";

                goto up;
            }
        }
        system("pause");
        system("CLS");
    }
}

void customer()
{
    int flag = 0, j = 1;
    char ch;
    cout << ("\n\t\t\t\t\t   ----------------------------------------------\n");
    cout << ("\t\t\t\t\t\t\t    CUSTOMER SECTION\n");
    cout << ("\t\t\t\t\t   ----------------------------------------------\n");
    while (1)
    {
    label1:
        customermenu();

        int opt, counter4 = 4;
    up2:
        cin >> opt;
        while (!cin.good() || opt < 0)
        {
            if (counter4 > 1 && counter4 <= 4) {
                counter4--;
                cout << "\n\n        " << counter4 << " times left";
                cout << "\n\t\t\t\t\t\tInvalid! Enter again: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                goto up2;
            }
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            system("pause");
            system("CLS");
            goto label1;
        }

        if (opt == 5)
            break;

        switch (opt)
        {
        case 1:
            displayList(heada);
            cout << ("\n\t\t\t\t\t\tEnter serial number corresponding to the item you want to order: ");
        up1:
            int n;
            cin >> n;
            while (!cin.good() || n < 0)
            {
                if (counter4 > 1 && counter4 <= 4) {
                    counter4--;
                    cout << "\n\n        " << counter4 << " times left";
                    cout << "\n\t\t\t\t\t\tInvalid serial no. ! Enter again: ";
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    goto up1;
                }
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                system("pause");
                system("CLS");
                goto label1;
            }
            cout << ("\t\t\t\t\t\tEnter quantity: ");
            int quantity;
        up3:
            cin >> quantity;

            while (!cin.good() || quantity < 0)
            {
                if (counter4 > 1 && counter4 <= 4) {
                    counter4--;
                    cout << "\n\n        " << counter4 << " times left";
                    cout << "\n\t\t\t\t\t\tInvalid quantity! Enter again: ";
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    goto up3;
                }
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                system("pause");
                system("CLS");
                goto label1;

            }
            headc = createcustomer(headc, n, quantity);
            break;
        case 2:
            cout << ("\n\t\t\t\t\t\t\t  ### List of ordered items ###\n");
            displayList(headc);
            break;
        case 3:
            if (deletecustomer())
            {
                cout << ("\n\t\t\t\t\t\t### Updated list of your ordered food items ###\n");
                displayList(headc);
            }
            else
                cout << ("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n");
            break;
        case 4:
            calculatetotsales();
            cout << ("\n\t\t\t\t\t\t\t  ### Final Bill ###\n");
            displaybill();
            headc = deleteList(headc);
            cout << ("\n\t\t\t\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t");
            fflush(stdin);
            ch = fgetc(stdin);
            flag = 1;
            break;

        default:
            cout << ("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
            break;
        }
        if (flag == 1)
            break;
    }
}

void Menu()
{
    cout << ("\n                                 **************************************************************************\n");
    cout << ("                                                     WELCOME TO CAFETERIA MANAGEMENT SYSTEM\n");
    cout << ("                                 **************************************************************************\n\n\n");
    cout << ("\t\t\t\t\t\t\t1. ADMIN SECTION--> \n");
    cout << ("\t\t\t\t\t\t\t2. CUSTOMER SECTION--> \n");
    cout << ("\t\t\t\t\t\t\t3. Exit--> \n\n");
    cout << ("\t\t\t\t\t\t\t Enter Your Choice --->");
}
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void boldgreen()
{
    cout << "\033[1m\033[32m";
}

void red()
{
    cout << "\033[1m\033[31m";
}
void start()
{
    system("cls");
    int i, j;
    gotoxy(45, 10);
    red();
    cout << "*************** CAFETERIA MANAGEMENT SYSTEM ***************";
    gotoxy(40, 15);
    boldgreen();
    cout << "LOADING...";
    gotoxy(45, 16);
    for (i = 1; i <= 60; i++)
    {
        for (j = 1; j <= 20000000; j++)
            ;
        cout << char(220);
    }
    gotoxy(45, 20);
    red();
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t Project Prepared by" << endl << endl;
    boldgreen();
    cout << "\t\t\t\t\t\t\t\t Syed Ammar Ali" << endl;
    cout << "\t\t\t\t\t\t\t\t Tashad Tarij Rana" << endl;
    cout << "\t\t\t\t\t\t\t\t Muhammad Abdullah Butt" << endl;
    cout << endl;
    system("pause");
    system("cls");
}

int main()
{
    static CONSOLE_FONT_INFOEX  fontex;
    fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    GetCurrentConsoleFontEx(h, 0, &fontex);
    fontex.FontWeight = 700;
    fontex.dwFontSize.X = 25;
    fontex.dwFontSize.Y = 25;
    SetCurrentConsoleFontEx(h, 0, &fontex);

    heada = createadmin(heada, 1, "Allo Wala paratha", 100);
    heada = createadmin(heada, 2, "Burger", 200);
    heada = createadmin(heada, 3, "Manchurian", 150);
    heada = createadmin(heada, 4, "Fried Rice", 180);
    heada = createadmin(heada, 5, "Chai", 60);
    heada = createadmin(heada, 6, "Biryani", 180);
    heada = createadmin(heada, 7, "Coffee", 80);
    heada = createadmin(heada, 8, "Paratha roll", 120);
    heada = createadmin(heada, 9, "Anda Paratha", 110);
    heada = createadmin(heada, 10, "Peach Juice", 90);

    ccolor(26);
    start();
    while (1)
    {
    label3:
        Menu();
        int choice, counter7 = 4;
    up:
        cin >> choice;
        while (!cin.good() || choice < 0)
        {
            if (counter7 > 1 && counter7 <= 4) {
                counter7--;
                cout << "\n\n        " << counter7 << " times left";
                cout << "\n\t\t\t\t\t\tInvalid Choice! please try again: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                goto up;
            }
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            system("pause");
            system("CLS");
            goto label3;
        }

        if (choice == 3)
        {
            cout << ("\n\n\t\t\t\t\t\t\t**********Thank you!!**********\n");
            break;
        }

        switch (choice)
        {
        case 1:
            admin();
            break;
        case 2:
            customer();
            break;
        case 3:
            break;

        default:
            cout << ("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
            break;
        }
    }
}
