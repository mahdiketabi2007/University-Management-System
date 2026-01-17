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

struct lesson_information
{
    char name[50];
    char number_of_unit[10];
    char type[50];
    char code[20];
};

struct student_information
{
    char gender[10];
    char name[50];
    char family[50];
    char code[11];
    struct date birth_date;
    char birth_city[50];
    char field_of_study[50];
    char id[50];
    char phone_number[12];
    char email[50];
    struct department_head_information *link ;
};

struct student_score
{
    char student_id[50];
    char lesson_code[50];
    char score[5];
    char date[12];
    char time[12];
    char user_name[50];
};

// ---------------------------------------------------------------------------
// files
// ---------------------------------------------------------------------------

FILE *head_file_ptr = NULL ;
FILE *staff_file_ptr = NULL ;
FILE *lesson_file_ptr = NULL ;
FILE *student_file_ptr = NULL ;
FILE *score_file_ptr = NULL ;

// ---------------------------------------------------------------------------
// other functions 
// ---------------------------------------------------------------------------

int check_string(char str[]);
int check_number(char numbr[]);
struct department_head_information head_list(char head_user_name[]);

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
void admin_observe_users();

void department_head_login();
int department_head_check_login(char user_name[] , char password[]);
void department_head_menu(struct department_head_information head);
void department_head_menu_choice(int head_choice , struct department_head_information head);
void department_head_log_lesson( struct department_head_information head);
void department_head_log_score( struct department_head_information head);

void academic_staff_login();
int academic_staff_check_login(char staff_user_name[] , char staff_password[]);
void academic_staff_menu( struct academic_staff_information staff);
void academic_staff_menu_choice(int staff_choice ,  struct academic_staff_information staff);
void academic_staff_log_student(struct academic_staff_information staff);
void academic_staff_log_score(struct academic_staff_information staff);
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
int check_string(char str[])
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

// link list of department head information
struct department_head_information head_list(char head_user_name[])
{
    struct department_head_information *s = malloc(sizeof(struct department_head_information));
    struct department_head_information *e = malloc(sizeof(struct department_head_information));
    struct department_head_information *d = NULL;
    struct department_head_information *temp = NULL;
    struct department_head_information *temp2 = NULL;

    head_file_ptr = fopen("department_head_information.txt" , "r");
    
    fscanf(head_file_ptr , "%s" , s->gender);
    fscanf(head_file_ptr , "%s" , s->name);
    fscanf(head_file_ptr , "%s" , s->family);
    fscanf(head_file_ptr , "%4s/%2s/%2s" , s->start_date.year , s->start_date.month , s->start_date.day);
    fscanf(head_file_ptr , "%s" , s->group_name);
    fscanf(head_file_ptr , "%s" , s->code);
    fscanf(head_file_ptr , "%s" , s->phone_number);
    fscanf(head_file_ptr , "%s" , s->email);
    fscanf(head_file_ptr , "%s" , s->user_name);
    fscanf(head_file_ptr , "%s" , s->password);

    fscanf(head_file_ptr , "%s" , e->gender);
    fscanf(head_file_ptr , "%s" , e->name);
    fscanf(head_file_ptr , "%s" , e->family);
    fscanf(head_file_ptr , "%4s/%2s/%2s" , e->start_date.year , e->start_date.month , e->start_date.day);
    fscanf(head_file_ptr , "%s" , e->group_name);
    fscanf(head_file_ptr , "%s" , e->code);
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
        fscanf(head_file_ptr , "%s" , d->code);
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
    while(temp != NULL)
    {
        if(!strcmp(temp->user_name , head_user_name))
        {
            return *temp;
        }
        temp = temp->link ;
    }


    // delete link list 
    temp2 = s ;
    temp = s->link ; 
    while (temp != NULL)
    {
        temp2 = NULL;
        free(temp2);
        temp2 = temp ;
        temp = temp->link;
        
    }
}

// link list of academic staff information
struct academic_staff_information staff_list(char staff_user_name[])
{
    struct academic_staff_information *s = malloc(sizeof(struct academic_staff_information));
    struct academic_staff_information *e = malloc(sizeof(struct academic_staff_information));
    struct academic_staff_information *d = NULL;
    struct academic_staff_information *temp = NULL;
    struct academic_staff_information *temp2 = NULL;

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


