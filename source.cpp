#include <iostream>
#include <jni.h>
#include "header.h"
using namespace std;

//calling native methods 
// JNIEXPORT jnidatatype JNICALL method_name (JNIEnv *env, jobject obj_name, jdatatype/s var_names)

   JNIEXPORT jint JNICALL Java_header_add (JNIEnv *env , jobject obj, jint a, jint b)
   {
   jint result =a+b;
   cout<<"a+b = "<<result<<endl;
   return result;
   }

   JNIEXPORT jint JNICALL Java_header_sub (JNIEnv *env, jobject obj, jint a , jint b)
   { 
   jint result = a-b;
   cout<<"a-b = "<<result<<endl;
   return result;
   }
  
  
   JNIEXPORT jfloat JNICALL Java_header_div(JNIEnv *env, jobject obj, jint a , jint b)
   {
      if (b==0)
      {
        cout<<"Cant divide by 0"<<endl;
        return 0.0f;
      }
    jfloat result =a/b;
    cout<<"a/b = "<<result<<endl;
    return result;
    
   }
  
  JNIEXPORT jint JNICALL Java_header_mult(JNIEnv *env, jobject obj, jint a , jint b)
  {
     jint result = a*b;
     cout<<"a*b = "<<result<<endl;
     return result;
  
  }
/*OUTPUT 
pc@pc-Lenovo-S510:~$ javac header.java
pc@pc-Lenovo-S510:~$ javac -h . header.java
pc@pc-Lenovo-S510:~$ gcc -shared -o libsource.so -fPIC -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" source.cpp
source.cpp:2:10: fatal error: jni.h: No such file or directory
    2 | #include <jni.h>
      |          ^~~~~~~
compilation terminated.
pc@pc-Lenovo-S510:~$ export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
pc@pc-Lenovo-S510:~$ gcc -shared -o libsource.so -fPIC -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" source.cpp
pc@pc-Lenovo-S510:~$ java Djava.library.path=. header
Error: Could not find or load main class Djava.library.path=.
pc@pc-Lenovo-S510:~$ java -Djava.library.path=. header
Enter value of a :
24
Enter value of b :
7
MENU
1. Add 
 2. Subtract 
 3. Multiply 
 4. Divide 
Enter a choice : 
1
a+b = 31
MENU
1. Add 
 2. Subtract 
 3. Multiply 
 4. Divide 
Enter a choice : 
2
a-b = 17
MENU
1. Add 
 2. Subtract 
 3. Multiply 
 4. Divide 
Enter a choice : 
3
a*b = 168
MENU
1. Add 
 2. Subtract 
 3. Multiply 
 4. Divide 
Enter a choice : 
4
a/b = 3
MENU
1. Add 
 2. Subtract 
 3. Multiply 
 4. Divide 
Enter a choice : 
5
Invalid option selected, please enter a valid option 
pc@pc-Lenovo-S510:~$ 

*/
