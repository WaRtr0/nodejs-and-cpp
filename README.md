<h1 align="center">NodeJS & C++ with Node-Addon-Api</h1>

[Node-Addon-Api](https://github.com/nodejs/node-addon-api/) - [NodeJS](https://nodejs.org/)

<div align="center">
  <a href="https://github.com/WaRtrO89/node-and-cpp/blob/main/README.md">
    <img src="https://user-images.githubusercontent.com/25512932/160092140-bee4eee1-e755-48b7-b220-1d94adf14e16.png" alt="en">
  </a>
  <a href="https://github.com/WaRtrO89/node-and-cpp/blob/main/README_FR.md">
    <img src="https://user-images.githubusercontent.com/25512932/160092152-0ab75363-b38b-4a91-a745-e2aeb6741b4e.png" alt="fr">
  </a>
</div>

# About

Here is a small tutorial to use c++ with NodeJs!

# Installation on Windows

1) Install [Visual Studio Tools](https://visualstudio.microsoft.com/downloads/)
  - Select Desktop Environment C++ and Click on install

2) Install [Python3.10](https://www.python.org/downloads/release/python-3100/)

3) Execute Windows Power Shell in Administrator
  
  (If you watch this tutorial I assume you have already installed NodeJS and Npm otherwise do it)
  
  Enter his commands :
  ```
    npm install -g node-gyp
  ```
  ```
    npm config set python python3.10
  ```
  ```
    npm config set msvs_version 2017
  ```
  ```
      Set-ExecutionPolicy Unrestricted -Force
  ```
4) Create your project
  You can now go or create your folder that will contain your project
  
  On the terminal enter :
  ```
  npm init
  ```
  It's up to you to fill in with the right arguments...
  Then enter
  ```
  npm install -S node-addon-api
  ```
5) Create a folder at the root of your project that will contain your C++ module
      - Create ``name_module.cpp`` It will contain your script that nodeJs will use
      - Create ``name_module.h`` It will contain the header / declaration of your functions and constant of your file 'name_module.cpp'
      - Create ``index.cpp`` It will contain the script to link between c++ and nodeJs


# Contact

Discord : WaRtrO#6293
