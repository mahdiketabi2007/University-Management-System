#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<conio.h>
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
    char status[50] ;
    struct date terminate_date;
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
    char status[50] ;
    struct date terminate_date;
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
    char status[20];
    struct lesson_information *link;
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
    struct student_information *link ;
};

struct student_score
{
    char student_id[50];
    char lesson_code[50];
    char score[5];
    char date[50];
    char time[50];
    char user_name[50];
    struct student_score *link ;
};

// ---------------------------------------------------------------------------
// files
// ---------------------------------------------------------------------------

FILE *head_file_ptr = NULL ;
FILE *staff_file_ptr = NULL ;
FILE *lesson_file_ptr = NULL ;
FILE *student_file_ptr = NULL ;
FILE *score_file_ptr = NULL ;
FILE *terminate_head_file_ptr = NULL ;
FILE *terminate_staff_file_ptr = NULL ;
FILE *deleted_lesson_file_ptr = NULL ;

FILE *backup_head_file_ptr = NULL ;
FILE *backup_staff_file_ptr = NULL ;
FILE *backup_lesson_file_ptr = NULL ;
FILE *backup_student_file_ptr = NULL ;
FILE *backup_score_file_ptr = NULL ;
// ---------------------------------------------------------------------------
// protoype other functions
// ---------------------------------------------------------------------------

int check_string(char str[]);
int check_number(char numbr[]);
int check_email(char email[]);
struct department_head_information head_list(char head_user_name[]);
struct academic_staff_information staff_list(char staff_user_name[]);
struct student_information student_list(char student_name[] , char student_family[]  , char student_id[]);
struct lesson_information lesson_list(char lesson_code[]);
void date(char date[]);
char* star_password();
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
void admin_observe_department_head_list(char type[]);
void admin_observe_academic_staff_list(char type[]);
void admin_observe_terminated_users_list();
void admin_delete_users_menu();
void admin_delete_head_page();
void admin_delete_head(char head_name[] , char head_family[] ,char terminate_date[]);
void admin_delete_staff_page();
void admin_delete_staff(char hstaff_name[] , char staff_family[] ,char terminate_date[]);
void admin_delete_users_menu_choice(int admin_choice);
void admin_backup_menu();
void admin_backup_menu_choice( int admin_choice);
void admin_backup(int n);
void admin_reports_page();
void admin_reports_menu_choice(int admin_choice);

void department_head_login();
int department_head_check_login(char user_name[] , char password[]);
void department_head_menu(struct department_head_information head);
void department_head_menu_choice(int head_choice , struct department_head_information head);
void department_head_log_lesson( struct department_head_information head);
void department_head_log_score( struct department_head_information head);
void department_head_edit_score_page(struct department_head_information head);
void department_head_edit_score_list(char student_id[] , char lesson_code[] , char score[]);
void department_head_edit_lesson(struct department_head_information head);
void department_head_edit_lessons_list(char lesson_code[] , char type[] , char new[]);
void department_head_edit_lesson_menu_choice(int head_choice , struct department_head_information head);
void department_head_edit_lessons_name_page(struct department_head_information head);
void department_head_edit_lessons_number_of_unit_page(struct department_head_information head);
void department_head_edit_lessons_type_page(struct department_head_information head);
void department_head_delete_lesson_page(struct department_head_information head);
void department_head_delete_lesson_list(char lesson_code[]);
void department_head_reports_page(struct department_head_information head);
void department_head_reports_menu_choice(int head_choice , struct department_head_information head);
void department_head_find_student_page(struct department_head_information head);
void department_head_find_student_menu_choice(int head_choice , struct department_head_information head);
void department_head_find_student_name_page(struct department_head_information head);
void department_head_find_student_id_page(struct department_head_information head);
void department_head_student_list(struct department_head_information head);
void department_head_lesson_list(struct department_head_information head ,  char type[]);
void department_head_student_scores_page(struct department_head_information head);
void department_head_students_scores_list(char student_id[] , char lesson_code[] , char type[]);
void department_head_students_scores_page(struct department_head_information head);
void department_head_sorted_students_scores_page(struct department_head_information head);
void department_head_student_average_page(struct department_head_information head);
float department_head_student_average(char student_id[]);
void department_head_lesson_average_page(struct department_head_information head);
float department_head_lesson_average(char lesson_code[]);
void department_head_students_average_list(struct department_head_information head , char type[]);
void department_head_passed_students_page(struct department_head_information head);
void department_head_failed_students_page(struct department_head_information head);
void department_head_conditional_students_list_take_lesson_page(struct department_head_information head);
void department_head_conditional_students_list_take_lesson(char lesson_code[]);
void department_head_setting_page(struct department_head_information head);
void department_head_setting_menu_choice(int head_choice , struct department_head_information head);
void department_head_setting(struct department_head_information head , char type[] , char new[]);
void department_head_setting_password_page(struct department_head_information head);
void department_head_setting_email_page(struct department_head_information head);
void department_head_setting_phone_number_page(struct department_head_information head);

void academic_staff_login();
int academic_staff_check_login(char staff_user_name[] , char staff_password[]);
void academic_staff_menu( struct academic_staff_information staff);
void academic_staff_menu_choice(int staff_choice ,  struct academic_staff_information staff);
void academic_staff_log_student(struct academic_staff_information staff);
void academic_staff_log_score(struct academic_staff_information staff);
void academic_staff_edit_students_information(struct academic_staff_information staff);
void academic_staff_edit_students_information_menu_choice(int staff_choice , struct academic_staff_information staff);
void academic_staff_edit_students_gender_page(struct academic_staff_information staff);
void academic_staff_edit_students_name_page(struct academic_staff_information staff);
void academic_staff_edit_students_family_page(struct academic_staff_information staff);
void academic_staff_edit_students_code_page(struct academic_staff_information staff);
void academic_staff_edit_students_birth_date_page(struct academic_staff_information staff);
void academic_staff_edit_students_birth_city_page(struct academic_staff_information staff);
void academic_staff_edit_students_field_of_study_page(struct academic_staff_information staff);
void academic_staff_edit_students_phone_number_page(struct academic_staff_information staff);
void academic_staff_edit_students_email_page(struct academic_staff_information staff);
void academic_staff_edit_students_information_list(char students_id[] , char type[] , char new[]);
void academic_staff_setting_page(struct academic_staff_information staff);
void academic_staff_setting_menu_choice(int staff_choice , struct academic_staff_information staff);
void academic_staff_setting_password_page(struct academic_staff_information staff);
void academic_staff_setting_email_page(struct academic_staff_information staff);
void academic_staff_setting_phone_number_page(struct academic_staff_information staff);
void academic_staff_setting(struct academic_staff_information head , char type[] , char new[]);

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

// check strings
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

// check emails
int check_email(char email[])
{
    int dot = 0 , at = 0 , len , i = 0 ; 

    len = strlen(email);

    if(len < 10)
    {
        return 0 ;
    }

    for(i = 0 ; i < len ; i++)
    {
        if(email[i] == '@')
        {
            at = i ;
        }
        if(email[i] == '.' && at != 0)
        {
            dot = i ;
        }
    }

    if(at == 0 || dot == 0)
    {
        return 0 ;
    } else if(email[at+10] != '\0')
    {
        return 0 ;
    }

    for(i = at+1 ; email[i] != '\0' ; i++)
    {
        email[i] = tolower(email[i]);
    }

    if(strstr(email , "gmail.com") == NULL)
    {
        return 0 ;
    }

    
    return 1 ;
}

// link list of department head information -> return head name and family
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
    fscanf(head_file_ptr , "%s" , s->status);
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
    fscanf(head_file_ptr , "%s" , e->status);
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
        fscanf(head_file_ptr , "%s" , d->status);
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

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    }

}

// link list of academic staff information -> return staff name and family
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
    fscanf(staff_file_ptr , "%s" , s->status);
    fscanf(staff_file_ptr , "%s" , s->user_name );
    fscanf(staff_file_ptr , "%s" , s->password);

    fscanf(staff_file_ptr , "%s" , e->gender);
    fscanf(staff_file_ptr , "%s" , e->name);
    fscanf(staff_file_ptr , "%s" , e->family);
    fscanf(staff_file_ptr , "%4s/%2s/%2s" , e->start_date.year , e->start_date.month , e->start_date.day);
    fscanf(staff_file_ptr , "%s" , e->rank);
    fscanf(staff_file_ptr , "%s" , e->phone_number);
    fscanf(staff_file_ptr , "%s" , e->email);
    fscanf(staff_file_ptr , "%s" , e->status);
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
        fscanf(staff_file_ptr , "%s" , d->status);
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

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    }

}

// link list of student information
struct student_information student_list(char student_name[] , char student_family[] , char student_id[])
{
    struct student_information *s = malloc(sizeof(struct student_information));
    struct student_information *e = malloc(sizeof(struct student_information));
    struct student_information *d = NULL;
    struct student_information *temp = NULL;
    struct student_information *temp2 = NULL;

    student_file_ptr = fopen("student_information.txt" , "r");

    fscanf(student_file_ptr , "%s" , s->gender);
    fscanf(student_file_ptr , "%s" , s->name);
    fscanf(student_file_ptr , "%s" , s->family);
    fscanf(student_file_ptr , "%s" , s->code);
    fscanf(student_file_ptr , "%4s/%2s/%2s" , s->birth_date.year , s->birth_date.month , s->birth_date.day);
    fscanf(student_file_ptr , "%s" , s->birth_city);
    fscanf(student_file_ptr , "%s" , s->field_of_study);
    fscanf(student_file_ptr , "%s" , s->id);
    fscanf(student_file_ptr , "%s" , s->phone_number);
    fscanf(student_file_ptr , "%s" , s->email );

    fscanf(student_file_ptr , "%s" , e->gender);
    fscanf(student_file_ptr , "%s" , e->name);
    fscanf(student_file_ptr , "%s" , e->family);
    fscanf(student_file_ptr , "%s" , e->code);
    fscanf(student_file_ptr , "%4s/%2s/%2s" , e->birth_date.year , e->birth_date.month , e->birth_date.day);
    fscanf(student_file_ptr , "%s" , e->birth_city);
    fscanf(student_file_ptr , "%s" , e->field_of_study);
    fscanf(student_file_ptr , "%s" , e->id);
    fscanf(student_file_ptr , "%s" , e->phone_number);
    fscanf(student_file_ptr , "%s" , e->email );

    s->link = e ;
    e->link = NULL;


    // make link list of staff  information
    while(feof(student_file_ptr) == 0)
    {
        d = malloc(sizeof(struct student_information));

        fscanf(student_file_ptr , "%s" , d->gender);
        fscanf(student_file_ptr , "%s" , d->name);
        fscanf(student_file_ptr , "%s" , d->family);
        fscanf(student_file_ptr , "%s" , d->code);
        fscanf(student_file_ptr , "%4s/%2s/%2s" , d->birth_date.year , d->birth_date.month , d->birth_date.day);
        fscanf(student_file_ptr , "%s" , d->birth_city);
        fscanf(student_file_ptr , "%s" , d->field_of_study);
        fscanf(student_file_ptr , "%s" , d->id);
        fscanf(student_file_ptr , "%s" , d->phone_number);
        fscanf(student_file_ptr , "%s" , d->email );

        e->link = d ;
        e = d ;

    }
    e->link = NULL ;

    fclose(student_file_ptr);

    temp = s ;
    while(temp != NULL)
    {
        if(!strcmp(temp->name , student_name))
        {
           if(!strcmp(temp->family , student_family))
           {
                 return *temp;
           }
        } else if (!strcmp(temp->id , student_id))
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

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    }

    

}

// link list of lessons information
struct lesson_information lesson_list(char lesson_code[])
{
    struct lesson_information *s = malloc(sizeof(struct lesson_information));
    struct lesson_information *e = malloc(sizeof(struct lesson_information));
    struct lesson_information *d = NULL;
    struct lesson_information *temp = NULL;
    struct lesson_information *temp2 = NULL;

    lesson_file_ptr = fopen("lessons_information.txt" , "r");

    fscanf(lesson_file_ptr , "%s" , s->name);
    fscanf(lesson_file_ptr , "%s" , s->number_of_unit);
    fscanf(lesson_file_ptr , "%s" , s->type);
    fscanf(lesson_file_ptr , "%s" , s->code);
    fscanf(lesson_file_ptr , "%s" , s->status);

    fscanf(lesson_file_ptr , "%s" , e->name);
    fscanf(lesson_file_ptr , "%s" , e->number_of_unit);
    fscanf(lesson_file_ptr , "%s" , e->type);
    fscanf(lesson_file_ptr , "%s" , e->code);
    fscanf(lesson_file_ptr , "%s" , e->status);

    s->link = e ;
    e->link = NULL;


    // make link list of staff  information
    while(feof(lesson_file_ptr) == 0)
    {
        d = malloc(sizeof(struct student_information));

        fscanf(lesson_file_ptr , "%s" , d->name);
        fscanf(lesson_file_ptr , "%s" , d->number_of_unit);
        fscanf(lesson_file_ptr , "%s" , d->type);
        fscanf(lesson_file_ptr , "%s" , d->code);
        fscanf(lesson_file_ptr , "%s" , d->status);

        e->link = d ;
        e = d ;

    }
    e->link = NULL ;

    fclose(lesson_file_ptr);

    temp = s ;
    while(temp != NULL)
    {
        if (!strcmp(temp->code , lesson_code))
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

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    }
}

// date  1404/2/3 -> 1404/02/03
void date(char date[] )
{
    char d[10];
    int i = 0 , j = 0 ; 

    strcpy(d , date);
    for(i = 0 ; i < 2 ; i++)
    {
        date[i] = '0' ;
    }
    date[i] = '\0';
    
    j = strlen(d);
    for(i = 1 ; i >= 0 ; i--)
    {
        if(j == 0)
        {
            break;
        } 
        
        date[i] = d[j-1]; 

        if(j != 0) 
        {
            j--;
        }
    }

    
}

/// star password a123b -> *****
char* star_password()
{
    static char str[50] , ch;
    int i = 0 ;

    while(1)
    {
        ch = getch();

        if(ch == '\n' || ch == '\r')
        {
            str[i] = '\0';
            break;
        } else if (ch == 8)
        {
            if(i > 0)
            {
                printf("\b \b");
                i--;
            }
        } else
        {
            str[i] = ch ;
            i++;
            printf("*");
        }
    }
    

    return str ;
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
    while(choice <= 0 || choice > 4 )
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
    strcpy(admin_password , star_password());
    while(strcmp(admin_password , "") == 0)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter your password : ");
        strcpy(admin_password , star_password());
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
            admin_observe_department_head_list("observe users");
            admin_observe_academic_staff_list("observe users");
            break;
        }
        case 4 :
        {
            admin_delete_users_menu();
            break;
        }
        case 5 :
        {
            admin_reports_page();
            break;
        }
        case 6 :
        {
            admin_backup_menu();
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
    while(check_number(department_head.start_date.year) == 0 || strlen(department_head.start_date.year) != 4)
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
    date(department_head.start_date.month);

    printf("\n\t\t\t\tPlease enter day of %s  start: " , ch);
    gets(department_head.start_date.day);
    //check day
    while(check_number(department_head.start_date.day) == 0 || strlen(department_head.start_date.day) > 2)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter day of  %s  srtart: " , ch);
        gets(department_head.start_date.day);
    }
    date(department_head.start_date.day);

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
    // check email
    while(!check_email(department_head.email))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s email : " , ch);
        gets(department_head.email);
    }

    strcpy(department_head.status , "active");

    printf("\n\t\t\t\tPlease enter %s user name : " , ch);
    gets(department_head.user_name);

    printf("\n\t\t\t\tPlease enter %s password : " , ch);
    strcpy(department_head.password , star_password());

    printf("\n\n\t\t\t\tPlease confirm %s password : " , ch);
    strcpy(confirm_password , star_password());

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
    fprintf(head_file_ptr , "%s\n" , department_head.status);
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
    while(check_number(staff.start_date.year) == 0 || strlen(staff.start_date.year) != 4)
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
    date(staff.start_date.month);

    printf("\n\t\t\t\tPlease enter day of %s  start: " , ch);
    gets(staff.start_date.day);
    //check day
    while(check_number(staff.start_date.day) == 0 || strlen(staff.start_date.day) > 2)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter day of  %s  start: " , ch);
        gets(staff.start_date.day);
    }
    date(staff.start_date.day);

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
    while(!check_email(staff.email))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s email : " , ch);
        gets(staff.email);
    }

    strcpy(staff.status , "active");

    printf("\n\t\t\t\tPlease enter %s user name : " , ch);
    gets(staff.user_name);

    printf("\n\t\t\t\tPlease enter %s password : " , ch);
    strcpy(staff.password , star_password());

    printf("\n\n\t\t\t\tPlease confirm %s password : " , ch);
    strcpy(confirm_password , star_password());

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
    fprintf(staff_file_ptr , "%s\n" , staff.status);
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

// observe department head list
void admin_observe_department_head_list(char type[])
{
    system("cls");

    int i = 0  , j = 0;
    char enter ;
    

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
    fscanf(head_file_ptr , "%s" , s->status);
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
    fscanf(head_file_ptr , "%s" , e->status);
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
        fscanf(head_file_ptr , "%s" , d->status);
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
    printf("%-14s%c" , "GROUP NAME" , 179);
    printf("%-14s%c" , "CODE" , 179);
    printf("%-13s%c" , "PHONE NUMBER" , 179);
    printf("%-33s%c" , "EMAIL" , 179);
    printf("%-9s%c" , "STATUS" , 179);
    printf("%-13s%c" , "USER NAME" , 179);
    printf("%-12s" , "PASSWORD");
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
        printf("%4s/%2s/%2s%2c" , temp->start_date.year , temp->start_date.month , temp->start_date.day ,  179);
        printf("%-14s%c" , temp->group_name , 179);
        printf("%-14s%c" , temp->code , 179);
        printf("%-13s%c" , temp->phone_number , 179);
        printf("%-33s%c" , temp->email , 179);
        printf("%-9s%c" , temp->status , 179);
        printf("%-13s%c" , temp->user_name , 179);
        printf("%-12s" , temp->password);
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

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    }

    if(!strcmp(type , "reports"))
    {
        // return to main menu
        printf("\033[34m""\n    Please enter to continue ....""\033[0m");
        enter = getchar();
        if(enter == '\n')
        {
            admin_menu();
        }
    }
}

