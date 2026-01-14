#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

// ---------------------------------------------------------------------------
// structs and variables 
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// files
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// protoype functions
// ---------------------------------------------------------------------------
int main_menu();
void choice(int choice);
int admin_menu();
int department_head_menu();
int academic_staff_menu();
// ---------------------------------------------------------------------------
// main function
// ---------------------------------------------------------------------------
void main()
{
    choice(main_menu());
}
// ---------------------------------------------------------------------------
// functions 
// ---------------------------------------------------------------------------
int main_menu()
{
    int choice = 0 ;
    char c[100] ;

    system("cls");

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|     WELCOME TO MY STUDNT INFORMATION SYSTEM      |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\t1- Admin Login");
    printf("\n\t\t\t\t2- Department Head Login");
    printf("\n\t\t\t\t3- Academic Staff Login");
    printf("\n\t\t\t\t4- Exit\n");

    printf("\n\t\t\t\tPlease enter your choice : ");
    scanf("%d" , &choice);
    getchar();
    while(choice <= 0 || choice > 4)
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter your choice : ");
        scanf("%d" , &choice);
        gets(c);
    }

    return choice ;
}

void choice(int choice)
{
    switch(choice)
    {
        case 1 :
        {
            //admin_menu();
            break;
        }
        case 2 :
        {
            //department_head_menu();
            break;
        }
        case 3 :
        {
            //academic_staff_menu();
            break;
        }
        case 4 :
        {
            printf("\033[34m""\n\t\t\t\tCome back soon :)""\033[0m");
            break;
        }
    }
}