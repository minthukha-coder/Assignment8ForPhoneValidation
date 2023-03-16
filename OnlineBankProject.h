//
// Created by National Cyber City on 2/20/2023.
//

#ifndef DIPLEVEL1_ZOOM_ONLINE_BANK_H
#define DIPLEVEL1_ZOOM_ONLINE_BANK_H

#include "stdio.h"
#include "stdlib.h"
#define SIZE 1000 // symbolic constant
struct trans{
    char note[200];
};
//id name nrc email password pOrb loan_status monthly_income
// loan_amount loan_rate accountStatus account_Level phNumber current_amount address TransRC
struct data{
    unsigned int id;
    char name[30];
    char nrc[50];
    char email[50];
    char password[50];
    char pOrb[20]; // personal or business
    char loan_s[2]; // loan status
    unsigned int monthly_income;
    unsigned int loan_amount; // ဘယ်လောက်ချေးထားသလဲ
    float loan_rate;
    char acc_s[10]; //account status
    int acc_level;
    char phNumber[50];
    unsigned int cur_amount; //current amount
    char address[100];
    unsigned int transAmoLimitPerDay; // transAmountLimitPerDay minimize for our project 5min
    struct trans trc[100];
    void copy_two_char_array(char receiver[200] ,char transmitter[200]);

};

struct data db[SIZE];

// Global Variable Declaration

int users=0;
int gValid=-1;
int emailExist=-1;
int two_charArray=-1;
int nrc_valid = -1;
int strongPass=-1;
int phone_valid = -1;
int phone_valid2 = -1;
int pFound = -1;
int eFound = -1;
int phone_found = -1;

// For Function Declaration
void welcome();
void user_sector();
void loadingAllDataFromFile();
void printingAllData();
void registration();
int charCounting(char toCount[50]);
void myGmailValidation(char toValidate[50]);
void emailExistChecking(char toCheck[50]);
void compare_two_charArray(char first[50] , char second[50]);
void phone_validation_exit(char phone_toValid[50]);
void phone_validation(char phone_toValid[50]);
void nrc_validation(char nrc_toCheck[50]);
void myStrongPassword(char pass[50]);
void myStringCopy(char first[50] , char second[50]);
void passChecking(char pass[],int userIndex);
void login();
void transfer_function();
void withdraw_function();

void welcome(){

    int option=0;
    printf("Welcome to our Bank!\n");
    printf("Press 1 to Login!\nPress 2 to Register!\nPress 3 to Exit!:::");
    scanf("%d",&option);

    if(option == 1){
        printf("This is login!\n");
        login();

    } else if(option == 2){
        registration();

    } else if( option == 3){

        exit(1);
    } else {
        welcome();
    }

}

void user_sector(){
    int userOption = 0;
    printf("This is user Sector\n");
    printf("Press 1 to transfer\nPress 2 to withdraw money\nPress 3 to update your information\nPress 4 to Cash in:\nPress 5 to loan:\nPress 6 to "
           "view your history\nPress 7 to Exit\n");
    scanf("%d",&userOption);
    if (userOption == 1){
        transfer_function();
    }else if (userOption == 2){
        withdraw_function();
    }else if (userOption == 7){
        exit(1);
    }else{
        user_sector();
    }


}
//id name nrc email password pOrb loan_status monthly_income
// loan_amount loan_rate accountStatus account_Level phNumber current_amount address TransRC
void loadingAllDataFromFile(){

    FILE *fptr = fopen("ncc_db1.txt","r");

    if( fptr == NULL){
        printf("Error at loadingAllDataFromFile Function!\n");
    } else{
        for(int ncc=0; ncc<SIZE ; ncc++){

            fscanf(fptr ,"%u%s%s%s%s%s%s%u%u%f%s%d%s%u%s%u%s",&db[ncc].id,&db[ncc].name,&db[ncc].nrc,&db[ncc].email,&db[ncc].password,&db[ncc].pOrb,&db[ncc].loan_s,&db[ncc].monthly_income,&db[ncc].loan_amount ,&db[ncc].loan_rate , &db[ncc].acc_s ,&db[ncc].acc_level,&db[ncc].phNumber , &db[ncc].cur_amount,&db[ncc].address ,&db[ncc].transAmoLimitPerDay,&db[ncc].trc[0].note );


            if(db[ncc].email[0] == '\0'){
                break;
            }

            users++;

        }

    }

    fclose(fptr);

}
void printingAllData(){

    for(int ncc=0; ncc<users ; ncc++){


        printf("%u-%s-%s-%s-%s-%s-%s-%u-%u-%f-%s-%d-%s-%u-%s-%u-%s\n",db[ncc].id,db[ncc].name,db[ncc].nrc,db[ncc].email,db[ncc].password,
               db[ncc].pOrb, db[ncc].loan_s,db[ncc].monthly_income,db[ncc].loan_amount ,db[ncc].loan_rate , db[ncc].acc_s ,db[ncc].acc_level,
               db[ncc].phNumber , db[ncc].cur_amount,db[ncc].address ,db[ncc].transAmoLimitPerDay,db[ncc].trc[0].note);
    }

}

