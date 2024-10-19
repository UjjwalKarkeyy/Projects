#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define USERLENGTH  10
#define PASSLENGTH  10
#define MAX_USERS 20

int count_turn = 0;

typedef struct 
{
    char us_name[USERLENGTH];
    char pass[PASSLENGTH];
}Users;

int login_user(Users *user, int *user_count)
{   
    getchar();
    int flag = 0;
    char name[USERLENGTH],pwd[PASSLENGTH];

    printf("Username (max 10 length): ");
    scanf("%s", name);
    printf("Password (max 8 length): ");
    scanf("%s", pwd);

    for(int i = 0; i < *user_count; i++)
    {
        if(strcmp(name, user[i].us_name) == 0 && strcmp(pwd, user[i].pass) == 0)
        {
            flag = 1;
            break;
        }
    }

    return flag;
}

void register_user(Users *user, int *user_count)
{
    FILE *fptr;

    fptr = fopen("/home/root123/ML Class/file_practice.txt", "a");

    if(fptr == NULL)
    {
        printf("Error while appending to the file!\n");
    }
    getchar();
    printf("Username (max 10 length): ");
    scanf("%s", user[*user_count].us_name);
    getchar();
    printf("Password (max 8 length): ");
    scanf("%s", user[*user_count].pass);

    fprintf(fptr, "%s %s\n", user[*user_count].us_name, user[*user_count].pass);
    fclose(fptr);

    *user_count += 1;

    printf("New user registered successfully!\nYou may login now\n\n");
}

int read_users(Users *user)
{
    FILE *fptr;
    int count = 0;

    fptr = fopen("/home/root123/ML Class/file_practice.txt", "r");

    if(fptr == NULL)
    {
        printf("Error while appending to the file!\n");
    }

    //What does -> mean?
    //what does EOF mean here?
    while(fscanf(fptr, "%s %s", user[count].us_name,user[count].pass) != EOF)
    {
        count++;
    }

    fclose(fptr);

    return count;
}

void clear_screen()
{
    system("clear");
}

void create_ticstruct(char *p)
{
    for(int i = 0, count = 6; i < 21; i+=2)
    {
        *(p + i) = '|';

        if(i == count && count != 20)
        {
            i -= 1;
            count += 7;
        }
    }

    for(int i = 1, value = 49, count = 5; i < 20; i+=2)
    {
        *(p + i) = (char)value;
        value += 1;

        if(i == count)
        {
            count += 7;
            i+=1;
        }
    }
}

void print_screen(char *p)
{
    printf("\n-------------------------------------------------\n");

    for(int i = 0, count = 6; i < 21; i++)
    {
        printf("%c\t", *(p+i));

        if(i == count)
        {
            printf("\n-------------------------------------------------\n");
            count += 7;
        }
    }
}

int find_index(int num, int used_values[], int used_num)
{

    for(int i = 0; i < used_num; i++)
    {
        if(num == used_values[i])
        {   
            return 0;
        }
    }
    switch(num)
    {
        case 1:
            return 1;

        case 2:
            return 3;

        case 3:
            return 5;

        case 4:
            return 8;

        case 5:
            return 10;

        case 6:
            return 12;

        case 7:
            return 15;

        case 8:
            return 17;

        case 9:
            return 19;

        default:
            return 0;
    }
}

int player_check_win(char *p, int win, char c)
{
    //Horizontal win check
    if ((*(p + 1) == c && *(p + 3) == c && *(p + 5) == c ) || (*(p + 8) == c && *(p + 10) == c && *(p + 12) == c ) || (*(p + 15) == c && *(p + 17) == c && *(p + 19) == c ))
        win = 1;

    //Verticle win check
    if(*(p + 1) == c && *(p + 8) == c && *(p + 15) == c || (*(p + 3) == c && *(p + 10) == c && *(p + 17) == c ) || (*(p + 5) == c && *(p + 12) == c && *(p + 19) == c ))
        win = 1;
    
    //Diagonal win check
    if(*(p + 1) == c && *(p + 10) == c && *(p + 19) == c || (*(p + 5) == c && *(p + 10) == c && *(p + 15) == c ))
        win = 1;

    return win;
}