// observe academic staff list
void admin_observe_academic_staff_list(char type[])
{
    if(!strcmp(type , "reports"))
    {
        system("cls");
    }

    int i = 0  , j = 0;
    char enter ;

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
    fscanf(staff_file_ptr , "%s" , s2->status);
    fscanf(staff_file_ptr , "%s" , s2->user_name);
    fscanf(staff_file_ptr , "%s" , s2->password);

    fscanf(staff_file_ptr , "%s" , e2->gender);
    fscanf(staff_file_ptr , "%s" , e2->name);
    fscanf(staff_file_ptr , "%s" , e2->family);
    fscanf(staff_file_ptr , "%4s/%2s/%2s" , e2->start_date.year , e2->start_date.month , e2->start_date.day);
    fscanf(staff_file_ptr , "%s" , e2->rank);
    fscanf(staff_file_ptr , "%s" , e2->phone_number);
    fscanf(staff_file_ptr , "%s" , e2->email);
    fscanf(staff_file_ptr , "%s" , e2->status);
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
        fscanf(staff_file_ptr , "%s" , d2->status);
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
    printf("%-16s%c" , "NAME" , 179);
    printf("%-17s%c" , "FAMILY" , 179);
    printf("%-12s%c" , "STAT DATE" , 179);
    printf("%-13s%c" , "RANK" , 179);
    printf("%-13s%c" , "PHONE NUMBER" , 179);
    printf("%-33s%c" , "EMAIL" , 179);
    printf("%-9s%c" , "STATUS" , 179);
    printf("%-16s%c" , "USER NAME" , 179);
    printf("%-16s" , "PASSWORD");
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
        printf("%-16s%c" , t->name , 179);
        printf("%-17s%c" , t->family , 179);
        printf("%4s/%2s/%2s%3c" , t->start_date.year , t->start_date.month , t->start_date.day , 179);
        printf("%-13s%c" , t->rank , 179);
        printf("%-13s%c" , t->phone_number , 179);
        printf("%-33s%c" , t->email , 179);
        printf("%-9s%c" , t->status , 179);
        printf("%-16s%c" , t->user_name , 179);
        printf("%-16s" , t->password);
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

        free(t2);
        t2 = t ;
        t = t->link;

    }

    // return to main menu
    printf("\033[34m""\n    Please enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        admin_menu();
    }
}

// delete users
void admin_delete_users_menu()
{
     int admin_choice = 0 ;
    char c[100];

    system("cls");

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|             ADMIN DELETE USERS PAGE              |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\t1- Delete department head");
    printf("\n\t\t\t\t2- Delete academic staff");
    printf("\n\t\t\t\t3- Exit\n");

    printf("\n\t\t\t\tPlease enter your choice : ");
    scanf("%d" , &admin_choice);
    getchar();
    // limit admin inputs
    while(admin_choice <= 0 || admin_choice > 3)
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter your choice : ");
        scanf("%d" , &admin_choice);
        gets(c);
    }

    admin_delete_users_menu_choice(admin_choice);
}

// switch structure for admin choice in delete users page
void admin_delete_users_menu_choice(int admin_choice)
{
    switch(admin_choice)
    {
        case 1 :
        {
            admin_delete_head_page();
            break;
        }
        case 2 :
        {
            admin_delete_staff_page();
            break;
        }
        case 3 :
        {
            admin_menu();
            break;
        }
    }
}

// delete head page
void admin_delete_head_page()
{
    
    char enter , head_name[50] , head_family[50]  , t_date[20];
    struct date terminate_date ;

    system("cls");

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|         ADMIN DELETE DEPARTMENT HEAD PAGE        |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");


    printf("\n\t\t\t\tPlease enter users name : ");
    gets(head_name);
    // check 
    while(!check_string(head_name))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter users name : ");
        gets(head_name);
    }

    printf("\n\t\t\t\tPlease enter users family : ");
    gets(head_family);
    // check 
    while(!check_string(head_family))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter users family : ");
        gets(head_family);
    }

    printf("\n\t\t\t\tPlease enter year of terminate : ");
    gets(terminate_date.year);
    //check 
    while(check_number(terminate_date.year) == 0 || strlen(terminate_date.year) != 4)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter year of terminate : ");
        gets(terminate_date.year);
    }

    printf("\n\t\t\t\tPlease enter month of terminate : ");
    gets(terminate_date.month);
    //check 
    while(check_number(terminate_date.month) == 0 || strlen(terminate_date.month) > 2)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter month of terminate : ");
        gets(terminate_date.month);
    }
    date(terminate_date.month);

    printf("\n\t\t\t\tPlease enter day of terminate : ");
    gets(terminate_date.day);
    //check 
    while(check_number(terminate_date.day) == 0 || strlen(terminate_date.day) > 2)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter day of terminate : ");
        gets(terminate_date.day);
    }
    date(terminate_date.day);
    
    sprintf(t_date , "%4s/%2s/%2s" , terminate_date.year  , terminate_date.month , terminate_date.day);

    admin_delete_head(head_name , head_family , t_date);

    printf("\033[32m""\n\t\t\t\tuser delete successfully :)\n""\033[0m");

    // return to admin page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        admin_menu();
    }
}

// delete head
void admin_delete_head(char head_name[] , char head_family[] , char terminate_date[])
{
    struct department_head_information *s = malloc(sizeof(struct department_head_information));
    struct department_head_information *e = malloc(sizeof(struct department_head_information));
    struct department_head_information *d = NULL ;
    struct department_head_information *temp = NULL ;
    struct department_head_information *temp2 = NULL ;

    head_file_ptr = fopen("department_head_information.txt" , "r");

    fscanf(head_file_ptr , "%s" , s->gender);
    fscanf(head_file_ptr , "%s" , s->name);
    fscanf(head_file_ptr , "%s" , s->family);
    fscanf(head_file_ptr , "%4s/%2s/%2s" , s->start_date.year , s->start_date.month , s->start_date.day);
    fscanf(head_file_ptr , "%s" , s->group_name);
    fscanf(head_file_ptr , "%s" , s->code);
    fscanf(head_file_ptr , "%s" , s->phone_number);
    fscanf(head_file_ptr , "%s" , s->email);
    fscanf(head_file_ptr , "%s" , s->status);
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
    fscanf(head_file_ptr , "%s" , e->status);
    fscanf(head_file_ptr , "%s" , e->user_name);
    fscanf(head_file_ptr , "%s" , e->password);

    s->link = e ;
    e->link = NULL ;

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
        fscanf(head_file_ptr , "%s" , d->status);
        fscanf(head_file_ptr , "%s" , d->user_name);
        fscanf(head_file_ptr , "%s" , d->password);

        e->link = d ;
        e = d ;
    }
    e->link = NULL ;

    fclose(head_file_ptr);

    head_file_ptr = fopen("department_head_information.txt" , "w");

    temp = s ;
    while(temp != NULL)
    {
        if(!strcmp(temp->name , head_name))
        {
            if(!strcmp(temp->family , head_family))
            {
                strcpy(temp->status , "");
                strcpy(temp->status , "inactive");
                
                terminate_head_file_ptr = fopen("terminated_head.txt" , "a");

                sscanf(terminate_date , "%4s/%2s/%2s" , temp->terminate_date.year , temp->terminate_date.month , temp->terminate_date.day);

                if(temp == s)
                    fprintf(terminate_head_file_ptr , "%s\n" , temp->gender);
                else 
                    fprintf(terminate_head_file_ptr , "\n%s\n" , temp->gender);
                fprintf(terminate_head_file_ptr , "%s\n" , temp->name);
                fprintf(terminate_head_file_ptr , "%s\n" , temp->family);
                fprintf(terminate_head_file_ptr , "%4s/%2s/%2s\n" , temp->start_date.year , temp->start_date.month , temp->start_date.day);
                fprintf(terminate_head_file_ptr , "%s\n" , temp->group_name);
                fprintf(terminate_head_file_ptr , "%s\n" , temp->code);
                fprintf(terminate_head_file_ptr , "%s\n" , temp->phone_number);
                fprintf(terminate_head_file_ptr , "%s\n" , temp->email);
                fprintf(terminate_head_file_ptr , "%s\n" , temp->status);
                fprintf(terminate_head_file_ptr , "%4s/%2s/%2s\n" , temp->terminate_date.year , temp->terminate_date.month, temp->terminate_date.day);
                fprintf(terminate_head_file_ptr , "%s\n" , temp->user_name);
                fprintf(terminate_head_file_ptr , "%s" , temp->password);

                fclose(terminate_head_file_ptr);

            }
        }

        if(temp == s)
            fprintf(head_file_ptr , "%s\n" , temp->gender);
        else 
            fprintf(head_file_ptr , "\n%s\n" , temp->gender);
        fprintf(head_file_ptr , "%s\n" , temp->name);
        fprintf(head_file_ptr , "%s\n" , temp->family);
        fprintf(head_file_ptr , "%4s/%2s/%2s\n" , temp->start_date.year , temp->start_date.month , temp->start_date.day);
        fprintf(head_file_ptr , "%s\n" , temp->group_name);
        fprintf(head_file_ptr , "%s\n" , temp->code);
        fprintf(head_file_ptr , "%s\n" , temp->phone_number);
        fprintf(head_file_ptr , "%s\n" , temp->email);
        fprintf(head_file_ptr , "%s\n" , temp->status);
        fprintf(head_file_ptr , "%s\n" , temp->user_name);
        fprintf(head_file_ptr , "%s" , temp->password);

        temp = temp->link ;
    }

    fclose(head_file_ptr);

    // delete link list
    temp2 = s ;
    temp = s->link ;
    while (temp != NULL)
    {

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    }
    
}

// delete staff page
void admin_delete_staff_page()
{
    
    char enter , staff_name[50] , staff_family[50]  , t_date[20];
    struct date terminate_date ;

    system("cls");

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|         ADMIN DELETE ACADEMIC STAFF PAGE         |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");


    printf("\n\t\t\t\tPlease enter users name : ");
    gets(staff_name);
    // check 
    while(!check_string(staff_name))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter users name : ");
        gets(staff_name);
    }

    printf("\n\t\t\t\tPlease enter users family : ");
    gets(staff_family);
    // check 
    while(!check_string(staff_family))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter users family : ");
        gets(staff_family);
    }

    printf("\n\t\t\t\tPlease enter year of terminate : ");
    gets(terminate_date.year);
    //check 
    while(check_number(terminate_date.year) == 0 || strlen(terminate_date.year) != 4)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter year of terminate : ");
        gets(terminate_date.year);
    }

    printf("\n\t\t\t\tPlease enter month of terminate : ");
    gets(terminate_date.month);
    //check 
    while(check_number(terminate_date.month) == 0 || strlen(terminate_date.month) > 2)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter month of terminate : ");
        gets(terminate_date.month);
    }
    date(terminate_date.month);

    printf("\n\t\t\t\tPlease enter day of terminate : ");
    gets(terminate_date.day);
    //check 
    while(check_number(terminate_date.day) == 0 || strlen(terminate_date.day) > 2)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter day of terminate : ");
        gets(terminate_date.day);
    }
    date(terminate_date.day);
    
    sprintf(t_date , "%4s/%2s/%2s" , terminate_date.year  , terminate_date.month , terminate_date.day);

    admin_delete_staff(staff_name , staff_family , t_date);

    printf("\033[32m""\n\t\t\t\tuser delete successfully :)\n""\033[0m");

    // return to admin page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        admin_menu();
    }
}

// delete staff
void admin_delete_staff(char staff_name[] , char staff_family[] , char terminate_date[])
{
    struct academic_staff_information *s = malloc(sizeof(struct academic_staff_information));
    struct academic_staff_information *e = malloc(sizeof(struct academic_staff_information));
    struct academic_staff_information *d = NULL ;
    struct academic_staff_information *temp = NULL ;
    struct academic_staff_information *temp2 = NULL ;

    staff_file_ptr = fopen("staff_information.txt" , "r");

    fscanf(staff_file_ptr , "%s" , s->gender);
    fscanf(staff_file_ptr , "%s" , s->name);
    fscanf(staff_file_ptr , "%s" , s->family);
    fscanf(staff_file_ptr , "%4s/%2s/%2s" , s->start_date.year , s->start_date.month , s->start_date.day);
    fscanf(staff_file_ptr , "%s" , s->rank);
    fscanf(staff_file_ptr , "%s" , s->phone_number);
    fscanf(staff_file_ptr , "%s" , s->email);
    fscanf(staff_file_ptr , "%s" , s->status);
    fscanf(staff_file_ptr , "%s" , s->user_name);
    fscanf(staff_file_ptr , "%s" , s->password);

    fscanf(staff_file_ptr , "%s" , e->gender);
    fscanf(staff_file_ptr , "%s" , e->name);
    fscanf(staff_file_ptr , "%s" , e->family);
    fscanf(staff_file_ptr , "%4s/%2s/%2s" , e->start_date.year , e->start_date.month , e->start_date.day);
    fscanf(staff_file_ptr , "%s" , e->rank);
    fscanf(staff_file_ptr , "%s" , e->phone_number);
    fscanf(staff_file_ptr , "%s" , e->email);
    fscanf(staff_file_ptr , "%s" , e->status);
    fscanf(staff_file_ptr , "%s" , e->user_name);
    fscanf(staff_file_ptr , "%s" , e->password);

    s->link = e ;
    e->link = NULL ;

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
        fscanf(staff_file_ptr , "%s" , d->status);
        fscanf(staff_file_ptr , "%s" , d->user_name);
        fscanf(staff_file_ptr , "%s" , d->password);
        
        e->link = d ;
        e = d ;
    }
    e->link = NULL ;

    fclose(staff_file_ptr);

    staff_file_ptr = fopen("staff_information.txt" , "w");

    temp = s ;
    while(temp != NULL)
    {
        if(!strcmp(temp->name , staff_name))
        {
            if(!strcmp(temp->family , staff_family))
            {
                strcpy(temp->status , "");
                strcpy(temp->status , "inactive");
                
                terminate_staff_file_ptr = fopen("terminated_staff.txt" , "a");

                sscanf(terminate_date , "%4s/%2s/%2s" , temp->terminate_date.year , temp->terminate_date.month , temp->terminate_date.day);

                if(temp == s)
                    fprintf(terminate_staff_file_ptr , "%s\n" , temp->gender);
                else 
                    fprintf(terminate_staff_file_ptr , "\n%s\n" , temp->gender);
                fprintf(terminate_staff_file_ptr , "%s\n" , temp->name);
                fprintf(terminate_staff_file_ptr , "%s\n" , temp->family);
                fprintf(terminate_staff_file_ptr , "%4s/%2s/%2s\n" , temp->start_date.year , temp->start_date.month , temp->start_date.day);
                fprintf(terminate_staff_file_ptr , "%s\n" , temp->rank);
                fprintf(terminate_staff_file_ptr , "%s\n" , temp->phone_number);
                fprintf(terminate_staff_file_ptr , "%s\n" , temp->email);
                fprintf(terminate_staff_file_ptr , "%s\n" , temp->status);
                fprintf(terminate_staff_file_ptr , "%4s/%2s/%2s\n" , temp->terminate_date.year , temp->terminate_date.month, temp->terminate_date.day);
                fprintf(terminate_staff_file_ptr , "%s\n" , temp->user_name);
                fprintf(terminate_staff_file_ptr , "%s" , temp->password);

                fclose(terminate_staff_file_ptr);

            }
        }

        if(temp == s)
            fprintf(staff_file_ptr , "%s\n" , temp->gender);
        else 
            fprintf(staff_file_ptr , "\n%s\n" , temp->gender);
        fprintf(staff_file_ptr , "%s\n" , temp->name);
        fprintf(staff_file_ptr , "%s\n" , temp->family);
        fprintf(staff_file_ptr , "%4s/%2s/%2s\n" , temp->start_date.year , temp->start_date.month , temp->start_date.day);
        fprintf(staff_file_ptr , "%s\n" , temp->rank);
        fprintf(staff_file_ptr , "%s\n" , temp->phone_number);
        fprintf(staff_file_ptr , "%s\n" , temp->email);
        fprintf(staff_file_ptr , "%s\n" , temp->status);
        fprintf(staff_file_ptr , "%s\n" , temp->user_name);
        fprintf(staff_file_ptr , "%s" , temp->password);

        temp = temp->link ;
        
    }

    fclose(staff_file_ptr);

    // delete link list
    temp2 = s ;
    temp = s->link ;
    while (temp != NULL)
    {

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    }
}

// reports page
void admin_reports_page()
{
   int admin_choice = 0 ;
    char c[100];

    system("cls");

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|                ADMIN REPORTS PAGE                |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\t1- Academic staff information lists");
    printf("\n\t\t\t\t2- Department head information list");
    printf("\n\t\t\t\t3- Terminated users information list");
    printf("\n\t\t\t\t4- Exit\n");

    printf("\n\t\t\t\tPlease enter your choice : ");
    scanf("%d" , &admin_choice);
    getchar();
    // limit admin inputs
    while(admin_choice <= 0 || admin_choice > 4)
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter your choice : ");
        scanf("%d" , &admin_choice);
        gets(c);
    }

    admin_reports_menu_choice(admin_choice); 
}

// switch structure for admin choice in reports page
void admin_reports_menu_choice(int admin_choice)
{
    switch(admin_choice)
    {
        case 1 :
        {
            admin_observe_academic_staff_list("reports");
            break;
        }
        case 2 :
        {
            admin_observe_department_head_list("reports");
            break;
        }
        case 3 : 
        {
            admin_observe_terminated_users_list();
            break;
        }
        case 4 : 
        {
            admin_menu();
            break;
        }
    }
}

