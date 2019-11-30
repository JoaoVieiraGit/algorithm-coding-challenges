#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <string.h>
#include <math.h>

int n;
int vertices[21][2];
int saved[21][2];
int convex_hull[21][2];
float result = 0.0;
int found = 0;


int counterclockwise(int ponto1[], int ponto2[], int ponto3[])
{
  return (ponto2[0] - ponto1[0])*(ponto3[1] - ponto1[1]) - (ponto2[1] - ponto1[1])*(ponto3[0] - ponto1[0]);
}


void geometry(){
    int i;
    int t;
    int k = 0;
    for (i=0; i< n; ++i){
        while (k >= 2 && counterclockwise(convex_hull[k-2], convex_hull[k-1], vertices[i]) <= 0){ --k;}
        convex_hull[k][0] = vertices[i][0];
        convex_hull[k++][1] = vertices[i][1];
    }
    for (i = n-2, t = k+1; i >= 0; --i) {
        while (k >= t && counterclockwise(convex_hull[k-2], convex_hull[k-1], vertices[i]) <= 0){ --k;}
        convex_hull[k][0] = vertices[i][0];
        convex_hull[k++][1] = vertices[i][1];
    }
}


int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

void differences(){
    int i,k=0;
    int changes = 0;
    int first[2];
    float area = 0.0;
    for (i=0; i<n; i++){
        if (saved[i][0] == convex_hull[k][0] && saved[i][1] == convex_hull[k][1]){
            k++;
            if(changes == 1) {
                area += saved[i-1][0] * first[1] - saved[i-1][1] * first[0];
                printf("%d %.1f\n", found, fabs(area/2));
                found++;
                changes = 0;
            }
            area=0.0;
        }
        else{
            if (area == 0){
                first[0] = convex_hull[k][0];
                first[1] = convex_hull[k][1];
                area += convex_hull[k][0] * convex_hull[k-1][1] - convex_hull[k][1] * convex_hull[k-1][0];
                changes = 1;
            }
            area += saved[i-1][0] * saved[i][1] - saved[i-1][1] * saved[i][0];
            if(i==n-1){
                area += saved[i][0] * first[1] - saved[i][1] * first[0];
                printf("%d %.1f\n", found, fabs(area/2));
                area = 0;
                changes = 0;
            }
        }
    }
}

int main()
{
    int i;
    while (scanf("%d", &n) != EOF){
        found = 0;
        memset(vertices,0,sizeof(int)*21);
        memset(saved,0,sizeof(int)*21);
        memset(convex_hull,0,sizeof(int)*21);
        result = 0.0;
        for (i=0 ; i < n ; i++){
            scanf("%d %d", &vertices[i][0], &vertices[i][1]);
            saved[i][0] = vertices[i][0];
            saved[i][1] = vertices[i][1];
        }
        qsort (vertices, i, sizeof(int) * 2, compare);
        geometry();
        differences();
    }
    return 0;
}
