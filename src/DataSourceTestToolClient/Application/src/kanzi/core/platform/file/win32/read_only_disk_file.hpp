// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_WINDOWS_READ_ONLY_DISK_FILE_HPP
#define KZ_WINDOWS_READ_ONLY_DISK_FILE_HPP

#ifndef KZ_READ_ONLY_DISK_FILE_HPP
    #error "Do not include this header directly. Please use instead: #include <kanzi/core/file/read_only_disk_file.hpp>"
#endif

#include <kanzi/core/file/file.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string_view.hpp>


// Opaque handle type used by Win32.
typedef void* HANDLE;


namespace kanzi
{

class ReadOnlyDiskFile;

typedef unique_ptr<ReadOnlyDiskFile> ReadOnlyDiskFileUniquePtr;

/// Implements the File interface for files residing on a disk.
class KANZI_API ReadOnlyDiskFile : public File
{
public:
    /// Factory function.
    /// Creates an object representing an open file handle to a disk file.
    /// \param filename The name (including path) of the disk file to handle.
    /// \return Pointer to the object, or null when file cannot be accessed.
    static ReadOnlyDiskFileUniquePtr tryOpen(string_view filename);

    /// Constructor.
    /// \param filename The name (including path) of the disk file to handle.
    /// Throws runtime_error if file cannot be accessed.
    explicit ReadOnlyDiskFile(string_view filename);

    /// Constructor.
    /// \param filename The name (including path) of the disk file to handle.
    /// Throws runtime_error if file cannot be accessed.
    explicit ReadOnlyDiskFile(const char* filename) : ReadOnlyDiskFile(string_view(filename)) {}

    /// Destructor.
    /// Closes the file handle and unmaps the file as needed.
    virtual ~ReadOnlyDiskFile() KZ_OVERRIDE;

    virtual void read(char* buffer, uint64_t count) KZ_OVERRIDE;

    virtual void write(const char* buffer, uint64_t count) KZ_OVERRIDE;

    virtual uint64_t size() const KZ_OVERRIDE;

    virtual uint64_t tell() const KZ_OVERRIDE;

    virtual void seek(SeekPosition position, int64_t offset) KZ_OVERRIDE;

    /// Creates a memory mapping of the disk file.
    /// Does nothing if the disk file has already been memory mapped.
    /// \return Pointer to the view of the memory map.
    virtual const byte* map() KZ_OVERRIDE;

protected:
    /// Constructor.
    /// \param fileHandle An open disk file handle.
    explicit ReadOnlyDiskFile(HANDLE fileHandle);

    /// Opaque handle to the disk file.
    HANDLE m_fileHandle;

    /// Opaque handle to the memory map of the disk file.
    HANDLE m_mapHandle;

    /// Pointer to the view of the memory map of the disk file.
    void* m_mapView;

private:
    ReadOnlyDiskFile(const ReadOnlyDiskFile&) KZ_DELETED_FUNCTION;
    ReadOnlyDiskFile& operator=(const ReadOnlyDiskFile&) KZ_DELETED_FUNCTION;
};

}


#endif
