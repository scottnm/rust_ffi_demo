# TODO: build as static lib
# TODO: build as dll
# TODO: build test exe and link in lib
# TODO: build test exe and link in dll
# TODO: C11 support - build with clang

Param(
    [switch] $Direct,
    [switch] $Static
    )

function ExitIfErr
{
    if (!$?)
    {
        Write-Host -ForegroundColor Red "Build Failed"
        exit
    }
}

# Default to build all if nothing is specified
$All = (!$Direct -and !$Static);

$SrcDir = "$PSScriptRoot\..\src\"
$TargetDir = "$PSScriptRoot\..\target\"

# Direct build
if ($Direct -or $All)
{
    Write-Warning "DIRECT: compile all"
    cl /TC $SrcDir\demo_lib_test.c $SrcDir\demo_lib.c /Fo:$TargetDir /Fe:$TargetDir\demo_lib_test_direct.exe
    ExitIfErr;
}

# Static build
if ($Static -or $All)
{
    Write-Warning "STATIC: compile libobj"
    cl /TC $SrcDir\demo_lib.c /c /Fo:$TargetDir\demo_lib_static_lib.obj
    ExitIfErr;

    Write-Warning "STATIC: link libobj to lib"
    lib $TargetDir\demo_lib_static_lib.obj /OUT:$TargetDir\demo_lib_static.lib
    ExitIfErr;

    Write-Warning "STATIC: compile test exe"
    cl /TC $SrcDir\demo_lib_test.c /Fo:$TargetDir /Fe:$TargetDir\demo_lib_test_static.exe /link $TargetDir\demo_lib_static.lib
    ExitIfErr;
}
