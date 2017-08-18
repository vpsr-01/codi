set(SOURCES CocoaInterface.mm
            OSXGLView.mm
            OSXGLWindow.mm
            OSXScreenManager.mm
            OSXTextInputResponder.mm
            smc.c
            XBMCHelper.cpp)

set(HEADERS CocoaInterface.h
            OSXGLView.h
            OSXGLWindow.h
            OSXScreenManager.h
            OSXTextInputResponder.h
            smc.h
            XBMCHelper.h)

core_add_library(platform_osx)