    // make link list of staff  information
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
    while(temp != NULL)
    {
        if(!strcmp(temp->user_name , staff_user_name))
        {
            return *temp;
        }
        temp = temp->link ;
    }


    // delete link list 
    temp2 = s ;
    temp = s->link ; 
    while (temp != NULL)
    {
        temp2 = NULL;
        free(temp2);
        temp2 = temp ;
        temp = temp->link;
        
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
           break;
        }
        case 2 :
        {
            admin_log_staff();
            break;
        }
        case 3 :
        {
            admin_observe_users();
            break;
        }
        case 4 :
        {

            break;
        }
        case 5 :
        {

            break;
        }
        case 6 :
        {

            break;
        }
        case 7 :
        {
            main_menu_choice(main_menu());
            break;
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
    while(!check_string(department_head.name))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s name : " , ch);
        gets(department_head.name);
    }

    printf("\n\t\t\t\tPlease enter %s family : " , ch);
    gets(department_head.family);
    // check family
    while(!check_string(department_head.family))
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

    printf("\n\t\t\t\tPlease enter %s code : " , ch);
    gets(department_head.code);
    // check code
    while(!check_number(department_head.code))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter day of  %s  code: " , ch);
        gets(department_head.code); 
    }

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
    fprintf(head_file_ptr , "\n%s\n" , department_head.gender);
    fprintf(head_file_ptr , "%s\n" , department_head.name);
    fprintf(head_file_ptr , "%s\n" , department_head.family);
    fprintf(head_file_ptr , "%4s/%2s/%2s\n" , department_head.start_date.year ,department_head.start_date.month , department_head.start_date.day);
    fprintf(head_file_ptr , "%s\n" , department_head.group_name);
    fprintf(head_file_ptr , "%s\n" , department_head.code);
    fprintf(head_file_ptr , "%s\n" , department_head.phone_number);
    fprintf(head_file_ptr , "%s\n" , department_head.email);
    fprintf(head_file_ptr , "%s\n" , department_head.user_name);
    fprintf(head_file_ptr , "%s" , department_head.password);
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
    while(!check_string(staff.name))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s name : " , ch);
        gets(staff.name);
    }

    printf("\n\t\t\t\tPlease enter %s family : " , ch);
    gets(staff.family);
    // check family
    while(!check_string(staff.family))
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
        printf("\n\t\t\t\tPlease enter year of  %s  start: " , ch);
        gets(staff.start_date.year); 
    }

    printf("\n\t\t\t\tPlease enter month of %s  start: " , ch);
    gets(staff.start_date.month);
    //check month
    while(check_number(staff.start_date.month) == 0 || strlen(staff.start_date.month) > 2)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter month of  %s  start: " , ch);
        gets(staff.start_date.month); 
    }

    printf("\n\t\t\t\tPlease enter day of %s  start: " , ch);
    gets(staff.start_date.day);
    //check day
    while(check_number(staff.start_date.day) == 0 || strlen(staff.start_date.day) > 2)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter day of  %s  start: " , ch);
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
    fprintf(staff_file_ptr , "\n%s\n" , staff.gender);
    fprintf(staff_file_ptr , "%s\n" , staff.name);
    fprintf(staff_file_ptr , "%s\n" , staff.family);
    fprintf(staff_file_ptr , "%4s/%2s/%2s\n" , staff.start_date.year ,staff.start_date.month , staff.start_date.day);
    fprintf(staff_file_ptr , "%s\n" , staff.rank);
    fprintf(staff_file_ptr , "%s\n" , staff.phone_number);
    fprintf(staff_file_ptr , "%s\n" , staff.email);
    fprintf(staff_file_ptr , "%s\n" , staff.user_name);
    fprintf(staff_file_ptr , "%s" , staff.password);
    fclose(staff_file_ptr);

    // return to admin page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        admin_menu();
    }
    

     
}

