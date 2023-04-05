#include <stdio.h>
#include <ctype.h>

int main(void){
		
		int x;
			
			printf("16진수 숫자 입력: ");
				scanf("%x", &x); 
					
					for (int i = 15; i > 11; i--) {
						        int result = x >> i & 1;
							        printf("%d", result);
								    }
					    printf(" : ");
					        for (int i = 11; i > 8; i--) {
							        int result = x >> i & 1;
								        printf("%d", result);
									    }
						    printf(" : ");
						        for (int i = 8; i >= 0; i--) {
								        int result = x >> i & 1;
									        printf("%d", result);
										    }
							    printf("\n");
							    	
							    	return 0;
}
