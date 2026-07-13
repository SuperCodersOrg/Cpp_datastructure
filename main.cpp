#include "include/dynamicarray.h"
#include "include/hashmap.h"
#include "include/linkedlist.h"
#include <cassert>
#include <iostream>
#include <string>

// User-defined Key type
struct CustomKey {
  int id;
  std::string name;

  bool operator==(const CustomKey &other) const {
    return id == other.id && name == other.name;
  }
};

// Custom Hash functor for CustomKey
struct CustomKeyHash {
  std::size_t operator()(const CustomKey &k) const {
    return std::hash<int>{}(k.id) ^ (std::hash<std::string>{}(k.name) << 1);
  }
};

// User-defined Value type with tracking for construction/destruction
struct CustomValue {
  std::string val;
  static int constructorCount;
  static int destructorCount;

  CustomValue() : val("") { constructorCount++; }
  CustomValue(const std::string &v) : val(v) { constructorCount++; }
  CustomValue(const CustomValue &other) : val(other.val) { constructorCount++; }
  ~CustomValue() { destructorCount++; }
};

int CustomValue::constructorCount = 0;
int CustomValue::destructorCount = 0;

// Simple hash functor for std::string
struct StringHash {
  std::size_t operator()(const std::string &s) const {
    std::size_t hash = 0;
    for (char c : s) {
      hash = hash * 31 + c;
    }
    return hash;
  }
};

