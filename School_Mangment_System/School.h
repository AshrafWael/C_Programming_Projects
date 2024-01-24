#ifndef  _SCHOOL_H_
#define  _SCHOOL_H_
/*============================		MACROCS		=========================*/
#define NAMESIZE   30
#define BIRTHSIZE  11
#define ADDRESSIZE 30
#define PHONESIZE  12

typedef struct{
  u16 computer_Since;
  u16 Mathe;
  u16 Electronics;
  u16 logic;
}Subject_Score;

typedef struct{
	u8 name[NAMESIZE];
	u8 birthDay[BIRTHSIZE];
	u8 address[ADDRESSIZE];
	u32 phoneNumber[PHONESIZE];
	u32 ID;
	u32 age;
	Subject_Score Score;
}Student_Entry;

typedef struct myNode{
	Student_Entry data;
	struct myNode *pNext; // Doubly linked list 
	struct myNode *pPrev;                         
    struct myNode *leftPtr;
    struct myNode *rightPtr;	//tree 
}StudentNode_t;

 
 
typedef struct{
	 StudentNode_t *pHead;
     StudentNode_t *pTail;
	 StudentNode_t *TreeNodePtr;// pointer to studentNode
     u32 NumberOFStudent;
}Class1_t;
/*
typedef struct{
	 StudentNode_t *pHead;
     StudentNode_t *pTail;
     u32 ListSize;
}Class2_t;
*/
typedef enum {     
	NULL_PTR =1,
	OUT_OF_RANGE =2,
	SUCCES=3
}ErrorState;

typedef enum {
	TRUE=1,
	FALSE=0
}bool_t;
/*============================		Functions prototypes		=========================*/
ErrorState  MAIN_MENU(void);
ErrorState  Class_Init(Class1_t *PC); 
ErrorState  NEW_STUDENT(Class1_t *PC,Student_Entry e);
ErrorState  DELET_STUDENT(Class1_t *PC,u32 e); 
ErrorState  STUDENT_EDIT(Class1_t *PC,u32 id); 
ErrorState  RANK_STUDENT(Class1_t *PC);
ErrorState  STUDENT_SCORE(Class1_t *PC,u32 id);
ErrorState  STUDENT_LIST(const Class1_t *PC);
ErrorState  Class_FreeClass(Class1_t *PC);
ErrorState  Class_SearchStudent(Class1_t *PC,u32 Id,StudentNode_t **ppNode);
ErrorState  Class_NumberOFStudent(const Class1_t *PC,u32 *pSize);
ErrorState  List_InsertNode(Class1_t *PC,Student_Entry e);
ErrorState  Student_PrintStudent(Class1_t *PC,StudentNode_t **ppNode);
ErrorState  Class_isEmpty(const Class1_t *PC,bool_t *pstate);
ErrorState insertNode( StudentNode_t **treePtr, Student_Entry e ); 
ErrorState  inOrder( StudentNode_t *treePtr );




#endif