@echo off

SET visualstudio=vs2019
SET project=TappyPlane2D
SET script=GameEngine\Script\GenerateProjectFiles.bat

%script% %visualstudio% %project%