//Name: Mahmoud Kamal Aldeen Mahmoud Ali     // B.N: 141083

#include <stdio.h>
#include <stdlib.h> 
#include<string.h>
#include <time.h>
#include <ctype.h>

	struct patient_node{		//struct to store patient data each patient as node in linked-list data strucutre
		char name[100];
		unsigned long long int id;
		char address[150];
		int clinic_number;
		struct patient_node*next;  //this pointer holds the address of the next node in the linked-list data strucutre 
	}; 
	
patient_node*head =NULL;



//Function Declarartions//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void empty_stdin (void);
void append(char pat_name[], long long int id_num, char pat_address[], int clin_num);
void add_patient();
void remove(int clin_num);
void display();
int no_of_patients();
void check_patient(int clin_num);
int generate_clin_number();
void menu();
unsigned int no_oper();
int go_back();
int no_of_lines();
void order();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	FILE *fptr;				// pointer to file in order to open it
	fptr=fopen("names.txt","w"); 		// this line to erase any old data in the file every time the program run
        int flag;							// this flag takes 0 or 1 value from user to return to menu or exit 
	
	
        while (1){ 						// the while loop keeps on repeating until the user enters 0 to exit from program and not  to return to menu
        menu();
	
	
        switch(no_oper())
        {
		
		
            case 1: {
		     add_patient();
                       flag=go_back();  //asks the user if he want to go back to main menu or to close program
	    break;}
	    
	    
            case 2:{
                printf("------------------------------\n");
		printf("please enter clinic number\n");
		int clin_num;
		scanf("%d",&clin_num);
		check_patient(clin_num);
                flag=go_back();
	    break;}
	    
	    
            case 3:{
                printf("------------------------------\n");
		printf("please enter clinic number\n");
		int clin_num;
		scanf("%d",&clin_num);
		remove(clin_num);
                flag=go_back();
	    break;}
	    
	    
            case 4:{
                printf("------------------------------\n");
                display();
                flag=go_back();
	    break;}  
	    
	    
            case 5:{
			order();
			flag=go_back();
	    break;}


            }


        if (flag==0){ 
		break;}    //if user entered 0 this means he wants to close program
        }

	return 0;
}






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void empty_stdin (void) /* simple helper-function to empty stdin */
{
    int c = getchar();

    while (c != '\n' && c != EOF)
        c = getchar();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// this append function will take data from user, create new struct on the heap and store the data in it 
// without any waste of memory and without knowing the number of patients
void append(char pat_name[], long long int id_num, char pat_address[], int clin_num){
	struct patient_node* new_patient = (struct patient_node*)malloc(sizeof(struct patient_node)); 
	strcpy(new_patient->name, pat_name);
	new_patient->id = id_num;
	strcpy(new_patient->address, pat_address);
	new_patient->clinic_number=clin_num;
	new_patient->next=NULL;
	if(head==NULL){
		head = new_patient;
	}
	else {
		patient_node*temp = head;
		while(temp->next!=NULL){
			temp = temp->next;
		}
		temp->next=new_patient;
	}
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// in order to sort the names of the patients, their taken names are stored in file first  and 
//then these names are read from file and sorted

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void add_patient(){
	printf("------------------------------\n");
		printf("please enter the following data\n");
		char pat_name[100];
		printf("Patient name:");
		fgets(pat_name,100,stdin);
		//////////////////////////////
		FILE*fptr=NULL;
		fptr=fopen("names.txt","a");
		if(fptr == NULL)
				   {
				      printf("Error!");   
				      exit(1);             
				   }
		fprintf(fptr,"%s",pat_name);
		fclose(fptr);
		printf("Id number:");
		long long int id_num;
		scanf("%lld",&id_num);
		empty_stdin();
		char pat_address[150];
		printf("Address:");
		fgets(pat_address,150,stdin);
		int clin_num = generate_clin_number();
		append(pat_name,id_num,pat_address,clin_num);
		printf("Done! the clinic number is %d ", clin_num);
                
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//the next function deletes patient (node) from the linked list data structure by unlinking it and then (free) its address


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void remove(int clin_num){
	if(head==NULL){
		return;
	}
	patient_node* prev, *temp;
	prev=temp=head;
	if(head->clinic_number==clin_num){
		head=temp->next;
		delete temp;
		return;
	}
	while (temp!=NULL&&temp->clinic_number!=clin_num){
		prev = temp;
		temp=temp->next;
	}
	
	if (temp==NULL) return;
	else {
		prev->next = temp->next;
		delete temp;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//simple funtion to display the patient record
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void display(){
	patient_node*temp = head;
	while(temp!=NULL){
		printf("name: %s",temp->name);
		printf("id: %llu\n",temp->id);
		printf("address: %s",temp->address);
		printf("clinic number: %d\n",temp->clinic_number);
		printf("=========\n");
		temp=temp->next;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//the function tells the number of patients recorded
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int no_of_patients(){
	patient_node*temp = head;
	int count = 0;
		while(temp!=NULL){
		temp=temp->next;
		++count;
	}
	return count;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//this function loops through the whole linked-list data structure till the
// next of node is null to compare data value to check exsiting patient
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void check_patient(int clin_num) {
	   //start from the first link
	   struct patient_node* current = head;

	   //if list is empty
	   if(head == NULL) {
	      printf("registery is empty\n");
	      return;
	   }

	   //navigate through list
	   while(current->clinic_number != clin_num) {
		
	      //if it is last node
	      if(current->next == NULL) {
		printf("Patient number %d is not found\n", clin_num );
		return;
	      } else {
		 //go to next link
		 current = current->next;
	      }
	   }      
		
	   //if data found, return the current Link

	  printf("patient number %d is found\n", clin_num);
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//this function generates random number to assign as clinic number of patient
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int generate_clin_number(){
		    srand(time(0));
		    int num = rand()%1000;
		    return num;        
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
//simple function to display the menu
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void menu(){
                printf("Welcome to the banking system!\n------------------------------\nMenu:\n"
                       "1)Register new patient\n"
                       "2)Check already registered patient\n"
                       "3)Delete a patient registeration\n"
                       "4)Display all patients\n"
                       "5)Sort names of patients\n"
                       "------------------------------\n"
                       );
        }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	
//this function takes the number of operation to process from the user
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	unsigned int no_oper()
          {
		printf("Please, type the number of operation to process: ");
		unsigned int input;
		for (;;) {
				    printf("Please, type the number of operation to process: ");
				    scanf("%d",&input);
				    empty_stdin ();
				    if(input==1||input==2||input==3||input==4||input==5) {
					break;                    
				    }
				    printf("Invalid selection, choose again.\n");
			     }
		return input;
          } 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	  
	  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	      int go_back(){
                printf("Enter 1 to return to main menu and 0 to exit\n");    // helping the user to make more than one operation in one run
                int flag;
                scanf("%d",&flag);
		system("cls");
                return flag;
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// to sort the names of the patients, we need to know how many patients we have, this function counts this from the
// names registered in the file 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int no_of_lines() 
		{ 
		    FILE *fp; 
		    int count = 0;  // Line counter (result) 
		    char filename[100] = "names.txt";
		    char c;  
		  

		    fp = fopen(filename, "r"); 
		    if (fp == NULL) 
		    { 
			printf("Could not open file %s", filename); 
			return 0; 
		    } 

		    for (c = getc(fp); c != EOF; c = getc(fp)) 
			if (c == '\n')
			    count = count + 1; 
		    fclose(fp); 
		   return count;

		} 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//the order function depends on comparing each char using strcmp function 
// as it compares each char and if it is before or after the next entered char returing 1 or -1
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void order(){
		int i,j;
		char str[25][25],temp[25];
		 int count;
	int choice = 1;
			printf("Enter 1 to ascending order or 2 to descending order\n");
			scanf("%d",&choice);
			empty_stdin();
			   count = no_of_lines();
				FILE*fptr=NULL;
				fptr=fopen("names.txt","r");
				if(fptr == NULL)
				   {
				      printf("Error!");   
				      exit(1);             
				   }
			  for(int i=0;i<=count;i++)
			   fgets(str[i],100,fptr);
				if(choice==1){
					for(int i=0;i<=count;i++)
				      for(int j=i+1;j<=count;j++){
					 if(strcmp(str[i],str[j])>0){
					    strcpy(temp,str[i]);
					    strcpy(str[i],str[j]);
					    strcpy(str[j],temp);
				 }
			    }
			    
			    printf("Ordered Names:\n");
				for(int i=0;i<=count;i++)
				puts(str[i]);
				}
				if(choice==2){
				for(i=0;i<=count;i++)
			      for(j=i+1;j<=count;j++){
				 if(strcmp(str[i],str[j])<0){
				    strcpy(temp,str[i]);
				    strcpy(str[i],str[j]);
				    strcpy(str[j],temp);
				 }
			      }
				
				printf("Ordered Names:\n");
				for(int i=0;i<=count;i++)
				puts(str[i]);
				
				}
			      fclose(fptr);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


