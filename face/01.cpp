int a[]={1,2,3,4};
int *b=a;
*b+=2;
*(b+2)=2;
b++; 
printf(“%d,%d\n”,*b,*(b+2));

https://www.nowcoder.com/test/question/analytic?tid=38464250