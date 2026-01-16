#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

//--------------------- admin username = admin |   admin password = 1212 ---------------------

// ---------------------------------------------------------------------------
// structs and variables 
// ---------------------------------------------------------------------------
struct date
{
    char year[5];
    char month[3];
    char day[3];
};

struct department_head_information 
{
    char gender[10];
    char name[50];
    char family[50];
    struct date start_date;
    char group_name[50];
    char code[11];
    char phone_number[12];
    char email[50];
    char user_name[50];
    char password[50];
    struct department_head_information *link ;
};

struct academic_staff_information
{
    char gender[10];
    char name[50];
    char family[50];
    struct date start_date;
    char rank[10];
    char phone_number[12];
    char email[50];
    char user_name[50];
    char password[50];
    struct academic_staff_information *link ;
};
// ---------------------------------------------------------------------------
// files
// ---------------------------------------------------------------------------

FILE *head_file_ptr = NULL ;
FILE *staff_file_ptr = NULL ;
// ---------------------------------------------------------------------------

// other functions 
// ---------------------------------------------------------------------------

int check_name(char str[]);
int check_number(char numbr[]);


// ---------------------------------------------------------------------------
// protoype functions
// ---------------------------------------------------------------------------

int main_menu();
void main_menu_choice(int choice);

void admin_login();
void admin_menu();
void admin_menu_choice(int admin_choice);
void admin_log_head();
void admin_log_staff();

void department_head_login();
int department_head_check_login(char user_name[] , char password[]);
void department_head_menu();
void department_head_menu_choice(int head_choice);

void academic_staff_login();
int academic_staff_check_login(char staff_user_name[] , char staff_password[]);
// ---------------------------------------------------------------------------
// main function
// ---------------------------------------------------------------------------

void main()
{
    main_menu_choice(main_menu());
    
}

// ---------------------------------------------------------------------------
// other functions 
// ---------------------------------------------------------------------------

// check name family
int check_name(char str[])
{
    int len = 0 , correct_name = 1 , i = 0;
    len = strlen(str);
    for(i = 0 ; i < len ; i++)
    {
        if(isalpha(str[i]) == 1 || isalpha(str[i]) == 2)
        {
            continue;
        } else 
        {
            correct_name = 0 ; 
            break ;
        }
    }
    if(correct_name == 1)
    {
        return 1 ;
    } else 
    {
        return 0 ;
    }

}

// check numbers
int check_number(char number[])
{
    int len = 0 , correct_number = 1 , i = 0;
    len = strlen(number);
    for(i = 0 ; i < len ; i++)
    {
        if(isdigit(number[i]) == 1)
        {
            continue;
        } else 
        {
            correct_number = 0 ; 
            break ;
        }
    }
    if(correct_number == 1)
    {
        return 1 ;
    } else 
    {
        return 0 ;
    }
}


// ---------------------------------------------------------------------------
// functions 
// ---------------------------------------------------------------------------

// function for diasplay main menu
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
    // limit user inputs
    while(choice <= 0 || choice > 4)
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter your choice : ");
        scanf("%d" , &choice);
        gets(c);
    }

    return choice ;
}

// switch structure for user choice
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
            department_head_login();
            break;
        }
        case 3 :
        {
            academic_staff_login();
            break;
        }
        case 4 :
        {
            printf("\033[34m""\n\t\t\t\tCome back soon :)""\033[0m");
            break;
        }
    }
}

// login page for admin 
void admin_login()
{
    int  admin_found = 0;
    char enter , admin_user_name[50] , admin_password[50];

    system("cls");

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|                    ADMIN LOGIN                   |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter your user name : ");
    gets(admin_user_name);
    while(strcmp(admin_user_name , "") == 0)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter your user name : ");
        gets(admin_user_name);
    }

    printf("\n\t\t\t\tPlease enter your password : ");
    gets(admin_password);
    while(strcmp(admin_user_name , "") == 0)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter your user name : ");
        gets(admin_user_name);
    }

    if(!strcmp(admin_user_name , "admin"))
    {
        if(!strcmp(admin_password , "1212"))
        {
            printf("\033[32m""\n\t\t\t\tWelcome to admin page :)""\033[0m");
            admin_found = 1 ;
            
        } 
        
    } 
    
    if(admin_found == 1)
    {
        admin_menu();
    } else 
    {
        printf("\033[31m""\n\t\t\t\tERROR! incorrect user name or password.\n""\033[0m");
        // return to main menu
        printf("\033[34m""\n\t\t\t\tPlease enter to continue ....""\033[0m");
        enter = getchar();
        if(enter == '\n')
        {
             main_menu_choice(main_menu());
        }
    }
    
    
}

