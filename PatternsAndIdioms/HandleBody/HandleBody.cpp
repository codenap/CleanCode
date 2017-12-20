#include <iostream>
#include <string>

// The Handle Body Idiom.

// Motivation:

// (1) Although access specifiers certainly helps towards the principle of encapsulation, the implementation and the representation
//     of the object is still hard-coupled to each other. This means that a change on the implementation of the object, will require 
//     a recompilation of the representation code (since they're written in the same spot).

// (2) We take a hit on the object extensibility if we keep the implementation of the code in the same place as its representation
//     since each representation methods are hard-coupled with the well-hidden but highly specialized implementation code.
//     What this entails for us is that it will be unnecessarily difficult for us to change around our object implementation if
//     something better comes up in the near future.

// Solution:

// (*) Create two objects: one for implementation and one for representation. 

// (*) The representation will be fully transparent with each necessary method being accessible to the public. 

// (*) As for the implementation, all methods will be private. 
//     This requires the implementation object to declare the representation object as a 'friend.' 

// (*) Any attempt to access a representation method is internally just a delegation to an implementation method.

// Structure:


class Implementation {
  
  friend class Representation;

private:
  
  Implementation (void) {
  }

  ~Implementation (void) noexcept {
  }

  void Behaviour (void) const {
    
    std::cout << "Behaviour called from the Implementation class through the Representation class.\n";
  }

};


class Representation {
  
public:
  
  Representation (void) 
      
      : implementation_(new Implementation ()) {
  }

  ~Representation (void) noexcept {
    
    delete this->implementation_;
    
    this->implementation_ = nullptr;
  }

  void ExecuteBehaviour (void) const {
  
    this->implementation_->Behaviour ();  
  }

private:

  Implementation* implementation_;

};


int main (int arg_count, char* arg_vector []) {
  
  // Demonstration of the Handle Body Idiom:

  Representation representation_object;
  
  representation_object.ExecuteBehaviour ();

  return 0;
}
