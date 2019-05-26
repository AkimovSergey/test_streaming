@echo off

setlocal ENABLEEXTENSIONS
set WORKSPACE_DIR=%~dp0\workspace

echo Workspace directory is "%WORKSPACE_DIR%"

if NOT EXIST "%WORKSPACE_DIR%" (mkdir "%WORKSPACE_DIR%" || echo Can not create workspace directory && exit /b 1)
pushd "%WORKSPACE_DIR%" || echo Can not change dir to workspace directory && exit /b 1

cmake  ..  || echo Configuration failed && goto :error
cmake --build . --use-stderr --config RelWithDebInfo || echo Build failed && goto :error


echo EVERYTHING OK

popd
goto :EOF

:error
popd
exit /b 1
