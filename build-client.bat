@echo off

mkdir build
pushd build
cmake -G"Visual Studio 16" -DCLIENT_MODULE=1 -A x64 ..
cmake --build . --config Release
popd

IF NOT EXIST dist\ (
    mkdir dist
)
IF NOT EXIST dist\client\ (
    mkdir dist\client
)
copy build\win64\client\Release\config-module.dll dist\client
copy build\win64\client\Release\config-module.pdb dist\client