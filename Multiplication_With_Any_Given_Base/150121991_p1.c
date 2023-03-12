// Name: Niyazi Ozan Ateþ - StudentNumber: 150121991 - ProjectNumber: 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Here we struct the node for creating the LL. It contains the digit it will hold and a pointer to the next node.
struct node {
	int digit;
	struct node *nextPtr;
};

// Here we typedef our node and its pointer so that writing the code would by simplified and reading the code would be easier.
typedef struct node node;
typedef node *nextPtr;

// These are our function prototypes.
void createLinkedList(nextPtr *mainPtr, int newDigit);
void printList(FILE *fptrOutput, nextPtr currentPtr, int length);
void multiply(nextPtr result, nextPtr number1, nextPtr number2, int number1Length, int number2Length, int theBase);
int convertNumberToBase10(nextPtr mainNumber, nextPtr *based10Number, int length, int theBase);

// We create a file pointer to write to an output file.
	FILE *fptrOutput;

int main(int argc, char* argv[]){
    
    if(argc==1)
        printf("Error message!");
    if(argc>=2) {
    	
// We create a file pointer to read from an input file.
        FILE* fptrInput = fopen(argv[1], "r");
		fptrOutput = fopen("150121991_p1_output.txt","a+");
	
// Here we check if the file is found or not.
		if (fptrInput == NULL) {
			printf("The input file doesn't exists or is not found");
			fprintf(fptrOutput, "The input file doesn't exists or is not found");
			return 0;
		}
		if (fptrOutput == NULL) {
			printf("The output file doesn't exists or is not found");
			fprintf(fptrOutput, "The input file doesn't exists or is not found");
			return 0;
		}
	
// We create pointers for the numbers that will be multiplied and results. Both in the base and decimal form. These will be used to create the LL.
		nextPtr startPtr1 = NULL;
		nextPtr startPtr2 = NULL;
		nextPtr resultPtr = NULL;
		nextPtr firstNumberToBased10 = NULL;
		nextPtr secondNumberToBased10 = NULL;
		nextPtr resultToBased10 = NULL;
	
		int firstNumberLength = 0; // Keeping track of how long the LL for number1 is.
		int secondNumberLength = 0; // Keeping track of how long the LL for number2 is.
		char c = getc(fptrInput); // Gets the character from the file.
	
// With the while loops we create a LL until we are at the end of the line .
		while (!feof(fptrInput) && c != '\n') { 
			createLinkedList(&startPtr1, (c - 48));
			c = getc(fptrInput);
			firstNumberLength++;
		}
		c = getc(fptrInput);
		while (!feof(fptrInput) && c != '\n') {
			createLinkedList(&startPtr2, (c - 48));
			c = getc(fptrInput);
			secondNumberLength++;
		}
		int base = getc(fptrInput) - 48; // At this point we will get the base
	
// Because the base is between 2<=base<=10 and we accept that there are no input errors. It will mean that if we have read 1 as the base in the file it means that it says 10.
		if (base == 1) {
			base = 10;
		}
		int resultMaxLength = firstNumberLength + secondNumberLength; // Holds the maximum length of the result and it will be helpfull for creating and printing the result.
	
// Here we create the LL for the result of maximum length
		int i = 0;
		for (i = 0 ; i < resultMaxLength ; i++) {
			createLinkedList(&resultPtr, 0);
		}
	
// We multiply the first and second number in the given base and write the result in the result LL.
		multiply(resultPtr, startPtr1, startPtr2, firstNumberLength, secondNumberLength, base); 
	
// Here we convert each number that was in the base form to new a decimal number LL. We also return the length of that number so we can use it to print the number.
		int newLenght1 = convertNumberToBase10(startPtr1, &firstNumberToBased10, firstNumberLength, base);
		int newLenght2 = convertNumberToBase10(startPtr2, &secondNumberToBased10, secondNumberLength, base);
		int newLenghtResult = convertNumberToBase10(resultPtr, &resultToBased10, resultMaxLength, base);
	
// Here we print our numbers with the function in the console and also in the an output file.
		printList(fptrOutput, startPtr1, firstNumberLength);
		printList(fptrOutput, startPtr2, secondNumberLength);
		printList(fptrOutput, resultPtr, resultMaxLength);	
		printList(fptrOutput, firstNumberToBased10, newLenght1);
		printList(fptrOutput, secondNumberToBased10, newLenght2);
		printList(fptrOutput, resultToBased10, newLenghtResult);
	
// As last we close our files.
		fclose(fptrInput);
		fclose(fptrOutput);
		return 0;
	}
}

