#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

//--------------------- admin username = admin |   admin password = 1212 ---------------------

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
void main_menu_choice(int choice);
void admin_login();
void admin_menu();
void department_head_login();
void academic_staff_login();
// ---------------------------------------------------------------------------
// main function
// ---------------------------------------------------------------------------
void main()
{
    main_menu_choice(main_menu());
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

void main_menu_choice(int choice)
{
    switch(choice)
    {
        case 1 :
        {
            admin_login();
            break;
        }
        case 2 :
        {
            //department_head_login();
            break;
        }
        case 3 :
        {
            //academic_staff_login();
            break;
        }
        case 4 :
        {
            printf("\033[34m""\n\t\t\t\tCome back soon :)""\033[0m");
            break;
        }
    }
}

void admin_login()
{
    int choice = 0 , user_found = 0;
    char enter , admin_user_name[50] , admin_password[50];

    system("cls");

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|                    ADMIN LOGIN                   |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter your user name : ");
    gets(admin_user_name);
    printf("\n\t\t\t\tPlease enter your password : ");
    gets(admin_password);
    if(!strcmp(admin_user_name , "admin"))
    {
        if(!strcmp(admin_password , "1212"))
        {
            printf("\033[32m""\n\t\t\t\tWelcome to admin page :)""\033[0m");
            user_found = 1 ;
            
        } 
        
    } 
    
    if(user_found == 1)
    {
        //admin_menu();
    } else 
    {
        printf("\033[31m""\n\t\t\t\tERROR! incorrect user name or password.\n""\033[0m");
        printf("\033[34m""\n\t\t\t\tPlease enter to continue ....""\033[0m");
        enter = getchar();
        if(enter == '\n')
        {
             main_menu_choice(main_menu());
        }
    }
    
    
}