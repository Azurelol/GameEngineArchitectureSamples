# Sample Audio Pipeline

This sample project demonstrates a simple Audio pipeline as well as Audio API integration for an Audio system for an ECSS game engine, using an instancing pattern for generic sound objects called "SoundInstances".
Whenever a sound is requested to be played an unique object is created using the original SoundCue as a blueprint, and the new instance itself is controlled through provided methods.

At the moment this sample has integrations for:

- FMOD Low Level
- FMOD Studio

(If there's demand, in the future I may also integrate Wwise.)

<img src ="/SampleAudioSystem/Documentation/Header.png">

----
###Documentation - [Web](https://docs.google.com/document/d/1rITj9iOmGxvMOTLG72y53AwxwA3NrRB0h41DWONUGIQ/edit?usp=sharing) <br />