#include<stdio.h>
#include<stdlib.h>
#include<string.h>



#define MAX_SIZE 10000

struct node;

struct list{
	struct node *nextNode;
	struct list *next;
};

struct node{
	char name[MAX_SIZE];
	int area;
	int id;
	struct node * next;
	struct list * pre;
	struct list * post;
};


struct node* hw1(int argc, char *argv){

	FILE* input_file = fopen(argv, "r");
	//FILE* output_file = fopen("function.out", "w+");

	char input_txt[MAX_SIZE], pre_txt[MAX_SIZE], tmp_txt[MAX_SIZE], current_txt[MAX_SIZE];
	char* p, *x,*y;
	char input[MAX_SIZE];
	char t[MAX_SIZE];
	char d[]=" ";
	struct node *head,*current;
	struct node *tmp, *tmp_input;
	struct list *list_tmp, *list_current;
	int flag = 0,flag2 = 0,flag3 = 0,flag4 = 0,flag5 = 0;
	char *name;
	int count;
	//fprintf(output_file,"Node function:\n");

	head = malloc(sizeof(struct node));
	strcpy(head->name,"0");
	head->next = NULL;
	head->pre = NULL;
	head->post = NULL;
	current = head;

	while(fgets(input_txt,MAX_SIZE,input_file) != NULL){
		//printf("%s",input_txt);
		if(flag5 == 1){
			strcat(pre_txt,input_txt);
			strcpy(input_txt,pre_txt);
			//printf("%s\n",input_txt);
		}
		if(strlen(input_txt)>2){
			if(input_txt[strlen(input_txt)-1] == '\n')
				input_txt[strlen(input_txt)-1] = '\0';
			count = 0;
			while(input_txt[strlen(input_txt)-1-count] == '\0'){
				count += 1;
			}
			if(input_txt[strlen(input_txt)-1-count] == '\\'){
				input_txt[strlen(input_txt)-1-count] = '\0';
				strcpy(pre_txt,input_txt);
				flag5 = 1;
				//printf("count:%d\n",count);
				continue;
			}
		}
		flag5 = 0;
		//printf("%s\n",input_txt);

		if(flag == 1){
			if(input_txt[0] == '0' || input_txt[0] == '1' || input_txt[0] == '-'){


				strcpy(tmp_txt,pre_txt);
				//printf("pre: %s\tcur: %s", pre_txt, input_txt);
				y = strtok(tmp_txt," ");
				while(y != NULL){
					strcpy(t,y);
					y = strtok(NULL," ");
				}
				strcpy(tmp_txt,pre_txt);
				if(flag2){
					//fprintf(output_file,"%s = ",t);
					flag2 = 0;
				}
				else{
					//fprintf(output_file," + ");
				}

				x = strtok(input_txt," ");
				y = strtok(tmp_txt," ");
				y = strtok(NULL," ");
				for(int i = 0;i<strlen(x);i++){
					if(x[i] == '0'){
						//fprintf(output_file,"%s' ",y);
					}
					else if(x[i] == '1'){
						//fprintf(output_file,"%s ",y);
					}

					y = strtok(NULL," ");
				}
			current = head->next;
				
			while(current != NULL){
				if(strcmp(current->name,t) == 0){
					current->area++;
					break;
				}
				current = current->next;
			}

			//printf("\n");
			//fprintf(output_file,"pre: %s\tcur: %s\n", pre_txt, input_txt);
			}
			else{
				//fprintf(output_file,"\n");
				flag = 0;
				strcpy(pre_txt, input_txt);
			}
		}
		else{
			strcpy(pre_txt, input_txt);
		}







		strcpy(current_txt,input_txt);
		p = strtok(current_txt," ");
		while(p != NULL){
			strcpy(t,p);
			p = strtok(NULL," ");
		}

		p = strtok(input_txt,d);
		if(strcmp(p,".inputs") == 0){
			p = strtok(NULL,d);
			
			while(p != NULL){
				tmp = malloc(sizeof(struct node));
				strcpy(tmp->name,p);
				tmp->next = NULL;
				tmp->pre = NULL;
				tmp->post = NULL;
				tmp->area = 0;
				current->next = tmp;
				current = tmp;
				p = strtok(NULL,d);
			}
		}
		
		else if(strcmp(p,".names") == 0){
			flag = 1;
			flag2 = 1;

			tmp = malloc(sizeof(struct node));
			tmp->next = NULL;
			tmp->pre = NULL;
			tmp->post = NULL;
			tmp->area = 0;
			strcpy(tmp->name,t);

			p = strtok(NULL,d);
			
			flag4 = 0;
			current = head;
			while(current != NULL){
				if(strcmp(current->name,t) == 0){
					flag4 = 1;
					free(tmp);
					tmp = current;
				}
				current = current->next;
			}
			if(flag4 == 0){
				current = head;
				while(current->next != NULL)
					current = current->next;
				current->next = tmp;
			}



			
			while(p != NULL){
				if(strcmp(t,p) == 0)
					break;
				flag3 = 0;
				current = head->next;
				while(current != NULL){

					if(strcmp(current->name,p) == 0){
						flag3 = 1;

						//post
						list_current = current->post;
						if(current->post != NULL){
							while(list_current->next != NULL)
								list_current = list_current->next;
						
							list_tmp = malloc(sizeof(struct list));
							list_current->next = list_tmp;
							list_current = list_current->next;
							list_current->nextNode = tmp; 
							list_current->next = NULL;
						}
							
						else{
							list_tmp = malloc(sizeof(struct list));
							current->post = list_tmp;
							current->post->nextNode = tmp; 
							current->post->next = NULL;
							//printf("post: %s\n",current->post->nextNode->name);
						}
						

						tmp->area++;
						//pre
						list_current = tmp->pre;
						//printf("pre: %s, cur: %s\n",tmp->name,current->name);
						if(tmp->pre != NULL){
							while(list_current->next != NULL)
								list_current = list_current->next;
						
							list_tmp = malloc(sizeof(struct list));
							list_current->next = list_tmp;
							list_current = list_current->next;
							list_current->nextNode = current; 
							list_current->next = NULL;


						}
							
						else{
							list_tmp = malloc(sizeof(struct list));
							tmp->pre = list_tmp;
							tmp->pre->nextNode = current; 
							tmp->pre->next = NULL;
						}
						
					}
					current = current->next;
				}

				if(flag3 == 0){
					current = head->next;
					while(current->next != NULL)
						current = current->next;
					tmp_input = malloc(sizeof(struct node));
					current->next = tmp_input;
					current = current->next;
					current->next = NULL;
					strcpy(current->name,p);

					list_tmp = malloc(sizeof(struct list));
					current->post = list_tmp;
					current->post->nextNode = tmp; 
					current->post->next = NULL;

					list_tmp = malloc(sizeof(struct list));
					list_current = tmp->pre;
					if(list_current != NULL){
						while(list_current->next != NULL)
							list_current = list_current->next;
						list_current->next = list_tmp;
						list_current = list_current->next;
						list_current->nextNode = current;
						list_current->next = NULL;
					}
					else{
						tmp->pre = list_tmp;
						tmp->pre->nextNode = current; 
						tmp->pre->next = NULL;
					}
						
				}
				
				p = strtok(NULL,d);
			}

		}
		
	}
	//fprintf(output_file,"END");

