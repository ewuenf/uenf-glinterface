


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

  it internalPointer; // increments by 3/2/1 (depends also on storage type of triangle or lines!)

  // for triangle
  T & first/second/thirdEdge();

  bool calculateWinding() const;
}


class NodeInterface
{
  virtual ~NodeInterface(){}
  virtual void update() {}
  virtual void execute() {}
}


class SingleContextReferrer : public NodeInterface
{  
  weak_ptr<NodeInterface> parent;  
  std::vector<Context> const & getContext() //  maybe virtual?
  {
    Context * ptr = dynamic_cast<Context *>(parent.lock().get());
    if(ptr) return {ptr}; 
    else    return ptr->collectContexts();
  }
}


class MultiContextReferrer : public NodeInterface
{  
  std::vector<Context> & getContexts() = 0;
}


class NodesToUpdate : public Event
{
  void add(SingleContextReferrer);
  void add(MultiContextReferrer);
}


template < class T, 
           class PtrType = shared_ptr<T>, 
           class ReferrerType = SingleContextReferrer
         >
         Node : public ReferrerType
{
  PtrType objectPtr;
  void update()  {objectPtr->update();}
  void execute() {objectPtr->execute();}
}



class MultiParentNode<T> : public NodeBase<T>
{
  std::vector<weak_ptr<NodeInterface>> parents;  
  std::vector<Context> contexts; // cache
  
  std::vector<Context> const & getContexts()
  {
    if(parents.empty())
      return {};
    std::vector<Context> contexts;
    // iterate over parents!
    for(auto parent: parents)
    {
      Context * ptr = dynamic_cast<Context *>(parent.lock().get());
      if(ptr) return {ptr}; 
      else    return ptr->collectContexts();      
    }
    return contexts;
  }
}


was bedeutet das update einer Node in mehreren Contexten (nach dem ersten Update ist es ja überall gleich
und andererseits muss das update selbst synchronisiert sein (alle Kontexte brauchen eine Barrier)

Das Ein- und Austragen von Nodes in die Baumstruktur erfordert evtl die Anpassung der betroffenen Contexte
pro Node (für die Kinder des Nodes), falls ein Sync-Objekt direkt auf dem Node generiert werden kann, falls
dieses Sync-Objekt sich die Contexte einsammelt (Visitor-Pattern!), dann ist dies nicht nötig. Jedoch dann,
falls Sync-Objekte schon existieren (immer nur einmal generieren?)