// admin page
void admin_menu()
{
    int admin_choice = 0 ;
    char c[100];

    system("cls");

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|                    ADMIN PAGE                    |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\t1- Log new Department Head");
    printf("\n\t\t\t\t2- Log new academic staff");
    printf("\n\t\t\t\t3- Observe users list as type");
    printf("\n\t\t\t\t4- Delete user from system");
    printf("\n\t\t\t\t5- Reports");
    printf("\n\t\t\t\t6- Backup files");
    printf("\n\t\t\t\t7- Exit\n");

    printf("\n\t\t\t\tPlease enter your choice : ");
    scanf("%d" , &admin_choice);
    getchar();
    // limit admin inputs 
    while(admin_choice <= 0 || admin_choice > 7)
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter your choice : ");
        scanf("%d" , &admin_choice);
        gets(c);
    }

    admin_menu_choice(admin_choice);
}

// switch structure for admin choice
void admin_menu_choice(int admin_choice)
{
    switch(admin_choice)
    {

        case 1 :
        {
           admin_log_head(); 
        }
        case 2 :
        {
            admin_log_staff();
        }
        case 3 :
        {

        }
        case 4 :
        {

        }
        case 5 :
        {

        }
        case 6 :
        {

        }
        case 7 :
        {
            main_menu_choice(main_menu());
        }

    } 
}