// observe terminated 
void admin_observe_terminated_users_list()
{
    system("cls");

    int i = 0  , j = 0;
    char enter ;
    
    // observe terminated head

    struct department_head_information *s = malloc(sizeof(struct department_head_information));
    struct department_head_information *e = malloc(sizeof(struct department_head_information));
    struct department_head_information *d = NULL;
    struct department_head_information *temp = NULL;
    struct department_head_information *temp2 = NULL;

    terminate_head_file_ptr = fopen("terminated_head.txt" , "r");

    fscanf(terminate_head_file_ptr , "%s" , s->gender);
    fscanf(terminate_head_file_ptr , "%s" , s->name);
    fscanf(terminate_head_file_ptr , "%s" , s->family);
    fscanf(terminate_head_file_ptr , "%4s/%2s/%2s" , s->start_date.year , s->start_date.month , s->start_date.day);
    fscanf(terminate_head_file_ptr , "%s" , s->group_name);
    fscanf(terminate_head_file_ptr , "%s" , s->code);
    fscanf(terminate_head_file_ptr , "%s" , s->phone_number);
    fscanf(terminate_head_file_ptr , "%s" , s->email);
    fscanf(terminate_head_file_ptr , "%s" , s->status);
    fscanf(terminate_head_file_ptr , "%4s/%2s/%2s" , s->terminate_date.year , s->terminate_date.month , s->terminate_date.day);
    fscanf(terminate_head_file_ptr , "%s" , s->user_name);
    fscanf(terminate_head_file_ptr , "%s" , s->password);

    fscanf(terminate_head_file_ptr , "%s" , e->gender);
    fscanf(terminate_head_file_ptr , "%s" , e->name);
    fscanf(terminate_head_file_ptr , "%s" , e->family);
    fscanf(terminate_head_file_ptr , "%4s/%2s/%2s" , e->start_date.year , e->start_date.month , e->start_date.day);
    fscanf(terminate_head_file_ptr , "%s" , e->group_name);
    fscanf(terminate_head_file_ptr , "%s" , e->code);
    fscanf(terminate_head_file_ptr , "%s" , e->phone_number);
    fscanf(terminate_head_file_ptr , "%s" , e->email);
    fscanf(terminate_head_file_ptr , "%s" , e->status);
    fscanf(terminate_head_file_ptr , "%4s/%2s/%2s" , e->terminate_date.year , e->terminate_date.month , e->terminate_date.day);
    fscanf(terminate_head_file_ptr , "%s" , e->user_name);
    fscanf(terminate_head_file_ptr , "%s" , e->password);

    s->link = e ;
    e->link = NULL ;

    //make link list
    while(feof(terminate_head_file_ptr) == 0)
    {
        d = malloc(sizeof(struct department_head_information));

        fscanf(terminate_head_file_ptr , "%s" , d->gender);
        fscanf(terminate_head_file_ptr , "%s" , d->name);
        fscanf(terminate_head_file_ptr , "%s" , d->family);
        fscanf(terminate_head_file_ptr , "%4s/%2s/%2s" , d->start_date.year , d->start_date.month , d->start_date.day);
        fscanf(terminate_head_file_ptr , "%s" , d->group_name);
        fscanf(terminate_head_file_ptr , "%s" , d->code);
        fscanf(terminate_head_file_ptr , "%s" , d->phone_number);
        fscanf(terminate_head_file_ptr , "%s" , d->email);
        fscanf(terminate_head_file_ptr , "%s" , d->status);
        fscanf(terminate_head_file_ptr , "%4s/%2s/%2s" , d->terminate_date.year , d->terminate_date.month , d->terminate_date.day);
        fscanf(terminate_head_file_ptr , "%s" , d->user_name);
        fscanf(terminate_head_file_ptr , "%s" , d->password);

        e->link = d ;
        e = d ;
    }
    e->link = NULL ;

    fclose(terminate_head_file_ptr) ;

    printf("\n%c" , 201);
    for(i = 0 ; i < 164 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 187);

    printf("%c" , 186);
    printf("%69s%s%69s" , "" , "TERMINATED DEPARTMENT HEAD" , "");
    printf("%c\n" , 186);

    printf("%c" , 186);
    for(i = 0 ; i < 164 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 186);

    printf("%c" , 186);
    printf("%2s%c" , "" , 179);
    printf("%-7s%c" , "GENDER" , 179);
    printf("%-12s%c" , "NAME" , 179);
    printf("%-12s%c" , "FAMILY" , 179);
    printf("%-11s%c" , "STAT DATE" , 179);
    printf("%-13s%c" , "GROUP NAME" , 179);
    printf("%-13s%c" , "CODE" , 179);
    printf("%-13s%c" , "PHONE NUMBER" , 179);
    printf("%-32s%c" , "EMAIL" , 179);
    printf("%-14s%c" , "TERMINATE DATE" , 179);
    printf("%-12s%c" , "USER NAME" , 179);
    printf("%-12s" , "PASSWORD");
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
        printf("%-12s%c" , temp->family , 179);
        printf("%4s/%2s/%2s%2c" , temp->start_date.year , temp->start_date.month , temp->start_date.month ,  179);
        printf("%-13s%c" , temp->group_name , 179);
        printf("%-13s%c" , temp->code , 179);
        printf("%-13s%c" , temp->phone_number , 179);
        printf("%-32s%c" , temp->email , 179);
        printf("%4s/%2s/%2s%5c" , temp->terminate_date.year , temp->terminate_date.month ,temp->terminate_date.day , 179);
        printf("%-12s%c" , temp->user_name , 179);
        printf("%-12s" , temp->password);
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

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    }


    // observe terminated staff

    struct academic_staff_information *s2 = malloc(sizeof(struct academic_staff_information));
    struct academic_staff_information *e2 = malloc(sizeof(struct academic_staff_information));
    struct academic_staff_information *d2 = NULL;
    struct academic_staff_information *t = NULL;
    struct academic_staff_information *t2 = NULL;

    terminate_staff_file_ptr = fopen("terminated_staff.txt" , "r");

    fscanf(terminate_staff_file_ptr , "%s" , s2->gender);
    fscanf(terminate_staff_file_ptr , "%s" , s2->name);
    fscanf(terminate_staff_file_ptr , "%s" , s2->family);
    fscanf(terminate_staff_file_ptr , "%4s/%2s/%2s" , s2->start_date.year , s2->start_date.month , s2->start_date.day);
    fscanf(terminate_staff_file_ptr , "%s" , s2->rank);
    fscanf(terminate_staff_file_ptr , "%s" , s2->phone_number);
    fscanf(terminate_staff_file_ptr , "%s" , s2->email);
    fscanf(terminate_staff_file_ptr , "%s" , s2->status);
    fscanf(terminate_staff_file_ptr , "%4s/%2s/%2s" , s2->terminate_date.year , s2->terminate_date.month , s2->terminate_date.day);
    fscanf(terminate_staff_file_ptr , "%s" , s2->user_name);
    fscanf(terminate_staff_file_ptr , "%s" , s2->password);

    fscanf(terminate_staff_file_ptr , "%s" , e2->gender);
    fscanf(terminate_staff_file_ptr , "%s" , e2->name);
    fscanf(terminate_staff_file_ptr , "%s" , e2->family);
    fscanf(terminate_staff_file_ptr , "%4s/%2s/%2s" , e2->start_date.year , e2->start_date.month , e2->start_date.day);
    fscanf(terminate_staff_file_ptr , "%s" , e2->rank);
    fscanf(terminate_staff_file_ptr , "%s" , e2->phone_number);
    fscanf(terminate_staff_file_ptr , "%s" , e2->email);
    fscanf(terminate_staff_file_ptr , "%s" , e2->status);
    fscanf(terminate_staff_file_ptr , "%4s/%2s/%2s" , e2->terminate_date.year , e2->terminate_date.month , e2->terminate_date.day);
    fscanf(terminate_staff_file_ptr , "%s" , e2->user_name);
    fscanf(terminate_staff_file_ptr , "%s" , e2->password);

    s2->link = e2 ;
    e2->link = NULL ;
    // make link list
    while(feof(terminate_staff_file_ptr) == 0)
    {
        d2 = malloc(sizeof(struct academic_staff_information));

        fscanf(terminate_staff_file_ptr , "%s" , d2->gender);
        fscanf(terminate_staff_file_ptr , "%s" , d2->name);
        fscanf(terminate_staff_file_ptr , "%s" , d2->family);
        fscanf(terminate_staff_file_ptr , "%4s/%2s/%2s" , d2->start_date.year , d2->start_date.month , d2->start_date.day);
        fscanf(terminate_staff_file_ptr , "%s" , d2->rank);
        fscanf(terminate_staff_file_ptr , "%s" , d2->phone_number);
        fscanf(terminate_staff_file_ptr , "%s" , d2->email);
        fscanf(terminate_staff_file_ptr , "%s" , d2->status);
        fscanf(terminate_staff_file_ptr , "%4s/%2s/%2s" , d2->terminate_date.year , d2->terminate_date.month , d2->terminate_date.day);
        fscanf(terminate_staff_file_ptr , "%s" , d2->user_name);
        fscanf(terminate_staff_file_ptr , "%s" , d2->password);

        e2->link = d2 ;
        e2 = d2 ;
    }
    e2->link = NULL ;

    fclose(terminate_staff_file_ptr) ;

    printf("\n\n%c" , 201);
    for(i = 0 ; i < 164 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 187);

    printf("%c" , 186);
    printf("%74s%s%74s" , "" , "TERMINATED STAFF" , "");
    printf("%c\n" , 186);

    printf("%c" , 186);
    for(i = 0 ; i < 164 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 186);

    printf("%c" , 186);
    printf("%2s%c" , "" , 179);
    printf("%-7s%c" , "GENDER" , 179);
    printf("%-14s%c" , "NAME" , 179);
    printf("%-15s%c" , "FAMILY" , 179);
    printf("%-12s%c" , "STAT DATE" , 179);
    printf("%-13s%c" , "RANK" , 179);
    printf("%-12s%c" , "PHONE NUMBER" , 179);
    printf("%-32s%c" , "EMAIL" , 179);
    printf("%-16s%c" , "TERMINATED STAFF" , 179);
    printf("%-16s%c" , "USER NAME" , 179);
    printf("%-15s" , "PASSWORD");
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
        printf("%-14s%c" , t->name , 179);
        printf("%-15s%c" , t->family , 179);
        printf("%4s/%2s/%2s%3c" , t->start_date.year , t->start_date.month , t->start_date.day , 179);
        printf("%-13s%c" , t->rank , 179);
        printf("%-12s%c" , t->phone_number , 179);
        printf("%-32s%c" , t->email , 179);
        printf("%4s/%2s/%2s%7c" , t->terminate_date.year, t->terminate_date.month , t->terminate_date.day , 179);
        printf("%-16s%c" , t->user_name , 179);
        printf("%-15s" , t->password);
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

        free(t2);
        t2 = t ;
        t = t->link;

    }

    // return to main menu
    printf("\033[34m""\n    Please enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        admin_menu();
    }
    
}

// backup files
void admin_backup_menu()
{
   int admin_choice = 0 ;
    char c[100] , enter;

    system("cls");

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|                   BACK UP PAGE                   |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\t1- Back up from department head information file");
    printf("\n\t\t\t\t2- Back up from academic staff information file");
    printf("\n\t\t\t\t3- Back up from student information file");
    printf("\n\t\t\t\t4- Back up from lessons  information file");
    printf("\n\t\t\t\t5- Back up from scores file");
    printf("\n\t\t\t\t6- .........");
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

    admin_backup_menu_choice(admin_choice);

    printf("\033[32m""\n\t\t\t\tBackup file successfully built :)\n""\033[0m");

    // return to main menu
    printf("\033[34m""\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
         admin_menu();
    }

}

// switch structure for admin choice in backup file page
void admin_backup_menu_choice( int admin_choice)
{
    switch(admin_choice)
    {

        case 1 :
        {
            admin_backup(1);
            break;
        }
        case 2 :
        {
            admin_backup(2);
            break;
        }
        case 3 :
        {
            admin_backup(3);
            break;
        }
        case 4 :
        {
            admin_backup(4);
            break;
        }
        case 5 :
        {
            admin_backup(5);
            break;
        }
        case 6 :
        {
            admin_backup(6);
            break;
        }
        case 7 :
        {
            admin_menu();
            break;
        }

    }
}

// backup system
void admin_backup(int n)
{
    char c  , file_name[70];
    if(n == 1)
    {
        head_file_ptr = fopen("department_head_information.txt" , "r");

        sprintf(file_name , "backup_department_head_information(%s).txt" , __DATE__);

        backup_head_file_ptr = fopen(file_name ,  "w");

        c = fgetc(head_file_ptr);
        while(feof(head_file_ptr) == 0)
        {
            fputc(c , backup_head_file_ptr);
            c = fgetc(head_file_ptr);
        }

        fclose(head_file_ptr);
        fclose(backup_head_file_ptr);

    } else if(n == 2)
    {
        staff_file_ptr = fopen("staff_information.txt" , "r");

        sprintf(file_name , "backup_staff_information(%s).txt" , __DATE__);

        backup_staff_file_ptr = fopen(file_name ,  "w");

        c = fgetc(staff_file_ptr);
        while(feof(staff_file_ptr) == 0)
        {
            fputc(c , backup_staff_file_ptr);
            c = fgetc(staff_file_ptr);
        }

        fclose(staff_file_ptr);
        fclose(backup_staff_file_ptr);

    } else if(n == 3)
    {
        student_file_ptr = fopen("student_information.txt" , "r");

        sprintf(file_name , "backup_student_information(%s).txt" , __DATE__);

        backup_student_file_ptr = fopen(file_name ,  "w");

        c = fgetc(student_file_ptr);
        while(feof(student_file_ptr) == 0)
        {
            fputc(c , backup_student_file_ptr);
            c = fgetc(student_file_ptr);
        }

        fclose(student_file_ptr);
        fclose(backup_student_file_ptr);

    } else if(n == 4)
    {
        lesson_file_ptr = fopen("lessons_information.txt" , "r");

        sprintf(file_name , "backup_lessons_information(%s).txt" , __DATE__);

        backup_lesson_file_ptr = fopen(file_name ,  "w");

        c = fgetc(lesson_file_ptr);
        while(feof(lesson_file_ptr) == 0)
        {
            fputc(c , backup_lesson_file_ptr);
            c = fgetc(lesson_file_ptr);
        }

        fclose(lesson_file_ptr);
        fclose(backup_lesson_file_ptr);

    } else if(n == 5)
    {
        score_file_ptr = fopen("scores_information.txt" , "r");

        sprintf(file_name , "backup_scores_information(%s).txt" , __DATE__);

        backup_score_file_ptr = fopen(file_name ,  "w");

        c = fgetc(score_file_ptr);
        while(feof(score_file_ptr) == 0)
        {
            fputc(c , backup_score_file_ptr);
            c = fgetc(score_file_ptr);
        }

        fclose(score_file_ptr);
        fclose(backup_score_file_ptr);

    } else if(n == 6)
    {

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
    strcpy(head_password , star_password());
    while(strcmp(head_password , "") == 0)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter your password : ");
        strcpy(head_password , star_password());
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
    fscanf(head_file_ptr , "%s" , s->status);
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
    fscanf(head_file_ptr , "%s" , e->status);
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
        fscanf(head_file_ptr , "%s" , d->status);
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
    printf("\n\t\t\t\t4- Edit lessons information");
    printf("\n\t\t\t\t5- Delete old lesson information");
    printf("\n\t\t\t\t6- Reports");
    printf("\n\t\t\t\t7- User account settings");
    printf("\n\t\t\t\t8- Exit\n");

    printf("\n\t\t\t\tPlease enter your choice : ");
    scanf("%d" , &head_choice);
    getchar();
    // limit department head inputs
    while(head_choice <= 0 || head_choice > 8)
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
            department_head_edit_score_page(head);
            break;
        }
        case 4 :
        {
            department_head_edit_lesson(head);
            break;
        }
        case 5 :
        {
            department_head_delete_lesson_page(head);
            break;
        }
        case 6 :
        {
            department_head_reports_page(head);
            break;
        }
        case 7 :
        {
            department_head_setting_page(head);
            break;
        }
        case 8 :
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

    strcpy(lesson.status , "available");


    // print lesson information in file
    lesson_file_ptr = fopen("lessons_information.txt" , "a");

    fprintf(lesson_file_ptr , "\n%s\n" , lesson.name);
    fprintf(lesson_file_ptr , "%s\n" , lesson.number_of_unit);
    fprintf(lesson_file_ptr , "%s\n" , lesson.type);
    fprintf(lesson_file_ptr , "%s\n" , lesson.code);
    fprintf(lesson_file_ptr , "%s" , lesson.status);



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
    fprintf(score_file_ptr , "%s\n" , __TIME__);
    fprintf( score_file_ptr ,"%s %s" , head.name , head.family);
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

// department head edit score page
void department_head_edit_score_page(struct department_head_information head)
{
    char   enter;
    struct student_score score;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|                    EDIT SCORE                    |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");


    printf("\n\t\t\t\tPlease enter students id : ");
    gets(score.student_id);
    // check id
    while(!check_number(score.student_id))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter students id  : ");
        gets(score.student_id );
    }

    printf("\n\t\t\t\tPlease enter lessons code : ");
    gets(score.lesson_code );
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

    department_head_edit_score_list(score.student_id , score.lesson_code , score.score);

    printf("\033[32m""\n\n\t\t\t\tscore edit successfully :)\n""\033[0m");

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }
}

// edit system for  students score from department head
void department_head_edit_score_list(char student_id[] , char lesson_code[] , char score[])
{
    struct student_score *s = malloc(sizeof(struct student_score));
    struct student_score *e = malloc(sizeof(struct student_score));
    struct student_score *d = NULL;
    struct student_score *temp = NULL;
    struct student_score *temp2 = NULL;

    score_file_ptr = fopen("scores_information.txt" , "r");

    fgets(s->student_id , sizeof(d->student_id) , score_file_ptr);
    fgets(s->lesson_code, sizeof(d->lesson_code) , score_file_ptr);
    fgets(s->score , sizeof(d->score) , score_file_ptr);
    fgets(s->date , sizeof(d->date) , score_file_ptr);
    fgets(s->time , sizeof(d->time) , score_file_ptr);
    fgets(s->user_name , sizeof(d->user_name) ,  score_file_ptr );

    fgets(e->student_id , sizeof(d->student_id) , score_file_ptr);
    fgets(e->lesson_code, sizeof(d->lesson_code) , score_file_ptr);
    fgets(e->score , sizeof(d->score) , score_file_ptr);
    fgets(e->date , sizeof(d->date) , score_file_ptr);
    fgets(e->time , sizeof(d->time) , score_file_ptr);
    fgets(e->user_name , sizeof(d->user_name) ,  score_file_ptr );

    s->link = e ;
    e->link = NULL ;


    while(feof(score_file_ptr) == 0)
    {
        d = malloc(sizeof(struct student_score));

        fgets(d->student_id , sizeof(d->student_id) , score_file_ptr);
        fgets(d->lesson_code, sizeof(d->lesson_code) , score_file_ptr);
        fgets(d->score , sizeof(d->score) , score_file_ptr);
        fgets(d->date , sizeof(d->date) , score_file_ptr);
        fgets(d->time , sizeof(d->time) , score_file_ptr);
        fgets(d->user_name , sizeof(d->user_name) ,  score_file_ptr );

        e->link = d ;
        e = d ;

    }
    e->link = NULL ;

    fclose(score_file_ptr);

    score_file_ptr = fopen("scores_information.txt" , "w");

    strcat(student_id , "\n");
    strcat(lesson_code , "\n");
    strcat(score , "\n");

    temp = s ;
    while(temp != NULL)
    {
        if(!strcmp(temp->student_id , student_id))
        {

            if(!strcmp(temp->lesson_code , lesson_code))
            {

                strcpy(temp->score , "");
                strcpy(temp->score , score );
            }
        }

        fprintf(score_file_ptr , "%s" , temp->student_id);
        fprintf(score_file_ptr , "%s" , temp->lesson_code);
        fprintf(score_file_ptr , "%s" , temp->score);
        fprintf(score_file_ptr , "%s" , temp->date);
        fprintf(score_file_ptr , "%s" , temp->time);
        fprintf(score_file_ptr , "%s" , temp->user_name);

        temp = temp->link ;


    }

    fclose(score_file_ptr);

    // delete link list
    temp2 = s ;
    temp = s->link ;
    while (temp != NULL)
    {

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    }

}

// department head edit lessons information page
void department_head_edit_lesson(struct department_head_information head)
{
    int head_choice = 0 ;
    char c[100] , enter;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|           EDIT LESSONS INFORMATION PAGE          |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\t1- Edit lessons name");
    printf("\n\t\t\t\t2- Edit lessons number fo unit");
    printf("\n\t\t\t\t3- Edit type of lesson");
    printf("\n\t\t\t\t4- Exit\n");

    printf("\n\t\t\t\tPlease enter your choice : ");
    scanf("%d" , &head_choice);
    getchar();
    // limit admin inputs
    while(head_choice <= 0 || head_choice > 4)
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter your choice : ");
        scanf("%d" , &head_choice);
        gets(c);
    }

    department_head_edit_lesson_menu_choice(head_choice , head);

}

