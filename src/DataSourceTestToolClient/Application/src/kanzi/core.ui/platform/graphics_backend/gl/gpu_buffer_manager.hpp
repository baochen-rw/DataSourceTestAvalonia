// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GPU_BUFFER_MANAGER_HPP
#define KZ_GPU_BUFFER_MANAGER_HPP

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>

#ifndef KANZI_GPU_BUFFER_MANAGER_ENABLED
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_buffer_handle.hpp>
#endif

struct KzcMemoryManager;

namespace kanzi
{
class Renderer;
}

/// Handle to memory block in buffer object available for the user.
struct KzcGPUBufferMemoryHandle;

struct KzcGPUBufferManager;

namespace kanzi
{

/// GPU memory buffer, for vertex or index data.
class Buffer
{
    typedef void (Buffer::*bool_type)() const;
    void this_type_does_not_support_comparisons() const
    {
    }

public:
    /// Type enumeration of the buffer.
    enum BufferType
    {
        /// Vertex buffer.
        BufferTypeVertex,

        /// Index buffer.
        BufferTypeIndex
    };

    /// Constructor
    explicit Buffer();

    /// Constructor
    explicit Buffer(Renderer* renderer, BufferType type, const void* data, unsigned int size);

    /// Destructor
    ~Buffer();

    /// Get buffer type
    BufferType getType() const;

    /// Get buffer native handle
    unsigned int getNativeHandle() const;

    /// Get start offset of buffer data
    unsigned int getDataOffset() const;

    friend void swap(Buffer& left, Buffer& right)
    {
        using std::swap;
        swap(left.m_renderer, right.m_renderer);
        swap(left.m_handle, right.m_handle);
#ifndef KANZI_GPU_BUFFER_MANAGER_ENABLED
        swap(left.m_type, right.m_type);
#endif
    }

    Buffer(KZ_RV_REF(Buffer) other) :
        m_renderer(other.m_renderer),
#ifdef KANZI_GPU_BUFFER_MANAGER_ENABLED
        m_handle(other.m_handle)
#else
        m_handle(kanzi::move(other.m_handle)),
        m_type(other.m_type)
#endif
    {
        other.m_renderer = 0;
#ifdef KANZI_GPU_BUFFER_MANAGER_ENABLED
        other.m_handle = 0;
#endif
    }

    Buffer& operator=(KZ_RV_REF(Buffer) other)
    {
        if (this != &other)
        {
            m_renderer = other.m_renderer;
            other.m_renderer = 0;

#ifdef KANZI_GPU_BUFFER_MANAGER_ENABLED
            m_handle = other.m_handle;
            other.m_handle = 0;
#else
            m_handle = kanzi::move(other.m_handle);
            m_type = other.m_type;
#endif
        }
        return *this;
    }

private:
    KZ_MOVABLE_BUT_NOT_COPYABLE(Buffer)

    /// Renderer
    Renderer* m_renderer;

#ifdef KANZI_GPU_BUFFER_MANAGER_ENABLED
    /// Buffer handle
    const KzcGPUBufferMemoryHandle* m_handle;
#else
    /// Buffer handle
    GLBufferHandle m_handle;

    /// Buffer type
    BufferType m_type;
#endif
};

}

/// Statistics of GPU buffer manager usage.
struct KzcGPUBufferManagerStatistics
{
    const KzcGPUBufferManager* bufferManager;   ///< Owner buffer manager.
    kanzi::Buffer::BufferType bufferType;       ///< Type of the statistics.
    unsigned int poolsCount;                    ///< Number of memory pools.
    unsigned int availableMemorySize;           ///< Available memory size.
    unsigned int usedMemorySize;                ///< How much memory is used.
    unsigned int availableMemoryBlocksCount;    ///< Number of available memory blocks.
    unsigned int usedMemoryBlocksCount;         ///< Number of used memory blocks.
    unsigned int maximumAvailableBlockSize;     ///< Maximum size block available.
};


/// Creates a new buffer manager. 
/// \param vertexBufferPoolSize - default size of vertex buffer pool (== VBO). If equal to 0, the no default buffer will be created, 
///  and new pool will be created for each uploaded data.
/// \param indexBufferPoolSize - default size of index buffer pool (== IBO). If equal to 0, the no default buffer will be created, 
///  and new pool will be created for each uploaded data.
kzsError kzcGPUBufferManagerCreate(const KzcMemoryManager* memoryManager, kanzi::Renderer* renderer, 
                                   unsigned int vertexBufferPoolSize, unsigned int indexBufferPoolSize,
                                   KzcGPUBufferManager** out_bufferManager);

/// Deletes buffer manager.
kzsError kzcGPUBufferManagerDelete(KzcGPUBufferManager* bufferManager);

/// Invalidates GPU memory manager by this manager. All pools will be removed and handles to this manager will became invalid.
kzsError kzcGPUBufferManagerInvalidateGPUMemory(KzcGPUBufferManager* bufferManager);

/// Uploads vertex data to VBO. 
/// If there is no available memory left in existing VBO's, the new one will be created. 
/// \param handle to uploaded vertex data (owned by GPU buffer manager so user should not delete it).
kzsError kzcGPUBufferManagerUploadData(KzcGPUBufferManager* bufferManager, kanzi::Buffer::BufferType bufferType, const void* data, unsigned int size, 
                                       const KzcGPUBufferMemoryHandle** out_handle);
/// Frees vertex data in VBO. 
/// \param handle to uploaded vertex data. The handle will be deleted by GPU buffer manager and should not be used after calling this function.
kzsError kzcGPUBufferManagerFreeData(const KzcGPUBufferManager* bufferManager, const KzcGPUBufferMemoryHandle* handle);

/// Gets type of buffer object referenced by specified handle.
kanzi::Buffer::BufferType kzcGPUBufferMemoryHandleGetBufferType(const KzcGPUBufferMemoryHandle* handle);

/// Gets handle of buffer object referenced by specified handle.
unsigned int kzcGPUBufferMemoryHandleGetBufferHandle(const KzcGPUBufferMemoryHandle* handle);

/// Gets offset in bytes in buffer object for the memory referenced by specified handle.
unsigned int kzcGPUBufferMemoryHandleGetDataOffset(const KzcGPUBufferMemoryHandle* handle);

/// Returns statistics for GPU buffer manager. User is responsible for deleting returned struct instance.
/// \param statistics - pointer to KzcGpuBufferManagerStatistics struct instance which will be filled with statistics data.
void kzcGPUBufferManagerGetStatistics(const KzcGPUBufferManager* bufferManager, kanzi::Buffer::BufferType bufferType, KzcGPUBufferManagerStatistics* statistics);

/// Prints out statistics for GPU buffer manager.
void kzcGPUBufferManagerDumpStatistics(const KzcGPUBufferManager* bufferManager, kzBool dumpPoolBlocks);

#endif // KZ_GPU_BUFFER_MANAGER_HPP
