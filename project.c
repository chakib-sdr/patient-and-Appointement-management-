#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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


typedef struct appointment {
    int id;
    int patient_id;
    date appointment_date;
    time appointment_time;
} appointment;

typedef struct node_appointement
{
    appointment info;
    struct node_appointement *next;
}node_appointement;


node_patient *ADD_patient(node_patient *head, node_patient *newpatient){
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

int search_patient(node_patient *head,patient x){
    node_patient *temp;
    temp = head;
    while (temp != NULL)
    {
        if(strcmp(temp->info.firstname, x.firstname) == 0 && strcmp(temp->info.lastname, x.lastname)==0){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

node_patient *modify_patient(node_patient *head,int x){
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

node_patient *delete_patient(node_patient *head,int x){
    node_patient *prev,*curr;
    prev = NULL; curr = head;
    if (curr == NULL) {
        printf("the patient does not exist\n");
        return head;
    }
    if(curr->info.id == x){
        head = curr->next;
        free(curr);
        return head;
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
    return head;

}

node_appointement *ADD_appointement(node_appointement *head,node_appointement *newappointement){
    node_appointement *tail;
    newappointement->next = NULL;
    if(head == NULL){
        head = newappointement;
    }else{
        tail = head;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = newappointement;
    }
    return head;
}


int search_appointement(node_appointement *head,date temp){
        node_appointement *temp1;
        temp1 = head;
        printf("The Date of the appointement\n");
        while (temp1 != NULL)
        {
            if(temp1->info.appointment_date.year == temp.year && temp1->info.appointment_date.month == temp.month && temp1->info.appointment_date.day == temp.day){
                return 1;
            }
            temp1 = temp1->next;
        }
        return 0;
}

node_appointement *modify_appointement(node_appointement *head,int x){
    node_appointement *temp;
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


node_appointement *delete_appointement(node_appointement *head,int x){
    node_appointement *prev,*curr;
    prev = NULL; curr = head;
    if (curr == NULL) {
        printf("this appointement does not exist\n");
        return head;
    }
    if(curr->info.id == x){
        head = curr->next;
        free(curr);
        return head;
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
    return head;
}


int main(){
    printf("Title of The Project: Patient and Appointment Management\n");
    printf("Group number: 10\n");
    printf("Made by:\n\n\n");



    printf("|_________________________________________________|\n\n\n");

    printf("Welcome to the clinic\n\n");
    printf("Which management to choose 0-exit 1-Patient Management 2-Appointement Managemnt\n");
    int choice_management;
    scanf("%d",&choice_management);
    while (choice_management <0 || choice_management>2)
    {
    scanf("%d",&choice_management);       
    }
    /*Declared the heads here so they are not reset every loop and lose the patient and appointement lists*/
        node_patient *head; 
        head = NULL;
        int nextid = 1;
        node_appointement *head1; 
        head1 = NULL;
        int nextid_appointement = 1;
while (choice_management != 0)
{

    if(choice_management == 1){
    printf("What do you want to do\n 0-exit\n 1-Add a patient\n 2-Search for a patient\n 3-Modify a patient\n 4-Delete patient\n 5-list all patient\n\n");
    int choice;
    scanf("%d",&choice);
    while (choice < 0 || choice > 5){
        printf("Enter a valid choice\n");
    scanf("%d",&choice);   
    }
    
    while (choice != 0)
    {
  
    if(choice == 1){

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

            head = ADD_patient(head, newpatient);
    printf("======================================\n");
            printf("Patient Added successfully\n");
    printf("======================================\n");

            
        }
    }


    else if(choice == 2){
        patient temp;
        printf("The first name of the patient you are searching for\n");
        scanf("%s",temp.firstname);
        printf("The last name of the patient you are searching for\n");
        scanf("%s",temp.lastname);
        
        if(search_patient(head,temp)){
    printf("======================================\n");
            printf("patient Found\n");
    printf("======================================\n");
    }else{
    printf("======================================\n");
        printf("This patient does not exist\n");
    printf("======================================\n");
    }

    }

    
    else if(choice == 3){
        int id;
        node_patient *temp;
        printf("The id of the patient you want to modify\n");
        scanf("%d",&id);
        if(modify_patient(head,id) == NULL){
            printf("patient not found\n");
        }else{
            temp = modify_patient(head,id);
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
                printf("======================================\n");
                printf("First name modified\n");
                printf("======================================\n");
            }else if( c == 2){
                printf("Enter the new Last_name\n");
                scanf("%s",temp->info.lastname);
                printf("======================================\n");
                printf("Last name modified\n");
                printf("======================================\n");
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
            printf("======================================\n");
            printf("Date of birth modified\n");
            printf("======================================\n");
            }else{
            printf("Enter the new Gender\n");
            scanf(" %c",&temp->info.gender);
            temp->info.gender = toupper(temp->info.gender);
            while (temp->info.gender != 'M' && temp->info.gender != 'F')
            {
                printf("choose a valid option\n");
            scanf(" %c",&temp->info.gender);
            temp->info.gender = toupper(temp->info.gender);
            }
            printf("======================================\n");
            printf("Gender modified\n");
            printf("======================================\n");               
            }
        }


    }else if(choice == 4){
        int id;
        printf("The id of the patient you want to delete\n");
        scanf("%d",&id);
        printf("\n");
        if (modify_patient(head, id) != NULL) { /*since modify function check if the patient exist and return it*/
        head = delete_patient(head, id);
    printf("======================================\n");     
        printf("Patient deleted successfully\n");
    printf("======================================\n\n");
        } else {
    printf("======================================\n");
    printf("Patient not found");
    printf("======================================\n\n");
    }

    }else{
        node_patient *temp;
        temp = head;
        printf("\n========== LIST OF PATIENTS ==========\n\n");
    while (temp != NULL)
    {
        printf("ID:%d\nFirst name: %s\nLast name: %s\nDate of birth: %d %d %d \nGender:%c\n\n",temp->info.id, temp->info.firstname, temp->info.lastname, temp->info.birth.year , temp->info.birth.month , temp->info.birth.day, temp->info.gender);
        temp = temp->next;
    }
    printf("======================================\n\n");
    }

    printf("What do you want to do\n 0-exit\n 1-Add a patient\n 2-Search for a patient\n 3-Modify a patient\n 4-Delete patient\n 5-list all patient\n\n");
    scanf("%d",&choice);
    }


}




    else{
    printf("What do you want to do\n 0-exit\n 1-Add an appointement\n 2-Search for a specified appointement\n 3-Modify an appointement\n 4-Delete an appointement\n 5-list all appointement\n\n");
    int choice;
    scanf("%d",&choice);
    while (choice < 0 || choice > 5){
        printf("Enter a valid choice\n");
    scanf("%d",&choice);   
    }
    
    while (choice != 0){
    if(choice == 1){

        printf("How many Appointement you want to Add\n");
        int n,i;
        while (scanf("%d", &n) != 1 || n < 0) /*A boolean for scanf to make sure that thee entered value is an int*/
        {
        printf("Enter a valid option\n");     
        }

        for(i = 0; i<n; i++){
        node_appointement *newappointement = malloc(sizeof(node_appointement));
    
            printf("The ID of the patient who get this appointement\n");
            scanf("%d",&newappointement->info.patient_id);
            while (modify_patient(head,newappointement->info.patient_id) == NULL && newappointement->info.patient_id!=0)
            {
                printf("This patient does not exist, enter a valid patient id or 0 to exit\n");
                scanf("%d",&newappointement->info.patient_id);
            }
            if (newappointement->info.patient_id == 0)
            {
                printf("Appointement canceled\n");
                break;
            }
            

            printf("Date of the appointement (year,month,day)\n");
            scanf("%d",& newappointement->info.appointment_date.year);
            scanf("%d",&newappointement->info.appointment_date.month);
            scanf("%d",&newappointement->info.appointment_date.day);
            printf("\n");
            while ((newappointement->info.appointment_date.year<2026) || (newappointement->info.appointment_date.month<0 || newappointement->info.appointment_date.month>12) || (newappointement->info.appointment_date.day<0 || newappointement->info.appointment_date.day>31)){
            printf("Enter a valid Date\n");
            scanf("%d",&newappointement->info.appointment_date.year);
            scanf("%d",&newappointement->info.appointment_date.month);
            scanf("%d",&newappointement->info.appointment_date.day);
            }

            printf("Enter the time (hour, minute)\n");
            scanf("%d", &newappointement->info.appointment_time.hour);
            scanf("%d", &newappointement->info.appointment_time.min);

            while (newappointement->info.appointment_time.hour < 0 ||
            newappointement->info.appointment_time.hour > 23 ||
            newappointement->info.appointment_time.min < 0 ||
            newappointement->info.appointment_time.min > 59) {
            printf("Enter a valid time\n");
            scanf("%d", &newappointement->info.appointment_time.hour);
            scanf("%d", &newappointement->info.appointment_time.min);
            

            printf("\n");
            }

            newappointement->info.id = nextid_appointement;
            nextid_appointement++;

            head1 = ADD_appointement(head1, newappointement);
    printf("======================================\n");
            printf("Appointement Added successfully\n");
    printf("======================================\n");
 
        }
    }else if (choice == 2){
        date temp;

        printf("The Date of the appointement\n");
        scanf("%d",&temp.year);
        scanf("%d",&temp.month);
        scanf("%d",&temp.day);
        if(search_appointement(head1,temp)){
                printf("======================================\n");
                printf("Found the appointement\n");
                printf("======================================\n");
        }else{
            printf("======================================\n");
            printf("This appointement does not exist\n");
            printf("======================================\n");
        }
    }else if (choice == 3){
        int id;
        node_appointement *temp;
        printf("The id of the Appointement you want to modify\n");
        scanf("%d",&id); 
        if(modify_appointement(head1,id) == NULL){
            printf("======================================\n");
            printf("Appointement not found\n");
            printf("======================================\n");
        }else{
         temp = modify_appointement(head1,id);
            printf("What do you want to modify\n 1-which patient get the appointement\n 2-the date of the appointement\n 3-the time of the appointement\n");
            int c;
            scanf("%d",&c);
            while (c<1 || c>3)
            {
                printf("Enter a valid option\n");
                scanf("%d",&c);
            }
            if(c == 1){
                printf("Enter the new id of the patient who get the appointement\n");
                scanf("%d",&temp->info.patient_id);
                printf("======================================\n");
                printf("Patient id odified modified\n");
                printf("======================================\n");
            }else if (c == 2){
                printf("Enter the new date");
            scanf("%d",& temp->info.appointment_date.year);
            scanf("%d",&temp->info.appointment_date.month);
            scanf("%d",&temp->info.appointment_date.day);
            
            while ((temp->info.appointment_date.year < 2026) || (temp->info.appointment_date.month<1 || temp->info.appointment_date.month>12) || (temp->info.appointment_date.day<1 || temp->info.appointment_date.day>31)){
            printf("Enter a valid Date\n");
            scanf("%d",& temp->info.appointment_date.year);
            scanf("%d",&temp->info.appointment_date.month);
            scanf("%d",&temp->info.appointment_date.day);
            }
            printf("======================================\n");
            printf("Date of appointement modified\n");
            printf("======================================\n");
            }else{

                printf("Enter the new time (hour, minute)\n");
                scanf("%d", &temp->info.appointment_time.hour);
                scanf("%d", &temp->info.appointment_time.min);

                while (temp->info.appointment_time.hour < 0 ||
                 temp->info.appointment_time.hour > 23 ||
                temp->info.appointment_time.min < 0 ||
                temp->info.appointment_time.min > 59) {
                printf("Enter a valid time\n");
                scanf("%d", &temp->info.appointment_time.hour);
                scanf("%d", &temp->info.appointment_time.min);
                }
            printf("======================================\n");
            printf("Time modified\n");
            printf("======================================\n"); 
            }
              
            }
        }else if(choice == 4){
        int id;
        printf("The id of the appointement you want to delete\n");
        scanf("%d",&id);
        printf("\n");
        if (modify_appointement(head1, id) != NULL) { /*since modify function check if the patient exist and return it*/
        head1 = delete_appointement(head1, id);
    printf("======================================\n");     
        printf("appointement deleted successfully\n");
    printf("======================================\n\n");
        }else {
    printf("======================================\n");
    printf("appointement not found\n");
    printf("======================================\n\n");
    }

        }
        else{
        node_appointement *temp;
        temp = head1;
        printf("\n========== LIST OF Appointements ==========\n\n");
    while (temp != NULL)
    {
        printf("ID:%d\nPatient_id:%d\nDate of the appointement: %d %d %d \nTime:%d : %d\n\n",temp->info.id, temp->info.patient_id, temp->info.appointment_date.year , temp->info.appointment_date.month , temp->info.appointment_date.day, temp->info.appointment_time.hour,temp->info.appointment_time.min);
        temp = temp->next;
    }
    printf("======================================\n\n");
    }

    printf("What do you want to do\n 0-exit\n 1-Add an appointment\n 2-Search for an appointement\n 3-Modify an appointement\n 4-Delete an appointement\n 5-list all appointement\n\n");
    scanf("%d",&choice);

        }


    
    }



    printf("Which management to choose 0-exit 1-Patient Management 2-Appointement Managemnt\n");
    scanf("%d",&choice_management);
    while (choice_management <0 || choice_management>2)
    {
        printf("Enter a valid option\n");
    scanf("%d",&choice_management);       
    }
}
}