int main() {
  std::cout << "=== DynamicArray Code ===" << std::endl;
  DynamicArray<int> arr;
  arr.append(1);
  arr.append(2);
  arr.append(3);

  std::cout << "Size: " << arr.size() << std::endl;
  std::cout << "Capacity: " << arr.capacity() << std::endl;

  for (int i = 0; i < arr.size(); ++i) {
    std::cout << "Element at index " << i << ": " << arr.get(i) << std::endl;
  }

  arr.remove(1);
  std::cout << "After removing element at index 1:" << std::endl;
  for (int i = 0; i < arr.size(); ++i) {
    std::cout << "Element at index " << i << ": " << arr.get(i) << std::endl;
  }

  std::cout << "Is array empty? " << (arr.isEmpty() ? "Yes" : "No")
            << std::endl;

  arr.insert(1, 5);
  std::cout << "After inserting 5 at index 1:" << std::endl;
  for (int i = 0; i < arr.size(); ++i) {
    std::cout << "Element at index " << i << ": " << arr.get(i) << std::endl;
  }

  std::cout << "\n=== LinkedList Code ===" << std::endl;
  LinkedList<int> list;
  list.insertFront(10);
  list.insertBack(20);
  list.insertBack(30);
  list.insertAt(1, 15);

  std::cout << "Initial list: ";
  list.print();

  std::cout << "Size: " << list.size() << std::endl;
  std::cout << "Search 20: " << (list.search(20) ? "Found" : "Not Found")
            << std::endl;
  std::cout << "Search 100: " << (list.search(100) ? "Found" : "Not Found")
            << std::endl;

  list.deleteAt(1);
  std::cout << "After deleting at index 1: ";
  list.print();

  list.deleteFront();
  std::cout << "After deleting front: ";
  list.print();

  list.deleteBack();
  std::cout << "After deleting back: ";
  list.print();

  std::cout << "Is list empty? " << (list.isEmpty() ? "Yes" : "No")
            << std::endl;

  std::cout << "\n=== HashMap Code ===" << std::endl;

  std::cout << "--- Testing Constructors & Rule of Three ---" << std::endl;
  {
    HashMap<std::string, int, StringHash> map1(8);
    std::cout << "Successfully constructed map1 (capacity 8)." << std::endl;

    HashMap<std::string, int, StringHash> map2 = map1; // Copy constructor
    std::cout << "Successfully copy-constructed map2 from map1." << std::endl;

    HashMap<std::string, int, StringHash> map3;
    map3 = map2; // Copy assignment operator
    std::cout << "Successfully copy-assigned map3 from map2." << std::endl;
  }
  std::cout << "Successfully destructed all maps." << std::endl;

  std::cout << "\n--- Testing with User-defined Types ---" << std::endl;
  {
    CustomValue::constructorCount = 0;
    CustomValue::destructorCount = 0;
    {
      HashMap<CustomKey, CustomValue, CustomKeyHash> customMap1(4);
      std::cout << "Successfully constructed customMap1." << std::endl;
      customMap1.insert(CustomKey{1, "Alice"}, CustomValue{"Value1"});
      customMap1.insert(CustomKey{2, "Bob"}, CustomValue{"Value2"});

      HashMap<CustomKey, CustomValue, CustomKeyHash> customMap2(customMap1);
      std::cout << "Successfully copy-constructed customMap2." << std::endl;

      CustomValue val;
      assert(customMap2.get(CustomKey{1, "Alice"}, val) && val.val == "Value1");
      assert(customMap2.get(CustomKey{2, "Bob"}, val) && val.val == "Value2");
    }
    std::cout << "Constructor count: " << CustomValue::constructorCount << std::endl;
    std::cout << "Destructor count: " << CustomValue::destructorCount << std::endl;
    assert(CustomValue::constructorCount == CustomValue::destructorCount);
  }
  std::cout << "Successfully destructed all custom maps." << std::endl;

  std::cout << "\n--- Testing HashMap Core Operations (Primitive Keys) ---" << std::endl;
  {
    HashMap<int, std::string> map(4);
    assert(map.isEmpty());
    assert(map.size() == 0);

    // Test Insert
    map.insert(1, "One");
    map.insert(2, "Two");
    map.insert(3, "Three");

    assert(!map.isEmpty());
    assert(map.size() == 3);
    assert(map.contains(1));
    assert(map.contains(2));
    assert(map.contains(3));
    assert(!map.contains(4));

    // Test Get
    std::string val;
    assert(map.get(1, val) && val == "One");
    assert(map.get(2, val) && val == "Two");
    assert(map.get(3, val) && val == "Three");
    assert(!map.get(4, val));

    // Test Update
    map.insert(2, "Second");
    assert(map.get(2, val) && val == "Second");
    assert(map.size() == 3);

    // Test Resize/Rehash (maxLoadFactor = 0.75, capacity = 4, threshold = 3)
    // Inserting the 4th unique key should trigger a rehash (new capacity = 8)
    map.insert(4, "Four");
    assert(map.size() == 4);
    assert(map.get(4, val) && val == "Four");
    assert(map.get(1, val) && val == "One"); // Ensure older keys are still accessible after rehash

    // Test Remove
    assert(map.remove(2));
    assert(!map.contains(2));
    assert(!map.get(2, val));
    assert(map.size() == 3);

    // Test Remove of non-existent key
    assert(!map.remove(10));
    assert(map.size() == 3);

    std::cout << "All core operations with HashMap<int, std::string> passed successfully." << std::endl;
  }

  std::cout << "\n--- Testing HashMap with Double/Float Keys ---" << std::endl;
  {
    HashMap<double, char> doubleMap(4);
    doubleMap.insert(3.14, 'p');
    doubleMap.insert(2.718, 'e');
    doubleMap.insert(0.0, 'z');

    char c;
    assert(doubleMap.get(3.14, c) && c == 'p');
    assert(doubleMap.get(2.718, c) && c == 'e');
    assert(doubleMap.get(0.0, c) && c == 'z');
    assert(!doubleMap.contains(1.414));

    std::cout << "All operations with HashMap<double, char> passed successfully." << std::endl;
  }

  std::cout << "\n--- Testing HashMap with Pointer Keys ---" << std::endl;
  {
    HashMap<int*, int> ptrMap(4);
    int a = 10, b = 20;
    ptrMap.insert(&a, 100);
    ptrMap.insert(&b, 200);

    int val;
    assert(ptrMap.get(&a, val) && val == 100);
    assert(ptrMap.get(&b, val) && val == 200);
    assert(!ptrMap.contains(nullptr));

    std::cout << "All operations with HashMap<int*, int> passed successfully." << std::endl;
  }

  std::cout << "\n--- Testing HashMap with Long Double Keys ---" << std::endl;
  {
    HashMap<long double, int> ldMap(4);
    ldMap.insert(3.141592653589793238L, 1);
    ldMap.insert(2.718281828459045235L, 2);
    ldMap.insert(0.0L, 0);

    int val;
    assert(ldMap.get(3.141592653589793238L, val) && val == 1);
    assert(ldMap.get(2.718281828459045235L, val) && val == 2);
    assert(ldMap.get(0.0L, val) && val == 0);
    assert(!ldMap.contains(1.414213562373095048L));

    std::cout << "All operations with HashMap<long double, int> passed successfully." << std::endl;
  }

  std::cout << "\n--- Testing HashMap with nullptr_t Keys ---" << std::endl;
  {
    HashMap<std::nullptr_t, std::string> npMap(4);
    npMap.insert(nullptr, "Null Pointer");

    std::string val;
    assert(npMap.get(nullptr, val) && val == "Null Pointer");
    assert(npMap.contains(nullptr));

    std::cout << "All operations with HashMap<nullptr_t, std::string> passed successfully." << std::endl;
  }

  std::cout << "\n--- Testing loadFactor(), print(), and clear() ---" << std::endl;
  {
    HashMap<std::string, int, StringHash> map(4);
    assert(map.loadFactor() == 0.0f);

    map.insert("one", 1);
    map.insert("two", 2);
    map.insert("three", 3);

    // loadFactor should be 3 / 4 = 0.75f
    assert(map.loadFactor() == 0.75f);

    std::cout << "HashMap contents (print):" << std::endl;
    map.print();

    map.clear();
    assert(map.isEmpty());
    assert(map.size() == 0);
    assert(map.loadFactor() == 0.0f);
    assert(!map.contains("one"));

    std::cout << "loadFactor(), print(), and clear() tests passed successfully." << std::endl;
  }

  return 0;
}