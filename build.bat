@echo on

mkdir build
pushd build
cmake -G"Visual Studio 16" -A x64 ..
cmake --build . --config Release
popd

mkdir dist
copy build\win64\Release\altv-client-config.dll dist
REM copy build\win64\Release\altv-client-config.pdb dist