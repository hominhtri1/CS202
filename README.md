# CS202

A C++ console game where the objective is to control a character to cross the road without touching the obstacles. When the character reaches the other side of the road, the level increases.

Features include:
  * There are many types of obstacles, such as cars and dinosaurs, each with their own graphic and sound.
  * The obstacles are randomly generated and increase in number as the level goes higher.
  * Users can not just save the level number but also the status of the level.
  * Users can configure the settings of the game, such as turning the sound on/off.

**Note**: To use Window's sound library on Visual Studio:
  1. Right click on project, go to Properties
  2. Go to Linker -> Input
  3. Click on Additional Dependencies -> <Edit...>
  4. Type winmm.lib. Click OK
