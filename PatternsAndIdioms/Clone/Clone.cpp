#include <iostream>
#include <string>

// Clone Pattern.

// Motivation:

// (1) Suppose you were in a position where you created a class inheritance hierarchy that all inherits from an abstract/interface base class
//     and you decided to virtualize some base class methods intending to store the heap derived class instances to a pointer to the base class.
//     Now, imagine a client code needing to create a copy of the object that the pointer to the base class is pointing to. Simply calling the
//     new operator on the base class wouldn't work as this would create an instance of base class.

// (2) A solution to the above problem can be to create a virtual constructor (pretty much just a selector) on the base class and let the client
//     code call 'Create' on the base class such that the base class creates the correct specified object. This CAN work, but is flawed as (1)
//     the client code will need to be aware of the existence of the derived classes (unwanted coupling) and (2) you will need some sort of RTTI
//     (run-time type identification) to distinguish the derived classes from each other.

// (Better) Solution:

// (*) Define a virtual method called "Clone" ("Copy", "ProduceSimilarPopulationsOfGeneticallyIdenticalIndividualObjects", or anything really)
//     such that the method has the following signature: Base_Class* Derived_class::Clone (void) const.

//     NOTE: Notice the const keyword? Although not necessary, it is a good practice to not modify any members of the invoking object as that
//     is not well-defined through the name of the method. IF you really want such, please following a naming convention that reveals your
//     true intentions, kind like: "CloneAndModifySomeShit" (not recommended).

// (*) The point of the Clone object is to return a copy of ITSELF through the use of shallow copy: return new derived_class (*this)

// (*) Make the all the derived classes override the Clone method such that an invocation of such method, even through the base class pointer,
//     returns the specific copy of the object stored in the base class pointer.

// Structure:

class Base {

public:
  
  explicit Base (const std::string& object_number) 
      
      : object_number (object_number) {
  }

  virtual ~Base (void) noexcept {
  }

  virtual Base* Clone (void) const {
    
    return new Base (*this);
  }

  virtual void ExecuteBehaviour (void) const {
    
    std::cout << this->object_number << " Base class behaviour is executed.\n";
  }

protected:

  std::string object_number;
};



class Derived : public Base {

public:
  
  explicit Derived (const std::string& object_number)
      
      : Base (object_number) {
  }

  virtual ~Derived (void) noexcept override {
  }

  virtual Base* Clone (void) const override {
    return new Derived (*this);
  }

  virtual void ExecuteBehaviour (void) const override {
  
    std::cout << this->object_number << " Derived Class behaviour is executed.\n";
  }
};



int main (int arg_count, char* arg_vector []) {
  
  // Demo of the Clone Pattern:

  // Store Two Objects of different type to a Base pointer:

  Base* first_base_object = new Base ("First");

  Base* first_derived_object = new Derived ("First");

  first_base_object->ExecuteBehaviour ();

  first_derived_object->ExecuteBehaviour ();
  
  // Now perform the Clone Object:

  Base* second_base_object = first_base_object->Clone ();

  Base* second_derived_object = first_derived_object->Clone ();

  second_base_object->ExecuteBehaviour ();

  second_derived_object->ExecuteBehaviour ();

  
  delete second_derived_object;
  
  delete second_base_object;
  
  delete first_derived_object;
  
  delete first_base_object;


  return 0;
} 
