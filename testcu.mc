function hi(x){
   printf("%ld \n",x);
   return 0;
}

function main() {
  var i, sum;
  i = 1;
  sum = 0;
  while(i < 3) {
    sum = sum + 1;
    i = i + 1;
  }
  if( 1 && 1){
    printf("%ld \n",i);
  }
  i = hi(sum); 
 return sum;

}