// observe users 
void admin_observe_users()
{
    system("cls");

    int i = 0  , j = 0;
    char enter ;
    //observe department head information

    struct department_head_information *s = malloc(sizeof(struct department_head_information)); 
    struct department_head_information *e = malloc(sizeof(struct department_head_information));  
    struct department_head_information *d = NULL;  
    struct department_head_information *temp = NULL; 
    struct department_head_information *temp2 = NULL; 

    head_file_ptr = fopen("department_head_information.txt" , "r");
    
    fscanf(head_file_ptr , "%s" , s->gender);
    fscanf(head_file_ptr , "%s" , s->name);
    fscanf(head_file_ptr , "%s" , s->family);
    fscanf(head_file_ptr , "%4s/%2s/%2s" , s->start_date.year , s->start_date.month , s->start_date.day);
    fscanf(head_file_ptr , "%s" , s->group_name);
    fscanf(head_file_ptr , "%s" , s->code);
    fscanf(head_file_ptr , "%s" , s->phone_number);
    fscanf(head_file_ptr , "%s" , s->email);
    fscanf(head_file_ptr , "%s" , s->user_name);
    fscanf(head_file_ptr , "%s" , s->password);

    fscanf(head_file_ptr , "%s" , e->gender);
    fscanf(head_file_ptr , "%s" , e->name);
    fscanf(head_file_ptr , "%s" , e->family);
    fscanf(head_file_ptr , "%4s/%2s/%2s" , e->start_date.year , e->start_date.month , e->start_date.day);
    fscanf(head_file_ptr , "%s" , e->group_name);
    fscanf(head_file_ptr , "%s" , e->code);
    fscanf(head_file_ptr , "%s" , e->phone_number);
    fscanf(head_file_ptr , "%s" , e->email);
    fscanf(head_file_ptr , "%s" , e->user_name);
    fscanf(head_file_ptr , "%s" , e->password);

    s->link = e ;
    e->link = NULL ;

    //make link list
    while(feof(head_file_ptr) == 0)
    {
        d = malloc(sizeof(struct department_head_information)); 

        fscanf(head_file_ptr , "%s" , d->gender);
        fscanf(head_file_ptr , "%s" , d->name);
        fscanf(head_file_ptr , "%s" , d->family);
        fscanf(head_file_ptr , "%4s/%2s/%2s" , d->start_date.year , d->start_date.month , d->start_date.day);
        fscanf(head_file_ptr , "%s" , d->group_name);
        fscanf(head_file_ptr , "%s" , d->code);
        fscanf(head_file_ptr , "%s" , d->phone_number);
        fscanf(head_file_ptr , "%s" , d->email);
        fscanf(head_file_ptr , "%s" , d->user_name);
        fscanf(head_file_ptr , "%s" , d->password);

        e->link = d ;
        e = d ;
    }
    e->link = NULL ;

    fclose(head_file_ptr) ;
    
    printf("\n%c" , 201);
    for(i = 0 ; i < 164 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 187);
    
    printf("%c" , 186);
    printf("%75s%s%74s" , "" , "DEPARTMENT HEAD" , "");
    printf("%c\n" , 186);

    printf("%c" , 186);
    for(i = 0 ; i < 164 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 186);

    printf("%c" , 186);
    printf("%2s%c" , "" , 179);
    printf("%-7s%c" , "GENDER" , 179);
    printf("%-12s%c" , "NAME" , 179);
    printf("%-13s%c" , "FAMILY" , 179);
    printf("%-11s%c" , "STAT DATE" , 179);
    printf("%-15s%c" , "GROUP NAME" , 179);
    printf("%-14s%c" , "CODE" , 179);
    printf("%-14s%c" , "PHONE NUMBER" , 179);
    printf("%-35s%c" , "EMAIL" , 179);
    printf("%-15s%c" , "USER NAME" , 179);
    printf("%-16s" , "PASSWORD");
    printf("%c\n" , 186);

    printf("%c" , 186);
    for(i = 0 ; i < 164 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 186);
    
    temp = s ; 
    j = 1 ;
    // print tables data
    while(temp != NULL)
    {

        printf("%c" , 186);
        printf("%-2d%c" , j++ , 179);
        printf("%-7s%c" , temp->gender , 179);
        printf("%-12s%c" , temp->name , 179);
        printf("%-13s%c" , temp->family , 179);
        printf("%4s/%2s/%2s%2c" , temp->start_date.year , temp->start_date.month , temp->start_date.month ,  179);
        printf("%-15s%c" , temp->group_name , 179);
        printf("%-14s%c" , temp->code , 179);
        printf("%-14s%c" , temp->phone_number , 179);
        printf("%-35s%c" , temp->email , 179);
        printf("%-15s%c" , temp->user_name , 179);
        printf("%-16s" , temp->password);
        printf("%c\n" , 186);

        printf("%c" , 186);
        for(i = 0 ; i < 164 ; i++)
            printf("%c" , 205);
        printf("%c\n" , 186);
        
        temp = temp->link ;
        

    }

    printf("%c" , 186);
    printf("%164s" , "");
    printf("%c\n" , 186);

    printf("%c" , 200);
    for(i = 0 ; i < 164 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 188);

    // delete link list 
    temp2 = s ;
    temp = s->link ; 
    while (temp != NULL)
    {
        temp2 = NULL;
        free(temp2);
        temp2 = temp ;
        temp = temp->link;
        
    }
    s = NULL ;
    free(s);
    e = NULL ;
    free(e);

    // observe academic staff information 

    struct academic_staff_information *s2 = malloc(sizeof(struct academic_staff_information)); 
    struct academic_staff_information *e2 = malloc(sizeof(struct academic_staff_information));  
    struct academic_staff_information *d2 = NULL;  
    struct academic_staff_information *t = NULL; 
    struct academic_staff_information *t2 = NULL; 

    staff_file_ptr = fopen("staff_information.txt" , "r");

    fscanf(staff_file_ptr , "%s" , s2->gender);
    fscanf(staff_file_ptr , "%s" , s2->name);
    fscanf(staff_file_ptr , "%s" , s2->family);
    fscanf(staff_file_ptr , "%4s/%2s/%2s" , s2->start_date.year , s2->start_date.month , s2->start_date.day);
    fscanf(staff_file_ptr , "%s" , s2->rank);
    fscanf(staff_file_ptr , "%s" , s2->phone_number);
    fscanf(staff_file_ptr , "%s" , s2->email);
    fscanf(staff_file_ptr , "%s" , s2->user_name);
    fscanf(staff_file_ptr , "%s" , s2->password);

    fscanf(staff_file_ptr , "%s" , e2->gender);
    fscanf(staff_file_ptr , "%s" , e2->name);
    fscanf(staff_file_ptr , "%s" , e2->family);
    fscanf(staff_file_ptr , "%4s/%2s/%2s" , e2->start_date.year , e2->start_date.month , e2->start_date.day);
    fscanf(staff_file_ptr , "%s" , e2->rank);
    fscanf(staff_file_ptr , "%s" , e2->phone_number);
    fscanf(staff_file_ptr , "%s" , e2->email);
    fscanf(staff_file_ptr , "%s" , e2->user_name);
    fscanf(staff_file_ptr , "%s" , e2->password);

    s2->link = e2 ;
    e2->link = NULL ;
    // make link list
    while(feof(staff_file_ptr) == 0)
    {
        d2 = malloc(sizeof(struct academic_staff_information)); 

        fscanf(staff_file_ptr , "%s" , d2->gender);
        fscanf(staff_file_ptr , "%s" , d2->name);
        fscanf(staff_file_ptr , "%s" , d2->family);
        fscanf(staff_file_ptr , "%4s/%2s/%2s" , d2->start_date.year , d2->start_date.month , d2->start_date.day);
        fscanf(staff_file_ptr , "%s" , d2->rank);
        fscanf(staff_file_ptr , "%s" , d2->phone_number);
        fscanf(staff_file_ptr , "%s" , d2->email);
        fscanf(staff_file_ptr , "%s" , d2->user_name);
        fscanf(staff_file_ptr , "%s" , d2->password);

        e2->link = d2 ;
        e2 = d2 ;
    }
    e2->link = NULL ;

    fclose(staff_file_ptr) ;
    
    printf("\n\n%c" , 201);
    for(i = 0 ; i < 164 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 187);
    
    printf("%c" , 186);
    printf("%75s%s%75s" , "" , "ACADEMIC STAFF" , "");
    printf("%c\n" , 186);

    printf("%c" , 186);
    for(i = 0 ; i < 164 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 186);

    printf("%c" , 186);
    printf("%2s%c" , "" , 179);
    printf("%-7s%c" , "GENDER" , 179);
    printf("%-17s%c" , "NAME" , 179);
    printf("%-17s%c" , "FAMILY" , 179);
    printf("%-12s%c" , "STAT DATE" , 179);
    printf("%-13s%c" , "RANK" , 179);
    printf("%-13s%c" , "PHONE NUMBER" , 179);
    printf("%-40s%c" , "EMAIL" , 179);
    printf("%-17s%c" , "USER NAME" , 179);
    printf("%-17s" , "PASSWORD");
    printf("%c\n" , 186);

    printf("%c" , 186);
    for(i = 0 ; i < 164 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 186);
    
    t = s2 ; 
    j = 1 ;
    // print second tables data
    while(t != NULL)
    {
       
        printf("%c" , 186);
        printf("%-2d%c" , j++ , 179);
        printf("%-7s%c" , t->gender , 179);
        printf("%-17s%c" , t->name , 179);
        printf("%-17s%c" , t->family , 179);
        printf("%4s/%2s/%2s%3c" , t->start_date.year , t->start_date.month , t->start_date.day , 179);
        printf("%-13s%c" , t->rank , 179);
        printf("%-13s%c" , t->phone_number , 179);
        printf("%-40s%c" , t->email , 179);
        printf("%-17s%c" , t->user_name , 179);
        printf("%-17s" , t->password);
        printf("%c\n" , 186);

        printf("%c" , 186);
        for(i = 0 ; i < 164 ; i++)
            printf("%c" , 205);
        printf("%c\n" , 186);
        
        t = t->link ;
        

    }

    printf("%c" , 186);
    printf("%164s" , "");
    printf("%c\n" , 186);

    printf("%c" , 200);
    for(i = 0 ; i < 164 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 188);

    // delete link list 
    t2 = s2 ;
    t = s2->link ; 
    while (t != NULL)
    {
        t2 = NULL;
        free(t2);
        t2 = t ;
        t = t->link;
        
    }
    s2 = NULL ;
    free(s2);
    e2 = NULL ;
    free(e2);

    // return to main menu
    printf("\033[34m""\n    Please enter to continue ....""\033[0m");
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
        
        department_head_menu(head_list(head_user_name));
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
    struct department_head_information *temp2 = NULL;

    head_file_ptr = fopen("department_head_information.txt" , "r");
    
    fscanf(head_file_ptr , "%s" , s->gender);
    fscanf(head_file_ptr , "%s" , s->name);
    fscanf(head_file_ptr , "%s" , s->family);
    fscanf(head_file_ptr , "%4s/%2s/%2s" , s->start_date.year , s->start_date.month , s->start_date.day);
    fscanf(head_file_ptr , "%s" , s->group_name);
    fscanf(head_file_ptr , "%s" , s->code);
    fscanf(head_file_ptr , "%s" , s->phone_number);
    fscanf(head_file_ptr , "%s" , s->email);
    fscanf(head_file_ptr , "%s" , s->user_name);
    fscanf(head_file_ptr , "%s" , s->password);

    fscanf(head_file_ptr , "%s" , e->gender);
    fscanf(head_file_ptr , "%s" , e->name);
    fscanf(head_file_ptr , "%s" , e->family);
    fscanf(head_file_ptr , "%4s/%2s/%2s" , e->start_date.year , e->start_date.month , e->start_date.day);
    fscanf(head_file_ptr , "%s" , e->group_name);
    fscanf(head_file_ptr , "%s" , e->code);
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
        fscanf(head_file_ptr , "%s" , d->code);
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

    // delete link list 
    temp2 = s ;
    temp = s->link ; 
    while (temp != NULL)
    {
        temp2 = NULL;
        free(temp2);
        temp2 = temp ;
        temp = temp->link;
        
    }

    if(head_found == 1)
    {
        return 1 ;
    } else 
    {
        return 0 ;
    }
    
}

