#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STD_TYBS.h"
#include "School.h"

#define INSERT     1
#define DELET      2
#define PRINT      3
#define EDIT       4
#define RANK       5
#define SCORE      6
#define SEARCH     7
#define StudentNum 8
#define DELETALL   9
#define EXIT       10


ErrorState MAIN_MENU(void)
{
	ErrorState Local_enState=SUCCES;
	Class1_t C1;
	u32 choice,size;
	Class_Init(&C1);
	Student_Entry  e;
	printf("-----Welcom To School Mangment System----\n");
	do{
	printf("===============================:\n");
    printf("Please Entrer your Process:\n ");
  printf("======================:\n");	
 printf("1-Insert New Student in Class \n2-delet Student from Class\n3-Print Class Student List\n");
  printf("4-Edit Student Information\n5-Rank Student According to Logic Score\n");
  printf("6-Student Score\n7-Search for a Student\n8-Print Number of Student in class\n");
  printf("9-Delet All Student From Class\n10-EXIT from System\n");
  fflush(stdin);
  scanf("%d",&choice);
  switch(choice)
  {
	case INSERT:  
	{
		Student_Entry e;
         NEW_STUDENT(&C1,e);
	}
	         break;
	case DELET:
	{
		    u32 Id;
         	printf("Enter ID of Student to Delet: ");
			fflush(stdin);
			scanf("%d",&Id);
			DELET_STUDENT(&C1,Id);
			printf("Delet Complet\n");
	}
	        break;
	case PRINT :
	           STUDENT_LIST(&C1);
			break;
	case EDIT :
	{            u32 Id;
         	printf("Enter ID of Student to Edit information: ");
			fflush(stdin);
			scanf("%d",&Id);
	         STUDENT_EDIT(&C1,Id);
	}
	     
		    break;
	case RANK :
	           RANK_STUDENT(&C1);
			break;
	case SCORE :
	{
	         u32 Id;
         	printf("Enter ID of Student: ");
			fflush(stdin);
			scanf("%d",&Id);
	       STUDENT_SCORE(&C1,Id);
	}
			break;
    case  SEARCH :
	{	  u32 Id;
       	StudentNode_t *temp;
         	printf("Enter ID of Student to Search for: ");
			fflush(stdin);
			scanf("%d",&Id);
           	Class_SearchStudent(&C1,Id,&temp);
			if(temp==NULL) printf("ID not Found\n");
		else Student_PrintStudent(&C1,&temp);	
	}			
			break;
	case StudentNum  : 
               Class_NumberOFStudent(&C1,&size);
		      printf("Nubmber of student =%d\n",size);
			break;
	case DELETALL   : 	
                    Class_FreeClass(&C1);	
					printf("All Student Deleted\n");
			break;
	case  EXIT : 		
			break;
	 default :
       printf("invalid choise\n");
             break;	   
  }
	}while(choice!=EXIT);
	return Local_enState;
}
ErrorState Class_Init(Class1_t *PC)
{
	  ErrorState Local_enState=SUCCES;
	if(PC==NULL)
	{
		Local_enState=NULL_PTR;	
	}
	else
	{ 
     PC->pHead=PC->pTail=NULL;
       PC->NumberOFStudent=0;
	}
	return Local_enState;
}
ErrorState  List_InsertNode(Class1_t *PC,Student_Entry e)
{ 
	ErrorState Local_enState=SUCCES;
	if(PC==NULL)
	{
		Local_enState=NULL_PTR;	
	}
	else
 { 
	StudentNode_t* pn=(StudentNode_t*)malloc(sizeof(StudentNode_t));
	if(pn==NULL)  
	{
		printf("Heap is full");
	}
	else  // not full
	{ //step1: init node  
		pn->data=e;
		pn->pNext=NULL;
		pn->pPrev =NULL;
		pn->leftPtr =NULL;
		pn->rightPtr=NULL;
		// check if list is Empty or not
		bool_t state;
		Class_isEmpty(PC,&state);
		if(state == TRUE)// empty
		{
			PC->pHead=PC->pTail=pn;
			PC->TreeNodePtr=pn;       //root=&pn(node)
			PC->NumberOFStudent++;     
		}
		else  //not empty
	{
	      StudentNode_t *temp=PC->pHead; 
		while(temp !=NULL && strcmp((temp->data.name),(pn->data.name))< 0)  //insert in Alphapatical order
		{                                                    
			temp= temp->pNext;
		}
		if(temp==PC->pHead) // insert @head
		{
		PC->pHead->pPrev=pn;
		pn->pNext=PC->pHead;
		PC->pHead=pn;
		PC->NumberOFStudent++;
		}
		else if(temp==NULL)// insert@tail
		{
			pn->pPrev=PC->pTail;
			PC->pTail->pNext=pn;
			PC->pTail=pn;
			PC->NumberOFStudent++;
		}
		else  // insert @middel
		{
			//temp->pNext=pn->pPrev;
			pn->pNext=temp;
			pn->pPrev=temp->pPrev;
			temp->pPrev->pNext=pn;
			temp->pPrev=pn;
			PC->NumberOFStudent++;
		}
		
	} // it is not empty 
		
	}// list is not full
 
 }
   return Local_enState;
}
StudentNode_t *rootPtr ;
ErrorState NEW_STUDENT(Class1_t *PC,Student_Entry e)
{
	
		ErrorState Local_enState=SUCCES;
	if(PC==NULL)
	{
		Local_enState=NULL_PTR;	
	}
	else
 { 
     printf("Enter Student ID: ");
	 fflush(stdin);
	 scanf("%d",&e.ID);
	  StudentNode_t *temp=NULL;
	 Class_SearchStudent(PC,e.ID,&temp);
	  while(temp !=NULL && (temp->data.ID)==e.ID)  // To make ID uniq with evry student
		{
			printf("This ID is Alrady existed Try Anthor one\n ");
			printf("Enter Student ID: ");
	        fflush(stdin);
	       scanf("%d",&e.ID);
		   Class_SearchStudent(PC,e.ID,&temp);
		}
	 printf("Enter Student Full Name: ");
	 fflush(stdin);
	 scanf ("%[^\n]s",e.name);
	  printf("Enter Student Age: ");
	 fflush(stdin);
	 scanf("%d",&e.age);
	  printf("Enter Student Phone number: ");
	  fflush(stdin);
	  scanf ("%[^\n]%*c",e.phoneNumber);
	  	printf("Enter Student Date of birth: ");
	  fflush(stdin);
	  scanf ("%[^\n]%*c",e.birthDay);
	  	printf("Enter Student Address: ");
	  fflush(stdin);
	  scanf ("%[^\n]%*c",e.address);
	  e.Score.computer_Since=0;
	  e.Score.Mathe=0;
	  e.Score.Electronics=0;
	  e.Score.logic=0;
	 List_InsertNode(PC,e);
	 insertNode(&rootPtr,e);
	
 }
	return Local_enState;
}
ErrorState DELET_STUDENT(Class1_t *PC,u32 e)
{
		ErrorState Local_enState=SUCCES;
	if(PC==NULL)
	{
		Local_enState=NULL_PTR;	
	}
	else
	{ 
	   bool_t state;
		Class_isEmpty(PC,&state);
		if(state ==TRUE) // list emty
		{   
	printf("List is Empty Can not Delat");
	   StudentNode_t  *ppNode=NULL;
		}
	else  // list is not empty
	{
		StudentNode_t *temp=NULL; //  erturned temp =&Node
		Class_SearchStudent(PC,e,&temp);
		if(temp == NULL)// id not found
		{
			printf("Can not delet id not found ");
		}
		else // id found 
		{
			if(PC->pHead==PC->pTail)//ONLY ONE
			{
				free(PC->pHead);
				PC->pHead=PC->pTail=NULL;
					//PL->ListSize=0;
			}
			else if(PC->pHead==temp)//@Head
			{
				PC->pHead=PC->pHead->pNext;
				free(PC->pHead->pPrev);
				PC->pHead->pPrev=NULL;
			}
			else if(PC->pTail==temp) //@tail
			{
				PC->pTail=PC->pTail->pPrev;
				free(PC->pTail->pNext);
				PC->pTail->pNext=NULL;
			}
			else // @middele
			{
				temp->pPrev->pNext=temp->pNext;
				temp->pNext->pPrev=temp->pPrev;
				free(temp);
			}
			PC->NumberOFStudent--;
		}
	}
	}
	return Local_enState;
}
ErrorState STUDENT_EDIT(Class1_t *PC,u32 id)
{
		ErrorState Local_enState=SUCCES;
	if(PC==NULL)
	{
		Local_enState=NULL_PTR;	
	}
	else
	{ 
       StudentNode_t *temb=NULL;
	 Class_SearchStudent(PC,id,&temb);
	 if(temb==NULL)
		{
			printf("ID not Found\n");
		}
		else{
			printf("Last Information is\n");
			Student_PrintStudent(PC,&temb);
	 printf("Enter Student New Age: ");
	 fflush(stdin);
	 scanf("%d",&temb->data.age);
	  printf("Enter Student New Phone number: ");
	  fflush(stdin);
	  scanf ("%[^\n]%*c",temb->data.phoneNumber);
	  	printf("Enter Student New Date of birth: ");
	  fflush(stdin);
	  scanf ("%[^\n]%*c",temb->data.birthDay);
	  	printf("Enter Student New Address: ");
	  fflush(stdin);
	  scanf ("%[^\n]%*c",temb->data.address);
	  printf("Update Completed\n");
		}
	}
	return Local_enState;
}
ErrorState STUDENT_LIST(const Class1_t *PC)
{
		ErrorState Local_enState=SUCCES;
	if(PC==NULL)
	{
		Local_enState=NULL_PTR;	
	}
	else
	{ 
	   bool_t state;
		Class_isEmpty(PC,&state);
		if(state ==TRUE) //empty 
		{   
	printf("Class  is Empty Can not Be brinted\n ");
		}
		else //not empty 
	      {
	  StudentNode_t *temp;
	for(temp=PC->pHead;temp!=NULL;temp=temp->pNext)
	{
		 static u32 i=1;
		printf("StudentNumber\tID\t\tName\t\tage\t\tPhone_Number\t\tDateOFBitrh\t\tAdress\n");
		printf("Student_%d:\t",i);
		printf("%d\t%s\t%d\t\t%s\t",temp->data.ID,temp->data.name,temp->data.age,temp->data.phoneNumber);
		printf("\t%s\t\t%s\n",temp->data.birthDay,temp->data.address);
		i++;
	}
		  }
	}
	return Local_enState;
}
ErrorState  Class_FreeClass(Class1_t *PC)
{
		ErrorState Local_enState=SUCCES;
	if(PC==NULL)
	{
		Local_enState=NULL_PTR;	
	}
	else
	{ 
  StudentNode_t *temp=NULL;
	 while(PC->pHead!=NULL)
	 {
		 temp=PC->pHead;//temp=&5
		 PC->pHead=PC->pHead->pNext; //head =&6
		 free(temp);
	 }
      PC->pTail=NULL;
       PC->NumberOFStudent=0;
	}
	return Local_enState;
}
ErrorState  Class_SearchStudent(Class1_t *PC,u32 Id,StudentNode_t **ppNode)
{
		ErrorState Local_enState=SUCCES;
	if(PC==NULL)
	{
		Local_enState=NULL_PTR;	
	}
	else
 { 
	     bool_t state;
		Class_isEmpty(PC,&state);
		if(state ==TRUE) 
		{   
	//printf("List is Empty Can not Search\n");
	*ppNode=NULL;
		}
	else
  {
	  
	StudentNode_t *temp=PC->pHead; 
	while(temp !=NULL && (temp->data.ID)!=Id)  
		{
			temp= temp->pNext;
		}
		*ppNode=temp;
  }
 }
	return Local_enState;
}
ErrorState RANK_STUDENT(Class1_t *PC)
{
		ErrorState Local_enState=SUCCES;
	if(PC==NULL)
	{
		Local_enState=NULL_PTR;	
	}
	else
	{ 
    inOrder(rootPtr);
	}
	return Local_enState;
}
ErrorState STUDENT_SCORE(Class1_t *PC,u32 id)
{
		ErrorState Local_enState=SUCCES;
	if(PC==NULL)
	{
		Local_enState=NULL_PTR;	
	}
	else
 { 
       bool_t state;
		Class_isEmpty(PC,&state);
		if(state ==TRUE) // list emty
		{   
	printf("Clss is Empty There is no Student");
		}
	else  // Class is not empty
	{
	 StudentNode_t *temb=NULL;
	 Class_SearchStudent(PC,id,&temb);
	 if(temb==NULL)
		{
			printf("ID not Found\n");
		}
		else
		{
		u8 choise;
	printf("Do you Want to Update Students Score OR Print Student Score\n");
	printf("Enter 'U' if you want to Update AND Enter 'P' if you want to print\n");
	fflush(stdin);
		scanf("%c",&choise);
		if('U'==choise)
			{
				static u32 i=1;
		printf(" Enter Student_%d: Coputer Scince Score: ",i);
		fflush(stdin);
	 scanf("%d",&temb->data.Score.computer_Since);
	 printf(" Enter Student_%d: Mathe Score: ",i);
		fflush(stdin);
	 scanf("%d",&temb->data.Score.Mathe);
	 printf(" Enter Student_%d: Electronics Score: ",i);
		fflush(stdin);
	 scanf("%d",&temb->data.Score.Electronics);
	 printf(" Enter Student_%d: logic Score: ",i);
		fflush(stdin);
	 scanf("%d",&temb->data.Score.logic);
	i++;
	printf("Update Copleted\n");
		}
			
	   else if('P'==choise)
	   {
           printf("\tName\t\tCoputer Scince Score\tElectronics Score\tMathe Score\tlogic Score\n");
		    printf("%s\t\t    %d\t\t    %d\t\t   ",temb->data.name,temb->data.Score.computer_Since,temb->data.Score.Electronics);
		    printf("  %d\t\t    %d\n",temb->data.Score.Mathe,temb->data.Score.logic);
	   }
      else 
	      {
	         printf("Invalid input");
          }
	}//id found
	}//not empty		  
 } //not NULL pointer
	return Local_enState;
}
ErrorState  Class_NumberOFStudent(const Class1_t *PC,u32 *pSize)
{
	ErrorState Local_enState=SUCCES;
	if(PC==NULL)
	{
		Local_enState=NULL_PTR;	
	}
	else
	{ 
	*pSize=PC->NumberOFStudent;
	}
	return Local_enState;	
}
ErrorState  Class_isEmpty(const Class1_t *PC,bool_t *pstate)
{
	
		ErrorState Local_enState=SUCCES;
	if(PC==NULL)
	{
		Local_enState=NULL_PTR;	
	}
	else
 { 
	if(PC->pHead==NULL) 	//so tail == NuLL
	{
		*pstate=TRUE;
	}
	else
	{
		*pstate=FALSE;
	}
 }
 return Local_enState;
	
}
ErrorState  Student_PrintStudent(Class1_t *PC,StudentNode_t **ppNode)
{
	ErrorState Local_enState=SUCCES;
	if(PC==NULL)
	{
		Local_enState=NULL_PTR;	
	}
	else
 { 
StudentNode_t *temp=*ppNode;
if(temp==NULL)
		{
			printf("ID not Found\n");
		}
		else{
			printf("ID\t\tName\t\tage\t\tPhone_Number\t\tDateOFBitrh\t\tAdress\n");
		    printf("%d\t%s\t%d\t\t%s\t",temp->data.ID,temp->data.name,temp->data.age,temp->data.phoneNumber);
		    printf("\t%s\t\t%s\n",temp->data.birthDay,temp->data.address);
		}
 }
 return Local_enState;
}
ErrorState insertNode( StudentNode_t **treePtr, Student_Entry e)
{
		ErrorState Local_enState=SUCCES;
	if(*treePtr==NULL)
	{
		Local_enState=NULL_PTR;	
	}
	else
    { 
 if ( *treePtr == NULL ) {
 *treePtr = malloc( sizeof( StudentNode_t) );
 if ( *treePtr != NULL ) {
 ( *treePtr )->data.Score.logic = e.Score.logic;
 ( *treePtr )->leftPtr = NULL;
( *treePtr )->rightPtr = NULL;
} 
 else {
 printf( " not inserted. No memory available.\n" );
 } 
 } 
 else {

if (  e.Score.logic < ( *treePtr )->data.Score.logic ) {
insertNode( &( ( *treePtr )->leftPtr ),e );
}

else if ( e.Score.logic > ( *treePtr )->data.Score.logic ) {
insertNode( &( ( *treePtr )->rightPtr ),e);
}
 else { 
 printf( "dup value " );
     } 
   } 
    }
 return Local_enState;
}
ErrorState  inOrder( StudentNode_t *treePtr )
{
		ErrorState Local_enState=SUCCES;
	if(treePtr==NULL)
	{
		Local_enState=NULL_PTR;	
	}
	else
       { 
   if ( treePtr != NULL ) {
	inOrder( treePtr->rightPtr );
	printf( "%s\t%d\n",treePtr->data.name, treePtr->data.Score.logic);
	inOrder( treePtr->leftPtr );
	}

		}
 
 return Local_enState;
}


