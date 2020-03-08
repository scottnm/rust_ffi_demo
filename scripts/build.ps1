# TODO: build as static lib
# TODO: build as dll
# TODO: build test exe and link in lib
# TODO: build test exe and link in dll
# TODO: C11 support - build with clang

$SrcDir = "$PSScriptRoot\..\src\"
$TargetDir = "$PSScriptRoot\..\target\"

cl /TC $SrcDir\demo_lib_test.c $SrcDir\demo_lib.c /Fo:$TargetDir /Fe:$TargetDir\demo_lib_test_direct.exe