//department head page menu
void department_head_menu(struct department_head_information head)
{
    int head_choice = 0 ;
    char c[100];

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

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

    department_head_menu_choice(head_choice , head);
}

// switch structure for department head choice
void department_head_menu_choice(int head_choice , struct department_head_information head)
{
    switch(head_choice)
    {

        case 1 :
        {
           department_head_log_lesson(head);
           break;
        }
        case 2 :
        {
            department_head_log_score(head);
            break;
        }
        case 3 :
        {

            break;
        }
        case 4 :
        {

            break;
        }
        case 5 :
        {

            break;
        }
        case 6 :
        {

            break;
        }
        case 7 :
        {
            main_menu_choice(main_menu());
            break;
        }

    } 
}

// log new lesson from department head
void department_head_log_lesson( struct department_head_information head)
{
    char   enter;
    struct lesson_information lesson;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|                  LOG NEW LESSON                  |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");


    printf("\n\t\t\t\tPlease enter lessons name : ");
    gets(lesson.name);
    // check name
    while(!check_string(lesson.name))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter lessons name : ");
        gets(lesson.name);
    }

    printf("\n\t\t\t\tPlease enter number of unit : ");
    gets(lesson.number_of_unit);
    // check
    while(!check_number(lesson.number_of_unit))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter number of unit : ");
        gets(lesson.number_of_unit);
    }

    printf("\n\t\t\t\tPlease enter type of this lesson(theory , parctical , experimental , workshop): ");
    gets(lesson.type);
    //check 
    while(strcmp(lesson.type , "theory") != 0 && strcmp(lesson.type , "parctical") != 0 && strcmp(lesson.type , "experimental") != 0 && strcmp(lesson.type , "workshop") != 0)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter type of this lesson(theory , parctical , experimental , workshop): ");
        gets(lesson.type);
    }

    printf("\n\t\t\t\tPlease enter lessons code : " );
    gets(lesson.code);
    //check
    while(check_number(lesson.code) == 0 )
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter lessons code : " );
        gets(lesson.code);
    }



    // print lesson information in file
    lesson_file_ptr = fopen("lessons_information.txt" , "a");
    fprintf(lesson_file_ptr , "%s\n" , lesson.name);
    fprintf(lesson_file_ptr , "%s\n" , lesson.number_of_unit);
    fprintf(lesson_file_ptr , "%s\n" , lesson.type);
    fprintf(lesson_file_ptr , "%s\n" , lesson.code);

    fclose(lesson_file_ptr);

    printf("\033[32m""\n\t\t\t\tlesson log successfully complited :)\n""\033[0m");

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }

}

