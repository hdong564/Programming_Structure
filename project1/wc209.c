//20180523 Handong_Lee assignment1 

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

//word counting system
//count for # of words, lines, characters. comment as one character
/*There are severaks rules for this program
use many expressions of DFA
compile this file with gcc209
DFAState of IN OUT CMIN CMOUT 
*/
enum DFAState {IN ,OUT, CM1, CM2, CMin ,LCM} ;
//CM1 CM2 LCM1 LCM2 refers to /* abc */
int main(){ // transition occurs between stats, and count.

	/* 1. count lines(numberof lines) regardless of comment.
	   2. count cWords(#of words) when OUT goes to IN or CM1 
	   3. count chars(#of characters) at every transition except, 
              CM1,CM2,CMin,LCM*/
    int lines, cWords, chars ;
    enum DFAState state =  OUT;
    enum DFAState beforeState = OUT;
    lines =1; cWords =0; chars =0; 
    int positionComment; 
/*check where the comment
begun when Program return error*/ 
    int c =0; 
    int findError =0;//indicator of Errormessage.
    
    while((c=getchar())!= EOF){
        if (c ==10){        // new line for ascii code : 10
            lines++;         //count up lines regardless of comment
        }
        switch (state){ 
		/* inside of the word, transition can occur
		   to OUT, CM1 or IN again.   */
	    case IN:          
                if(isspace(c)){ //transition #1      
                    state = OUT;
                    chars++;
                    beforeState = IN; break;
                }
                else if (c== 47){  //transition #2
                    state = CM1; 
                    chars++;
                    beforeState = IN; break;
                }
                else {state = IN; chars++; break;} //transition #3                        
            case OUT:       
		/* outside of the word, transition can occur to 
		   OUT again, IN, CM1 */
                
                if(!isspace(c)){ 
                    if (c == 47) {state = CM1; cWords++ ;chars++ ;
			beforeState = OUT; break;} //transition 4
                    else {state = IN; cWords++;chars++;
			beforeState = OUT; break;}// transition 5
                }
                else if (isspace(c)){state = OUT; chars++;
			beforeState = OUT; break;} // transition 6
            case CM1:
		/* startpoint of the comment. Transition can occour to
		   {IN OUT} (exit comment)
		   {CM2} (real start of comment)*/
                
                if (c!=42){
                    if(isspace(c)){ 
			state = OUT;
			chars++;
			beforeState = CM1; 
			break;
		    } //transition #7
                    else if (c==47){
			state = CM1;
			chars++;
			beforeState = IN ;
		        break; 
			} //transition 8
                    else{ 
			state = IN;chars++;
			beforeState = CM1;
			break;}// transition #9
                    }
                else if( c == 42) { 
                state = CM2;
                if (beforeState == OUT){cWords--;}  
                chars--;
                positionComment = lines; // Real start of comment 
                findError =1;
                beforeState = CM1; break; 
                } //transition #10
                //start comment after this state

            case CM2: /* position of * of initial comment in comment*/
                
                if(c == 10){chars++; break;}
                else if(c!=42){ state = CMin;beforeState = CM2; break;} 
			// AL #6
                else if(c == 42){state = LCM; beforeState = CM2; break;} 
			// AL #7

            case CMin:/* position of letters in side the comment*/
                
                if(c == 10){chars++;beforeState = CMin; break;}
                else if (c==42) {state = LCM;beforeState = CMin; break;} 
			//transition #8
                else if (c!=42) {state = CMin;beforeState = CMin; break;} 
			//transition 8-r
            case LCM: /* position of last letter in comment*/
                
                if(c == 10){chars++;state = CMin;beforeState = LCM; break;}
                else if (c==42){state = LCM;break;}
                else if(c!=47){state = CMin;beforeState = LCM; 
			break;} //AL #9  
                else if(c==47){chars++;state = OUT; findError =0;
			beforeState = LCM; break;} //AL #10
                
               
            default:
                printf(" there is some error");

        }

        
        
    } 
    if (findError ==1){
	fprintf(stderr, "Error: line %d: unterminated comment\n", positionComment);
	return EXIT_FAILURE; }
    else{
        printf ("%d %d %d\n", lines, cWords, chars);
    }






    return EXIT_SUCCESS;
}   


