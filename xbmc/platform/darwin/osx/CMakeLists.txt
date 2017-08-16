set(SOURCES CocoaInterface.mm
            OSXGLView.mm
            OSXGLWindow.mm
            OSXTextInputResponder.mm
            smc.c
            XBMCHelper.cpp)

set(HEADERS CocoaInterface.h
            OSXGLView.h
            OSXGLWindow.h
            OSXTextInputResponder.h
            smc.h
            XBMCHelper.h)

core_add_library(platform_osx)