// switch stracture for department head choice in edit lessons information page
void department_head_edit_lesson_menu_choice(int head_choice , struct department_head_information head)
{
    switch(head_choice)
    {
        case 1 :
        {
            department_head_edit_lessons_name_page(head);
            break;
        }
        case 2 :
        {
            department_head_edit_lessons_number_of_unit_page(head);
            break;
        }
        case 3 :
        {
            department_head_edit_lessons_type_page(head);
            break;
        }
        case 4 :
        {
            department_head_menu(head);
            break;
        }
    }
}

// edit lessons name page
void department_head_edit_lessons_name_page(struct department_head_information head)
{
    struct lesson_information lesson ;
    char enter ;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|              EDIT LESSONS NAME PAGE              |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter lessons code : ");
    gets(lesson.code);
    // check
    while(!check_number(lesson.code))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter lessons code : ");
        gets(lesson.code);
    }

    printf("\n\t\t\t\tPlease enter lessons new name : ");
    gets(lesson.name);
    // check
    while(!check_string(lesson.name))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter lessons new name : ");
        gets(lesson.name);
    }



    department_head_edit_lessons_list(lesson.code , "name" , lesson.name);

    printf("\033[32m""\n\n\t\t\t\tedit lessons name successfully complited :)\n""\033[0m");

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }
}

// edit lessons number of unit page
void department_head_edit_lessons_number_of_unit_page(struct department_head_information head)
{
    struct lesson_information lesson ;
    char enter ;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|         EDIT LESSONS NUMBER OF UNIT PAGE         |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter lessons code : ");
    gets(lesson.code);
    // check
    while(!check_number(lesson.code))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter lessons code : ");
        gets(lesson.code);
    }

    printf("\n\t\t\t\tPlease enter lessons new number of unit : ");
    gets(lesson.number_of_unit);
    // check
    while(!check_number(lesson.number_of_unit))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter lessons new number of unit : ");
        gets(lesson.number_of_unit);
    }



    department_head_edit_lessons_list(lesson.code , "number of unit" , lesson.number_of_unit);

    printf("\033[32m""\n\n\t\t\t\tedit lessons number of unit successfully complited :)\n""\033[0m");

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }
}

// edit lessons type page
void department_head_edit_lessons_type_page(struct department_head_information head)
{
    struct lesson_information lesson ;
    char enter ;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|              EDIT LESSONS TYPE PAGE              |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter lessons code : ");
    gets(lesson.code);
    // check
    while(!check_number(lesson.code))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter lessons code : ");
        gets(lesson.code);
    }

    printf("\n\t\t\t\tPlease enter lessons new type : ");
    gets(lesson.type);
    // check
    while(!check_string(lesson.type))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter lessons new type : ");
        gets(lesson.type);
    }



    department_head_edit_lessons_list(lesson.code , "type" , lesson.type);

    printf("\033[32m""\n\n\t\t\t\tedit lessons type successfully complited :)\n""\033[0m");

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }
}

// edit system for lessons information
void department_head_edit_lessons_list(char lesson_code[] , char type[] , char new[])
{
    struct lesson_information *s = malloc(sizeof(struct lesson_information));
    struct lesson_information *e = malloc(sizeof(struct lesson_information));
    struct lesson_information *d = NULL;
    struct lesson_information *temp = NULL;
    struct lesson_information *temp2 = NULL;

    lesson_file_ptr = fopen("lessons_information.txt" , "r");

    fscanf(lesson_file_ptr , "%s" , s->name);
    fscanf(lesson_file_ptr , "%s" , s->number_of_unit);
    fscanf(lesson_file_ptr , "%s" , s->type);
    fscanf(lesson_file_ptr , "%s" , s->code);
    fscanf(lesson_file_ptr , "%s" , s->status);

    fscanf(lesson_file_ptr , "%s" , e->name);
    fscanf(lesson_file_ptr , "%s" , e->number_of_unit);
    fscanf(lesson_file_ptr , "%s" , e->type);
    fscanf(lesson_file_ptr , "%s" , e->code);
    fscanf(lesson_file_ptr , "%s" , e->status);

    s->link = e ;
    e->link = NULL ;

    while(feof(lesson_file_ptr) == 0)
    {
        d = malloc(sizeof(struct lesson_information));

        fscanf(lesson_file_ptr , "%s" , d->name);
        fscanf(lesson_file_ptr , "%s" , d->number_of_unit);
        fscanf(lesson_file_ptr , "%s" , d->type);
        fscanf(lesson_file_ptr , "%s" , d->code);
        fscanf(lesson_file_ptr , "%s" , d->status);

        e->link = d ;
        e = d ;
    }
    e->link = NULL ;

    fclose(lesson_file_ptr);


    lesson_file_ptr = fopen("lessons_information.txt" , "w");

    if(!strcmp(type , "name"))
    {
        temp = s ;
        while(temp != NULL)
        {

            if(!strcmp(temp->code , lesson_code))
            {

                strcpy(temp->name , "");
                strcpy(temp->name , new);
            }
            if(temp == s)
                fprintf(lesson_file_ptr , "%s\n" , temp->name);
            else
                fprintf(lesson_file_ptr , "\n%s\n" , temp->name);
            fprintf(lesson_file_ptr , "%s\n" , temp->number_of_unit);
            fprintf(lesson_file_ptr , "%s\n" , temp->type);
            fprintf(lesson_file_ptr , "%s\n" , temp->code);
            fprintf(lesson_file_ptr , "%s" , temp->status);

            temp = temp->link ;
        }

    } else if(!strcmp(type , "number of unit"))
    {
        temp = s ;
        while(temp != NULL)
        {

            if(!strcmp(temp->code , lesson_code))
            {

                strcpy(temp->number_of_unit , "");
                strcpy(temp->number_of_unit , new);
            }

            if(temp == s)
                fprintf(lesson_file_ptr , "%s\n" , temp->name);
            else
                fprintf(lesson_file_ptr , "\n%s\n" , temp->name);
            fprintf(lesson_file_ptr , "%s\n" , temp->number_of_unit);
            fprintf(lesson_file_ptr , "%s\n" , temp->type);
            fprintf(lesson_file_ptr , "%s\n" , temp->code);
            fprintf(lesson_file_ptr , "%s" , temp->status);

            temp = temp->link ;
        }

    } else if(!strcmp(type , "type"))
    {
        temp = s ;
        while(temp != NULL)
        {

            if(!strcmp(temp->code , lesson_code))
            {

                strcpy(temp->type , "");
                strcpy(temp->type , new);
            }

            if(temp == s)
                fprintf(lesson_file_ptr , "%s\n" , temp->name);
            else
                fprintf(lesson_file_ptr , "\n%s\n" , temp->name);
            fprintf(lesson_file_ptr , "%s\n" , temp->number_of_unit);
            fprintf(lesson_file_ptr , "%s\n" , temp->type);
            fprintf(lesson_file_ptr , "%s\n" , temp->code);
            fprintf(lesson_file_ptr , "%s" , temp->status);


            temp = temp->link ;
        }

    }

    fclose(lesson_file_ptr);

    // delete link list
    temp2 = s ;
    temp = s->link ;
    while (temp != NULL)
    {

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    }
}

// delete lesson page
void department_head_delete_lesson_page(struct department_head_information head)
{
    struct lesson_information lesson ;
    char enter ;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|                DELETE LESSON PAGE                |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter lessons code : ");
    gets(lesson.code);
    // check
    while(!check_number(lesson.code))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter lessons code : ");
        gets(lesson.code);
    }



    department_head_delete_lesson_list(lesson.code);

    printf("\033[32m""\n\n\t\t\t\tlesson delete successfully :)\n""\033[0m");

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n');
}

//delete lesson
void department_head_delete_lesson_list(char lesson_code[]) 
{
    struct lesson_information *s = malloc(sizeof(struct lesson_information));
    struct lesson_information *e = malloc(sizeof(struct lesson_information));
    struct lesson_information *d = NULL;
    struct lesson_information *temp = NULL;
    struct lesson_information *temp2 = NULL;

    lesson_file_ptr = fopen("lessons_information.txt" , "r");

    fscanf(lesson_file_ptr , "%s" , s->name);
    fscanf(lesson_file_ptr , "%s" , s->number_of_unit);
    fscanf(lesson_file_ptr , "%s" , s->type);
    fscanf(lesson_file_ptr , "%s" , s->code);
    fscanf(lesson_file_ptr , "%s" , s->status);

    fscanf(lesson_file_ptr , "%s" , e->name);
    fscanf(lesson_file_ptr , "%s" , e->number_of_unit);
    fscanf(lesson_file_ptr , "%s" , e->type);
    fscanf(lesson_file_ptr , "%s" , e->code);
    fscanf(lesson_file_ptr , "%s" , e->status);

    s->link = e ;
    e->link = NULL ;

    while(feof(lesson_file_ptr) == 0)
    {
        d = malloc(sizeof(struct lesson_information));

        fscanf(lesson_file_ptr , "%s" , d->name);
        fscanf(lesson_file_ptr , "%s" , d->number_of_unit);
        fscanf(lesson_file_ptr , "%s" , d->type);
        fscanf(lesson_file_ptr , "%s" , d->code);
        fscanf(lesson_file_ptr , "%s" , d->status);

        e->link = d ;
        e = d ;
    }
    e->link = NULL ;

    fclose(lesson_file_ptr);


    lesson_file_ptr = fopen("lessons_information.txt" , "w");

    temp = s ;
    while(temp != NULL)
    {
        if(!strcmp(temp->code , lesson_code))
        {
            strcpy(temp->status , "");
            strcpy(temp->status , "unavailabe");
        }

        if(temp == s)
            fprintf(lesson_file_ptr , "%s\n" , temp->name);
        else
            fprintf(lesson_file_ptr , "\n%s\n" , temp->name);
        fprintf(lesson_file_ptr , "%s\n" , temp->number_of_unit);
        fprintf(lesson_file_ptr , "%s\n" , temp->type);
        fprintf(lesson_file_ptr , "%s\n" , temp->code);
        fprintf(lesson_file_ptr , "%s" , temp->status);
        temp = temp->link ;
    }

    fclose(lesson_file_ptr);

    deleted_lesson_file_ptr = fopen("deleted_lesson.txt" , "a");

    temp = s ;
    while(temp != NULL)
    {
        if(!strcmp(temp->code , lesson_code))
        {
            strcpy(temp->status , "");
            strcpy(temp->status , "unavailabe");
            if(temp == s)
                fprintf(lesson_file_ptr , "%s\n" , temp->name);
            else
                fprintf(lesson_file_ptr , "\n%s\n" , temp->name);
            fprintf(lesson_file_ptr , "%s\n" , temp->number_of_unit);
            fprintf(lesson_file_ptr , "%s\n" , temp->type);
            fprintf(lesson_file_ptr , "%s\n" , temp->code);
            fprintf(lesson_file_ptr , "%s" , temp->code);
        }

        temp = temp->link ;
    }

    fclose(deleted_lesson_file_ptr);

    // delete link list
    temp2 = s ;
    temp = s->link ;
    while (temp != NULL)
    {

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    }
}

// reports
void department_head_reports_page(struct department_head_information head)
{
    int head_choice = 0 ;
    char c[100];

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|           DEPARTMENT HEAD REPORTS PAGE           |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\t1- Find students information");
    printf("\n\t\t\t\t2- Students information list");
    printf("\n\t\t\t\t3- Lessons information list");
    printf("\n\t\t\t\t4- Deleted lessons list");
    printf("\n\t\t\t\t5- Available lessons list");
    printf("\n\t\t\t\t6- Find student scores");
    printf("\n\t\t\t\t7- Find students scores in special lesson");
    printf("\n\t\t\t\t8- Find students scores in special lesson (sorted)");
    printf("\n\t\t\t\t9- Find students average");
    printf("\n\t\t\t\t10- Find average of special lesson");
    printf("\n\t\t\t\t11- Students list sorted by average");
    printf("\n\t\t\t\t12- List of students who passed special lesson");
    printf("\n\t\t\t\t13- List of students who faild special lesson");
    printf("\n\t\t\t\t14- Conditional students list");
    printf("\n\t\t\t\t15- List of conditional students who heve taken a spesific lesson");
    printf("\n\t\t\t\t16- Exit\n");

    printf("\n\t\t\t\tPlease enter your choice : ");
    scanf("%d" , &head_choice);
    getchar();
    // limit department head inputs
    while(head_choice <= 0 || head_choice > 16)
    {
        printf("\033[31m""\n\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter your choice : ");
        scanf("%d" , &head_choice);
        gets(c);
    }

    department_head_reports_menu_choice(head_choice , head);
}

// switch structure for head choice in reports page
void department_head_reports_menu_choice(int head_choice , struct department_head_information head)
{
    switch(head_choice)
    {
        case 1 :
        {
            department_head_find_student_page(head);
            break;
        }
        case 2 :
        {
            department_head_student_list(head);
            break;
        }
        case 3 :
        {
            department_head_lesson_list(head , "all");
            break;
        }
        case 4 :
        {
            department_head_lesson_list(head , "unavailable");
            break;
        }
        case 5 :
        {
            department_head_lesson_list(head , "available");
            break;
        }
        case 6 :
        {
            department_head_student_scores_page(head);
            break;
        }
        case 7 :
        {
            department_head_students_scores_page(head);
            break;
        }
        case 8 :
        {
            department_head_sorted_students_scores_page(head);
            break;
        }
        case 9 :
        {
            department_head_student_average_page(head);
            break;
        }
        case 10 :
        {
            department_head_lesson_average_page(head);
            break;
        }
        case 11 :
        {
            department_head_students_average_list(head , "all");
            break;
        }
        case 12 :
        {
            department_head_passed_students_page(head);
            break;
        }
        case 13 :
        {
            department_head_failed_students_page(head);
            break;
        }
        case 14 :
        {
            department_head_students_average_list(head , "conditional");
            break;
        }
        case 15 :
        {
            department_head_conditional_students_list_take_lesson_page(head);
            break;
        }
        case 16 :
        {
            department_head_menu(head);
            break;
        }
        
    }
}

// find student information page
void department_head_find_student_page(struct department_head_information head)
{
    int head_choice = 0 ;
    char c[100];

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|  DEPARTMENT HEAD FIND STUDENTS INFORMATION PAGE  |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\t1- Find by name");
    printf("\n\t\t\t\t2- Find by id");
    printf("\n\t\t\t\t3- Exit\n");

    printf("\n\t\t\t\tPlease enter your choice : ");
    scanf("%d" , &head_choice);
    getchar();
    // limit department head inputs
    while(head_choice <= 0 || head_choice > 3)
    {
        printf("\033[31m""\n\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter your choice : ");
        scanf("%d" , &head_choice);
        gets(c);
    }

    department_head_find_student_menu_choice(head_choice , head);
}

// switch structure for head  choice in find student information page
void department_head_find_student_menu_choice(int head_choice , struct department_head_information head)
{
    switch(head_choice)
    {
        case 1 :
        {
            department_head_find_student_name_page(head);
            break;
        } 
        case 2 :
        {
            department_head_find_student_id_page(head);
            break;
        } 
        case 3 :
        {
            department_head_menu(head);
            break;
        } 
    }
}

// find student by name page
void department_head_find_student_name_page(struct department_head_information head)
{
    char  enter;
    struct student_information student , st;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|               FIND STUDENTS BY NAME              |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");


    printf("\n\t\t\t\tPlease enter students name : ");
    gets(student.name);
    // check name
    while(!check_string(student.name))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter students name : ");
        gets(student.name);
    }

    printf("\n\t\t\t\tPlease enter students family : ");
    gets(student.family);
    // check family
    while(!check_string(student.family))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter students family : ");
        gets(student.family);
    } 

    st = student_list(student.name , student.family , "");

    printf("\n\t\t\t\t+------------------------------------------------+");
    printf("\n\t\t\t\t| gender = %-37s |" , st.gender);
    printf("\n\t\t\t\t| name = %-39s |" , st.name);
    printf("\n\t\t\t\t| family = %-37s |" ,  st.family);
    printf("\n\t\t\t\t| code = %-39s |" , st.code);
    printf("\n\t\t\t\t| birth date = %4s/%2s/%-25s |" , st.birth_date.year , st.birth_date.month , st.birth_date.day);
    printf("\n\t\t\t\t| birth city = %-33s |" , st.birth_city);
    printf("\n\t\t\t\t| field of study = %-29s |" , st.field_of_study);
    printf("\n\t\t\t\t| id = %-41s |" , st.id);
    printf("\n\t\t\t\t| phone number = %-31s |" , st.phone_number);
    printf("\n\t\t\t\t| email = %-38s |" , st.email);
    printf("\n\t\t\t\t+------------------------------------------------+");
    

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }

}

// find student by id page
void department_head_find_student_id_page(struct department_head_information head)
{
    char  enter;
    struct student_information student , st;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|                FIND STUDENTS BY ID               |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");


    printf("\n\t\t\t\tPlease enter students id : ");
    gets(student.id);
    // check id
    while(!check_number(student.id))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter students id : ");
        gets(student.id);
    }

    st = student_list("" , "" , student.id);

    printf("\n\t\t\t\t+------------------------------------------------+");
    printf("\n\t\t\t\t| gender = %-37s |" , st.gender);
    printf("\n\t\t\t\t| name = %-39s |" , st.name);
    printf("\n\t\t\t\t| family = %-37s |" ,  st.family);
    printf("\n\t\t\t\t| code = %-39s |" , st.code);
    printf("\n\t\t\t\t| birth date = %4s/%2s/%-25s |" , st.birth_date.year , st.birth_date.month , st.birth_date.day);
    printf("\n\t\t\t\t| birth city = %-33s |" , st.birth_city);
    printf("\n\t\t\t\t| field of study = %-29s |" , st.field_of_study);
    printf("\n\t\t\t\t| id = %-41s |" , st.id);
    printf("\n\t\t\t\t| phone number = %-31s |" , st.phone_number);
    printf("\n\t\t\t\t| email = %-38s |" , st.email);
    printf("\n\t\t\t\t+------------------------------------------------+");
    

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }

}

