$build_dir = 'build'
if (!(Test-Path -Path $build_dir)) {
  New-Item -ItemType directory -Path $build_dir
}
cd $build_dir
cmake -G 'Visual Studio 11' $args ..
$sln_file = Get-Childitem -Name -Filter *.sln
devenv $sln_file  /build release
cd ..
