#include <stdio.h>
#include <stdlib.h>
#define AMOUNT 10000

void print_list(int *list, int size){
  if(size == 1){
    printf("[%d]", list[0]);
    return;
  }
  for(int i=0; i<size; i++){
    if(i == 0){
      printf("[%d,", list[i]);
      continue;
    }
    if(i == size-1){
      printf("%d]", list[i]);
      return;
    }
    printf("%d,", list[i]);
  }
}

int *merge(int *left, int lsize, int *right, int rsize, int *list){
  int size = lsize+rsize;
  int p1 = 0;
  int p2 = 0;
  for(int i=0; i<size; i++){
    if(p1 == lsize){
      list[i] = right[p2];
      p2++;
    }
    else if(p2 == rsize){
      list[i] = left[p1];
      p1++;
    }
    else if(left[p1] == right[p2]){
      list[i] = left[p1];
      p1++;
    }
    else if(left[p1] < right[p2]){
      list[i] = left[p1];
      p1++;
    }
    else if(left[p1] > right[p2]){
      list[i] = right[p2];
      p2++;
    }
  }
  free(right);
  free(left);
  return list;
}

int *split(int *list, int size){
  if(size < 2) {
    return list;
  }
  int left = size/2;
  int right = size-left;
  int *first_half = calloc(left,sizeof(int));
  for(int i=0; i<left; i++){
    first_half[i] = list[i];
  }
  int *second_half = calloc(right,sizeof(int));
  for(int j=0, i=left; j<=right; i++,j++){
    second_half[j] = list[i];
  }
  return merge(split(first_half, left), left, split(second_half, right), right, list);
}


int main() {
  int *list = calloc(AMOUNT, sizeof(int));
  for(int i=AMOUNT; i>0; i--){
    list[AMOUNT-i] = i;
  }
  split(list,AMOUNT);
  print_list(list,AMOUNT);
  free(list);
  return 0;
}
