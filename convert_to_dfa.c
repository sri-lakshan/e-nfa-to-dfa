#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
	int *states, init_state, *final_states, statecount;
	char *input;
	char delta[3][3][3];
} nfa;

int visited[20], pos=0;

int arrlength(int arr[]){
	int i=0;
	while(arr[i] != -1) i++;

	return i;
}

int contains(int arr[], int x){

	for(int i=0;i<pos;i++){
		if(arr[i]==x) return 1;
	}
	
	return 0;
}

int hash(int arr[]){
	int n = arrlength(arr), res=0, i;
	for(i=0;i<n;i++) res += pow(2, arr[i]);

	return res;
}

void display(int arr[]){
        int n = arrlength(arr);
	if(!n){
		printf("NULL");
		return;
	}
        for(int i=0;i<n;i++) printf("%d", arr[i]);
}

int dell(nfa *N, int *state, int length, char symbol){
	int *next_state = malloc(5*sizeof(int));
	int i,j; 

	for(i=0;i<length;i++){
		for(j=0;j<N->statecount;j++){
			if(strchr(N->delta[state[i]][j], symbol)) return j;
		}
	}

	return -1;
}

int *eclosure(nfa *N, int state){
	if(state==-1){
		int *new_state = malloc(sizeof(int));
		new_state[0] = -1;
		return new_state;
	}

	int i, index=1, start=0, end=0;
	int *new_state = malloc(5*sizeof(int));
	int current[] = {[0 ... 19] = -1};
	new_state[0] = state;
	current[0] = state;

	while(current[start] != -1){
		for(i=0;i < N->statecount;i++){
			if(strchr(N->delta[current[start]][i], 'e')){
				new_state[index++] = i;
				current[++end] = i;
			}
		}
		current[start++] = -1;
	}

	new_state[index++] = -1;

	return new_state;	
}

void lazy_eval(nfa *N, int *state){
	int n = arrlength(state), hashval;
	visited[pos++] = hash(state);
	
	printf("\nDELL ( ");
	display(state);
	int *zero = eclosure(N, dell(N, state, n, '0'));
	printf(" , 0 ) =  ");
	display(zero);
	hashval = hash(zero);
	if(zero[0] != -1 && !contains(visited, hashval)){
		lazy_eval(N, zero);
	}

	printf("\nDELL ( ");
        display(state);
        int *one = eclosure(N, dell(N, state, n, '1'));
        printf(" , 1 ) = ");
        display(one);
        hashval = hash(one);
        if(one[0] != -1 && !contains(visited, hashval)){
                lazy_eval(N, one);
        }

	//Comment this out if there is no input symbol "2" (2 does not belong to sigma)

	/*printf("\nDELL ( ");
        display(state);
        int *two = eclosure(N, dell(N, state, n, '2'));
        printf(" , 2 ) = ");
        display(two);
        hashval = hash(two);
        if(two[0] != -1 && !contains(visited, hashval)){
                lazy_eval(N, two);
        }*/

}

int main(){
	nfa *A = (nfa *)malloc(sizeof(nfa));

	//First NFA (Refer nfa1.jpg for diagram and answer2.jpg for the equivalent dfa)
	int state_c=3, finalstate_c=1, states[] = {0,1,2}, final_states[] = {2}, *eclos;
        char input[] = {'0','1','e'}, transition[3][3][3] = 	{{{'1'},{'e'},{}},
                                                                 {{},{'0'},{'e'}},
                                                                 {{'1'},{'0'},{}}};

	
	//Second NFA (Refer nfa2.png for diagram)
	/*int state_c=3, finalstate_c=1, states[] = {0,1,2}, final_states[] = {2}, *eclos;
        char input[] = {'0','1','e'}, transition[3][3][3] = 	{{{'1'},{'e','0'},{'0'}},
                                                                 {{},{'1'},{'e'}},
                                                                 {{},{},{'0','1'}}};*/

	//Third NFA (Refer nfa3.png for diagram)
	/*int state_c=3, finalstate_c=1, states[] = {0,1,2}, final_states[] = {2}, *eclos;
	char input[] = {'0','1','2','e'}, transition[3][3][3] = {{{'0'},{'e'},{},},
				                                 {{},{'1'},{'e'}},
                                				 {{},{},{'2'}}};*/

	//Fourth NFA (Refer nfa4.png for diagram)	
	/*int state_c=5, finalstate_c=1, states[] = {0,1,2,3,4}, final_states[] = {4}, *eclos;
        char input[] = {'0','1','e'}, transition[5][5][3] = 	{{{},{'e'},{'e'},{},{}},
                                                                 {{},{},{},{'0'},{}},
                                                                 {{},{},{},{'1'},{}},
								 {{},{},{},{},{'1'}},
								 {{},{},{},{},{}}};*/

	
	A->states = states;
	A->init_state = 0;
	A->final_states = final_states;
	A->input = input;
	A->statecount = state_c;
	memcpy(A->delta, transition, sizeof(transition));

	eclos = eclosure(A, A->init_state);
	
	lazy_eval(A, eclos);

	return 0;
}


			
	

	 
		

