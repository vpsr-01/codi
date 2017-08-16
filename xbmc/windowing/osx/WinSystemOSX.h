#pragma once

/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#if defined(TARGET_DARWIN_OSX)

#include "windowing/WinSystem.h"
#include "threads/CriticalSection.h"
#include "threads/Timer.h"

typedef struct _CGLContextObject *CGLContextObj;
class IDispResource;

class CWinSystemOSX : public CWinSystemBase, public ITimerCallback
{
public:

  CWinSystemOSX();
  virtual ~CWinSystemOSX();

  // ITimerCallback interface
  virtual void OnTimeout() override;

  // CWinSystemBase
  virtual bool InitWindowSystem() override;
  virtual bool DestroyWindowSystem() override;
  virtual bool CreateNewWindow(const std::string& name, bool fullScreen, RESOLUTION_INFO& res) override;
  virtual bool DestroyWindow() override;
  bool         DestroyWindowInternal();
  virtual bool ResizeWindow(int newWidth, int newHeight, int newLeft, int newTop) override;
  bool         ResizeWindowInternal(int newWidth, int newHeight, int newLeft, int newTop, void *additional);
  virtual bool SetFullScreen(bool fullScreen, RESOLUTION_INFO& res, bool blankOtherDisplays) override;
  virtual void UpdateResolutions() override;
  virtual void NotifyAppFocusChange(bool bGaining) override;
  virtual void ShowOSMouse(bool show) override;
  virtual bool Minimize() override;
  virtual bool Restore() override;
  virtual bool Hide() override;
  virtual bool Show(bool raise = true) override;
  virtual void OnMove(int x, int y) override;

  virtual void EnableTextInput(bool bEnable) override;
  virtual bool IsTextInputEnabled() override;

  virtual void Register(IDispResource *resource);
  virtual void Unregister(IDispResource *resource);
  
  virtual int GetNumScreens() override;
  virtual int GetCurrentScreen() override;
  
  void        WindowChangedScreen();

  void        AnnounceOnLostDevice();
  void        AnnounceOnResetDevice();
  void        HandleOnResetDevice();
  void        StartLostDeviceTimer();
  void        StopLostDeviceTimer();

  
  void         SetMovedToOtherScreen(bool moved) { m_movedToOtherScreen = moved; }
  int          CheckDisplayChanging(uint32_t flags);
  void         SetFullscreenWillToggle(bool toggle){ m_fullscreenWillToggle = toggle; }
  bool         GetFullscreenWillToggle(){ return m_fullscreenWillToggle; }
  
  CGLContextObj  GetCGLContextObj();

  virtual std::string  GetClipboardText(void) override;
  float        CocoaToNativeFlip(float y);

protected:
  void  HandlePossibleRefreshrateChange();
  void* CreateWindowedContext(void* shareCtx);
  void* CreateFullScreenContext(int screen_index, void* shareCtx);
  void  GetScreenResolution(int* w, int* h, double* fps, int screenIdx);
  void  EnableVSync(bool enable); 
  bool  SwitchToVideoMode(int width, int height, double refreshrate, int screenIdx);
  void  FillInVideoModes();
  bool  FlushBuffer(void);
  bool  IsObscured(void);
  void  StartTextInput();
  void  StopTextInput();

  void                        *m_appWindow;
  void                        *m_glView;
  static void                 *m_lastOwnedContext;
  bool                         m_obscured;
  unsigned int                 m_obscured_timecheck;
  std::string                  m_name;

  bool                         m_use_system_screensaver;
  bool                         m_movedToOtherScreen;
  bool                         m_fullscreenWillToggle;
  int                          m_lastDisplayNr;
  int                          m_lastWidth;
  int                          m_lastHeight;
  int                          m_lastX;
  int                          m_lastY;
  double                       m_refreshRate;

  CCriticalSection             m_resourceSection;
  std::vector<IDispResource*>  m_resources;
  CTimer                       m_lostDeviceTimer;
  bool                         m_delayDispReset;
  XbmcThreads::EndTime         m_dispResetTimer;
  CCriticalSection             m_critSection;
};

#endif