/* This function is used to create the LL for a given number.
   We first create a newPtr and create some space for that. If there is space for that node. Then we give the value to the digit in the node and set the nextPtr to NULL. Otherwise, we print an error in the console/output file.
   If its the first number we assign the sPtr to the newPtr, which is the first node. Otherwise, we add the first node to the LL.
   While doing this we do it in reverse order, which will help use by multiplying the number in the given base. Example: If the number is 5301 then the LL will be 1-0-3-5.
*/
void createLinkedList(nextPtr *sPtr, int value) {
	
	nextPtr newPtr = malloc(sizeof(node));
	
	if (newPtr != NULL) {
		newPtr->digit = value;
		newPtr->nextPtr = NULL;
		
		nextPtr currentPtr = *sPtr;
		
		if (currentPtr != NULL) {
			*sPtr = newPtr;
			newPtr->nextPtr = currentPtr;
		}
		else {
			*sPtr = newPtr;
		}
	}
	else {
		printf("Not enough space available to create a Linked List!");
		fprintf(fptrOutput, "Not enough space available to create a Linked List!");
	}
}

/* This function is used to print a number to the console and an output file.
   We check first if the there a is LL with a number. Otherwise, we print an error to the console/output file.
   Because we hold our information in a LL in reverse order, we have to first reverse it again to the normal version of that number. We do that with the while loop.
   After that we will check if there are any '0' at the start of the number with the firstIndexControl variable.
   If so, then we skip that part until we find a number other than '0' and start to print the digits one-by-one.
*/
void printList(FILE *fptrOutput, nextPtr currentPtr, int length) {
	
	if (currentPtr == NULL) {
		printf("List is empty, an error has been detected while running the program!");
		fprintf(fptrOutput, "List is empty, an error has been detected while running the program!");
		return;
	}
	
	int reversedNumberToNormalCondition[length];
	int i = 0;
	while (currentPtr != NULL) {
		reversedNumberToNormalCondition[i] = currentPtr->digit;
		currentPtr = currentPtr->nextPtr;
		i++;
	}
	
	int firstIndexControl = 0;
	for (i = 1 ; i <= length ; i++) {
		if (firstIndexControl == reversedNumberToNormalCondition[length-i]) {
			continue;
		}
		else {
			firstIndexControl = 10;
		}
		printf("%d", reversedNumberToNormalCondition[length-i]);
		fprintf(fptrOutput, "%d", reversedNumberToNormalCondition[length-i]);
	}
	printf("\n");
	fprintf(fptrOutput, "\n");
}

/* This function is used to multiply two numbers in a given base and write the result in a result LL.
   We create some pointers that will control the flow of the system and move around the LL, while the main pointer will stay at the start of the numbers.
   Because we got the numbers in the LL in reverse order, we just multiply the number one-by-one and if the result of that multiplication is higher than the base.
   We will put the remainder in the corresponding node and the integer division of that number with the base into the next node.
   The first for loop control the seconds number its digit which will multiply the whole first number while the second loop goes through the whole first number.
   We also reset the currentPtr1 to the start and move currentPtr2 to the next digit.
   While every turn of the first for loop we let the tempPtr start i indexes from the start of the result LL. This is because every time we multiply the next digit of the second number it goes by a multiply of that base.
*/
void multiply(nextPtr result, nextPtr number1, nextPtr number2, int number1Length, int number2Length, int theBase) {
	
	nextPtr tempPtr = result;
	nextPtr currentPtr1 = number1;
	nextPtr currentPtr2 = number2;
	
	int i = 0;
	int j = 0;
	int k = 0;
	
	for (i = 0 ; i < number2Length ; i++) {
		for (j = 0 ; j < number1Length ; j++) {
			tempPtr->digit = (currentPtr2->digit * currentPtr1->digit) + tempPtr->digit;
			if (tempPtr->digit >= theBase) {
				tempPtr->nextPtr->digit = (tempPtr->digit)/theBase + tempPtr->nextPtr->digit;
				tempPtr->digit = (tempPtr->digit)%theBase;
			}
			currentPtr1 = currentPtr1->nextPtr;
			tempPtr = tempPtr->nextPtr;
		}
		tempPtr = result;
		for (k = 0 ; k < i+1 ; k++) {
			tempPtr = tempPtr->nextPtr;
		}
		currentPtr1 = number1;
		currentPtr2 = currentPtr2->nextPtr;
	}
}

