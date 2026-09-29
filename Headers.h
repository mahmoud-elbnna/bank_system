#ifndef HEADERS_H
#define HEADERS_H
typedef struct //date struct
{
    int year;
    int month;
} Date;
typedef struct //account data
{
    char number[57];
    char name[57];
    char email[57];
    char mobile[57];
    float balance;
    Date dateOpened;
    char status[57];
} Account;
typedef struct //timestamp struct (more detailed than date)
{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
} Timestamp;
typedef struct //transaction data
{
    char type[57];
    float amount;
    char secondParty[57]; //number of receiver/sender in case of transfer, "_" otherwise
    Timestamp tm;
} Transaction;
int read_integer(const char*message);
float read_float(const char*message);
void read_number(char*location,const char*message);
void read_word(char*location,const char*message);
int is_all_digits(char* x);
void read_date(int* month, int* year);
void read_string(char*location,const char*message);
int loadReport(char*number,int idx);
int loadToReport(const char*number,int idx);
int searchUsername(char*username);
int login();
void printDate(Date t);
int loadToProgram();
int loadToFile();
void enterNumber(char*location,const char*message);
void enterMobile(char*location,const char*message);
int enterOption(int l,int r);
int nameValidation(char*name);
void enterName(char*location,const char*message);
int emailValidation(char*name);
void enterEmail(char*location,const char*message);
void QUIT();
void SAVE(const char*partyOne,const char*partyTwo);
void ADD();
void DELETE();
void DIRECTDELETE(int x);
void DELETEMULTIPLE();
void MODIFY();
void CHANGE_STATUS();
float DAILYLIMIT(char*num);
void WITHDRAW();
void DEPOSIT();
void TRANSFER();
void REPORT();
void sortbyName();
void sortbyDate();
void sortbyBalance();
void sortbyStatus();
void PRINT(Account x);
void QUERYSEARCH();
void ADVANCEDSEARCH();
void PRINTSORT();
void mainMenu();
#endif
