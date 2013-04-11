#ifndef UENF_GLINTERFACE_NODETYPE_H
#define UENF_GLINTERFACE_NODETYPE_H

#include <cstdint>
#include <limits>


namespace uenf
{

namespace glInterface
{

typedef uint32_t NodeTypeBase;

enum class NodeType : NodeTypeBase
{
  None = 0,
  Test = 1,
  User = std::numeric_limits<NodeTypeBase>::max() / 2,
  Max = User * 2      
};

  
} // namespace glInterface

} // end of namespace uenf

#endif // UENF_GLINTERFACE_NODETYPE_H

