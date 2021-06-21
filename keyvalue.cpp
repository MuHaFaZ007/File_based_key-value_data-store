// Project to create a file based kye-value data store having a local storage for a single process

// This file which containes the dtat store and the supporting functions can be included in any other programs as api or as a library file

#include<iostream>
#include<fstream>
#include<ctime>
#include<unordered_map>
#include<algorithm>
#include<cctype>
#include<windows.h>
#include<thread>
#include<string>

using namespace std;

// Creating a class name fazul which acts as a container for our data store type
class fazul
{
    // We are creating a container for our key-value data store. Unordered map gives us a unordered key value pair storing system (Reducing our time complexity of sorting in map)
    unordered_map <string,string> DataBase;
    public:

    // create member function is defined here with parameters key, value and time stamp.
    
    // Key contains the key of the data store which does not exceeds more than 32 chars length.
    
    // value contains the value of the data store which contains the Json objects. here Json object is considered as string for storing purpose.

    // timestamp parameter is used to denote the time to live property. It is an optional one not mandatory paramter which automatically assigns 0 if not mentioned . It intakes the No of seconds the key value pair can live from the time of its creation. 

    void create(string key,string value,long long timestamp=0)
    {
        if(DataBase.find(key)!=DataBase.end())  // Checks whether the given key is already exits or not . If so then it cannot be created so it throws an error message. 
            cerr<<"This key "<<key<<" is already exist\n";
        else   
        {
            if(key.length()<=32) // Checks whether the given key string has less than or equal to 32 characters. if exceeds then it throws an erro message.
            {
               if(DataBase.size()<=(1024*1024*1024) && value.length()<=(16*1024)) // Checks whether the whole size of the data store for a single process exceeds more than 1 gb or The size of the json object (value) exceeds more than 16kb ,if so then throws error message.
                {
                    if(timestamp!=0) // checks whether the given time to live property is 0 or any value . If any value is given then it is added to the system time(the no of seconds from the epoch) , for detecting the expiry time of the key value pair.
                       timestamp += time(NULL);
                    // File is created with the name of the key given .This is an optional part here we store in file for a permanent storage system.
                    // Reason for creating files for each key : It reduces the space complexity . for example of the whole data is stored in a single file then we will be having a specific space allocated for each type ex: 32 bytes for key and 16kb for each value and a 8 bytes for time to live property .
                    
                    // Hence while using seperate file for different key it reduces the space complexity so that for each key value data store we will be allocating space for only existing contents no excess space is left for seeking purpose   
                    ofstream file(key); /// output file stream is called for storing the contents into the file.

                    file << value<<"\n";//Storing the value (Json object) into the file named as the respective key name. 
                    file << timestamp; // time stamp is also stored in that file.
                    file.close();
                    DataBase[key]=value; 
                    cout<<"Successfully Created :"<<key<<endl;
                }
                else
                    cerr<<"Memory limit is exceeding"<<endl;   
            }
            else
               cerr<<"Given key "<<key<<" value exceeds the limit 32"<<endl;
        }    
    }
    // Read member function has a single parameter key . It fetches the Key value pair as a json object ex: {key : value}.
    string read(string key)
    {
        if(DataBase.find(key)!=DataBase.end())// Here we search whether the key exist in our data store or not . if not then throws a error message .
        {
            string value;
            int timestamp;
            ifstream file(key);   // input file stream is called for reading the contents of the file names as the key name.
            getline(file,value);
            file>>timestamp;  // fetches the time to live parameter value.
         //   cout<<timestamp<<time(NULL)<<endl;
            if ( timestamp == 0 || time(NULL)<=timestamp)// checks whther the time to live value of the given key is expired or not if so then it throws and error message.If not then prints.
                return   "{ "+key+" : "+ value +" }" ;
            else
               return "Time to live property of the key : "+key+" has been expired";
        }
        else
            return "The key " +key +" does'nt exist in the database";
    }

    // _delete member function is defined with single parameter key. It deletes the key-value entry in our temporary(DataBase) storage and permanent(File) storage. 
    void _delete(string key)
    {
        if(DataBase.find(key)!=DataBase.end())//checks whether the given key exist or not . if not then throws and error.
        {
            string value;
            int timestamp;
            ifstream file(key);  // input file stream is called for reading the contents of the file names as the key name. 
            getline(file,value);
            file>>timestamp; // Fetches the time to live value of the given key pair 
           // cout<<timestamp <<" "<<time(NULL)<<endl;
            if (timestamp==0 || time(NULL) <= timestamp) // If the key pair value time to live property is expired then it cant be deleted hence throws an error.
            {
                // If the time to live property is not expired then . it is deleted from the data store temporary (DataBase) and permanent(file) storages.
                remove( key.c_str() );
                DataBase.erase(key);
                cout<<"Successfully removed :"<<key<<endl;
            }
            else
               cerr<<"Time to live property of the key :"<<key<<" has been expired"<<endl;
        }
        else
          cerr<<"The key "<<key<<" does'nt exist in the database"<<endl;
    }
};

// controlled memory efficiency in file by storing creating different file for different key.
// Optimized logics are implemented.


//This program can be used in several client programs by including this file name in their programs.