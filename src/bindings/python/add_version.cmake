message("Python: Add Version to generated file")

if(NOT EXISTS ${CUR_BIN_DIRECTORY}/libtsb.py)
  message(FATAL_ERROR "  The SWIG wrapper has not yet been created")
else()
  file(APPEND ${CUR_BIN_DIRECTORY}/libtsb.py "
global __version__
__version__ = '${VERSION}'
")
endif()