// log new department head
void admin_log_head()
{
   
    char  ch[4] , confirm_password[50] , enter;
    struct department_head_information department_head;

    system("cls");

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|              LOG NEW DEPARTMENT HEAD             |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    // limit inputs for gender
    printf("\n\t\t\t\tPlease enter gender (male / female) : ");
    gets(department_head.gender);

    if(!strcmp(department_head.gender , "female"))
    {
        strcpy(ch , "her");
    } else if(!strcmp(department_head.gender , "male"))
    {
        strcpy(ch , "his");
    } else 
    {
        while(strcmp(department_head.gender , "female") != 0 && strcmp(department_head.gender , "male") != 0)
        {
            printf("\033[31m""\t\t\t\tERROR !""\033[0m");
            printf("\n\t\t\t\tPlease enter gender (male / female) : ");
            gets(department_head.gender);
        }
        if(!strcmp(department_head.gender , "female"))
        {
             strcpy(ch , "her");
        } else if(!strcmp(department_head.gender , "male"))
        {
            strcpy(ch , "his");
        }
    }

    printf("\n\t\t\t\tPlease enter %s name : " , ch);
    gets(department_head.name);
    // check name
    while(!check_name(department_head.name))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s name : " , ch);
        gets(department_head.name);
    }

    printf("\n\t\t\t\tPlease enter %s family : " , ch);
    gets(department_head.family);
    // check family
    while(!check_name(department_head.family))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s family : " , ch);
        gets(department_head.family);
    }

    printf("\n\t\t\t\tPlease enter year of %s  start: " , ch);
    gets(department_head.start_date.year);
    //check year
    while(check_number(department_head.start_date.year) == 0 || strlen(department_head.start_date.year) > 4)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter year of  %s  srtart: " , ch);
        gets(department_head.start_date.year); 
    }

    printf("\n\t\t\t\tPlease enter month of %s  start: " , ch);
    gets(department_head.start_date.month);
    //check month
    while(check_number(department_head.start_date.month) == 0 || strlen(department_head.start_date.month) > 2)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter month of  %s  srtart: " , ch);
        gets(department_head.start_date.month); 
    }

    printf("\n\t\t\t\tPlease enter day of %s  atart: " , ch);
    gets(department_head.start_date.day);
    //check day
    while(check_number(department_head.start_date.day) == 0 || strlen(department_head.start_date.day) > 2)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter day of  %s  srtart: " , ch);
        gets(department_head.start_date.day); 
    }

    printf("\n\t\t\t\tPlease enter %s group name : " , ch);
    gets(department_head.group_name);

    printf("\n\t\t\t\tPlease enter %s phone number : " , ch);
    gets(department_head.phone_number);
    //check phone number
    while(check_number(department_head.phone_number) == 0 || strlen(department_head.phone_number) > 11)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s phone number : " , ch);
        gets(department_head.phone_number); 
    }

    printf("\n\t\t\t\tPlease enter %s email : " , ch);
    gets(department_head.email);
    printf("\n\t\t\t\tPlease enter %s user name : " , ch);
    gets(department_head.user_name);
    printf("\n\t\t\t\tPlease enter %s password : " , ch);
    gets(department_head.password);
    printf("\n\t\t\t\tPlease confirm %s password : " , ch);
    gets(confirm_password);

    // check passwords matching
    if(!strcmp(department_head.password , confirm_password))
    {
        printf("\033[32m""\n\t\t\t\tDepartment head registation successfully complited :)\n""\033[0m");
        printf("\033[34m""\n\t\t\t\t%s user name = %s""\033[0m", ch , department_head.user_name);
        printf("\033[34m""\n\t\t\t\t%s password = %s""\033[0m" , ch , department_head.password);
    } else 
    {
        printf("\033[31m""\n\t\t\t\tERROR! passwors not matched.\n""\033[0m");
    }


    // print head department information in file
    head_file_ptr = fopen("department_head_information.txt" , "a");
    fprintf(head_file_ptr , "%s\n" , department_head.gender);
    fprintf(head_file_ptr , "%s\n" , department_head.name);
    fprintf(head_file_ptr , "%s\n" , department_head.family);
    fprintf(head_file_ptr , "%4s/%1s/%1s\n" , department_head.start_date.year ,department_head.start_date.month , department_head.start_date.day);
    fprintf(head_file_ptr , "%s\n" , department_head.group_name);
    fprintf(head_file_ptr , "%s\n" , department_head.phone_number);
    fprintf(head_file_ptr , "%s\n" , department_head.email);
    fprintf(head_file_ptr , "%s\n" , department_head.user_name);
    fprintf(head_file_ptr , "%s\n" , department_head.password);
    fclose(head_file_ptr);

    // return to admin page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        admin_menu();
    }
    

     
}