    fclose(input_file);
    //fclose(output_file);

    /*
    current = head->next;
    while(current != NULL){
    	printf("node: %s\n",current->name);
    	list_current = current->pre;
    	printf("pre: ");
    	
    	while(list_current != NULL){
	    	printf("%s\t",list_current->nextNode->name);
	    	list_current = list_current->next;
	    }
	    printf("\n");


    	list_current = current->post;
    	printf("post: ");
    	
    	while(list_current != NULL){
	    	printf("%s\t",list_current->nextNode->name);
	    	list_current = list_current->next;
	    }
	    printf("\n\n");
    	current = current->next;
    }
	*/

    /*
	
    printf("Please input a node: ");
    scanf("%s",input);
	while(strcmp(input,"0") != 0){
		current = head;
		while(current != NULL){
			if(strcmp(current->name,input) == 0){
				printf("seccessor: ");
				if(current->pre == NULL){
					printf("-");
				}
				else{
					list_current = current->pre;
					
					if(list_current != NULL){
						printf("%s",list_current->nextNode->name);
						list_current = list_current->next;
					}
					
					while(list_current != NULL){
						printf(", %s",list_current->nextNode->name);
						list_current = list_current->next;
					}
				}
				printf("\n");
				printf("predecessor: ");
				if(current->post == NULL){
					printf("-");
				}
				else{
					list_current = current->post;
					
					if(list_current != NULL){
						printf("%s",list_current->nextNode->name);
						list_current = list_current->next;
					}

					while(list_current != NULL){
						printf(", %s",list_current->nextNode->name);
						list_current = list_current->next;
					}
				}
				printf("\n");
			}
			
			
			current = current->next;
		}
		
		printf("Please input a node: ");
		scanf("%s",input);
	}
	
	*/
	return head;
}
