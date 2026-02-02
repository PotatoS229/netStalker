cd ../
mkdir build && cd build

# 3. Конфигурация с CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Или с дополнительными опциями:
cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_TESTS=OFF \
  -DBUILD_WEB_GUI=ON \
  -DENABLE_DEBUG=OFF

# 4. Сборка проекта
make -j$(nproc)  # Linux/macOS