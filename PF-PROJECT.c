#include <stdio.h>
#include <string.h>

#define MAX_ITEM 100
#define MAX_TABLES 10
#define MAX_ORDER_ITEMS 50
#define RESET "\033[0m"
#define YELLOW "\033[1;33m"
#define GREEN "\033[1;32m"
#define PINK "\033[1;35m"
#define RED "\033[1;31m"
#define BLUE "\033[1;34m"

struct menuitem{
    char name[50];
    char category[50];
    int price;
    int prepTime;
} menuitem;

struct OrderItem{
    int itemIndex;
    int quantity;
    int totalPrice;
    
} OrderItem;

struct menuitem menu[MAX_ITEM];
int menucount=0;
int tables[MAX_TABLES]={0};

char customername[50];
char phone_no[20];
int reservedtable= -1;

struct OrderItem orderlist[MAX_ORDER_ITEMS];
int ordercount=0;

int finaltotal=0;
int prepTime=0;

int paidcash=0;
int returncash=0;

void clearError() {
    while (getchar()!= '\n');
}

void startmenu() {

    strcpy(menu[0].category,"MAIN COURSE" );
    strcpy(menu[0].name, "Cheeseburger"); 
    menu[0].price= 350;menu[0].prepTime = 10;

    strcpy(menu[1].category,"MAIN COURSE");
    strcpy(menu[1].name, "Cheese Sandwich"); 
    menu[1].price= 300;menu[1].prepTime = 8;

    strcpy(menu[2].category, "MAIN COURSE");
    strcpy(menu[2].name, "Chicken Burger"); 
    menu[2].price= 400;menu[2].prepTime = 12;

    strcpy(menu[3].category, "MAIN COURSE");
    strcpy(menu[3].name, "Spicy Chicken"); 
    menu[3].price= 350;menu[3].prepTime = 15;

    strcpy(menu[4].category, "APPETIZERS");
    strcpy(menu[4].name, "Fruit Salad"); 
    menu[4].price= 150;menu[4].prepTime = 5;

    strcpy(menu[5].category,"APPETIZERS");
    strcpy(menu[5].name, "Cocktails"); 
    menu[5].price= 180;menu[5].prepTime = 3;

    strcpy(menu[6].category,"APPETIZERS");
    strcpy(menu[6].name, "Nuggets"); 
    
    menu[6].price= 180;menu[6].prepTime = 7;

    strcpy(menu[7].category,"APPETIZERS");
    strcpy(menu[7].name, "Sandwich"); 
    menu[7].price= 120;menu[7].prepTime = 6;

    strcpy(menu[8].category, "APPETIZERS");
    strcpy(menu[8].name, "French Fries"); 
    menu[8].price= 150;menu[8].prepTime = 5;

    strcpy(menu[9].category,"BEVERAGES");
    strcpy(menu[9].name, "Milkshake"); 
    menu[9].price= 100;menu[9].prepTime = 4;

    strcpy(menu[10].category,"BEVERAGES");
    strcpy(menu[10].name, "Iced Tea"); 
    menu[10].price= 80;menu[10].prepTime = 2;

    strcpy(menu[11].category,"BEVERAGES");
    strcpy(menu[11].name, "Orange Juice"); 
    menu[11].price= 120;menu[11].prepTime = 3;

    strcpy(menu[12].category,"BEVERAGES");
    strcpy(menu[12].name, "Coffee"); 
    menu[12].price= 180;menu[12].prepTime = 4;
    menucount = 13;
}

void displaymenu() {
    printf("\n"YELLOW"================MENU================="RESET"\n");
    char last[20] = "";

    for (int i = 0;i<menucount;i++) {
        if (strcmp(last,menu[i].category)!=0) {

            strcpy(last,menu[i].category);
            printf("\n%s:\n",last);
        }

        printf("%2d.%-20s %dRs(Prep: %dmin)\n",i + 1, menu[i].name, menu[i].price, menu[i].prepTime);
    }
}

void reservetable() {
    printf("\n" GREEN "========Table Reservation=======" RESET "\n");
    printf("Available tables are: ");

    int available= 0;

    for (int i =0; i<MAX_TABLES; i++) {

        if (tables[i]== 0) {
            
            printf("%d ",i + 1);
            available = 1;
        }
    }

    if (!available) {

        printf("\n" RED "Sorry there are no tables available\n" RESET);
        return;
    }

    int choice;
    printf("\nEnter table number: ");
    scanf("%d",&choice);
    clearError();

    if (choice < 1|| choice > MAX_TABLES|| tables[choice - 1] ==1) {

        printf(RED "Invalid table\n" RESET);
        return;
    }

    tables[choice - 1]= 1;
    reservedtable= choice;
    printf(PINK "%d Table is reserved successfully.\n"RESET, reservedtable);
}