int check_win(char *p, int count)
{
    int p1win = 0, p2win = 0;

    p1win = player_check_win(p, 0, 'X');
    p2win = player_check_win(p, 0, 'O');

    if(p1win == 1)
    {
        return p1win;
    }

    else if(p2win == 1)
    {
        return p2win+1;
    }

    else if(count == 9)
    {
        return 3;
    }

    else
        return 0;
}

void check_player(int count, int move)
{
    static int pl_one[9], pl_two[9], index1 = 0, index2 = 0;

    if(count % 2 != 0)
    {
        pl_one[index1] = move;
        index1++;
    }

    else if(count % 2 == 0)
    {
        pl_two[index2] = move;
        index2++;
    }
}

int take_user_input(char *p, int count)
{
    static int used_values[9], used_num = 0;
    
    if(count == 1)
        used_values[0] = 0;

    int num, win;
    char input;

    printf("Input number: ");
    scanf("%d", &num);

    check_player(count, num);

    int index = find_index(num, used_values, used_num);

    if(index == 0)
    {
        printf("Invalid input!\nEnter again\n");
        sleep(2);
        count_turn--;
        return win;
    }
 
    printf("Input: ");
    getchar();
    input = getchar();

    if(tolower(input) != 'x' && tolower(input) != 'o')
    {
        printf("Invalid input!\nEnter again\n");
        sleep(2);
        count_turn--;
        return win;
    }

    else if((count % 2 != 0) && tolower(input) == 'x')
    {
        *(p + index) = 'X';
    }

    else if((count % 2 == 0) && tolower(input) == 'o')
    {
        *(p + index) = 'O';
    }

    else
    {
        printf("Please wait for your turn!\n");
        sleep(2);
        count_turn--;
        return win;
    }

    used_values[used_num] = num;
    used_num++;

    if(count >= 3)
    {
        win = check_win(p, count);
    }

    return win;
}

int main()
{
    char arr[3][7], loading[10];
    char *p = *arr;

    while(count_turn != 6)
    {
    printf("Loading Game->[%s]\n",loading);
    sleep(3);
    clear_screen();
    

    strcat(loading, "|");
    count_turn++;
    }

    count_turn = 0;

    int choice;

    Users user[MAX_USERS];

    int count = read_users(user);
    int *user_count = &count;

    while(1)
    {
        int chk = 1, flag;

        printf("Select a choice:\n1. Register\n2. Login\nYour choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                register_user(user, user_count);
                flag = login_user(user, user_count);
                
                if (flag == 1)
                {
                    clear_screen();
                }

                else
                {
                    printf("Invalid username or password!\n");
                    chk = 0;
                }
                break;
            
            case 2:
                flag = login_user(user, user_count);

                if (flag == 1)
                {
                    clear_screen();
                }

                else
                {
                    printf("Invalid username or password!\n");
                    chk = 0;
                }

                break;

            default:
                printf("Invalid input!\n Try again\n");
                chk = 0;
                break;
        }

        if(chk == 0)
        {
            getchar();
            continue;
        }

        else
            break;
    }

    printf("Welcome to Tic-tac-toe\n");
    create_ticstruct(p);
    print_screen(p);

    while(1)
    {
        count_turn++;
        int win = take_user_input(p, count_turn);
        clear_screen();

        if(win == 1)
        {
            printf("Player 1 wins!\n");
            break;
        }

        else if(win == 2)
        {
            printf("Player 2 wins!\n");
            break;
        }

        else if(win == 3)
        {
            printf("Its a draw!\n");
            break;
        }
        print_screen(p);
    }
}