// sudent information list
void department_head_student_list(struct department_head_information head)
{
     system("cls");

    int i = 0  , j = 0;
    char enter ;
    

    struct student_information *s = malloc(sizeof(struct student_information));
    struct student_information *e = malloc(sizeof(struct student_information));
    struct student_information *d = NULL;
    struct student_information *temp = NULL;
    struct student_information *temp2 = NULL;

    student_file_ptr = fopen("student_information.txt" , "r");

    fscanf(student_file_ptr , "%s" , s->gender);
    fscanf(student_file_ptr , "%s" , s->name);
    fscanf(student_file_ptr , "%s" , s->family);
    fscanf(student_file_ptr , "%s" , s->code);
    fscanf(student_file_ptr , "%4s/%2s/%2s" , s->birth_date.year , s->birth_date.month , s->birth_date.day);
    fscanf(student_file_ptr , "%s" , s->birth_city);
    fscanf(student_file_ptr , "%s" , s->field_of_study);
    fscanf(student_file_ptr , "%s" , s->id);
    fscanf(student_file_ptr , "%s" , s->phone_number);
    fscanf(student_file_ptr , "%s" , s->email);

    fscanf(student_file_ptr , "%s" , e->gender);
    fscanf(student_file_ptr , "%s" , e->name);
    fscanf(student_file_ptr , "%s" , e->family);
    fscanf(student_file_ptr , "%s" , e->code);
    fscanf(student_file_ptr , "%4s/%2s/%2s" , e->birth_date.year , e->birth_date.month , e->birth_date.day);
    fscanf(student_file_ptr , "%s" , e->birth_city);
    fscanf(student_file_ptr , "%s" , e->field_of_study);
    fscanf(student_file_ptr , "%s" , e->id);
    fscanf(student_file_ptr , "%s" , e->phone_number);
    fscanf(student_file_ptr , "%s" , e->email);

    s->link = e ;
    e->link = NULL ;

    //make link list
    while(feof(student_file_ptr) == 0)
    {
        d = malloc(sizeof(struct student_information));

        fscanf(student_file_ptr , "%s" , d->gender);
        fscanf(student_file_ptr , "%s" , d->name);
        fscanf(student_file_ptr , "%s" , d->family);
        fscanf(student_file_ptr , "%s" , d->code);
        fscanf(student_file_ptr , "%4s/%2s/%2s" , d->birth_date.year , d->birth_date.month , d->birth_date.day);
        fscanf(student_file_ptr , "%s" , d->birth_city);
        fscanf(student_file_ptr , "%s" , d->field_of_study);
        fscanf(student_file_ptr , "%s" , d->id);
        fscanf(student_file_ptr , "%s" , d->phone_number);
        fscanf(student_file_ptr , "%s" , d->email);

        e->link = d ;
        e = d ;
    }
    e->link = NULL ;

    fclose(student_file_ptr) ;

    printf("\n%c" , 201);
    for(i = 0 ; i < 164 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 187);

    printf("%c" , 186);
    printf("%78s%s%78s" , "" , "STUDENTS" , "");
    printf("%c\n" , 186);

    printf("%c" , 186);
    for(i = 0 ; i < 164 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 186);

    printf("%c" , 186);
    printf("%2s%c" , "" , 179);
    printf("%-7s%c" , "GENDER" , 179);
    printf("%-15s%c" , "NAME" , 179);
    printf("%-15s%c" , "FAMILY" , 179);
    printf("%-14s%c" , "CODE" , 179);
    printf("%-11s%c" , "BIRTH DATE" , 179);
    printf("%-14s%c" , "BIRTH CITY" , 179);
    printf("%-16s%c" , "FIELD OF STUDY" , 179);
    printf("%-13s%c" , "ID" , 179);
    printf("%-13s%c" , "PHONE NUMBER" , 179);
    printf("%-34s" , "EMAIL" );
    
    
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
        printf("%-15s%c" , temp->name , 179);
        printf("%-15s%c" , temp->family , 179);
        printf("%-14s%c" , temp->code , 179);
        printf("%4s/%2s/%2s%2c" , temp->birth_date.year , temp->birth_date.month , temp->birth_date.month ,  179);
        printf("%-14s%c" , temp->birth_city ,  179);
        printf("%-16s%c" , temp->field_of_study, 179);
        printf("%-13s%c" , temp->id, 179);
        printf("%-13s%c" , temp->phone_number , 179);
        printf("%-34s" , temp->email);
        
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

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    }

    
    // return to department head menu
    printf("\033[34m""\n    Please enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }
    

}

// lesson information list
void department_head_lesson_list(struct department_head_information head , char type[])
{
    system("cls");

    int i = 0  , j = 0;
    char enter ;
    

    struct lesson_information *s = malloc(sizeof(struct lesson_information));
    struct lesson_information *e = malloc(sizeof(struct lesson_information));
    struct lesson_information *d = NULL;
    struct lesson_information *temp = NULL;
    struct lesson_information *temp2 = NULL;

    student_file_ptr = fopen("lessons_information.txt" , "r");

    
    fscanf(student_file_ptr , "%s" , s->name);
    fscanf(student_file_ptr , "%s" , s->number_of_unit);
    fscanf(student_file_ptr , "%s" , s->type);
    fscanf(student_file_ptr , "%s" , s->code);
    fscanf(student_file_ptr , "%s" , s->status);

    fscanf(student_file_ptr , "%s" , e->name);
    fscanf(student_file_ptr , "%s" , e->number_of_unit);
    fscanf(student_file_ptr , "%s" , e->type);
    fscanf(student_file_ptr , "%s" , e->code);
    fscanf(student_file_ptr , "%s" , e->status);

    s->link = e ;
    e->link = NULL ;

    //make link list
    while(feof(student_file_ptr) == 0)
    {
        d = malloc(sizeof(struct student_information));

        fscanf(student_file_ptr , "%s" , d->name);
        fscanf(student_file_ptr , "%s" , d->number_of_unit);
        fscanf(student_file_ptr , "%s" , d->type);
        fscanf(student_file_ptr , "%s" , d->code);
        fscanf(student_file_ptr , "%s" , d->status);

        e->link = d ;
        e = d ;
    }
    e->link = NULL ;

    fclose(student_file_ptr) ;

    printf("\n\t\t\t%c" , 201);
    for(i = 0 ; i < 94 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 187);

    printf("\t\t\t%c" , 186);

    if(!strcmp(type , "all"))
        printf("%42s%s%41s" , "" , "ALL LESSONS" , "");
    else if(!strcmp(type , "unavailable"))
        printf("%38s%s%37s" , "" , "UNAVAILABLE LESSONS" , "");
    else if(!strcmp(type , "available"))
        printf("%39s%s%38s" , "" , "AVAILABLE LESSONS" , "");

    printf("%c\n" , 186);

    printf("\t\t\t%c" , 186);
    for(i = 0 ; i < 94 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 186);

    printf("\t\t\t%c" , 186);
    printf("%5s%c" , "" , 179);
    printf("%-20s%c" , "NAME" , 179);
    printf("%-15s%c" , "NUMBER OF UNIT" , 179);
    printf("%-15s%c" , "TYPE" , 179);
    printf("%-15s%c" , "CODE" , 179);
    printf("%-19s" , "STATUS" );
    
    
    printf("%c\n" , 186);

    printf("\t\t\t%c" , 186);
    for(i = 0 ; i < 94 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 186);

    if(!strcmp(type , "all"))
    {
        temp = s ;
        j = 1 ;
        // print tables data
        while(temp != NULL)
        {
            printf("\t\t\t%c" , 186);
            printf("%-5d%c" , j++ , 179);
            printf("%-20s%c" , temp->name , 179);
            printf("%-15s%c" , temp->number_of_unit, 179);
            printf("%-15s%c" , temp->type , 179);
            printf("%-15s%c" , temp->code , 179);
            printf("%-19s" , temp->status);

            printf("%c\n" , 186);

            printf("\t\t\t%c" , 186);
            for(i = 0 ; i < 94 ; i++)
                printf("%c" , 205);
            printf("%c\n" , 186);

            temp = temp->link ;
        }
    } else if(!strcmp(type , "unavailable"))
    {
        temp = s ;
        j = 1 ;
        // print tables data
        while(temp != NULL)
        {
            if(!strcmp(temp->status , "unavailable"))
            {
                printf("\t\t\t%c" , 186);
                printf("%-5d%c" , j++ , 179);
                printf("%-20s%c" , temp->name , 179);
                printf("%-15s%c" , temp->number_of_unit, 179);
                printf("%-15s%c" , temp->type , 179);
                printf("%-15s%c" , temp->code , 179);
                printf("%-19s" , temp->status);

                printf("%c\n" , 186);

                printf("\t\t\t%c" , 186);
                for(i = 0 ; i < 94 ; i++)
                    printf("%c" , 205);
                printf("%c\n" , 186);
            }

            temp = temp->link ;
        }
    } else if(!strcmp(type , "available"))
    {
        temp = s ;
        j = 1 ;
        // print tables data
        while(temp != NULL)
        {
            if(!strcmp(temp->status , "available"))
            {
                printf("\t\t\t%c" , 186);
                printf("%-5d%c" , j++ , 179);
                printf("%-20s%c" , temp->name , 179);
                printf("%-15s%c" , temp->number_of_unit, 179);
                printf("%-15s%c" , temp->type , 179);
                printf("%-15s%c" , temp->code , 179);
                printf("%-19s" , temp->status);
                
                printf("%c\n" , 186);
                
                printf("\t\t\t%c" , 186);
                for(i = 0 ; i < 94 ; i++)
                    printf("%c" , 205);
                printf("%c\n" , 186);
            }

            temp = temp->link ;
        }
    }

    printf("\t\t\t%c" , 186);
    printf("%94s" , "");
    printf("%c\n" , 186);

    printf("\t\t\t%c" , 200);
    for(i = 0 ; i < 94 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 188);

    // delete link list
    temp2 = s ;
    temp = s->link ;
    while (temp != NULL)
    {

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    }

    
    // return to department head menu
    printf("\033[34m""\n\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }
}

// find student scores page
void department_head_student_scores_page(struct department_head_information head)
{
    char  enter;
    struct student_information student;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|               FIND STUDENTS SCORES               |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");


    printf("\n\t\t\t\tPlease enter students id : ");
    gets(student.id);
    // check id
    while(!check_number(student.id))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter students id : ");
        gets(student.id);
    }

    department_head_students_scores_list(student.id , "" , "unsorted");

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }
} 

// student scores list
void department_head_students_scores_list(char student_id[] , char lesson_code[] , char type[])
{
    struct student_information student , student2 ;
    struct lesson_information lesson ;
    int i = 0 , j = 0  , n = 2;

    system("cls");

    struct student_score *s = malloc(sizeof(struct student_score)) ;
    struct student_score *e = malloc(sizeof(struct student_score)) ;
    struct student_score *d = NULL ;
    struct student_score *temp = NULL ;
    struct student_score *temp2 = NULL ;
    struct student_score *temp3 = NULL ;
    struct student_score *t = NULL ;
    
    score_file_ptr = fopen("scores_information.txt" , "r");

    fgets(s->student_id , sizeof(s->student_id) , score_file_ptr);
    fgets(s->lesson_code , sizeof(s->lesson_code) , score_file_ptr);
    fgets(s->score , sizeof(s->score) ,score_file_ptr);
    fgets(s->date , sizeof(s->date) , score_file_ptr);
    fgets(s->time , sizeof(s->time) , score_file_ptr);
    fgets(s->user_name , sizeof(s->user_name) , score_file_ptr);

    fgets(e->student_id , sizeof(e->student_id) , score_file_ptr);
    fgets(e->lesson_code , sizeof(e->lesson_code) , score_file_ptr);
    fgets(e->score , sizeof(e->score) ,score_file_ptr);
    fgets(e->date , sizeof(e->date) , score_file_ptr);
    fgets(e->time , sizeof(e->time) , score_file_ptr);
    fgets(e->user_name , sizeof(e->user_name) , score_file_ptr);

    s->link = e ;
    e->link = NULL ;

    while(feof(score_file_ptr) == 0)
    {
        d = malloc(sizeof(struct student_score)) ;

        fgets(d->student_id , sizeof(d->student_id) , score_file_ptr);
        fgets(d->lesson_code , sizeof(d->lesson_code) , score_file_ptr);
        fgets(d->score , sizeof(d->score) ,score_file_ptr);
        fgets(d->date , sizeof(d->date) , score_file_ptr);
        fgets(d->time , sizeof(d->time) , score_file_ptr);
        fgets(d->user_name , sizeof(d->user_name) , score_file_ptr);

        e->link = d ;
        e = d ;

        n++;
    }
    e->link = NULL ;

    fclose(score_file_ptr) ;

    temp = s ;
    while(temp != NULL)
    {

        temp->student_id[strcspn(temp->student_id , "\n")] = '\0' ;
        temp->lesson_code[strcspn(temp->lesson_code , "\n")] = '\0' ;
        temp->score[strcspn(temp->score , "\n")] = '\0' ;
        temp->date[strcspn(temp->date , "\n")] = '\0' ;
        temp->time[strcspn(temp->time , "\n")] = '\0' ;
        temp->user_name[strcspn(temp->user_name , "\n")] = '\0' ;

        temp = temp->link ;

    }

    temp = s ;

    //sort list
    if(!strcmp(type , "sorted"))
    {
        for(i = 0 ; i < n && temp != NULL ; i++)
        {
            temp = temp2 = s ;
            temp3 = s->link; 
            while(temp != NULL)
            {
                student = student_list("" , "" , temp->student_id);
                student2 = student_list("" , "" , temp3->student_id);

                if(strcmp(student.family , student2.family) > 0)
                {
                    if(temp == s)
                    {
                        temp->link = temp3->link ;
                        temp3->link = temp ;

                        temp3 = temp2 = s ;

                        t = temp ; 
                        temp = temp3 ;
                        temp3 = t ;
                    } else if(temp3 == e)
                    {
                        temp->link = temp3->link;
                        temp3->link = temp;
                        temp2->link = temp3;

                        t = temp ;
                        temp = temp3 ;
                        temp3 = t;

                        e = temp3 ;
                    } else
                    {
                        temp->link = temp3->link ;
                        temp3->link = temp ;
                        temp2->link = temp3 ;

                        t = temp ;
                        temp = temp3 ;
                        temp3 = t;
                    }
                }
                
                temp2 = temp ;
                temp = temp->link ;
                if(temp3->link != NULL)
                    temp3 = temp3->link ;
            }
        }
    }

    printf("\n\t\t\t%c" , 201);
    for(i = 0 ; i < 112 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 187);

    printf("\t\t\t%c" , 186);
    printf("%49s%s%49s" , "" , "STUDENT SCORES" , "");
    printf("%c\n" , 186);

    printf("\t\t\t%c" , 186);
    for(i = 0 ; i < 112 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 186);

    printf("\t\t\t%c" , 186);
    printf("%5s%c" , "" , 179);
    printf("%-7s%c" , "GENDER" , 179);
    printf("%-15s%c" , "NAME" , 179);
    printf("%-15s%c" , "FAMILY" , 179);
    printf("%-15s%c" , "ID" , 179);
    printf("%-18s%c" , "LESSONS CODE" , 179);
    printf("%-18s%c" , "LESSONS NAME" , 179);
    printf("%-12s" , "SCORE" , 179);
    
    
    printf("%c\n" , 186);

    printf("\t\t\t%c" , 186);
    for(i = 0 ; i < 112 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 186);

    temp = s ;
    j = 1 ;


    // print tables data
    while(temp != NULL)
    {
        if(!strcmp(temp->student_id , student_id) || !strcmp(temp->lesson_code , lesson_code))
        {
            student = student_list("" , "" , temp->student_id);
            lesson = lesson_list(temp->lesson_code);

            // for passed and faild student list part
            if(!strcmp(type , "pass"))
            {
                if(atoi(temp->score) < 10)
                {
                    temp = temp->link ;
                    continue;
                }
            } else if(!strcmp(type , "fail"))
            {
                if(atoi(temp->score) > 10)
                {
                    temp = temp->link ;
                    continue;
                }
            } 

            printf("\t\t\t%c" , 186);
            printf("%-5d%c" , j++ , 179);
            printf("%-7s%c" , student.gender , 179);
            printf("%-15s%c" , student.name , 179);
            printf("%-15s%c" , student.family , 179);
            printf("%-15s%c" , temp->student_id , 179);
            printf("%-18s%c" , temp->lesson_code, 179);
            printf("%-18s%c" , lesson.name, 179);
            printf("%-12s" , temp->score);
            
            printf("%c\n" , 186);

            printf("\t\t\t%c" , 186);
            for(i = 0 ; i < 112 ; i++)
                printf("%c" , 205);
            printf("%c\n" , 186);
        } 

        temp = temp->link ;


    }

    printf("\t\t\t%c" , 186);
    printf("%112s" , "");
    printf("%c\n" , 186);

    printf("\t\t\t%c" , 200);
    for(i = 0 ; i < 112 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 188);

    // delete link list
    temp2 = s ;
    temp = s->link ;
    while (temp != NULL)
    {

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    } 
}

// find students scores page
void department_head_students_scores_page(struct department_head_information head)
{
    char  enter;
    struct lesson_information lesson;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|               FIND STUDENTS SCORES               |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");


    printf("\n\t\t\t\tPlease enter lessons code : ");
    gets(lesson.code);
    // check id
    while(!check_number(lesson.code))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter lessons code : ");
        gets(lesson.code);
    }

    department_head_students_scores_list("" ,lesson.code , "unsorted");

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }
}

// find students scores page (sorted)
void department_head_sorted_students_scores_page(struct department_head_information head)
{
    char  enter;
    struct lesson_information lesson;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|               FIND STUDENTS SCORES               |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");


    printf("\n\t\t\t\tPlease enter lessons code : ");
    gets(lesson.code);
    // check id
    while(!check_number(lesson.code))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter lessons code : ");
        gets(lesson.code);
    }

    department_head_students_scores_list("" ,lesson.code , "sorted");

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }
}

// average of student scores
void department_head_student_average_page(struct department_head_information head)
{
    char  enter;
    struct student_information student , st;
    float ave = 0 ;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|               FIND STUDENTS AVERAGE              |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");


    printf("\n\t\t\t\tPlease enter students id : ");
    gets(student.id);
    // check id
    while(!check_number(student.id))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter students id : ");
        gets(student.id);
    }

    st = student_list("" , "" , student.id);

    ave = department_head_student_average(student.id);
   
    printf("\033[32m""\n\n\t\t\t\t+--------------------------------------------+");
    printf("\n\t\t\t\t| Gender = %-33s |" , st.gender);
    printf("\n\t\t\t\t| Name = %-35s |" , st.name);
    printf("\n\t\t\t\t| Family = %-33s |" , st.family);
    printf("\n\t\t\t\t| Average = %-32.2f |" , ave);
    printf("\n\t\t\t\t+--------------------------------------------+""\033[0m");

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }
}

