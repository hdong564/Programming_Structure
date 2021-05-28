### --------------------------------------------------------------------
### mydc.s
###
### Desk Calculator (dc)
### --------------------------------------------------------------------

	.equ   ARRAYSIZE, 20
	.equ   EOF, -1
	
.section ".rodata"

scanfFormat:
	.asciz "%s"
printfFormat:
	.asciz "%d\n"

errorFormat:
	.asciz "dc: stack empty\n"
### --------------------------------------------------------------------

        .section ".data"


### --------------------------------------------------------------------

        .section ".bss"
buffer:
        .skip  ARRAYSIZE ##allocate space of 20B

### --------------------------------------------------------------------

	.section ".text"

	## -------------------------------------------------------------
	## int main(void)
	## Runs desk calculator program.  Returns 0.
	## -------------------------------------------------------------

	.globl  main
	.type   main,@function

main:

	pushl   %ebp
	movl    %esp, %ebp

input:

	## dc number stack initialized. %esp = %ebp
	
	## scanf("%s", buffer)
	pushl	$buffer ## push address of buffer into stack
	pushl	$scanfFormat
	call    scanf
	addl    $8, %esp
	## check if user input EOF
	cmp	$EOF, %eax
	je	quit
	
	## PSEUDO-CODE
	## /*
	##  * In this pseudo-code we are assuming that no local variables are created
	##  * in the _main_ process stack. In case you want to allocate space for local
	##  * variables, please remember to update logic for 'empty dc stack' condition
	##  * (lines 6, 15 and 20) accordingly.
	##  */
	##
	##1 while (1) {
	##2	if (scanf("%s", buffer) == EOF)
	##3		return 0;
	##4 	if (!isdigit(buffer[0])) {
	##5		if (buffer[0] == 'p') goto cm_p:
	##6		cm_p:  if (stack.peek() == NULL) { goto print_error:} /* is %esp == %ebp? */
	##9			printf("%d\n", (int)stack.top()); /* value is already pushed in the stack */
	##10			

	##11 	if (buffer[0] == 'q') { goto cm_q:
	##12	cm_q:	goto quit;
	##13	} else if (buffer[0] == '+') { goto op_add:
	##14	op_add:	int a, b;
	##15			if (stack.peek() == NULL) { goto print_error:
	##19			a = (int)stack.pop();
	##20			if (stack.peek() == NULL) { goto print_error:
	##21				printf("dc: stack empty\n");
	##22				stack.push(a); /* pushl some register value */
	##23				continue;
	##24			}
	##25			b = (int)stack.pop(); /* popl to some register */
	##26			res = a + b;
	##27 			stack.push(res);
	##28		} else if (buffer[0] == '-') {
	##29			/* ... */
	##30		} else if (buffer[0] == '^') {goto op_pow:
			#op_pow:
			##	int base,exponent;
			##loop1
	##if (stack.peek == NULL) goto print_error:
	##	int a = stack.pop()
	##if (stack.peek == NULL) goto print_error:
	##	int b = stack.pop()
	##if edi == 0 goto exp_0:
	##loop1: 
	##  if index == exp goto loopend: 
	##  eax = eax *eax
	## 	goto loop1:
	##loopend:
	## 	return eax
	##31			/* ... powerfunc() ... */
	##32		} else if { /* ... and so on ... */
	##33 	} else { /* the first no. is a digit */
	##34		int no = atoi(buffer);
	##35		stack.push(no);	/* pushl some register value */
	##36	}
	##37 }

## isdigit buffer[0] and sign value
	xor %ecx,%ecx
	movb buffer, %cl


## check -sign value
	cmpl $'_',%ecx
	je push_minus

##check isdigit
	pushl %ecx
	call isdigit
	addl $4, %esp
	
	cmpl $0, %eax
	je op_cm

	pushl $buffer
	call atoi ##parameter as pointer
	addl $4, %esp
	pushl %eax
	jmp input
	

	xorl %ecx, %ecx
	movb buffer, %cl



