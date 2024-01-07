SET SCRIPT_DIR=%~dp0
echo %SCRIPT_DIR%
cd %SCRIPT_DIR%

mkdir build
cd build
"C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake" ..
"C:\Program Files\Microsoft Visual Studio\2022\Community\Msbuild\Current\Bin\msbuild.exe" DeviceService.sln