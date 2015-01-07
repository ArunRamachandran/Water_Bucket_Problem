/* Water Bucket Challenge 
   Given Smallest & Largest bucket sizes ( s_max, l_max)
   Have to fill one of them with exactly X leters of water */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node {
	int l_max, s_max;
	int l, s;
	struct node *next;
};

int GCF_X(int a, int b) {
	if (b == 0) 
		return a;
	else 
		return GCF_X(b, a % b);
}

struct node *initial(large, small, req) {

/* */   //printf("In Initial()\n");
	struct node *head = malloc(sizeof(struct node));

	head->l_max = large;
	head->s_max = small;
	head->l = 0;
	head->s = 0;

	return head;
}

char check_buckets(struct node *head, int s_max) {
	if (head->l == 0) return 'E';     //if Large is EMPTY--> then fill up the bucket
	if (head->s == s_max) return 'F'; //if small is FULL --> then empty the smallest
	if (head->l != 0 && head->s != s_max) return 'P'; //if neither of this present, then proceed to further process
}

void fill_large(struct node *head, int large, int small, struct node **new) {
	//struct node *new = malloc(sizeof(struct node));
	//printf("Filling large..\n");
	
	(*new)->l = large;
	(*new)->s = head->s;

	//return new;
}

void empty_small(struct node *head, int large, int small, struct node **new) {
	//struct node *new = malloc(sizeof(struct node));
	//printf("Emptying small..\n");

	(*new)->s = 0;
	(*new)->l = head->l;

	//return new;
}

void pour_water(struct node *head, int large, int small, struct node **new) {
	//struct node *new = malloc(sizeof(struct node));
	//printf("Pour_water..\n");
	int diff;

	if (head->s ==  0) {
		(*new)->s = head->l ; // pouring water from largest bucket to smallest
		if ((*new)->s > small) { // if beyond limit
			(*new)->s = small;
		}
		if (head->l <= small) {
			(*new)->l = 0;
		}
		if (head->l > small) {
			(*new)->l = (head->l) - small;
		}
	}
	if (head->s != 0) { 
		(*new)->s = head->s + head->l;
		if ((*new)->s > small) {
			diff = (*new)->s - small;
			(*new)->s = small;
		}
		if (head->l <= small) {
			(*new)->l = 0;
		}
		if (head->l > small) {
		//	(*new)->l = (head->l) - small;
			(*new)->l = diff;
		}
	}
		

	//return new;
}

struct node *get_result(struct node *head, int large, int small, int x) {

/*  */  //printf("In get_result() \n");
	struct node *temp = NULL;
	struct node *new  = malloc(sizeof(struct node));
	char status;

	if (head->next == NULL) { // if [0 0]
/*  */		//printf("Initial element detected..\n");
/*  */		//printf("Filling_large()\n");
		 fill_large(head, large, small, &new); // then new = [F 0]
		//printf("Returning new : \n");
		return new;
	}
	else {
/*  */          //printf("Detected more elements in head \n");
	
				
		while (head->next != NULL) {
			temp = head->next;
			head = temp;
		}

/*  */		//printf("Checking status..\n");
		status = check_buckets(head, small);
/*  */		//printf("Status : %c\n", status);
		if (status == 'E') {
			 fill_large(head, large, small, &new);
			//printf("new : [large : %d  small : %d]\n", new->l, new->s);
		}
		if (status == 'F') {
			empty_small(head, large, small, &new);
			//printf("new : [large : %d  small : %d]\n", new->l, new->s);
		}
		if (status == 'P') {
			pour_water(head, large, small, &new);
			//printf("new : [large : %d  small : %d]\n", new->l, new->s);
		}	
		
		return new;
	}
}


struct node *Append(struct node *head, struct node *new) {
	if (head == NULL) return new;
	else {
		head->next = Append(head->next, new);
		return head;
	}
}

void print(struct node *head, int l_max, int s_max) {
	printf("[%d/%d   %d/%d]\n", head->l, l_max, head->s, s_max);

	if (head->next != NULL)
		print(head->next, l_max, s_max);
	else return;
}

//int count;

struct node *meassure_water(struct node *head, int large, int small, int x) {
//	count++;

/*  */  //printf("In meassure_water()\n");
	struct node *new = NULL;
	
/*  */  //printf("Calling get_result()\n");
	new = get_result(head, large, small, x);
	head = Append(head,new);

	//printf("element in New.. : [new->s : %d  new->l : %d]\n",new->s, new->l); 

/* */   //printf("\n\n\n");

	if (new->s == x || new->l == x) return head;

	if (new->s != x || new->l != x) {
		 //printf("Not detected the desired result..\n");
		 //if (count == 20) return;
		 meassure_water(head, large, small, x);
	}
}
				
main() {
	int large, small; // To keep max sizes of 2 buckets.
	//int l, s; // To keep present amount of water in each buckets.
	int a, b, x, gcf;

	printf("Give the size of two buckets : \n");
	scanf("%d%d", &a, &b);
	if (a > b) {
		large = a;
		small = b;
	}
	else {
		large = b;
		small = a;
	}

	printf("Largest : %d, Smallest : %d\n", large,small);

	printf("Give an amount 'X' to meassure with these two : ");
	scanf("%d", &x);
	printf("X : %d\n", x);

/* */   //printf("Read Inputs....\n");

	if (x > large) {
		printf("Unable to Process...\n");
		printf("Value should be less than l_max\n");
		return;
	}
	gcf = GCF_X(large, small); // checking whether the given amount is a multiple of

/* */   //printf("Calcilated GCF : %d\n", gcf);
 
				// sizeof buckets.
	if (x % gcf != 0) {    // if the given amount is not a multiple of gcf
		printf("Unable to process...\n");
		printf("X : %d should be the multiple of gcf : %d\n", x, gcf);
		return;
	}
/* */   //printf("\n\n");
	if (x % gcf == 0 && x < large) { // if it satisfies both the conditions
		struct node *head = NULL;
/* */           
     		//printf("In Main() - Processing..\n");		
		head = initial(large, small, x);	
		//printf("Back to main()...\n");
		//printf("Calling meassure_water(%d, %d, %x)\n ", large, small, x);
		meassure_water(head, large, small, x); // meassuring water 
		print(head, large, small); // print result ... untill the result.
	}
	
}		
