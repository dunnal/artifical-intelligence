#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void main(){
	int x = 6;
	int count=0;
	
	while(x != 0){
		x-=2;
		if(x <= 0){
			break;
		}
		count++;
		x+=1;
		count++;
		printf("%d\n",x);
	}
	count++;
	
	printf("%d\n", count);
	
}