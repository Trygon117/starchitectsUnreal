# starchitectsUnreal

This is the Unreal Engine side of the Starchitect project. Here there is a Universe full of stars that can be added, and controlled through a websocket connection with a web server.  

# Open VSCode Workspace
open the "Starchitect.code-workspace" file to open the workspace in vscode  

# Open Unreal Engine Workspace
open the "Starchitect.uproject" file  

# Set Up The Enviroment

Here is an online Guide that you can refer to: 
https://docs.unrealengine.com/5.0/en-US/setting-up-visual-studio-code-for-unreal-engine/#installingthecompilertoolset  

Get the "C/C++ extension pack" and "C#" extensions for vscode.

Get the compiler toolset for windows Scroll down to "Tools for Visual Studio" and select "Build Tools for Visual Studio 2022": https://visualstudio.microsoft.com/downloads/  
Then when you run the installer select "Desktop development with C++" and ".NET Desktop Build Tools" and hit install  

Make sure you have Unreal Engine(5.3.2) installed

If you need to set VS Code as your default IDE (optional), open Unreal Editor and go to 
	Edit > Editor Preferences > General > Source Code  
	then set your Source Code Editor to Visual Studio Code.   
	Restart the editor for the change to take effect.  

To set up IntelliSense
	Navigate to ".vscode/c_cpp_properties.json"  
	add "includePath": [ "${workspaceFolder}\\Intermediate\\**", "[Workspace Folder]\\Plugins\\**", "[Workspace Folder]\\Source\\**" ], to the "StarchitectsEditor Editor Win64 Development (Starchitects)" object  
	Go the the C/C++ Extension settings and change C_Cpp: IntelliSense Engine Fallback to Enabled  
