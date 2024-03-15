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

#pragma once

#include "OpenGLSupport.h"
#include "GPU3D.h"

#include <array>
#include <optional>

namespace melonDS
{
class GPU;
struct RenderSettings;
class GLRenderer;
class GLCompositor
{
public:
    static std::optional<GLCompositor> New() noexcept;
    GLCompositor(const GLCompositor&) = delete;
    GLCompositor& operator=(const GLCompositor&) = delete;
    GLCompositor(GLCompositor&&) noexcept;
    GLCompositor& operator=(GLCompositor&&) noexcept;
    ~GLCompositor();

    void SetScaleFactor(int scale) noexcept;
    [[nodiscard]] int GetScaleFactor() const noexcept { return Scale; }

    void Stop(const GPU& gpu) noexcept;
    void RenderFrame(const GPU& gpu, Renderer3D& renderer) noexcept;
    void BindOutputTexture(int buf);
<<<<<<< HEAD
    
=======
private:
>>>>>>> e7feddaea5c54ed5a674a840ddd7ddbf186c6641
    GLCompositor(GLuint CompShader) noexcept;

    int Scale;
    int ScreenH, ScreenW;

    GLuint CompShader;
    GLuint CompScaleLoc;
    GLuint Comp3DXPosLoc;

    GLuint CompVertexBufferID = 0;
    GLuint CompVertexArrayID = 0;

    struct CompVertex
    {
        std::array<float, 2> Position {};
        std::array<float, 2> Texcoord {};
    };
    std::array<CompVertex, 2*3*2> CompVertices {};

    GLuint CompScreenInputTex = 0;
    std::array<GLuint, 2> CompScreenOutputTex {};
    std::array<GLuint, 2> CompScreenOutputFB {};
};

}
