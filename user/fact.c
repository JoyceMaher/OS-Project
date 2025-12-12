#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

uint64

fact(int x){
  uint64 result =1;
  for(int i=1;i<=x;i++){
  result*=i;}
  return result;
}

int main(int argc,char *argv[]){
    if(argc==2 && strcmp(argv[1],"?")==0)
    {
      printf("Usage: fact number/n");
      exit(0);
    }

    if(argc!=2)
    {
      printf("A single number only is allowed!");
      exit(0);
    }

    int n = atoi(argv[1]);

    if(n<0)
    {
      printf("Error:only positive a number is allowed!");
      exit(0);
    }

    uint64 result = fact(n);
    printf("Factorial of %d is %ld\n", n, result);

    exit(0);

}
