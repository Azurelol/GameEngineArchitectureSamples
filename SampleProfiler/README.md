# Sample Profiler

This sample project demonstrates the implementation and use of a simple profiler system for your engine. 

<img src ="/SampleProfiler/Documentation/Header.png">

Performance is important. When developing a game engine with its myriad systems, there will be often times when a new system or feature is being implemented that the framerate will plummet. When one is most fortunate, the culprit code is easy to find. However, more often than not the cause of the bottleneck is hard to find, especially if you don’t have enough data to draw from to make an informed hypothesis.

----
### Documentation - [Web](http://azurecross.net/gam/2016/02/28/a-simple-profiler-system-for-your-engine/) <br />

I have documented the thought process behind the implementation of the Profiler system in this project which includes the following:

- A Profiler object which will receive all the aggregate data and store it in a logical manner for us to parse.
- A Timer object which will record the time elapsed inside a function call for us and report it back to the Profiler object.

----
### Examples

<img src ="/SampleProfiler/Documentation/Demo.png">
An example of the Profiler system being used in a student game engine (Mine!).