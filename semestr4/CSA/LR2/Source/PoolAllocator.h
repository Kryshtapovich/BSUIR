
#ifndef RISCV_SIM_POOLALLOCATOR_H
#define RISCV_SIM_POOLALLOCATOR_H

#include <cstddef>
#include <cstdlib>

template <typename T>
class PoolAllocator
{
public:
    PoolAllocator(size_t chunksPerBlock)
            : _chunksPerBlock(chunksPerBlock) {}

    void *allocate(size_t size)
    {

        // No chunks left in the current block, or no any block
        // exists yet. Allocate a new one, passing the chunk size:

        if (_alloc == nullptr)
        {
            _alloc = allocateBlock(size);
        }

        // The return value is the current position of
        // the allocation pointer:

        Chunk *freeChunk = _alloc;

        // Advance (bump) the allocation pointer to the next chunk.
        //
        // When no chunks left, the `_alloc` will be set to `nullptr`, and
        // this will cause allocation of a new block on the next request:

        _alloc = _alloc->next;

        return freeChunk;
    }
    void deallocate(void *chunk, size_t size)
    {

        // The freed chunk's next pointer points to the
        // current allocation pointer:

        reinterpret_cast<Chunk *>(chunk)->next = _alloc;

        // And the allocation pointer is now set
        // to the returned (free) chunk:

        _alloc = reinterpret_cast<Chunk *>(chunk);
    }

private:
    struct Chunk {
        /**
         * When a chunk is free, the `next` contains the
         * address of the next chunk in a list.
         *
         * When it's allocated, this space is used by
         * the user.
         */
        Chunk *next;
    };

    /**
     * Number of chunks per larger block.
     */
    size_t _chunksPerBlock;

    /**
     * Allocation pointer.
     */
    Chunk *_alloc = nullptr;

    /**
     * Allocates a larger block (pool) for chunks.
     */
    Chunk *allocateBlock(size_t chunkSize)
    {
//        cout << "\nAllocating block (" << _chunksPerBlock << " chunks):\n\n";

        size_t blockSize = _chunksPerBlock * chunkSize;

        // The first chunk of the new block.
        auto *blockBegin = reinterpret_cast<Chunk *>(malloc(blockSize));

        // Once the block is allocated, we need to chain all
        // the chunks in this block:

        Chunk *chunk = blockBegin;

        for (int i = 0; i < _chunksPerBlock - 1; ++i) {
            chunk->next =
                    reinterpret_cast<Chunk *>(reinterpret_cast<char *>(chunk) + chunkSize);
            chunk = chunk->next;
        }

        chunk->next = nullptr;

        return blockBegin;
    }
};

template <typename T>
class PoolAllocated
{
public:
    static void *operator new(size_t size)
    {
        return allocator.allocate(size);
    }

    static void operator delete(void *ptr, size_t size)
    {
        return allocator.deallocate(ptr, size);
    }
private:
    static PoolAllocator<T> allocator;
};

#endif //RISCV_SIM_POOLALLOCATOR_H
