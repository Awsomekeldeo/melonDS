/*
    Copyright 2016-2023 melonDS team

    This file is part of melonDS.

    melonDS is free software: you can redistribute it and/or modify it under
    the terms of the GNU General Public License as published by the Free
    Software Foundation, either version 3 of the License, or (at your option)
    any later version.

    melonDS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with melonDS. If not, see http://www.gnu.org/licenses/.
*/

#ifndef MAIN_H
#define MAIN_H

#include "glad/glad.h"

#include <QApplication>
#include <QWidget>
#include <QWindow>
#include <QMainWindow>
#include <QImage>
#include <QActionGroup>
#include <QTimer>
#include <QScreen>
#include <QCloseEvent>

#include "Window.h"
#include "EmuThread.h"
#include "FrontendUtil.h"
<<<<<<< HEAD
=======
#include "duckstation/gl/context.h"

class EmuThread : public QThread
{
    Q_OBJECT
    void run() override;

public:
    explicit EmuThread(QObject* parent = nullptr);

    void changeWindowTitle(char* title);

    // to be called from the UI thread
    void emuRun();
    void emuPause();
    void emuUnpause();
    void emuStop();
    void emuFrameStep();

    bool emuIsRunning();
    bool emuIsActive();

    void initContext();
    void deinitContext();

    int FrontBuffer = 0;
    QMutex FrontBufferLock;

    void updateScreenSettings(bool filter, const WindowInfo& windowInfo, int numScreens, int* screenKind, float* screenMatrix);

signals:
    void windowUpdate();
    void windowTitleChange(QString title);

    void windowEmuStart();
    void windowEmuStop();
    void windowEmuPause();
    void windowEmuReset();
    void windowEmuFrameStep();

    void windowLimitFPSChange();

    void screenLayoutChange();

    void windowFullscreenToggle();

    void swapScreensToggle();
    void screenEmphasisToggle();

    void syncVolumeLevel();

private:
    void drawScreenGL();
    void initOpenGL();
    void deinitOpenGL();

    enum EmuStatusKind
    {
        emuStatus_Exit,
        emuStatus_Running,
        emuStatus_Paused,
        emuStatus_FrameStep,
    };
    std::atomic<EmuStatusKind> EmuStatus;

    EmuStatusKind PrevEmuStatus;
    EmuStatusKind EmuRunning;

    constexpr static int EmuPauseStackRunning = 0;
    constexpr static int EmuPauseStackPauseThreshold = 1;
    int EmuPauseStack;

    enum ContextRequestKind
    {
        contextRequest_None = 0,
        contextRequest_InitGL,
        contextRequest_DeInitGL
    };
    std::atomic<ContextRequestKind> ContextRequest = contextRequest_None;

    GL::Context* oglContext = nullptr;
    GLuint screenVertexBuffer, screenVertexArray;
    GLuint screenTexture;
    GLuint screenShaderProgram;
    GLuint screenShaderTransformULoc, screenShaderScreenSizeULoc;

    QMutex screenSettingsLock;
    WindowInfo windowInfo;
    float screenMatrix[Frontend::MaxScreenTransforms][6];
    int screenKind[Frontend::MaxScreenTransforms];
    int numScreens;
    bool filter;

    int lastScreenWidth = -1, lastScreenHeight = -1;
};


class ScreenHandler
{
    Q_GADGET

public:
    ScreenHandler(QWidget* widget);
    virtual ~ScreenHandler();
    QTimer* setupMouseTimer();
    void updateMouseTimer();
    QTimer* mouseTimer;
    QSize screenGetMinSize(int factor);

protected:
    void screenSetupLayout(int w, int h);

    void screenOnMousePress(QMouseEvent* event);
    void screenOnMouseRelease(QMouseEvent* event);
    void screenOnMouseMove(QMouseEvent* event);

    void screenHandleTablet(QTabletEvent* event);
    void screenHandleTouch(QTouchEvent* event);

    float screenMatrix[Frontend::MaxScreenTransforms][6];
    int screenKind[Frontend::MaxScreenTransforms];
    int numScreens;

    bool touching = false;

    void showCursor();
};


class ScreenPanelNative : public QWidget, public ScreenHandler
{
    Q_OBJECT

public:
    explicit ScreenPanelNative(QWidget* parent);
    virtual ~ScreenPanelNative();

protected:
    void paintEvent(QPaintEvent* event) override;

    void resizeEvent(QResizeEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    void tabletEvent(QTabletEvent* event) override;
    bool event(QEvent* event) override;
private slots:
    void onScreenLayoutChanged();

private:
    void setupScreenLayout();

    QImage screen[2];
    QTransform screenTrans[Frontend::MaxScreenTransforms];
};


class ScreenPanelGL : public QWidget, public ScreenHandler
{
    Q_OBJECT

public:
    explicit ScreenPanelGL(QWidget* parent);
    virtual ~ScreenPanelGL();

    std::optional<WindowInfo> getWindowInfo();

    bool createContext();

    GL::Context* getContext() { return glContext.get(); }

    void transferLayout(EmuThread* thread);
protected:

    qreal devicePixelRatioFromScreen() const;
    int scaledWindowWidth() const;
    int scaledWindowHeight() const;

    QPaintEngine* paintEngine() const override;

    void resizeEvent(QResizeEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    void tabletEvent(QTabletEvent* event) override;
    bool event(QEvent* event) override;

private slots:
    void onScreenLayoutChanged();

private:
    void setupScreenLayout();

    std::unique_ptr<GL::Context> glContext;
};
>>>>>>> e7feddaea5c54ed5a674a840ddd7ddbf186c6641

class MelonApplication : public QApplication
{
    Q_OBJECT

public:
    MelonApplication(int &argc, char** argv);
    bool event(QEvent* event) override;
};

extern QString* systemThemeName;

#endif // MAIN_H
