#!/bin/bash
install_name_tool -change /usr/local/lib/libSDL2-2.0.0.dylib @executable_path/SDL2.framework/Versions/A/SDL2 dontrunme 
install_name_tool -change /usr/local/lib/libSDL2_image-2.0.0.dylib @executable_path/SDL2_image.framework/Versions/A/SDL2_image dontrunme 
install_name_tool -change /usr/local/lib/libSDL2_mixer-2.0.0.dylib @executable_path/SDL2_mixer.framework/Versions/A/SDL2_mixer dontrunme 
install_name_tool -change /usr/local/lib/libSDL2_net-2.0.0.dylib @executable_path/SDL2_net.framework/Versions/A/SDL2_net dontrunme 