// log new department head
void admin_log_staff()
{
   
    char  ch[4] , confirm_password[50] , enter;
    struct academic_staff_information staff;

    system("cls");

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|              LOG NEW ACADEMIC STAFF              |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    // limit inputs for gender
    printf("\n\t\t\t\tPlease enter gender (male / female) : ");
    gets(staff.gender);
    if(!strcmp(staff.gender , "female"))
    {
        strcpy(ch , "her");
    } else if(!strcmp(staff.gender , "male"))
    {
        strcpy(ch , "his");
    } else 
    {
        while(strcmp(staff.gender , "female") != 0 && strcmp(staff.gender , "male") != 0)
        {
            printf("\033[31m""\t\t\t\tERROR !""\033[0m");
            printf("\n\t\t\t\tPlease enter gender (male / female) : ");
            gets(staff.gender);
        }
        if(!strcmp(staff.gender , "female"))
        {
             strcpy(ch , "her");
        } else if(!strcmp(staff.gender , "male"))
        {
            strcpy(ch , "his");
        }
    }

    printf("\n\t\t\t\tPlease enter %s name : " , ch);
    gets(staff.name);
    // check name
    while(!check_name(staff.name))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s name : " , ch);
        gets(staff.name);
    }

    printf("\n\t\t\t\tPlease enter %s family : " , ch);
    gets(staff.family);
    // check family
    while(!check_name(staff.family))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s family : " , ch);
        gets(staff.family);
    }

    printf("\n\t\t\t\tPlease enter year of %s  start: " , ch);
    gets(staff.start_date.year);
    //check year
    while(check_number(staff.start_date.year) == 0 || strlen(staff.start_date.year) > 4)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter year of  %s  srtart: " , ch);
        gets(staff.start_date.year); 
    }

    printf("\n\t\t\t\tPlease enter month of %s  start: " , ch);
    gets(staff.start_date.month);
    //check month
    while(check_number(staff.start_date.month) == 0 || strlen(staff.start_date.month) > 2)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter month of  %s  srtart: " , ch);
        gets(staff.start_date.month); 
    }

    printf("\n\t\t\t\tPlease enter day of %s  atart: " , ch);
    gets(staff.start_date.day);
    //check day
    while(check_number(staff.start_date.day) == 0 || strlen(staff.start_date.day) > 2)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter day of  %s  srtart: " , ch);
        gets(staff.start_date.day); 
    }

    printf("\n\t\t\t\tPlease enter %s rank : " , ch);
    gets(staff.rank);

    printf("\n\t\t\t\tPlease enter %s phone number : " , ch);
    gets(staff.phone_number);
    //check phone number
    while(check_number(staff.phone_number) == 0 || strlen(staff.phone_number) > 11)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s phone number : " , ch);
        gets(staff.phone_number); 
    }

    printf("\n\t\t\t\tPlease enter %s email : " , ch);
    gets(staff.email);
    printf("\n\t\t\t\tPlease enter %s user name : " , ch);
    gets(staff.user_name);
    printf("\n\t\t\t\tPlease enter %s password : " , ch);
    gets(staff.password);
    printf("\n\t\t\t\tPlease confirm %s password : " , ch);
    gets(confirm_password);

    // check passwords matching
    if(!strcmp(staff.password , confirm_password))
    {
        printf("\033[32m""\n\t\t\t\tDepartment head registation successfully complited :)\n""\033[0m");
        printf("\033[34m""\n\t\t\t\t%s user name = %s""\033[0m", ch , staff.user_name);
        printf("\033[34m""\n\t\t\t\t%s password = %s""\033[0m" , ch , staff.password);
    } else 
    {
        printf("\033[31m""\n\t\t\t\tERROR! passwors not matched.\n""\033[0m");
    }


    // print head department information in file
    staff_file_ptr = fopen("staff_information.txt" , "a");
    fprintf(staff_file_ptr , "%s\n" , staff.gender);
    fprintf(staff_file_ptr , "%s\n" , staff.name);
    fprintf(staff_file_ptr , "%s\n" , staff.family);
    fprintf(staff_file_ptr , "%4s/%2s/%2s\n" , staff.start_date.year ,staff.start_date.month , staff.start_date.day);
    fprintf(staff_file_ptr , "%s\n" , staff.phone_number);
    fprintf(staff_file_ptr , "%s\n" , staff.email);
    fprintf(staff_file_ptr , "%s\n" , staff.user_name);
    fprintf(staff_file_ptr , "%s\n" , staff.password);
    fclose(staff_file_ptr);

    // return to admin page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        admin_menu();
    }
    

     
}

// login page for department head 
void department_head_login()
{
    int  head_found = 0;
    char enter , head_user_name[50] , head_password[50];

    system("cls");

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|               DEPARTMENT HEAD LOGIN              |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter your user name : ");
    gets(head_user_name);
    while(strcmp(head_user_name , "") == 0)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter your user name : ");
        gets(head_user_name);
    }

    printf("\n\t\t\t\tPlease enter your password : ");
    gets(head_password);
    while(strcmp(head_user_name , "") == 0)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter your user name : ");
        gets(head_user_name);
    }
    
    head_found = department_head_check_login(head_user_name , head_password);
    
    if(head_found == 1)
    {
        department_head_menu();
    } else 
    {
        printf("\033[31m""\n\t\t\t\tERROR! incorrect user name or password.\n""\033[0m");
        // return to main menu
        printf("\033[34m""\n\t\t\t\tPlease enter to continue ....""\033[0m");
        enter = getchar();
        if(enter == '\n')
        {
             main_menu_choice(main_menu());
        }
    }
    
    
}

