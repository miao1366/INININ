// https://www.nowcoder.com/test/question/analytic?tid=38464250

#include <stdio.h>
// int main() {

// int a[]={1,2,3,4};
// int *b=a;
// *b+=2;
// *(b+2)=2;
// b++; 
// printf("%d,%d\n",*b,*(b+2));
// }

// int main(int argc, char **argv)
// {
//     int a[4] = {1, 2, 3, 4};
//     int *ptr = (int *)(&a + 1);  //&a+1不是首地址+1，系统会认为加了一个整个a数组，偏移了整个数组a的大小
//     printf("%d", *(ptr - 1));
// }

int a(int tab){
   int n=tab-1;
   n |= n >> 1;
   n |= n >> 2;
   n |= n >> 4;
   n |= n >> 8;
   n |= n >> 16;
   return n;
}

int main(int argc, char **argv)
{
    printf("%d", a(666));
    printf("%d", a(510));
}