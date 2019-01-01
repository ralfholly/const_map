# const_map -- a read-only, std::map-like associative array.

## Introduction

A `const_map` is built around a given array of key/value pairs (a so-called mapping table), sorted by key in ascending order. Since element lookup is done via binary search, the time
complexity is O(log(n)).

A typical example:
```c++
static const const_map<int, const char*>::value_type COLOR_STR[] = {
    { 111, "red"   },
    { 222, "green" },
    { 333, "blue"  },
};

const_map<int, const char*> color_strings(COLOR_STR);

// Simple lookup.
EXPECT_EQ("green", color_strings[222]);

// Lookup via 'find'.
auto iter = color_strings.find(333);
EXPECT_TRUE(iter != color_strings.end());
EXPECT_EQ("blue", iter->second);

// Lookup via 'find' failed.
iter = color_strings.find(12345);
EXPECT_TRUE(iter == color_strings.end());
```

## Sentinels

One problem with `const_map` is that using `operator[]` to look-up a non-exitent element yields undefined behavior. While some would say that this nicely mirrors the behavior of out-of-bounds array access, others would rather have a more resilient behavior. The latter can be achieved by adding an (otherwise unused) sentinel value to the mapping table:

```c++
static const const_map<int, const char*>::value_type COLOR_STR[] = {
    { 111, "red"   },  // <-- begin()
    { 222, "green" },
    { 333, "blue"  },  // last element of mapping table
    // Sentinel
    {  -1, nullptr },  // <-- end()
};

const_map<int, const char*> color_strings(COLOR_STR, const_map_sentinel::yes);

// No match found.
EXPECT_EQ(nullptr, color_strings[12345]);
EXPECT_EQ(color_strings.end()->second, color_strings[12345]);
EXPECT_EQ(nullptr, color_strings[999]);

// Lookup via 'find'.
auto iter = color_strings.find(12345);
EXPECT_TRUE(iter == color_strings.end());
iter = color_strings.find(999);
EXPECT_TRUE(iter == color_strings.end());
```

The only constraint on the sentinel value is that the key value must be unique, that is, it's not already used in the mapping table. Further, the sentinel's value should also be unique such that its value can be unambigously interpreted as "not found". 

What the sentinel basically does is make the iterator that `end()` returns "dereferenceable".
