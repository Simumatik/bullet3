premake4.exe --no-bullet3 --no-demos --no-extras --no-test --file=premake4_no_suffix.lua vs2010

SETLOCAL
REM SET MSBUILD_EXEC="C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\MSBuild\Current\Bin\MSBuild.exe"
SET MSBUILD_EXEC"C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\MSBuild\15.0\Bin\MSBuild.exe" 
cd vs2010 
%MSBUILD_EXEC% /p:PlatformToolset=v140 /p:Configuration=Release /p:Platform=x64 /t:clean 0_Bullet3Solution.sln
%MSBUILD_EXEC% /p:PlatformToolset=v140 /p:Configuration=Release /p:Platform=x64 0_Bullet3Solution.sln
cd ..

ENDLOCAL