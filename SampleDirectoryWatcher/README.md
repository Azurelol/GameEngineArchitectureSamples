# Sample Directory Watcher

This sample project demonstrates a simple implementation of a Directory Watcher, an object which when instantiated and pointed at a given directory will continuously scan it
for changes to the files in it. When it detects a change it will inform the client of it with both the type of the event and an object containing information about it.
For this sample I implemented a simple callback interface where you pass in the address to the a function that fulfillss the signature specified in the class and that function
will be considered "subscribed" and invoked whenever a valid change is detected.

For implementation purposes I used the currently experimental STL filesystem library (though I have used boost::filesystem in the past... which the filesystem library is based off!)

<img src ="/SampleDirectoryWatcher/Documentation/Header.png">