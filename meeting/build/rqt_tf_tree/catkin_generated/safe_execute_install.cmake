execute_process(COMMAND "/home/ubuntu/CapstoneB/meeting/build/rqt_tf_tree/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/ubuntu/CapstoneB/meeting/build/rqt_tf_tree/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
