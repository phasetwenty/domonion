/*
 * IToString.h
 *
 *  Created on: Feb 7, 2013
 *      Author: chris
 */

#ifndef DOMONION_INTERFACES_H_
#define DOMONION_INTERFACES_H_

#include <string>

class IToString {
public:
  virtual std::string* ToString() const = 0;

  virtual ~IToString() { }
};

class IViewable : public IToString {
public:
  virtual std::string* Info() const = 0;

  virtual ~IViewable() { }
};

#endif /* DOMONION_INTERFACES_H_ */
