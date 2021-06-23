:: Script to build app, copy dependencies and build installer
mingw32-make
cd .\release
windeployqt .\QuickKey.exe --no-translations --no-opengl-sw --release
cd ..\installer
candle setup.wxs Custom_ExitDialog.wxs Custom_InstallDir.wxs Custom_InstallDirDialog.wxs
light -out setup.msi setup.wixobj Custom_ExitDialog.wixobj Custom_InstallDir.wixobj Custom_InstallDirDialog.wixobj -ext WixUIExtension -ext WixUtilExtension