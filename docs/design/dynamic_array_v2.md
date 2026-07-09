# Phase 0 - Dynamic array design proposal
**Project:** Collections Library (C++)  
**Component:** Dynamic array
**Phase:** 0 – Design Proposal  
**Version:** 2.0 

## Objective

The objective of designing the Dynamic Array is to build a reusable, memory-efficient, and dynamically resizable container that can store elements in contiguous heap memory. Unlike fixed-size arrays, the Dynamic Array can automatically grow during runtime when more storage is required.

This implementation focuses on understanding manual memory management, dynamic allocation, resizing strategies, object lifetime, and safe memory ownership. The structure will support efficient random access, insertion, deletion, and modification operations while maintaining proper handling of heap memory using the Rule of Three.

---

# Section 1: Public API

![Public API](./project-api.png)


    Generic Template Design

The Dynamic Array is implemented as a generic template class using C++ templates. Instead of restricting the container to a single data type such as int, the template parameter T allows the same implementation to store different data types without modifying the source code.

This means a single implementation can be used to create Dynamic Arrays of various primitive data types such as:


    #include <iostream>
    #include <cstdlib>

    template <typename T>
    class DynamicArray
    {
    private:
    T* data;
    int currentSize;
    int currentCapacity;

    void resize();
    bool isValidIndex(int index) const;

    public:
    // Constructors
    DynamicArray();
    DynamicArray(int initialCapacity);

    // Rule of Three
    DynamicArray(const DynamicArray<T>& other);
    DynamicArray<T>& operator=(const DynamicArray<T>& other);
    ~DynamicArray();

    // Element Modification
    void append(const T& value);
    void insert(int index, const T& value);
    void remove(int index);
    void clear();

    // Element Access
    T get(int index) const;
    void set(int index, const T& value);

    // State Information
    int size() const;
    int capacity() const;
    bool isEmpty() const;

    // Display
    void display() const;
    };


## API Design Justification

The proposed API has been designed to separate responsibilities into four categories:

### Object Lifecycle
- Constructor
- Destructor

### Data Modification
- `append()`
- `insert()`
- `remove()`
- `set()`
- `clear()`

### Data Access
- `get()`

### State Inspection
- `size()`
- `capacity()`

Additional utility methods such as `set()`, `isEmpty()`, and `clear()` have been included to improve usability and readability without increasing the complexity of the implementation.

---

# Section 2: Internal Representation

The internal representation describes how the Dynamic Array stores and manages its data internally. It focuses on how the data structure is organized in memory and how memory is managed throughout the lifetime of the object.

Since we are dealing with dynamic memory, all elements are stored in **contiguous heap memory**. Because the number of elements cannot be determined at compile time, memory is allocated dynamically during runtime.

## Private Data Members

### 1. `data`

**Type:** Pointer to the element type

**Purpose:**

The `data` pointer stores the address of the first element of the dynamically allocated array. It provides access to the contiguous block of heap memory where all elements are stored.

---

### 2. `size`

**Type:** Integer

**Purpose:**

The `size` variable keeps track of the number of elements currently stored in the Dynamic Array. It changes whenever elements are inserted or removed.

---

### 3. `capacity`

**Type:** Integer

**Purpose:**

The `capacity` variable represents the total number of elements that the currently allocated memory block can hold before a resize operation becomes necessary.

---

## Memory Map Diagram

![Memory Diagram](./Dynamic_memory.jpg)

---

## Resize Strategy

When the Dynamic Array becomes full (`size == capacity`), a new memory block with larger capacity is allocated. Existing elements are copied into the new block, the old memory is released, and the `data` pointer is updated to point to the new memory location.

This allows the Dynamic Array to grow dynamically during runtime.

---

## Rule of Three

Since the Dynamic Array manages heap memory manually, the **Rule of Three** plays a crucial role in ensuring proper resource management.

### Destructor

The destructor is responsible for releasing the heap memory owned by the Dynamic Array when the object is destroyed. This prevents memory leaks.

---

### Copy Constructor

The copy constructor performs a **deep copy** by allocating a new memory block and copying all elements from the source object. This ensures that each Dynamic Array owns its own memory.

