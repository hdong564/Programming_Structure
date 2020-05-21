/* 20180523_HandongLee , assignment2, str.c*/



#include <assert.h> /* to use assert() */
#include <stdio.h>
#include "str.h"
#include <string.h>
/* Your task is: 
   1. Rewrite the body of "Part 1" functions - remove the current
      body that simply calls the corresponding C standard library
      function.
   2. Write appropriate comment per each function
*/

/* Part 1 */
/*------------------------------------------------------------------------*/
size_t StrGetLength(const char* pcSrc)
{
  const char *pcEnd;
  assert(pcSrc); /* NULL address, 0, and FALSE are identical. */
  pcEnd = pcSrc;
	
  while (*pcEnd) /* null character and FALSE are identical. */
    pcEnd++;

  return (size_t)(pcEnd - pcSrc);
}

/*------------------------------------------------------------------------*/
char *StrCopy(char *pcDest, const char* pcSrc)
{
  /*It returns start pointer after copying iterately */
  assert(pcSrc!=NULL);
  char *start = pcDest;
  while(*(pcSrc)!='\0'){
    *pcDest = *pcSrc;
    pcDest++;pcSrc++;
  }
  *pcDest = '\0';
  
  return start;
}

/*------------------------------------------------------------------------*/
int StrCompare(const char* pcS1, const char* pcS2)
{
  /* It returns subtraction of each element. */
  assert(pcS1&&pcS2);
  size_t len1 = StrGetLength(pcS1);
  size_t len2 = StrGetLength(pcS2);
  
  while(*pcS2!='\0'){
    if (*pcS2>*pcS1){return *pcS1 - *pcS2;}
    else if (*pcS2<*pcS1){return *pcS1 - *pcS2;}
    else {pcS2++;pcS1++;}
    }
  if (len1>len2){return *pcS1-*pcS2;}
  else{return 0;}
}
/*------------------------------------------------------------------------*/
char *StrSearch(const char* pcHaystack, const char *pcNeedle)
{
  /* search for first char of pcNeedle in pcHaystack
   if program finds it, it iterately search for next element,
   and if it iterates for length fo pcNeedle times, it returns pointer */
  
  int len = (int)StrGetLength(pcNeedle);
  int same =0;
  if (len == 0){
    return (char *)pcHaystack;
  }
  while(*pcHaystack != '\0'){
    if (*pcHaystack == *pcNeedle){
      same++;
      pcHaystack++;pcNeedle++;
      while ((*pcHaystack==*pcNeedle)&&(*pcNeedle !='\0')){
	same++;
	pcHaystack++;pcNeedle++;
      }
      if (same==len){
	return ((char*)pcHaystack-len);
      }
      else{pcNeedle = pcNeedle - same;}
    }
    else {pcHaystack++;}
    
  }
  return NULL;
}
/*------------------------------------------------------------------------*/
char *StrConcat(char *pcDest, const char* pcSrc)
{
  /* pointer iterate until pcDest's '\0' part, 
     then append pcSrc after it */

  assert((pcDest!=NULL)&&(pcSrc!=NULL));
  char *start = pcDest;
  while(*pcDest != '\0'){
    pcDest++;
  }
  StrCopy(pcDest,pcSrc);
  
  return start;
}


    