void copy_two_char_array(char receiver[200] ,char transmitter[200] ){


//    for(register int i=0; i<200; i++){
//        receiver[i]='\0';
//    }

    int transmit_counter = charCounting(transmitter);
    for(int i=0; i<transmit_counter; i++){
        receiver[i] = transmitter[i];
    }


}


void registration() {

    char reEmail[50];
    char re_name[50];
    char re_nrc[50];
    char re_pass[50];

    char re_phone[50];
    printf("This is NCC Bank User Registration!\n");
    printf("Enter your email:");
    scanf(" %[^\n]", &reEmail);
    gValid = -1;
    myGmailValidation(reEmail);
    if (gValid != -1) {

        emailExist = -1;
        emailExistChecking(reEmail);

        if (emailExist == -1) {

            printf("Your email is valid!\n");
            printf("Enter your name:");
            scanf(" %[^\n]", &re_name);
            nrc_valid = -1;
            while (nrc_valid == -1) {
                printf("Enter your NRC:");
                scanf(" %[^\n]", &re_nrc);

                nrc_validation(re_nrc);
                if (nrc_valid == -1) {
                    printf("Your NRC Format was Not Valid!\n");
                }

            }
            printf("Your NRC Format was Valid!\n");
            strongPass = -1;
            while (strongPass == -1) {
                printf("Enter your password!: To be strong password, Your password have to be more than 8");
                scanf(" %[^\n]", &re_pass);
                myStrongPassword(re_pass);
                if (strongPass == -1) {
                    printf("Your Password Format too weak and Try Again!\n");
                }
            }
            printf("Your password format was valid and saved!\n");


            phone_valid2 = -1;
            while (phone_valid2 == -1 || phone_valid == -1) {
                printf("Please enter your phone number:");
                scanf(" %[^\n]", &re_phone);
                phone_validation(re_phone);
                if (phone_valid2 == -1) {
                    printf("Your phone number is not format\n");
                }
                if (phone_valid2 == 1) {
                    printf("Your phone number is format\n");
                }
                phone_valid = -1;
                while (phone_valid == -1) {
                    phone_validation_exit((re_phone));
                    if (phone_valid == -1) {
                        printf("Invalid password or already exit\n");
                        break;

                    }
                }
            }

                printf("Your phone number was saved\n");
                printf("Please enter your amount");
                scanf("%u", &db[users].cur_amount);
                printf("Please enter your address");
                scanf(" %[^\n]", &db[users].address);

                copy_two_char_array(db[users].email, reEmail);
                copy_two_char_array(db[users].name, re_name);
                copy_two_char_array(db[users].nrc, re_nrc);
                copy_two_char_array(db[users].phNumber, re_phone);




                copy_two_char_array(db[users].pOrb, db[2].pOrb);
                copy_two_char_array(db[users].loan_s, db[2].loan_s);
                copy_two_char_array(db[users].acc_s, db[2].acc_s);
                copy_two_char_array(db[users].trc[0].note,db[2].trc[0].note);

                db[users].monthly_income = db[2].monthly_income;
                db[users].loan_amount = db[2].loan_amount;
                db[users].loan_rate = db[2].loan_rate;

                db[users].acc_level = db[2].acc_level;
                db[users].transAmoLimitPerDay = db[2].transAmoLimitPerDay;
                db[users].id = users + 1;

                users++;
                printingAllData();
                welcome();



            } else {

                printf("Your gmail already taken!\n");
                registration();
            }

        } else {
            printf("Your gmail format not valid!\n");
            registration();
        }



}


void login() {
    char lEmail[50];
    char lPassword[50];
    emailExist = -1;
    two_charArray = -1;
    while (emailExist == -1 || two_charArray == -1) {
        printf("Enter your email to login:");
        scanf(" %[^\n]", &lEmail);
        printf("Enter your password to login:");
        scanf(" %[^\n]", &lPassword);
        emailExist = -1;
        two_charArray = -1;
        emailExistChecking(lEmail);
        compare_two_charArray(db[emailExist].password, lPassword);
        if (emailExist == -1 || two_charArray == -1) {
            emailExist = -1;
            two_charArray = -1;
            printf("Wrong Email or Password\n");
        } else {
            printf("Welcome Mr.%s\n", db[emailExist].name);
            printf("Login Success\n");
            user_sector();
        }

    }
}

void transfer_function() {
    printf("This is transfer function\n");
}

void withdraw_function(){
    printf("This is withdraw function\n");
}


int charCounting(char toCount[50]){ // toCount[50] = {'w','i','n','@'gmail.com,'\0' , '\0'}
    int charCount = 0;
    for(int gcc=0; gcc<50 ; gcc++){

        if( toCount[gcc] == '\0'){
            break;
        } else{
            charCount++;
        }
    }
    return charCount;
}

