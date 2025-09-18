#include <iostream>
#include <jni.h>
#include "A3.h"
using namespace std;

//calling native methods 
// JNIEXPORT jnidatatype JNICALL method_name (JNIEnv *env, jobject obj_name, jdatatype/s var_names)

   JNIEXPORT jint JNICALL Java_A3_add (JNIEnv *env , jobject obj, jint a, jint b)
   {
   jint result =a+b;
   cout<<"a+b = "<<result<<endl;
   return result;
   }

   JNIEXPORT jint JNICALL Java_A3_sub (JNIEnv *env, jobject obj, jint a , jint b)
   { 
   jint result = a-b;
   cout<<"a-b = "<<result<<endl;
   return result;
   }
  
  
   JNIEXPORT jint JNICALL Java_A3_div(JNIEnv *env, jobject obj, jint a , jint b)
   {
      if (b==0)
      {
        cout<<"Cant divide by 0"<<endl;
      }
    jint result =a/b;
    cout<<"a/b = "<<result<<endl;
    return result;
    
   }
  
  JNIEXPORT jint JNICALL Java_A3_mult(JNIEnv *env, jobject obj, jint a , jint b)
  {
     jint result = a*b;
     cout<<"a*b = "<<result<<endl;
     return result;
  
  }