// log student score
void department_head_log_score( struct department_head_information head)
{
    char   enter;
    struct student_score score;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|                    LOG SCORE                     |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");


    printf("\n\t\t\t\tPlease enter students id : ");
    gets(score.student_id);
    // check id
    while(!check_number(score.student_id))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter students id  : ");
        gets(score.student_id);
    }

    printf("\n\t\t\t\tPlease enter lessons code : ");
    gets(score.lesson_code);
    // check code
    while(!check_number(score.lesson_code))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter lessons code : ");
        gets(score.lesson_code);
    }

    printf("\n\t\t\t\tPlease enter score : ");
    gets(score.score);
    //check score
    while(!check_number(score.score))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter score : ");
        gets(score.score);
    }

    printf("\n\t\t\t\tDate : %s" , __DATE__);
    
    printf("\n\n\t\t\t\tTime : %s" , __TIME__);
    
    printf("\n\n\t\t\t\tDepartment head name : %s %s" , head.name , head.family);

    // print score information in file
    score_file_ptr = fopen("scores_information.txt" , "a");
    fprintf(score_file_ptr , "\n%s\n" , score.student_id);
    fprintf(score_file_ptr , "%s\n" , score.lesson_code);
    fprintf(score_file_ptr , "%s\n" , score.score);
    fprintf(score_file_ptr , "%s\n" , __DATE__);
    fprintf(score_file_ptr , "%s" , __TIME__);

     fclose(score_file_ptr);

    printf("\033[32m""\n\n\t\t\t\tscore log successfully complited :)\n""\033[0m");

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
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
        academic_staff_menu(staff_list(staff_user_name));
        
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
    struct academic_staff_information *temp2 = NULL;

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

    // delete link list 
    temp2 = s ;
    temp = s->link ; 
    while (temp != NULL)
    {
        temp2 = NULL;
        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    }
    

    if(staff_found == 1)
    {
        return 1 ;
    } else 
    {
        return 0 ;
    }
    
}