void myGmailValidation(char toValidate[50]){

    // winhtut@gmail.com
    int toEndPoint = charCounting(toValidate);
    char form[10]={'@','g','m','a','i','l','.','c','o','m'};
    int count=0;

    for(int i=0; i<toEndPoint; i++){

        if(toValidate[i] == '@' || toValidate[i] ==' '){
            break;
        }else{
            count++;
        }

    }
    int tocheck=0;
    for( int i=0 ; i< toEndPoint ; i++){

        if( toValidate[count] != form[i]){
            break;
        } else{
            count++;
            tocheck++;
        }
    }

    if( tocheck == 10){
        gValid=1;
    }

}


void passChecking(char pass[],int userIndex) {
    int sameCount = 0;
    int passCount = charCounting(pass);
    int infoPassCount = charCounting(db[userIndex].password);
    if (passCount == infoPassCount) {
        for (int i = 0; i < passCount; i++) {
            if (pass[i] == db[userIndex].password[i]){
                sameCount++;
            }else{
                break;
            }
        }
        if (sameCount == passCount){
            pFound = 1;
        }
    }
}

void emailExistChecking(char toCheck[50]){

    int toCheckCount = charCounting(toCheck);
    int sameCounting=0;

    for(int ncc=0; ncc<users ; ncc++){
        int dbEmailCount = charCounting(db[ncc].email);

        sameCounting=0;
        if( toCheckCount == dbEmailCount){

            for(int gcc=0; gcc<toCheckCount ; gcc++){

                if(toCheck[gcc] != db[ncc].email[gcc] ){
                    break;
                } else{
                    sameCounting++;
                }

            }


        }

        if(toCheckCount == sameCounting){

            emailExist = ncc;
        }

    }


}

void phone_validation_exit(char phone_toValid[50]) {
    int phone_counter = 0;
    for (int i = 0; i < users; i++) {
        two_charArray = -1;
        compare_two_charArray(phone_toValid, db[i].phNumber);
        if (two_charArray == -1) {
            phone_counter++;
        } else {
            phone_valid = -1; // -1 ဆို phone exit // တူ
            phone_found = i;
            break;
        }

    }

    if (phone_counter == users){
        phone_valid = 1; // 1 ဆို phone မရှိ
    }

}


void phone_validation(char phone_toValid[50]) {
    int result = 0;
    int phone_count = 0;
    char phone_form[50] = {'9', '5', '9'};
    phone_count = charCounting(phone_toValid);
    if (phone_count == 12) {
        for (int i = 0; i < phone_count; i++) {
            if (phone_toValid[i] != phone_form[i]) {
                phone_valid2 = -1;
               break;
            } else {
                result++;
            }
        }

        if (result > 0) {
            for (int i = result; i < phone_count; i++) {
                if (phone_toValid[i] > 0 || phone_toValid[i] < 9) {
                    phone_valid2 = 1;
                }
            }

        }

    }
}


void nrc_validation(char nrc_toCheck[50]){

    int nrc_counter =charCounting(nrc_toCheck);
    int nrc_char=0;

    for(register int i=0; i< nrc_counter ; i++){

        if( nrc_toCheck[i] == ')'){
            break;
        }
        nrc_char++;
    }

    for(int i=0; i<3; i++){

        two_charArray=-1;
        compare_two_charArray(nrc_toCheck,db[i].nrc);
        if(two_charArray == 1){
            nrc_valid=1;
            break;
        }

    }


}

void compare_two_charArray(char first[50] , char second[50]){

    int first_counter =  charCounting(first);
    int second_counter = charCounting(second);
    int same_counter = 0;

    if( first_counter == second_counter) {
        for (register int i = 0; i < first_counter; i++) {
            if(first[i] != second[i]){
                break;
            }
            same_counter++;
        }

        if( first_counter == same_counter){
            two_charArray = 1;
        }
    }

}




void myStringCopy(char first[50] , char second[50] ){

    int secondCount =charCounting(second);
    for( int i=0; i<50; i++){
        first[i]='\0';
    }

    for(int a=0; a<secondCount ; a++){

        first[a] = second[a];

    }
    eFound = 1;

}

void myStrongPassword(char pass[50]){

    int i=0;
    int special=0;
    int numberChar=0;
    int capChar=0;
    int smallChar=0;
    int pass_counter = charCounting(pass);
    while (strongPass == -1 && pass_counter > 8){
        if( i == pass_counter){
            strongPass=-1;
            break;
        }
        if( pass[i] >= 33 && pass[i] <= 42){

            special++;
        } else  if( pass[i] >= 48 && pass[i] <= 57){

            numberChar++;

        } else if( pass[i] >= 65 && pass[i] <= 90){

            capChar++;
        } else if( pass[i] >= 97 && pass[i] <= 122) {

            smallChar++;
        }
        i++;
        if( special > 0 && numberChar >0 && capChar > 0 && smallChar >0){
            strongPass = 1;
        }
    }


}


#endif //DIPLEVEL1_ZOOM_ONLINE_BANK_H