/* This function is used to convert a reversed number with a given base into a reversed decimal number LL and return its length.
   Because we don't want to get any overflow, we must use again a LL. Our number is in reversed order and while using a method without overflow we must reverse it, as in the while loop.
   When converting the number to decimal we have to use (number)^(index-1) formula. With knowing this. We will multiply the digit one time and add the digit to the right of it.
   After we have done that, we multiply the new total number and add the number right to it. And so on...
   Now that we have reverse our number, we can assign the biggest number which is at the most left to the first number of the LL.
   Next, we multiply that number with the base and if it's the first time we do it. We check if its bigger than or equal to 10. If so, we add a new node with the integer division of that number.
   And we hold the remainder in the node. If the case is that it's not the first time, then we multiply all the nodes by the base and add the next number.
   After this we check each node if its smaller then 10. If not than we shift the integer division of that number to the next node and keep the remainder in the node we were working on.
   If the last node is bigger than or equal to 10, we will create a new node to put the integer division value in it.
   Now we got our reversed number in decimal and return its length back so it can be printed out.
*/
int convertNumberToBase10(nextPtr mainNumber, nextPtr *based10Number, int length, int theBase) {
	
	nextPtr newPtr = malloc(sizeof(node));
	nextPtr currentPtr = mainNumber;
	
	int reversedNumberToNormalCondition[length];
	int i = 0;
	while (currentPtr != NULL) {
		reversedNumberToNormalCondition[length-i-1] = currentPtr->digit;
		currentPtr = currentPtr->nextPtr;
		i++;
	}
	
	int newLength = 1;
	
	if (newPtr != NULL) {
		newPtr->digit = reversedNumberToNormalCondition[0];
		newPtr->nextPtr = NULL;
		
		*based10Number = newPtr;
		currentPtr = *based10Number;
		
		int i = 0;
		int temp = 0;

		for (i = 1 ; i < length ; i++) {
			
			(currentPtr->digit) = (currentPtr->digit)*theBase;
				if ((currentPtr->digit) >= 10 && (currentPtr->nextPtr) == NULL) {
					temp = (currentPtr->digit)/10;
					(currentPtr->digit) = (currentPtr->digit)%10 + reversedNumberToNormalCondition[i];
					nextPtr tempPtr = malloc(sizeof(node));
					tempPtr->digit = temp;
					tempPtr->nextPtr = NULL;
					currentPtr->nextPtr = tempPtr;
					newLength++;
					continue;
				}
				else if ((currentPtr->digit) < 10 && (currentPtr->nextPtr) == NULL) {
					(currentPtr->digit) = (currentPtr->digit) + reversedNumberToNormalCondition[i];
					continue;
				}
				
				while ((currentPtr->nextPtr) != NULL) {
					currentPtr = (currentPtr->nextPtr);
					(currentPtr->digit) = (currentPtr->digit)*theBase;
				}

				currentPtr = *based10Number;
				(currentPtr->digit) = (currentPtr->digit) + reversedNumberToNormalCondition[i];
				
				while (currentPtr->nextPtr != NULL) {
					if ((currentPtr->digit) >= 10) {
						temp = (currentPtr->digit)/10;
						(currentPtr->digit) = (currentPtr->digit)%10;
						currentPtr = (currentPtr->nextPtr);
						currentPtr->digit = (currentPtr->digit) + temp;
					}
					else {
						currentPtr = (currentPtr->nextPtr);
					}
				}
				
				if ((currentPtr->digit) >= 10) {
					temp = (currentPtr->digit)/10;
					(currentPtr->digit) = (currentPtr->digit)%10;
					nextPtr tempPtr = malloc(sizeof(node));
					tempPtr->digit = temp;
					tempPtr->nextPtr = NULL;
					(currentPtr->nextPtr) = tempPtr;
					newLength++;
				}
				currentPtr = *based10Number;
		}
	}
	else {
		printf("Not enough space available to create a Linked List!");
		fprintf(fptrOutput, "Not enough space available to create a Linked List!");
	}
	return newLength;
}
