# const_map -- a read-only, std::map-like associative array.

## Introduction

A `const_map` is built around a given array of key/value pairs (a so-called mapping table), sorted by key in ascending order. Since element lookup is done via binary search, the time
complexity is O(log(n)).

A typical example:
```c++
static const const_map<int, const char*>::value_type COLOR_NAMES[] = {
    { 111, "red"   },
    { 222, "green" },
    { 333, "blue"  },
};

const_map<int, const char*> color_names(COLOR_NAMES);

// Simple lookup.
EXPECT_EQ("green", color_names[222]);

// Lookup via 'find'.
auto iter = color_names.find(333);
EXPECT_TRUE(iter != color_names.end());
EXPECT_EQ("blue", iter->second);

// Lookup via 'find' failed.
iter = color_names.find(12345);
EXPECT_TRUE(iter == color_names.end());
```

## Sentinels

One problem with `const_map` is that using `operator[]` to look-up a non-exitent element yields undefined behavior. While some would say that this nicely mirrors the behavior of out-of-bounds array access, others would rather have a more resilient behavior. The latter can be achieved by adding an (otherwise unused) sentinel value to the mapping table:

```c++
static const const_map<int, const char*>::value_type COLOR_NAMES[] = {
    { 111, "red"   },  // <-- begin()
    { 222, "green" },
    { 333, "blue"  },  // last element of mapping table
    // Sentinel
    {  -1, nullptr },  // <-- end()
};

const_map<int, const char*> color_names(COLOR_NAMES, const_map_sentinel::yes);

// No match found.
EXPECT_EQ(nullptr, color_names[12345]);
EXPECT_EQ(color_names.end()->second, color_names[12345]);
EXPECT_EQ(nullptr, color_names[999]);

// Lookup via 'find'.
auto iter = color_names.find(12345);
EXPECT_TRUE(iter == color_names.end());
iter = color_names.find(999);
EXPECT_TRUE(iter == color_names.end());
```

The only constraint on the sentinel value is that the key value must be unique, that is, it's not already used in the mapping table. Further, the sentinel's value should also be unique such that its value can be unambigously interpreted as "not found". 

What the sentinel basically does is make the iterator that `end()` returns "dereferenceable".


## Static Lookup

`const_map` comes with an overhead of two pointers, one to the beginning and another one to the end of the mapping table. If even this is too much, you can use the 'lookup' class method, which doesn't require an object:

```c++
static const const_map<int, const char*>::value_type COLOR_NAMES[] = {
 { 111, "red"   },
 { 222, "green" },
 { 333, "blue"  },
};

// 'lookup' doesn't require an instance.
auto iter = const_map<int, const char*>::lookup(COLOR_NAMES, 333);
EXPECT_TRUE(iter != nullptr);
EXPECT_EQ("blue", iter->second);

// 'lookup' doesn't find a match.
iter = const_map<int, const char*>::lookup(COLOR_NAMES, 12345);
EXPECT_TRUE(iter == nullptr);
```
