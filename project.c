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
    char phone[15];             
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
    char reason[50];               
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

/* displays every patient with this first name and last name (several patients can match) and returns how many were found */
int search_patient(node_patient *head,patient x){
    node_patient *temp;
    int count = 0;
    temp = head;
    while (temp != NULL)
    {
        if(strcmp(temp->info.firstname, x.firstname) == 0 && strcmp(temp->info.lastname, x.lastname)==0){
            printf("ID:%d\nFirst name: %s\nLast name: %s\nDate of birth: %d %d %d \nGender:%c\nPhone: %s\n\n",temp->info.id, temp->info.firstname, temp->info.lastname, temp->info.birth.year , temp->info.birth.month , temp->info.birth.day, temp->info.gender, temp->info.phone);
            count++;
        }
        temp = temp->next;
    }
    return count;
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


/* displays all the appointements of the date sorted by time and returns how many were found */
int search_appointement(node_appointement *head, date d) {
    node_appointement *temp;
    int count = 0, i, j;

    temp = head;

    /* Count appointments on this date */
    while (temp != NULL) {
        if (temp->info.appointment_date.year == d.year && temp->info.appointment_date.month == d.month && temp->info.appointment_date.day == d.day) {
            count++;
        }
        temp = temp->next;
    }

    if (count == 0)
        return 0;

    node_appointement *arr[count];


    temp = head;
    i = 0;

    while (temp != NULL) {
        if (temp->info.appointment_date.year == d.year && temp->info.appointment_date.month == d.month && temp->info.appointment_date.day == d.day) {
            arr[i] = temp;
            i++;
        }
        temp = temp->next;
    }

    /*sort by appointment time */
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            int time1 = arr[j]->info.appointment_time.hour * 60 + arr[j]->info.appointment_time.min;
            int time2 = arr[j + 1]->info.appointment_time.hour * 60 + arr[j + 1]->info.appointment_time.min;

            if (time1 > time2) {
                node_appointement *swap = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = swap;
            }
        }
    }

    /* Display appointments in chronological order */
    for (i = 0; i < count; i++) {
        temp = arr[i];

        printf("ID:%d\nPatient_id:%d\nDate: %d %d %d\nTime:%02d:%02d\nReason: %s\n\n",
               temp->info.id,
               temp->info.patient_id,
               temp->info.appointment_date.year,
               temp->info.appointment_date.month,
               temp->info.appointment_date.day,
               temp->info.appointment_time.hour,
               temp->info.appointment_time.min,
               temp->info.reason);
    }

    return count;
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


int check_appointement(node_appointement *head, appointment a){
    node_appointement *temp;
    temp = head;
    while (temp != NULL)
    {

        if (temp->info.id != a.id &&
            temp->info.appointment_date.year  == a.appointment_date.year  &&
            temp->info.appointment_date.month == a.appointment_date.month &&
            temp->info.appointment_date.day   == a.appointment_date.day   &&
            temp->info.appointment_time.hour  == a.appointment_time.hour  &&
            temp->info.appointment_time.min   == a.appointment_time.min){
            return 1;
            }
    temp = temp->next;
    
}
    return 0;
    }


