#ifndef GPU3D_TEXCACHEOPENGL
#define GPU3D_TEXCACHEOPENGL

#include "GPU3D_Texcache.h"
#include "OpenGLSupport.h"

<<<<<<< HEAD
namespace melonDS
=======
namespace GPU3D
>>>>>>> e7feddaea5c54ed5a674a840ddd7ddbf186c6641
{

template <typename, typename>
class Texcache;

class TexcacheOpenGLLoader
{
public:
    GLuint GenerateTexture(u32 width, u32 height, u32 layers);
    void UploadTexture(GLuint handle, u32 width, u32 height, u32 layer, void* data);
    void DeleteTexture(GLuint handle);
};

using TexcacheOpenGL = Texcache<TexcacheOpenGLLoader, GLuint>;

}

#endif