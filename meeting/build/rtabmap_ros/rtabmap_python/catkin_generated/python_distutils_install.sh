#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/bao/CapstoneB/meeting/src/rtabmap_ros/rtabmap_python"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/bao/CapstoneB/meeting/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/bao/CapstoneB/meeting/install/lib/python3/dist-packages:/home/bao/CapstoneB/meeting/build/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/bao/CapstoneB/meeting/build" \
    "/usr/bin/python3" \
    "/home/bao/CapstoneB/meeting/src/rtabmap_ros/rtabmap_python/setup.py" \
    egg_info --egg-base /home/bao/CapstoneB/meeting/build/rtabmap_ros/rtabmap_python \
    build --build-base "/home/bao/CapstoneB/meeting/build/rtabmap_ros/rtabmap_python" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/bao/CapstoneB/meeting/install" --install-scripts="/home/bao/CapstoneB/meeting/install/bin"