void sort_appointments(node_appointement *head1, int id)
{
    node_appointement *temp = head1;
    int count = 0;

    while (temp != NULL)
    {
        if (temp->info.patient_id == id)
            count++;

        temp = temp->next;
    }

    if (count == 0)
    {
        printf("This patient has no appointment\n");
        return;
    }

    node_appointement *arr[count];

    temp = head1;
    int i = 0;
    int j;
    while (temp != NULL)
    {
        if (temp->info.patient_id == id)
        {
            arr[i] = temp;
            i++;
        }

        temp = temp->next;
    for (i = 0; i < count - 1; i++)
    {
        for (j = 0; j < count - 1 - i; j++)
        {
            /*we multiply so its easy to compare ex (2026.1.5) will be 202615*/
            int date1 = arr[j]->info.appointment_date.year * 10000 + arr[j]->info.appointment_date.month * 100 + arr[j]->info.appointment_date.day;

            int date2 = arr[j + 1]->info.appointment_date.year * 10000 + arr[j + 1]->info.appointment_date.month * 100 + arr[j + 1]->info.appointment_date.day;

            int time1 = arr[j]->info.appointment_time.hour * 60 + arr[j]->info.appointment_time.min;

            int time2 = arr[j + 1]->info.appointment_time.hour * 60 + arr[j + 1]->info.appointment_time.min;
            if (date1 > date2 || (date1 == date2 && time1 > time2))
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
}


int main(){
    printf("Title of The Project: Patient and Appointment Management\n");
    printf("Group number: 10\n");
    printf("Made by:\n\n\n");



    printf("|_________________________________________________|\n\n\n");

    printf("Welcome to the clinic\n\n");
    printf("Which management to choose 0-exit 1-Patient Management 2-Appointement Managemnt 3-Statistics\n");
    int choice_management;
    scanf("%d",&choice_management);
    while (choice_management <0 || choice_management>3)
    {
    scanf("%d",&choice_management);       
    }
    /*declared the heads here so they are not reset every loop and lose the patient and appointement lists*/
        node_patient *head; 
        head = NULL;
        node_appointement *head1; 
        head1 = NULL;
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

            printf("The ID of the patient\n");
            scanf("%d",&newpatient->info.id);
            while (newpatient->info.id <= 0 || modify_patient(head,newpatient->info.id) != NULL)
            {
                printf("This ID is invalid or already used, enter another ID\n");
                scanf("%d",&newpatient->info.id);
            }

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
            while ((newpatient->info.birth.year<1900 || newpatient->info.birth.year > 2026) || (newpatient->info.birth.month<1 || newpatient->info.birth.month>12) || (newpatient->info.birth.day<1 ||newpatient->info.birth.day>31)){
            printf("Enter a valid Date\n");
            scanf("%d",& newpatient->info.birth.year);
            scanf("%d",&newpatient->info.birth.month);
            scanf("%d",&newpatient->info.birth.day);
            printf("\n");
            }


            printf("The phone number of the patient\n");
            scanf("%10s",newpatient->info.phone);
            while (strlen(newpatient->info.phone)!=10)
            {
                printf("Enter a Valid phone number\n");
                scanf("%10s",newpatient->info.phone);               
            }
            

            head = ADD_patient(head, newpatient);
    printf("======================================\n");
            printf("Patient Added successfully\n");
    printf("======================================\n");

            
        }
    }


    else if(choice == 2){

        int by;
        printf("Search by 1-ID 2-Name\n");
        scanf("%d",&by);
        while (by < 1 || by > 2)
        {
            printf("Enter a valid option\n");
            scanf("%d",&by);
        }
        if(by == 1){
            int id;
            node_patient *found;
            printf("The id of the patient you are searching for\n");
            scanf("%d",&id);
            found = modify_patient(head,id);
            if(found != NULL){
    printf("======================================\n");
                printf("patient Found\n");
    printf("======================================\n");
                printf("ID:%d\nFirst name: %s\nLast name: %s\nDate of birth: %d %d %d \nGender:%c\nPhone: %s\n\n",found->info.id, found->info.firstname, found->info.lastname, found->info.birth.year , found->info.birth.month , found->info.birth.day, found->info.gender, found->info.phone);
            }else{
    printf("======================================\n");
                printf("This patient does not exist\n");
    printf("======================================\n");
            }
        }else{
            patient temp;
            printf("The first name of the patient you are searching for\n");
            scanf("%s",temp.firstname);
            printf("The last name of the patient you are searching for\n");
            scanf("%s",temp.lastname);
            printf("\n");

            if(search_patient(head,temp) > 0){
    printf("======================================\n");
            printf("patient Found\n");
    printf("======================================\n");
    
            }else{
    printf("======================================\n");
            printf("This patient does not exist\n");
    printf("======================================\n");
            }
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
            printf("What do you want to modify\n 1-First_name\n 2-Last_name\n 3-Date of birth\n 4-gender\n 5-phone number\n");
            int c;
            scanf("%d",&c);
            while (c<1 || c>5)
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
            }else if (c == 4){
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
            }else{
            
            printf("Enter the new phone number\n");
            scanf("%10s",temp->info.phone);
            while (strlen(temp->info.phone)!=10)
            {
                printf("Enter a Valid phone number\n");
                scanf("%12s",temp->info.phone);               
            }
            printf("======================================\n");
            printf("Phone number modified\n");
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
        /*After deleting a patient its appointement should be deleted*/
        node_appointement *temp = head1;
        while (temp != NULL) {
            node_appointement *next = temp->next;
            if (temp->info.patient_id == id)
            head1 = delete_appointement(head1, temp->info.id);
            temp = next;
    }
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
        printf("ID:%d\nFirst name: %s\nLast name: %s\nDate of birth: %d %d %d \nGender:%c\nPhone: %s\n\n",temp->info.id, temp->info.firstname, temp->info.lastname, temp->info.birth.year , temp->info.birth.month , temp->info.birth.day, temp->info.gender, temp->info.phone);
        temp = temp->next;
    }
    printf("======================================\n\n");
    }

    printf("What do you want to do\n 0-exit\n 1-Add a patient\n 2-Search for a patient\n 3-Modify a patient\n 4-Delete patient\n 5-list all patient\n\n");
    scanf("%d",&choice);
    while (choice<0 || choice >5)
    {
        printf("Enter a valid option\n");
        scanf("%d",&choice);
    }
    
    }


}




    else if(choice_management == 2){
    printf("What do you want to do\n 0-exit\n 1-Add an appointement\n 2-Display the appointements of a day\n 3-Modify an appointement\n 4-Delete an appointement\n 5-list all appointement\n 6-Display the appointements of a patient\n 7-Find available time slots\n\n");
    int choice;
    scanf("%d",&choice);
    while (choice < 0 || choice > 7){
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

            
            printf("The number of the appointement\n");
            scanf("%d",&newappointement->info.id);
            while (newappointement->info.id <= 0 || modify_appointement(head1,newappointement->info.id) != NULL)
            {
                printf("This number is invalid or already used, enter another number\n");
                scanf("%d",&newappointement->info.id);
            }
    
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
                free(newappointement);
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

            
            printf("The reason of the consultation\n");
            scanf(" %49[^\n]", newappointement->info.reason);

            if (check_appointement(head1, newappointement->info)) {
                printf("This time slot is already booked\n");
                free(newappointement);
                continue;
                }

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
        printf("\n");
        if(search_appointement(head1,temp) > 0){
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
            printf("What do you want to modify\n 1-which patient get the appointement\n 2-the date of the appointement\n 3-the time of the appointement\n 4-the reason of the appointement\n");
            int c;
            scanf("%d",&c);
            while (c<1 || c>4)
            {
                printf("Enter a valid option\n");
                scanf("%d",&c);
            }
            if(c == 1){
                
                int newid;
                printf("Enter the new id of the patient who get the appointement\n");
                scanf("%d",&newid);
                while (modify_patient(head,newid) == NULL)
                {
                    printf("This patient does not exist, enter a valid patient id\n");
                    scanf("%d",&newid);
                }
                temp->info.patient_id = newid;
                printf("======================================\n");
                printf("Patient id modified modified\n");
                printf("======================================\n");
            }else if (c == 2){
                
                date olddate;
                olddate = temp->info.appointment_date;
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
            if (check_appointement(head1, temp->info)) {
                temp->info.appointment_date = olddate;
                printf("======================================\n");
                printf("This time slot is already booked, date not modified\n");
                printf("======================================\n");
            }else{
            printf("======================================\n");
            printf("Date of appointement modified\n");
            printf("======================================\n");
            }
            }else if (c == 3){
            
                time oldtime;
                oldtime = temp->info.appointment_time;

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
                if (check_appointement(head1, temp->info)) {
                    temp->info.appointment_time = oldtime;
                    printf("======================================\n");
                    printf("This time slot is already booked, time not modified\n");
                    printf("======================================\n");
                }else{
            printf("======================================\n");
            printf("Time modified\n");
            printf("======================================\n"); 
                }
            }else{

                printf("Enter the new reason of the consultation\n");
                scanf(" %49s", temp->info.reason);
                printf("======================================\n");
                printf("Reason modified\n");
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
        else if(choice == 5){
        node_appointement *temp;
        temp = head1;
        printf("\n========== LIST OF Appointements ==========\n\n");
    while (temp != NULL)
    {
        printf("ID:%d\nPatient_id:%d\nDate of the appointement: %d %d %d \nTime:%d : %d\nReason: %s\n\n",temp->info.id, temp->info.patient_id, temp->info.appointment_date.year , temp->info.appointment_date.month , temp->info.appointment_date.day, temp->info.appointment_time.hour,temp->info.appointment_time.min, temp->info.reason);
        temp = temp->next;
    }
    printf("======================================\n\n");
    }else if(choice == 6){
        
        int id;
        printf("The id of the patient\n");
        scanf("%d",&id);
        if(modify_patient(head,id) == NULL){
            printf("======================================\n");
            printf("Patient not found\n");
            printf("======================================\n\n");
        }else{
            sort_appointments(head1, id);
            node_appointement *temp;
            temp = head1;
            printf("\n========== APPOINTEMENTS OF THE PATIENT ==========\n\n");
            while (temp != NULL)
            {
                    printf("ID: %d\n", temp->info.id);
                    printf("Date: %d/%d/%d\n",temp->info.appointment_date.day,temp->info.appointment_date.month,temp->info.appointment_date.year);
                    printf("Time: %02d:%02d\n",temp->info.appointment_time.hour,temp->info.appointment_time.min);
                    printf("Reason: %s\n\n", temp->info.reason);
                temp = temp->next;
            }
            

        }
    }else{
        
        date d;
        appointment a;
        int h, m, found = 0;
        printf("The Date (year,month,day)\n");
        scanf("%d",&d.year);
        scanf("%d",&d.month);
        scanf("%d",&d.day);
        a.id = 0;
        a.appointment_date = d;
        printf("\nAvailable time slots on %d %d %d :\n", d.year, d.month, d.day);
        for (h = 8; h < 17; h++)
        {
            for (m = 0; m < 60; m += 30)
            {
                a.appointment_time.hour = h;
                a.appointment_time.min = m;
                if (!check_appointement(head1, a)){
                    printf("%02d:%02d\n", h, m); /*%02 is usedto display in time format*/
                    found = 1;
                }
            }
        }
        if (!found) printf("No available time slot on this day\n");
        printf("\n");
    }

    printf("What do you want to do\n 0-exit\n 1-Add an appointment\n 2-Display the appointements of a day\n 3-Modify an appointement\n 4-Delete an appointement\n 5-list all appointement\n 6-Display the appointements of a patient\n 7-Find available time slots\n\n");
    scanf("%d",&choice);
    while (choice<0 || choice>7)
    {
        printf("Enter a valid option\n");
        scanf("%d",&choice);
    }
    
        }


    
    }

    else{

        node_patient *temp;
        node_appointement *temp1;
        int nb_patients = 0, nb_appointements = 0, nb_day = 0;
        date d;

        temp = head;
        while (temp != NULL) { nb_patients++; temp = temp->next; }
        temp1 = head1;
        while (temp1 != NULL) { nb_appointements++; temp1 = temp1->next; }

        printf("The Date for the statistics (year,month,day)\n");
        scanf("%d",&d.year);
        scanf("%d",&d.month);
        scanf("%d",&d.day);
        while (d.year<2026 || (d.month<1 || d.month>12) || (d.day<1 || d.day>31))
        {
            printf("Enter a valid date\n");
        scanf("%d",&d.year);
        scanf("%d",&d.month);
        scanf("%d",&d.day);       
        }
        
        temp1 = head1;
        while (temp1 != NULL)
        {
            if (temp1->info.appointment_date.year == d.year && temp1->info.appointment_date.month == d.month && temp1->info.appointment_date.day == d.day)
                nb_day++;
            temp1 = temp1->next;
        }
        printf("\n========== STATISTICS ==========\n");
        printf("Total number of patients: %d\n", nb_patients);
        printf("Number of scheduled appointements: %d\n", nb_appointements);
        printf("Number of appointements on %d %d %d : %d\n", d.year, d.month, d.day, nb_day);
        printf("======================================\n\n");
    }



    printf("Which management to choose 0-exit 1-Patient Management 2-Appointement Managemnt 3-Statistics\n");
    scanf("%d",&choice_management);
    while (choice_management <0 || choice_management>3)
    {
        printf("Enter a valid option\n");
    scanf("%d",&choice_management);       
    }
}

    /* free the memory of both lists before terminating */
    node_patient *temp;
    node_appointement *temp1;
    while (head != NULL)
    {
        temp = head->next;
        free(head);
        head = temp;
    }
    while (head1 != NULL)
    {
        temp1 = head1->next;
        free(head1);
        head1 = temp1;
    }
}