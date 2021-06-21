#include<iostream>
#include "keyvalue.cpp" //The api(library) of the data store is included in this program . Hence we can access the contents of the data store.
#include<windows.h>
#include<thread>

using namespace std;

int main()
{
    // New instance of our data store fazul is created by heap allocation.
    fazul * taskPtr = new fazul();
    taskPtr->create("variable","{int : 478345; float : 87473948.574; char : characters",8); // creating a key-value pair in our data store with time stamp.
    
    taskPtr->create("myObj"," { name : John , age : 30, cars : { car1 : Ford , car2 : BMW , car3 : Fiat } }");

    // here we use multithreading concept to make sure that it can be optimally used when multiple clients are working on our api program.
     taskPtr->create("Fazul","Tele : 8606885746",4);
    // Reading returns the string of the json structure of key-value pair. (constraints are maintained).
    cout<<taskPtr->read("variable")<<endl;
    
    std::thread th1(&fazul::create, taskPtr, "fazul","message : Hi iam a bTech graduate",7); // Creating using thread.
    Sleep(10000);
    std::thread th2(&fazul::create, taskPtr, "gif","dhbcsdhb",0);
    Sleep(10000); // here we make this program to go sleep for few secs so that to check whether the time to live property works or not.
    std::thread th3(&fazul::_delete, taskPtr, "gif"); // deleting a key-value pair using thread.
    th3.join();
    th1.join();
    th2.join();
    
    Sleep(10000); // here we make this program to go sleep for few secs so that to check whether the time to live property works or not.
    
    taskPtr->create("Office","System scaling : horizontal; Process scaling : vertical",7);
    cout<<taskPtr->read("fazul")<<endl;
    
    taskPtr->_delete("gif");
    
    taskPtr->create("havingmorethan32charactersinthekey","key : It will be invalid");//Here this is implemented to check the 32 char key length constraints.
    

    cout<<taskPtr->read("myObj")<<endl;
    delete taskPtr;// the heap allocation of the instance of the data store fazul is deleted.
    return 0;
}