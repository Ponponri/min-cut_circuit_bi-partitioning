#include<stdio.h>
#include<stdlib.h>
#include "hw1.c"
#include "hw5.h"

int main(int argc, char *argv[]){

	FILE* input_file = fopen(argv[1], "r");
	struct node *head, *current, *current2;
	struct list *list_current;
	head = hw1(argc, argv[1]);

	int ratio = 100*(atof(argv[2])) - 50;
	if(ratio == 0){
		ratio = 1;
	}
	if(ratio > 49){
		ratio = 49;
	}
	//printf("ratio: %d\n",ratio);
	int count = 0;
	int v_num;
	int ind_num;
	int i;

	current = head->next;
    while(current != NULL){
    	current->id = count;
    	count+=1;
    	current=current->next;
    }

    int ptr[count];

    v_num = count;
    char names[v_num][MAX];
    int myarea[v_num];
    int wgts_v[v_num];
    int in_num = 0;
    int in_node[v_num];
	for(i=0;i<v_num;i+=1){
		in_node[i] = 0;
	}
	
    count = 0;
    current = head->next;
	while(current != NULL){
		strcpy(names[current->id],current->name);
		if(current->pre == NULL){
			in_node[current->id] = 1;
			in_num += 1;
		}
		myarea[current->id] = current->area;
		wgts_v[current->id] = current->area;
		count+=1;
		list_current = current->post;
    	while(list_current != NULL){
    		count+=1;
    		list_current = list_current->next;
    	}
    	current = current->next;
    }
    //printf("count:%d\n",count);

    ind_num = count;
    i=0;
    int ind[ind_num];
    int base=0,limit;
    current = head->next;
    while(current != NULL){
    	limit = 0;
    	ind[base+limit] = current->id;
    	//printf("%d ",current->id);
    	limit += 1;
    	list_current = current->post;
    	while(list_current != NULL){
    		ind[base+limit] = list_current->nextNode->id;
    		//printf("%d ", list_current->nextNode->id);
    		limit += 1;
    		list_current = list_current->next;
    	}
	//printf("\n");
    	ptr[i] = base;
    	i += 1;
    	base += limit;
    	current = current->next;
    }
    ptr[i] = base;

    /*
    printf("ptr: ");
    for(i=0;i<=v_num;i+=1)
    	printf("%d ",ptr[i]);
    printf("\nind: ");
    for(i=0;i<ind_num;i+=1)
    	printf("%d ",ind[i]);
    printf("\n");
    */
	//int ptr[] = {0,2,5,8,11,13,17,19,21,24,25,26};
	//int ind[] = {0,5,1,9,6,2,5,6,3,5,6,4,8,5,7,10,8,6,8,7,9,8,9,10,9,10};

    
    int flag;

    int connect_node[v_num];
    for(i=0;i<v_num;i+=1){
    	connect_node[i] = 0;
    }
	current = head->next;
	while(current != NULL){
		list_current = current->pre;
		flag = 0;
		while(list_current != NULL){
			for(i=0;i<v_num;i+=1){
				if(in_node[list_current->nextNode->id] == 0){
					flag = 1;
					//connect_node[current->id] = 1;
				}
			}
			list_current = list_current->next;
		}
		if(flag == 0){
			connect_node[current->id] = 1;
		}
		current = current->next;
	}

	int wgts_e[v_num];

	for(i=0;i<v_num;i+=1){
		wgts_e[i] = 0;
		//printf("con:%d\n",connect_node[i]);
	}
	
	current = head->next;
	while(current != NULL){
		
		if(in_node[current->id] == 1){
			flag=0;
			list_current = current->post;
			while(list_current != NULL){
				if(connect_node[list_current->nextNode->id] == 0){
					flag=1;
				}
				list_current = list_current->next;
			}
			if(flag == 0){
				wgts_e[current->id] = MAX;
			}
			else{
				wgts_e[current->id] = 0;
			}
		}
		else{
			count = 0;
			list_current = current->post;
			while(list_current != NULL){
				count += 1;
				list_current = list_current->next;
			}
			wgts_e[current->id] = count;
		}
		current = current->next;
	}
	/*
	printf("wgts_e: ");
	for(i=0;i<v_num;i+=1){
		printf("%d ",wgts_e[i]);
	}
	printf("\n");

	printf("wgts_v: ");
	for(i=0;i<v_num;i+=1){
		printf("%d ",wgts_v[i]);
	}
	printf("\n");
	*/

	//int wgts_e[] = {MAX,0,MAX,MAX,0,3,1,1,2,0,0};
	//int wgts_v[] = {0,0,0,0,0,4,8,2,4,6,3};

 	int op[] = {0,1,5,1,0,0,0,0,0};
	int nvtxs = v_num;
	int nhedges = v_num;

	int *vwgts = wgts_v;
	int *eptr = ptr;
	int *eind = ind;
	int *hewgts = wgts_e;
	int nparts = 2;
	int ubfactor = ratio;
	int *options = op;

	int part[MAX];
	int edgecut;

	for(int i=0;i<MAX;i++){
		part[i] = -1;
	}

	//printf("start\n");
	int x_area,y_area;
	float r_x=1.0,r_y=1.0;
	while(r_x > atof(argv[2]) || r_y > atof(argv[2])){
		HMETIS_PartRecursive (nvtxs, nhedges, vwgts, eptr, eind, hewgts, nparts, ubfactor, options, part, &edgecut);
		
		x_area = 0;
		y_area = 0;
		
		for(int i=0;i<MAX;i++){
			if(part[i] == -1){
				break;
			}
			//printf("%d: part:%d\n",i,part[i]);
			if(part[i] == 1){
				x_area += myarea[i];
			}
			else{
				y_area += myarea[i];
			}
		}

		

		r_x = (float)x_area/(x_area+y_area);
		r_y = (float)y_area/(x_area+y_area);

		ubfactor -= 1;
		if(ubfactor < 1){
			break;
		}
	}
	printf("Partition X:\nNode: ");
	for(i=0;i<v_num;i+=1){
		if(part[i] == 1 && in_node[i] == 0){
			printf("%s ",names[i]);
		}
	}
	printf("\narea: %d",x_area);
	printf("\nratio: %.3f\n",r_x);

	printf("Partition Y:\nNode: ");
	for(i=0;i<v_num;i+=1){
		if(part[i] == 0 && in_node[i] == 0){
			printf("%s ",names[i]);
		}
	}
	printf("\narea: %d",y_area);
	printf("\nratio: %.3f\n",r_y);

	printf("edgecut:%d\n",edgecut);

/*
	current = head->next;
    while(current != NULL){
    	printf("node: %s\n",current->name);
    	printf("id: %d\n",current->id);
    	printf("area: %d\n",current->area);
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
	return 0;
}