// make link  list  of department head information and check it fo login
int department_head_check_login(char head_user_name[] , char head_password[])
{
    int head_found = 0 ;

    struct department_head_information *s = malloc(sizeof(struct department_head_information));
    struct department_head_information *e = malloc(sizeof(struct department_head_information));
    struct department_head_information *d = NULL;
    struct department_head_information *temp = NULL;

    head_file_ptr = fopen("department_head_information.txt" , "r");
    
    fscanf(head_file_ptr , "%s" , s->gender);
    fscanf(head_file_ptr , "%s" , s->name);
    fscanf(head_file_ptr , "%s" , s->family);
    fscanf(head_file_ptr , "%4s/%2s/%2s" , s->start_date.year , s->start_date.month , s->start_date.day);
    fscanf(head_file_ptr , "%s" , s->group_name);
    fscanf(head_file_ptr , "%s" , s->phone_number);
    fscanf(head_file_ptr , "%s" , s->email);
    fscanf(head_file_ptr , "%s" , s->user_name);
    fscanf(head_file_ptr , "%s" , s->password);

    fscanf(head_file_ptr , "%s" , e->gender);
    fscanf(head_file_ptr , "%s" , e->name);
    fscanf(head_file_ptr , "%s" , e->family);
    fscanf(head_file_ptr , "%4s/%2s/%2s" , e->start_date.year , e->start_date.month , e->start_date.day);
    fscanf(head_file_ptr , "%s" , e->group_name);
    fscanf(head_file_ptr , "%s" , e->phone_number);
    fscanf(head_file_ptr , "%s" , e->email);
    fscanf(head_file_ptr , "%s" , e->user_name);
    fscanf(head_file_ptr , "%s" , e->password);

    s->link = e ;
    e->link = NULL; 
    // make link list of head department information
    while(feof(head_file_ptr) == 0)
    {
        d = malloc(sizeof(struct department_head_information));

        fscanf(head_file_ptr , "%s" , d->gender);
        fscanf(head_file_ptr , "%s" , d->name);
        fscanf(head_file_ptr , "%s" , d->family);
        fscanf(head_file_ptr , "%4s/%2s/%2s" , d->start_date.year , d->start_date.month , d->start_date.day);
        fscanf(head_file_ptr , "%s" , d->group_name);
        fscanf(head_file_ptr , "%s" , d->phone_number);
        fscanf(head_file_ptr , "%s" , d->email);
        fscanf(head_file_ptr , "%s" , d->user_name);
        fscanf(head_file_ptr , "%s" , d->password);

        e->link = d ;
        e = d ;
    }
    e->link = NULL ;

    fclose(head_file_ptr);

    temp = s ;
    // search user name and password
    while(temp != NULL)
    {
        if(!strcmp(temp->user_name , head_user_name))
        {
            if(!strcmp(temp->password , head_password))
            {
                head_found = 1 ;
                break;
            }
        }
        temp = temp->link ;
    }

    if(head_found == 1)
    {
        return 1 ;
    } else 
    {
        return 0 ;
    }
    
}

//department head page
void department_head_menu()
{
    int head_choice = 0 ;
    char c[100];

    system("cls");

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|               DEPARTMENT HEAD PAGE               |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\t1- Log new lesson");
    printf("\n\t\t\t\t2- Log students score");
    printf("\n\t\t\t\t3- Edit students score");
    printf("\n\t\t\t\t4- Delete old lesson information");
    printf("\n\t\t\t\t5- Reports");
    printf("\n\t\t\t\t6- User account settings");
    printf("\n\t\t\t\t7- Exit\n");

    printf("\n\t\t\t\tPlease enter your choice : ");
    scanf("%d" , &head_choice);
    getchar();
    // limit department head inputs 
    while(head_choice <= 0 || head_choice > 7)
    {
        printf("\033[31m""\n\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter your choice : ");
        scanf("%d" , &head_choice);
        gets(c);
    }

    department_head_menu_choice(head_choice);
}

// switch structure for department head choice
void department_head_menu_choice(int head_choice)
{
    switch(head_choice)
    {

        case 1 :
        {
           
        }
        case 2 :
        {
            
        }
        case 3 :
        {

        }
        case 4 :
        {

        }
        case 5 :
        {

        }
        case 6 :
        {

        }
        case 7 :
        {
            main_menu_choice(main_menu());
        }

    } 
}