// calculate students average
float department_head_student_average(char student_id[])
{
    int  sum = 0 , n = 0;
    float ave = 0 ;

    struct student_score *s = malloc(sizeof(struct student_score)) ;
    struct student_score *e = malloc(sizeof(struct student_score)) ;
    struct student_score *d = NULL ;
    struct student_score *temp = NULL ;
    struct student_score *temp2 = NULL ;
    
    score_file_ptr = fopen("scores_information.txt" , "r");

    fgets(s->student_id , sizeof(s->student_id) , score_file_ptr);
    fgets(s->lesson_code , sizeof(s->lesson_code) , score_file_ptr);
    fgets(s->score , sizeof(s->score) ,score_file_ptr);
    fgets(s->date , sizeof(s->date) , score_file_ptr);
    fgets(s->time , sizeof(s->time) , score_file_ptr);
    fgets(s->user_name , sizeof(s->user_name) , score_file_ptr);

    fgets(e->student_id , sizeof(e->student_id) , score_file_ptr);
    fgets(e->lesson_code , sizeof(e->lesson_code) , score_file_ptr);
    fgets(e->score , sizeof(e->score) ,score_file_ptr);
    fgets(e->date , sizeof(e->date) , score_file_ptr);
    fgets(e->time , sizeof(e->time) , score_file_ptr);
    fgets(e->user_name , sizeof(e->user_name) , score_file_ptr);

    s->link = e ;
    e->link = NULL ;

    while(feof(score_file_ptr) == 0)
    {
        d = malloc(sizeof(struct student_score)) ;

        fgets(d->student_id , sizeof(d->student_id) , score_file_ptr);
        fgets(d->lesson_code , sizeof(d->lesson_code) , score_file_ptr);
        fgets(d->score , sizeof(d->score) ,score_file_ptr);
        fgets(d->date , sizeof(d->date) , score_file_ptr);
        fgets(d->time , sizeof(d->time) , score_file_ptr);
        fgets(d->user_name , sizeof(d->user_name) , score_file_ptr);

        e->link = d ;
        e = d ;

    }
    e->link = NULL ;

    fclose(score_file_ptr) ;

    temp = s ;
    while(temp != NULL)
    {

        temp->student_id[strcspn(temp->student_id , "\n")] = '\0' ;
        temp->lesson_code[strcspn(temp->lesson_code , "\n")] = '\0' ;
        temp->score[strcspn(temp->score , "\n")] = '\0' ;
        temp->date[strcspn(temp->date , "\n")] = '\0' ;
        temp->time[strcspn(temp->time , "\n")] = '\0' ;
        temp->user_name[strcspn(temp->user_name , "\n")] = '\0' ;

        temp = temp->link ;

    }

    temp = s ;

    while(temp != NULL)
    {
        if(!strcmp(student_id , temp->student_id))
        {
            sum += atoi(temp->score);
            n++; 
        }

        temp = temp->link;
    }

    ave = (float)sum/n ;
    

    // delete link list
    temp2 = s ;
    temp = s->link ;
    while (temp != NULL)
    {

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    } 

    return ave ;
}

// average of lessons scores
void department_head_lesson_average_page(struct department_head_information head)
{
    char  enter;
    struct lesson_information lesson , les;
    float ave = 0 ;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|               FIND LESSONS AVERAGE               |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");


    printf("\n\t\t\t\tPlease enter lessons code : ");
    gets(lesson.code);
    // check code
    while(!check_number(lesson.code))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter lessons code : ");
        gets(lesson.code);
    }

    les = lesson_list(lesson.code);

    ave = department_head_lesson_average(lesson.code);
   
    printf("\033[32m""\n\n\t\t\t\t+--------------------------------------------+");
    printf("\n\t\t\t\t| Name = %-35s |" , les.name);
    printf("\n\t\t\t\t| Code = %-35s |" , les.code);
    printf("\n\t\t\t\t| Number of unit = %-25s |" , les.number_of_unit);
    printf("\n\t\t\t\t| Average = %-32.2f |" , ave);
    printf("\n\t\t\t\t+--------------------------------------------+""\033[0m");

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }
}

// calculate lessons average
float department_head_lesson_average(char lesson_code[])
{
    int  sum = 0 , n = 0;
    float ave = 0 ;

    struct student_score *s = malloc(sizeof(struct student_score)) ;
    struct student_score *e = malloc(sizeof(struct student_score)) ;
    struct student_score *d = NULL ;
    struct student_score *temp = NULL ;
    struct student_score *temp2 = NULL ;
    
    score_file_ptr = fopen("scores_information.txt" , "r");

    fgets(s->student_id , sizeof(s->student_id) , score_file_ptr);
    fgets(s->lesson_code , sizeof(s->lesson_code) , score_file_ptr);
    fgets(s->score , sizeof(s->score) ,score_file_ptr);
    fgets(s->date , sizeof(s->date) , score_file_ptr);
    fgets(s->time , sizeof(s->time) , score_file_ptr);
    fgets(s->user_name , sizeof(s->user_name) , score_file_ptr);

    fgets(e->student_id , sizeof(e->student_id) , score_file_ptr);
    fgets(e->lesson_code , sizeof(e->lesson_code) , score_file_ptr);
    fgets(e->score , sizeof(e->score) ,score_file_ptr);
    fgets(e->date , sizeof(e->date) , score_file_ptr);
    fgets(e->time , sizeof(e->time) , score_file_ptr);
    fgets(e->user_name , sizeof(e->user_name) , score_file_ptr);

    s->link = e ;
    e->link = NULL ;

    while(feof(score_file_ptr) == 0)
    {
        d = malloc(sizeof(struct student_score)) ;

        fgets(d->student_id , sizeof(d->student_id) , score_file_ptr);
        fgets(d->lesson_code , sizeof(d->lesson_code) , score_file_ptr);
        fgets(d->score , sizeof(d->score) ,score_file_ptr);
        fgets(d->date , sizeof(d->date) , score_file_ptr);
        fgets(d->time , sizeof(d->time) , score_file_ptr);
        fgets(d->user_name , sizeof(d->user_name) , score_file_ptr);

        e->link = d ;
        e = d ;

    }
    e->link = NULL ;

    fclose(score_file_ptr) ;

    temp = s ;
    while(temp != NULL)
    {

        temp->student_id[strcspn(temp->student_id , "\n")] = '\0' ;
        temp->lesson_code[strcspn(temp->lesson_code , "\n")] = '\0' ;
        temp->score[strcspn(temp->score , "\n")] = '\0' ;
        temp->date[strcspn(temp->date , "\n")] = '\0' ;
        temp->time[strcspn(temp->time , "\n")] = '\0' ;
        temp->user_name[strcspn(temp->user_name , "\n")] = '\0' ;

        temp = temp->link ;

    }

    temp = s ;

    while(temp != NULL)
    {
        if(!strcmp(lesson_code , temp->lesson_code))
        {
            sum += atoi(temp->score);
            n++; 
        }

        temp = temp->link;
    }

    ave = (float)sum/n ;
    

    // delete link list
    temp2 = s ;
    temp = s->link ;
    while (temp != NULL)
    {

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    } 

    return ave ;
}

// student average list page
void department_head_students_average_list(struct department_head_information head , char type[])
{
    int i = 0 , j = 0  , n = 2;
    char enter ;

    system("cls");

    struct student_information *s = malloc(sizeof(struct student_information)) ;
    struct student_information *e = malloc(sizeof(struct student_information)) ;
    struct student_information *d = NULL ;
    struct student_information *temp = NULL ;
    struct student_information *temp2 = NULL ;
    struct student_information *temp3 = NULL ;
    struct student_information *t = NULL ;
    
    student_file_ptr = fopen("student_information.txt" , "r");

    fscanf(student_file_ptr , "%s" , s->gender);
    fscanf(student_file_ptr , "%s" , s->name);
    fscanf(student_file_ptr , "%s" , s->family);
    fscanf(student_file_ptr , "%s" , s->code);
    fscanf(student_file_ptr , "%4s/%2s/%2s" , s->birth_date.year , s->birth_date.month , s->birth_date.day);
    fscanf(student_file_ptr , "%s" , s->birth_city);
    fscanf(student_file_ptr , "%s" , s->field_of_study);
    fscanf(student_file_ptr , "%s" , s->id);
    fscanf(student_file_ptr , "%s" , s->phone_number);
    fscanf(student_file_ptr , "%s" , s->email);

    fscanf(student_file_ptr , "%s" , e->gender);
    fscanf(student_file_ptr , "%s" , e->name);
    fscanf(student_file_ptr , "%s" , e->family);
    fscanf(student_file_ptr , "%s" , e->code);
    fscanf(student_file_ptr , "%4s/%2s/%2s" , e->birth_date.year , e->birth_date.month , e->birth_date.day);
    fscanf(student_file_ptr , "%s" , e->birth_city);
    fscanf(student_file_ptr , "%s" , e->field_of_study);
    fscanf(student_file_ptr , "%s" , e->id);
    fscanf(student_file_ptr , "%s" , e->phone_number);
    fscanf(student_file_ptr , "%s" , e->email);

    s->link = e ;
    e->link = NULL ;

    while(feof(student_file_ptr) == 0)
    {
        d = malloc(sizeof(struct student_information)) ;

        fscanf(student_file_ptr , "%s" , d->gender);
        fscanf(student_file_ptr , "%s" , d->name);
        fscanf(student_file_ptr , "%s" , d->family);
        fscanf(student_file_ptr , "%s" , d->code);
        fscanf(student_file_ptr , "%4s/%2s/%2s" , d->birth_date.year , d->birth_date.month , d->birth_date.day);
        fscanf(student_file_ptr , "%s" , d->birth_city);
        fscanf(student_file_ptr , "%s" , d->field_of_study);
        fscanf(student_file_ptr , "%s" , d->id);
        fscanf(student_file_ptr , "%s" , d->phone_number);
        fscanf(student_file_ptr , "%s" , d->email);

        e->link = d ;
        e = d ;

        n++;
    }
    e->link = NULL ;

    fclose(student_file_ptr) ;

   

    //sort list
    
    for(i = 0 ; i < n ; i++)
    {
        temp = temp2 = s ;
        temp3 = s->link; 
        while(temp != NULL)
        {
            if(department_head_student_average(temp->id) < department_head_student_average(temp3->id))
            {
                if(temp == s)
                {
                    temp->link = temp3->link ;
                    temp3->link = temp ;

                    temp2 = s = temp3 ;
                    
                    t = temp ; 
                    temp = temp3 ;
                    temp3 = t ;
                } else if(temp3 == e)
                {
                    temp->link = temp3->link;
                    temp3->link = temp;
                    temp2->link = temp3;

                    t = temp ;
                    temp = temp3 ;
                    temp3 = t;

                    e = temp3 ;
                } else
                {
                    temp->link = temp3->link ;
                    temp3->link = temp ;
                    temp2->link = temp3 ;

                    t = temp ;
                    temp = temp3 ;
                    temp3 = t;
                }
            }
            
            temp2 = temp ;
            temp = temp->link ;
            if(temp3->link != NULL)
                temp3 = temp3->link ;
        }
    }
    

    printf("\n\t\t\t%c" , 201);
    for(i = 0 ; i < 101 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 187);

    printf("\t\t\t%c" , 186);
    printf("%43s%s%43s" , "" , "STUDENT AVERAGE" , "");
    printf("%c\n" , 186);

    printf("\t\t\t%c" , 186);
    for(i = 0 ; i < 101 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 186);

    printf("\t\t\t%c" , 186);
    printf("%5s%c" , "" , 179);
    printf("%-7s%c" , "GENDER" , 179);
    printf("%-16s%c" , "NAME" , 179);
    printf("%-16s%c" , "FAMILY" , 179);
    printf("%-15s%c" , "ID" , 179);
    printf("%-20s%c" , "FIELD OF STUDENT" , 179);
    printf("%-16s" , "AVERAGE" , 179);
    
    
    printf("%c\n" , 186);

    printf("\t\t\t%c" , 186);
    for(i = 0 ; i < 101 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 186);

    temp = s ;
    j = 1 ;


    // print tables data
    while(temp != NULL)
    {
        // for conditional students list
        if(!strcmp(type , "conditional"))
        {
            if(department_head_student_average(temp->id) > 12)
            {
                temp = temp->link ;
                continue;
            }
        }

        printf("\t\t\t%c" , 186);
        printf("%-5d%c" , j++ , 179);
        printf("%-7s%c" , temp->gender , 179);
        printf("%-16s%c" , temp->name , 179);
        printf("%-16s%c" , temp->family , 179);
        printf("%-15s%c" , temp->id , 179);
        printf("%-20s%c" , temp->field_of_study, 179);
        printf("%-16f" , department_head_student_average(temp->id));
        
        printf("%c\n" , 186);

        printf("\t\t\t%c" , 186);
        for(i = 0 ; i < 101 ; i++)
            printf("%c" , 205);
        printf("%c\n" , 186);
        

        temp = temp->link ;


    }

    printf("\t\t\t%c" , 186);
    printf("%101s" , "");
    printf("%c\n" , 186);

    printf("\t\t\t%c" , 200);
    for(i = 0 ; i < 101 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 188);

    // delete link list
    temp2 = s ;
    temp = s->link ;
    while (temp != NULL)
    {

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    } 

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }
}

// list of passed students in special lesson
void department_head_passed_students_page(struct department_head_information head)
{
    char  enter;
    struct lesson_information lesson;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|               FIND PASSED STUDENTS               |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");


    printf("\n\t\t\t\tPlease enter lessons code : ");
    gets(lesson.code);
    // check id
    while(!check_number(lesson.code))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter lessons code : ");
        gets(lesson.code);
    }

    department_head_students_scores_list("" ,lesson.code , "pass");

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }
}

// list of faild students list in special lesson
void department_head_failed_students_page(struct department_head_information head)
{
    char  enter;
    struct lesson_information lesson;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|               FIND FAILED STUDENTS               |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");


    printf("\n\t\t\t\tPlease enter lessons code : ");
    gets(lesson.code);
    // check id
    while(!check_number(lesson.code))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter lessons code : ");
        gets(lesson.code);
    }

    department_head_students_scores_list("" ,lesson.code , "fail");

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }
}

// page for observe list of conditional studnts who taken special lesson 
void department_head_conditional_students_list_take_lesson_page(struct department_head_information head)
{
    char  enter;
    struct lesson_information lesson , les;
    float ave = 0 ;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|   FIND CONDITIONAL STUDENTS IN SPECIAL LESSON    |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter lessons code : ");
    gets(lesson.code);
    // check code
    while(!check_number(lesson.code))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter lessons code : ");
        gets(lesson.code);
    }

    department_head_conditional_students_list_take_lesson(lesson.code);

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }
}

// list of conditional studnts who taken special lesson
void department_head_conditional_students_list_take_lesson(char lesson_code[])
{
    struct lesson_information lesson ;
    struct student_information student ;
    int i = 0 , j = 0  , n = 2;
    
    lesson = lesson_list(lesson_code);

    system("cls");

    struct student_score *s = malloc(sizeof(struct student_score)) ;
    struct student_score *e = malloc(sizeof(struct student_score)) ;
    struct student_score *d = NULL ;
    struct student_score *temp = NULL ;
    struct student_score *temp2 = NULL ;
    
    score_file_ptr = fopen("scores_information.txt" , "r");

    fgets(s->student_id , sizeof(s->student_id) , score_file_ptr);
    fgets(s->lesson_code , sizeof(s->lesson_code) , score_file_ptr);
    fgets(s->score , sizeof(s->score) ,score_file_ptr);
    fgets(s->date , sizeof(s->date) , score_file_ptr);
    fgets(s->time , sizeof(s->time) , score_file_ptr);
    fgets(s->user_name , sizeof(s->user_name) , score_file_ptr);

    fgets(e->student_id , sizeof(e->student_id) , score_file_ptr);
    fgets(e->lesson_code , sizeof(e->lesson_code) , score_file_ptr);
    fgets(e->score , sizeof(e->score) ,score_file_ptr);
    fgets(e->date , sizeof(e->date) , score_file_ptr);
    fgets(e->time , sizeof(e->time) , score_file_ptr);
    fgets(e->user_name , sizeof(e->user_name) , score_file_ptr);

    s->link = e ;
    e->link = NULL ;

    while(feof(score_file_ptr) == 0)
    {
        d = malloc(sizeof(struct student_score)) ;

        fgets(d->student_id , sizeof(d->student_id) , score_file_ptr);
        fgets(d->lesson_code , sizeof(d->lesson_code) , score_file_ptr);
        fgets(d->score , sizeof(d->score) ,score_file_ptr);
        fgets(d->date , sizeof(d->date) , score_file_ptr);
        fgets(d->time , sizeof(d->time) , score_file_ptr);
        fgets(d->user_name , sizeof(d->user_name) , score_file_ptr);

        e->link = d ;
        e = d ;

        n++;
    }
    e->link = NULL ;

    fclose(score_file_ptr) ;

    temp = s ;
    while(temp != NULL)
    {

        temp->student_id[strcspn(temp->student_id , "\n")] = '\0' ;
        temp->lesson_code[strcspn(temp->lesson_code , "\n")] = '\0' ;
        temp->score[strcspn(temp->score , "\n")] = '\0' ;
        temp->date[strcspn(temp->date , "\n")] = '\0' ;
        temp->time[strcspn(temp->time , "\n")] = '\0' ;
        temp->user_name[strcspn(temp->user_name , "\n")] = '\0' ;

        temp = temp->link ;

    }

     printf("\n\t\t\t%c" , 201);
    for(i = 0 ; i < 112 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 187);

    printf("\t\t\t%c" , 186);
    printf("%49s%s%49s" , "" , "STUDENT SCORES" , "");
    printf("%c\n" , 186);

    printf("\t\t\t%c" , 186);
    for(i = 0 ; i < 112 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 186);

    printf("\t\t\t%c" , 186);
    printf("%5s%c" , "" , 179);
    printf("%-7s%c" , "GENDER" , 179);
    printf("%-15s%c" , "NAME" , 179);
    printf("%-15s%c" , "FAMILY" , 179);
    printf("%-15s%c" , "ID" , 179);
    printf("%-12s%c" , "AVERAGE" , 179);
    printf("%-18s%c" , "LESSONS NAME", 179);
    printf("%-18s" , "LESSONS CODE" );
    
    
    
    printf("%c\n" , 186);

    printf("\t\t\t%c" , 186);
    for(i = 0 ; i < 112 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 186);

    temp = s ;
    j = 1 ;


    // print tables data
    while(temp != NULL)
    {
        if(!strcmp(temp->lesson_code , lesson_code) && department_head_student_average(temp->student_id) < 12)
        {
            student = student_list("" , "" , temp->student_id);

            printf("\t\t\t%c" , 186);
            printf("%-5d%c" , j++ , 179);
            printf("%-7s%c" , student.gender , 179);
            printf("%-15s%c" , student.name , 179);
            printf("%-15s%c" , student.family , 179);
            printf("%-15s%c" , temp->student_id , 179);
            printf("%-12f%c" , department_head_student_average(temp->student_id) , 179);
            printf("%-18s%c" , lesson.name, 179);
            printf("%-18s" , lesson_code);
            
            printf("%c\n" , 186);

            printf("\t\t\t%c" , 186);
            for(i = 0 ; i < 112 ; i++)
                printf("%c" , 205);
            printf("%c\n" , 186);
        } 

        temp = temp->link ;


    }

    printf("\t\t\t%c" , 186);
    printf("%112s" , "");
    printf("%c\n" , 186);

    printf("\t\t\t%c" , 200);
    for(i = 0 ; i < 112 ; i++)
        printf("%c" , 205);
    printf("%c\n" , 188);

    // delete link list
    temp2 = s ;
    temp = s->link ;
    while (temp != NULL)
    {

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    } 
}

// department head setting page
void department_head_setting_page(struct department_head_information head)
{
    int head_choice = 0 ;
    char c[100];

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|           DEPARTMENT HEAD SETTING PAGE           |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\t1- Edit password");
    printf("\n\t\t\t\t2- Edit email");
    printf("\n\t\t\t\t3- Edit phone number");
    printf("\n\t\t\t\t4- Exit");
    

    printf("\n\t\t\t\tPlease enter your choice : ");
    scanf("%d" , &head_choice);
    getchar();
    // limit department head inputs
    while(head_choice <= 0 || head_choice > 4)
    {
        printf("\033[31m""\n\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter your choice : ");
        scanf("%d" , &head_choice);
        gets(c);
    }

    department_head_setting_menu_choice(head_choice , head);
}