// academic staff page menu
void academic_staff_menu(struct academic_staff_information staff)
{
    int staff_choice = 0 ;
    char c[100];

    system("cls");

    printf("%c academic staff name :  %s %s\n" , 240 , staff.name , staff.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|                ACADEMIC STAFF PAGE               |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\t1- Log new student");
    printf("\n\t\t\t\t2- Edit students information");
    printf("\n\t\t\t\t3- Log studnts score");
    printf("\n\t\t\t\t4- Reports");
    printf("\n\t\t\t\t5- User account settings");
    printf("\n\t\t\t\t6- Exit\n");

    printf("\n\t\t\t\tPlease enter your choice : ");
    scanf("%d" , &staff_choice);
    getchar();
    // limit department head inputs 
    while(staff_choice <= 0 || staff_choice > 6)
    {
        printf("\033[31m""\n\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter your choice : ");
        scanf("%d" , &staff_choice);
        gets(c);
    }

    academic_staff_menu_choice(staff_choice , staff);
}

// switch structure for academic staff choice
void academic_staff_menu_choice(int staff_choice ,  struct academic_staff_information staff)
{
    switch(staff_choice)
    {

        case 1 :
        {
            academic_staff_log_student(staff);
            break;
        }
        case 2 :
        {
           
            break;
        }
        case 3 :
        {
            academic_staff_log_score(staff);
            break;
        }
        case 4 :
        {

            break;
        }
        case 5 :
        {

            break;
        }
        case 6 :
        {
            main_menu_choice(main_menu());
            break;
        }

    } 
}

// log new student from academic staff
void academic_staff_log_student(struct academic_staff_information staff)
{
   
    char  ch[4] , enter;
    struct student_information student;

    system("cls");

    printf("%c academic staff name :  %s %s\n" , 240 , staff.name , staff.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|                  LOG NEW STUDENT                 |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    // limit inputs for gender
    printf("\n\t\t\t\tPlease enter gender (male / female) : ");
    gets(student.gender);

    if(!strcmp(student.gender , "female"))
    {
        strcpy(ch , "her");
    } else if(!strcmp(student.gender , "male"))
    {
        strcpy(ch , "his");
    } else 
    {
        while(strcmp(student.gender , "female") != 0 && strcmp(student.gender , "male") != 0)
        {
            printf("\033[31m""\t\t\t\tERROR !""\033[0m");
            printf("\n\t\t\t\tPlease enter gender (male / female) : ");
            gets(student.gender);
        }
        if(!strcmp(student.gender , "female"))
        {
             strcpy(ch , "her");
        } else if(!strcmp(student.gender , "male"))
        {
            strcpy(ch , "his");
        }
    }

    printf("\n\t\t\t\tPlease enter %s name : " , ch);
    gets(student.name);
    // check name
    while(!check_string(student.name))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s name : " , ch);
        gets(student.name);
    }

    printf("\n\t\t\t\tPlease enter %s family : " , ch);
    gets(student.family);
    // check family
    while(!check_string(student.family))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s family : " , ch);
        gets(student.family);
    }

    printf("\n\t\t\t\tPlease enter %s fcode : " , ch);
    gets(student.code);
    // check code
    while(!check_number(student.code))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s code : " , ch);
        gets(student.code);
    }

    printf("\n\t\t\t\tPlease enter %s birth year : " , ch);
    gets(student.birth_date.year);
    //check year
    while(check_number(student.birth_date.year) == 0 || strlen(student.birth_date.year) > 4)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s birth year : " , ch);
        gets(student.birth_date.year); 
    }

    printf("\n\t\t\t\tPlease enter %s birth month : " , ch);
    gets(student.birth_date.month);
    //check month
    while(check_number(student.birth_date.month) == 0 || strlen(student.birth_date.month) > 2)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s birth month : " , ch);
        gets(student.birth_date.month); 
    }

    printf("\n\t\t\t\tPlease enter %s birth day : " , ch);
    gets(student.birth_date.day);
    //check day
    while(check_number(student.birth_date.day) == 0 || strlen(student.birth_date.day) > 2)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s birth day : " , ch);
        gets(student.birth_date.day); 
    }

    printf("\n\t\t\t\tPlease enter %s birth city : " , ch);
    gets(student.birth_city);
    //check
    while(check_string(student.birth_city) == 0)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s birth city : " , ch);
        gets(student.birth_city);
    }

    printf("\n\t\t\t\tPlease enter %s filed of study : " , ch);
    gets(student.field_of_study);
    //check
    while(check_string(student.field_of_study) == 0)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s filed of study : " , ch);
        gets(student.field_of_study);
    }

    printf("\n\t\t\t\tPlease enter %s id : " , ch);
    gets(student.id);
    //check
    while(check_number(student.id) == 0)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s id : " , ch);
        gets(student.id);
    }

    

    printf("\n\t\t\t\tPlease enter %s phone number : " , ch);
    gets(student.phone_number);
    //check phone number
    while(check_number(student.phone_number) == 0 || strlen(student.phone_number) > 11)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s phone number : " , ch);
        gets(student.phone_number); 
    }

    printf("\n\t\t\t\tPlease enter %s email : " , ch);
    gets(student.email);
    

    printf("\033[32m""\n\t\t\t\tstudent log successfully complited :)\n""\033[0m");


    // print student information in file
    student_file_ptr = fopen("student_information.txt" , "a");

    fprintf(staff_file_ptr , "\n%s\n" , student.gender);
    fprintf(staff_file_ptr , "%s\n" , student.name);
    fprintf(staff_file_ptr , "%s\n" , student.family);
    fprintf(staff_file_ptr , "%s\n" , student.code);
    fprintf(staff_file_ptr , "%4s/%1s/%1s\n" , student.birth_date.year ,student.birth_date.month , student.birth_date.day);
    fprintf(staff_file_ptr , "%s\n" , student.birth_city);
    fprintf(staff_file_ptr , "%s\n" , student.field_of_study);
    fprintf(staff_file_ptr , "%s\n" , student.id);
    fprintf(staff_file_ptr , "%s\n" , student.phone_number);
    fprintf(staff_file_ptr , "%s" , student.email);
    
    fclose(student_file_ptr);

    // return to academic staff page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        academic_staff_menu(staff);
    }
    

     
}

