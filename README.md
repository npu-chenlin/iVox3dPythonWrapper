# IVoxPythonWrapper

This repository contains the source code for the Python wrapper of the IVox, which is a library for the [faster-lio](https://github.com/gaoxiang12/faster-lio)

## 1. Dependencies
```bash
sudo apt-get install libeigen3-dev
sudo apt-get install libpcl-dev
```
If you are using Windows, you can install Eigen and PCL library by [vcpkg](https://github.com/microsoft/vcpkg/).
```bash
vcpkg install x64-windows:pcl
```
For svar dependency and usage, please refer to [svar](https://github.com/zdzhaoyong/Svar) for more details.

## 2.Build
### 2.1 WINDOWS
```bash
mkdir build & cd build
cmake.exe --no-warn-unused-cli -G "Visual Studio 17 2022" -T host=x64 -A x64 -DCMAKE_BUILD_TYPE=Release  -DCMAKE_TOOLCHAIN_FILE=PATH/TO/vcpkg.cmake  ..
make
```
## 2.2 Linux
```bash
mkdir build & cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## 3. Usage
```python
import numpy as np
import svar
ivox3d = svar.load("ivox3d")
# resolution, inv_resolution, NearbyType, capacity
options = ivox3d.IVoxOption(0.2, 10.0, 1, 5e6)
# init a ivox
ivox = ivox3d.IVox(options)

XYZ = np.random.rand(300000*3)
# add points
ivox.AddPoints(XYZ.tolist())
# query nearest point
ret = ivox.GetClosestPoint([1.0, 0.0, 0.0])
print(ret)
# query nearest N point with max distance
ret = ivox.GetClosestPoints([1.0, 0.0, 0.0], 5, 0.5 )
print(ret)
```