// switch structure fo head choice in user setting page
void department_head_setting_menu_choice(int head_choice , struct department_head_information head)
{
    switch(head_choice)
    {
        case 1 : 
        {
            department_head_setting_password_page(head);
            break ;
        }
        case 2 : 
        {
            department_head_setting_email_page(head);
            break ;
        }
        case 3 : 
        {
            department_head_setting_phone_number_page(head);
            break ;
        }
        case 4 : 
        {
            department_head_menu(head);
            break;
        }
    }
}

// department head setting page (password)
void department_head_setting_password_page(struct department_head_information head)
{
    struct department_head_information hd ;
    char enter , confirm_password[50] ;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|        EDIT DEPARTMENT HEAD PASSEORD PAGE        |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter new password : ");
    gets(hd.password);

    printf("\n\t\t\t\tPlease confirm new password : ");
    gets(confirm_password);
    // check
    if(!strcmp(hd.password , confirm_password))
    {
        department_head_setting(head , "password" , hd.password);
        printf("\033[32m""\n\t\t\t\tYour password edit successfully :)\n""\033[0m");
    } else 
    {
        printf("\033[31m""\n\t\t\t\tERROR ! passwords not matched .\n""\033[0m");
    }

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }

}

// department head setting page (email)
void department_head_setting_email_page(struct department_head_information head)
{
    struct department_head_information hd ;
    char enter ;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|         EDIT DEPARTMENT HEAD EMAIL PAGE          |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter new email : ");
    gets(hd.email);
    //check
    while(!check_email(hd.email))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter new email : ");
        gets(hd.email);
    }
    
    
    department_head_setting(head , "email" , hd.email);
        
    printf("\033[32m""\n\t\t\t\tYour email edit successfully :)\n""\033[0m");
    

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }
}

// department head setting page (phone number)
void department_head_setting_phone_number_page(struct department_head_information head)
{
    struct department_head_information hd ;
    char enter ;

    system("cls");

    printf("%c department head name :  %s %s\n" , 240 , head.name , head.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|      EDIT DEPARTMENT HEAD PPHONE NUMBER PAGE     |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter new phone number : ");
    gets(hd.phone_number);
    //check
    while(!check_number(hd.phone_number))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter new phone number : ");
        gets(hd.phone_number);
    }
    
    
    department_head_setting(head , "phone number" , hd.phone_number);
        
    printf("\033[32m""\n\t\t\t\tYour phone number edit successfully :)\n""\033[0m");
    

    // return to department head page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        department_head_menu(head);
    }
}

//  department head setting
void department_head_setting(struct department_head_information head , char type[] , char new[])
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
    fscanf(head_file_ptr , "%s" , s->status);
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
    fscanf(head_file_ptr , "%s" , e->status);
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
        fscanf(head_file_ptr , "%s" , d->status);
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
        if(!strcmp(type , "password"))
        {
            if(!strcmp(temp->user_name , head.user_name))
            {
                strcpy(temp->password , "");
                strcpy(temp->password , new );
            }
        } else if(!strcmp(type , "email"))
        {
            if(!strcmp(temp->user_name , head.user_name))
            {
                strcpy(temp->email , "");
                strcpy(temp->email , new );
            }
        }  else if(!strcmp(type , "phone number"))
        {
            if(!strcmp(temp->user_name , head.user_name))
            {
                strcpy(temp->phone_number , "");
                strcpy(temp->phone_number , new );
            }
        }
        temp = temp->link ;
    }

    head_file_ptr = fopen("department_head_information.txt" , "w");

    temp = s ;
    while(temp != NULL)
    {   
        if(temp == s)
            fprintf(head_file_ptr , "%s\n" , temp->gender);
        else
            fprintf(head_file_ptr , "\n%s\n" , temp->gender);
        fprintf(head_file_ptr , "%s\n" , temp->name);
        fprintf(head_file_ptr , "%s\n" , temp->family);
        fprintf(head_file_ptr , "%4s/%2s/%2s\n" , temp->start_date.year , temp->start_date.month , temp->start_date.day);
        fprintf(head_file_ptr , "%s\n" , temp->group_name);
        fprintf(head_file_ptr , "%s\n" , temp->code);
        fprintf(head_file_ptr , "%s\n" , temp->phone_number);
        fprintf(head_file_ptr , "%s\n" , temp->email);
        fprintf(head_file_ptr , "%s\n" , temp->status);
        fprintf(head_file_ptr , "%s\n" , temp->user_name);
        fprintf(head_file_ptr , "%s" , temp->password);

        temp = temp->link ;
        
    }

    fclose(head_file_ptr);

    // delete link list
    temp2 = s ;
    temp = s->link ;
    while (temp != NULL)
    {

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

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
    strcpy(staff_password , star_password());
    while(strcmp(staff_password , "") == 0)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter your password : ");
        strcpy(staff_password , star_password());
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
    fscanf(staff_file_ptr , "%s" , s->status);
    fscanf(staff_file_ptr , "%s" , s->user_name);
    fscanf(staff_file_ptr , "%s" , s->password);

    fscanf(staff_file_ptr , "%s" , e->gender);
    fscanf(staff_file_ptr , "%s" , e->name);
    fscanf(staff_file_ptr , "%s" , e->family);
    fscanf(staff_file_ptr , "%4s/%2s/%2s" , e->start_date.year , e->start_date.month , e->start_date.day);
    fscanf(staff_file_ptr , "%s" , e->rank);
    fscanf(staff_file_ptr , "%s" , e->phone_number);
    fscanf(staff_file_ptr , "%s" , e->email);
    fscanf(staff_file_ptr , "%s" , e->status);
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
        fscanf(staff_file_ptr , "%s" , d->status);
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
           academic_staff_edit_students_information(staff);
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
            academic_staff_setting_page(staff);
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

    printf("\n\t\t\t\tPlease enter %s code : " , ch);
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
    while(check_number(student.birth_date.year) == 0 || strlen(student.birth_date.year) != 4)
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
    date(student.birth_date.month);

    printf("\n\t\t\t\tPlease enter %s birth day : " , ch);
    gets(student.birth_date.day);
    //check day
    while(check_number(student.birth_date.day) == 0 || strlen(student.birth_date.day) > 2)
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s birth day : " , ch);
        gets(student.birth_date.day);
    }
    date(student.birth_date.day);

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
    // check email
    while(!check_email(student.email))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter %s email : " , ch);
        gets(student.email);
    }
    


    printf("\033[32m""\n\t\t\t\tstudent log successfully complited :)\n""\033[0m");


    // print student information in file
    student_file_ptr = fopen("student_information.txt" , "a");

    fprintf(staff_file_ptr , "\n%s\n" , student.gender);
    fprintf(staff_file_ptr , "%s\n" , student.name);
    fprintf(staff_file_ptr , "%s\n" , student.family);
    fprintf(staff_file_ptr , "%s\n" , student.code);
    fprintf(staff_file_ptr , "%4s/%2s/%2s\n" , student.birth_date.year ,student.birth_date.month , student.birth_date.day);
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

// academic staff edit students information page
void academic_staff_edit_students_information(struct academic_staff_information staff)
{
    int staff_choice = 0 ;
    char c[100] , enter;

    system("cls");

    printf("%c academic staff name :  %s %s\n" , 240 , staff.name , staff.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|           EDIT STUDENTS INFORMATION PAGE         |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\t1- Edit studentds gender");
    printf("\n\t\t\t\t2- Edit students name");
    printf("\n\t\t\t\t3- Edit students family");
    printf("\n\t\t\t\t4- Edit students code");
    printf("\n\t\t\t\t5- Edit students birth_date");
    printf("\n\t\t\t\t6- Edit students birth_city");
    printf("\n\t\t\t\t7- Edit students field of study");
    printf("\n\t\t\t\t8- Edit students phone number");
    printf("\n\t\t\t\t9- Edit students email");
    printf("\n\t\t\t\t10- Exit\n");

    printf("\n\t\t\t\tPlease enter your choice : ");
    scanf("%d" , &staff_choice);
    getchar();
    // limit admin inputs
    while(staff_choice <= 0 || staff_choice > 10)
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter your choice : ");
        scanf("%d" , &staff_choice);
        gets(c);
    }

    academic_staff_edit_students_information_menu_choice(staff_choice , staff);

}

// switch structure for academic staff choices in edit students information page
void academic_staff_edit_students_information_menu_choice(int staff_choice , struct academic_staff_information staff)
{
    switch(staff_choice)
    {

        case 1 :
        {
            academic_staff_edit_students_gender_page( staff);
            break;
        }
        case 2 :
        {
           academic_staff_edit_students_name_page( staff);
            break;
        }
        case 3 :
        {
            academic_staff_edit_students_family_page( staff);
            break;
        }
        case 4 :
        {
            academic_staff_edit_students_code_page( staff);
            break;
        }
        case 5 :
        {
            academic_staff_edit_students_birth_date_page( staff);
            break;
        }
        case 6 :
        {
            academic_staff_edit_students_birth_city_page( staff);
            break;
        }
        case 7 :
        {
            academic_staff_edit_students_field_of_study_page( staff);
            break;
        }
        case 8 :
        {
            academic_staff_edit_students_phone_number_page( staff);
            break;
        }
        case 9 :
        {
            academic_staff_edit_students_email_page( staff);
            break;
        }
        case 10 :
        {
            academic_staff_menu(staff);
            break;
        }

    }
}

// edit students gender page
void academic_staff_edit_students_gender_page(struct academic_staff_information staff)
{
    struct student_information student ;
    char enter ;

    system("cls");

    printf("%c academic staff name :  %s %s\n" , 240 , staff.name , staff.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|             EDIT STUDENTS GENDER PAGE            |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter students id : ");
    gets(student.id);
    // check
    while(!check_number(student.id))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students id : ");
        gets(student.id);
    }

    printf("\n\t\t\t\tPlease enter students gender : ");
    gets(student.gender);
    // check
    while(check_string(student.gender) == 0 || ( strcmp(student.gender , "male") != 0 && strcmp(student.gender , "female") != 0 ) )
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students gender : ");
        gets(student.gender);
    }


    academic_staff_edit_students_information_list(student.id , "gender" , student.gender);

    printf("\033[32m""\n\n\t\t\t\tstudents gender edit successfully :)\n""\033[0m");

    // return to academic staff page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        academic_staff_menu(staff);
    }
}

// edit students name page
void academic_staff_edit_students_name_page(struct academic_staff_information staff)
{
    struct student_information student ;
    char enter ;

    system("cls");

    printf("%c academic staff name :  %s %s\n" , 240 , staff.name , staff.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|             EDIT STUDENTS NAME PAGE              |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter students id : ");
    gets(student.id);
    // check
    while(!check_number(student.id))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students id : ");
        gets(student.id);
    }

    printf("\n\t\t\t\tPlease enter students name : ");
    gets(student.name);
    // check
    while(!check_string(student.name))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students name : ");
        gets(student.name);
    }


    academic_staff_edit_students_information_list(student.id , "name" , student.name);

    printf("\033[32m""\n\n\t\t\t\tstudents name edit successfully :)\n""\033[0m");

    // return to academic staff page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        academic_staff_menu(staff);
    }
}

// edit students family page
void academic_staff_edit_students_family_page(struct academic_staff_information staff)
{
    struct student_information student ;
    char enter ;

    system("cls");

    printf("%c academic staff name :  %s %s\n" , 240 , staff.name , staff.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|             EDIT STUDENTS FAMILY PAGE            |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter students id : ");
    gets(student.id);
    // check
    while(!check_number(student.id))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students id : ");
        gets(student.id);
    }

    printf("\n\t\t\t\tPlease enter students family : ");
    gets(student.family);
    // check
    while(check_string(student.family) == 0)
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students family : ");
        gets(student.family);
    }


    academic_staff_edit_students_information_list(student.id , "family" , student.family);

    printf("\033[32m""\n\n\t\t\t\tstudents family edit successfully :)\n""\033[0m");

    // return to academic staff page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        academic_staff_menu(staff);
    }
}

// edit students code page
void academic_staff_edit_students_code_page(struct academic_staff_information staff)
{
    struct student_information student ;
    char enter ;

    system("cls");

    printf("%c academic staff name :  %s %s\n" , 240 , staff.name , staff.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|             EDIT STUDENTS CODE PAGE              |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter students id : ");
    gets(student.id);
    // check
    while(!check_number(student.id))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students id : ");
        gets(student.id);
    }

    printf("\n\t\t\t\tPlease enter students code : ");
    gets(student.code);
    // check
    while(check_number(student.code) == 0)
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students code : ");
        gets(student.code);
    }


    academic_staff_edit_students_information_list(student.id , "code" , student.code);

    printf("\033[32m""\n\n\t\t\t\tstudents code edit successfully :)\n""\033[0m");

    // return to academic staff page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        academic_staff_menu(staff);
    }
}

// edit students birth date page
void academic_staff_edit_students_birth_date_page(struct academic_staff_information staff)
{
    struct student_information student ;
    char enter , birth_date[50] ;

    system("cls");

    printf("%c academic staff name :  %s %s\n" , 240 , staff.name , staff.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|           EDIT STUDENTS BIRTH DATE PAGE          |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter students id : ");
    gets(student.id);
    // check
    while(!check_number(student.id))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students id : ");
        gets(student.id);
    }

    printf("\n\t\t\t\tPlease enter students year of birth : ");
    gets(student.birth_date.year);
    // check
    while(check_number(student.birth_date.year) == 0 || strlen(student.birth_date.year) != 4)
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students year of birth : ");
        gets(student.birth_date.year);
    }

    printf("\n\t\t\t\tPlease enter students month of birth : ");
    gets(student.birth_date.month);
    // check
    while(check_number(student.birth_date.month) == 0 || strlen(student.birth_date.month) > 2)
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students month of birth : ");
        gets(student.birth_date.month);
    }
    date(student.birth_date.month);

    printf("\n\t\t\t\tPlease enter students day of birth : ");
    gets(student.birth_date.day);
    // check
    while(check_number(student.birth_date.day) == 0 || strlen(student.birth_date.day) > 2)
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students day of birth : ");
        gets(student.birth_date.day);
    }
    date(student.birth_date.day);

    sprintf(birth_date , "%4s/%2s/%2s" , student.birth_date.year , student.birth_date.month , student.birth_date.day);

    academic_staff_edit_students_information_list(student.id , "birth date" , birth_date );

    printf("\033[32m""\n\n\t\t\t\tstudents birth date edit successfully :)\n""\033[0m");

    // return to academic staff page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        academic_staff_menu(staff);
    }
}

// edit students birth city page
void academic_staff_edit_students_birth_city_page(struct academic_staff_information staff)
{
    struct student_information student ;
    char enter ;

    system("cls");

    printf("%c academic staff name :  %s %s\n" , 240 , staff.name , staff.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|           EDIT STUDENTS BIRTH CITY PAGE          |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter students id : ");
    gets(student.id);
    // check
    while(!check_number(student.id))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students id : ");
        gets(student.id);
    }

    printf("\n\t\t\t\tPlease enter students birth city : ");
    gets(student.birth_city);
    // check
    while(check_string(student.birth_city) == 0)
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students birth city : ");
        gets(student.birth_city);
    }


    academic_staff_edit_students_information_list(student.id , "birth city" , student.birth_city);

    printf("\033[32m""\n\n\t\t\t\tstudents birth city edit successfully :)\n""\033[0m");

    // return to academic staff page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        academic_staff_menu(staff);
    }
}

// edit students field of study page
void academic_staff_edit_students_field_of_study_page(struct academic_staff_information staff)
{
    struct student_information student ;
    char enter ;

    system("cls");

    printf("%c academic staff name :  %s %s\n" , 240 , staff.name , staff.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|         EDIT STUDENTS FIELD OF STUDY PAGE        |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter students id : ");
    gets(student.id);
    // check
    while(!check_number(student.id))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students id : ");
        gets(student.id);
    }

    printf("\n\t\t\t\tPlease enter students field of study : ");
    gets(student.field_of_study);
    // check
    while(check_string(student.field_of_study) == 0)
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students field of study : ");
        gets(student.field_of_study);
    }


    academic_staff_edit_students_information_list(student.id , "field of study" , student.field_of_study);

    printf("\033[32m""\n\n\t\t\t\tstudents field of study edit successfully :)\n""\033[0m");

    // return to academic staff page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        academic_staff_menu(staff);
    }
}

// edit students phone number page
void academic_staff_edit_students_phone_number_page(struct academic_staff_information staff)
{
    struct student_information student ;
    char enter ;

    system("cls");

    printf("%c academic staff name :  %s %s\n" , 240 , staff.name , staff.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|          EDIT STUDENTS PHONE NUMBER PAGE         |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter students id : ");
    gets(student.id);
    // check
    while(!check_number(student.id))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students id : ");
        gets(student.id);
    }

    printf("\n\t\t\t\tPlease enter students phone number : ");
    gets(student.phone_number);
    // check
    while(check_number(student.phone_number) == 0)
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students phone number : ");
        gets(student.phone_number);
    }


    academic_staff_edit_students_information_list(student.id , "phone number" , student.phone_number);

    printf("\033[32m""\n\n\t\t\t\tstudents phone number edit successfully :)\n""\033[0m");

    // return to academic staff page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        academic_staff_menu(staff);
    }
}

// edit students email page
void academic_staff_edit_students_email_page(struct academic_staff_information staff)
{
    struct student_information student ;
    char enter ;

    system("cls");

    printf("%c academic staff name :  %s %s\n" , 240 , staff.name , staff.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|             EDIT STUDENTS EMAIL PAGE             |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter students id : ");
    gets(student.id);
    // check
    while(!check_number(student.id))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter students id : ");
        gets(student.id);
    }

    printf("\n\t\t\t\tPlease enter students email : ");
    gets(student.email);
    // check email
    while(!check_email(student.email))
    {
        printf("\033[31m""\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter  email : ");
        gets(student.email);
    }
    


    academic_staff_edit_students_information_list(student.id , "email" , student.email);

    printf("\033[32m""\n\n\t\t\t\tstudents email edit successfully :)\n""\033[0m");

    // return to academic staff page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        academic_staff_menu(staff);
    }
}

