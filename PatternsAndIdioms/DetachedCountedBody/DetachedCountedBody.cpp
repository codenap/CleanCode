#include <iostream>
#include <string>

// Detached Counted Body Idiom.

// Motivation:

// (1) With the Counted Body Idiom, we've seen how we can be fairly efficient with large object copies through the use of reference counts. 
//     In general, however, developers have to work with library objects with no support for reference counting whatsoever. If the library
//     is too good to pass up, a typical fix is to create a wrapper class that has a reference count as a field and delegates all method calls
//     to the library code. This is can be good but, concerning efficiency, each method call has a "CALL" overhead attached to it. Not a big
//     but it kinda defeats the purpose of being efficient with copies if we're not efficient with a simple call.

// (Better) Solution:

// (*) Design the representation object such that there is a separate reference counter object and a separate implementation object.

// (*) When a copy is initiated, both the references to the reference counter object and implementation object is copied.

// (*) Just like in Counted Body, once the reference counter hits zero or lower, we deallocate the implementation object, but in this case,
//     along with the reference counter object.

// (*) Just like in Counted Body, leave all the memory management to the representation object.

// Structure:


class LibraryObject {

  friend class Representation;

private:

  LibraryObject (void) {
  }
  
  ~LibraryObject (void) noexcept {
  }

  void Behaviour (void) const {
  
    std::cout << "Behaviour executed from an unmodifiable Library Object from the Representation class.\n";
  }
};



class Representation {

public:

  Representation (void) 

      : implementation (new LibraryObject ())
      
      , reference_count (new int64_t (1)) {
  }

  Representation (const Representation& another_representation) {
    
    this->implementation  = another_representation.implementation;

    this->reference_count = another_representation.reference_count;

    this->IncrementReferenceCount ();
  }

  ~Representation (void) noexcept {
  
    this->DecrementReferenceCount ();
  }

  void operator= (const Representation& another_representation) {
    
    this->DecrementReferenceCount ();

    this->implementation = another_representation.implementation;

    this->reference_count = another_representation.reference_count;

    this->IncrementReferenceCount ();
  }

  void ExecuteBehaviour (void) {
    
    this->implementation->Behaviour ();
    
    std::cout << "\tRepresentation Addresss: " << this 

        << " || Reference Counter Address: " << this->reference_count 

        << " || Library Object Implementation Address: " << this->implementation

        << '\n';
  }


private:  

  LibraryObject* implementation;

  int64_t* reference_count;

  void DecrementReferenceCount  (void) {
    
    --*(this->reference_count);

    if (*this->reference_count > 0) {
      return;
    }

    delete this->implementation;

    this->implementation = nullptr;

    delete this->reference_count;

    this->implementation = nullptr;
  }

  void IncrementReferenceCount (void) {
    
    ++*(this->reference_count);
  }
};



int main (int arg_count, char* arg_vector []) {
 
  // Demo of Detached Counted Body Idiom.
  
  // Using Empty Constructor: 
  Representation first_representation_object;    
 
  first_representation_object.ExecuteBehaviour ();
  
  // Using Copy Constructor:
  Representation second_representation_object = first_representation_object;

  second_representation_object.ExecuteBehaviour ();

  // Using Assignment Operator:
  Representation third_representation_object;

  third_representation_object = second_representation_object;

  third_representation_object.ExecuteBehaviour ();

  return 0;
}
