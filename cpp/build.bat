@ECHO OFF
SET done=0;

cd shaders-def
node build-shaders.js
cd ..

IF "%1"=="--context" (
    IF "%2"=="emcc" (
        ECHO Performing emcc build...
        SET done=1
        emcc src/coreApp/gl-utils.cpp src/coreApp/Transform.cpp src/coreApp/ObjModel.cpp src/coreApp/Cube.cpp src/coreApp/Scene.cpp src/coreApp/api.cpp ^
            -I./src/include/ -O3 -s FULL_ES3=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s EXPORTED_FUNCTIONS=["_initGLAPI","_drawAPI"] -s EXTRA_EXPORTED_RUNTIME_METHODS=["cwrap","setValue"] ^
            -o ../js/wasm_build.js
        SHIFT
    )
    IF "%2"=="emccdebug" (
        ECHO Performing emcc DEBUG build...
        SET done=1
        emcc  src/coreApp/gl-utils.cpp src/coreApp/Transform.cpp src/coreApp/ObjModel.cpp src/coreApp/Cube.cpp src/coreApp/Scene.cpp src/coreApp/api.cpp ^
            -I./src/include/ -O1 -s FULL_ES3=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s EXPORTED_FUNCTIONS=["_initGLAPI","_drawAPI"] -s EXTRA_EXPORTED_RUNTIME_METHODS=["cwrap","setValue"] -g4 --source-map-base http://localhost:8000/cpp/ ^
            -o ./wasm_build.js
        SHIFT
    )
    IF "%2"=="g++" (
        ECHO Performing g++ standalone native build...
        SET done=1
        g++ src/coreApp/gl-utils.cpp src/coreApp/Transform.cpp src/coreApp/ObjModel.cpp src/coreApp/Cube.cpp src/coreApp/Scene.cpp src/coreApp/api.cpp ^
            src/glutApp/glutApp.cpp ^
            -I./src/include/ -Wall -lopengl32 -lglew32 -lfreeglut -lglu32 ^
            -o ./native.exe
        SHIFT
    )   
    SHIFT
)
IF done==0 (
   ECHO "Usage: build.bat --context=[emcc|emcc-debug|g++]"
)
