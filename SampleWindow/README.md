# Sample Window System

This sample project demonstrates the implementation of a window management system for a game engine through the use of a layered design pattern where an interface abstracts the implementation details, which are contained inside classes whose purpose is to handle the window management. This is done first by ourselves (to demonstrate how it works behind the scenes), then through the use of the following APIs:

- SFML
- GLFW
- SDL

Besides the implementation details, I demonstrate a tried-and-true (at least for me!) design pattern that I have used in my own game engine.

<img src ="/SampleWindow/Documentation/Header.png">

----
**Notes**

1.	This sample at the moment is missing quite a bit of documentation, so let me know if you got any questions on how it works. However, it is very easy to find resources on how to do window management on the internet. My main purpose was to demonstrate it in the terms of a game engine's framework. In the future, given demand, I may demonstrate how to go fullscreen, among other things.
2.	I have been told that I shouldn't play favorites regarding what API to use when demonstrating them, so I [won't](http://www.sfml-dev.org/) .

