#include <iostream>
#include <string>

// Counted Body Idiom.

// Motivation:

// (1) Naive object assignment is quite expensive. Reasoning to this statement is that the compiler's default assignment constructor performs a 
//     recursive member-wise copy (shallow copy). This works fairly well if your members are small, non-reference types such as char, double, etc.
//     However, imagine if your members are larger, more complex types like a matrix concrete data type decorated with all the fancy data structures
//     the STL provides. This can even be worse if the member is a reference type which can cause unwanted memory access if you're not careful.

// (2) The above can be avoided if we indeed use pointers. Say pointer1 points to the same object as pointer 2. Fairly efficient as both doesn't
//     hold the same yet distinct copies their underlying object. However, this can be messy to manage for the client; this is not easy to use.

// Solution:

// (*) Maintain an object structure as defined in the HandleBody.cpp idiom.

// (*) Add a reference counter to the implementation class.

// (*) Whenever a copy is done in the representation, the pointer to the same implementation class is copied to the desired representation.

// (*) Let the representation class manage the implementation memory. Simply decrement the reference count if a representation is deleted and 
//     increment if an assignment occurs. If the reference count to the implementation class is 0 by the end of a reference count decrement,
//     then that signals that the implementation is no longer needed and will have to be deallocated from the heap.

// Structure:


class Implementation {

  friend class Representation;

private:
  
  Implementation (void)

      : reference_count (0) {
  }

  ~Implementation (void) noexcept {
  }

  void Behaviour (void) const {
  
    std::cout << "Behaviour is executed from the Implementation class through the Representaiton class\n";
  }

  int64_t reference_count;
};


class Representation {

public:
  Representation (void)
   
      : implementation (new Implementation ()) {

    this->IncrementReferenceCount ();
  }

  Representation (const Representation& another_representation) {
    
    this->implementation = another_representation.implementation;

    this->IncrementReferenceCount ();
  }

  ~Representation (void) noexcept {
  
    this->DecrementReferenceCount ();
  }

  void operator= (const Representation& another_representation) {
  
    this->DecrementReferenceCount ();

    this->implementation = another_representation.implementation;

    this->IncrementReferenceCount ();
  }

  void ExecuteBehaviour (void) const {
    
    this->implementation->Behaviour ();
    
    std::cout << "\tRepresentation address: " << this << " || Implementation address: " << this->implementation << '\n';
  }


private:

  void DecrementReferenceCount (void) {
    
    --this->implementation->reference_count;

    if (this->implementation->reference_count > 0) {
      
      return;
    }

    delete this->implementation;

    this->implementation == nullptr;
  }

  void IncrementReferenceCount (void) {
    
    ++this->implementation->reference_count;
  }

  Implementation* implementation;
};



int main (int arg_count, char* arg_vector []) {
  
  // Demo of the Counted Body Idiom.

  // Empty constructor:
  Representation first_representation_object;

  first_representation_object.ExecuteBehaviour ();

  // Using copy constructor:
  Representation second_representation_object (first_representation_object);

  second_representation_object.ExecuteBehaviour ();

  // Using assignment operator:
  Representation third_representation_object;

  third_representation_object = second_representation_object;

  third_representation_object.ExecuteBehaviour ();
  
  return 0;
}