// log students score
void academic_staff_log_score(struct academic_staff_information staff)
{
    char   enter;
    struct student_score score;

    system("cls");

    printf("%c academid staff name :  %s %s\n" , 240 , staff.name , staff.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|                    LOG SCORE                     |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");


    printf("\n\t\t\t\tPlease enter students id : ");
    gets(score.student_id);
    // check id
    while(!check_number(score.student_id))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter students id  : ");
        gets(score.student_id);
    }

    printf("\n\t\t\t\tPlease enter lessons code : ");
    gets(score.lesson_code);
    // check code
    while(!check_number(score.lesson_code))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter lessons code : ");
        gets(score.lesson_code);
    }

    printf("\n\t\t\t\tPlease enter score : ");
    gets(score.score);
    //check score
    while(!check_number(score.score))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter score : ");
        gets(score.score);
    }

    printf("\n\t\t\t\tDate : %s" , __DATE__);
    
    printf("\n\n\t\t\t\tTime : %s" , __TIME__);
    
    printf("\n\n\t\t\t\tAcademic staff name : %s %s" , staff.name , staff.family);

    // print score information in file
    score_file_ptr = fopen("scores_information.txt" , "a");
    fprintf(score_file_ptr , "\n%s\n" , score.student_id);
    fprintf(score_file_ptr , "%s\n" , score.lesson_code);
    fprintf(score_file_ptr , "%s\n" , score.score);
    fprintf(score_file_ptr , "%s\n" , __DATE__);
    fprintf(score_file_ptr , "%s" , __TIME__);

     fclose(score_file_ptr);

    printf("\033[32m""\n\n\t\t\t\tscore log successfully complited :)\n""\033[0m");

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        academic_staff_menu(staff);
    }

}





