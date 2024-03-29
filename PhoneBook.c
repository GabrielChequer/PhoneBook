#include<stdio.h>
#include <stdlib.h>
#include <string.h>


struct phonebook 
{
     char first[30];
     char last [30];
     char phone [30];
     int deleted;
} contacts[10], temp;

int Contact_Number = 0;

void main() {
	int option=0,i,j;
	do{	
		system("CLS");
	    option =0;
		printf("Phone Book Application\n1) Add friend\n2) Delete friend\n3) Show phone book\n4) Display phone book alphabetically\n5) Find contact\n6) Make a random call\n7) Delete everyone\n8) Load contacts\n9) Save contacts\n10) Exit\n");
		scanf("%i",&option);
	    switch(option){         
	    	case 1:
	    		add();
	    		Contact_Number++;
	    		break;                   
	    	case 2:    		
	    		delete();
	    		break;
	    	case 3:
	    		show();
	    		system("PAUSE");
	    		break;
	    	case 4:
	    		alph();
				show();
				system("PAUSE");
	    		break;
	    	case 5:
	    		find();
	    		system("PAUSE");
	    		break;
	    	case 6:
	    		ran_call();
				break;
					printf("Contacts:\n");
	    		del_everyone();
				break;
	    	case 8:
	    		load();
	    		system("PAUSE");
	    		break;
	    	case 9:
	    		sav();
	    		printf("Contacts saved\n");
	    		system("PAUSE");
				break;
	    	case 10:
	    		printf("Thanks for using this app");
	    		break;
	    }
	}while (option<10);
}
add(){
 
	//Student's record
	printf("First name: ");
    scanf("%s",contacts[Contact_Number].first);
	printf("Last name: ");
    scanf("%s",contacts[Contact_Number].last);
    printf("Phone Number: ");
    scanf("%s",contacts[Contact_Number].phone);
}
delete(){
	char fname[30], lname[30];
	int i;
	printf("First name of contact you want to delete: ");
	scanf("%s",&fname);
	printf("Last name of contact you want to delete: ");
	scanf("%s",&lname);
	 //Little bit like the find function but also changes the status of "Deleted"
	for(i=0;i<Contact_Number;i++){
		if(strcmp(contacts[i].first, fname) != 0 && (strcmp(contacts[i].last, lname) != 0)){
				contacts[i].deleted = contacts[i].deleted;
		}
		else{
			contacts[i].deleted=1;
		}
	}
}
show(){
	int i =0;
	for(i=0; i<Contact_Number; i++){
		if(contacts[i].deleted != 1){
	        printf("Name is: %s ", contacts[i].first);
	        printf("%s \n", contacts[i].last);
	        printf("Number is: %s\n",contacts[i].phone);
		}
    }
}
alph(){
	int i=0, j=0;
	for (i = 1; i < Contact_Number; i++){
	    			
					for (j = 0; j < Contact_Number - i; j++) {
				    	if (strcmp(contacts[j].first, contacts[j + 1].first) > 0) {
				    		temp = contacts[j];
				            contacts[j] = contacts[j + 1];
				            contacts[j + 1] = temp;
				        }
				    }
				}
}
find(){
	char fname[30], lname[30];
	int i,c=0;
	printf("First name of contact you want to search: ");
	scanf("%s",&fname);
	printf("Last name of contact you want to search: ");
	scanf("%s",&lname);
	 //Searches for name and last name you introduced
	for(i=0;i<Contact_Number;i++){
		if(strcmp(contacts[i].first, fname)){
			c=1;
		}
		else{
			if(strcmp(contacts[i].last,lname)){
				c=1;
			}
			else{
				if(contacts[i].deleted != 1){
			        printf("Name is: %s ", contacts[i].first);
			        printf("%s \n", contacts[i].last);
			        printf("Number is: %s\n",contacts[i].phone);
			        i==Contact_Number;
			        c=0;
				}
			}
		}
	}
	if(c>0){
		printf("Contact not found");
	}
}
ran_call(){
		//Calls random number
	int r = (rand() % (Contact_Number + 1 - 1)) + 1;
		//You can't call someone you deleted
	if(contacts[r-1].deleted==0){
		printf("Calling %s %s",contacts[r-1].first,contacts[r-1].last);
		printf("(Press enter to continue)");
		system("PAUSE");
	}
	else{
		ran_call(Contact_Number);
	}
}
del_everyone(){
	int i;
		//Everyone gets the status of deleted
	for(i=0;i<Contact_Number;i++){
		contacts[i].deleted=1;
	}
}
load(){
	FILE *in;
	char line[512];
	int x=0,ch=0,num_lineas=0;
	char f[50],l[50],p[10];
	
	if ((in = fopen("file.txt", "r")) == NULL){
		printf("File does not exist");
		in=fopen("file.txt","w");
      	printf("File created");
	}
	else{
   		while ((ch = fgetc(in)) != EOF){
			if (ch == '\n'){
				num_lineas++;
    		}
    	}
		
	    fclose(in);
	    
		in=fopen("file.txt","r");
		
		do{
			fgets(line, 512, in);
			sscanf (line, "%[^,], %[^,], %[^\n]",f,l,p);
			strcpy ( contacts[x].first, f);
			strcpy ( contacts[x].last, l);
			strcpy ( contacts[x].phone, p);
			contacts[x].deleted =0;
			Contact_Number++;
			x++;
		}while(x<4);
		fclose(in);
		printf("\nContacts loaded successfully\n");
	}
}
sav(){
	FILE *f;
	int i =0;
		//Opening file for writing 
	f = fopen ("file.txt","w");
		//Checking the file exists
	if(f==NULL){
		f=fopen("file.txt","w");
      	printf("File created");
	}
	else{
			//Saving in the txt the contacts before closing the program
		for(i=0; i<Contact_Number; i++){
				//Only saving the contacts that are not "deleted" so next time you open the program and load them, you dont have the ones you wanted to delete
			if(contacts[i].deleted != 1){
		        fprintf(f,"%s,%s,%s\n", contacts[i].first, contacts[i].last, contacts[i].phone);
			}
	    }
	}
	fclose(f);
}