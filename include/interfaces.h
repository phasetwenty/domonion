/*
 * IToString.h
 *
 *  Created on: Feb 7, 2013
 *      Author: chris
 */

#ifndef DOMONION_INTERFACES_H_
#define DOMONION_INTERFACES_H_

class IToString {
public:
  virtual std::string ToString() const = 0;

  virtual ~IToString();
};

class IInfo : public IToString {
public:
  virtual std::string Info() const = 0;
//  virtual std::string ToString() const = 0;

};

#endif /* DOMONION_INTERFACES_H_ */