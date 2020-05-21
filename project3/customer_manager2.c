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
int 
searchID(DB_T d,const char *id){
  struct node *p;
  int h = hash_function(id,d->curArrSize);
  for(p = d->hash_ID[h];p!=NULL;p = p->next_id){
    if(strcmp(p->id,id)==0){
      return 1;
    }
  }
  return 0;  
}


int 
searchNAME(DB_T d,const char *name){
  struct node *p;
  int h = hash_function(name,d->curArrSize);
  for(p = d->hash_NAME[h];p!=NULL;p = p->next_name){
    if(strcmp(p->name,name)==0){
      return 1;
    }
  }
  return 0;  
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

  
  return d;
}
/*--------------------------------------------------------------------*/
void
DestroyCustomerDB(DB_T d)
{
  /* fill out this function */
   //////// need to be fixed
  assert(d!=NULL);
  for(int i=0;i< d->curArrSize;i++){
    struct node *c;
    for (c = d->hash_ID[i];c!=NULL; c = c ->next_id){
      free(c->id);
      free(c->name);
      free(c);
    }
  }
  free(d->hash_ID);
  free(d->hash_NAME);
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
  // first make new item(p)
  
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
  // check whether there is same id or name

  p->next_id = d->hash_ID[h_id];
  d->hash_ID[h_id] = p;
  p->next_name = d->hash_NAME[h_name];
  d->hash_NAME[h_name] = p;
  d->numItems++;
  // if not, change connection
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
  if (d->numItems ==0) return -1;
  struct node *rm;// we will remove rm finally
  int h = hash_function(id,d->curArrSize);
  struct node *head = d->hash_ID[h];
  rm =NULL;
  struct node *s;
  for (s = head;s!=NULL;s = s->next_id){
    if(strcmp(s->id,id)==0){
      rm = s;
      break;
    }
    else continue;
  }
 // check weather id is in Hashdatabase
  if (head == rm){
    head = rm->next_id;
  }
  // check for index 1 is same as id we are looking for
  else{
    struct node *current;
    for(current = head;current!=NULL;current = current->next_id){
      if(current->next_id == rm ){
        current->next_id = rm->next_id;
      }
      else continue;
    }
  }
  //change connection of next_id
  int x = hash_function(rm->name,d->curArrSize);
  struct node *head1 = d->hash_NAME[x];
  if(head1 == rm){
    head1 = rm->next_name;
  }
  else{
    struct node *current1;
    for(current1 = head1;current1!=NULL;current1 = current1->next_name){
      if(current1->next_name == rm){
        current1-> next_name = rm->next_name;
      }
      else continue;
    }
  }
  //change connection of next_name
  free(rm->id);
  free(rm->name);
  free(rm);
  rm->id = NULL;
  rm->name = NULL;
  rm = NULL; 
  //free rm
  d->numItems--;
  return 0;
}
/*--------------------------------------------------------------------*/
int
UnregisterCustomerByName(DB_T d, const char *name)
{
  /* fill out this function */
  //it is reverse version of UnregisterCustomerByID
  assert(d!=NULL);
  if (name == NULL) return -1;
  struct node *rm;
  int h = hash_function(name,d->curArrSize);
  struct node *head = d->hash_NAME[h];
  if (d->numItems ==0) return -1;
  rm =NULL;
  struct node *s;
  for (s = head;s!=NULL;s = s->next_name){
    if(strcmp(s->name,name)==0){
      rm = s;
      break;
    }
    else continue;
  }

  if (head == rm){
    head = rm->next_name;
  }
  else{
    struct node *current;
    for(current = head;current!=NULL;current = current->next_name){
      if(current->next_name == rm ){
        current->next_name = rm->next_name;
      }
      else continue;
    }
  }
  int x = hash_function(rm->id,d->curArrSize);
  struct node *head1 = d->hash_ID[x];
  if(head1 == rm){
    head1 = rm->next_id;
  }
  else{
    struct node *current1;
    for(current1 = head1;current1!=NULL;current1 = current1->next_id){
      if(current1->next_id == rm){
        current1-> next_id = rm->next_id;
      }
      else continue;
    }
  }

  free(rm->id);
  free(rm->name);
  free(rm);
  rm->id = NULL;
  rm->name = NULL;
  rm = NULL; 
  
  d->numItems--;
  return 0;
}
/*--------------------------------------------------------------------*/
int
GetPurchaseByID(DB_T d, const char* id)
{
  /* fill out this function */
  //if there is no id, return -1,
  // if there is id, find node whose ID is id, and get purchase
  assert(d!=NULL);
  if(id == NULL) return -1;
  int h = hash_function(id,d->curArrSize);
  if(d->hash_ID[h] == NULL)
    return -1;
  printf("%d\n",searchNAME(d,id));
  if (searchID(d,id) == 0) return -1;
  struct node *c;
  for (c = d->hash_ID[h];c != NULL;c = c->next_id){
    if (strcmp(c->id,id)==0){
      return (c->purchase);
    }
    else continue;
  }    
  return (-1);
}
/*--------------------------------------------------------------------*/
int
GetPurchaseByName(DB_T d, const char* name)
{
  /* fill out this function */
  //if there is no name, return -1,
  // if there is id, find node whose NAME is name, and get purchase
  assert(d!=NULL);
  if(name == NULL) return -1;
  printf("s1\n");
  int h = hash_function(name,d->curArrSize);
  if(d->hash_NAME[h] == NULL)
    return -1;
  printf("s1\n");
  printf("%d\n",searchNAME(d,name));
  //if(searchNAME(d,name)==0) return -1;
  struct node *c;
  for (c = d->hash_NAME[h];c != NULL;c = c->next_name){
    if (strcmp(c->name,name)==0){
      return (c->purchase);
    }
    else continue;
  }    
  return (-1);
}
/*--------------------------------------------------------------------*/
int
GetSumCustomerPurchase(DB_T d, FUNCPTR_T fp)
{
  /* fill out this function */
  //iterate for hash_ID then iterate for linked lit in each element.
  assert(d!=NULL);
  if (fp == NULL) return -1;

  int sum = 0;
  for (int i = 0;i<(d->curArrSize);i++){
    if (d->hash_ID[i]==NULL){
      continue;
    }
    else {
      //printf("%s %s \n",d->hash_ID[i]->name,d->hash_ID[i]->id);
      struct node *c;
      for (c = d->hash_ID[i];c != NULL;c = c->next_id){
        sum = sum+fp(c->id,c->name,c->purchase);
      }
    }
      
  }
  return sum;

}

