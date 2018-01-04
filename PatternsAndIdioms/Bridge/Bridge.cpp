#include <iostream>
#include <string>

// Bridge Pattern Idiom.

// Motivation:

// (1) With typical class definitions, the object representation is usually hard-coupled with its implementation. 
//     This forces the developer to make an object inheriting such object to inherit the base object's implementation if 
//     if it were to inherit its representation and vice versa.

// (2) Strict 'IS-A' inheritance scheme is prone to combinatorial explosion. 

// Solution:

// (*) Create a separate Interface/Abstract Class for the object representation and its implementation.

// (*) Maintain a reference of an implementation class as a field in the representation class.

// (*) Keep the implementation members private and declare the base representation class as a friend of the base 
//     implementation class.

// (*) Separate inheritance trees can be built for both the implementation class and representation class.

// (*) To reduce coupling of each implementation class derivative to its representation class, put all the elementary processing to
//     inside the base implementation class so the representation class doesn't need to be aware of all the base implementation 
//     class derivatives.

// Structure:


class BehaviourImplementation {
  
  friend class BaseObject;

protected:
  
  BehaviourImplementation (void) {
  }
  
  virtual ~BehaviourImplementation (void) noexcept {
  }
  
  virtual void BehaviourCalledBy (const std::string& executor_name) const = 0;
  
  
  static BehaviourImplementation* CreateDefault (void);  
  
  static BehaviourImplementation* CreateFirst (void);
  
  static BehaviourImplementation* CreateSecond (void);
};


class Default : public BehaviourImplementation {
  
  friend class BehaviourImplementation;

protected:
  
  Default (void)
      
      : BehaviourImplementation () {
  }
  
  virtual ~Default (void) noexcept override {
  }
  
  virtual void BehaviourCalledBy (const std::string& executor_name) const override {
    
    std::cout << "Default behaviour executed from " << executor_name << ".\n";
  }
};


class First : public BehaviourImplementation {
  
  friend class BehaviourImplementation;

protected:
  
  First (void)
      
      : BehaviourImplementation () {
  }
  
  virtual ~First (void) noexcept override {
  }
  
  virtual void BehaviourCalledBy (const std::string& executor_name) const override {
    
    std::cout << "First behaviour executed from " << executor_name << ".\n";
  }
};


class Second : public BehaviourImplementation  {
  
  friend class BehaviourImplementation;

protected:
  
  Second (void)
      
      : BehaviourImplementation () {
  }
  
  virtual ~Second (void) noexcept override {
  }  
  
  virtual void BehaviourCalledBy (const std::string& executor_name) const override {
    
    std::cout << "Second behaviour executed from " << executor_name << ".\n";
  }
};


BehaviourImplementation* BehaviourImplementation::CreateDefault (void) {
  
  return new Default ();
}

BehaviourImplementation* BehaviourImplementation::CreateFirst (void) {
  
  return new First ();
}

BehaviourImplementation* BehaviourImplementation::CreateSecond (void) {
  
  return new Second ();
}



class BaseObject {

public:
  
  enum class Behaviour {Default, First, Second};

  virtual ~BaseObject (void) noexcept {
    
    delete this->implementation;
  }
  
  const BaseObject& SetBehaviour (const Behaviour& new_behaviour) {
    
    delete this->implementation;
    
    switch (new_behaviour) {
      
      case Behaviour::Default:
        
        this->implementation = BehaviourImplementation::CreateDefault ();
        
        break;
      
      case Behaviour::First:
        
        this->implementation = BehaviourImplementation::CreateFirst ();
        
        break;
      
      case Behaviour::Second:
        
        this->implementation = BehaviourImplementation::CreateSecond ();
        
        break;
    }
    
    return *this;
  }
  
  void ExecuteBehaviour (void) const {
    
    this->implementation->BehaviourCalledBy (this->name);
  }

protected:
  
  BaseObject (void) 
      
      : implementation (nullptr) {
    
    this->SetBehaviour (Behaviour::Default);
  } 
  
  std::string name;

private:
  
  BehaviourImplementation* implementation;
};


class ObjectOne : public BaseObject {

public:
  
  ObjectOne (void)
      
      : BaseObject () {
    
    this->name = "ObjectOne";
  }
  
  virtual ~ObjectOne (void) noexcept override {
  }
};


class ObjectTwo : public BaseObject {

public:
  
  ObjectTwo (void)
      
      : BaseObject () {
    
    this->name = "ObjectTwo";
  }
  
  virtual ~ObjectTwo (void) noexcept override {
  }
};

int main (int arg_count, char* arg_vector []) {

  //Demo of Bridge Pattern:
  
  ObjectOne object_one;
  
  object_one.ExecuteBehaviour ();

  object_one.SetBehaviour (BaseObject::Behaviour::First).ExecuteBehaviour ();

  object_one.SetBehaviour (BaseObject::Behaviour::Second).ExecuteBehaviour ();


  ObjectTwo object_two;

  object_two.ExecuteBehaviour ();

  object_two.SetBehaviour (BaseObject::Behaviour::First).ExecuteBehaviour ();

  object_two.SetBehaviour (BaseObject::Behaviour::Second).ExecuteBehaviour ();
  
  
  return 0;
}