void Orderfood() {

    printf("\nEnter name of customer: ");
    scanf("%s", customername);

    printf("Enter phone number: ");
    scanf("%s", phone_no);
    ordercount=0;
    finaltotal= 0;
    prepTime=0;
    reservedtable= -1;

    int choice;
    int quantity;
    char again;

    do {
        displaymenu();

        printf("\nEnter item number: ");
        scanf("%d", &choice);
        clearError();

        if (choice < 1||choice > menucount) {

            printf(RED "This item is not available.\n"RESET);
            continue;
        }

        printf("Enter quantity: ");
        scanf("%d",&quantity);
        clearError();

        orderlist[ordercount].itemIndex =choice - 1;
        orderlist[ordercount].quantity = quantity;
        orderlist[ordercount].totalPrice =menu[choice - 1].price * quantity;

        finaltotal += orderlist[ordercount].totalPrice;
        prepTime += menu[choice - 1].prepTime * quantity;

        ordercount++;

        printf( YELLOW "Do you want to order more item?(y/n): " RESET);
        scanf(" %c", &again);
        clearError();

    } 
    while (again =='y'|| again =='Y');

    printf( PINK "\nWould you like to reserve a table?(y/n): "RESET);
    scanf(" %c", &again);
    clearError();

    if (again =='y' ||again =='Y')
        reservetable();

    printf("\n" GREEN "Please go to the payment section" RESET"\n");
}

void Payment() {
    if (ordercount== 0) {
        printf("\n" RED "No order found. Please order first." RESET"\n");
        return;
    }

    printf( PINK"\nTotal bill = %d Rs\n" RESET, finaltotal);

    printf("Enter cash: ");
    scanf("%d", &paidcash);
    clearError();

    if (paidcash <finaltotal) {
        printf(RED "Payment failed due to insufficient cash.\n" RESET);
        return;
    }

    returncash = paidcash - finaltotal;

    printf("\n" YELLOW "=========== FINAL - BILL ===========" RESET "\n");
    printf("Customer: %s\n", customername);
    printf("Phone: %s\n",phone_no);

    if (reservedtable != -1) {
        printf("Reserved Table: %d\n", reservedtable);
    }
    else {
        printf("Reserved Table: No\n");
    }

    printf(PINK "\n----Ordered Items----\n" RESET);
    for (int i = 0; i < ordercount; i++) {
        printf("%s x %d= %dRs\n",menu[orderlist[i].itemIndex].name,orderlist[i].quantity,orderlist[i].totalPrice);
    }

    printf("\nTotal Price: %dRs\n", finaltotal);
    printf("Cash Paid: %dRs\n", paidcash);
    printf("Cash Returned: %dRs\n", returncash);
    printf("Prep Time: %d minutes\n", prepTime);
    printf("===============================\n");

    printf("\n"PINK " your order has been placed successfully." RESET "\n");
}

void ViewReserved() {
    printf("\n" YELLOW " ====== RESERVED TABLES ======" RESET "\n");
    int found = 0;

    for (int i = 0; i< MAX_TABLES;i++) {

        if (tables[i] == 1) {
            printf("Table %d is reserved.\n", i+ 1);
            found = 1;
        }
    }

    if (!found) printf(RED "No reserved tables.\n" RESET);
}

void AddMenuItem() {

    if (menucount>= MAX_ITEM) {
        printf(RED "Menu is full\n" RESET);
        return;
    }

    printf("\n "PINK "===== ADD MENU ITEM ===== " RESET "\n ");

    printf("Enter Category: ");
    scanf(" %s", menu[menucount].category);  
    
    printf("Enter Item Name: ");
    scanf(" %s", menu[menucount].name);  
    
    printf("Enter Price: ");
    scanf("%d", &menu[menucount].price);
    clearError();

    printf("Enter Preparation Time (in minutes): ");
    scanf("%d", &menu[menucount].prepTime);
    clearError();
    menucount++;

    printf(PINK "\nItem successfully added\n" RESET);
}

void ManagerPanel() {
    char pass[20];

    printf("\nEnter Password: ");
    scanf("%s",pass);
    clearError();

    if (strcmp(pass, "admin123") != 0) {
        printf(RED "Wrong password!\n" RESET);
        return;
    }

    int option;

    do {
        printf("\n" YELLOW "===== MANAGER PANEL =====" RESET "\n");
        printf(PINK"1. View Reserved Tables\n"RESET);
        printf(GREEN"2. View Menu\n"RESET);
        printf(BLUE "3. Add Menu Item\n"RESET);
        printf(RED"4. Back\n"RESET);
        printf("Enter choice: ");
        scanf("%d", &option);
        clearError();

        switch (option) {
            case 1: ViewReserved(); break;
            case 2: displaymenu(); break;
            case 3: AddMenuItem(); break;
            case 4: break;
            default: printf(RED "Invalid choice!\n" RESET);
        }

    } while (option != 4);
}

void Customerpanel() {
    int option;

    do {
        printf("\n" YELLOW "===== CUSTOMER MENU =====" RESET "\n");
        printf( PINK"1.Order Food\n"RESET);
        printf(GREEN"2.Payment\n" RESET);
        printf(RED"3.Back\n"RESET);
        printf("Enter choice: ");
        scanf("%d", &option);
        clearError();

        if(option ==1) {
            Orderfood(); } 

        else if(option ==2) {
             Payment(); }

        else if(option !=3) {
             printf(RED "Invalid option\n" RESET); }

    } 
    while(option != 3);
}

int main() {
    startmenu();
    int option;
    while(1) {
        printf("\n" YELLOW"===== MAIN MENU =====" RESET "\n");
        printf(PINK"1.Customer panel\n"RESET);
        printf(GREEN"2.Manager panel\n"RESET);
        printf(RED"3.Exit\n"RESET);
        printf("Enter choice: ");
        scanf("%d",&option);
        clearError();

        if(option==1) {
            Customerpanel(); }

        else if(option==2) {
            ManagerPanel(); }

        else if(option==3) {
            break; }

        else {
            printf(RED "Invalid option.\n" RESET);
        }
    }

    return 0;
}






