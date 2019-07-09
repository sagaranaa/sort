#include <stdio.h>

// 素数
#define N 2999

int A[N];

// *p と *q の値を入れ替える関数
void swap(int *p, int *q){
  int tmp;
  tmp = *p;
  *p = *q;
  *q = tmp;
}


int quick_select(int A[], int n, int k){
  int i, j, pivot;

// 真ん中の要素をピボットとする
  pivot = A[n/2];
  A[n/2] = A[0];
  A[0] = pivot;
  for(i = j = 1; i < n; i++){
    if(A[i] <= pivot){
      swap(A+i, A+j);
      j++;
    }
  }

  if(j == k+1) return pivot;
  else if(j < k+1) return quick_select(A+j, n-j, k-j);
  else return quick_select(A+1, j-1, k);
}

int median_of_median(int A[], int n, int k){
  if(n<=5){
    return quick_select(A, n, k);
  }else{
    int i,j,l,pivot;
    int len_A = n;
    int len_B = 0;
    int B[(N+4)/5];

    while(len_A>=5){
      B[len_B] = median_of_median(A+5*len_B, 5, 2);
      len_A-=5;
      len_B++;
    }
    if(len_A!=0)B[len_B] = median_of_median(A+5*len_B,len_A,len_A/2);

    pivot = median_of_median(B,len_B+1,(len_B+1)/2);
    for(i = j = 0; i < n; i++){
      if(A[i] < pivot){
        swap(A+i, A+j);
        j++;
      }
    }

    for(i = l = j; i < n; i++){
      if(A[i] == pivot){
        swap(A+i, A+l);
        l++;
      }
    }

    if(j <= k){
      if(l < k+1) return median_of_median(A+l, n-l, k-l);
      else return pivot;
    }else return median_of_median(A, j, k);

  }

}


int main(){
  int i;
  A[0] = 0;
  A[1] = 17; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }

  for(i=0;i<N;i++){
    if(median_of_median(A, N, i) != i) printf("ERROR %d\n", i);
    //printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
