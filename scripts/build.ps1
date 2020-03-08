# TODO: build as static lib
# TODO: build as dll
# TODO: build test exe and link in lib
# TODO: build test exe and link in dll

$SrcDir = "$PSScriptRoot\..\src\"
$TargetDir = "$PSScriptRoot\..\target\"

cl /TC $SrcDir\demo_lib_test.c /Fo:$TargetDir\demo_lib_test.obj /Fe:$TargetDir\demo_lib_test.exe
