#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "customer_manager.h"



#define UNIT_ARRAY_SIZE 1024

struct node {
  char *id;
  char *name;                // customer name
  int purchase;                  // customer id
  struct node *next_id;
  struct node *next_name;              // purchase amount (> 0)
};

struct DB {
  struct node *hash_ID[UNIT_ARRAY_SIZE]; 
  struct node *hash_NAME[UNIT_ARRAY_SIZE];
    // pointer to the array
  int curArrSize;            // current array size (max # of elements)
  int numItems;              // # of stored items, needed to determine
			     // # whether the array should be expanded
			     // # or not
};

enum {HASH_MULTIPLIER = 65599};

static int hash_function(const char *pcKey, int iBucketCount)

/* Return a hash code for pcKey that is between 0 and iBucketCount-1,
   inclusive. Adapted from the EE209 lecture notes. */
{
   int i;
   unsigned int uiHash = 0U;
   for (i = 0; pcKey[i] != '\0'; i++)
      uiHash = uiHash * (unsigned int)HASH_MULTIPLIER
               + (unsigned int)pcKey[i];
   return (int)(uiHash % (unsigned int)iBucketCount);
}


/*--------------------------------------------------------------------*/
DB_T
CreateCustomerDB(void)
{
  struct DB *d;
  d = (DB_T)calloc(1,sizeof(struct DB));
  if (d == NULL){
    fprintf(stderr,"Can't allocate a memory for DB_T\n");
    return NULL;
  } 
  d->curArrSize = UNIT_ARRAY_SIZE;
  d->numItems = 0;
  //d->hash_ID = (struct node *)calloc(d->curArrSize,
  //              sizeof(struct node*));
  //d->hash_NAME = (struct node *)calloc(d->curArrSize,
  //              sizeof(struct node*));            
  return d;
}
/*--------------------------------------------------------------------*/
void
DestroyCustomerDB(DB_T d)
{
  /* fill out this function */
   //////// need to be fixed
  assert(d!=NULL);
  /*for(int i=0;i< d->curArrSize;i++){
    struct node *c;
    for (c = d->hash_ID[i];c!=NULL; c = c ->next_id){
      free((char *)c->id);
      free((char *)c->name);
      free(c);
    }
  }
  free(d->hash_ID);
  free(d->hash_NAME);*/
  free(d);
  
}
/*--------------------------------------------------------------------*/
int
RegisterCustomer(DB_T d, const char *id,
		 const char *name, const int purchase)
{
  /* fill out this function */
  assert(d!=NULL);
  if (id == NULL) return -1;
  if (name == NULL) return -1;
  if (purchase<=0) return -1; 
  int h_id = hash_function(id,d->curArrSize);
  int h_name = hash_function(name,d->curArrSize);
  struct node *p = (struct node*)malloc(sizeof(struct node));
  p->id = strdup(id);
  p->name = strdup(name);
  p->purchase = purchase;
  if (d->hash_ID[h_id] !=NULL){
    struct node *c1;
    for (c1 = d->hash_ID[h_id];c1 != NULL;c1 = c1->next_id){
        if (strcmp(c1->id,id)==0) return -1;
    }
  }
  if (d->hash_NAME[h_name]!=NULL){
    struct node *c2;
    for (c2 = d->hash_NAME[h_name];c2 != NULL;c2 = c2->next_name){
        if (strcmp(c2 ->name,name) == 0) return -1;
    }
  }
  p->next_id = d->hash_ID[h_id];
  d->hash_ID[h_id] = p;
  p->next_name = d->hash_NAME[h_name];
  d->hash_NAME[h_name] = p;
  d->numItems++;
  return 0;
  
  
  return 0;
}
/*--------------------------------------------------------------------*/
int
UnregisterCustomerByID(DB_T d, const char *id)
{
  /* fill out this function */
  assert(d!=NULL);
  if (id == NULL) return -1;
  struct node *rm;
  /*--------for ID------*/
  int h = hash_function(id,d->curArrSize);
  struct node *head = d->hash_ID[h];
  printf("%d\n",head->id == NULL);
  if(head->id == NULL) return -1;
  if (strcmp(head->id,id)==0){
    rm = head;
    head = rm->next_id;
    printf("rm : %s\n",rm->id);
    printf("rm : %s\n",rm->name);
  }
  else{
    struct node *current = head;
    while (current != NULL && (strcmp(current->next_id->id,id)==0)){
      current = current -> next_id;
    }
    printf("rm : %s\n",current->next_id->id);
    if(current!=NULL){
      rm = current->next_id;
      
      current->next_id = rm->next_id;
    }
    else return -1;
  }
  /*------for name ------*/
  int x = hash_function(rm->name,d->curArrSize);
  struct node *head1 = d->hash_NAME[x];
  if (strcmp(head1->id,id)==0){
    head1 = rm->next_name;
  }
  else{
    struct node *current1 = head1;
    while (current1 != NULL &&(current1->next_name !=rm)){
      current1 = current1 -> next_name;
    }
    if(current1 != NULL){
      printf("rm1 : %s\n",current1->next_name->name);
      current1 -> next_name = rm->next_name;
    }
    else return -1;
  }
  
  /*rm->id = NULL;
  rm->name = NULL;
  rm =  NULL;*/
  
  free(rm->id);
  
  free(rm->name);
  
  free(rm);
  

  d->numItems--;
  return 0;
}




int main(){
    DB_T d = CreateCustomerDB();
    int num = 3;
    char name[100];
	  char id[100];
    for (int i = 1; i < num; i++) {
		  sprintf(name, "name%d", i);
		  sprintf(id, "id%d", i);
		  if (RegisterCustomer(d, id, name, 10) < 0) {
			  printf("RegisterCustomer returns error\n");
			  return 0;
		  }
    }
    UnregisterCustomerByID(d,"id1");
    UnregisterCustomerByID(d,"id2");
    UnregisterCustomerByName(d,"name2");
    //printf("%s\n", (d->hash_ID[439]->next_id)->name);
    UnregisterCustomerByName(d,"name1");
    printf("S1");
    return 0;

}
