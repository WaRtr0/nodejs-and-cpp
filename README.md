[![Contributors][contributors-shield]][contributors-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

<h1 align="center">NodeJS & C++ with Node-Addon-Api</h1>

[Node-Addon-Api](https://github.com/nodejs/node-addon-api/) - [NodeJS](https://nodejs.org/) - [node-gyp](https://github.com/nodejs/node-gyp)

<div align="center">
  <a href="https://github.com/WaRtrO89/nodejs-and-cpp/blob/main/README.md">
    <img src="https://user-images.githubusercontent.com/25512932/160092140-bee4eee1-e755-48b7-b220-1d94adf14e16.png" alt="en">
  </a>
  <a href="https://github.com/WaRtrO89/nodejs-and-cpp/blob/main/README_FR.md">
    <img src="https://user-images.githubusercontent.com/25512932/160092152-0ab75363-b38b-4a91-a745-e2aeb6741b4e.png" alt="fr">
  </a>
</div>

# About

Here is a small tutorial to use c++ with NodeJs!

I'll show you how to create a small C++ addon, with `Napi` that allows binding.

We will use `node-gyp` to compile everything.

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
# Create your First project
 
 1) You can now go or create your folder that will contain your project
  
  On the terminal enter :
  ```
  npm init
  ```
  It's up to you to fill in with the right arguments...
  Then enter
  ```
  npm install -S node-addon-api
  ```
  2) Create a folder at the root of your project that will contain your C++ module
      - Create ``name_module.cpp``  It will contain your script that nodeJs will use
      - Create ``name_module.h``  It will contain the header / declaration of your functions and constant of your file ``name_module.cpp``
      - Create ``index.cpp``  It will contain the script to link between c++ and nodeJs

  3) Create a file ``binding.gyp`` at the root
  
Write inside

```py
{
  "targets": [
    {
      "target_name": "nameModule",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./folder_contain_module/name_module.cpp",
        "./folder_contain_module/index.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}
```
- **target_name** : is the ``.node`` name that will be returned when compiling
- **sources** : is the location of each ``.cpp`` file to compile
- **include_dirs** : the script will retrieve the ``node-addon-api`` content to compile correctly
- **Others** : mandatory files to have no problem

  4) Create your First C++ script

We of course we create a Hello World function

I advise you to rename your files like this, to understand better :

``name_module.cpp`` -> ``hello.cpp``

``name_module.h`` -> ``hello.h``

Folder : ``helloWorld``


In the ``binding.gyp``, write:

```py
{
  "targets": [
    {
      "target_name": "helloModule",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./helloWorld/hello.cpp",
        "./helloWorld/index.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}
```

In ``hello.cpp`` write :
```cpp
#include <string>
#include "hello.h"

std::string helloWorld() {
  return "Hello World !!!";
}
```

In ``hello.h`` write :
```h
#include <string>

std::string helloWorld();
}
```

In ``index.cpp`` write :
```cpp
#include <napi.h>
#include <string>
#include "hello.h" //get the header of your function

Napi::String helloWorldFonc(const Napi::CallbackInfo& info) { //create a new function who recovers the argument with Callback
    Napi::Env env = info.Env();
    std::string result = helloWorld(); //your function -> hello.cpp
    return Napi::String::New(env, result);
}
Napi::Object Init(Napi::Env env, Napi::Object exports) { //Object to export your script on nodeJs
    exports.Set(
        Napi::String::New(env, "helloWorld"), // function name for nodeJs (const hello = require('./helloModule.node').helloWorld();
        Napi::Function::New(env, helloWorldFonc) //the fonction create just before with callBack
    );
    return exports;
}
NODE_API_MODULE(helloModule, Init) //out name.node (the same as in "binding.gyp") and Init == exports
```
The script is finished, not very complicated...
All that's left is to compile it into ``.node``

On your terminal, write :

``
node-gyp configure
``
and
``
node-gyp build
``

Get the file generate ``.node`` in `/Build/Release/helloModule.node` and drag it to the root

Use it on your ``index.js`` file !!!

```js
const myAddon = require('./helloModule.node');
console.log(myAddon.helloWorld());
```
Launch your file then admire the work 😎

# Use arguments on this function

In ``hello.cpp`` write :
```cpp
#include <string>
#include "hello.h"

std::string helloWorld( std::string Argument ) {
  return "Hello" + Argument + " !!!";
}
```
In ``hello.h`` write :
```h
#include <string>

std::string helloWorld( std::string Argument );
}
```
In ``index.cpp`` write :
```cpp
#include <napi.h>
#include <string>
#include "hello.h"

Napi::String helloWorldFonc(const Napi::CallbackInfo& info) { // the arguments are stored here!!!
    Napi::Env env = info.Env();
    std::string Argument = (std::string) info[0].ToString(); // get the first argument
    std::string result = helloWorld(Argument);
    return Napi::String::New(env, result);
}
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
        Napi::String::New(env, "helloWorld"),
        Napi::Function::New(env, helloWorldFonc)
    );
    return exports;
}
NODE_API_MODULE(helloModule, Init)
```
Don't forget to delete the ``Build``folder and rebuild with ``node-gyp``

In ``index.js``
```js
const myAddon = require('./helloModule.node');
console.log(myAddon.helloWorld('everyone'));
```
And that's magic

Here I hope to have helped you...


Other basic scripts are available on git, do not hesitate to look at them 🧐
# Contact

Discord : WaRtrO#6293
