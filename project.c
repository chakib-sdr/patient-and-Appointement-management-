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
    int id;
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

int search (node_patient *head,patient x){
    node_patient *temp;
    temp = head;
    while (temp != NULL)
    {
        if(temp->info.firstname == x.firstname && temp->info.lastname == x.lastname){
            return 1;
        }
        temp = temp->next;
    }
    return -1;
}

node_patient *modify(node_patient *head,int x){
    node_patient *temp;
    temp = head;
    while (temp != NULL)
    {
        if(temp->info.id == x){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

node_patient *delete(node_patient *head,int x){
    node_patient *prev,*curr;
    prev = NULL; curr = head;
    if(curr->info.id == x){
        free(curr);
        return curr->next;
    }
    while (curr != NULL)
    {
    if(curr->info.id == x){
        prev->next = curr->next;
        free(curr);
        return head;
    }
    prev = curr;
    curr = curr->next;
    }
    printf("patient not found\n");
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
        patient temp;
        node_patient *head; /*head outside the loop so its ot reseted every time (to keep the previous one)*/
        head = NULL;
        int nextid = 1; 
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
            printf("\n");
            while ((newpatient->info.birth.year<1900 || newpatient->info.birth.year > 2026) || (newpatient->info.birth.month<0 || newpatient->info.birth.month>12) || (newpatient->info.birth.day<0 || newpatient->info.birth.day>31)){
            printf("Enter a valid Date\n");
            scanf("%d",& newpatient->info.birth.year);
            scanf("%d",&newpatient->info.birth.month);
            scanf("%d",&newpatient->info.birth.day);
            printf("\n");
            }

            newpatient->info.id = nextid;
            nextid++;

            head = ADD(head, newpatient);
            printf("Patient Added successfully\n\n\n");

            
        }
    }


    else if(choice == 2){
        patient temp;
        printf("The first name of the patient you are searching for\n");
        scanf("%s",temp.firstname);
        printf("The last name of the patient you are searching for\n");
        scanf("%s",temp.lastname);
        
        if(search(head,temp)){
            printf("patient Found\n");
    }else{
        printf("This patient does not exist\n");
    }
    printf("What do you want to do\n 0-exit\n 1-Add a patient\n 2-Search for a patient\n 3-Modify a patient\n 4-Delete patient\n 5-list all patient\n\n");
    scanf("%d",&choice);

    }

    
    else if(choice == 3){
        int id;
        node_patient *temp;
        printf("The id of the patient you want to modify\n");
        scanf("%d",&id);
        if(modify(head,id) == NULL){
            printf("patient not found\n");
        }else{
            temp = modify(head,id);
            printf("What do you want to modify\n 1-First_name\n 2-Last_name\n 3-Date of birth\n 4-gender\n");
            int c;
            scanf("%d",&c);
            while (c<1 || c>4)
            {
                printf("Enter a valid option\n");
                scanf("%d",&c);
            }
            if(c == 1){
                printf("Enter the new First_name\n");
                scanf("%s", temp->info.firstname);
                printf("First name modified\n");
            }else if( c == 2){
                printf("Enter the new Last_name\n");
                scanf("%s",temp->info.lastname);
                printf("Last name modified\n");
            }else if (c == 3){
                printf("Enter the new date");
            scanf("%d",& temp->info.birth.year);
            scanf("%d",&temp->info.birth.month);
            scanf("%d",&temp->info.birth.day);
            
            while ((temp->info.birth.year<1900 || temp->info.birth.year > 2026) || (temp->info.birth.month<0 || temp->info.birth.month>12) || (temp->info.birth.day<0 || temp->info.birth.day>31)){
            printf("Enter a valid Date\n");
            scanf("%d",& temp->info.birth.year);
            scanf("%d",&temp->info.birth.month);
            scanf("%d",&temp->info.birth.day);
            }
            printf("Date of birth modified\n");
            }else{
            scanf(" %c",&temp->info.gender);
            temp->info.gender = toupper(temp->info.gender);
            while (temp->info.gender != 'M' && temp->info.gender != 'F')
            {
                printf("choose a valid option\n");
            scanf(" %c",&temp->info.gender);
            temp->info.gender = toupper(temp->info.gender);
            }               
            }
        }


    }else if(choice == 4){
        int id;
        printf("The id of the patient you want to delete\n");
        scanf("%d",&id);
        printf("\n");
        head = delete(head,id);
        printf("paitent deleted successfully\n");
    }else{
        node_patient *temp;
        temp = head;
    while (temp != NULL)
    {
        printf("ID:%d\nFirst name: %s\nLast name: %s\nDate of birth: %d %d %d \nGender:%c\n\n",temp->info.id, temp->info.firstname, temp->info.lastname, temp->info.birth.year , temp->info.birth.month , temp->info.birth.day, temp->info.gender);
        temp = temp->next;
    }
    
    }

    printf("What do you want to do\n 0-exit\n 1-Add a patient\n 2-Search for a patient\n 3-Modify a patient\n 4-Delete patient\n 5-list all patient\n\n");
    scanf("%d",&choice);
    }
    
}