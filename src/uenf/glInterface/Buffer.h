#ifndef UENF_GLINTERFACE_BUFFER_H
#define UENF_GLINTERFACE_BUFFER_H

// Copyright 2013 (c) by Thorsten Gecks (see also the file LICENSE in the base directory (its MIT))


#include <uenf/glInterface/Node.h>




namespace uenf
{

namespace glInterface
{

class VertexTypeInfo : std::vector<AttributeInfo>
{
public:  
  class AttributeInfo
  {
  public:
    GLuint attributeSize;
    GLuint attributeIndex;
  };
};


template <typename VertexType> class Buffer : public Node
{
public:    
  Buffer();
  Buffer(std::size_t bufSize)
  {
  }

  void update();
  void execute(GLPassInformation pass);
};


class Index
{};

template <typename VertexType> class PointBuffer : public Buffer<VertexType>;
template <typename VertexType> class LineBuffer : public Buffer<VertexType>;
template <typename VertexType> class TriangleBuffer : public Buffer<VertexType>;




  
} // namespace glInterface

} // end of namespace uenf





#endif // UENF_GLINTERFACE_BUFFER_H
