git clone https://github.com/google/googletest.git

cd googletest

cmake -B build 

cmake --build build --target install #на этом этапе происходит ошибка

cd ..

cmake -B build -DGTEST_ROOT=/Users/GTest_temp

cmake --build build

# Windows:
cmake -B build -DCMAKE_INSTALL_PREFIX=/Users/GTest_temp -Dgtest_force_shared_crt=ON