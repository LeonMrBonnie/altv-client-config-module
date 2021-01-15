mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DSERVER_MODULE=1 ..
cmake --build . --config Release
cd ..

if [ ! -d "./dist" ]; then
    mkdir dist
fi
if [ ! -d "./dist/server" ]; then
    mkdir dist/server
fi

cp build\linux64\server\Release\config-module.so dist\server
#cp build\linux64\server\Release\config-module.pdb dist\server
