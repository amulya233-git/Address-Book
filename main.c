/*
Name : Amulya M
Discription : Project 'Address Book'
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
struct contact
{
    char name[20];
    char phno[25];
    char emailid[25];
};
struct Addressbook
{
    struct contact contact_list[100];
    int contact_count;
};
struct Addressbook creat_contact(struct Addressbook *var);//declaration of creat contact
void list_contact(struct Addressbook *ptr);//declaration of list contact
int search_contact(struct Addressbook *ptr1);//declaration of search contact
void delete_contact(struct Addressbook *ptr2);//declaration of delet contact
void edit_contact(struct Addressbook *ptr3);//declaration of edit contact
void save_contact(struct Addressbook *ptr4);//declaration of save contact
void load(struct Addressbook *ptr5);//declaration of load contact

int main()
{
    //struct Addressbook var;
    struct Addressbook var={.contact_count=0};//it will assign for both count and list for perticular means use '.'
    load(&var);//load function call
     int op;
    do
    {
      printf("\nWELLCOM TO ADDRESS BOOK\n");
      printf("1.Creat Contact\n2.List Contact\n3.Search Contact\n4.Delete Contact\n5.Edit Contact\n6.Save & EXIT Contact\n7.EXIT\n");
      printf("Please enter your chioce(1-7):");
      scanf("%d", &op);//read option

     switch(op)//perform based on option
     {
            case 1:
            creat_contact(&var);
            break;

            case 2:
            list_contact(&var);
            break;

            case 3:
            search_contact(&var);
            break;

            case 4:
            delete_contact(&var);
            break;

            case 5:
            edit_contact(&var);
            break;

            case 6:
            save_contact(&var);
            break;

            case 7:
            exit(0);//to come out of program
            break;
      
            default:
            printf("Invalid option. Please enter valide option(1-7)\n");
      }
    }while (op != 7);   
}
//creat contact
int validateid(char *id)
 {
    int len = strlen(id);
    int atcount=0;
    if (len < 5) 
    return 0; // minimum length check

    // Must contain one '@' and one ".com" at the end
    char *at = strchr(id, '@');
    char *dot = strstr(id, ".com");

    if (at == NULL || dot == NULL)
     return 0;

    // ".com" must be at the end
    if (strcmp(dot, ".com") != 0) 
    return 0;

    // '@' must not be first or last character
    if (at == id || *(at + 1) == '\0') 
    return 0;

    // There should be at least one character between '@' and '.com'
    if (dot - at <= 1)
     return 0;

    // place of '.' immediately after '@'
    if (*(at + 1) == '.')
     return 0;

    // All characters must be alphanumeric or one of '@', '.', '_'
    for (int i = 0; i < len; i++) 
    {
        char ch = id[i];
        if (!islower(ch) && (!isdigit(ch)) && ch != '@' && ch != '.' && ch != '_')
            return 0;
        
        if(ch == '@')
        atcount++;
    }
    if(atcount != 1)
    return 0;
    
    return 1;
}
int validatephone(char *phonenumber)//validation for phone number
{
    
    if(strlen(phonenumber)!=10)// checking for minimum length
    return 0;
    for(int i=0;i!=10;i++)
    {
        if(!isdigit(phonenumber[i]))
        return 0;
    }
      return 1;
}
struct Addressbook creat_contact(struct Addressbook *var)//function to creat contact
{
    printf("\nENTERED TO CREATE_CONTACT\n");
    printf("Enter your Name: ");
    char name[25];
    getchar();//remove leftover newline
    scanf("%[^\n]",name);//read include space
    strcpy(var->contact_list[var->contact_count].name,name);//copying name to contact list
    
    char number[25];
    int duplicate;
    do
    {
      duplicate=0;
      printf("Enter your Phone Number:\n ");
      scanf("%s",number);
      if(!validatephone(number))//checking for validation
      {
        printf("INVALID Phone number\n");
        continue;
      }
      //chech for duplicate number
      for(int i=0; i<var->contact_count; i++)
      {
        if(strcmp(var->contact_list[i].phno, number)==0)
        {
          duplicate=1;
          printf("Contact Already Exit\n");
        }
      }
    } while (!validatephone(number) || (duplicate!=0));//condition to repeat

  char id[30];    
  do
  {
    printf("Enter your Email: ");
    getchar();
    scanf("%[^\n]",id);
    if(!validateid(id))//checking for email validation
      {
        printf("Invalide Mail ID\n");
        continue;
      }
  }while(!validateid(id));//condition to repeate

  //storing number and email to contact list
  strcpy(var->contact_list[var->contact_count].phno,number);
  strcpy(var->contact_list[var->contact_count].emailid,id);
  printf("CONTACT SAVED SUCCESSFULLY\n");
  var->contact_count++;//increment contact count
}
//list contact
void list_contact(struct Addressbook *ptr)
{
  printf("ENTERED TO LIST_CONTACT\n");
  if(ptr->contact_count==0)//check for contact exist
  {
    printf(" NO Contact Found \n");
  }
  else
  {
    printf("SAVED CONTACT:\n");
    printf("------------------------------------------------------------------------\n");
    printf("| %-4s | %-15s | %-15s | %-25s |\n", "NO", "NAME", "MOBILE_NUMBER", "MAIL_ID");
    printf("------------------------------------------------------------------------\n");
    for(int i=0;i<ptr->contact_count;i++)
    {
      printf("-------------------------------------------------------------------------\n");
      printf("| %-4d | %-15s | %-15s | %-25s |\n", i+1, ptr->contact_list[i].name, ptr->contact_list[i].phno,ptr->contact_list[i].emailid); 
      printf("-------------------------------------------------------------------------\n"); 
    }
  }
} 
//search_Conatct
int searchbyemail(struct Addressbook *id)//search by email
{
  char mail[20];
  do
  {
    printf("Enter the Email ID: ");
    getchar();//clear buffer
    scanf("%s", mail);
    if(!validateid(mail))//check validation
     printf("INVALID MAIL\n");
  } while (!validateid(mail));

  int count=0;
  for(int i=0; i<id->contact_count; i++)//loop for all contacts
  {
    if(strcmp(id->contact_list[i].emailid, mail)==0)//if match found
   {
    if(count==0)//to print header only once
    {
      printf("CONTACT FOUND\n");
      printf("----------------------------------------------------------------------\n");
      printf("| %-4s | %-15s | %-15s | %-25s |\n", "NO", "NAME", "MOBILE_NUMBER", "MAIL_ID");
      printf("----------------------------------------------------------------------\n");
    }
      //print matching contact
      printf("----------------------------------------------------------------------\n");
      printf("| %-4d | %-15s | %-15s | %-25s |\n", i+1, id->contact_list[i].name, id->contact_list[i].phno, id->contact_list[i].emailid);
      printf("----------------------------------------------------------------------\n"); 
      count =1; 
   }
  }
  if(count!=1)//if no match found
  {
    printf("Contact Not found\n");
    return -1;
  }
} 
int searchbynumber(struct Addressbook *no)//search by number
{
  char number[20];
  do
  {
    printf("Enter the Phone Number: ");
    getchar();//buffer
    scanf("%s", number);
    if(!validatephone(number))//check validation
      printf("INVALID NUMBER\n");
  } while (!validatephone(number));

  int count=0;
  for(int i=0; i<no->contact_count; i++)//loop upto count
  {
    if(strcmp(no->contact_list[i].phno, number)==0)//match found condition
   {
    if(count==0)//print only header
    {
      printf("CONTACT FOUND\n");
      printf("------------------------------------------------------------------------\n");
      printf("| %-4s | %-15s | %-15s | %-25s |\n", "NO", "NAME", "MOBILE_NUMBER", "MAIL_ID");
      printf("------------------------------------------------------------------------\n");
    }
      printf("------------------------------------------------------------------------\n");
      printf("| %-4d | %-15s | %-15s | %-25s |\n", i+1, no->contact_list[i].name, no->contact_list[i].phno, no->contact_list[i].emailid);
      printf("------------------------------------------------------------------------\n"); 
      count=1; 
     
   }
  }
  if(count!=1)//match not found
  {
    printf("Contact Not found\n");
    return -1;
  }
}
int searchbyname(struct Addressbook *n)//search by name
{
  char name[20];
  int found_arr[100];//storing indices
  int count=0;
  printf("Enter the Name: ");
  getchar();//buffer
  scanf("%[^\n]", name);

  for(int i=0; i<n->contact_count; i++)//loop upto count
  {
    if(strcmp(n->contact_list[i].name, name)==0)//match found
     {
       if(count==0)//print only header
         {
          printf("CONTACT FOUND\n");
          printf("------------------------------------------------------------------------\n");
          printf("| %-4s | %-15s | %-15s | %-25s |\n", "NO", "NAME", "MOBILE_NUMBER", "MAIL_ID");
          printf("------------------------------------------------------------------------\n");
         }
        printf("------------------------------------------------------------------------\n");
        printf("| %-4d | %-15s | %-15s | %-25s |\n", i+1, n->contact_list[i].name, n->contact_list[i].phno, n->contact_list[i].emailid);
        printf("------------------------------------------------------------------------\n"); 
        count=1;
      }
  }
  if(count==0)//no match
  {
    printf("Contact Not found\n");
    return -1;
  }
  
}
int search_contact(struct Addressbook *ptr1)//main menu to choose search 
{
  int choice;
  printf("Entered to Search Contact\n");
  printf("1.Search By Name\n2.Search By Phone Number\n3.Search By Email\n");
  printf("Enter your Choice: ");
  scanf("%d", &choice);//read choice

  switch(choice)//execute based on choice
  {
    case 1:
    searchbyname(ptr1);
    break;

    case 2:
    searchbynumber(ptr1);
    break;

    case 3:
    searchbyemail(ptr1);
    break;

    default:
    printf("Invalide Choice\n");
    return -1;//invalid input
  }
  
}
   
//delet_contact
void delete_contact(struct Addressbook *ptr2)//main menu to choose delet type
{
  printf("ENTERED TO DELETE CONTACT\n");
    if (ptr2->contact_count == 0)//check for contact present
    {
        printf("NO CONTACT AVAILABLE TO DELETE\n");
        return;
    }

    int choice;
    printf("1. Delete Contact By Name\n2. Delete Contact By Mobile Number\n3. Delete Contact By Mail ID\nEnter your choice: ");
    scanf("%d", &choice);//read choice
    getchar(); //buffer

    char input[25];//to store user input
    int indexes[100];//to store matching contacts indices
    int found_count = 0;// count of found contact
    switch (choice)//work on the bases of choice
    {
    case 1:
        printf("Enter name: ");
        scanf("%[^\n]", input);
        break;
    case 2:
        do
        {
            printf("Enter mobile number: ");
            scanf("%[^\n]", input);
            getchar();//buffer
            if (!validatephone(input))//validating number
                printf("Invalid Mobile Number. 'Try again' \n");
        } while (!validatephone(input));
        break;
    case 3:
        do
        {
            printf("Enter Mail ID: ");
            scanf("%[^\n]", input);
            getchar();//buffer
            if (!validateid(input))//validating email
                printf("Invalid Mail ID. 'Try again'\n");
        } while (!validateid(input));
        break;
    default:
        printf("INVAILD Choice.\n");
        return;
    }

    for (int i = 0; i < ptr2->contact_count; i++)//loop uoto count
    {
        int found = 0;
        if (choice == 1 && strcmp(ptr2->contact_list[i].name, input) == 0)
            found = 1;//name found
        else if (choice == 2 && strcmp(ptr2->contact_list[i].phno, input) == 0)
            found = 1;//number found
        else if (choice == 3 && strcmp(ptr2->contact_list[i].emailid, input) == 0)
            found = 1;//email found

        if (found)//if match found
        {
            if (found_count == 0)//to print header only  once
            {
                printf("\nCONTACT(S) FOUND:\n");
                printf("------------------------------------------------------------------\n");
                printf("| NO | NAME            | MOBILE_NUMBER   | MAIL_ID\n");
            }
            indexes[found_count] = i;//storing the matching index
            printf("------------------------------------------------------------------\n");
            printf("| %-3d | %-15s | %-15s | %-30s\n", found_count + 1,ptr2->contact_list[i].name,ptr2->contact_list[i].phno,
                   ptr2->contact_list[i].emailid);
            found_count++;//increment match count
        }
    }

    if (found_count == 0)//no contact found
    {
        printf("NO MATCHING CONTACT FOUND.\n");
        return;
    }

    int user_choice;
    if (found_count == 1)
    {
        user_choice= indexes[0]; //if only onr match delet directly
    }
    else
    {
        //multiple matches found asking user to choose
        printf("Multiple contacts found.\n Enter the serial no (1 to %d) to delete: ", found_count);
        scanf("%d", &user_choice);
        if (user_choice < 1 || user_choice> found_count)//validate choice
        {
            printf("INVALID Selection.\n");
            printf("Enter Valid Index(1 t0 %d) to Delet: ", found_count);
            scanf("%d", &user_choice);
            
        }
        user_choice= indexes[user_choice - 1];//convert serial to actual index
    }

    // Shift contacts to delete
    for (int i = user_choice; i < ptr2->contact_count - 1; i++)
    {
        ptr2->contact_list[i] = ptr2->contact_list[i + 1];
    }
    ptr2->contact_count--;//decrement count

    printf("CONTACT DELETED SUCCESSFULLY.\n");
}

//edit_contact
void edit_contact(struct Addressbook *ptr3)
{
  printf("ENTERED TO EDIT_CONTACT\n");
  if(ptr3->contact_count==0)//check for contact
    {
        printf("NO CONTACT AVAILABLE TO EDIT");
        return;
    }
    int choice;
    printf("1. Edit By Name\n2. Edit By Mobile Number\n3. Edit By Mailid\nEnter the Choice: ");
    scanf("%d", &choice);//read choice
    getchar();

    char input[20];//to store user input
    int indexes[100];//to store matching index
    int found_count=0;//to matchung count

    switch(choice)
    {
        case 1:
        printf("Enter Name: ");
        scanf("%[^\n]", input);
        getchar();
        break;

        case 2:
        do
        {
            printf("Enter Mobile Number: ");
            scanf("%[^\n]", input);
            getchar();//buffer
            if (!validatephone(input))//validate number
                printf("INVALID Mobile Number. 'Try Again'\n");
        } while (!validatephone(input));
        break;
 case 3:
        do
        {
            printf("Enter Mail ID: ");
            scanf("%[^\n]", input);
            getchar();//buffer
            if (!validateid(input))//validate mail
                printf("INVALID Mail ID. 'Try Again'\n");
        } while (!validateid(input));
        break;
    default:
        printf("INVALID Choice.\n");
        return;
    }

    for(int i=0;i<ptr3->contact_count;i++)//loop upto count
    {
        int found=0;
        if(choice==1&&strcmp(ptr3->contact_list[i].name, input)==0)
        found=1;//found name
    
        else if(choice==2&&strcmp(ptr3->contact_list[i].phno, input)==0)
        found=1;//found number
        
        else if(choice==3&&strcmp(ptr3->contact_list[i].emailid, input)==0)
        found=1;//found email
    
        if(found)//if contact found
        {
         if(found_count==0)//to print header once
         {
           printf("------------------------------------------------------------------\n");
           printf("| %-3s | %-15s | %-15s | %-30s\n", "NO", "NAME", "MOBILE_NUMBER", "MAIL_ID");
           printf("------------------------------------------------------------------\n");
         }

           indexes[found_count]=i;//store matching indeces
          printf("------------------------------------------------------------------\n");
          printf("| %-3d | %-15s | %-15s | %-30s\n", found_count + 1,ptr3->contact_list[i].name, ptr3->contact_list[i].phno,ptr3->contact_list[i].emailid);
          found_count++;//increment matching count
        }
    }
            
    if(found_count==0)//if matching not found
    {
      printf("NO MATCHING CONTACT FOUND\n");
      return ;
    }

int user_choice;
if(found_count==1)
{
    user_choice=indexes[0];//if one matching found edit directly
}
//multiple contacts found ask user to choose
else
{
printf("Multiple contacts found\nEnter The Index(1 to %d) To Edit: ", found_count);
scanf("%d", &user_choice);
while(user_choice<1||user_choice>found_count)//validate choice
{
   printf("INVALID Selection\n");
   printf("Enter Valid Index(1 t0 %d) to Edit: ", found_count);
   scanf("%d", &user_choice);
}
user_choice=indexes[user_choice-1];//convert serial no to actual index
}

int edit_choice;//asking user to edit type
    printf("\n1. Edit By Name\n2. Edit By Mobile Number\n3. Edit By Mail ID\nEnter your choice: ");
    scanf("%d", &edit_choice);//tead choice
    getchar();
    
     int duplicate;
    char newdata[25];//to store new input
    switch (edit_choice)
     {
    case 1:
        printf("Enter new name: ");
        scanf("%[^\n]", newdata);
        strcpy(ptr3->contact_list[user_choice].name, newdata);//copy new i/p to list
        break;

    case 2:
        do {
            duplicate=0;
            printf("Enter new mobile number: ");
            scanf("%[^\n]", newdata);
            getchar();
            if(!validatephone(newdata))//checking for validation
              {
                printf("INVALID Phone number\n");
                continue;
              }
            //chech for duplicate number
            for(int i=0; i<ptr3->contact_count; i++)
              {
                if(strcmp(ptr3->contact_list[i].phno, newdata)==0)
                  {
                    duplicate=1;
                    printf("Contact Already Exit\n");
                  }
              }
          } while (!validatephone(newdata) || (duplicate!=0));//condition to repeat
       
        strcpy(ptr3->contact_list[user_choice].phno, newdata);//copy new i/p to list
        break;

    case 3:
      do {
            printf("Enter new mail ID: ");
            scanf("%[^\n]", newdata);
            getchar();
         } while (!validateid(newdata));//validate email
        strcpy(ptr3->contact_list[user_choice].emailid, newdata);//copy new i/p to list
        break;

    default:
        printf("INVALID Edit Option.\n");
        return;
    }
    printf("CONTACT UPDATED SUCCESSFULLY.\n");
}

//save contact
void save_contact(struct Addressbook *ptr4)//save contact to cv file
{
  FILE *fptr;
  fptr=fopen("contacts.csv", "w");//open file in writing mood
  if(fptr == NULL)
  {
    printf("Error: File not exits");
  }

  fprintf(fptr, "%d\n", ptr4->contact_count);//write contact count to file

  for(int i=0; i<ptr4->contact_count; i++)//loop through count
  {
   // write each contact in cv formate: name, phno, email
    fprintf(fptr, "%s, %s, %s\n", ptr4->contact_list[i].name, ptr4->contact_list[i].phno, ptr4->contact_list[i].emailid);
  }
  printf("SAVED SUCCESFULLY\n");
  fclose(fptr);//close file
}

//load contact
void load(struct Addressbook *ptr5)//load contact from cv file
{
  FILE *fptr;
  fptr=fopen("contacts.csv", "r");//open file for reading
  if(fptr == NULL)//check if file opened succesfully
  {
    printf("Error: File not exits");
  }

  fscanf(fptr, "%d\n", &ptr5->contact_count);//read contact count

  for(int i=0; i<ptr5->contact_count; i++)//loop to read contact
  {
    //read name, phno, email from eatch line using cv formate
    fscanf(fptr, "%[^,], %[^,], %[^\n]\n", ptr5->contact_list[i].name, ptr5->contact_list[i].phno, ptr5->contact_list[i].emailid);
  } 
  fclose(fptr);//close file
}