// edit system for students information
void academic_staff_edit_students_information_list(char students_id[] , char type[] , char new[])
{
    struct student_information *s = malloc(sizeof(struct student_information));
    struct student_information *e = malloc(sizeof(struct student_information));
    struct student_information *d = NULL ;
    struct student_information *temp = NULL ;
    struct student_information *temp2 = NULL ;

    student_file_ptr = fopen("student_information.txt" , "r");

    fscanf(student_file_ptr , "%s" , s->gender);
    fscanf(student_file_ptr , "%s" , s->name);
    fscanf(student_file_ptr , "%s" , s->family);
    fscanf(student_file_ptr , "%s" , s->code);
    fscanf(student_file_ptr , "%4s/%2s/%2s" , s->birth_date.year  , s->birth_date.month , s->birth_date.day);
    fscanf(student_file_ptr , "%s" , s->birth_city);
    fscanf(student_file_ptr , "%s" , s->field_of_study);
    fscanf(student_file_ptr , "%s" , s->id);
    fscanf(student_file_ptr , "%s" , s->phone_number);
    fscanf(student_file_ptr , "%s" , s->email);

    fscanf(student_file_ptr , "%s" , e->gender);
    fscanf(student_file_ptr , "%s" , e->name);
    fscanf(student_file_ptr , "%s" , e->family);
    fscanf(student_file_ptr , "%s" , e->code);
    fscanf(student_file_ptr , "%4s/%2s/%2s" , e->birth_date.year  , e->birth_date.month , e->birth_date.day);
    fscanf(student_file_ptr , "%s" , e->birth_city);
    fscanf(student_file_ptr , "%s" , e->field_of_study);
    fscanf(student_file_ptr , "%s" , e->id);
    fscanf(student_file_ptr , "%s" , e->phone_number);
    fscanf(student_file_ptr , "%s" , e->email);

    s->link = e ;
    e->link = NULL ;

    while(feof(student_file_ptr) == 0)
    {
        d = malloc(sizeof(struct student_information));

        fscanf(student_file_ptr , "%s" , d->gender);
        fscanf(student_file_ptr , "%s" , d->name);
        fscanf(student_file_ptr , "%s" , d->family);
        fscanf(student_file_ptr , "%s" , d->code);
        fscanf(student_file_ptr , "%4s/%2s/%2s" , d->birth_date.year  , d->birth_date.month , d->birth_date.day);
        fscanf(student_file_ptr , "%s" , d->birth_city);
        fscanf(student_file_ptr , "%s" , d->field_of_study);
        fscanf(student_file_ptr , "%s" , d->id);
        fscanf(student_file_ptr , "%s" , d->phone_number);
        fscanf(student_file_ptr , "%s" , d->email);

        e->link = d ;
        e = d ;
    }
    e->link = NULL ;

    fclose(student_file_ptr);

    student_file_ptr = fopen("student_information.txt" , "w");

    if(!strcmp(type , "gender"))
    {
        temp = s ;
        while(temp != NULL)
        {
            if(!strcmp(temp->id , students_id))
            {
                strcpy(temp->gender , "");
                strcpy(temp->gender , new);
            }

            fprintf(student_file_ptr , "%s\n" , temp->gender);
            fprintf(student_file_ptr , "%s\n" , temp->name);
            fprintf(student_file_ptr , "%s\n" , temp->family);
            fprintf(student_file_ptr , "%s\n" , temp->code);
            fprintf(student_file_ptr , "%4s/%2s/%2s\n" , temp->birth_date.year  , temp->birth_date.month , temp->birth_date.day);
            fprintf(student_file_ptr , "%s\n" , temp->birth_city);
            fprintf(student_file_ptr , "%s\n" , temp->field_of_study);
            fprintf(student_file_ptr , "%s\n" , temp->id);
            fprintf(student_file_ptr , "%s\n" , temp->phone_number);
            fprintf(student_file_ptr , "%s\n" , temp->email);


            temp = temp->link ;
        }
    } else if(!strcmp(type , "name"))
    {
        temp = s ;
        while(temp != NULL)
        {
            if(!strcmp(temp->id , students_id))
            {
                strcpy(temp->name , "");
                strcpy(temp->name , new);
            }

            fprintf(student_file_ptr , "%s\n" , temp->gender);
            fprintf(student_file_ptr , "%s\n" , temp->name);
            fprintf(student_file_ptr , "%s\n" , temp->family);
            fprintf(student_file_ptr , "%s\n" , temp->code);
            fprintf(student_file_ptr , "%4s/%2s/%2s\n" , temp->birth_date.year  , temp->birth_date.month , temp->birth_date.day);
            fprintf(student_file_ptr , "%s\n" , temp->birth_city);
            fprintf(student_file_ptr , "%s\n" , temp->field_of_study);
            fprintf(student_file_ptr , "%s\n" , temp->id);
            fprintf(student_file_ptr , "%s\n" , temp->phone_number);
            fprintf(student_file_ptr , "%s\n" , temp->email);


            temp = temp->link ;
        }
    }  else if(!strcmp(type , "family"))
    {
        temp = s ;
        while(temp != NULL)
        {
            if(!strcmp(temp->id , students_id))
            {
                strcpy(temp->family , "");
                strcpy(temp->family , new);
            }

            fprintf(student_file_ptr , "%s\n" , temp->gender);
            fprintf(student_file_ptr , "%s\n" , temp->name);
            fprintf(student_file_ptr , "%s\n" , temp->family);
            fprintf(student_file_ptr , "%s\n" , temp->code);
            fprintf(student_file_ptr , "%4s/%2s/%2s\n" , temp->birth_date.year  , temp->birth_date.month , temp->birth_date.day);
            fprintf(student_file_ptr , "%s\n" , temp->birth_city);
            fprintf(student_file_ptr , "%s\n" , temp->field_of_study);
            fprintf(student_file_ptr , "%s\n" , temp->id);
            fprintf(student_file_ptr , "%s\n" , temp->phone_number);
            fprintf(student_file_ptr , "%s\n" , temp->email);


            temp = temp->link ;
        }
    }  else if(!strcmp(type , "code"))
    {
        temp = s ;
        while(temp != NULL)
        {
            if(!strcmp(temp->id , students_id))
            {
                strcpy(temp->code , "");
                strcpy(temp->code , new);
            }

            fprintf(student_file_ptr , "%s\n" , temp->gender);
            fprintf(student_file_ptr , "%s\n" , temp->name);
            fprintf(student_file_ptr , "%s\n" , temp->family);
            fprintf(student_file_ptr , "%s\n" , temp->code);
            fprintf(student_file_ptr , "%4s/%2s/%2s\n" , temp->birth_date.year  , temp->birth_date.month , temp->birth_date.day);
            fprintf(student_file_ptr , "%s\n" , temp->birth_city);
            fprintf(student_file_ptr , "%s\n" , temp->field_of_study);
            fprintf(student_file_ptr , "%s\n" , temp->id);
            fprintf(student_file_ptr , "%s\n" , temp->phone_number);
            fprintf(student_file_ptr , "%s\n" , temp->email);


            temp = temp->link ;
        }
    }  else if(!strcmp(type , "birth date"))
    {
        temp = s ;
        while(temp != NULL)
        {
            if(!strcmp(temp->id , students_id))
            {
                strcpy(temp->birth_date.year , "");
                strcpy(temp->birth_date.month , "");
                strcpy(temp->birth_date.day , "");
                sscanf(new , "%4s/%2s/%2s" , temp->birth_date.year , temp->birth_date.month ,temp->birth_date.day);
                
            }

            fprintf(student_file_ptr , "%s\n" , temp->gender);
            fprintf(student_file_ptr , "%s\n" , temp->name);
            fprintf(student_file_ptr , "%s\n" , temp->family);
            fprintf(student_file_ptr , "%s\n" , temp->code);
            fprintf(student_file_ptr , "%s/%s/%s\n" , temp->birth_date.year  , temp->birth_date.month , temp->birth_date.day);
            fprintf(student_file_ptr , "%s\n" , temp->birth_city);
            fprintf(student_file_ptr , "%s\n" , temp->field_of_study);
            fprintf(student_file_ptr , "%s\n" , temp->id);
            fprintf(student_file_ptr , "%s\n" , temp->phone_number);
            fprintf(student_file_ptr , "%s\n" , temp->email);


            temp = temp->link ;
        }
    } else if(!strcmp(type , "birth city"))
    {
        temp = s ;
        while(temp != NULL)
        {
            if(!strcmp(temp->id , students_id))
            {
                strcpy(temp->birth_city , "");
                strcpy(temp->birth_city , new);
            }

            fprintf(student_file_ptr , "%s\n" , temp->gender);
            fprintf(student_file_ptr , "%s\n" , temp->name);
            fprintf(student_file_ptr , "%s\n" , temp->family);
            fprintf(student_file_ptr , "%s\n" , temp->code);
            fprintf(student_file_ptr , "%4s/%2s/%2s\n" , temp->birth_date.year  , temp->birth_date.month , temp->birth_date.day);
            fprintf(student_file_ptr , "%s\n" , temp->birth_city);
            fprintf(student_file_ptr , "%s\n" , temp->field_of_study);
            fprintf(student_file_ptr , "%s\n" , temp->id);
            fprintf(student_file_ptr , "%s\n" , temp->phone_number);
            fprintf(student_file_ptr , "%s\n" , temp->email);


            temp = temp->link ;
        }
    } else if(!strcmp(type , "field of study"))
    {
        temp = s ;
        while(temp != NULL)
        {
            if(!strcmp(temp->id , students_id))
            {
                strcpy(temp->field_of_study , "");
                strcpy(temp->field_of_study , new);
            }

            fprintf(student_file_ptr , "%s\n" , temp->gender);
            fprintf(student_file_ptr , "%s\n" , temp->name);
            fprintf(student_file_ptr , "%s\n" , temp->family);
            fprintf(student_file_ptr , "%s\n" , temp->code);
            fprintf(student_file_ptr , "%4s/%2s/%2s\n" , temp->birth_date.year  , temp->birth_date.month , temp->birth_date.day);
            fprintf(student_file_ptr , "%s\n" , temp->birth_city);
            fprintf(student_file_ptr , "%s\n" , temp->field_of_study);
            fprintf(student_file_ptr , "%s\n" , temp->id);
            fprintf(student_file_ptr , "%s\n" , temp->phone_number);
            fprintf(student_file_ptr , "%s\n" , temp->email);


            temp = temp->link ;
        }
    } else if(!strcmp(type , "phone number"))
    {
        temp = s ;
        while(temp != NULL)
        {
            if(!strcmp(temp->id , students_id))
            {
                strcpy(temp->phone_number , "");
                strcpy(temp->phone_number , new);
            }

            fprintf(student_file_ptr , "%s\n" , temp->gender);
            fprintf(student_file_ptr , "%s\n" , temp->name);
            fprintf(student_file_ptr , "%s\n" , temp->family);
            fprintf(student_file_ptr , "%s\n" , temp->code);
            fprintf(student_file_ptr , "%4s/%2s/%2s\n" , temp->birth_date.year  , temp->birth_date.month , temp->birth_date.day);
            fprintf(student_file_ptr , "%s\n" , temp->birth_city);
            fprintf(student_file_ptr , "%s\n" , temp->field_of_study);
            fprintf(student_file_ptr , "%s\n" , temp->id);
            fprintf(student_file_ptr , "%s\n" , temp->phone_number);
            fprintf(student_file_ptr , "%s\n" , temp->email);


            temp = temp->link ;
        }
    } else if(!strcmp(type , "email"))
    {
        temp = s ;
        while(temp != NULL)
        {
            if(!strcmp(temp->id , students_id))
            {
                strcpy(temp->email , "");
                strcpy(temp->email , new);
            }

            fprintf(student_file_ptr , "%s\n" , temp->gender);
            fprintf(student_file_ptr , "%s\n" , temp->name);
            fprintf(student_file_ptr , "%s\n" , temp->family);
            fprintf(student_file_ptr , "%s\n" , temp->code);
            fprintf(student_file_ptr , "%4s/%2s/%2s\n" , temp->birth_date.year  , temp->birth_date.month , temp->birth_date.day);
            fprintf(student_file_ptr , "%s\n" , temp->birth_city);
            fprintf(student_file_ptr , "%s\n" , temp->field_of_study);
            fprintf(student_file_ptr , "%s\n" , temp->id);
            fprintf(student_file_ptr , "%s\n" , temp->phone_number);
            fprintf(student_file_ptr , "%s\n" , temp->email);


            temp = temp->link ;
        }
    }


    fclose(staff_file_ptr);

    // delete link list
    temp2 = s ;
    temp = s->link ;
    while (temp != NULL)
    {

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

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
    fprintf(score_file_ptr , "%s\n" , __TIME__);
    fprintf( score_file_ptr ,"%s %s" , staff.name , staff.family);

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

// academic staff setting page
void academic_staff_setting_page(struct academic_staff_information staff)
{
    int staff_choice = 0 ;
    char c[100];

    system("cls");

    printf("%c academic staff name :  %s %s\n" , 240 , staff.name , staff.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|            ACADEMIC STAFF SETTING PAGE           |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\t1- Edit password");
    printf("\n\t\t\t\t2- Edit email");
    printf("\n\t\t\t\t3- Edit phone number");
    printf("\n\t\t\t\t4- Exit");
    

    printf("\n\t\t\t\tPlease enter your choice : ");
    scanf("%d" , &staff_choice);
    getchar();
    // limit academic staff inputs
    while(staff_choice <= 0 || staff_choice > 4)
    {
        printf("\033[31m""\n\t\t\t\tERROR !""\033[0m");
        printf("\n\t\t\t\tPlease enter your choice : ");
        scanf("%d" , &staff_choice);
        gets(c);
    }

    academic_staff_setting_menu_choice(staff_choice , staff);
}

// switch structure fo staff choice in user setting page
void academic_staff_setting_menu_choice(int staff_choice , struct academic_staff_information staff)
{
    switch(staff_choice)
    {
        case 1 : 
        {
            academic_staff_setting_password_page(staff);
            break ;
        }
        case 2 : 
        {
            academic_staff_setting_email_page(staff);
            break ;
        }
        case 3 : 
        {
            academic_staff_setting_phone_number_page(staff);
            break ;
        }
        case 4 : 
        {
            academic_staff_menu(staff);
            break;
        }
    }
}

// academic staff setting page (password)
void academic_staff_setting_password_page(struct academic_staff_information staff)
{
    struct academic_staff_information st ;
    char enter , confirm_password[50] ;

    system("cls");

    printf("%c academic staff name :  %s %s\n" , 240 , staff.name , staff.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|        EDIT ACADEMIC STAFF PASSEORD PAGE         |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter new password : ");
    gets(st.password);

    printf("\n\t\t\t\tPlease confirm new password : ");
    gets(confirm_password);
    // check
    if(!strcmp(st.password , confirm_password))
    {
        academic_staff_setting(staff , "password" , st.password);
        printf("\033[32m""\n\t\t\t\tYour password edit successfully :)\n""\033[0m");
    } else 
    {
        printf("\033[31m""\n\t\t\t\tERROR ! passwords not matched .\n""\033[0m");
    }

    // return to academic staff page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        academic_staff_menu(staff);
    }

}

// academic setting page (email)
void academic_staff_setting_email_page(struct academic_staff_information staff)
{
    struct academic_staff_information st ;
    char enter ;

    system("cls");

    printf("%c academic staff name :  %s %s\n" , 240 , staff.name , staff.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|         EDIT ACADEMIC STAFF EMAIL PAGE           |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter new email : ");
    gets(st.email);
    //check
    while(!check_email(st.email))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter new email : ");
        gets(st.email);
    }
    
    
    academic_staff_setting(staff , "email" , st.email);
        
    printf("\033[32m""\n\t\t\t\tYour email edit successfully :)\n""\033[0m");
    

    // return to academic staff page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        academic_staff_menu(staff);
    }
}

// academic staff setting page (phone number)
void academic_staff_setting_phone_number_page(struct academic_staff_information staff)
{
    struct academic_staff_information st ;
    char enter ;

    system("cls");

    printf("%c academic staff name :  %s %s\n" , 240 , staff.name , staff.family);

    printf("\033[34m""\n\t\t\t\t+--------------------------------------------------+");
    printf("\n\t\t\t\t|      EDIT ACADEMIC STAFF PPHONE NUMBER PAGE      |");
    printf("\n\t\t\t\t+--------------------------------------------------+\n\n""\033[0m");

    printf("\n\t\t\t\tPlease enter new phone number : ");
    gets(st.phone_number);
    //check
    while(!check_number(st.phone_number))
    {
        printf("\033[31m""\n\t\t\t\tERROR !\n""\033[0m");
        printf("\n\t\t\t\tPlease enter new phone number : ");
        gets(st.phone_number);
    }
    
    
    academic_staff_setting(staff , "phone number" , st.phone_number);
        
    printf("\033[32m""\n\t\t\t\tYour phone number edit successfully :)\n""\033[0m");
    

    // return to academic staff page menu
    printf("\033[34m""\n\n\t\t\t\tPlease enter to continue ....""\033[0m");
    enter = getchar();
    if(enter == '\n')
    {
        academic_staff_menu(staff);
    }
}

//  academic staff setting
void academic_staff_setting(struct academic_staff_information head , char type[] , char new[])
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
    fscanf(staff_file_ptr , "%s" , s->status);
    fscanf(staff_file_ptr , "%s" , s->user_name);
    fscanf(staff_file_ptr , "%s" , s->password);

    fscanf(staff_file_ptr , "%s" , e->gender);
    fscanf(staff_file_ptr , "%s" , e->name);
    fscanf(staff_file_ptr , "%s" , e->family);
    fscanf(staff_file_ptr , "%4s/%2s/%2s" , e->start_date.year , e->start_date.month , e->start_date.day);
    fscanf(staff_file_ptr , "%s" , e->rank);
    fscanf(staff_file_ptr , "%s" , e->phone_number);
    fscanf(staff_file_ptr , "%s" , e->email);
    fscanf(staff_file_ptr , "%s" , e->status);
    fscanf(staff_file_ptr , "%s" , e->user_name);
    fscanf(staff_file_ptr , "%s" , e->password);

    s->link = e ;
    e->link = NULL;


    // make link list of academic staff
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
        fscanf(staff_file_ptr , "%s" , d->status);
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
        if(!strcmp(type , "password"))
        {
            if(!strcmp(temp->user_name , head.user_name))
            {
                strcpy(temp->password , "");
                strcpy(temp->password , new );
            }
        } else if(!strcmp(type , "email"))
        {
            if(!strcmp(temp->user_name , head.user_name))
            {
                strcpy(temp->email , "");
                strcpy(temp->email , new );
            }
        }  else if(!strcmp(type , "phone number"))
        {
            if(!strcmp(temp->user_name , head.user_name))
            {
                strcpy(temp->phone_number , "");
                strcpy(temp->phone_number , new );
            }
        }
        temp = temp->link ;
    }

    staff_file_ptr = fopen("staff_information.txt" , "w");

    temp = s ;
    while(temp != NULL)
    {   
        if(temp == s)
            fprintf(staff_file_ptr , "%s\n" , temp->gender);
        else
            fprintf(staff_file_ptr , "\n%s\n" , temp->gender);
        fprintf(staff_file_ptr , "%s\n" , temp->name);
        fprintf(staff_file_ptr , "%s\n" , temp->family);
        fprintf(staff_file_ptr , "%4s/%2s/%2s\n" , temp->start_date.year , temp->start_date.month , temp->start_date.day);
        fprintf(staff_file_ptr , "%s\n" , temp->rank);
        fprintf(staff_file_ptr , "%s\n" , temp->phone_number);
        fprintf(staff_file_ptr , "%s\n" , temp->email);
        fprintf(staff_file_ptr , "%s\n" , temp->status);
        fprintf(staff_file_ptr , "%s\n" , temp->user_name);
        fprintf(staff_file_ptr , "%s" , temp->password);

        temp = temp->link ;
        
    }

    fclose(staff_file_ptr);

    // delete link list
    temp2 = s ;
    temp = s->link ;
    while (temp != NULL)
    {

        free(temp2);
        temp2 = temp ;
        temp = temp->link;

    }
}





