


//GUI parts +++++++++++++++++++++++++++++++++++++++++++++++++++++


typedef Eigen::Matrix4d CoorSys;

class Frame<Allocator?>  // Allocator for CoorSyss could help having these in a block of contigous, aligned memory
{
  static resX, resY; // resolution in Pixels
  void getPixelResolution(sizeXout, sizeYout)
  {
    return unit vectors of the local coordinate system in x and y direction scaled by the statics resX and resY
  }
  
  std::vector<Frame *> subFrames[];

  std::unique_ptr<CoorSys> globalCoorSys;
  std::unique_ptr<CoorSys> localCoorSys;

  void updateFromParent(CoorSys * coorSysParent)
  {
    (*globalCoorSys) = (*coorSysParent) * (*localCoorSys);
    updateChilds();
  }
  
  void updateChilds()
  {
    for(auto * frame: subFrames) {frame->update(globalCoorSys);}
  }

  
  void rotateXYZ()
  {
    // apply rot mat
  }
  void rotateXYZAndUpdate()
  {
    // apply rot mat and then
    updateChilds();
  }
}


class LayeredDrawCompressedCoorSyss
{
  define subframes and compress these by scaling, so they are thightly
  packed
}


class LayeredDrawOrderDependentNoDepth // optimized for GUI elements
{
  disable depth testing and draw sub-elements from back to front
  (eventually setting an artificial depth to be combinable with other
  elements)
}




class ColorPalette
{
  Color light, dark;
  Color reddish, greenish, bluish;
  Color error, warning, info, debug;
};


//GUI parts end +++++++++++++++++++++++++++++++++++++++++++++++++++++












class Program
{
  has referenced textures maybe and lots of possible additional variables (how to do these?)
  and can be updated
}


class ProgramManager
{
public:
  uint getProgramNameMapping(std::string name);
  std::shared_ptr<Program> getProgram(std::string name);
  std::shared_ptr<Program> getProgram(uint id);
}



class BufferInterface
{
public:
  virtual bool checkProgramCompatibility(Program const & program) const = 0;
  virtual void setupVAO(GLuint vao) = 0;
};


class BufferAllocator
{
  class AllocInfo
  {
    GLuint glBuffer, offset, size;
    void * memBuffer;
  }

  AllocInfo allocate  (size_t bytes);
  AllocInfo deallocate(size_t bytes);
};


// do a interleaved implementation first, a non-interleaved can be done transparently using templates?
template<typename Vertex, typename Allocator = BufferAllocator> class Buffer : public BufferInterface
{
  void setupVAO(GLuint vao)
  {
    Vertex::setupVAO(vao, allocInfo); // use static function from vertex type to setup the vao
                                      // needs an AllocInfo additionally (for the necessary GL infos)    
  }
  
}




class DrawableBase
{
public:
  virtual void setup(); // sets up vao
  virtual void update();
  virtual void draw();
  
  virtual void check(); // called in UENF_GL_DEBUG environments

  // typically has a buffer, a VAO and references a program
  // optionally has an index array and instanced data
  
  virtual BufferInterface const * getBuffer() const;
  std::shared_ptr<Program> getProgram();
  
protected:
  // common functions
  
protected:
  GLuint vao;
};


class DrawableIndexed
{
  
};


class DrawableWithFrame
{
public:  // use composition here
  std::unique_ptr<DrawableBase> drawable;
  Frame frame;
};



// DrawableCategory associates a drawable that is the one behind all gui elements of that category
// This is just needed for organization of drawables in gui-library
enum DrawableCategory : uint16 {
  Splash,
  Background,
  Button,
  Menu,
  TextLabel,        // has a string-based map identifying subcategories depending on the font (and thus the associated texture) 
  User = (2 << 12)  // free category for library extensions by users, implies a string-based map too 
}

class DrawableCategoryIndex
{
  DrawableCategory category;
  int16 subIndex;
};


// The "NAME"! flat axis-aligned quad (oder auch Kuhflaad ;-) )  
// This would be the base class for all GUI elements (recursivly), as it is a frame essentially,
// that could host a button, an image, a text box, etc...
class FlaadInterface
{};

class Flaad : public FlaadInterface
{
public:
  DrawableCategoryIndex const drawableCategoryIndex;
  
  every Flaad of a certain type just refers to subindices of a common Buffer in a Drawable (drawing Triangles)
  of the given FlaadCategory, the Drawable is then responsible for the appereance of
  all associated Flaads, thus setting the values for this Drawable changes the
  appereance of all associated Flaads in a central place, which is what we want
};

class TextFlaad;
class ButtonFlaad; // has a TextFlaad contained
class TabFlaad;




namespace RenderFunctions
{
  namespace FlatNoLightingRenderer
  {
    void update();
    void render();
  }
  
  namespace StdLightingRenderer
  {
    void update();
    void render();
  }  

  namespace DeferredLightingRenderer
  {
    void update();
    void render();
  }    
}