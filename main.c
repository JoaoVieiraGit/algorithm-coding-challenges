#include <stdio.h>
#include <stdlib.h>

int n;
int homework[20000][2];
int current;
int max = 0;

int comp(const void* p1, const void* p2) {
	int *arr1 = (int*) p1;
	int *arr2 = (int*) p2;
	int diff1 = arr1[1] - arr2[1];
	if (diff1) return diff1;
	return arr1[0] - arr2[0];
}


void greedy(){
	int k, max = 0;
	qsort(homework, n, sizeof(int) * 2, comp);
	for (k=0;k<n;k++){
		if (current + homework[k][0] - homework[k][1] > max) max = current + homework[k][0] - homework[k][1];
		current += homework[k][0];
	}
	printf("%d\n",max);
}

int main()
{
    int i;
    while(scanf("%d", &n) != EOF){
	    for(i=0;i<n;i++){
	    	scanf("%d %d", &homework[i][0], &homework[i][1]);
	    }
	    scanf("%d",&current);
	    greedy();
	    max = 0;
	}
	return 0;
}