---

### Copy Assignment Operator

The copy assignment operator also performs a **deep copy**. Before copying, it releases any previously allocated memory owned by the destination object to avoid memory leaks.

---

# Section 3: Complexity Estimates

![Time Complexity](./timecomplexity.png)

---

# Section 4: Design Decisions

## Design Decision 1: Contiguous Memory Storage

### Selected Design

The Dynamic Array stores all elements in a contiguous block of heap memory.

### Reason

Contiguous storage allows direct indexing of elements, making random access efficient. It also improves cache locality, resulting in better overall performance during sequential traversal.

### Alternative Considered

Linked storage using nodes.

### Why Rejected

Linked storage requires pointer traversal to access elements, resulting in **O(n)** random access. Since one of the primary goals of the Dynamic Array is fast indexing, linked storage was rejected.

---

## Design Decision 2: Dynamic Heap Allocation

### Selected Design

The Dynamic Array allocates memory dynamically on the heap instead of using fixed-size stack memory.

### Reason

The number of elements that the container must store is not known during compilation. Heap allocation allows the container to grow as new elements are inserted.

### Alternative Considered

Fixed-size stack array.

### Why Rejected

A stack array has a fixed size that cannot be changed during program execution. Once full, no additional elements can be inserted without creating another array.

---

## Design Decision 3: Automatic Resizing

### Selected Design

Whenever the array reaches its maximum capacity, a larger memory block is allocated automatically and the existing elements are copied into the new block.

### Reason

Automatic resizing allows the Dynamic Array to continue accepting new elements without requiring intervention from the user.

### Alternative Considered

Fixed capacity with overflow errors.

### Why Rejected

Requiring users to manually manage capacity makes the data structure less reusable and more difficult to use in real-world applications.

---

## Design Decision 4: Capacity Doubling Strategy

### Selected Design

Whenever resizing is required, the capacity of the array is doubled.

### Reason

Doubling the capacity minimizes the number of reallocations and provides an **amortized time complexity of O(1)** for append operations.

### Alternatives Considered

- Increase capacity by one element.
- Increase capacity by a fixed constant.
- Increase capacity by 50%.

### Why Rejected

Increasing capacity by one or by a fixed constant results in frequent reallocations and unnecessary copying of elements. Although a 50% growth strategy is more memory-efficient, doubling provides a simpler implementation and stronger performance guarantees for this project.

---

## Design Decision 5: Deep Copy

### Selected Design

The Dynamic Array implements deep copying through the copy constructor and copy assignment operator.

### Reason

Each object should own its own independent block of memory. Deep copying prevents shared ownership and ensures that destroying one object does not affect another.

### Alternative Considered

Shallow copy.

### Why Rejected

A shallow copy duplicates only the pointer value, causing multiple objects to reference the same memory block. This can lead to dangling pointers, double deletion, and undefined behavior.

---

## Design Decision 6: Separate Size and Capacity Variables

### Selected Design

The Dynamic Array maintains separate variables for `size` and `capacity`.

### Reason

The `size` represents the number of valid elements currently stored, while `capacity` represents the total allocated storage. Keeping these values separate allows the implementation to determine when resizing is necessary.

### Alternative Considered

Store only the current size.

### Why Rejected

Without tracking capacity, the container would not know whether additional memory allocation is required before inserting new elements.

---

## Design Decision 7: Error Handling Strategy

The Dynamic Array performs boundary checking before accessing or modifying elements.

For operations that receive an index, the valid index range is checked before execution.

If the index is outside the valid range, the operation is rejected safely by throwing an exception.

### `get(index)`

Valid only if:

```cpp
0 <= index < size
```

If:

```cpp
index < 0 || index >= size
```

the access is considered invalid because the requested memory location does not belong to the stored elements.

---

### `insert(index, value)`

Valid range:

```cpp
0 <= index <= size
```

Insertion is allowed at the end position (`index == size`).

---

### `remove(index)`

Valid range:

```cpp
0 <= index < size
```

Only existing elements can be removed.

---

### Benefits of Boundary Checking

This strategy prevents:

- Out-of-bounds memory access
- Undefined behavior
- Invalid modification of heap memory