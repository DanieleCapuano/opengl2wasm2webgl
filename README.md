# OpenGL2Wasm2WebGL
A simple system whose aim is to let you work on a native GLUT + OpenGL C++ app which can be compiled either natively (tested on Windows only) or with [Emscripten](https://emscripten.org/) (.wasm), so that it can be accessed and executed via a web app (tested on Chrome only). The current environment provides:
* the web app (Webpack-based);
* the C++ app;
* a Node.js web server to get the static files from the web


## Prerequisites [Tested on a Windows 10 machine]
* Node.js (tested on version 12.16.1 - [INSTALL](https://nodejs.org/download/release/v12.16.1/))
* Emscripten environment ([INSTALL](https://emscripten.org/docs/getting_started/downloads.html))
* GCC compilation environment for C++ (this has been tested on Windows using MinGW-64 under MSYS-2 - [INSTALL](https://www.msys2.org/wiki/MSYS2-installation/)). 

The final MSYS installation must must include at least the following packages:
  * free-glut
  * GLEW
  * GLM

## Build [C++ to Wasm-based Web App]
    cd cpp
    .\build.bat --context=emcc
    cd ..
    npm i
    npm run build [or npm run build-dev for contiuous watching changes]
    npm run start

The webapp will respond on http://localhost:8000

## Build [C++ to Wasm-based Web App with DEBUG CAPABILITIES]
    cd cpp
    .\build.bat --context=emccdebug
    cd ..
    npm i
    npm run build [or npm run build-dev for contiuous watching changes]
    npm run start

The webapp will respond on http://localhost:8000

## Build [Native App]
    cd cpp
    .\build.bat --context=g++
    .\native.exe

## WARNING: COMMENTS management in GLSL files
There's a node.js - based script which reads the .glsl files in cpp/shaders-def/src and exposes them as single-line strings within the "shaders-def.h" header file. Due to the implementation of such script, please **avoid using inline comments, your shaders will break!**. For example

    #version 300 es
    precision mediump float;

    //fine-working comment
    uniform float myunif;       //THIS COMMENT WILL BREAK YOUR SHADER
    uniform vec3 myotherunif;   /* This will work fine */

    void main() {
        /* ... */
    }