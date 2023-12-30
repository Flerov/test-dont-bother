#include <iostream>
#include <stdio.h>

// Define a template for a node in the dictionary
template <typename K, typename V>
struct DICTIONARY_NODE {
  K Key;
  V Value;
  DICTIONARY_NODE* Flink;  // Next node in the list
  DICTIONARY_NODE* Blink;  // Previous node in the list
};

// Define a template for the dictionary
template <typename K, typename V>
class GenericDictionary {
public:
  GenericDictionary() : ListHead(nullptr) {}

  ~GenericDictionary() {
    RemoveAll();
  }

  // Function to add a key-value pair to the dictionary
  int AddToDictionary(const K& key, const V& value) {
    DICTIONARY_NODE<K, V>* node = (DICTIONARY_NODE<K, V>*)malloc(sizeof(DICTIONARY_NODE<K, V>));
    if (!node) {
      return -1;  // Return an error code or throw an exception
    }

    // Copy the key and value
    node->Key = key;
    node->Value = value;
    node->Flink = nullptr;

    // Add to the dictionary
    if (!ListHead) {
      ListHead = node;
      node->Blink = nullptr;
    } else {
      ListTail->Flink = node;
      node->Blink = ListTail;
    }
    ListTail = node;

    return 0;
  }

// Function to retrieve the value associated with a key
int GetValue(const K& key, V& value) const {
  DICTIONARY_NODE<K, V>* current = ListHead;
  while (current) {
    if (current->Key == key) {
      value = current->Value;
      return 0;
    }
    current = current->Flink;
  }
  return -1;
}

// Function to remove a node from the dictionary
int Remove(const K& key) {
  DICTIONARY_NODE<K, V>* current = ListHead;
  while (current) {
    if (current->Key == key) {
      if (current->Blink) {
        current->Blink->Flink = current->Flink;
      } else {
        ListHead = current->Flink;
      }

      if (current->Flink) {
        current->Flink->Blink = current->Blink;
      } else {
        ListTail = current->Blink;
      }

      free(current);
      return 0;
    }
    current = current->Flink;
  }
  return -1;
}

private:
  DICTIONARY_NODE<K, V>* ListHead;
  DICTIONARY_NODE<K, V>* ListTail;

  // Function to remove all key-value pairs from the dictionary
  void RemoveAll() {
    while (ListHead) {
      DICTIONARY_NODE<K, V>* temp = ListHead;
      ListHead = ListHead->Flink;
      free(temp);
    }
    ListTail = nullptr;
  }
};

int main() {
  GenericDictionary<int, const char*> intStringDictionary;
  
  intStringDictionary.AddToDictionary(1, "One");
  intStringDictionary.AddToDictionary(2, "Two");
  intStringDictionary.AddToDictionary(3, "Three");
  intStringDictionary.AddToDictionary(4, "Four");
  intStringDictionary.AddToDictionary(5, "Five");

  const char* value;
  if (intStringDictionary.GetValue(4, value) == 0) {
    std::cout << "Value for key 1: " << value << std::endl;
  } else {
    std::cout << "Key not found." << std::endl;
  }

  intStringDictionary.Remove(3);
  intStringDictionary.GetValue(1, value);
  printf("Want 1: Get: %s\n", value);
  intStringDictionary.GetValue(2, value);
  printf("Want 2: Get: %s\n", value);
  intStringDictionary.GetValue(4, value);
  printf("Want 4: Get: %s\n", value);
  intStringDictionary.GetValue(5, value);
  printf("Want 5: Get: %s\n", value);




  return 0;
}

