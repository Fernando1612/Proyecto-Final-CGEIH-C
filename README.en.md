[![es](https://img.shields.io/badge/lang-es-yellow.svg)](https://github.com/Fernando1612/Proyecto-Final-CGEIH-C/blob/316054416_ProyectoFinalTeo_GPO4/README.md)

<div align="center">
 
# User Manual 📖
 
## Final Project of Computer Graphics and Human-Computer Interaction 👨🏽‍💻

## Student:
 - Maceda Patricio Fernando🤵🏽
 - ID: 316054416
  
### Semester 2022-2 | Class ID 4
</div>

### Requirements

* To run with Visual Studio 2019 and C++ installation or with the .exe file:
    - Windows 7, Windows 8, Windows 10
    - Processor: 1.8 GHz (recommended 4 cores or more)
    - 2.5 GB RAM minimum, 8 GB recommended
    - 20 GB free on hard disk
    - Graphic chip of minimum 720p resolution

### Opening and execution

Download the project from GitHub by clicking the green button ("Code") and selecting one of the options
<div align="Center">
    <img src="img/Captura1.JPG" alt="Descarga GitHub 1" ></img>
<div align="justify">
 
If you select "Open with GitHub Desktop" you need to have this application installed on your computer and follow the steps to clone the repository locally, once
cloned skip to ["Run the .exe file"](#item1).

"Download ZIP" selection will download a .zip file of the project, unzip it on your computer and skip to ["Run the .exe file"](#item1).
  
 ### Execution with Visual Studio 💻
 
  If you wish and have the Visual Studio IDE installed, you can run the application by following the steps below.
  Have the project downloaded from git-hub and have unzipped the zip folder. Once you have this open Visual Studio and select the option "Open a project or a solution"
 
 <div align="Center">
  <img src="img/Captura3.jpg" alt="Abrir proyecto"></img>
<div align="justify">
 
Find the file "Proyecto_Final.sln" inside the folder and click on the "Open" button.
  
  <div align="Center">
  <img src="img/Captura4.jpg" alt="Abrir archivo sln"></img>
<div align="justify">
  
Before executing the program We check that all the libraries and configurations are loaded correctly. We go to the solution explorer, right click on the project name and select the properties option.
 
<div align="Center">
  <img src="img/Captura5.jpg" alt="Propiedades"></img>
<div align="justify">
 
In the "General" section we verify that the Platform Toolkit We have downloaded, it can be v142 or v143.
  
 <div align="Center">
  <img src="img/Captura6.jpg" alt="General"></img>
<div align="justify">

Inside C/C++ -> General check that the keyword **include** is in additional include directories. In Linker -> General check that the keyword **lib** is in Additional Library Directories and finally in Linker -> Input verify that dependencies  **Winmm.lib;SDL2.lib;SDL2main.lib;assimp-vc141-mtd.lib;opengl32.lib;glfw3.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)** are included in Additional Dependencies. 
 
 <div align="Center">
  <img src="img/Captura7.jpg" alt="Include"></img>
<div align="justify">
 
 <div align="Center">
  <img src="img/Captura8.jpg" alt="lib"></img>
<div align="justify">
 
 <div align="Center">
  <img src="img/Captura9.jpg" alt="Dependecias"></img>
<div align="justify">
  
To run the project, you must select the "x86" option in the upper bar and verify that the "Debug" option is selected, as in the following image:
 
 <div align="Center">
  <img src="img/Captura10.jpg" alt="X86"></img>
<div align="justify">
 
You can now run the project by clicking on the "Local Windows Debugger" button, this button opens the program window.
  
  <div align="Center">
  <img src="img/Captura11.jpg" alt="X86"></img>
<div align="justify">
 
 <a name="item1"></a>
 ### Run the .exe file 🚀
  
Once the project has been cloned or the ZIP has been unzipped: open the generated folder or repository location on your computer and go to ".\Proyecto_Final\Proyecto_Final", locate the file "Proyecto_Final.exe" and double-click to open. This will open a window with the virtual space running.
  
  
<div align="Center">
  <img src="img/Captura2.jpg" alt="Archivo executable"></img>
<div align="justify">
 
### Interaction with the environment ⛺️

With the window open; being inside the virtual space we can move the camera with the mouse. The interaction occurs through the keyboard and mouse of the computer.
  
<div align="Center">
<img src="img/Captura18.jpg" alt="Programa abierto, posición inicial"></img>
<div align="justify">
  
Model of the Church and its location⛪.
 <div align="Center">
<img src="img/Captura19.jpg" alt="Modelo de la iglesia y su ubicación"></img>
<div align="justify">
 Model of the Oxxo Store and its location 🏪.
 <div align="Center">
<img src="img/Captura20.jpg" alt="Modelo de la tienda Oxxo y su ubicación"></img>
<div align="justify">
 Location of the rooms on the map. Go to this building to be able to observe the furniture and animations 🏬. 
  <div align="Center">
<img src="img/Captura21.jpg" alt="ubicación de cuartos"></img>
<div align="justify">
 First room 🏠.
  <div align="Center">
<img src="img/Captura23.jpg" alt="cuarto 1"></img>
<div align="justify">
 Second room 🏠.
  <div align="Center">
<img src="img/Captura22.jpg" alt="cuarto 2"></img>
<div align="justify">
  
#### Functions
* Keyboard:
    * "Esc" : to exit the window / finish the program. ❌
    
    Simulation of forward ⬆️, backward ⬇️, left ⬅️, right ➡️ keys for movement as it happens in video games
    * "W" : move the camera forward ⬆️. 
    * "S" : move the camera backward ⬇️. 
    * "A" : move the camera to the left  ⬅️.
    * "D" : move the camera to the right ➡️.
    
    Music:
    * "Z" : Start the music :notes:.
 
    Animations:
 
    * "SPACE" : turn car animation on or off 🚗.
    <div align="Center">
      <img src="img/Captura12.jpg" alt="AnimacionCarro"></img>
    <div align="justify">
     
    * "1"     : activate the animation of the person walking 🚶‍♂️. 
     
    <div align="Center">
      <img src="img/Captura13.jpg" alt="AnimacionCamina"></img>
    <div align="justify">
     
    * The tricycle animation does not need user input 🚲.
     
    <div align="Center">
      <img src="img/Captura14.jpg" alt="AnimacionTriciclo"></img>
    <div align="justify">
     
    * The bicycle animation does not need user input 🚴‍♂️.
     
    <div align="Center">
      <img src="img/Captura15.jpg" alt="AnimacionBicicleta"></img>
    <div align="justify">
     
    * The animation of the person walking with the dog does not need user input 🚶‍♀️🐕.
     
    <div align="Center">
      <img src="img/Captura16.jpg" alt="AnimacionPasear"></img>
    <div align="justify">
     
    * The athlete animation does not require user input ⛹️‍♂️.
     
    <div align="Center">
      <img src="img/Captura17.jpg" alt="AnimacionDeportista"></img>
    <div align="justify">
          
    * The chair animation does not need user input. 🪑.
     
    <div align="Center">
      <img src="img/Captura24.jpg" alt="AnimacionSilla"></img>
    <div align="justify">
          
    * The refrigerator animation does not need user input. 🧊.
     
    <div align="Center">
      <img src="img/Captura25.jpg" alt="AnimacionRefri"></img>
    <div align="justify">
          
    * Fan animation does not need user input 💨. 
     
    <div align="Center">
      <img src="img/Captura26.jpg" alt="AnimacionVentilador"></img>
    <div align="justify">
    
* Mouse movements:
    * Mouse swipe 🔁 left or right, up or down rotates the camera 📷 in that swipe direction, the field of view 🔍 moves like a computer cursor.
    * Mouse scroll zoom + 🔍 moving it forward and zoom - 🔍 backward.