## check whether operation or command
op_cm:
	xorl %ecx, %ecx
	movb buffer, %cl


	cmpl $'p',%ecx
	je cm_p

	cmpl $'q',%ecx
	je cm_q
	##-----part 

	cmpl $'f',%ecx
	je cm_f

	cmpl $'c', %ecx
	je cm_c

	cmpl $'d', %ecx
	je cm_d

	cmpl $'r', %ecx
	je cm_r
	
	cmpl $'f',%ecx
	je cm_f

	cmpl $'+',%ecx
	je op_add

	cmpl $'-',%ecx
	je op_sub

	cmpl $'*',%ecx
	je op_mul

	cmpl $'/',%ecx
	je op_div

	cmpl $'%',%ecx
	je op_rem

	cmpl $'^',%ecx
	je op_pow


	jmp input

## convert to minus and push
push_minus:	
	movl $buffer, %esi
	addl $1, %esi
	pushl %esi
	call atoi 
	addl $4, %esp
	neg %eax
	pushl %eax
	jmp input

## print top stack value
cm_p:
	cmpl %esp, %ebp
	je print_error
	movl (%esp), %ecx
	pushl %ecx
	pushl $printfFormat
	call printf
	add $8, %esp
	jmp input

## getout
cm_q:
	jmp quit

## iterate with %esi to print all values in stack
cm_f:
	movl $0, %esi
	cmpl %esp, %ebp
	je input
	loop2:
		xor %ecx, %ecx
		xor %eax, %eax
		xor %edi, %edi
		movl %esp, %edi
		movl %esi, %eax
		imull $4, %eax
		addl %eax, %edi
		cmpl %edi, %ebp
		je loopend2
		movl (%esp,%esi,4),%ecx
		pushl %ecx
		pushl $printfFormat
		call printf
		addl $8, %esp
		inc  %esi
		jmp loop2
	loopend2:
		jmp input


## subtract the number of stacks to esp
cm_c:
	movl %esp, %edi
	movl %ebp, %esi
	subl %edi, %esi
	addl %esi , %esp
	jmp input

## pop and copy it to esi then push twice
cm_d:
	popl %esi
	pushl %esi
	pushl %esi
	jmp input

##pop two item and push it reversely
cm_r:
	popl %esi
	popl %edi
	pushl %esi
	pushl %edi
	jmp input

## check for error using cmp esp, ebp and pop two and add then push
op_add:
	cmpl %esp, %ebp
	je print_error
	popl %esi
	cmpl %esp,%ebp
	je print_error
	popl %edi
	addl %esi, %edi
	pushl %edi
	jmp input

## similar as add
op_sub:
	cmpl %esp, %ebp
	je print_error
	popl %esi
	cmpl %esp, %ebp
	je print_error
	popl %edi
	subl %esi, %edi
	pushl %edi
	jmp input

##similar as add and sub
op_mul:
	cmpl %esp, %ebp
	je print_error
	popl %eax
	cmpl %esp, %ebp
	je print_error
	popl %edi
	imull %edi
	pushl %eax
	jmp input

##quotient is saved to eax
op_div:
	cmpl %esp, %ebp
	je print_error
	popl %edi
	cmpl %esp, %ebp
	je print_error
	popl %eax
	cdq ## expanstion for getting fit of register siz

	idivl %edi
	
	pushl %eax
	jmp input

##remainder is saved to edx
op_rem:
	cmpl %esp, %ebp
	je print_error
	popl %edi
	cmpl %esp, %ebp
	je print_error
	popl %eax
	cdq
	idivl %edi
	pushl %edx
	jmp input

## goto loop1 if exponent is not 0, 
op_pow:
	cmpl %esp, %ebp
	je print_error
	popl %edi ##exponent
	cmpl %esp, %ebp
	je print_error
	popl %eax ##base
	movl %eax, %esi 
	movl $1, %ecx ## index
	
	cmpl $0, %edi
	je exp_0

##iterate and multiply self
	loop1: 
		cmpl %ecx, %edi 
		je loopend	
		imull %esi
		addl $1, %ecx
		jmp loop1

	loopend:
		pushl %eax
		jmp input
		exp_0:
			movl $1, %eax
			pushl %eax
			jmp input
	
##extra functions --
print_error: 
	pushl $errorFormat
	call printf
	add $4, %esp
	jmp input
##------------------


quit:	
	## return 0
	movl    $0, %eax
	movl    %ebp, %esp
	popl    %ebp
	ret


