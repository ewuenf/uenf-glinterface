#ifndef UENF_GLINTERFACE_NODE_H
#define UENF_GLINTERFACE_NODE_H

// Copyright 2013 (c) by Thorsten Gecks (see also the file LICENSE in the base directory (its MIT))




#include <uenf/glInterface/GLPassInformation.h>


#ifdef UENF_GLINTERFACE_TRYTYPEFIELD
#include <uenf/glInterface/NodeType.h>
#endif


#include <memory>




namespace uenf
{

namespace glInterface
{


//! As we have no virtuals (in shared memory scenarios), we will use a type field.
class Node
{
public:    
  std::weak_ptr<Node> const & getParent() const { return parent; }
  void setParent(std::weak_ptr<Node> const & parentArg) { parent = parentArg; }
  
  #ifdef UENF_GLINTERFACE_TRYTYPEFIELD
  Node(NodeType const & typeArg = NodeType::None):type(typeArg){}

  NodeType const & getNodeType() const { return nodeType; }
  #endif

  // All derived may just overwrite the following functions. This is essentially defining an interface,
  // but only by convention, not using virtual functions, because we want to simplify inlining and be
  // able to use the class in shared memory scenarios (thus no virtuals)
  #ifdef UENF_GLINTERFACE_TRYTYPEFIELD
  void update(){}
  #else
  virtual void update() = 0;
  #endif
  
  #ifdef UENF_GLINTERFACE_TRYTYPEFIELD
  void execute(GLPassInformation pass){}
  #else
  virtual void execute(GLPassInformation const & pass) = 0;
  #endif
  
private:
  std::weak_ptr<Node> parent;
  
  #ifdef UENF_GLINTERFACE_TRYTYPEFIELD
  const NodeType type;
  #endif
};

  
} // namespace glInterface

} // end of namespace uenf

#endif // UENF_GLINTERFACE_NODE_H

