void consoleLog (int num);
const int SIZE = 10;
int data[SIZE];
int main() { 
  int i,j;
  int total=0;
  int flag=1;
    for (i = 0; i <20; i++) {
      for (j = 0; j <20; j++) {
        
        if(total>1000)
          flag=0;
        else if(total<0)
          flag=1;
        if(flag)
          total=total+i+j;
        else 
          total=total-i-j;
      }
    }
    consoleLog (total);
    return total;
}
int add(int value) { 
  for (int i=0; i<SIZE; i++) {
    data[i] = data[i] + value;
  }
  return 1;
}
int* getData() {
  consoleLog (123);
  return &data[0];
}
int getArraySize() {
  consoleLog (sizeof(data)/sizeof(int));
 
  return sizeof(data)/sizeof(int);
}