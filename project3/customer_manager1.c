#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "customer_manager.h"




#define UNIT_ARRAY_SIZE 1024

struct UserInfo {
  char *name;                // customer name
  char *id;                  // customer id
  int purchase;              // purchase amount (> 0)
};

struct DB {
  struct UserInfo *pArray;   // pointer to the array
  int curArrSize;            // current array size (max # of elements)
  int numItems;              // # of stored items, needed to determine
			     // # whether the array should be expanded
			     // # or not
};

// DB -> pArray, curArrsize, numitems

/*--------------------------------------------------------------------*/
DB_T
CreateCustomerDB(void) //  create and return DB structure
{
 // can use DB_T by customer manager.h library 
  DB_T d;
  
  d = (DB_T) calloc(1, sizeof(struct DB)); //-> size : 20
  if (d == NULL) {
    fprintf(stderr, "Can't allocate a memory for DB_T\n");
    return NULL;
  }
  d->curArrSize = UNIT_ARRAY_SIZE; // start with 1024 elements
  d->numItems = 0;
  d->pArray = (struct UserInfo *)calloc(d->curArrSize,
               sizeof(struct UserInfo));
  if (d->pArray == NULL) {
    fprintf(stderr, "Can't allocate a memory for array of size %d\n",
	    d->curArrSize);   
    free(d);
    return NULL;
  }
  
  return d;

}
/*--------------------------------------------------------------------*/
void
DestroyCustomerDB(DB_T d)
{
  /* fill out this function */
  assert(d!= NULL);
  int set = d->numItems;
  int k = set/UNIT_ARRAY_SIZE;
  for(int i=0 ;i<k*UNIT_ARRAY_SIZE;i++){
    free(d->pArray[i].id);
    free(d->pArray[i].name);
  }
  free(d->pArray);
  free(d);
  //iterate for array and free one by one 
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
  int set = d->numItems;
  int k = set/UNIT_ARRAY_SIZE;
  if (k!=0){
    d->pArray = (struct UserInfo *)realloc(d->pArray,UNIT_ARRAY_SIZE*k); 
  } // k decide to do expansion or not
  if (set ==0){
    
  }
  for (int i=0;i<set;i++){
    if ((strcmp(d->pArray[i].id,id)&strcmp(d->pArray[i].name,name))==0){
      return -1;
    }
  }
  // check for same id or name
  d->pArray[set].id = strdup(id);
  d->pArray[set].name = strdup(name);
  d->pArray[set].purchase = purchase;
  //add item in the end of the array of items
  (d->numItems)++;
  return 0;
}
/*--------------------------------------------------------------------*/
int
UnregisterCustomerByID(DB_T d, const char *id)
{
  /* fill out this function */
  //find element to unregister and free it
  //then pull all the elements behind the freed memory to fill tbe blank
  if (d == NULL) return -1;
  if (id == NULL) return -1;
  int set = d->numItems;
  struct UserInfo *Customers = d->pArray;
  for (int i = 0; i< set;i++){
    if (strcmp(Customers[i].id,id)==0){
      //printf("Unregister ith NAME : %d\n",i);
      //printf("%s\n",Customers[i].name);
      
      free(d->pArray[i].name);
      free(d->pArray[i].id);
      //printf("s1\n");
      d->numItems--;
      if (i == set-1) {return 0;}
      //printf("s2\n");
      for(int j=i;j<set-1;j++){
        char *c1 = strdup(Customers[j+1].id);
        char *c2 = strdup(Customers[j+1].name);
        int c3 = Customers[j+1].purchase;
        Customers[j].id = c1;
        Customers[j].name = c2;
        Customers[j].purchase = c3;
        free(Customers[j+1].id);
        free(Customers[j+1].name);
      }
      return 0;
    }
    else continue;
  }
  
  return (-1);
}

/*--------------------------------------------------------------------*/
int
UnregisterCustomerByName(DB_T d, const char *name)
{
  /* fill out this function */
  //find element to unregister and free it
  //then pull all the elements behind the freed memory to fill tbe blank
  if (d == NULL) return -1;
  if (name == NULL) return -1;
  int set = d->numItems;
  struct UserInfo *Customers = d->pArray;
  for (int i = 0; i< set;i++){
    if (strcmp(Customers[i].name,name)==0){
      //printf("Unregister ith NAME : %d\n",i);
      //printf("%s\n",Customers[i].name);
      
      free(d->pArray[i].name);
      free(d->pArray[i].id);
      //printf("s1\n");
      d->numItems--;
      if (i == set-1) {return 0;}
      //printf("s2\n");
      for(int j=i;j<set-1;j++){
        char *c1 = strdup(Customers[j+1].id);
        char *c2 = strdup(Customers[j+1].name);
        int c3 = Customers[j+1].purchase;
        Customers[j].id = c1;
        Customers[j].name = c2;
        Customers[j].purchase = c3;
        free(Customers[j+1].id);
        free(Customers[j+1].name);
      }
      return 0;
    }
    else continue;
  }
  
  return (-1);
}
/*--------------------------------------------------------------------*/
int
GetPurchaseByID(DB_T d, const char* id)
{
  /* fill out this function */
  //iterate to find element that has same id, then return purchase
  if ( d==NULL ) return -1;
  if (id == NULL) return -1;
  int set = d->numItems;
  for (int i=0;i<set;i++){
    if(strcmp(d->pArray[i].id,id)==0){
      return d->pArray[i].purchase;
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
  //iterate to find element that has same name, then return purchase
  if ( d==NULL ) return -1;
  if (name == NULL) return -1;
  int set = d->numItems;
  for (int i=0;i<set;i++){
    if(strcmp(d->pArray[i].name,name)==0){
      return d->pArray[i].purchase;
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
  //iterate for all elements and sum fps
  if (d ==NULL) return -1;
  if (fp == NULL) return -1;
  int sum = 0;
  for (int i =0;i<(d->numItems);i++){
    sum = sum + fp(d->pArray[i].id,d->pArray[i].name,d->pArray[i].purchase);
  }
  return sum;

}

