// Filename: eggObject.cxx
// Created by:  drose (17Jan99)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) 2001 - 2004, Disney Enterprises, Inc.  All rights reserved
//
// All use of this software is subject to the terms of the Panda 3d
// Software license.  You should have received a copy of this license
// along with this source code; you will also find a current copy of
// the license at http://etc.cmu.edu/panda3d/docs/license/ .
//
// To contact the maintainers of this program write to
// panda3d-general@lists.sourceforge.net .
//
////////////////////////////////////////////////////////////////////

#include "eggObject.h"

TypeHandle EggObject::_type_handle;


////////////////////////////////////////////////////////////////////
//     Function: EggObject::Constructor
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
EggObject::
EggObject() {
}


////////////////////////////////////////////////////////////////////
//     Function: EggObject::Copy constructor
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
EggObject::
EggObject(const EggObject &copy) : 
  TypedReferenceCount(copy),
  _user_data(copy._user_data),
  _default_user_data(copy._default_user_data)
{
}


////////////////////////////////////////////////////////////////////
//     Function: EggObject::Copy assignment operator
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
EggObject &EggObject::
operator = (const EggObject &copy) {
  TypedReferenceCount::operator = (copy);
  _user_data = copy._user_data;
  _default_user_data = copy._default_user_data;
  return *this;
}

////////////////////////////////////////////////////////////////////
//     Function: EggObject::Destructor
//       Access: Published, Virtual
//  Description:
////////////////////////////////////////////////////////////////////
EggObject::
~EggObject() {
}

////////////////////////////////////////////////////////////////////
//     Function: EggObject::set_user_data
//       Access: Published
//  Description: Sets the user data associated with this object.  This
//               may be any EggUserData-derived object.  The egg
//               library will do nothing with this pointer, except to
//               hold its reference count and return the pointer on
//               request.
//
//               The EggObject maintains multiple different
//               EggUserData pointers, one for each unique type (as
//               reported by get_type()).  If you know that only one
//               type of EggUserData object will be added in your
//               application, you may use the query functions that
//               accept no parameters, but it is recommended that in
//               general you pass in the type of your particular user
//               data, to allow multiple applications to coexist in
//               the same egg data.
//
//               This pointer is also copied by the copy assignment
//               operator and copy constructor.
////////////////////////////////////////////////////////////////////
void EggObject::
set_user_data(EggUserData *user_data) {
  _user_data[user_data->get_type()] = user_data;
  _default_user_data = user_data;
}

////////////////////////////////////////////////////////////////////
//     Function: EggObject::get_user_data
//       Access: Published
//  Description: Returns the user data pointer most recently stored on
//               this object, or NULL if nothing was previously
//               stored.
////////////////////////////////////////////////////////////////////
EggUserData *EggObject::
get_user_data() const {
  return _default_user_data;
}

////////////////////////////////////////////////////////////////////
//     Function: EggObject::get_user_data
//       Access: Published
//  Description: Returns the user data pointer of the indicated type,
//               if it exists, or NULL if it does not.
////////////////////////////////////////////////////////////////////
EggUserData *EggObject::
get_user_data(TypeHandle type) const {
  UserData::const_iterator ui;
  ui = _user_data.find(type);
  if (ui != _user_data.end()) {
    return (*ui).second;
  }
  return NULL;
}

////////////////////////////////////////////////////////////////////
//     Function: EggObject::has_user_data
//       Access: Published
//  Description: Returns true if a generic user data pointer has
//               recently been set and not yet cleared, false
//               otherwise.
////////////////////////////////////////////////////////////////////
bool EggObject::
has_user_data() const {
  return !_default_user_data.is_null();
}

////////////////////////////////////////////////////////////////////
//     Function: EggObject::has_user_data
//       Access: Published
//  Description: Returns true if the user data pointer of the
//               indicated type has been set, false otherwise.
////////////////////////////////////////////////////////////////////
bool EggObject::
has_user_data(TypeHandle type) const {
  UserData::const_iterator ui;
  ui = _user_data.find(type);
  return (ui != _user_data.end());
}

////////////////////////////////////////////////////////////////////
//     Function: EggObject::clear_user_data
//       Access: Published
//  Description: Removes *all* user data pointers from the node.
////////////////////////////////////////////////////////////////////
void EggObject::
clear_user_data() {
  _user_data.clear();
  _default_user_data.clear();
}

////////////////////////////////////////////////////////////////////
//     Function: EggObject::clear_user_data
//       Access: Published
//  Description: Removes the user data pointer of the indicated type.
////////////////////////////////////////////////////////////////////
void EggObject::
clear_user_data(TypeHandle type) {
  UserData::iterator ui;
  ui = _user_data.find(type);
  if (ui != _user_data.end()) {
    if ((*ui).second == _default_user_data) {
      _default_user_data.clear();
    }
    _user_data.erase(ui);
  }
}

////////////////////////////////////////////////////////////////////
//     Function: EggObject::as_transform
//       Access: Public, Virtual
//  Description: Returns this object cross-cast to an EggTransform
//               pointer, if it inherits from EggTransform, or NULL if
//               it does not.
////////////////////////////////////////////////////////////////////
EggTransform *EggObject::
as_transform() {
  return NULL;
}
