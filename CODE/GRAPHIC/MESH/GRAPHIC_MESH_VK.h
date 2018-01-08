
#ifndef GRAPHIC_MESH_VK_DEFINE
#define GRAPHIC_MESH_VK_DEFINE

    VkBuffer
        Buffer;
    VkDeviceMemory
        Memory;
    VkDescriptorBufferInfo
        BufferInfo;
        
public:

    inline VkBuffer & GetVkBuffer() { return Buffer; }
    inline VkDeviceMemory & GetVkMemory() { return Memory; }
    inline VkDescriptorBufferInfo & GetVkBufferInfo() { return BufferInfo; }
    
    inline void SetVkBuffer( VkBuffer & buffer ) { Buffer = buffer; }
    inline void SetVkVkDeviceMemory( VkDeviceMemory & memory ) {  Memory = memory;  }
    inline void SetVkDescriptorBufferInfo( VkDescriptorBufferInfo & info ) { BufferInfo = info; }

#endif // ! GRAPHIC_MESH_VK_DEFINE


