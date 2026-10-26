#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct date
{
    int year;
    int month;
    int day;
}date;

typedef struct time
{
    int hour;
    int min;
}time;


typedef struct patient
{
    char firstname[20];
    char lastname[20];
    date birth;
    char gender;
}patient;


typedef struct node_patient
{
    patient info;
    struct node_patient *next;
}node_patient;



node_patient *ADD(node_patient *head, node_patient *newpatient){
    node_patient *tail;

    newpatient->next = NULL;

    if (head == NULL) {
        head = newpatient;
    } else {
        tail = head;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = newpatient;
    }
    return head;
}




int main(){
    printf("Title of The Project: Patient and Appointment Management\n");
    printf("Group number: 10\n");
    printf("Made by:\n\n\n");



    printf("|_________________________________________________|\n\n\n");

    printf("Welcome to the clinic\n");
    printf("What do you want to do\n 0-exit\n 1-Add a patient\n 2-Search for a patient\n 3-Modify a patient\n 4-Delete patient\n 5-list all patient\n\n");
    int choice;
    scanf("%d",&choice);
    while (choice < 0 || choice > 5){
        printf("Enter a valid choice\n");
    scanf("%d",&choice);   
    }
        node_patient *temp;
        node_patient *head; /*head outside the loop so its ot reseted every time (to keep the previous one)*/
        head = NULL; 
    while (choice != 0)
    {
  
    if(choice == 1){

        node_patient *newpatient;

        printf("How many patient you want to Add\n");
        int n,i;
        while (scanf("%d", &n) != 1 || n < 0) /*A boolean for scanf to make sure that thee entered value is an int*/
        {
        printf("Enter a valid option\n");
                 
        }

        for(i = 0; i<n; i++){
        node_patient *newpatient = malloc(sizeof(node_patient));
            printf("The First name of the patient\n");
            scanf("%19s",newpatient->info.firstname);

            printf("The Last name of the patient\n");
            scanf("%19s",newpatient->info.lastname);

            printf("The gender of the patient (M : Male  F : Female)\n");
            scanf(" %c",&newpatient->info.gender);
            newpatient->info.gender = toupper(newpatient->info.gender);
            while (newpatient->info.gender != 'M' && newpatient->info.gender != 'F')
            {
                printf("choose a valid option\n");
            scanf(" %c",&newpatient->info.gender);
            newpatient->info.gender = toupper(newpatient->info.gender);
            }

            printf("Date of Birth of the patient (year,month,day)\n");
            scanf("%d",& newpatient->info.birth.year);
            scanf("%d",&newpatient->info.birth.month);
            scanf("%d",&newpatient->info.birth.day);

            while ((newpatient->info.birth.year<1900 || newpatient->info.birth.year > 2026) || (newpatient->info.birth.month<0 || newpatient->info.birth.month>12) || (newpatient->info.birth.day<0 || newpatient->info.birth.day>31)){
            printf("Enter a valid Date\n");
            scanf("%d",& newpatient->info.birth.year);
            scanf("%d",&newpatient->info.birth.month);
            scanf("%d",&newpatient->info.birth.day);
            }

            head = ADD(head, newpatient);
            printf("Patient Added successfully\n");

            
        }
    }

    else if(choice == 2){
        printf("The first name of the patient you are searching for\n");
        scanf("%s",temp->info.firstname);
        printf("The last name of the patient you are searching for\n");
        scanf("%s",temp->info.lastname);

    }
    printf("What do you want to do\n 0-exit\n 1-Add a patient\n 2-Search for a patient\n 3-Modify a patient\n 4-Delete patient\n 5-list all patient\n\n");
    scanf("%d",&choice);
    }
    
}