# File_based_key-value_data-store

Project to create a file based key-value data store having a local storage for a single process.

We are creating a container for our key-value data store. Unordered map gives us a unordered key value pair storing system (Reducing our time complexity of sorting in map)

CREATE FUNCTION:

create member function is defined with parameters key, value and time stamp.

Key contains the key of the data store which does not exceeds more than 32 chars length.

value contains the value of the data store which contains the Json objects. here Json object is considered as string for storing purpose.

timestamp parameter is used to denote the time to live property. It is an optional one not mandatory paramter which automatically assigns 0 if not mentioned . It intakes the No of seconds the key value pair can live from the time of its creation.

READ FUNCTION:

Read member function has a single parameter key . It fetches the Key value pair as a json object ex: {key : value}.

DELETE FUNCTION:

delete member function is defined with single parameter key. It deletes the key-value entry in our temporary(DataBase) storage and permanent(File) storage.

All the given Functional and Non-functional requirements are satisfied.
