#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <emscripten/emscripten.h>
#include "cJSON.h"
#include "cJSON.c"
#include <emscripten/fetch.h>
int value[10];
char key[10][50];
char string_value[10][100];
char string_key[10][50];
char func_name_s[10][50];
int getvalue(char* p) {
  for (int i = 0; i < 2; i++ ){   
      if(!strcmp(key[i],p))
        return  value[i];
  }  
  
  return -1;
}

void json_func(const char *file_input){
 
  cJSON *root_json= cJSON_Parse(file_input);
  if (NULL == root_json)
	{
    printf("cJSON_Parse error, status:%s\n", cJSON_GetErrorPtr());
    printf("NULL == root_json \n");
		cJSON_Delete(root_json);
	}
	else{
		
    int i;

    cJSON *item = cJSON_GetObjectItem(root_json,"data");
    for (i = 0 ; i < cJSON_GetArraySize(item) ; i++)
    {
      cJSON * subitem = cJSON_GetArrayItem(item, i);
      if(cJSON_GetObjectItem(subitem, "value")->valueint){
        strcpy(key[i], cJSON_GetObjectItem(subitem, "key")->valuestring);
        value[i]= cJSON_GetObjectItem(subitem, "value")->valueint;
        printf("%s: %d \r\n", key[i],value[i]);
      }
      else{
        strcpy(string_key[i], cJSON_GetObjectItem(subitem, "key")->valuestring);
        strcpy(string_value[i], cJSON_GetObjectItem(subitem, "value")->valuestring);
        printf("%s: %s \r\n", string_key[i],string_value[i]);
      }
      
      
    }
		cJSON_Delete(root_json);
  }
}
void downloadSucceeded(emscripten_fetch_t *fetch) {
  printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
  //printf("DATA : %s.\n",fetch->data);
  json_func(fetch->data);
  // The data is now available at fetch->data[0] through fetch->data[fetch->numBytes-1];
  emscripten_fetch_close(fetch); // Free data associated with the fetch.
}

void downloadFailed(emscripten_fetch_t *fetch) {
  printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
  emscripten_fetch_close(fetch); // Also free data on failure.
}

void fetch_test() {
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, "GET");
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
  attr.onsuccess = downloadSucceeded;
  attr.onerror = downloadFailed;
  emscripten_fetch(&attr, "data.json");
 
}

void set_parameter(){
  // strcpy(key[0], "value1");
  // value[0]=8888;
 

  // strcpy(string_key[0], "string1");
  // strcpy(string_value[0], "Canada and Mexico");
  
  fetch_test();
  srand(time(NULL));
}

char *getsrting(char* p) {
  for (int i = 0; i < 2; i++ ){   
      if(!strcmp(string_key[i],p))
        return  string_value[i];
  }  
  
  return "not found";
}
int double_fuc(int num) {
  return num*num;
}

int WebAssembly_func(char* func_name,int *in,int size){

  strcpy(func_name_s[0], "double_fuc");
  
  if(!strcmp(func_name,func_name_s[0])) 
    return double_fuc(in[0]);  
  
  return -1;
}
