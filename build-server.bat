@echo off

mkdir build
pushd build
cmake -G"Visual Studio 16" -DSERVER_MODULE=1 -A x64 ..
cmake --build . --config Release
popd

IF NOT EXIST dist\ (
    mkdir dist
)
IF NOT EXIST dist\server\ (
    mkdir dist\server
)
copy build\win64\server\Release\altv-config-module.dll dist\server
copy build\win64\server\Release\altv-config-module.pdb dist\server