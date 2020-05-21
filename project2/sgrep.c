#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* for skeleton code */
#include <unistd.h> /* for getopt */
#include "str.h"

#define FIND_STR        "-f"
#define REPLACE_STR     "-r"
#define DIFF_STR        "-d"

#define MAX_STR_LEN 1023

#define FALSE 0
#define TRUE  1

typedef enum {
  INVALID,
  FIND,
  REPLACE,
  DIFF
} CommandType;

/*
 * Fill out your functions here (If you need) 
 */

/*--------------------------------------------------------------------*/
/* PrintUsage()
   print out the usage of the Simple Grep Program                     */
/*--------------------------------------------------------------------*/
void 
PrintUsage(const char* argv0) 
{
  const static char *fmt = 
    "Simple Grep (sgrep) Usage:\n"
    "%s [COMMAND] [OPTIONS]...\n"
    "\nCOMMNAD\n"
    "\tFind: -f [search-string]\n"
    "\tReplace: -r [string1] [string2]\n"
    "\tDiff: -d [file1] [file2]\n";

  printf(fmt, argv0);
}
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/

/* it reads each line from stdin, and print the line to stdout
 if the line contains pcSearch*/
int
DoFind(const char *pcSearch)
{
  char buf[MAX_STR_LEN + 2]; 
  int len;
  if (StrGetLength(pcSearch)>1023){
    fprintf(stderr,"Error: argument is too long");
    return FALSE;
  }
   
  /* Read the line by line from stdin, Note that this is an example */
  while (fgets(buf, sizeof(buf), stdin)) {
    if ((len = StrGetLength(buf)) > MAX_STR_LEN) {
      fprintf(stderr, "Error: input line is too long\n");
      return FALSE;
    }
    if(StrSearch(buf,pcSearch)!=NULL){
      printf("%s",buf);
    } 
  }
   
  return TRUE;
}
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/

/*for each line from stdin, if it contains pcString, change the line 
 until all pcStrings change to pcStirng2 print out to stdout stream*/
int
DoReplace(const char *pcString1, const char *pcString2)
{
  char buf[MAX_STR_LEN + 2]; 
  int len;

  if (StrGetLength(pcString1)>1023){
    fprintf(stderr,"Error: argument is too long");
    return FALSE;
  }
  if (StrGetLength(pcString2)>1023){
    fprintf(stderr,"Error: argument is too long");
    return FALSE;
  }
  if (pcString1 == NULL){
    fprintf(stderr,"Error: Can't replace an empty substring");
    return FALSE;
  }
  while (fgets(buf, sizeof(buf), stdin)) {
    if ((len = StrGetLength(buf)) > MAX_STR_LEN) {
      fprintf(stderr, "Error: input line is too long\n");
      return FALSE;
    }

     while(StrSearch(buf,pcString1)!=NULL){
       char c1[MAX_STR_LEN];
       char c2[MAX_STR_LEN];
       char c3[MAX_STR_LEN];
       char *C1 = &c1[0];
       char *C2 = &c2[0];
       char *C3 = &c3[0];
       StrCopy(C1,buf);
       StrCopy(C3,buf);
       StrCopy(C2,pcString2);
       *(StrSearch(c1,pcString1)) = '\0';
       C3 = StrSearch(c3,pcString1)+StrGetLength(pcString1);
       char *temp = StrConcat(C1,c2);
       char *total = StrConcat(temp,C3);
       StrCopy(buf,total);
     }
       printf("%s",buf);
  }
  return TRUE;
}
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/*open each file1 and file2 to make FILE pointer. read each line
 of file1 and file2 then compare line by line. numline variable 
 is global variable that counts up each time it reads line.*/

int
DoDiff(const char *file1, const char *file2)
{
  char buf1[MAX_STR_LEN + 2];
  char buf2[MAX_STR_LEN + 2];
  FILE *txt1 = fopen(file1,"r");
  FILE *txt2 = fopen(file2,"r");
  int numline=1;
  int len;
  if (StrGetLength(file1)>1023){
    fprintf(stderr, "Error: argument is too long");
    return FALSE;
  }
  if (StrGetLength(file2)>1023){
    fprintf(stderr, "Error: argument is too long");
    return FALSE;
  }
  if (txt1==NULL){
    fprintf(stderr,"Error: fail to open file %s\n",file1);
    return FALSE;
  }
  if (txt2==NULL){
    fprintf(stderr,"Error: fail to open file %s\n",file2);
    return FALSE;
  }
  
  while(fgets(buf1,sizeof(buf1),txt1)!=NULL){
    if ((len = StrGetLength(buf1)) > MAX_STR_LEN) {
      fprintf(stderr, "Error: input line %s is too long\n",file1);
      return FALSE;
    }
    
    if (fgets(buf2,sizeof(buf2),txt2)!=NULL){
      if ((len = StrGetLength(buf2)) > MAX_STR_LEN) {
	fprintf(stderr, "Error: input line %s is too long\n",file2);
	return FALSE;
      }
      if(StrSearch(buf1,"\n")==0){
	StrConcat(buf1,"\n");
      }
      if(StrSearch(buf2,"\n")==0){
	StrConcat(buf2,"\n");
      }

      if(StrCompare(buf1,buf2)!=0){
	printf("%s@%d:%s",file1,numline,buf1);
	printf("%s@%d:%s",file2,numline,buf2);
      }
      numline++;
    }
    else {
      fprintf(stderr,"Error: %s ends early at line %d",file2,numline);
    }
  }
  if(fgets(buf2,sizeof(buf2),txt2)!=NULL){
    fprintf(stderr,"Error: %s ends early at line %d",file1,numline);
  }
  return TRUE;
}
/*-------------------------------------------------------------------*/
/* CommandCheck() 
   - Parse the command and check number of argument. 
   - It returns the command type number
   - This function only checks number of argument. 
   - If the unknown function is given or the number of argument is 
   different from required number, this function returns FALSE.
   
   Note: You SHOULD check the argument rule later                    */
/*-------------------------------------------------------------------*/ 
int
CommandCheck(const int argc, const char *argv1)
{
  int cmdtype = INVALID;
   
  /* check minimum number of argument */
  if (argc < 3)
    return cmdtype;
   
  /* check command type */ 
  if (strcmp(argv1, FIND_STR) == 0) {
    if (argc != 3)
      return FALSE;    
    cmdtype = FIND;       
  }
  else if (strcmp(argv1, REPLACE_STR) == 0) {
    if (argc != 4)
      return FALSE;
    cmdtype = REPLACE;
  }
  else if (strcmp(argv1, DIFF_STR) == 0) {
    if (argc != 4)
      return FALSE;
    cmdtype = DIFF;
  }
   
  return cmdtype;
}
/*-------------------------------------------------------------------*/
int 
main(const int argc, const char *argv[]) 
{
  int type, ret;
   
  /* Do argument check and parsing */
  if (!(type = CommandCheck(argc, argv[1]))) {
    fprintf(stderr, "Error: argument parsing error\n");
    PrintUsage(argv[0]);
    return (EXIT_FAILURE);
  }
   
  /* Do appropriate job */
  switch (type) {
  case FIND:
    ret = DoFind(argv[2]);
    break;
  case REPLACE:
    ret = DoReplace(argv[2], argv[3]);
    break;
  case DIFF:
    ret = DoDiff(argv[2], argv[3]);
    break;
  } 

  return (ret)? EXIT_SUCCESS : EXIT_FAILURE;
}
