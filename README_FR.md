<h1 align="center">NodeJS & C++ avec Node-Addon-Api</h1>

[Node-Addon-Api](https://github.com/nodejs/node-addon-api/) - [NodeJS](https://nodejs.org/) - [node-gyp](https://github.com/nodejs/node-gyp)

<div align="center">
  <a href="https://github.com/WaRtrO89/nodejs-and-cpp/blob/main/README.md">
    <img src="https://user-images.githubusercontent.com/25512932/160092140-bee4eee1-e755-48b7-b220-1d94adf14e16.png" alt="en">
  </a>
  <a href="https://github.com/WaRtrO89/nodejs-and-cpp/blob/main/README_FR.md">
    <img src="https://user-images.githubusercontent.com/25512932/160092152-0ab75363-b38b-4a91-a745-e2aeb6741b4e.png" alt="fr">
  </a>
</div>

# À propos

Voici un petit tuto pour utiliser du C++ avec NodeJs!

Je vais, vous montrez comment créer un petit addon C++, avec `Napi` qui permet le lier à NodeJs.

Nous utiliserons `node-gyp`pour compiler le tout.

# Installation sur Windows

1) Installer [Visual Studio Tools](https://visualstudio.microsoft.com/downloads/)
    - Sélectionner `Desktop Environment C++` et cliquer sur installer

2) Installer [Python3.10](https://www.python.org/downloads/release/python-3100/)

3) Exécuter le Power sheel de windows en administrateur.
  
  (Je suppose que vous avez déjà installé NodeJs et npm, sinon faites le!)
  
  Entrer les commandes suivantes:
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
# Créer votre premier Projet
 
 1) Aller ou créer un dossier contenant votre projet
  
  Dans le terminal entrer :
  ```
  npm init
  ```
  Je vous laisse compléter ce qu'il vous demande.

  Puis entrer
  ```
  npm install -S node-addon-api
  ```
  2) Créer un dossier à la racine de votre projet qui contiendra votre nouveau Module
      - Créer ``name_module.cpp``  Il contient votre script exporter sur nodeJs
      - Créer ``name_module.h``  C'est un fichier contenant toutes les déclarations de votre script (fonction, constante...)
      - Créer ``index.cpp``  Ce fichier va permettre de link votre script à NodeJS avec Napi

  3) Créer un fichier à la racine ``binding.gyp``
  
Écrire à l'intérieur :

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
- **target_name** : est le nom du ``.node`` qui sera compilé à la fin
- **sources** : est l'emplacement des fichiers c++ que nous allons compiler
- **include_dirs** :le script va récupérer ``node-addon-api`` pour correctement compiler avec Napi
- **Others** : est des paramètres obligatoires pour que le script fonctionne correctement

  4) Créer votre premier module C++

Bien évidemment nous allons créer la classique fonction Hello World !

Je vous conseille de renommer les fichiers comme ceci, pour plus facilement suivre :

``name_module.cpp`` -> ``hello.cpp``

``name_module.h`` -> ``hello.h``

Dossier : ``helloWorld``


Dans le ``binding.gyp``, écrire:

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

Dans ``hello.cpp`` écrit :
```cpp
#include <string>
#include "hello.h"

std::string helloWorld() {
  return "Hello World !!!";
}
```

Dans ``hello.h`` écrit :
```h
#include <string>

std::string helloWorld();
}
```

Dans ``index.cpp`` écrit :
```cpp
#include <napi.h>
#include <string>
#include "hello.h" //Récupère le header, les déclarations de votre script

Napi::String helloWorldFonc(const Napi::CallbackInfo& info) { //Créer une nouvelle fonction qui récupère les arguments avec le callBack
    Napi::Env env = info.Env();
    std::string result = helloWorld(); //Votre fonction -> hello.cpp
    return Napi::String::New(env, result);
}
Napi::Object Init(Napi::Env env, Napi::Object exports) { //Object pour exporte votre script sur nodeJs
    exports.Set(
        Napi::String::New(env, "helloWorld"), // le nom de la fonction que nous utiliserons sur nodejs (const hello = require('./helloModule.node').helloWorld();
        Napi::Function::New(env, helloWorldFonc) //la fonction qui récupère les arguments et qui retourne le résultat de votre fonction c++
    );
    return exports;
}
NODE_API_MODULE(helloModule, Init) //helloModule == Nom du fichier final helloModule.node (le même présent dans target sur "binding.gyp") et Init == exports
```
Le script est terminé ! Manque plus qu'à le compiler...
Tout sera compilé dans un fichier ``.node``

Sur le terminal, écrire :

``
node-gyp configure
``
puis
``
node-gyp build
``

Puis récupérer le fichier ``.node`` dans `/Build/Release/helloModule.node` et glisser le à la racine de votre projet

Puis utilise le dans ton fichier ``index.js`` !!!

```js
const monAddon = require('./helloModule.node');
console.log(monAddon.helloWorld());
```
Lance le fichier et admire le travaille ! 😎

# Rajouter des arguments sur la fonction

Dans ``hello.cpp`` écrit :
```cpp
#include <string>
#include "hello.h"

std::string helloWorld( std::string Argument ) {
  return "Hello" + Argument + " !!!";
}
```
Dans ``hello.h`` écrit :
```h
#include <string>

std::string helloWorld( std::string Argument );
}
```
Dans ``index.cpp`` écrit :
```cpp
#include <napi.h>
#include <string>
#include "hello.h"

Napi::String helloWorldFonc(const Napi::CallbackInfo& info) { // les arguments sont ici
    Napi::Env env = info.Env();
    std::string Argument = (std::string) info[0].ToString(); // nouvelle ligne qui récupère le premier argument
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
N'oublie pas de supprimer le dossier``Build``et reconstruire avec le ``node-gyp``

Dans ``index.js`` écrit :
```js
const monAddon = require('./helloModule.node');
console.log(monAddon.helloWorld('tout le monde'));
```
Et voilà, c'est magique.

J'espère vous avoir aidé...

Et n'hésite pas de regarder les autres scripts très basiques présents dans le git 🧐

# Contact

Discord : WaRtrO#6293
