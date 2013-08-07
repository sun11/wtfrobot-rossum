FILE(REMOVE_RECURSE
  "../srv_gen"
  "../src/playground/srv"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_py"
  "../src/playground/srv/__init__.py"
  "../src/playground/srv/_SetDriveControlGains.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
