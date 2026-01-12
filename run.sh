echo "==================================="
echo "   Pong (Linux)"
echo "==================================="

if [ ! -d "build" ]; then
    mkdir build
fi

cd build

cmake .. -DCMAKE_BUILD_TYPE=Release

if [ $? -ne 0 ]; then
    echo
    echo "Cmake config error"
    exit 1
fi

cmake --build . --config Release

if [ $? -ne 0 ]; then
    echo
    echo "Error build failed"
    exit 1
fi

echo
echo "Build Done"

if [ -d "../resources" ]; then
    echo "Copying resourses to game folder..."
    mkdir -p Pong_resources 
    cp -r ../resources/* Pong_resources/ 2>/dev/null || true
fi

echo "Running game..."

./Pong
