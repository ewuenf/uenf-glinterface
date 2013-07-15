


class AttributeInfo
{
  std::string name;
  GLint size;
  GLenum type;
  GLboolean normalized;
  GLsizei stride;
  void * offset;
  bool enabled;
}


/*
  For vertex data, the type VertexType must define
  two functions beginAttributeInfo() and endAttributeInfo()
  that can be used to iterate over a sequence of AttributeInfo
  objects, that define the parts of VertexType. Both functions
  are provided const and non-const
*/


class VertexBuffer<typename VertexType>
{
  typedef VertexType * iterator;

  (const) iterator begin() end()
  
  std::shared_array<VertexType> vertexArray;
  
  GLuint glBufferObject;
  void * bufferOffset;
}


class IndexedVertexBuffer<typename VertexType>
{
  class IndexedIterator<VertexType>
  {
    VertexType & operator*();
    VertexType * operator->();
  }

  (const) IndexedIterator<VertexType> begin() end();
}



class Triangle/Line/PointIterator<typename BufferType>
{
  typedef typename BufferType::iterator it;

  it internalPointer; // increments by 3/2/1

  // for triangle
  T & first/second/thirdEdge();

  bool calculateWinding() const;
}


class NodeInterface
{
  virtual ~NodeInterface(){}
  virtual void update() {}
  virtual void execute() {}
  virtual std::vector<Context> const & collectContexts() {return std::vector<Context>();}
}

class NodeBase<T> : public NodeInterface
{
  shared_ptr<T> t;
  void update() {t->update();}
  void execute() {t->execute();}
}


class Node<T> : public NodeBase<T>
{
  weak_ptr<NodeInterface> parent;  
  std::vector<Context> const & collectContexts()
  {
    Context * ptr = dynamic_cast<Context *>(parent.lock().get());
    if(ptr) return {ptr}; 
    else    return ptr->collectContexts();
  }
}


class MultiParentNode<T> : public NodeBase<T>
{
  std::vector<weak_ptr<NodeInterface>> parents;  
  std::vector<Context> const & collectContexts()
  {
    // iterate over parents!
    Context * ptr = dynamic_cast<Context *>(parent.lock().get());
    if(ptr) return {ptr}; 
    else    return ptr->collectContexts();
  }
}





