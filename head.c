#include "Headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>
const float eps=1e-6; //acts like 0 for float datatypes
char input[10007];
Account accounts[207];
int N; //current number of accounts
Transaction report[2][207];
int M[2]; //current number of transactions in report
char current_password[57];
const char* months[] = {"Invalid", "January", "February", "March", "April", "May", "June",
                        "July", "August", "September", "October", "November", "December"
                       };
int read_integer(const char*message) //reads integer
{
    printf("%s",message);
    fflush(stdin);
    gets(input);
    int N=strlen(input);
    if(N>50)
    {
        printf("Invalid Input, input can't contain more than 50 characters\n");
        return read_integer(message);
    }
    if(input[0]==0)
    {
        printf("Invalid input, input can't be empty\n");
        return read_integer(message);
    }
    for(int i=0; input[i]; i++)
    {
        if(input[i]<'0'||input[i]>'9')
        {
            printf("Invalid input, input can only contain digits (0-9)\n");
            return read_integer(message);
        }
    }
    if(strlen(input)>9)
    {
        printf("Invalid input, too large for integer (overflow)\n");
        return read_integer(message);
    }
    return atoi(input);
}
float read_float(const char*message) //reads float
{
    printf("%s",message);
    fflush(stdin);
    gets(input);
    int N=strlen(input);
    if(N>50)
    {
        printf("Invalid Input, input can't contain more than 50 characters\n");
        return read_float(message);
    }
    if(input[0]==0)
    {
        printf("Invalid input, input can't be empty\n");
        return read_float(message);
    }
    if(input[0]=='.')
    {
        printf("Invalid input, input can't start with decimal point\n");
        return read_float(message);
    }
    int cnt=0;
    for(int i=0; input[i]; i++)
    {
        if((input[i]<'0'||input[i]>'9')&&input[i]!='.')
        {
            printf("Invalid input, input can only contain digits (0-9) and decimal point (.)\n");
            return read_float(message);
        }
        if(input[i]=='.')
        {
            cnt++;
            if(cnt>1)
            {
                printf("Invalid input, input can't contain more than one decimal point\n");
                return read_float(message);
            }
            if(input[i+1]==0)
            {
                printf("Invalid input, input must contain digits after the decimal point\n");
                return read_float(message);
            }
        }
    }
    return atof(input);
}
void read_number(char*location,const char*message) //reads string and validates it contains only digits
{
    printf("%s",message);
    fflush(stdin);
    gets(input);
    int N=strlen(input);
    if(N>50)
    {
        printf("Invalid Input, input can't contain more than 50 characters\n");
        return read_number(location,message);
    }
    if(input[0]==0)
    {
        printf("Invalid input, input can't be empty\n");
        return read_number(location,message);
    }
    for(int i=0; input[i]; i++)
    {
        if(input[i]<'0'||input[i]>'9')
        {
            printf("Invalid input, input can only contain digits (0-9)\n");
            read_number(location,message);
            return;
        }
    }
    for(int i=0;; i++)
    {
        location[i]=input[i];
        if(!input[i])break;
    }
}
void read_word(char*location,const char*message) //reads string and validates it has no spaces
{
    printf("%s",message);
    fflush(stdin);
    gets(input);
    int N=strlen(input);
    if(N>50)
    {
        printf("Invalid Input, input can't contain more than 50 characters\n");
        return read_word(location,message);
    }
    if(input[0]==0)
    {
        printf("Invalid input, input can't be empty\n");
        return read_word(location,message);
    }
    for(int i=0; input[i]; i++)
    {
        if(input[i]==' ')
        {
            printf("Invalid input, input can not contain spaces\n");
            read_word(location,message);
            return;
        }
    }
    for(int i=0;; i++)
    {
        location[i]=input[i];
        if(!input[i])break;
    }
}
int is_all_digits(char* x)
{
    if(x==NULL||x[0]=='\0')
        return 0;
    int len = strlen(x), i;
    for(i=0; i<len; i++)
    {
        if(x[i]>'9' || x[i]<'0')
            return 0;
    }
    return 1;
}
void read_date(int* month, int* year)
{
    printf("Enter date in the format YYYY-MM : ");
    fflush(stdin);
    gets(input);
    int N=strlen(input);
    if(N>7 || N<6 || input[4]!='-')
    {
        printf("Enter a valid date\n");
        return read_date(month, year);
    }
    char* tok;
    char y[10], m[10];
    tok = strtok(input, "-");
    if(strlen(tok)!=4)
    {
        printf("Enter a valid date\n");
        return read_date(month, year);
    }
    strcpy(y, tok);
    tok = strtok(NULL, "-");
    if(strlen(tok)>2)
    {
        printf("Enter a valid date\n");
        return read_date(month, year);
    }
    strcpy(m, tok);
    if(!is_all_digits(m) || !is_all_digits(y))
    {
        printf("Enter a valid date\n");
        return read_date(month, year);
    }
    *month = atoi(m);
    *year = atoi(y);
    if(*month>12 || *month<1 || *year>2030 || *year<1900)
    {
        printf("Enter a valid date\n");
        return read_date(month, year);
    }
}
void read_string(char*location,const char*message) //reads string that can contain spaces
{
    printf("%s",message);
    fflush(stdin);
    gets(input);
    int N=strlen(input);
    if(N>50)
    {
        printf("Invalid Input, input can't contain more than 50 characters\n");
        return read_string(location,message);
    }
    if(input[0]==0)
    {
        printf("Invalid input, input can't be empty\n");
        return read_string(location,message);
    }
    for(int i=0;; i++)
    {
        location[i]=input[i];
        if(!input[i])break;
    }
}
void printDate(Date t) //printing a date (kinda useless for now)
{
    printf("%02d-%04d\n",t.month,t.year);
}
Date curDate() //current date right now!!
{
    time_t now=time(NULL);
    struct tm*local=localtime(&now);
    Date cur;
    cur.year = local->tm_year + 1900;
    cur.month = local->tm_mon + 1;
    return cur;
}
Timestamp curTime() //current time right now!!!
{
    time_t now=time(NULL);
    struct tm*local=localtime(&now);
    Timestamp cur;
    cur.year = local->tm_year + 1900;
    cur.month = local->tm_mon + 1;
    cur.day = local->tm_mday;
    cur.hour = local->tm_hour;
    cur.min = local->tm_min;
    cur.sec = local->tm_sec;
    return cur;
}
int loadReport(char*number,int idx) //read from transactions txt file of user with that number, put it into report array
{
    char filename[57];
    strcpy(filename,number);
    strcat(filename,".txt");
    FILE*fptr=fopen(filename,"r");
    if(fptr==NULL)return 1;
    M[idx]=0;
    char line[207];
    while(fgets(line,200,fptr)!=NULL)
    {
        line[strcspn(line,"\n")]='\0';
        char linecopy[207];
        strcpy(linecopy,line);
        char*token=strtok(linecopy," ");
        if(token==NULL)
        {
            fclose(fptr);
            return -2;
        }
        strcpy(report[idx][M[idx]].type,token);
        token=strtok(NULL," ");
        if(token==NULL)
        {
            fclose(fptr);
            return -2;
        }
        strcpy(report[idx][M[idx]].secondParty,token);
        token=strtok(NULL," ");
        if(token==NULL)
        {
            fclose(fptr);
            return -2;
        }
        report[idx][M[idx]].amount=atof(token);
        token=strtok(NULL," ");
        if(token==NULL)
        {
            fclose(fptr);
            return -2;
        }
        char tm1[57];
        strcpy(tm1,token);
        token=strtok(NULL," ");
        if(token==NULL)
        {
            fclose(fptr);
            return -2;
        }
        char tm2[57];
        strcpy(tm2,token);
        token=strtok(NULL," ");
        if(token!=NULL)
        {
            fclose(fptr);
            return -2;
        }
        char*token2=strtok(tm1,"-");
        if(token2==NULL)
        {
            fclose(fptr);
            return -2;
        }
        report[idx][M[idx]].tm.day=atoi(token2);
        token2=strtok(NULL,"-");
        if(token2==NULL)
        {
            fclose(fptr);
            return -2;
        }
        report[idx][M[idx]].tm.month=atoi(token2);
        token2=strtok(NULL,"-");
        if(token2==NULL)
        {
            fclose(fptr);
            return -2;
        }
        report[idx][M[idx]].tm.year=atoi(token2);
        token2=strtok(NULL,"-");
        if(token2!=NULL)
        {
            fclose(fptr);
            return -2;
        }
        char*token3=strtok(tm2,":");
        if(token3==NULL)
        {
            fclose(fptr);
            return -2;
        }
        report[idx][M[idx]].tm.hour=atoi(token3);
        token3=strtok(NULL,":");
        if(token3==NULL)
        {
            fclose(fptr);
            return -2;
        }
        report[idx][M[idx]].tm.min=atoi(token3);
        token3=strtok(NULL,":");
        if(token3==NULL)
        {
            fclose(fptr);
            return -2;
        }
        report[idx][M[idx]].tm.sec=atoi(token3);
        token3=strtok(NULL,":");
        if(token3!=NULL)
        {
            fclose(fptr);
            return -2;
        }
        M[idx]++;
    }
    fclose(fptr);
    return 0;
}
int loadToReport(const char*number,int idx) //read from report array, put it into transactions txt file of user with that number
{
    char filename[57];
    strcpy(filename,number);
    strcat(filename,".txt");
    FILE*fptr=fopen(filename,"w");
    if(fptr==NULL)return -1;
    for(int i=0; i<M[idx]; i++)
    {
        fprintf(fptr,"%s %s %.2f %d-%d-%d %d:%d:%d\n",
                report[idx][i].type,
                report[idx][i].secondParty,
                report[idx][i].amount,
                report[idx][i].tm.day,
                report[idx][i].tm.month,
                report[idx][i].tm.year,
                report[idx][i].tm.hour,
                report[idx][i].tm.min,
                report[idx][i].tm.sec);
    }
    fclose(fptr);
    return 0;
}
int searchUsername(char*username) //search for username in users.txt, if exists put its password in current_password
{
    FILE*fptr=fopen("users.txt","r");
    if(fptr==NULL)return -2;
    char line[207];
    while(fgets(line,200,fptr)!=NULL)
    {
        line[strcspn(line,"\n")]='\0';
        char linecopy[207];
        strcpy(linecopy,line);
        char*token=strtok(linecopy," ");
        if(token==NULL)
        {
            fclose(fptr);
            return -2;
        }
        if(strcmp(username,token))continue;
        token=strtok(NULL," ");
        if(token==NULL)
        {
            fclose(fptr);
            return -2;
        }
        strcpy(current_password,token);
        fclose(fptr);
        return 0;
    }
    fclose(fptr);
    return 1;
}
int login() //tries to login user
{
    FILE*fptr=fopen("users.txt","r");
    if(fptr==NULL)return -1;
    fclose(fptr);
    char username[50];
    read_word(username,"Username: ");
    int x=searchUsername(username);
    if(x!=0)return x;
    char password[50];
    read_word(password,"Password: ");
    if(strcmp(password,current_password))return 2;
    return 0;
}
int loadToProgram() //read from accounts.txt file, put it into accounts array
{
    FILE*fptr=fopen("accounts.txt","r");
    if(fptr==NULL)return -1;
    N=0;
    char line[207];
    while(fgets(line,200,fptr)!=NULL)
    {
        line[strcspn(line,"\n")]='\0';
        char linecopy[207];
        strcpy(linecopy,line);
        char*token=strtok(linecopy,",");
        if(token==NULL)
        {
            fclose(fptr);
            return -2;
        }
        strcpy(accounts[N].number,token);
        token=strtok(NULL,",");
        if(token==NULL)
        {
            fclose(fptr);
            return -2;
        }
        strcpy(accounts[N].name,token);
        token=strtok(NULL,",");
        if(token==NULL)
        {
            fclose(fptr);
            return -2;
        }
        strcpy(accounts[N].email,token);
        token=strtok(NULL,",");
        if(token==NULL)
        {
            fclose(fptr);
            return -2;
        }
        accounts[N].balance=atof(token);
        token=strtok(NULL,",");
        if(token==NULL)
        {
            fclose(fptr);
            return -2;
        }
        strcpy(accounts[N].mobile,token);
        token=strtok(NULL,",");
        if(token==NULL)
        {
            fclose(fptr);
            return -2;
        }
        char date[57];
        strcpy(date,token);
        token=strtok(NULL," ,");
        if(token==NULL)
        {
            fclose(fptr);
            return -2;
        }
        strcpy(accounts[N].status,token);
        token=strtok(NULL,",");
        if(token!=NULL)
        {
            fclose(fptr);
            return -2;
        }
        char*token2=strtok(date,"-");
        if(token2==NULL)
        {
            fclose(fptr);
            return -2;
        }
        accounts[N].dateOpened.month=atoi(token2);
        token2=strtok(NULL,"-");
        if(token2==NULL)
        {
            fclose(fptr);
            return -2;
        }
        accounts[N].dateOpened.year=atoi(token2);
        token2=strtok(NULL,"-");
        if(token2!=NULL)
        {
            fclose(fptr);
            return -2;
        }
        N++;
    }
    for(int i=0; i<N; i++)
    {
        char filename[57];
        strcpy(filename,accounts[i].number);
        strcat(filename,".txt");
        FILE*tmp=fopen(filename,"a");
        fclose(tmp);
    }
    fclose(fptr);
    return 0;
}
int loadToFile() //read from accounts array, put it into accounts.txt file
{
    FILE*fptr=fopen("accounts.txt","w");
    if(fptr==NULL)return -1;
    for(int i=0; i<N; i++)
    {
        fprintf(fptr,"%s,%s,%s,%.2f,%s,%d-%d, %s\n",
                accounts[i].number,
                accounts[i].name,
                accounts[i].email,
                accounts[i].balance,
                accounts[i].mobile,
                accounts[i].dateOpened.month,
                accounts[i].dateOpened.year,
                accounts[i].status);
    }
    fclose(fptr);
    return 0;
}
void enterNumber(char*location,const char*message) //for taking account number as input
{
    read_number(location,message);
    while(strlen(location)!=10)
    {
        printf("Account number must be exactly 10 digits\n");
        read_number(location,message);
    }
}
void enterMobile(char*location,const char*message) //for taking account mobile number as input
{
    read_number(location,message);
    while(strlen(location)!=11)
    {
        printf("Account's mobile number must be exactly 11 digits\n");
        read_number(location,message);
    }
}
int enterOption(int l,int r) //enterOption is for taking an integer option choice from the user
{
    int option;
    while(1)
    {
        option=read_integer("Choose option by its corresponding number: ");
        if(option<l||option>r)
        {
            printf("Option must be between %d and %d (inclusive)\n",l,r);
            continue;
        }
        break;
    }
    return option;
}
int nameValidation(char*name) //validates account name
{
    for(int i=0; name[i]; i++)
    {
        if(name[i]==' ')
        {
            if(i==0)return 1;
            if(name[i+1]==0)return 2;
            if(name[i-1]==' ')return 3;
            continue;
        }
        if(name[i]>='a'&&name[i]<='z')continue;
        if(name[i]>='A'&&name[i]<='Z')continue;
        return 4;
    }
    return 0;
}
void enterName(char*location,const char*message) //takes account name as input
{
    read_string(location,message);
    while(1)
    {
        int flag=nameValidation(location);
        if(!flag)break;
        switch(flag)
        {
        case 1:
            printf("Name can't start with a space\n");
            break;
        case 2:
            printf("Name can't end with a space\n");
            break;
        case 3:
            printf("Name can't contain two consecutive spaces\n");
            break;
        case 4:
            printf("Name can only contain letters (a-z),(A-Z) and spaces\n");
            break;
        }
        read_string(location,message);
    }
}
int emailValidation(char*name) //validates email
{
    int atpos=-1;
    int dotpos=-1;
    for(int i=0; name[i]; i++)
    {
        if(atpos==-1)
        {
            if(name[i]>='a'&&name[i]<='z')continue;
            if(name[i]>='A'&&name[i]<='Z')continue;
            if(name[i]>='0'&&name[i]<='9')continue;
            if(name[i]=='.')continue;
            if(name[i]=='_')continue;
            if(name[i]=='%')continue;
            if(name[i]=='+')continue;
            if(name[i]=='-')continue;
            if(name[i]=='@')
            {
                atpos=i;
                continue;
            }
            return 1;
        }
        if(name[i]=='.'&&name[i+1]=='.') return 9;
        if(name[i]>='a'&&name[i]<='z')continue;
        if(name[i]>='A'&&name[i]<='Z')continue;
        if(name[i]>='0'&&name[i]<='9')continue;
        if(name[i]=='-')continue;
        if(name[i]=='.')
        {
            dotpos=i;
            continue;
        }
        return 2;
    }
    if(atpos==0)return 3;
    if(atpos==-1)return 4;
    if(dotpos==-1)return 5;
    if(dotpos==atpos+1)return 6;
    if(name[dotpos+1]==0)return 7;
    for(int i=dotpos+1; name[i]; i++)
    {
        if(name[i]>='a'&&name[i]<='z')continue;
        if(name[i]>='A'&&name[i]<='Z')continue;
        return 8;
    }
    return 0;
}
void enterEmail(char*location,const char*message) //takes email as input
{
    read_word(location,message);
    while(1)
    {
        int flag=emailValidation(location);
        if(!flag)break;
        switch(flag)
        {
        case 1:
            printf("Email's username can only contain letters (a-z),(A-Z), digits(0-9), symbols(._%%+-)\n");
            break;
        case 2:
            printf("Email's service/website can only contain letters (a-z),(A-Z), digits(0-9), (.-)\n");
            break;
        case 3:
            printf("Email's address can't start with '@'\n");
            break;
        case 4:
            printf("Email's address must contain one '@'\n");
            break;
        case 5:
            printf("Email's service/website must contain at least one '.'\n");
            break;
        case 6:
            printf("Email's service/website's name can't be empty\n");
            break;
        case 7:
            printf("Email's service/website's domain can't be empty\n");
            break;
        case 8:
            printf("Email's service/website's domain can only contain letters (a-z),(A-Z)\n");
            break;
        case 9:
            printf("Email's address must contain one '.'\n");
            break;
        }
        read_word(location,message);
    }
}
void QUIT() //QUIT function
{
    printf("Exiting system...\n");
    exit(0);
}
void SAVE(const char*partyOne,const char*partyTwo) //asks whether to confirm changes or discard
{
    printf("Do you want to confirm changes/transactions?\n");
    printf("1. Confirm\n");
    printf("2. Discard\n");
    int option=enterOption(1,2);
    if(option==2)
    {
        int flag=loadToProgram();
        if(flag==-2)
        {
            printf("FATAL ERROR\n");
            QUIT();
        }
        return;
    }
    loadToFile();
    if(strcmp(partyOne,"_"))loadToReport(partyOne,0);
    if(strcmp(partyTwo,"_"))loadToReport(partyTwo,1);
    int flag=loadToProgram();
    if(flag==-2)
    {
        printf("FATAL ERROR\n");
        QUIT();
    }
}
void ADD()
{
    if(N==200)
    {
        printf("Maximum limit of accounts exceeded!");
        printf("The bank can only allow 200 accounts at a time\n");
        return;
    }
    char num[57];
    enterNumber(num,"Enter the account's bank number: ");
    while(1)
    {
        int flag=1;
        for(int i=0; i<N; i++)
        {
            if(!strcmp(accounts[i].number,num))flag=0;
        }
        if(flag)break;
        printf("Account number already exists, choose another number\n");
        enterNumber(num,"Enter the account's bank number: ");
    }
    char name[57];
    enterName(name,"Enter the account's name: ");
    char email[57];
    enterEmail(email,"Enter the account's email address: ");
    float bal=read_float("Enter the account's balance: ");
    char mob[57];
    enterMobile(mob,"Enter the account's mobile number: ");
    strcpy(accounts[N].number,num);
    strcpy(accounts[N].name,name);
    strcpy(accounts[N].email,email);
    accounts[N].balance=bal;
    strcpy(accounts[N].mobile,mob);
    accounts[N].dateOpened=curDate();
    strcpy(accounts[N].status,"active");
    N++;
    SAVE("_","_");
}
void DELETE()
{
    char num[57];
    enterNumber(num,"Enter the account's bank number: ");
    int p=-1;
    for(int i=0; i<N; i++)
    {
        if(!strcmp(accounts[i].number,num))p=i;
    }
    if(p==-1)
    {
        printf("No account with such a number is found in the database\n");
        return;
    }
    if(accounts[p].balance>eps)
    {
        printf("Request rejected, can't delete an account with non-zero balance\n");
        return;
    }
    while(p+1<N)
    {
        accounts[p]=accounts[p+1];
        p++;
    }
    N--;
    M[0]=0;
    SAVE(num,"_");
}
void DIRECTDELETE(int x)
{
    char num[57];
    strcpy(num, accounts[x].number);
    while(x+1<N)
    {
        accounts[x]=accounts[x+1];
        x++;
    }
    N--;
    M[0]=0;
    SAVE(num,"_");

}
void DELETEMULTIPLE()
{
    int i, cnt=0;
    Date now = curDate();
    int m, y;
    printf("1) By date\n");
    printf("2) By inactivity\n");
    int option = enterOption(1,2);
    switch(option)
    {
    case 1 :
        read_date(&m, &y);
        for(i=0; i<N; i++)
        {
            if(accounts[i].dateOpened.month!=m)
                continue;
            if(accounts[i].dateOpened.year!=y)
                continue;
            if(accounts[i].balance>eps)
                continue;

            DIRECTDELETE(i);

            cnt++;
            i--;
        }
        break;
    case 2:
        for(i=0; i<N; i++)
        {
            int yearDiff = now.year - accounts[i].dateOpened.year;
            int monthDiff = now.month - accounts[i].dateOpened.month;
            int totalMonths = yearDiff * 12 + monthDiff;
            if(accounts[i].balance>eps)
                continue;
            if( strcmp("inactive", accounts[i].status) )
                continue;
            if(totalMonths <=3)
                continue;

            DIRECTDELETE(i);
            cnt++;
            i--;
        }
        break;
    }

    if(cnt)
        printf("%d Accounts have been successfully deleted\n", cnt);
    else
    {
        switch(option)
        {
        case 1:
            printf("\nThere is no account created on the given date with 0 balance\n");
            break;
        case 2:
            printf("\nThere is no inactive account with balance = 0 which has been created in the last 90 days\n");
            break;
        }
    }
    return;
}
void MODIFY()
{
    char num[57];
    enterNumber(num,"Enter the account's bank number: ");
    int p=-1;
    for(int i=0; i<N; i++)
    {
        if(!strcmp(accounts[i].number,num))p=i;
    }
    if(p==-1)
    {
        printf("No account with such a number is found in the database\n");
        return;
    }
    enterName(accounts[p].name,"Account's new name: ");
    enterMobile(accounts[p].mobile,"Account's new mobile number: ");
    enterEmail(accounts[p].email,"Account's new email: ");
    SAVE("_","_");
}
void CHANGE_STATUS()
{
    char num[57];
    enterNumber(num,"Enter the account's bank number: ");
    int p=-1;
    for(int i=0; i<N; i++)
    {
        if(!strcmp(accounts[i].number,num))p=i;
    }
    if(p==-1)
    {
        printf("No account with such a number is found in the database\n");
        return;
    }
    printf("Set status for account\n");
    printf("1. Active\n");
    printf("2. Inactive\n");
    int option=enterOption(1,2);
    if(option==1)
    {
        if(!strcmp(accounts[p].status,"active"))
        {
            printf("NOTICE: your account was already active, so nothing changed\n");
        }
        strcpy(accounts[p].status,"active");
    }
    if(option==2)
    {
        if(!strcmp(accounts[p].status,"inactive"))
        {
            printf("NOTICE: your account was already inactive, so nothing changed\n");
        }
        strcpy(accounts[p].status,"inactive");
    }
    SAVE("_","_");
}
float DAILYLIMIT(char*num)
{
    loadReport(num,0);
    Timestamp rn=curTime();
    float sum=0;
    for(int i=0; i<M[0]; i++)
    {
        if(strcmp(report[0][i].type,"withdraw"))continue;
        if(report[0][i].tm.year!=rn.year)continue;
        if(report[0][i].tm.month!=rn.month)continue;
        if(report[0][i].tm.day!=rn.day)continue;
        sum+=report[0][i].amount;
    }
    return sum;
}
void WITHDRAW()
{
    char num[57];
    enterNumber(num,"Enter the account's bank number: ");
    int p=-1;
    for(int i=0; i<N; i++)
    {
        if(!strcmp(accounts[i].number,num))p=i;
    }
    if(p==-1)
    {
        printf("No account with such a number is found in the database\n");
        return;
    }
    if(!strcmp(accounts[p].status,"inactive"))
    {
        printf("Account number %s is inactive, can't make transactions with inactive account\n",num);
        return;
    }
    float amount=read_float("Enter withdraw amount: ");
    while(1)
    {
        if(amount>1e4)
        {
            printf("Amount can't exceed maximum withdraw limit per transaction, which is 10,000$\n");
            amount=read_float("Enter withdraw amount: ");
            continue;
        }
        if(accounts[p].balance<amount)
        {
            printf("Not enough balance in account to withdraw this amount\n");
            printf("Current account balance: %.2f\n",accounts[p].balance);
            amount=read_float("Enter withdraw amount: ");
            continue;
        }
        break;
    }
    float curLimit=DAILYLIMIT(num);
    if(curLimit+amount>5e4)
    {
        printf("Can't perform transaction because account will exceed the daily limit of 50,000$ withdraw amounts\n");
        printf("Current daily withdraw amount: %.2f\n",curLimit);
        return;
    }
    loadReport(num,0);
    report[0][M[0]].tm=curTime();
    report[0][M[0]].amount=amount;
    strcpy(report[0][M[0]].secondParty,"-");
    strcpy(report[0][M[0]].type,"withdraw");
    M[0]++;
    accounts[p].balance-=amount;
    SAVE(num,"_");
}
void DEPOSIT()
{
    char num[57];
    enterNumber(num,"Enter the account's bank number: ");
    int p=-1;
    for(int i=0; i<N; i++)
    {
        if(!strcmp(accounts[i].number,num))p=i;
    }
    if(p==-1)
    {
        printf("No account with such a number is found in the database\n");
        return;
    }
    if(!strcmp(accounts[p].status,"inactive"))
    {
        printf("Account number %s is inactive, can't make transactions with inactive account\n",num);
        return;
    }
    float amount=read_float("Enter deposit amount: ");
    while(1)
    {
        if(amount>1e4)
        {
            printf("Amount can't exceed maximum deposit limit per transaction, which is 10,000$\n");
            amount=read_float("Enter deposit amount: ");
            continue;
        }
        break;
    }
    loadReport(num,0);
    report[0][M[0]].tm=curTime();
    report[0][M[0]].amount=amount;
    strcpy(report[0][M[0]].secondParty,"_");
    strcpy(report[0][M[0]].type,"deposit");
    M[0]++;
    accounts[p].balance+=amount;
    SAVE(num,"_");
}
void TRANSFER()
{
    char num1[57];
    enterNumber(num1,"Enter the sender's account's bank number: ");
    int p1=-1;
    for(int i=0; i<N; i++)
    {
        if(!strcmp(accounts[i].number,num1))p1=i;
    }
    if(p1==-1)
    {
        printf("No account with such a number is found in the database\n");
        return;
    }
    if(!strcmp(accounts[p1].status,"inactive"))
    {
        printf("Account number %s is inactive, can't make transactions with inactive account\n",num1);
        return;
    }
    char num2[57];
    enterNumber(num2,"Enter the reciever's account's bank number: ");
    int p2=-1;
    for(int i=0; i<N; i++)
    {
        if(!strcmp(accounts[i].number,num2))p2=i;
    }
    if(p2==-1)
    {
        printf("No account with such a number is found in the database\n");
        return;
    }
    if(!strcmp(accounts[p2].status,"inactive"))
    {
        printf("Account number %s is inactive, can't make transactions with inactive account\n",num2);
        return;
    }
    float amount=read_float("Enter transfer amount: ");
    while(1)
    {
        if(accounts[p1].balance<amount)
        {
            printf("Not enough balance in sender's account to withdraw this amount\n");
            printf("Current sender's account balance: %.2f\n",accounts[p1].balance);
            amount=read_float("Enter transfer amount: ");
            continue;
        }
        break;
    }
    loadReport(num1,0);
    report[0][M[0]].tm=curTime();
    report[0][M[0]].amount=amount;
    strcpy(report[0][M[0]].secondParty,num2);
    strcpy(report[0][M[0]].type,"transferSend");
    M[0]++;
    accounts[p1].balance-=amount;
    loadReport(num2,1);
    report[1][M[1]].tm=curTime();
    report[1][M[1]].amount=amount;
    strcpy(report[1][M[1]].secondParty,num1);
    strcpy(report[1][M[1]].type,"transferRecieve");
    M[1]++;
    accounts[p2].balance+=amount;
    SAVE(num1,num2);
}
void REPORT() //REPORT function
{
    char num[57];
    enterNumber(num,"Enter Account Number: ");
    int flag=loadReport(num,0);
    if(flag==1)
    {
        printf("No such account number exists in the database!\n");
        return;
    }
    printf("Account %s transaction history: \n\n",num);
    for(int i=(M[0]<5?0:M[0]-5); i<M[0]; i++)
    {
        printf("%s %s %.2f %d-%d-%d %d:%d:%d\n",
               report[0][i].type,
               report[0][i].secondParty,
               report[0][i].amount,
               report[0][i].tm.day,
               report[0][i].tm.month,
               report[0][i].tm.year,
               report[0][i].tm.hour,
               report[0][i].tm.min,
               report[0][i].tm.sec);
    }
}
void sortbyName()
{
    int i, j, flag;
    Account tempacc;
    for(i=0; i<N; i++)
    {
        flag = 0;
        for(j=1; j<N; j++)
        {
            int comp = strcmp( accounts[j-1].name, accounts[j].name );
            if(comp>0)
            {
                tempacc = accounts[j];
                accounts[j]=accounts[j-1];
                accounts[j-1]=tempacc;
                flag = 1;
            }
        }
        if(!flag)
            break;
    }

}
void sortbyDate()
{
    int i, j, flag, m1, m2, y1, y2;
    Account tempacc;
    for(i=0; i<N; i++)
    {
        flag = 0;
        for(j=1; j<N; j++)
        {
            m1 = accounts[j-1].dateOpened.month;
            y1 = accounts[j-1].dateOpened.year;
            m2 = accounts[j].dateOpened.month;
            y2 = accounts[j].dateOpened.year;
            if( y1>y2 || (y1==y2 && m1>m2) )
            {
                tempacc = accounts[j];
                accounts[j]=accounts[j-1];
                accounts[j-1]=tempacc;
                flag = 1;
            }

        }
        if(!flag)
            break;
    }

}
void sortbyBalance()
{
    int i, j, flag;
    float b1, b2;
    Account tempacc;
    for(i=0; i<N; i++)
    {
        flag = 0;
        for(j=1; j<N; j++)
        {
            b1 = accounts[j-1].balance;
            b2 = accounts[j].balance;
            if(b1>b2)
            {
                tempacc = accounts[j];
                accounts[j]=accounts[j-1];
                accounts[j-1]=tempacc;
                flag = 1;
            }
        }
        if(!flag)
            break;
    }


}
void sortbyStatus()
{
    int i, j, flag;
    Account tempacc;
    for(i=0; i<N; i++)
    {
        flag = 0;
        for(j=1; j<N; j++)
        {
            int comp = strcmp(accounts[j-1].status, accounts[j].status);
            if(comp>0)
            {
                tempacc = accounts[j];
                accounts[j]=accounts[j-1];
                accounts[j-1]=tempacc;
                flag = 1;
            }
        }
        if(!flag)
            break;
    }
}
void PRINT(Account x)
{
    printf("\nAccount Number : %s\n", x.number );
    printf("Name : %s\n", x.name );
    printf("E-mail : %s\n", x.email );
    printf("Balance : %f\n", x.balance );
    printf("Mobile : %s\n", x.mobile );
    printf("Date Opened : %s %d\n", months[x.dateOpened.month], x.dateOpened.year);
    printf("Status : %s\n\n", x.status );
}
void QUERYSEARCH()
{
    char accquery[57];
    char msg[] = "Enter the account number : ";
    enterNumber(accquery, msg);
    int i, comp;
    for(i=0; i<N; i++)
    {
        comp = strcmp(accquery, accounts[i].number);
        if(comp==0)
        {
            PRINT(accounts[i]);
            return;
        }
    }
    printf("\nAccount not found\n");

}
void ADVANCEDSEARCH()
{
    char keyword[57];
    char msg[] = "Enter keyword : ";
    read_string(keyword, msg);
    int i, flag=0;
    char* search;
    for(i=0; i<N; i++)
    {
        search = strstr(accounts[i].name, keyword);
        if(search!=NULL)
        {
            PRINT(accounts[i]);
            flag=1;
        }
    }
    if(!flag)
        printf("\nNo matches are found\n");

}
void PRINTSORT()
{
    printf("1. Sort By Name\n");
    printf("2. Sort By Date\n");
    printf("3. Sort By Balance\n");
    printf("4. Sort By Status\n");
    int option = enterOption(1, 4);
    switch(option)
    {
    case 1 :
        sortbyName();
        break;
    case 2 :
        sortbyDate();
        break;
    case 3 :
        sortbyBalance();
        break;
    case 4 :
        sortbyStatus();
        break;
    }
    int i;
    for(i=0; i<N; i++)
    {
        PRINT(accounts[i]);
    }
}
void mainMenu() //MENU function
{
    int option,flag;
ptr:
    printf("1. Login\n");
    printf("2. Exit\n");
    option=enterOption(1,2);
    if(option==2)QUIT();
    flag=login();
    if(flag==-2)
    {
        printf("FATAL ERROR\n");
        QUIT();
    }
    if(flag==-1)
    {
        printf("File \"users.txt\" not found, make sure to create it before running the program\n");
        QUIT();
    }
    if(flag>0)
    {
        if(flag==1)printf("Username does not exist in the database, login failed\n");
        if(flag==2)printf("Incorrect password, login failed\n");
        printf("1. Retry\n");
        printf("2. Exit\n");
        option=enterOption(1,2);
        if(option==2)QUIT();
        goto ptr;
    }
    printf("Login successful!\n");
    printf("Loading accounts' data...\n");
    flag=loadToProgram();
    if(flag==-2)
    {
        printf("FATAL ERROR\n");
        QUIT();
    }
    if(flag==-1)
    {
        printf("File \"accounts.txt\" not found, make sure to create it before running the program\n");
        QUIT();
    }
    printf("Loading successful!\n");
    while(1)
    {
        printf("\n========================================\n");
        printf("            MAIN MENU\n");
        printf("========================================\n");
        printf(" 1. Add\n");
        printf(" 2. Delete\n");
        printf(" 3. Modify\n");
        printf(" 4. Search\n");
        printf(" 5. Advanced Search\n");
        printf(" 6. Change Status\n");
        printf(" 7. Withdraw\n");
        printf(" 8. Deposit\n");
        printf(" 9. Transfer\n");
        printf("10. Report\n");
        printf("11. Print\n");
        printf("12. Quit\n");
        printf("13. Delete Multiple\n");
        printf("========================================\n");
        option=enterOption(1,13);
        switch(option)
        {
        case 1:
            ADD();
            break;

        case 2:
            DELETE();
            break;

        case 3:
            MODIFY();
            break;

        case 4:
            QUERYSEARCH();
            break;

        case 5:
            ADVANCEDSEARCH();
            break;

        case 6:
            CHANGE_STATUS();
            break;

        case 7:
            WITHDRAW();
            break;

        case 8:
            DEPOSIT();
            break;

        case 9:
            TRANSFER();
            break;

        case 10:
            REPORT();
            break;

        case 11:
            PRINTSORT();
            break;

        case 12:
            QUIT();
            break;
        case 13:
            DELETEMULTIPLE();
            break;
        }

    }
}
