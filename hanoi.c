#include <stdio.h>
#include <stdlib.h>

#define MAX 15

//int init(int *first, int *second, int *third); 
int move(int *to, int *from, int l); 
int readarray(int *a, int l);
int display(int *first, int *second, int* third, int l); 
int ring(int size, int indent); 
int *movewrap(int *first, int *second, int *third, char c); 
int isfull(int *tower, int h); 
int isempty(int *tower, int h); 
int iswin(int *third, int h); 

//next up
//create a "did i win", functon
//create a move function format such as m 1 2
//allow the user to pic the variable n. the define in the header should be maximum length, say 10
//print instructions only after -h 

int main(int argc, char *argv[])
{
	int first[MAX];
	int second[MAX];
	int third[MAX];
	
	int n; 
	int i;
       	char c;

	//test the arguemtn is one and an integer
	if (argc != 2){
		printf("This program should be called with a single argument between 1 and 9. e.g. >hanoi 9\n."); 
		return 0; 
	}

	if (*argv[1] > '9' || *argv[1] < '1'){
		printf("This program should be called with an argument between 1 and 9. e.g. >hanoi 9\n."); 
		return 0;	
	}

	n = *argv[1] - '0'; 

	for (i=0; i<n; i++){
		first[i] = i+1;
		second[i] = 0;
		third[i] = 0;
		//printf("%d\n", first[i]); 
	}

	int *to, *from; 

	while ((c = getchar()) != EOF){
		switch(c) {
		case 'd':
			display(first, second, third, n); 
			printf("\n"); 
			break;

		case 'm': 
			printf("Which tower to move a ring from? Select 1-3. Enter c to cancel \n");
			
			while ((c = getchar()) != EOF){
			        
				if (c == 'c')
					break; 	
				if ((c == '1') || (c == '2') || (c == '3')){
					from = movewrap(first,second,third,c);
					if (isempty(from,n) == 1) {
						printf("That tower is empty. Select another or enter c to cancel.\n"); 
					}
					else
						break; 
				}
			}

			if (c == 'c')
				break; 	
		       	
			printf("Which tower to move to? Enter 1-3. Enter c to cancel. \n");
			while ((c = getchar()) != EOF){
				
				if (c == 'c')
					break; 

				if ((c == '1') || (c == '2') || (c == '3')){
					to = movewrap(first, second, third, c); 
					if (isfull(to,n) == 1) {
						printf("That tower is full. Select another or enter c to cancel.\n"); 
					}
					else
						break; 
				}			
			}
			
			if (c == 'c')
				break; 

			//do the move here!
			move(to,from, n); 
			display(first, second,third, n); 
			if (iswin(third, n) == 1){
				printf("You won!\n");
				return 0; 
			}
			break; 

		case 'h':
			printf("(d) display \t  (m) \t move a ring \t (q) quit \t (h) print this message again.\n"); 
			break; 

		case '\n': 
			break;

		case '\t': 
			break; 
		
		case ' ':
			break; 

		case 'q': 
			return 1; 
			
		default:
			printf("Invalid input.\n"); 
			break; 
		}	
	}
}

int readarray(int *a, int l){
	int j;
	for (j=0; j<l; j++){
		printf("\ta[%d] = %d\n", j, *(a+j));
	}
	return 1;
}

int isfull(int *tower, int h){
	if (*(tower + h - 1) == 0)
		return 0;
	else 
		return 1; 
}	

int isempty(int *tower, int h){
	if (*tower == 0)
		return 1;
	else
		return 0; 
}
int *movewrap(int *first, int *second, int *third, char c){
	switch(c){
	case '1':
		return first; 
	case '2': 
		return second;
	case '3':
		return third; 
	default:
		return NULL; 
	}
}

int iswin(int *third, int h){
	int i; 
	for (i=0; i<h; i++)
		if (*(third+i) != i+1)
			return 0;
	return 1; 
}

//the top ring should occupy space 0 and work from there
int move(int *to, int *from, int l) //moves ring
{
	//check there is something in from
	//check to is not full 
	
	if (*from == 0){
		printf("from is empty!\n");
		return 0;
	}

	if (*(to+l-1) != 0){
		printf("to is full!\n"); 
		return 0;
	}
	int i; 
	int foo[l]; 

	for (i=0; i<l; i++)
		foo[i] = *(to+i);

	*(to) = *(from); 
	for (i=0; i<l-1; i++) 
		*(to+i+1) = foo[i]; 

	for (i=0; i<l-1; i++)
		*(from + i) = *(from+i+1);

	*(from + l - 1) = 0;

	return 1;
}

int display (int *first, int *second, int *third, int l)
{
	//first determine the number of rings on each 
	//start with the one with the most rings and work descending
	//make a functin to display a ring or empty part of the stick **||**
	//number is the total amount of rings	
	//
	int l1, l2, l3; //number of rings on first second third
	int i; 

	int index1, index2, index3; //variable to keep track of when we start displaying the rings
	putchar('\n');
	
	l1 = 0;
	l2 = 0; 
	l3 = 0;
	for (i=0; i<l; i++){
		if (*(first+i) == 0)
			break; 
		l1 += 1; 
	}

	for (i=0; i<l; i++) {
		if (*(second+i) == 0)
			break;
		l2 += 1; 
	}
	
	for (i=0; i<l; i++){
		if (*(third+i) == 0)
			break;
		l3 += 1; 
	}
	
	index1 = 0;
	index2 = 0; 
	index3 = 0; 

	for (i=0; i<l; i++){
		if (l1 < (l-i)) //if the last index is empty
			ring(0, l); 
		else {
		        ring(*(first+index1), l);
	       		index1 += 1; 	       
		}
		
		putchar('\t'); 

		if (l2 < (l-i))
			ring(0, l);
		
		else {
			ring(*(second+index2), l); 
			index2 += 1;
		}		
		putchar('\t'); 

		if (l3 < (l-i))
			ring(0,l); 
		
		else { 
			ring(*(third+index3), l); 
			index3 += 1; 
		} 
		putchar('\n'); 	
	}	
	return 1;
}

int ring(int size, int indent) {
	int i;
	if (indent < size){
		printf("Error. indent < size\n"); 
		return 0; 
	}
       	for (i=0; i<indent-size; i++)
		putchar(' '); 	
	for (i=0; i<size; i++)
		putchar('*'); 
	putchar('|');
	putchar('|');
	for (i=0; i<size; i++)
		putchar('*');

       	for (i=0; i<indent-size; i++)
		putchar(' '); 	
	return 1;
}