// login page for academic staff
void academic_staff_login()
{
    int  staff_found = 0;
    char enter , staff_user_name[50] , staff_password[50];

    system("cls");

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|               ACADEMIC STAFF LOGIN               |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter your user name : ");
    gets(staff_user_name);
    while(strcmp(staff_user_name , "") == 0)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter your user name : ");
        gets(staff_user_name);
    }

    printf("\n\t\t\t\tPlease enter your password : ");
    gets(staff_password);
    while(strcmp(staff_password , "") == 0)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter your password : ");
        gets(staff_user_name);
    }
    
    staff_found = academic_staff_check_login(staff_user_name , staff_password);
    
    if(staff_found == 1)
    {
        //academic_staff_menu();
        printf("!!!!");
    } else 
    {
        printf("\033[31m""\n\t\t\t\tERROR! incorrect user name or password.\n""\033[0m");
        // return to main menu
        printf("\033[34m""\n\t\t\t\tPlease enter to continue ....""\033[0m");
        enter = getchar();
        if(enter == '\n')
        {
             main_menu_choice(main_menu());
        }
    }
    
}

// make link  list  of academic staff information and check it fo login
int academic_staff_check_login(char staff_user_name[] , char staff_password[])
{
    int staff_found = 0 ;

    struct academic_staff_information *s = malloc(sizeof(struct academic_staff_information));
    struct academic_staff_information *e = malloc(sizeof(struct academic_staff_information));
    struct academic_staff_information *d = NULL;
    struct academic_staff_information *temp = NULL;

    staff_file_ptr = fopen("staff_information.txt" , "r");
    
    fscanf(staff_file_ptr , "%s" , s->gender);
    fscanf(staff_file_ptr , "%s" , s->name);
    fscanf(staff_file_ptr , "%s" , s->family);
    fscanf(staff_file_ptr , "%4s/%2s/%2s" , s->start_date.year , s->start_date.month , s->start_date.day);
    fscanf(staff_file_ptr , "%s" , s->rank);
    fscanf(staff_file_ptr , "%s" , s->phone_number);
    fscanf(staff_file_ptr , "%s" , s->email);
    fscanf(staff_file_ptr , "%s" , s->user_name);
    fscanf(staff_file_ptr , "%s" , s->password);

    fscanf(staff_file_ptr , "%s" , e->gender);
    fscanf(staff_file_ptr , "%s" , e->name);
    fscanf(staff_file_ptr , "%s" , e->family);
    fscanf(staff_file_ptr , "%4s/%2s/%2s" , e->start_date.year , e->start_date.month , e->start_date.day);
    fscanf(staff_file_ptr , "%s" , e->rank);
    fscanf(staff_file_ptr , "%s" , e->phone_number);
    fscanf(staff_file_ptr , "%s" , e->email);
    fscanf(staff_file_ptr , "%s" , e->user_name);
    fscanf(staff_file_ptr , "%s" , e->password);

    s->link = e ;
    e->link = NULL; 
    // make link list of staff department information
    while(feof(staff_file_ptr) == 0)
    {
        d = malloc(sizeof(struct academic_staff_information));

        fscanf(staff_file_ptr , "%s" , d->gender);
        fscanf(staff_file_ptr , "%s" , d->name);
        fscanf(staff_file_ptr , "%s" , d->family);
        fscanf(staff_file_ptr , "%4s/%2s/%2s" , d->start_date.year , d->start_date.month , d->start_date.day);
        fscanf(staff_file_ptr , "%s" , d->rank);
        fscanf(staff_file_ptr , "%s" , d->phone_number);
        fscanf(staff_file_ptr , "%s" , d->email);
        fscanf(staff_file_ptr , "%s" , d->user_name);
        fscanf(staff_file_ptr , "%s" , d->password);

        e->link = d ;
        e = d ;
    }
    e->link = NULL ;

    fclose(staff_file_ptr);

    temp = s ;
    // search user name and password
    while(temp != NULL)
    {
        if(!strcmp(temp->user_name , staff_user_name))
        {
            if(!strcmp(temp->password , staff_password))
            {
                staff_found = 1 ;
                break;
            }
        }
        temp = temp->link ;
    }

    if(staff_found == 1)
    {
        return 1 ;
    } else 
    {
        return 0 ;
    }
    
}